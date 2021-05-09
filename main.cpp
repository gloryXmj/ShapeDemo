#include <QCoreApplication>
#include <windows.h>
#include <time.h>
#include <iostream>
#include <thread>
#define ENLAGE_MAGNIFY_POWER 50

#include "Polygon.h"
#include "Point.h"
#include "pixshape.h"
#include "FillControl.h"
#include "cutline.h"
#include "cutpolygon.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    HDC hdc = GetWindowDC( GetDesktopWindow() );

    // 创建红色1像素宽度的实线画笔
    HPEN hpen1 = CreatePen( PS_SOLID, 1, RGB(255,0,0) );

    // 创建绿色5像素宽度的破折画笔，如果你想创建其他种类的画笔请参阅MSDN
    HPEN hpen2 = CreatePen( PS_DASH, 5, RGB(0,255,0) );

    // 创建一个实体蓝色画刷
    HBRUSH hbrush1 = CreateSolidBrush( RGB(0,0,255) );

    // 创造一个透明的画刷，如果你想创建其他种类的画刷请参阅MSDN
    HBRUSH hbrush2 = (HBRUSH)GetStockObject( NULL_BRUSH );

    // 将hpen1和hbrush1选进HDC，并保存HDC原来的画笔和画刷
    HPEN hpen_old = (HPEN)SelectObject( hdc, hpen1 );
    HBRUSH hbrush_old = (HBRUSH)SelectObject( hdc, hbrush1 );
    /*
        // 在(40,30)处画一个宽200像素，高50像素的矩形
        Rectangle( hdc, 40, 30, 40+200, 30+50 );

        // 画个椭圆看看
        Ellipse( hdc, 40, 200, 40+200, 200+50 );

        // 画个(0,600)到(800,0)的直线看看
        MoveToEx( hdc, 0, 600, NULL );
        LineTo( hdc, 800, 0 );
        // 在(700,500)处画个黄点，不过这个点只有一像素大小，你细细的看才能找到
        SetPixel( hdc, 700, 500, RGB(255,255,0) );
    */

    while(1)
    {
        clock_t timeBegin = clock();

        //    PixShape::Line(0,0,1920,1080,0);

        //    PixShape::Line_inefficiency(0,0,1920,1080,0);

        //    PixShape::MidpointLine(0,0,1920,1080,0);

        //    PixShape::MidPointCircle(200,0);

        //    PixShape::PointCircle_inefficiency(500,0);

        //    PixShape::MidPointCircle_Second_Order_Diff(200,0);
        //    PixShape::Rect(Point(0,0),Point(600,400),0);


        /**扫描线填充算法**/
        //        std::vector<Mcoder::Point*> pts;
        //        pts.push_back(new Mcoder::Point(1*ENLAGE_MAGNIFY_POWER,3*ENLAGE_MAGNIFY_POWER));
        //        pts.push_back(new Mcoder::Point(5*ENLAGE_MAGNIFY_POWER,1*ENLAGE_MAGNIFY_POWER));
        //        pts.push_back(new Mcoder::Point(13*ENLAGE_MAGNIFY_POWER,5*ENLAGE_MAGNIFY_POWER));
        //        pts.push_back(new Mcoder::Point(9*ENLAGE_MAGNIFY_POWER,10*ENLAGE_MAGNIFY_POWER));
        //        pts.push_back(new Mcoder::Point(7*ENLAGE_MAGNIFY_POWER,6*ENLAGE_MAGNIFY_POWER));
        //        pts.push_back(new Mcoder::Point(2*ENLAGE_MAGNIFY_POWER,8*ENLAGE_MAGNIFY_POWER));
        //        Mcoder::Polygon polygon(pts);
        //        polygon.setColor(Color(rand()%255,rand()%255,rand()%255));
        //        FillControl fillControl(&polygon);
        //        fillControl.paint(1);
        //        fillControl.scanLine();


        //        CutLine *cut =  new  Liang_Barsky::Liang_Barsky_CutLine();
        //        CutLine *cut = new Cohen_Suther_land::Cohen_Suther_CutLine();
        //        cut->setRect(Mcoder::Rect(320,120,240,150));
        //        Mcoder::Line line(100,100,2000,2000);
        //        line.setColor(Color(0,255,0));
        //        cut->addLine(&line);
        //        std::cout<< cut->exeCutLine()<<std::endl;
        ///https://blog.csdn.net/chengxuyuanliwanwan/article/details/96866762

        std::vector<Mcoder::Point*> polygonPts;
        ///凹多边形
        polygonPts.push_back(new Mcoder::Point(700,100));
        polygonPts.push_back(new Mcoder::Point(1100,900));
        polygonPts.push_back(new Mcoder::Point(700,500));
        polygonPts.push_back(new Mcoder::Point(300,900));
        polygonPts.push_back(new Mcoder::Point(700,100));

        //        Mcoder::Polygon polygon(polygonPts);
        //        polygon.setColor(Color(rand()%255,rand()%255,rand()%255));
        //        PixShape::Polygon(polygonPts,Color(rand()%255,rand()%255,rand()%255),true);

        std::vector<Mcoder::Point*> clipPts;
        ///裁剪区域在上面的 裁剪后还是一个整体的
        //        clipPts.push_back(new Mcoder::Point(400,0));
        //        clipPts.push_back(new Mcoder::Point(800,0));
        //        clipPts.push_back(new Mcoder::Point(800,600));
        //        clipPts.push_back(new Mcoder::Point(400,600));
        ///裁剪区域在下面  裁剪后变成两个独立的模块
        clipPts.push_back(new Mcoder::Point(200,550));
        clipPts.push_back(new Mcoder::Point(1200,550));
        clipPts.push_back(new Mcoder::Point(1200,1000));
        clipPts.push_back(new Mcoder::Point(200,1000));


        //        clipPts.push_back(new Mcoder::Point(400,0));
        //        PixShape::Polygon(clipPts,Color(rand()%255,rand()%255,rand()%255),true);

        CutPolygon cutploy;
        cutploy.setClipPts(clipPts);
        cutploy.setPolygon(polygonPts);
        std::vector<Mcoder::Point> outPts;
        cutploy.clipFunc(outPts);
        std::cout << outPts.size()<<std::endl;
        std::vector<Mcoder::Point*> pOutPts;
        for(int i =0 ;i < (int)outPts.size();i++)
            pOutPts.push_back(new Mcoder::Point(outPts.at(i)));
        PixShape::Polygon(pOutPts,Color(rand()%255,rand()%255,rand()%255),true);
        std::cout << "本次绘制用时 : " << clock()- timeBegin << "ms"<<std::endl;
        Sleep(100);
    }
    // 恢复原来的画笔和画刷
    SelectObject(hdc, hpen_old );
    SelectObject(hdc, hbrush_old );
    return a.exec();
}
