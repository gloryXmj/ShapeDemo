#ifndef PIXSHAPE_H
#define PIXSHAPE_H
#include <vector>
#include <iostream>

#include "Point.h"
#include "Color.h"

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
    static void Line_inefficiency(int x0,int y0,int x1,int y1,Color clr);
    /*!
     * \brief Line  基本增量算法的实现
     * \param x0
     * \param y0
     * \param x1
     * \param y1
     * \param value
     */
    static void Line(int x0,int y0,int x1,int y1,Color clr);
    /*!
     * \brief MidpointLine  中点线算法
     * \param x0
     * \param y0
     * \param x1
     * \param y1
     * \param value
     */
    static void MidpointLine(int x0,int y0,int x1,int y1,Color clr);
    /*!
     * \brief DoubleStepLine 双步画线算法
     * \param x0
     * \param y0
     * \param x1
     * \param y1
     * \param value
     */
    static void DoubleStepLine(int x0,int y0,int x1,int y1,Color clr);
    /*!
     * \brief CirclePoints 八方向对称圆的
     * \param x
     * \param y
     * \param value
     */

    static void CirclePoints(float x,float y , Color clr);
    /*!
     * \brief PointCircle_inefficiency
     * \param radius
     * \param value
     */
    static void  PointCircle_inefficiency(int radius , Color clr);
    /*!
     * \brief MidPointCircle  中点圆扫描转换算法
     * \param radius
     * \param value
     */
    static void MidPointCircle(int radius , Color clr);
    /**
     * @brief MidPointCircle2  扫描转换圆的整数型中点算法
     * @param radius
     * @param value
     */
    static void MidPointCircle_int(int radius , Color clr);
    /*!
     * \brief MidPointCircle_Second_Order_Diff
     * \param radius
     * \param value
     */

    static void MidPointCircle_Second_Order_Diff(int radius , Color clr);
    /*!
     * \brief Rect
     * \param ptTL
     * \param ptBR
     * \param value
     */

    static void Rect(Mcoder::Point ptTL ,Mcoder::Point ptBR,Color clr);

    /*!
     * \brief Polygon
     * \param pts
     * \param value
     * \param isSealOff  是否封闭
     */
    static void Polygon(std::vector<Mcoder::Point*> &pts ,Color clr,bool isSealOff = false);
};
#endif // PIXSHAPE_H
