#include "edges.h"

EdgeS::EdgeS()
{

}

/**
 * @Author xmj
 * @brief  构造函数
 * @param  double xi, double dx, int ymax
 * @date   2021/04/27
 */
EdgeS::EdgeS(double xi, double dx, int ymax)
{
    this->xi = xi;
    this->dx = dx;
    this->ymax = ymax;
}
