#define _CRT_SECURE_NO_WARNINGS
#include <tchar.h>
#include <stdio.h>

#include "resource.h"
#include "Character.h"
#include "ball.h"
using namespace std;
HBITMAP hbit;

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
	HDC hdc, memdc, memdcimage;
	static TCHAR str[100];
	static int page;
	static int store_angle;
	static int power_x,power_y;
	static float bullet_x, bullet_y;
	static int angle;
	static int plus;
	static int a;
	static float aim_x,aim_y;
	static int time;
	static int act;
	static int random;
	static int windpower;
	static int bullet_volume; //총알 크기
	static int player_HP, player_MP;
	static int turn;
	static HBITMAP hBitBackground, hBitBackground2, oldbitmap[4], windbitmap[2], HP, HP_M, MP, MP_M, power_gage[2], bullet_image, bullet_image_mask, font, player, player_mask, player2, hbitBackgroun2, v, s, v_mask, s_mask;
	RECT clientRect;
	GetClientRect(hWnd, &clientRect);

	static Character obj;
	switch (iMessage) {
	case WM_CREATE:
		page = 0;
		turn = 0;
		player_HP = 200;
		player_MP = 200;
		hdc = GetDC(hWnd);
		SetTimer(hWnd, 1000, 100, NULL);
		hbit = CreateCompatibleBitmap(hdc, 1600, 600);
		hBitBackground = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP3));
		hBitBackground2 = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP31));

		windbitmap[0] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP4));
		windbitmap[1] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP5));

		HP = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP6));
		HP_M = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP7));
		MP = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP8));
		MP_M = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP9));
		power_gage[0] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP10));
		power_gage[1] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP11));
		bullet_image = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP2));
		bullet_image_mask = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP12));
		font = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP27));
		player = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP29));
		player_mask = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP30));
		player2 = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP28));
		v = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP32));
		s = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP33));
		v_mask = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP34));
		s_mask = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP35));

		bullet_volume = 10;

		random = rand() % 8 + 1; //바람 방향 9가지 8방향
		a = 0;
		plus = 0;
		act = 0;
		time = 0;
		angle = 0;
		bullet_x = 40;
		bullet_y = 300;
		windpower = rand() % 10;
		aim_x = bullet.anlgepoint_x(angle);
		aim_y = bullet.anlgepoint_y(angle);
		bullet.windbitmap(g_hInst, &windbitmap[0], &windbitmap[1], random);
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
		case VK_RETURN:
			player_HP -= 2;
			break;
		case 'o':
			player_MP -= 2;
			break;

		case VK_UP:
			if (act == 0) {
				aim_x = bullet.anlgepoint_x(angle--);
				aim_y = bullet.anlgepoint_y(angle);

			}
			break;
		case VK_DOWN:
			if (act == 0) {
				aim_x = bullet.anlgepoint_x(angle++);
				aim_y = bullet.anlgepoint_y(angle);
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
			page = 1;
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
					power_x = bullet.windpower_x(power_x, random, windpower, turn);
					power_y = bullet.windpower_y(power_y, random, windpower);
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
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_TIMER:
		hdc = GetDC(hWnd);
		switch (wParam)
		{
		case 1:
			if (turn == 0) {
				if (act == 1) {
					if (plus == 0) {
						angle -= 2;
						aim_x = bullet.anlgepoint_x(angle);
						aim_y = bullet.anlgepoint_y(angle);
					}
					if (plus == 1) {
						angle += 2;
						aim_x = bullet.anlgepoint_x(angle);
						aim_y = bullet.anlgepoint_y(angle);
					}
					if (angle < store_angle - 30 && plus == 0) {
						plus = 1;
					}
					if (angle > store_angle + 30 && plus == 1) {
						plus = 0;
					}
				}//에임 위아래 이동
				if (act == 2) {

					if (plus == 0) { power_x += 5; power_y += 5; }
					if (plus == 1) { power_x -= 5; power_y -= 5; }
					if (power_x == 50)plus = 1;
					if (power_x == 0)plus = 0;
				} //힘조절
				if (act == 3) {
					time++;
					
					bullet_x = bullet.bullet_xmove(bullet_x, angle, power_x, time);
					bullet_y = bullet.bullet_ymove(bullet_y, angle, power_y, time);
					if (bullet_y > 600 ) {

						angle = 0;
						power_x = 0;
						power_y = 0;
						time = 0;
						bullet_x = 500;
						bullet_y = 300;
						act = 0;
						plus = 0;
						windpower = rand() % 10;
						random = rand() % 8 + 1;
						bullet.windbitmap(g_hInst, &windbitmap[0], &windbitmap[1], random);
						turn = 1;
						aim_x = -aim_x;
					}
				}//총알 궤적
			}
			else if (turn == 1) {
				if (act == 1) {
					if (plus == 0) {
						angle -= 2;
						aim_x = bullet.anlgepoint_x(angle);
						aim_y = bullet.anlgepoint_y(angle);
					}
					if (plus == 1) {
						angle += 2;
						aim_x = bullet.anlgepoint_x(angle);
						aim_y = bullet.anlgepoint_y(angle);
					}
					if (angle < store_angle - 30 && plus == 0) {
						plus = 1;
					}
					if (angle > store_angle + 30 && plus == 1) {
						plus = 0;
					}
				}//에임 위아래 이동
				if (act == 2) {

					if (plus == 0) { power_x += 5; power_y += 5; }
					if (plus == 1) { power_x -= 5; power_y -= 5; }
					if (power_x == 50)plus = 1;
					if (power_x == 0)plus = 0; 
				} //힘조절
				if (act == 3) {
					time++;

					
					bullet_x = bullet.Player2_bullet_xmove(bullet_x, angle, power_x, time);
					bullet_y = bullet.bullet_ymove(bullet_y, angle, power_y, time);
					if (bullet_y > 600 || bullet_x < 0) {
						angle = 0;
						power_x = 0;
						power_y = 0;
						time = 0;
						bullet_x = 20;
						bullet_y = 300;
						act = 0;
						plus = 0;
						windpower = rand() % 10;
						random = rand() % 8 + 1;
						bullet.windbitmap(g_hInst, &windbitmap[0], &windbitmap[1], random);
						turn = 0;
						aim_x = -aim_x;
					}
				}//총알 궤적
			}
			break;
		default:
			break;
		}

		memdc = CreateCompatibleDC(hdc); 
		memdcimage = CreateCompatibleDC(memdc); 
		oldbitmap[0] = (HBITMAP)SelectObject(memdc, hbit);

    	if (page == 0) {
			oldbitmap[1] = (HBITMAP)SelectObject(memdcimage, hBitBackground2);
			StretchBlt(memdc, 0, 0, 800, 600, memdcimage, 0, 0, 160, 64, SRCCOPY); // 배경
			oldbitmap[1] = (HBITMAP)SelectObject(memdcimage, player_mask);
			StretchBlt(memdc, 100, 100, 200, 200, memdcimage, 0, 0, 30, 30, SRCAND); // font
			oldbitmap[1] = (HBITMAP)SelectObject(memdcimage, player);
			StretchBlt(memdc, 100, 100, 200, 200, memdcimage, 0, 0, 30, 30, SRCPAINT); // font
			oldbitmap[1] = (HBITMAP)SelectObject(memdcimage, player_mask);
			StretchBlt(memdc, 500, 100, 200, 200, memdcimage, 30, 0, -30, 30, SRCAND); // font
			oldbitmap[1] = (HBITMAP)SelectObject(memdcimage, player2);
			StretchBlt(memdc, 500, 100, 200, 200, memdcimage, 30, 0, -30, 30, SRCPAINT); // font
			oldbitmap[1] = (HBITMAP)SelectObject(memdcimage, v_mask);
			StretchBlt(memdc, 320, 200, 100, 100, memdcimage, 0, 0, 45, 50, SRCAND); // font
			oldbitmap[1] = (HBITMAP)SelectObject(memdcimage, s_mask);
			StretchBlt(memdc, 420, 200, 75, 100, memdcimage, 0, 0, 34, 48, SRCAND); // font

			oldbitmap[1] = (HBITMAP)SelectObject(memdcimage, v);
			StretchBlt(memdc, 320, 200, 100, 100, memdcimage, 0, 0, 45, 50, SRCPAINT); // font
			oldbitmap[1] = (HBITMAP)SelectObject(memdcimage, s);
			StretchBlt(memdc, 420, 200, 75, 100, memdcimage, 0, 0, 34, 48, SRCPAINT); // font
		
		}
			if (page != 0) {
				
				oldbitmap[1] = (HBITMAP)SelectObject(memdcimage, hBitBackground);
				StretchBlt(memdc, 0, 0, 800, 600, memdcimage, 0, 0, 160, 64, SRCCOPY); // 배경

				oldbitmap[2] = (HBITMAP)SelectObject(memdcimage, hBitBackground2);
				StretchBlt(memdc, 800, 0, 1600, 600, memdcimage, 0, 0, 160, 64, SRCCOPY); // 배경
				oldbitmap[1] = (HBITMAP)SelectObject(memdcimage, windbitmap[1]);
				StretchBlt(memdc, 360, 0, 51, 51, memdcimage, 0, 0, 512, 512, SRCAND); // 바람
				oldbitmap[1] = (HBITMAP)SelectObject(memdcimage, windbitmap[0]);
				StretchBlt(memdc, 360, 0, 51, 51, memdcimage, 0, 0, 512, 512, SRCPAINT); // 바람
				oldbitmap[1] = (HBITMAP)SelectObject(memdcimage, HP);
				StretchBlt(memdc, 100, 500, 200, 25, memdcimage, 0, 0, 88, 10, SRCCOPY); // 닳은 HP
				oldbitmap[1] = (HBITMAP)SelectObject(memdcimage, HP_M);
				StretchBlt(memdc, 100, 500, player_HP, 25, memdcimage, 0, 0, 88, 10, SRCCOPY); // HP
				oldbitmap[1] = (HBITMAP)SelectObject(memdcimage, font);
				StretchBlt(memdc, 360, 51, 20, 20, memdcimage, bullet.font(windpower), 0, 60, 60, SRCPAINT); // font
				oldbitmap[1] = (HBITMAP)SelectObject(memdcimage, font);
				StretchBlt(memdc, 360 + 15, 51, 20, 20, memdcimage, 13 * 64, 192, 60, 60, SRCPAINT); // font
				oldbitmap[1] = (HBITMAP)SelectObject(memdcimage, font);
				StretchBlt(memdc, 360 + 25, 51, 20, 20, memdcimage, 13 * 64, 192 - 64, -60, 60, SRCPAINT); // font
				oldbitmap[1] = (HBITMAP)SelectObject(memdcimage, font);
				StretchBlt(memdc, 360 + 35, 51, 20, 20, memdcimage, 192, 192 + 64, 60, 60, SRCPAINT); // font
				oldbitmap[1] = (HBITMAP)SelectObject(memdcimage, player_mask);
				StretchBlt(memdc, 0, 450, 100, 100, memdcimage, 0, 0, 30, 30, SRCAND); // font
				if (turn == 0) {
					oldbitmap[1] = (HBITMAP)SelectObject(memdcimage, player);
					StretchBlt(memdc, 0, 450, 100, 100, memdcimage, 0, 0, 30, 30, SRCPAINT); // font
				}
				else {
					oldbitmap[1] = (HBITMAP)SelectObject(memdcimage, player2);
					StretchBlt(memdc, 0, 450, 100, 100, memdcimage, 0, 0, 30, 30, SRCPAINT); // font

				}
				oldbitmap[1] = (HBITMAP)SelectObject(memdcimage, MP_M);
				StretchBlt(memdc, 100, 525, 200, 25, memdcimage, 0, 0, 88, 10, SRCCOPY); // 닳은 MP
				oldbitmap[1] = (HBITMAP)SelectObject(memdcimage, MP);
				StretchBlt(memdc, 100, 525, player_MP, 25, memdcimage, 0, 0, 88, 10, SRCCOPY); // MP
				oldbitmap[1] = (HBITMAP)SelectObject(memdcimage, power_gage[1]);
				StretchBlt(memdc, bullet_x - 10, bullet_y - 40, 10, 50, memdcimage, 0, 0, 10, 88, SRCCOPY); // 닳은 power
				oldbitmap[1] = (HBITMAP)SelectObject(memdcimage, power_gage[0]);
				StretchBlt(memdc, bullet_x - 10, bullet_y + 10, 10, -power_x , memdcimage, 0, 0, 10, 88, SRCCOPY); // power
				if (turn == 0) {
					oldbitmap[1] = (HBITMAP)SelectObject(memdcimage, bullet_image_mask);
					StretchBlt(memdc, bullet_x, bullet_y, 40, 20, memdcimage, 0, 0, 40, 20, SRCAND);
					oldbitmap[1] = (HBITMAP)SelectObject(memdcimage, bullet_image);
					StretchBlt(memdc, bullet_x, bullet_y, 40, 20, memdcimage, 0, 0, 40, 20, SRCPAINT);
				}
				if (turn == 1) {
					oldbitmap[1] = (HBITMAP)SelectObject(memdcimage, bullet_image_mask);
					StretchBlt(memdc, bullet_x, bullet_y, -40, 20, memdcimage, 0, 0, 40, 20, SRCAND);
					oldbitmap[1] = (HBITMAP)SelectObject(memdcimage, bullet_image);
					StretchBlt(memdc, bullet_x, bullet_y, -40, 20, memdcimage, 0, 0, 40, 20, SRCPAINT);
				}
			}
		DeleteDC(memdc);
		DeleteObject(memdcimage);
		ReleaseDC(hWnd, hdc);

		InvalidateRect(hWnd, NULL, FALSE);

		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		memdc = CreateCompatibleDC(hdc);
		memdcimage = CreateCompatibleDC(memdc); //--- 이미지를 저장 할 메모리 DC 생성
		oldbitmap[0] = (HBITMAP)SelectObject(memdc, hbit);

		StretchBlt(hdc, 0, 0, 800, 600, memdc, 0, 0, 800, 600, SRCCOPY); // HP

		SelectObject(memdc, oldbitmap[0]);

		obj.draw(hdc);
		MoveToEx(hdc, bullet_x+20, bullet_y+10, NULL);
		LineTo(hdc, bullet_x + 20 * aim_x + 20, 20 * aim_y + bullet_y + 10);
		
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}