#ifndef PIXCONTROL_H
#define PIXCONTROL_H

#include <windows.h>

HDC hdc = GetWindowDC( GetDesktopWindow());

void WritePixel(int x,int y ,int value)
{
    SetPixel(hdc,x,y,RGB(255,0,0));
}

void WritePixel(float x,float y ,int value)
{
    SetPixel(hdc,x,y,RGB(255,0,0));
}

#endif // PIXCONTROL_H
