#include "Object.h"

void Object::init(HINSTANCE hins, LPCWSTR image)
{
	Bit = (HBITMAP)LoadBitmap(hins, image);
}

void Object::setResRect(RECT r)
{
	drawRect = r;
}

void Object::setLoc(POINT p)
{
	center = p;
}

void Object::setSize(POINT size)
{
	drawSize = size;
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
	if (dirChange) {
		StretchBlt(memdc, drawRect.left, drawRect.top, drawRect.right, drawRect.bottom, memdc, drawRect.left + drawRect.right, drawRect.top, -drawRect.right, drawRect.bottom, SRCCOPY);
	}
	TransparentBlt(hdc, dstR.left, dstR.top, dstR.right, dstR.bottom, memdc, drawRect.left, drawRect.top, drawRect.right, drawRect.bottom, RGB(255, 255, 255));
	DeleteObject(memdc);
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

RECT Object::getDrawRect()
{
	return drawRect;
}

void Object::setColRect(RECT colR)
{
	colRect = colR;
}

RECT Object::getColRect()
{
	return colRect;
}

void Object::drawCol(HDC hdc, RECT clientRect)
{
	HDC memdc = CreateCompatibleDC(hdc);
	HBITMAP hb = CreateCompatibleBitmap(hdc, clientRect.right, clientRect.bottom);
	SelectObject(memdc, hb);

	HBRUSH hbrush = CreateSolidBrush(RGB(255, 0, 0));
	
	RECT colR = getColRect();
	FrameRect(memdc, &colR, hbrush);
	

	TransparentBlt(hdc, 0, 0, clientRect.right, clientRect.bottom, memdc, clientRect.left, clientRect.top, clientRect.right, clientRect.bottom, RGB(0, 0, 0));

	DeleteObject(hbrush);
	DeleteObject(memdc);
	DeleteObject(hb);
}

bool Object::CheckCollision(RECT otherRect)
{
	if (getColRect().right < otherRect.left || getColRect().left > otherRect.right || getColRect().bottom < otherRect.top || getColRect().top > otherRect.bottom) {
		col = false;
	}
	else {
		col = true;
	}
	return col;
}

bool Object::getCol()
{
	return col;
}

bool Object::getDirChange()
{
	return dirChange;
}

void Object::setDirChange(bool is)
{
	dirChange = is;
}

