#include "fillingcontroler.h"
using namespace filling ;

namespace filling{

FillingControler::FillingControler()
{

}

}
/*
void FillingControler::ScanLinePolygonFill(const Polygon& py, int color)

{

    assert(py.IsValid());

    int ymin = 0;

    int ymax = 0;

    GetPolygonMinMax(py, ymin, ymax);

    std::vector< std::list<EDGE> > slNet(ymax - ymin + 1);

    InitScanLineNewEdgeTable(slNet, py, ymin, ymax);

    //PrintNewEdgeTable(slNet);

    HorizonEdgeFill(py, color); //水平边直接画线填充

    ProcessScanLineFill(slNet, ymin, ymax, color);

}


void FillingControler::InitScanLineNewEdgeTable(std::vector< std::list<EDGE> >& slNet, const Polygon& py, int ymin, int ymax)
{
    EDGE e;
    for(int i = 0; i < py.GetPolyCount(); i++)
    {
        const Point2D& ps = py.pts[i];
        const Point2D& pe = py.pts[(i + 1) % py.GetPolyCount()];
        const Point2D& pss = py.pts[(i - 1 + py.GetPolyCount()) % py.GetPolyCount()];
        const Point2D& pee = py.pts[(i + 2) % py.GetPolyCount()];
        if(pe.y != ps.y) //不处理水平线
        {
            e.dx = double(pe.x - ps.x) / double(pe.y - ps.y);
            if(pe.y > ps.y)
            {
                e.xi = ps.x;
                if(pee.y >= pe.y)
                    e.ymax = pe.y - 1;
                else
                    e.ymax = pe.y;
                slNet[ps.y - ymin].push_front(e);
            }
            else
            {
                e.xi = pe.x;
                if(pss.y >= ps.y)
                    e.ymax = ps.y - 1;
                else
                    e.ymax = ps.y;
                slNet[pe.y - ymin].push_front(e);
            }
        }
    }
}


void FillingControler::ProcessScanLineFill(std::vector< std::list<EDGE> >& slNet, int ymin, int ymax, int color)
{
 std::list<EDGE> aet;
 for(int y = ymin; y <= ymax; y++)
 {
 InsertNetListToAet(slNet[y - ymin], aet);
 FillAetScanLine(aet, y, color);
 //删除非活动边
 RemoveNonActiveEdgeFromAet(aet, y);
 //更新活动边表中每项的xi值，并根据xi重新排序
 UpdateAndResortAet(aet);
 }
}


bool FillingControler::IsEdgeOutOfActive(EDGE e, int y)
{
 return (e.ymax == y);
}

void FillingControler::RemoveNonActiveEdgeFromAet(std::list<EDGE>& aet, int y)
{
 aet.remove_if(std::bind2nd(std::ptr_fun(IsEdgeOutOfActive), y));
}
*/
