#ifndef PIXCONTROL_H
#define PIXCONTROL_H

#include <windows.h>
#include "Color.h"

static HDC hdc = GetWindowDC( GetDesktopWindow());
//

inline void WritePixel(int x,int y ,Color clr)
{

    SetPixel(hdc,x,y,RGB(clr.red(),clr.green(),clr.blue()));
}

inline void WritePixel(float x,float y ,Color clr)
{
    SetPixel(hdc,x,y,RGB(clr.red(),clr.green(),clr.blue()));
}

#endif // PIXCONTROL_H
