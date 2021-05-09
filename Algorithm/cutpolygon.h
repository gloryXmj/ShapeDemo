/*!
   1.裁剪多边形和被裁剪的多变型需要保证顺时针 且起点不变
   2.被裁剪的多边形只能是凸多边形
*/

#ifndef CUTPOLYGON_H
#define CUTPOLYGON_H
#include "Polygon.h"
#include "Point.h"

class CutPolygon
{

    using PolyGon = Mcoder::Polygon;
    using Point = Mcoder::Point;
    using Edge = Mcoder::Edge;
public:
    struct ExPoint{
        Mcoder::Point pt;
        bool exist = false;
    };
    CutPolygon();
    void execCutPolygon();

    /*!
     * \brief setClipPts 裁剪多变形的数据 （输入数据不用闭合 即首位数据可以不一致）
     * \param clipPts
     */

    void setClipPts(std::vector<Point*> clipPts);
    /*!
     * \brief setPolygon 待切割的多边形数据 （输入数据不用闭合 即首位数据可以不一致）
     * \param polygonPts
     */
    void setPolygon(std::vector<Point*> polygonPts);
    /*!
     * \brief clipFunc  裁剪函数
     * \param output
     */
    void clipFunc(std::vector<Point> &output);
private:
    ExPoint intersect(Edge *c,Edge *p);  /// 交点计算于判断
    bool inside(Point *p, Edge *c);      ///
    std::vector<Point*> clipShapePts;
    std::vector<Point*> polygonPts;
};

#endif // CUTPOLYGON_H
