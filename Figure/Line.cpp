#include "Line.h"
using namespace Mcoder;

Line::Line()
{

}

Line::Line(const double x0, const double y0, const double x1, const double y1)
{
    this->ptHead = Point(x0,y0);
    this->ptTail = Point(x1,y1);
}

Line::Line(const Line &line)
{
    this->ptHead = line.ptHead;
    this->ptTail = line.ptTail;
}

void Line::operator=(Line line)
{
    this->ptHead = line.ptHead;
    this->ptTail = line.ptTail;
}

void Line::setHeadPt(const Point ptHead)
{
    this->ptHead = ptHead;
}

void Line::setTailPt(const Point ptTail)
{
    this->ptTail = ptTail;
}

void Line::setPt(const Point &ptHead,const Point &ptTail)
{
    this->ptHead = ptHead;
    this->ptTail = ptTail;
}

Point Line::getHeadPt() const
{
    return this->ptHead;
}

Point Line::getTailPt() const
{
    return this->ptTail;
}

void Line::setColor(const Color clr)
{
    this->m_color = clr;
}

Color Line::getColor() const
{
    return m_color;
}
