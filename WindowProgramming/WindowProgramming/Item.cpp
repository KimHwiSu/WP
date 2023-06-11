#include "Item.h"

void Item::init(HINSTANCE hins, LPCWSTR image)
{
	Object::init(hins, image, RGB(153, 217, 234));
	setResRect(IdleRect);
	setSize(IdleSize);
	POINT p = getCenter();
	RECT ColR{ p.x - IdleSize.x, p.y - IdleSize.y, p.x + IdleSize.x, p.y + IdleSize.y };
	colPoint = { p.x, ColR.bottom };
	setColRect(ColR);
}

void Item::update(vector<RECT> cols)
{
	if (!getCol()) {
		moveC({ 0, 10 });
		for (const RECT c : cols) {
			if (checkBottom(c)) {
				do {
					moveC({ 0, -1 });
				} while (colPoint.y > c.top);
			}
		}
	}
}

void Item::moveC(POINT s)
{
	Object::move(s);
	POINT p = getCenter();
	RECT ColR{ p.x - IdleSize.x, p.y - IdleSize.y, p.x + IdleSize.x, p.y + IdleSize.y };
	setColRect(ColR);
	colPoint = { p.x, ColR.bottom };
}

bool Item::checkBottom(RECT r)
{
	if (colPoint.x >= r.left && colPoint.x <= r.right && colPoint.y >= r.top && colPoint.y <= r.bottom) {
		return true;
	}
	else {
		return false;
	}
}
