#pragma once
#include "Object.h"
#include <math.h>

class map : public Object
{
public:
    void ConvertToMaskImage(HBITMAP* image)
    {

        BITMAP bmp;
        GetObject(*image, sizeof(BITMAP), &bmp);


        int width = bmp.bmWidth;
        int height = bmp.bmHeight;


        HDC hdc = GetDC(NULL);
        HDC memDC = CreateCompatibleDC(hdc);
        HBITMAP maskImage = CreateCompatibleBitmap(hdc, width, height);
        SelectObject(memDC, maskImage);


        BitBlt(memDC, 0, 0, width, height, hdc, 0, 0, SRCCOPY);
        BitBlt(memDC, 0, 0, width, height, hdc, 0, 0, SRCINVERT);


        SelectObject(memDC, *image);
        BitBlt(memDC, 0, 0, width, height, memDC, 0, 0, SRCAND);


        DeleteDC(memDC);
        ReleaseDC(NULL, hdc);
        DeleteObject(maskImage);
    }
};