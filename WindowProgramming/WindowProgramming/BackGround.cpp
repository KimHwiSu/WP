#include "BackGround.h"

void BackGround::init(HINSTANCE hins, LPCWSTR image, RECT clientRect)
{
	Object::init(hins, image);
	setResRect(IdleRect);
	setSize({clientRect.right / 2, clientRect.bottom/2});
}
