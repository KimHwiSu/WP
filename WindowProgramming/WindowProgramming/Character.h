#pragma once
#include "Object.h"

class Character : public Object{
public:
	void init(HINSTANCE hins, LPCWSTR image) override;
private:
	RECT IdleRect = { 22, 46, 17, 27 };
	POINT IdleSize = { 10, 10 };
	int idleDis = 47;
};