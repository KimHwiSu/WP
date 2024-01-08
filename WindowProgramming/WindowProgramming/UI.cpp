#include "UI.h"

// 0: wind, 1: HP, 2: MP, 3: Charge gage (HP & MP mask is for left)
void Ui::setBmp(HINSTANCE hi, UINT bmp, UINT bmpM, int num)
{
	switch (num) {
	case 0:
		wind = LoadBitmap(hi, MAKEINTRESOURCE(bmp));
		windMask = LoadBitmap(hi, MAKEINTRESOURCE(bmpM));
		break;
	case 1:
		HP_M = LoadBitmap(hi, MAKEINTRESOURCE(bmp));
		HP = LoadBitmap(hi, MAKEINTRESOURCE(bmpM));
		break;
	case 2:
		MP_M = LoadBitmap(hi, MAKEINTRESOURCE(bmp));
		MP = LoadBitmap(hi, MAKEINTRESOURCE(bmpM));
		break;
	case 3:
		Charge = LoadBitmap(hi, MAKEINTRESOURCE(bmp));
		ChargeMask = LoadBitmap(hi, MAKEINTRESOURCE(bmpM));
		break;
	}
}

void Ui::windbitmap(HINSTANCE hi, int random)
{
	if (random == 1) {
		wind = LoadBitmap(hi, MAKEINTRESOURCE(IDB_BITMAP4));
		windMask = LoadBitmap(hi, MAKEINTRESOURCE(IDB_BITMAP5));
	}
	if (random == 2) {
		wind = LoadBitmap(hi, MAKEINTRESOURCE(IDB_BITMAP13));
		windMask = LoadBitmap(hi, MAKEINTRESOURCE(IDB_BITMAP14));
	}
	if (random == 3) {
		wind = LoadBitmap(hi, MAKEINTRESOURCE(IDB_BITMAP15));
		windMask = LoadBitmap(hi, MAKEINTRESOURCE(IDB_BITMAP16));
	}
	if (random == 4) {
		wind = LoadBitmap(hi, MAKEINTRESOURCE(IDB_BITMAP17));
		windMask = LoadBitmap(hi, MAKEINTRESOURCE(IDB_BITMAP18));
	}
	if (random == 5) {
		wind = LoadBitmap(hi, MAKEINTRESOURCE(IDB_BITMAP19));
		windMask = LoadBitmap(hi, MAKEINTRESOURCE(IDB_BITMAP20));
	}
	if (random == 6) {
		wind = LoadBitmap(hi, MAKEINTRESOURCE(IDB_BITMAP21));
		windMask = LoadBitmap(hi, MAKEINTRESOURCE(IDB_BITMAP22));
	}
	if (random == 7) {
		wind = LoadBitmap(hi, MAKEINTRESOURCE(IDB_BITMAP23));
		windMask = LoadBitmap(hi, MAKEINTRESOURCE(IDB_BITMAP24));
	}
	if (random == 8) {
		wind = LoadBitmap(hi, MAKEINTRESOURCE(IDB_BITMAP25));
		windMask = LoadBitmap(hi, MAKEINTRESOURCE(IDB_BITMAP26));
	}
}
