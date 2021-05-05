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




        std::cout << "本次绘制用时 : " << clock()- timeBegin << " ms"<<std::endl;
        Sleep(100);
    }
    // 恢复原来的画笔和画刷
    SelectObject(hdc, hpen_old );
    SelectObject(hdc, hbrush_old );
    return a.exec();
}
