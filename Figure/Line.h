#ifndef LINE_H
#define LINE_H
#include "Point.h"
#include "Color.h"

namespace Mcoder {
class Line
{
public:
    Line();
    Line(const double x0, const double y0,const double x1, const double y1);
    Line(const Line &line);
    void operator=(Line line);
    void setHeadPt(const Point ptHead);
    void setTailPt(const Point ptTail);
    void setPt(const Point &ptHead,const Point &ptTail);
    Point getHeadPt() const;
    Point getTailPt() const;
    void setColor(const Color clr);
    Color getColor() const;
private:
    Color m_color;
    Point ptHead,ptTail;
};
}
#endif // LINE_H
