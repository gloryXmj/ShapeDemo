#ifndef EDGE_H
#define EDGE_H
#include "Point.h"

namespace Mcoder {
// 自定义边数据结构
class Edge
{
public:
    Edge();
    Edge(const int a_x, const int a_y, const int b_x, const int b_y);
    Edge(const Point &p_a, const Point &p_b);
    Edge(const Edge &edge);
    ~Edge();

    /**
     * @brief getStart  获得一个端点
     * @return
     */
    Point* getStart();
    /**
     * @brief getEnd   获得另一个端点
     * @return
     */
    Point* getEnd();

    void set(const int a_x,const int a_y,const int b_x,const int b_y);
    void setStart(const int a_x,const int a_y);
    void setEnd(const int b_x,const int b_y);

    void print() const;

private:
    // 这两个点的顺序与画多边形时的顺序一个该是相同的
    Point p_start;
    Point P_end;
};

}


#endif // EDGE_H
