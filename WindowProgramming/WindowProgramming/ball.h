#pragma once
#include "Object.h"
#include <math.h>
#define PI 3.14

class bullet: public Object
{
public:
	float bullet_xmove(float x, int angle, int m, int time) {
		int currentx = x + cos(angle * PI / 180) * m * time; //m은 힘
		return currentx;
	}
	float bullet_ymove(float y, int angle, int m, int time) {
		int currenty = y + sin(angle * PI / 180) * m * time + 0.5 * 10 * time * time; //현재 y좌표 g=10으로 가정
		return currenty;
	}
	//각도
	float anlgepoint_x_up(int angle_x) {
		angle_x;
		return cos(angle_x * PI / 180);
	}
	float anlgepoint_y_up(int angle_y) {
		angle_y;
		return sin(angle_y * PI / 180);
	}
	float anlgepoint_x_down(int angle_x) {
		angle_x;
		return cos(angle_x * PI / 180);
	}
	float anlgepoint_y_down(int angle_y) {
		angle_y;
		return sin(angle_y * PI / 180);
	}

private:
	int a = 0;
};