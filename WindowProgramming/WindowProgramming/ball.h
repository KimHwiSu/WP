#pragma once
#include "Object.h"
#include <math.h>
#define PI 3.14

class bullet: public Object
{
public:
	float bullet_xmove(float x, int angle, int m, int time) {
		int currentx = x + cos(angle * PI / 180) * m * time; //m�� ��
		return currentx;
	}
	float bullet_ymove(float y, int angle, int m, int time) {
		int currenty = y + sin(angle * PI / 180) * m * time + 0.5 * 10 * time * time; //���� y��ǥ g=10���� ����
		return currenty;
	}
	
private:
};