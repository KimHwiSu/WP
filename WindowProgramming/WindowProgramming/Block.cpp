#include "Block.h"

void Block::init(HINSTANCE hins, LPCWSTR image)
{
	Object::init(hins, image);
	setResRect(IdleRect);
	setSize(IdleSize);
	POINT p = getCenter();
	RECT r{p.x - 30, p.y - 10,p.x+30, p.y +11};
	setColRect(r);

	whRate = {};
	dbRate = {};

}

void Block::destroy(RECT r)
{
}
