#pragma once
#include "Object.h"
#include <math.h>
#define PI 3.14

class bullet: public Object
{
public:
	int windpower_x(int x_power, int random, int windpower) {
		if (random == 0 || random == 1 || random == 5) return x_power; //정지,위,아래
		else if (random == 2 || random == 3 || random == 4) return x_power + windpower; //오른쪽
		else return x_power - windpower;	//왼쪽
	}
	int windpower_y(int y_power, int random, int windpower) {
		if (random == 0 || random == 3 || random == 7) return y_power; //정지,왼,오
		else if (random == 1 || random == 2 || random == 8) return y_power + windpower; //위
		else return y_power - windpower;	//왼쪽
	}
	
	float bullet_xmove(float x, int angle, int m, int time) {
		int currentx = x + cos(angle * PI / 180) * m * time; //m은 힘
		return currentx;
	}
	float bullet_ymove(float y, int angle, int m, int time) {
		int currenty = y + sin(angle * PI / 180) * m * time + 0.5 * 10 * time * time; //현재 y좌표 g=10으로 가정
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