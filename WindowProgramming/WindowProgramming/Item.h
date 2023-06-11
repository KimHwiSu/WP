#pragma once
#include "Object.h"

class Item : public Object {
public:
	void init(HINSTANCE hins, LPCWSTR image);
	void update(vector<RECT> cols);
	void moveC(POINT s);
	bool checkBottom(RECT r);
private:
	RECT IdleRect = { 100, 10, 90, 82 };
	POINT IdleSize = { 15, 15 };
	POINT colPoint{};
};