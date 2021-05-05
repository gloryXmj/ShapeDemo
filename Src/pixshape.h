#ifndef PIXSHAPE_H
#define PIXSHAPE_H
#include <vector>
#include <iostream>

class Point2D
{
public:
    explicit Point2D(double x, double y);
    Point2D(const Point2D &pt);
    double x();
    double y();
private :
    double m_x;
    double m_y;
};


class PixShape
{
public:
    PixShape();
    /*!
     * \brief Line_inefficiency  低效的绘制直线的方式
     * \param x0
     * \param y0
     * \param x1
     * \param y1
     * \param value
     */
    static void Line_inefficiency(int x0,int y0,int x1,int y1,int value);
    /*!
     * \brief Line  基本增量算法的实现
     * \param x0
     * \param y0
     * \param x1
     * \param y1
     * \param value
     */
    static void Line(int x0,int y0,int x1,int y1,int value);
    /*!
     * \brief MidpointLine  中点线算法
     * \param x0
     * \param y0
     * \param x1
     * \param y1
     * \param value
     */
    static void MidpointLine(int x0,int y0,int x1,int y1,int value);
    /*!
     * \brief DoubleStepLine 双步画线算法
     * \param x0
     * \param y0
     * \param x1
     * \param y1
     * \param value
     */
    static void DoubleStepLine(int x0,int y0,int x1,int y1,int value);

    /*!
     * \brief CirclePoints 八方向对称圆的
     * \param x
     * \param y
     * \param value
     */

    static void CirclePoints(float x,float y , int value);

    /*!
     * \brief PointCircle_inefficiency
     * \param radius
     * \param value
     */
    static void  PointCircle_inefficiency(int radius , int value);

    /*!
     * \brief MidPointCircle  中点圆扫描转换算法
     * \param radius
     * \param value
     */
    static void MidPointCircle(int radius , int value);

    /**
     * @brief MidPointCircle2  扫描转换圆的整数型中点算法
     * @param radius
     * @param value
     */
    static void MidPointCircle_int(int radius , int value);

    /*!
     * \brief MidPointCircle_Second_Order_Diff
     * \param radius
     * \param value
     */

    static void MidPointCircle_Second_Order_Diff(int radius , int value);

    /*!
     * \brief Rect
     * \param ptTL
     * \param ptBR
     * \param value
     */
    static void Rect(Point2D ptTL ,Point2D ptBR,int value);

    /*!
     * \brief Polygon
     * \param pts
     * \param value
     */
    static void Polygon(std::vector<Point2D> pts ,int value);

};



#endif // PIXSHAPE_H
