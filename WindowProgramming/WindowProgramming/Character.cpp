#include "Character.h"

void Character::init(HINSTANCE hins, LPCWSTR image)
{
	Object::init(hins, image);
	hi = hins;
	im = image;
	setResRect(IdleRect);
	setSize(IdleSize);
	POINT p = getCenter();
	RECT ColR{ p.x -13, p.y +3, p.x + 13, p.y +33 };
	colPoint = { p.x, ColR.bottom };
	setColRect(ColR);
}

void Character::update(vector<RECT> cols)
{
	Object::init(hi, im);
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
	RECT nextRect = IdleRect;
	nextRect.left += idleDis[state];
	setResRect(nextRect);
	IdleRect = Object::getDrawRect();
	index++;
	if (state != 2) {
		if (index > indexes[state] - 1) {
			index = 0;
			IdleRect.left = 0;
			
			setResRect(IdleRect);
		}
	}
	else {
		if (index > indexes[state] - 1) {
			index = indexes[state] - 1;
			IdleRect.left = index * idleDis[state];
			setResRect(IdleRect);
		}
	}
	POINT p = getCenter();
	RECT ColR{ p.x - 13, p.y + 3, p.x + 13, p.y + 33 };
	colPoint = { p.x, ColR.bottom };
	setColRect(ColR);
}

void Character::changeState(int i)
{
	switch (i) {
	case 0:
		state = 0;
		index = 0;
		IdleRect.left = 0;
		IdleRect.right = 63;
		IdleRect.top = 12;
		break;
	case 1:
		state = 1;
		index = 0;
		IdleRect.left = 0;
		IdleRect.right = 47;
		IdleRect.top = 85;
		break;
	case 2:
		state = 2;
		index = 0;
		IdleRect.left = 0;
		IdleRect.right = 55;
		IdleRect.top = 378;
	}
}

bool Character::getChange()
{
	return stateChange;
}

void Character::setChange(bool is)
{
	stateChange = is;
}

POINT Character::getColPoint()
{
	return colPoint;
}

void Character::setTurn(bool is)
{
	turn = is;
}

bool Character::getTurn()
{
	return turn;
}

bool Character::checkBottom(RECT r)
{
	if (colPoint.x >= r.left && colPoint.x <= r.right && colPoint.y >= r.top && colPoint.y <= r.bottom) {
		return true;
	}
	else {
		return false;
	}
}

void Character::moveC(POINT s)
{
	Object::move(s);
	POINT p = getCenter();
	RECT ColR{ p.x - 13, p.y + 3, p.x + 13, p.y + 33 };
	colPoint = { p.x, ColR.bottom };
}