#pragma once
#include "Object.h"
#include <math.h>
#define PI 3.14

class bullet: public Object
{
public:
	int windpower_x(int x_power, int random, int windpower) {
		if (random == 0 || random == 1 || random == 5) return x_power; //����,��,�Ʒ�
		else if (random == 2 || random == 3 || random == 4) return x_power + windpower; //������
		else return x_power - windpower;	//����
	}
	int windpower_y(int y_power, int random, int windpower) {
		if (random == 0 || random == 3 || random == 7) return y_power; //����,��,��
		else if (random == 1 || random == 2 || random == 8) return y_power + windpower; //��
		else return y_power - windpower;	//����
	}
	
	float bullet_xmove(float x, int angle, int m, int time) {
		int currentx = x + cos(angle * PI / 180) * m * time; //m�� ��
		return currentx;
	}
	float bullet_ymove(float y, int angle, int m, int time) {
		int currenty = y + sin(angle * PI / 180) * m * time + 0.5 * 10 * time * time; //���� y��ǥ g=10���� ����
		return currenty;
	}
	//����
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