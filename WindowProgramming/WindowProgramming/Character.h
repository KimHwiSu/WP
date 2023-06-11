#pragma once
#include "Object.h"

class Character : public Object{
public:
	void init(HINSTANCE hins, LPCWSTR image);
	void update(vector<RECT> cols);
	void changeState(int i);
	bool getChange();
	void setChange(bool is);
	POINT getColPoint();
	void setTurn(bool is);
	bool getTurn();
	bool checkBottom(RECT r);
	void moveC(POINT s);
	float getHP();
	float getMP();
	void damageHP(int i);
	void setMP(int i);
	void damageMP(int i);
	void addItem();
	void useItem();
	int getItem();
private:
	bool turn{};
	RECT IdleRect = { 0, 12, 63, 63 };
	POINT IdleSize = { 35, 35 };
	vector<int> idleDis{ 64, 47,  55};
	int index{};
	int state{};
	vector<int>indexes{ 8, 10, 3};
	bool stateChange{};
	POINT colPoint{};
	HINSTANCE hi;
	LPCWSTR im;
	int item{};

	float HP = 200;
	float MP = 200;
};