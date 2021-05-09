#ifndef FILLCONTROL_H
#define FILLCONTROL_H

#include "Point.h"
#include "edges.h"
#include "Edge.h"
#include "Polygon.h"

#include <stack>
#include <vector>
using std::vector;
namespace  SCAN_LINE_FILL {
class FillControl
{
    using Polygon = Mcoder::Polygon;
    using Point = Mcoder::Point;
    using Edge =Mcoder::Edge;

public:
    FillControl();
    FillControl(Polygon *polygon);
    void setPolygon(Polygon *polygon);
    void paint(int line_strip = 0);             // 用来画多边形
    /**
     * @author xmj
     * @brief  扫描线填充算法
     * @date   2021/04/28
     */
    void scanLine();            // 扫描线填充算法
    /**
     * @author xmj
     * @brief  生成边表
     * @return bool
     * @date   2021/04/28
     */
    bool buildEdgeTable();   // 生成sorted edge table
    /**
     *@author xmj
     *@brief  填充 扫描
     *@return void
     *@date   2021/04/28
     */
    void scan();
    /**
     * @author xmj
     * @brief  输出多边形信息
     * @return void
     * @date   2021/04/28
     */
    void print();
    /**
     * @author xmj
     * @brief  设置颜色
     * @param  QColor
     * @return void
     * @date   2021/04/28
     */
private:
    /**
     * @author xmj
     * @brief  添加边到排序边表
     * @param  Point* p_start;
     * @param  Point* p_end;
     * @return 返回值
     * @date   2017/04/09
     */
    void addEdgeToTable(Point *p_start, Point *p_end);
    /**
     * @author xmj
     * @brief  画活动边表的扫描线
     * @param  vector<EdgeS *> activeEdgeTable; 活动边表
     * @param  int y;       // y
     * @return 返回值
     * @date   2021/04/28
     */
    void printScanLine(vector<EdgeS*> activeEdgeTable, int y);
    /**
     * @author xmj
     * @brief  画水平边表的扫描线
     * @param  vector<EdgeS *> edgeHorizontal; 水平边表
     * @param  int y;
     * @return 返回值
     * @date   2021/04/28
     */
    void printHorizontalLine(vector<Edge*> edgeHorizontal);

private:
    Polygon *polyGon = NULL;
    vector<vector<EdgeS*>*> sortedEdgeTable;
    vector<Edge* > edge_horizontal;     // 水平边

    Point min;          // 多边形包围矩形的 左下角
    Point max;          // 多边形包围矩形的 右下角
};
}

namespace SEED_SCAN_LINE_FILL {

const int MAX_MAP_WIDTH = 16;
const int MAX_MAP_HEIGHT = 16;
class FillControl
{
    using Polygon = Mcoder::Polygon;
    using Point = Mcoder::Point;
    using Edge =Mcoder::Edge;

public:
    FillControl();
    FillControl(Polygon *polygon);
    void setPolygon(Polygon *polygon);
    void paint(int line_strip = 0);             // 用来画多边形(非填充多边形)
    void ScanLineSeedFill(int x, int y, int new_color, int boundary_color);
private:
    void SearchLineNewSeed(std::stack<Point> &stk, int xLeft, int xRight, int y, int new_color, int boundary_color);
    bool IsPixelValid(int x, int y, int new_color, int boundary_color);
    int SkipInvalidInLine(int x, int y, int xRight, int new_color, int boundary_color);
    int FillLineLeft(int x, int y, int new_color, int boundary_color);
    int FillLineRight(int x, int y, int new_color, int boundary_color);
    int GetPixelColor(int x, int y);
    void SetPixelColor(int x, int y, int color);
private:
    Polygon *polyGon = NULL;
};
}


#endif // FILLCONTROL_H
