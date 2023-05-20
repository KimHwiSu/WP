#pragma once
#pragma comment (lib, "msimg32.lib")
#include <iostream>
#include <windows.h>


using namespace std;

class Object {
public:
	virtual void init(HINSTANCE hins, LPCWSTR image);
	void setResRect(RECT r);
	void setLoc(POINT p);
	void setSize(POINT size);
	void draw(HDC hdc);
	POINT getCenter();
	void move(POINT m);
private:
	HBITMAP Bit;
	RECT drawRect;
	POINT center{};
	POINT drawSize;
};