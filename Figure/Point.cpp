﻿#include "Point.h"
#include <iostream>
using namespace Mcoder;         // 自定义的类型都放在这个命名空间里了

Point::Point()
{
    this->x = 0;
    this->y = 0;
}

Point::Point(int x, int y)
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

void Point::setX(int x)
{
    this->x = x;
}

int Point::getX()
{
    return this->x;
}

void Point::setY(int y)
{
    this->y = y;
}

int Point::getY()
{
    return this->y;
}

/**
 * @Author xmj
 * @brief  设置点
 * @param  int x
 * @param  int y
 * @date   2017/04/27
 */
void Point::set(int x, int y)
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
void Point::print()
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
