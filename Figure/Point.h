#ifndef POINT_H
#define POINT_H

namespace Mcoder {
// 自定义点数据结构
class Point
{
public:
    Point();
    Point(const double x, const double y);
    Point(const Point& point);      // 拷贝构造函数

    void setX(const double x);
    double getX() const;
    void setY(const double y);
    double getY() const;
    void set(const double x, const double y);

    void copy(const Point& point);
    void print() const;       // 输出点的信息

    // 重载运算符
    Point &operator =(const Point& point);      // 重载等于号

private:
    double x;   // 点的X坐标
    double y;   // 点的Y坐标
};
}


#endif // POINT_H
