#ifndef RECT_H
#define RECT_H
#include "Point.h"
#include "Color.h"

namespace Mcoder {
class Rect
{
public:
    Rect();

    Rect(const Rect &rect);

    /*!
     * \brief Rect
     * \param xmax  矩形框的x最大值
     * \param xmin  矩形框的x最小值
     * \param ymax  矩形框的y最大值
     * \param ymin  矩形框的y最小值
     */

    Rect(const double xmax, const double xmin,const double ymax,const double ymin);

    /*!
     * \brief Rect
     * \param ptTL 左上角的点
     * \param ptBR 右下角的点
     */

    Rect(const Point ptTL, const Point ptBR );

    void setPoint(const Point ptTL, const Point ptBR);

    /*!
     * \brief xmax
     * \return
     */
    double xmax() const;
    double xmin() const;
    double ymax() const;
    double ymin() const;

private:
    double x_max,x_min,y_max,y_min;
    Color color;
};
}
#endif // RECT_H
