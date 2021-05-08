#ifndef POLYGON_H
#define POLYGON_H
#include <vector>
#include <list>
#include "Point.h"
#include "Edge.h"
#include "edges.h"
#include "Color.h"

using std::vector;
using std::list;
#define MIN_POINT_SIZE 3

namespace Mcoder {
class Polygon
{
public:
    Polygon();
    Polygon(vector<Point *> &points);
    /**
     * @author xmj
     * @brief  插入一个新的点
     * @param  int x, int y 点坐标
     * @date   2021/04/28
     */
    void push(int x, int y);
    /**
     * @author xmj
     * @brief  获取多边形的点
     * @date   2021/04/28
     */
    vector<Point *> * getPoints();
    /**
     * @brief setPoints
     * @param points
     */
    void setPoints(vector<Point *>& points);
    /*!
     * \brief getSize 获得该多边形有多少个顶点
     * \return
     */
    int getSize();
    /**
     * @author xmj
     * @brief  获得指定的点
     * @param  int i 第i个点
     * @date   2021/04/28
     */
    Point* getPoint(int i);
    /*!
     * \brief getEndPoint 获取第一个点
     * \return
     */
    Point *getEndPoint();
    /**
     * @author xmj
     * @brief  绘制多边形
     * @param  int line_strip = 0 -> 折线，首尾不相连 1-> 多边形，首尾相连
     * @date   2021/04/28
     */
    void setColor(Color color);       // 将QColor转换为rgb
    /*!
     * \brief getColor 获取多边形的颜色
     * \return
     */
    Color getColor(){return Color(red,green,blue);}
    double getRed(){return this->red;}
    void setRed(double red){this->red = red;}
    double getGreen(){return this->green;}
    void setGreen(double green){this->green = green;}
    double getBlue(){return this->blue;}
    void setBlue(double blue){this->blue = blue;}
    /*!
     * \brief isColckWise  是否为顺时针图形
     * \return
     */
    bool isColckWise() const;

    /*!
     * \brief isConvex 是否为凸多边形
     * \return
     */
    bool isConvex() const;

private:
    vector<Point*> points;       // 点
    double red, green, blue;        // 绘图的颜色

};
}

#endif // POLYGON_H
