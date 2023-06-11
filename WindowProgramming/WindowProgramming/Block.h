#pragma once
#include "Object.h"

class Block : public Object {
public:
	void init(HINSTANCE hins, LPCWSTR image);
	void destroy(RECT r);
private:
	RECT IdleRect = { 0, 736, 128, 32 };
	POINT IdleSize = { 30, 10 };
	POINT whRate{};
	POINT dbRate{};
};