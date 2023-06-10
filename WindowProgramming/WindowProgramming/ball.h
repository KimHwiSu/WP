#pragma once
#include "Object.h"
#include <math.h>
#define PI 3.14

class bullet: public Object
{

public:
	int font(int random) {
		return random * 64;
	}
	void windbitmap(HINSTANCE g_hInst,HBITMAP* wind, HBITMAP* wind_mask, int random) {
		if (random == 1) {
			*wind = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP4));
			*wind_mask = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP5));
		}
		if (random == 2) {
			*wind = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP13));
			*wind_mask = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP14));
		}
		if (random == 3) {
			*wind = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP15));
			*wind_mask = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP16));
		}
		if (random == 4) {
			*wind = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP17));
			*wind_mask = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP18));
		}
		if (random == 5) {
			*wind = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP19));
			*wind_mask = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP20));
		}
		if (random == 6) {
			*wind = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP21));
			*wind_mask = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP22));
		}
		if (random == 7) {
			*wind = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP23));
			*wind_mask = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP24));
		}
		if (random == 8) {
			*wind = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP25));
			*wind_mask = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP26));
		}

	}
	int windpower_x(int x_power, int random, int windpower, int turn) {
		if (random == 7 || random == 3) { 
			return x_power;
			
		} //정지,위,아래
		else if (random == 8 || random == 1 || random == 2) {
			if (turn == 0)	return x_power + windpower; //오른쪽위,오,오아
			else return x_power - windpower;

		}
		else {
			if (turn == 0) return x_power - windpower;	//왼쪽
			else return x_power + windpower;
		}
	}
	int windpower_y(int y_power, int random, int windpower) {
		if (random == 5 || random == 1) return y_power; //정지,왼,오
		else if (random == 7 || random == 8 || random == 6 ) return y_power + windpower; //위,오위,왼위
		else return y_power - windpower;	//아래
	}
	float Player2_bullet_xmove(float x, int angle, int m, int time) {
		int l = -m;
		float currentx = x + cos(angle * PI / 180) * l * time; //m은 힘
		return currentx;
	}
	float bullet_xmove(float x, int angle, int m, int time) {
	   float currentx = x + cos(angle * PI / 180) * m * time; //m은 힘
		return currentx;
	}
	float bullet_ymove(float y, int angle, int m, int time) {
		float currenty = y + sin(angle * PI / 180) * m * time + 0.5 * 10 * time * time; //현재 y좌표 g=10으로 가정
		return currenty;
	}
	//각도
	float anlgepoint_x(int angle_x) {
		angle_x;
		return cos(angle_x * PI / 180);
	}
	float anlgepoint_y(int angle_y) {
		angle_y;
		return sin(angle_y * PI / 180);
	}

private:
	int a = 0;
};