#pragma once
#include "Object.h"

class Character : public Object{
public:
	void init(HINSTANCE hins, LPCWSTR image, POINT size) override;
private:
	RECT r = { 22, 46, 17, 27 };
	int idleDis = 47;
};