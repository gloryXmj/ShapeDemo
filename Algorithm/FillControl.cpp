#include "FillControl.h"
#include "PixControl.hpp"
#include "pixshape.h"
#include <QDebug>

#include <stack>

namespace SCAN_LINE_FILL {

FillControl::FillControl()
{

}

FillControl::FillControl(FillControl::Polygon *polygon)
{
    this->polyGon = polygon;
}

void FillControl::setPolygon(Mcoder::Polygon *polygon)
{
    this->polyGon = polygon;
}

void FillControl::paint(int line_strip)
{
    assert(polyGon);
    PixShape::Polygon(*(this->polyGon->getPoints()),this->polyGon->getColor(),line_strip);
}

void FillControl::scanLine()
{
    assert(polyGon);
    if(this->polyGon->getSize() < 3)
    {
        // 如果小于三个点，则不是多边形，无法填充
        qDebug()<<"小于三个点，不是多边形 ";
        return ;
    }

    // 确定扫描线的范围
    this->min.copy(*this->polyGon->getPoint(0));
    this->max.copy(*this->polyGon->getPoint(0));
    int size = this->polyGon->getSize();

    for(int i = 0; i < size; i++)
    {
        Point * temp = this->polyGon->getPoint(i);

        if(temp->getX() < min.getX())
        {
            min.setX(temp->getX());
        }
        else if(temp->getX() > max.getX())
        {
            max.setX(temp->getX());
        }

        if(temp->getY() < min.getY())
        {
            min.setY(temp->getY());
        }
        else if(temp->getY() > max.getY())
        {
            max.setY(temp->getY());
        }
    }

    // 确定了扫描线范围 min.y -> max.y
    this->buildEdgeTable();
    this->scan();
}

bool FillControl::buildEdgeTable()
{
    assert(polyGon);
    if(this->polyGon->getSize() < MIN_POINT_SIZE)
    {
        return false ;     // 三条边算不上多边形
    }

    this->sortedEdgeTable.clear();  // 清空边表
    this->edge_horizontal.clear();  // 清空水平边

    int ymin = this->min.getY();
    int ymax = this->max.getY();
    int size_edgeTable = ymax - ymin + 1;               //表格大小
    this->sortedEdgeTable.resize(size_edgeTable);       // 设置边表大小

    Point* p_start = this->polyGon->getPoint(0);
    Point* p_end;
    int size = this->polyGon->getSize();     // 获取有多少个点

    for(int i = 1; i<size; i++)
    {
        p_end = this->polyGon->getPoint(i);
        // 第一条边开始
        this->addEdgeToTable(p_start, p_end);
        p_start = p_end;
    }

    p_end = this->polyGon->getPoint(0);
    this->addEdgeToTable(p_start, p_end);

    return true;
}

void FillControl::scan()
{
    assert(polyGon);
    vector<EdgeS *> edge_active;                                // 新建活动边表
    int y_min = this->min.getY();                               // 获得扫描区域的最低端
    int size_sortedEdgeTable = this->sortedEdgeTable.size();    // 获得Sorted Edge Table 大小
    for(int i = 0; i < size_sortedEdgeTable; i++)
    {
        int y_scan = y_min + i;                     // 当前扫描的位置
        // 清除已经失效的边
        if(!edge_active.empty())
        {
            vector<EdgeS *>::iterator iter;
            for(iter = edge_active.begin() ; iter < edge_active.end(); iter++)
            {
                EdgeS *temp = *iter;
                if(y_scan > temp->ymax)
                {
                    edge_active.erase(iter);
                    // 防止删除一个点以后，内存位置发生改变，或者删除了最后一个点，导致出现异常
                    if(!edge_active.empty())
                        iter = edge_active.begin();     // 从头重新扫描
                    else
                        break;
                }
            }
        }
        // 将新的线段加入到边表中
        if(this->sortedEdgeTable[i] != NULL)
        {
            vector<EdgeS *> *temp = this->sortedEdgeTable[i];
            int size_temp = temp->size();
            for(int i = 0; i < size_temp; i++)
            {
                edge_active.push_back((*temp)[i]);
            }
        }
        // 画当前扫描线
        this->printScanLine(edge_active, y_scan);   // 画扫描线
    }
    this->printHorizontalLine(this->edge_horizontal);// 画水平线
}

void FillControl::print()
{
    assert(polyGon);
    std::cout << "Points:";
    int p_size = this->polyGon->getSize();
    for(int i = 0; i < p_size; i++)
    {
        (this->polyGon->getPoint(i))->print();
        std::cout << " ";
    }
}

void FillControl::addEdgeToTable(Point *p_start, Point *p_end)
{
    assert(polyGon);
    // 判断哪个点在上方
    Point * p_up, *p_down;
    //相等的时候表示水平边
    if(p_start->getY() == p_end->getY() )
    {
        // 水平边不加入数组中，加入水平边表中单独处理
        this->edge_horizontal.push_back(new Edge(*p_start, *p_end));
        return;
    }
    else if(p_start->getY() > p_end->getY())
    {
        // p_start 点在上方
        p_up = p_start;
        p_down = p_end;
    }
    else /*if(p_start->getY() < p_end->getY())*/
    {
        // p_end 点在上方
        p_up = p_end;
        p_down = p_start;
    }
    // 获得EdgeS数据的重要部分
    double dx = 1.0 * (p_up->getX() - p_down->getX()) /
            (p_up->getY() - p_down->getY());        // 斜率的倒数
    int y_min = (int)p_down->getY();                // 线段最低端y值
    double xi = p_down->getX();                     // 最下端x值
    int y_max = p_up->getY();                       // 线段最顶端 y值
    // ----------------------每条边 y方向上缩短一点
    xi = xi + dx;
    y_min = y_min + 1;

    int y_id = y_min - this->min.getY();        // 应该插入表中的位置
    vector<EdgeS *> * list_temp = this->sortedEdgeTable[y_id];
    if(list_temp == NULL)
    {
        // 如果这个队列为空的话，新建队列
        this->sortedEdgeTable[y_id] = list_temp
                = new vector<EdgeS *>();      // 新建队列
    }
    list_temp->push_back(new EdgeS(xi, dx, y_max));     // 将EdgeS插入到队列中
}

void FillControl::printScanLine(vector<EdgeS *> activeEdgeTable, int y)
{
    assert(polyGon);
    if(activeEdgeTable.empty()){
        qDebug() << u8"未画扫描线,y="<<y;
        return;
    }
    list<double> intersection;  // 交点
    vector<EdgeS*>::iterator iter_activeEdge;           // 活动边表的迭代器
    for(iter_activeEdge = activeEdgeTable.begin();
        iter_activeEdge < activeEdgeTable.end();
        iter_activeEdge++)
    {
        EdgeS *edge_temp = *iter_activeEdge;            // 遍历每条边
        double xi = edge_temp->xi;                      // 获取当前 x坐标
        edge_temp->xi = edge_temp->xi + edge_temp->dx;  // 计算下一次的Xi坐标
        intersection.push_back(xi);                     // 加入相交队列
    }
    intersection.sort();        // 对交点排序
    list<double >::iterator iter = intersection.begin();        // 迭代器
    while(iter != intersection.end())
    {
        double left = *iter;            // 左交点
        iter++;
        if(iter == intersection.end())
        {
            qDebug() << u8"交点个数为奇数个,交点个数： "<< activeEdgeTable.size()
                     <<",x:"<<left<<",y:"<<y;
            break;
        }
        double right = *iter;           // 右交点
        iter++;
        /// this->red, this->green, this->blue  // 设置颜色
        if(left==right) // 如果两条线是重合的，会填一条线
        {
            return;
        }
        for(int i =left; i <= right; i++)
            WritePixel(i,y,this->polyGon->getColor());
    }
}

void FillControl::printHorizontalLine(vector<Edge *> edgeHorizontal)
{
    assert(polyGon);

    if(edgeHorizontal.empty())
    {
        return;
    }
    vector<Edge *>::iterator iter = edgeHorizontal.begin();
    while(iter != edgeHorizontal.end())
    {
        Edge* edge_temp= *iter;     // 获得水平边
        ///设置颜色 this->red, this->green, this->blue
        int left = edge_temp->getStart()->getX();
        int right = edge_temp->getEnd()->getX();
        int y = edge_temp->getStart()->getY();
        if(left==right) // 如果两条线是重合的，会填一条线
        {
            return;
        }
        for(int i =left; i <= right; i++)
            WritePixel(i,y,this->polyGon->getColor());
        iter++;
    }
}


}


