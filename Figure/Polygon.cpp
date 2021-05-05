#include "Polygon.h"
#include <iostream>
#include <QDebug>

using namespace Mcoder;
using std::vector;



Polygon::Polygon()
{
    /* 初始为红色 */
    this->red = this->green = this->blue = 0;
}

Polygon::Polygon(vector<Point *>& points)
{
    this->points.clear();   // 清空
    this->points.insert(this->points.end(),points.begin(),points.end());
}


void Polygon::push(int x, int y)
{
    this->points.push_back(new Point(x,y));   // 插入一个点
}


vector<Point *> *Polygon::getPoints()
{
    return &this->points;
}

void Polygon::setPoints(vector<Point *>& points)
{
    this->points.clear();   // 清空
    this->points.insert(this->points.end(),points.begin(),points.end());
}


int Polygon::getSize()
{
    return this->points.size();
}

Point* Polygon::getPoint(int i)
{
    if(i >= (int)this->points.size() || i < 0)
    {
        return NULL;
    }
    return this->points[i];
}

Point *Polygon::getEndPoint()
{
    return this->points.back();
}

void Polygon::setColor(Color color)
{
    this->red = color.red();
    this->green = color.green();
    this->blue = color.blue();
}

