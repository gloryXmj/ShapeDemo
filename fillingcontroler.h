#ifndef FILLINGCONTROLER_H
#define FILLINGCONTROLER_H
#include "Point2D.h"
#include <vector>
#include <list>

//#include <Polygon>


namespace filling {

///*定义结构体用于活性边表AET和新边表NET*/
//typedef struct EDGE
//{
//    double x;  //x 当前扫描线与边的交点坐标；
//    double dx;   //dx从当前扫描线到下一条扫描线间x的增量（(x2-x1)/(y2-y1)）；
//    double ymax; //ymax 该边所交的最高扫描线
//    EDGE* next;
//}AET,NET;

 typedef struct tagEDGE
 {
     double xi; //x 当前扫描线与边的交点坐标；
     double dx; //dx从当前扫描线到下一条扫描线间x的增量（(x2-x1)/(y2-y1)）；
     int ymax;  //ymax 该边所交的最高扫描线
 }EDGE;


using Polygon = std::vector<Point2D> ;


class FillingControler
{
public:
    FillingControler();
//    //将点构成的多边形转化成边表结构
//    void ScanLinePolygonFill(const Polygon &py, int color);
//private:
//    void InitScanLineNewEdgeTable(std::vector<std::list<EDGE> > &slNet, const Polygon &py, int ymin, int ymax);
//    void ProcessScanLineFill(std::vector<std::list<EDGE> > &slNet, int ymin, int ymax, int color);
//    bool IsEdgeOutOfActive(EDGE e, int y);
//    void RemoveNonActiveEdgeFromAet(std::list<EDGE> &aet, int y);
};

};

#endif // FILLINGCONTROLER_H