namespace SEED_SCAN_LINE_FILL {

int color_pixel_map[MAX_MAP_WIDTH][MAX_MAP_HEIGHT] = { { 0 } };
int map_width = 0;
int map_height = 0;

FillControl::FillControl()
{

}

FillControl::FillControl(FillControl::Polygon *polygon)
{
    this->polyGon = polygon;
}

void FillControl::setPolygon(FillControl::Polygon *polygon)
{
    this->polyGon = polygon;
}

void FillControl::paint(int line_strip)
{
    assert(polyGon);
    PixShape::Polygon(*(this->polyGon->getPoints()),this->polyGon->getColor(),line_strip);
}

void FillControl::ScanLineSeedFill(int x, int y, int new_color, int boundary_color)
{
    std::stack<Point> stk;
    stk.push(Point(x, y)); //第1步，种子点入站
    while(!stk.empty())
    {
        Point seed = stk.top(); //第2步，取当前种子点
        stk.pop();
        //第3步，向左右填充
        int count = FillLineRight(seed.getX(), seed.getY(), new_color, boundary_color);//向'cf?右'd3?填'cc?充'b3?
        int xRight = seed.getX() + count - 1;
        count = FillLineLeft(seed.getX() - 1, seed.getY(), new_color, boundary_color);//向'cf?左'd7?填'cc?充'b3?
        int xLeft = seed.getX() - count;
        //第4步，处理相邻两条扫描线
        SearchLineNewSeed(stk, xLeft, xRight, seed.getY() - 1, new_color, boundary_color);
        SearchLineNewSeed(stk, xLeft, xRight, seed.getY() + 1, new_color, boundary_color);
    }

}

void FillControl::SearchLineNewSeed(std::stack<Point>& stk, int xLeft, int xRight,
                                    int y, int new_color, int boundary_color)
{
    int xt = xLeft;
    bool findNewSeed = false;
    while(xt <= xRight)
    {
        findNewSeed = false;
        while(IsPixelValid(xt, y, new_color, boundary_color) && (xt < xRight))
        {
            findNewSeed = true;
            xt++;
        }
        if(findNewSeed)
        {
            if(IsPixelValid(xt, y, new_color, boundary_color) && (xt == xRight))
                stk.push(Point(xt, y));
            else
                stk.push(Point(xt - 1, y));
        }
        /*向右跳过内部的无效点（处理区间右端有障碍点的情况）*/
        int xspan = SkipInvalidInLine(xt, y, xRight, new_color, boundary_color);
        xt += (xspan == 0) ? 1 : xspan;
        /*处理特殊情况,以退出while(x<=xright)循环*/
    }
}
int FillControl::FillLineRight(int x, int y, int new_color, int boundary_color)
{
    int xt = x;
    while(GetPixelColor(xt, y) != boundary_color)
    {
        SetPixelColor(xt, y, new_color);
        xt++;
    }
    return xt - x;
}
int FillControl::FillLineLeft(int x, int y, int new_color, int boundary_color)
{
    int xt = x;
    while(GetPixelColor(xt, y) != boundary_color)
    {
        SetPixelColor(xt, y, new_color);
        xt--;
    }

    return x - xt;
}
/*点不是边界，而且没有填充过*/
bool FillControl::IsPixelValid(int x, int y, int new_color, int boundary_color)
{
    return ( (GetPixelColor(x, y) != boundary_color)
             && (GetPixelColor(x, y) != new_color) );
}
int FillControl::SkipInvalidInLine(int x, int y, int xRight, int new_color, int boundary_color)
{
    int xt = x;
    while(!IsPixelValid(xt, y, new_color, boundary_color) && (xt < xRight))
    {
        xt++;
    }

    return xt - x;
}




int FillControl::GetPixelColor(int x, int y)
{
    assert((x >= 0) && (x < MAX_MAP_WIDTH));
    assert((y >= 0) && (y < MAX_MAP_HEIGHT));

    return color_pixel_map[y][x];
}

void FillControl::SetPixelColor(int x, int y, int color)
{
    assert((x >= 0) && (x < MAX_MAP_WIDTH));
    assert((y >= 0) && (y < MAX_MAP_HEIGHT));

    color_pixel_map[y][x] = color;
}

}


