#pragma once
#include <iostream>
#include <windows.h>
#include "resource.h"
using namespace std;

// ui list : wind, hp Max, mp Max, left hp, left mp, charge gage, font(for timer) 

class Ui {
public:
	void setBmp(HINSTANCE hi, UINT bmp, UINT bmpM, int num);
	void windbitmap(HINSTANCE hi, int random);
private:
	// bmps
	HBITMAP wind, HP_M, MP_M, HP, MP, Charge;
	HBITMAP windMask, ChargeMask;

	HBITMAP font;
};