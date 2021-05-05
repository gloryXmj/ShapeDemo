#include "Line.h"
using namespace Mcoder;

Line::Line()
{

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

void Line::setHeadPt(Point ptHead)
{
    this->ptHead = ptHead;
}

void Line::setTailPt(Point ptTail)
{
    this->ptTail = ptTail;
}

void Line::setPt(Point ptHead, Point ptTail)
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

void Line::setColor(Color clr)
{
    this->m_color = clr;
}

Color Line::getColor()
{
    return m_color;
}
