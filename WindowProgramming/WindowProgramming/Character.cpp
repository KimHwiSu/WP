#include "Character.h"

void Character::init(HINSTANCE hins, LPCWSTR image)
{
	Object::init(hins, image);
	setResRect(IdleRect);
	setSize(IdleSize);
}
