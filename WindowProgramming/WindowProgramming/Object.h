#pragma once
#pragma comment (lib, "msimg32.lib")
#include <iostream>
#include <windows.h>
#include <vector>


using namespace std;


class Object {
public:
	virtual void init(HINSTANCE hins, LPCWSTR image, COLORREF co);
	void setResRect(RECT r);
	void setLoc(POINT p);
	void setSize(POINT size);
	void draw(HDC hdc);
	POINT getCenter();
	void move(POINT m);
	RECT getDrawRect();
	void setColRect(RECT colR);
	RECT getColRect();
	void drawCol(HDC hdc, RECT clientRect);
	bool CheckCollision(RECT otherRect);
	bool getCol();
	bool getDirChange();
	void setDirChange(bool is);
	
private:
	bool dirChange{};
	HBITMAP Bit;
	RECT drawRect;
	POINT center{};
	POINT drawSize;
	RECT colRect{};
	bool col{};
	COLORREF color{};
};