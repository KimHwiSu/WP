#include "Character.h"

void Character::init(HINSTANCE hins, LPCWSTR image, POINT size)
{
	Object::init(hins, image, size);
	setResRect(r);
}
