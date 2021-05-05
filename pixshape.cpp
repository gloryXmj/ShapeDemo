#include "pixshape.h"
#include "PixControl.hpp"

#include <math.h>
#include <float.h>

//#define MIN_SCREEN_X 1920/3
//#define MIN_SCREEN_Y 1080/3

#define MIN_SCREEN_X 0
#define MIN_SCREEN_Y 0

PixShape::PixShape()
{
}

void PixShape::Line_inefficiency(int x0, int y0, int x1, int y1, Color clr)
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
        WritePixel(x,(int)(y+0.5),clr);
        y = m*x + B;
    }
}

void PixShape::Line(int x0, int y0, int x1, int y1, Color clr)
{
    /*这里假设 -1<= m <= 1 , x1 > x0
    x以单位步长从x0增长到x1*/
    float dy,dx,y,m,x;
    dx = x1 - x0;
    dy = y1 - y0;
    if (dx!=0) {
        m = dy/dx;
        float epsonl = m >= 0?0.5:-0.5;
        if(fabs(m) > 1)
        {
            x = y0>y1?x1:x0;
            for(y = (y0>y1?y1:y0);y<=(y1>y0?y1:y0);y++)
            {
                WritePixel((int)(x+epsonl),(int)y,clr);
                x+=1/m;
            }
        }
        else
        {
            y = x0>x1?y1:y0;
            for(x = (x0>x1?x1:x0);x<=(x1>x0?x1:x0);x++)
            {
                WritePixel((int)x,(int)(y+epsonl),clr);
                y+=m;
            }
        }
    }
    else
    {
        for(y = (y0>y1?y1:y0);y<=(y1>y0?y1:y0);y++)
        {
            WritePixel((int)x0,(int)(y),clr);
        }
    }
}

void PixShape::MidpointLine(int x0, int y0, int x1, int y1, Color clr)
{
    int dx ,dy, incrE, incrNE,d,x,y;
    dx = x1-x0;
    dy = y1-y0;
    d = dy*2-dx;
    incrE = dy*2;
    incrNE = (dy-dx)*2;
    x = x0;
    y = y0;
    WritePixel(x,y,clr);
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
        WritePixel(x,y,clr);
    }
}

void PixShape::DoubleStepLine(int x0, int y0, int x1, int y1, Color clr)
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

void PixShape::CirclePoints(float x, float y, Color clr)
{
    //这里当 x==y 时只需要绘制四个点就可以了 需要做特殊处理
    WritePixel(x+MIN_SCREEN_X,y+MIN_SCREEN_Y,clr);
    WritePixel(y+MIN_SCREEN_X,x+MIN_SCREEN_Y,clr);
    WritePixel(x+MIN_SCREEN_X,-y+MIN_SCREEN_Y,clr);
    WritePixel(-y+MIN_SCREEN_X,x+MIN_SCREEN_Y,clr);
    //    if(fabs(x-y) < FLT_EPSILON)
    {
        WritePixel(y+MIN_SCREEN_X,-x+MIN_SCREEN_Y,clr);
        WritePixel(-x+MIN_SCREEN_X,-y+MIN_SCREEN_Y,clr);
        WritePixel(-y+MIN_SCREEN_X,-x+MIN_SCREEN_Y,clr);
        WritePixel(-x+MIN_SCREEN_X,y+MIN_SCREEN_Y,clr);
    }
}

void PixShape::PointCircle_inefficiency(int radius, Color clr)
{
    int x ;
    float y ;
    float d;
    x = 0;
    y = radius;
    d = 5.0/4 - radius;
    CirclePoints(x,y,clr);
    for(x = 1 ;x < radius; x++ )
    {
        CirclePoints(x,y,clr);
        y = sqrt(powf(radius,2)-powf(x,2));
    }
}

void PixShape::MidPointCircle(int radius, Color clr)
{
    int x ,y ;
    float d;
    x = 0;
    y = radius;
    d = 5.0/4 - radius;
    CirclePoints(x,y,clr);
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
        CirclePoints(x,y,clr);
    }
}

void PixShape::MidPointCircle_int(int radius, Color clr)
{
    int x,y,d;
    x = 0;
    y = radius;
    d = 1- radius;
    CirclePoints(x,y,clr);
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
        CirclePoints(x,y,clr);
    }
}

void PixShape::MidPointCircle_Second_Order_Diff(int radius, Color clr)
{
    int x ,y , d, deltaE,deltaSE;
    x = 0;
    y = radius;
    d = 1 - radius;
    deltaE = 3;
    deltaSE = 5 - radius*2;
    CirclePoints(x,y,clr);
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
        CirclePoints(x,y,clr);
    }
}

void PixShape::Rect(Mcoder::Point ptTL, Mcoder::Point ptBR,Color clr)
{
    Line(ptTL.getX()+MIN_SCREEN_X,ptTL.getY()+MIN_SCREEN_Y,ptBR.getX()+MIN_SCREEN_X,ptTL.getY()+MIN_SCREEN_Y,clr);
    Line(ptBR.getX()+MIN_SCREEN_X,ptTL.getY()+MIN_SCREEN_Y,ptBR.getX()+MIN_SCREEN_X,ptBR.getY()+MIN_SCREEN_Y,clr);
    Line(ptBR.getX()+MIN_SCREEN_X,ptBR.getY()+MIN_SCREEN_Y,ptTL.getX()+MIN_SCREEN_X,ptBR.getY()+MIN_SCREEN_Y,clr);
    Line(ptTL.getX()+MIN_SCREEN_X,ptBR.getY()+MIN_SCREEN_Y,ptTL.getX()+MIN_SCREEN_X,ptTL.getY()+MIN_SCREEN_Y,clr);
}

void PixShape::Polygon(std::vector<Mcoder::Point*> &pts, Color clr,bool isSealOff)
{
    if(pts.size()<=2)
    {
        std::cout<<"The number of points cannot be less than three" << std::endl;
        return ;
    }
    std::vector<Mcoder::Point*>::iterator  ptIter,ptIterLast;
    ptIterLast = pts.begin();
    ptIter = pts.begin();
    ptIter++;
    for(;ptIter!=pts.end();)
    {
        Line((*ptIterLast)->getX()+MIN_SCREEN_X,(*ptIterLast)->getY()+MIN_SCREEN_Y,
             (*ptIter)->getX()+MIN_SCREEN_X,(*ptIter)->getY()+MIN_SCREEN_Y,clr);
        ptIterLast = ptIter;
        ptIter++;
        if(isSealOff)
        {
            if(ptIter==pts.end())
            {
                ptIter =  pts.begin();
                Line((*ptIterLast)->getX()+MIN_SCREEN_X,(*ptIterLast)->getY()+MIN_SCREEN_Y,
                     (*ptIter)->getX()+MIN_SCREEN_X,(*ptIter)->getY()+MIN_SCREEN_Y,clr);
                break;
            }
        }
    }
}





