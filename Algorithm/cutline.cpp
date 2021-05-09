#include "cutline.h"
#include "pixshape.h"
#include <iostream>


CutLine::CutLine()
{

}

void CutLine::setRect(CutLine::Rect rect)
{
    this->rect = rect;
}

void CutLine::setLines(std::vector<CutLine::Line *> lines)
{
    this->lines = lines;
}

CutLine::Line *CutLine::getLine(int id)
{
    if(id<0||id>=(int)this->lines.size())
        return NULL;
    return this->lines.at(id);
}

CutLine::iterator CutLine::getHeadLine()
{
    return this->lines.begin();
}

CutLine::iterator CutLine::getTailLine()
{
    return this->lines.end()-1;
}

CutLine::iterator CutLine::getEndLine()
{
    return this->lines.end();
}

void CutLine::addLine(CutLine::Line *line)
{
    this->lines.push_back(line);
}

int CutLine::LinesNum() const
{
    return (int)this->lines.size();
}


namespace Cohen_Suther_land{
#define left 1
#define right 2
#define bottom 4
#define top 8


bool Cohen_Suther_CutLine::exeCutLine(int lineId)
{

    if((int)lines.size() <= lineId||(int)lines.size()<=0)
        return false;

    PixShape::Rect(Point(this->rect.xmin(),this->rect.ymin()),
                   Point(this->rect.xmax(),this->rect.ymax()),Color(0,255,255));

    PixShape::Line((*this->lines.begin())->getHeadPt().getX(),
                   (*this->lines.begin())->getHeadPt().getY(),
                   (*this->lines.begin())->getTailPt().getX(),
                   (*this->lines.begin())->getTailPt().getY(),
                   Color(255,0,0));

    if(lineId==-1)
    {
        for(iterator lineiter = this->lines.begin();lineiter != this->lines.end();lineiter++)
        {
            CS_CutLine(*lineiter);
        }
    }
    else
    {
        CS_CutLine(getLine(lineId));
    }
    return true;
}

//编码
void Cohen_Suther_CutLine::encode(double x,double y,int &code)
{
    int c=0;
    if(x<this->rect.xmin())  {c=c+left;}
    else if(x>this->rect.xmax())  {c=c+right;}
    if(y<this->rect.ymin())  {c=c+bottom;}
    else if(y>this->rect.ymax())  {c=c+top;}
    code=c;
}

int Cohen_Suther_CutLine::CS_CutLine(const Line * line)
{
    double  x1 = line->getHeadPt().getX(),
            y1 = line->getHeadPt().getY(),
            x2 = line->getTailPt().getX(),
            y2 = line->getTailPt().getY();

    int code1=0,code2=0 ,code=0 ;
    int x = 0,y = 0;
    encode(x1,y1,code1);
    encode(x2,y2,code2);
    while(code1!=0||code2!=0)//都在里面时，直接画线，否则进行判断
    {
        if((code1&code2)!=0)return 0;//都在外面舍弃
        code=code1;
        if(code1==0)
            code = code2;
        if((left&code)!=0)
        {x=this->rect.xmin();y=y1+(y2-y1)*(this->rect.xmin()-x1)/(x2-x1);}
        else if((right&code)!=0)
        {x=this->rect.xmax();y=y1+(y2-y1)*(this->rect.xmax()-x1)/(x2-x1);}
        else if ((bottom&code) != 0)
        {y=this->rect.ymin();x=x1+(x2-x1)*(this->rect.ymin()-y1)/(y2-y1);}
        else if ((top&code) != 0)
        {y=this->rect.ymax();x=x1+(x2-x1)*(this->rect.ymax()-y1)/(y2-y1);}

        if(code == code1)
        {x1=x;y1=y; encode(x,y,code1);}
        else
        {x2=x;y2=y; encode(x,y,code2);}
    }
    PixShape::Line(x1,y1,x2,y2,line->getColor());
    return 0;
}
}

namespace Liang_Barsky {

bool Liang_Barsky_CutLine::exeCutLine(int lineId)
{
    if((int)lines.size() <= lineId||(int)lines.size()<=0)
        return false;

    PixShape::Rect(Point(this->rect.xmin(),this->rect.ymin()),
                   Point(this->rect.xmax(),this->rect.ymax()),Color(0,255,255));

    PixShape::Line((*this->lines.begin())->getHeadPt().getX(),
                   (*this->lines.begin())->getHeadPt().getY(),
                   (*this->lines.begin())->getTailPt().getX(),
                   (*this->lines.begin())->getTailPt().getY(),
                   Color(255,0,0));

    if(lineId==-1)
    {
        iterator lineiter;
        for(lineiter = this->lines.begin();lineiter != this->lines.end();lineiter++)
        {
            LiangBarskyLineClip(*lineiter);
        }
    }
    else
    {
        LiangBarskyLineClip(getLine(lineId));
    }
    return true;
}


bool Liang_Barsky_CutLine::ClipT(double q,double d,double &t0,double &t1)
{//当线段完全不可见时，返回false，否则，返回true
    double r;
    if(q<0)
    {
        r=(double)d/(double)q;
        if(r>t1)
            return false;
        else if(r>t0)
        {t0=r;return true;}
    }
    else if(q>0)
    {
        r=(double)d/(double)q;
        if(r<t0)
            return false;
        else if(r<t1)
        {t1=r;return true;}
    }
    else if(d<0)
        return false;
    return true;
}
void Liang_Barsky_CutLine::LiangBarskyLineClip(const Line *line)
{
    double  x0 = line->getHeadPt().getX(),
            y0 = line->getHeadPt().getY(),
            x1 = line->getTailPt().getX(),
            y1 = line->getTailPt().getY();

    double delatx,delaty,t0,t1;
    t0=0;t1=1;
    delatx=x1-x0;
    if(ClipT(-delatx,x0-this->rect.xmin(),t0,t1))
        if(ClipT(delatx,this->rect.xmax()-x0,t0,t1))
        {
            delaty=y1-y0;
            if(ClipT(-delaty,y0-this->rect.ymin(),t0,t1))
                if(ClipT(delaty,this->rect.ymax()-y0,t0,t1))
                {
                    PixShape::Line((int)(x0+t0*delatx),(int)(y0+t0*delaty),
                         (int)(x0+t1*delatx),(int)(y0+t1*delaty),line->getColor());
                    return;
                }
        }
}

}
