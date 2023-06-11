#pragma once
#include "Object.h"

class BackGround : public Object {
public:
	void init(HINSTANCE hins, LPCWSTR image, RECT clientRect);
private:
	RECT IdleRect = { 9, 387, 160, 64 };
};