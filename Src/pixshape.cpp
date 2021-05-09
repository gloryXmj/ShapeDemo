#include "pixshape.h"
#include "PixControl.h"

#include <math.h>
#include <float.h>

#define MIN_SCREEN_X 1920/2
#define MIN_SCREEN_Y 1080/2



Point2D::Point2D(double x, double y)
    :m_x(x),
      m_y(y)
{

}

Point2D::Point2D(const Point2D &pt)
{
    Point2D ptTmp = pt;
    m_x = ptTmp.x();
    m_y = ptTmp.y();
}

double Point2D::x()
{
    return m_x;
}

double Point2D::y()
{
    return m_y;
}





PixShape::PixShape()
{

}

void PixShape::Line_inefficiency(int x0, int y0, int x1, int y1, int value)
{
    int x ;
    float dy,dx,y,m;
    dx = x1 - x0;
    dy = y1 - y0;
    y = y0;
    m = dy/dx;
    float B = y1 - m*x1;
    for(x = x0;x<x1;x++)
    {
        WritePixel(x,(int)(y+0.5),value);
        y = m*x + B;
    }
}

void PixShape::Line(int x0, int y0, int x1, int y1, int value)
{
    int x ;
    /*这里假设 -1<= m <= 1 , x1 > x0
    x以单位步长从x0增长到x1*/
    float dy,dx,y,m;
    dx = x1 - x0;
    dy = y1 - y0;
    m = dy/dx;
    y = y0;
    for(x = x0;x<x1;x++)
    {
        WritePixel(x,(int)(y+0.5),value);
        y+=m;
    }
}

void PixShape::MidpointLine(int x0, int y0, int x1, int y1, int value)
{
    int dx ,dy, incrE, incrNE,d,x,y;
    dx = x1-x0;
    dy = y1-y0;
    d = dy*2-dx;
    incrE = dy*2;
    incrNE = (dy-dx)*2;
    x = x0;
    y = y0;
    WritePixel(x,y,value);
    while(x<x1)
    {
        if(d<=0)
        {
            d+=incrE;
            x++;
        }else{
            d += incrNE;
            x++;
            y++;
        }
        WritePixel(x,y,value);
    }
}

void PixShape::DoubleStepLine(int x0, int y0, int x1, int y1, int value)
{
    int curret_x ,inc_1,inc_2,cond,dx ,dy ,d;
    dx = x1 - x0;
    dy = y1 - y0;
    curret_x = x0;
    inc_1 = 4*dy;
    inc_2 = 4*dy- 2*dx;
    cond = 2*dy;
    d = 4*dy -dx;
    while(curret_x<x1)
    {
        if(d<0)
        {

        }else
        {
            if(d<cond)
            {

            }else
            {

            }
        }
    }
}

void PixShape::CirclePoints(float x, float y, int value)
{
    //这里当 x==y 时只需要绘制四个点就可以了 需要做特殊处理
    WritePixel(x+MIN_SCREEN_X,y+MIN_SCREEN_Y,value);
    WritePixel(y+MIN_SCREEN_X,x+MIN_SCREEN_Y,value);
    WritePixel(x+MIN_SCREEN_X,-y+MIN_SCREEN_Y,value);
    WritePixel(-y+MIN_SCREEN_X,x+MIN_SCREEN_Y,value);
    //    if(fabs(x-y) < FLT_EPSILON)
    {
        WritePixel(y+MIN_SCREEN_X,-x+MIN_SCREEN_Y,value);
        WritePixel(-x+MIN_SCREEN_X,-y+MIN_SCREEN_Y,value);
        WritePixel(-y+MIN_SCREEN_X,-x+MIN_SCREEN_Y,value);
        WritePixel(-x+MIN_SCREEN_X,y+MIN_SCREEN_Y,value);
    }
}

void PixShape::PointCircle_inefficiency(int radius, int value)
{
    int x ;
    float y ;
    float d;
    x = 0;
    y = radius;
    d = 5.0/4 - radius;
    CirclePoints(x,y,value);
    for(x = 1 ;x < radius; x++ )
    {
        CirclePoints(x,y,value);
        y = sqrt(powf(radius,2)-powf(x,2));
    }
}

void PixShape::MidPointCircle(int radius, int value)
{
    int x ,y ;
    float d;
    x = 0;
    y = radius;
    d = 5.0/4 - radius;
    CirclePoints(x,y,value);
    while(y>x)
    {
        if(d<0)
        {
            d+=x*2.0 + 3;
            x++;
        }else{
            d += (x-y)*2.0 +5;
            x++;
            y--;
        }
        CirclePoints(x,y,value);
    }
}

void PixShape::MidPointCircle_int(int radius, int value)
{
    int x,y,d;
    x = 0;
    y = radius;
    d = 1- radius;
    CirclePoints(x,y,value);
    while(y>x)
    {
        if(d<0)
        {
            d+=x*2 +3;
            x++;
        }else{
            d+=(x-y)*2 + 5;
            x++;
            y--;
        }
        CirclePoints(x,y,value);
    }
}

void PixShape::MidPointCircle_Second_Order_Diff(int radius, int value)
{
    int x ,y , d, deltaE,deltaSE;
    x = 0;
    y = radius;
    d = 1 - radius;
    deltaE = 3;
    deltaSE = 5 - radius*2;
    CirclePoints(x,y,value);
    while(y > x)
    {
        if(d<0)
        {
            d+=deltaE;
            deltaE+=2;
            deltaSE+=2;
            x++;
        }else{
            d += deltaSE;
            deltaE+=2;
            deltaSE+=4;
            x++;
            y--;
        }
        CirclePoints(x,y,value);
    }
}

void PixShape::Rect(Point2D ptTL, Point2D ptBR,int value)
{
    Line(ptTL.x(),ptTL.y(),ptBR.x(),ptTL.y(),value);
    Line(ptBR.x(),ptTL.y(),ptBR.x(),ptBR.y(),value);
    Line(ptBR.x(),ptBR.y(),ptTL.x(),ptBR.y(),value);
    Line(ptTL.x(),ptBR.y(),ptTL.x(),ptTL.y(),value);
}

void PixShape::Polygon(std::vector<Point2D> pts, int value)
{
    if(pts.size()<=2)
    {
        std::cout<<"The number of points cannot be less than three" << std::endl;
        return ;
    }
    std::vector<Point2D>::iterator  ptIter,ptIterLast;
    ptIterLast = pts.begin();
    ptIter++;
    for(;ptIter!=pts.end();ptIter++)
    {
        Line((*ptIterLast).x(),(*ptIterLast).y(),(*ptIter).x(),(*ptIter).y(),value);
        ptIterLast = ptIter;
    }
    ///combain
    ptIter =  pts.begin();
    Line((*ptIterLast).x(),(*ptIterLast).y(),(*ptIter).x(),(*ptIter).y(),value);
}





