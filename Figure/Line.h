#ifndef LINE_H
#define LINE_H
#include "Point.h"
#include "Color.h"

namespace Mcoder {
class Line
{
public:
    Line();
    Line(const Line &line);
    void operator=(Line line);
    void setHeadPt(Point ptHead);
    void setTailPt(Point ptTail);
    void setPt(Point ptHead,Point ptTail);
    Point getHeadPt() const;
    Point getTailPt() const;
    void setColor(Color clr);
    Color getColor();
private:
    Color m_color;
    Point ptHead,ptTail;
};
}
#endif // LINE_H
