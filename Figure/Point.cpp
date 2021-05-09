#include "Point.h"
#include <iostream>
using namespace Mcoder;         // 自定义的类型都放在这个命名空间里了

Point::Point()
{
    this->x = 0;
    this->y = 0;
}

Point::Point(const double x, const double y)
{
    this->x = (int)x;
    this->y = (int)y;
}

/**   拷贝构造函数
* * @brief Point::Point
* * @param point
* * @return
*/

Point::Point(const Point &point)
{
    this->x = point.x;
    this->y = point.y;
}

void Point::setX(const double x)
{
    this->x = x;
}

double Point::getX() const
{
    return this->x;
}

void Point::setY(const double y)
{
    this->y = y;
}

double Point::getY() const
{
    return this->y;
}

/**
 * @Author xmj
 * @brief  设置点
 * @param  int x
 * @param  int y
 * @date   2021/04/27
 */
void Point::set(const double x,const double y)
{
    this->x = x;
    this->y = y;
}

// 复制另一个点
void Point::copy(const Point &point)
{
    this->x = point.x;
    this->y = point.y;
}

/**
 * @Author xmj
 * @brief  输出点的信息
 * @return void
 * @date   2017/04/27
 */
void Point::print() const
{
    std::cout<< "<" << this->x
             << "," << this->y <<">";
}

// 重载运算符等于号
Point &Point::operator =(const Point &point)
{
    this->x = point.x;
    this->y = point.y;

    return *this;
}

Point &Point::operator -(const Point &point)
{
    this->x-=point.x;
    this->y-=point.y;
    return *this;
}

Point &Point::operator +(const Point &point)
{
    this->x+=point.x;
    this->y+=point.y;
    return *this;
}

bool Point::operator ==(const Point &point)
{
 return (this->x == point.x&&this->y == point.y);
}
