#define _CRT_SECURE_NO_WARNINGS
#include <tchar.h>
#include <stdio.h>

#include "resource.h"
#include "Character.h"
#include "ball.h"
using namespace std;

HINSTANCE g_hInst;
LPCWSTR lpszClass = L"WIndow Class Name";
LPCWSTR lpszWindowName = L"포트리스";

// WindowSize = 800 x 600
UINT width = 800;
UINT height = 600;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR lpszParam, int nCmdShow) {
	HWND hWnd;
	MSG Message;
	WNDCLASSEX WndClass;
	g_hInst = hInstance;
	WndClass.cbSize = sizeof(WndClass);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = lpszClass;
	WndClass.hIconSm = LoadIcon(NULL, IDI_QUESTION);
	RegisterClassEx(&WndClass);
	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW, 250, 50, width, height, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	bullet bullet;
	PAINTSTRUCT ps;
	HDC hdc;
	static int store_angle;
	static int power;
	static float bullet_x, bullet_y;
	static int angle;
	static int plus;
	static int a;
	static float aim_x,aim_y;
	static int time;
	static int act;
	RECT clientRect;
	GetClientRect(hWnd, &clientRect);

	static Character obj;
	switch (iMessage) {
	case WM_CREATE:
		a = 0;
		plus = 0;
		act = 0;
		time = 0;
		angle = 0;
		bullet_x = 40;
		bullet_y = 200;
		aim_x = bullet.anlgepoint_x_up(angle);
		aim_y = bullet.anlgepoint_y_up(angle);

		// printf (로그) 뽑는 용
		break;
	case WM_LBUTTONDOWN:
		// 원하는 지점 클릭하면 좌표 나옴
		POINT p;
		p.x = LOWORD(lParam);
		p.y = HIWORD(lParam);
		cout << p.x << ", " << p.y << endl;
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_UP:
			if (act == 0) {
				aim_x = bullet.anlgepoint_x_up(angle--);
				aim_y = bullet.anlgepoint_y_up(angle);

			}
			break;
		case VK_DOWN:
			if (act == 0) {
				aim_x = bullet.anlgepoint_x_down(angle++);
				aim_y = bullet.anlgepoint_y_down(angle);
			}
			break;
			//위아래키로 에임 조정
		case VK_SPACE:
			if (act == 0) {
				store_angle = angle;
				act = 1;
				SetTimer(hWnd, 1, 100, NULL);

			}
			
			break;
		default:
			break;
		}
		break;
	case WM_KEYUP:
		switch (wParam)
		{
		case VK_UP:
			
			break;
		case VK_DOWN:
			
			break;
		case VK_SPACE:
			
				
				if (act == 2) {
					act = 3;
					SetTimer(hWnd, 1, 100, NULL);
				}
				if (act == 1) {
					act = 2;
					SetTimer(hWnd, 1, 100, NULL);
				}
				plus = 0;
			break;
		default:
			break;
		}
		break;
	case WM_TIMER:
		switch (wParam)
		{
		case 1:
			if (act == 1) {
				if (plus == 0) {
					aim_x = bullet.anlgepoint_x_up(angle--);
					aim_y = bullet.anlgepoint_y_up(angle);
				}
				 if(plus == 1) {
					aim_x = bullet.anlgepoint_x_up(angle++);
					aim_y = bullet.anlgepoint_y_up(angle);
				}
				if (angle < store_angle - 30 && plus == 0) {
					plus = 1;
				}
				if (angle > store_angle + 30 && plus == 1) {
					plus = 0;
				}
			}//에임 위아래 이동
			if (act == 2) {
				
			if(plus == 0)power += 20;
			if (plus == 1)power -= 20;
			if (power == 300)plus = 1;
			if (power == 0)plus = 0;
			} //힘조절
			if (act == 3) {
				time++;
				bullet_x = bullet.bullet_xmove(bullet_x, angle, power, time);
				bullet_y = bullet.bullet_ymove(bullet_y, angle, power, time);
				if (bullet_y > 600) {
					time = 0;
					bullet_x = 20;
					bullet_y = 200;
					act = 0;
					plus = 0;
				}
			}//총알 궤적
			break;
		default:
			break;
		}
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		obj.draw(hdc);
		MoveToEx(hdc, bullet_x+20, bullet_y+10, NULL);
		LineTo(hdc, bullet_x + 20 * aim_x + 20, 20 * aim_y + bullet_y + 10);
		MoveToEx(hdc, bullet_x -10, bullet_y + 20, NULL);
		LineTo(hdc, bullet_x -10, -power + bullet_y );
		Ellipse(hdc, bullet_x, bullet_y, bullet_x + 20, bullet_y + 20);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}