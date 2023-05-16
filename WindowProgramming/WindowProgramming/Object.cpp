#include "Object.h"

void Object::init(HINSTANCE hins, LPCWSTR image, POINT size)
{
	Bit = (HBITMAP)LoadBitmap(hins, image);
	drawSize = size;
}

void Object::setResRect(RECT r)
{
	drawRect = r;
}

void Object::setLoc(POINT p)
{
	center = p;
}

void Object::draw(HDC hdc)
{
	HDC memdc = CreateCompatibleDC(hdc);
	SelectObject(memdc, Bit);

	RECT dstR = {
			center.x - drawSize.x,
			center.y - drawSize.y,
			2 * drawSize.x,
			2 * drawSize.y
	};

	TransparentBlt(hdc, dstR.left, dstR.top, dstR.right, dstR.bottom, memdc, drawRect.left, drawRect.top, drawRect.right, drawRect.bottom, RGB(255, 255, 255));
}

POINT Object::getCenter()
{
	return center;
}

void Object::move(POINT m)
{
	center.x += m.x;
	center.y += m.y;
}

