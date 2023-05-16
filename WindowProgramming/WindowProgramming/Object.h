#pragma once
#pragma comment (lib, "msimg32.lib")
#include <iostream>
#include <windows.h>


using namespace std;

class Object {
public:
	virtual void init(HINSTANCE hins, LPCWSTR image, POINT size);
	void setResRect(RECT r);
	void setLoc(POINT p);
	void draw(HDC hdc);
	POINT getCenter();
	void move(POINT m);
private:
	HBITMAP Bit;
	RECT drawRect;
	POINT center{};
	POINT drawSize;
};