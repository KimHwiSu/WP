#define _CRT_SECURE_NO_WARNINGS
#include <tchar.h>
#include <stdio.h>

#include "resource.h"
#include "Character.h"
#include "BackGround.h"
#include "Block.h"
#include "Bullet.h"

//#define visibleCollision

using namespace std;

HINSTANCE g_hInst;
LPCWSTR lpszClass = L"WIndow Class Name";
LPCWSTR lpszWindowName = L"포트리스";

// WindowSize = 800 x 600
UINT width = 800;
UINT height = 600;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
void DrawAll(HDC hdc, RECT clientRect);
void DrawTitle(HDC hdc, RECT clientRect);
void changeTurn();
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR lpszParam, int nCmdShow) {
	srand(time(0));
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
	WndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
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

BackGround bkg;
Character obj;
Character obj1;
vector<RECT> blocks;
Block block;
Block block1;
vector<RECT> bullets;
HBITMAP hbit;
HBITMAP titleMessage, hBitBackground, hBitBackground2, oldbitmap[4], windbitmap[2], HP, HP_M, MP, MP_M, power_gage[2], bullet_image, bullet_image_mask, font, player, player_mask, player2, hbitBackgroun2, v, s, v_mask, s_mask;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	Bullet bullet;
	PAINTSTRUCT ps;
	HDC hdc, memdc, memdcimage;
	static TCHAR str[100];
	static int page;
	static int store_angle;
	static int power_x, power_y;
	static float bullet_x, bullet_y;
	static int angle;
	static int plus;
	static int a;
	static float aim_x, aim_y;
	static int time;
	static int act;
	static int random;
	static int windpower;
	static int bullet_volume; //총알 크기
	static int player_HP, player_MP;
	static int turn;
	
	RECT clientRect;
	GetClientRect(hWnd, &clientRect);


	switch (iMessage) {
	case WM_CREATE:
		// printf (로그) 뽑는 용
		AllocConsole();
		_tfreopen(_T("CONOUT$"), _T("w"), stdout);
		_tfreopen(_T("CONIN$"), _T("r"), stdin);
		_tfreopen(_T("CONERR$"), _T("w"), stderr);
		SetTimer(hWnd, 1, 100, NULL);
		hBitBackground = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP3));
		hBitBackground2 = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP31));

		titleMessage = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP46));

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
		obj.setLoc({ 350, clientRect.bottom / 2});
		obj.init(g_hInst, MAKEINTRESOURCE(IDB_BITMAP36));
		obj.setTurn(true);
		
		obj1.setLoc({ 450, clientRect.bottom / 2 });
		obj1.init(g_hInst, MAKEINTRESOURCE(IDB_BITMAP43));
		obj1.setTurn(false);

		block.setLoc({ 350, 400 });
		block.init(g_hInst, MAKEINTRESOURCE(IDB_BITMAP45));
		block1.setLoc({ 450, 400 });
		block1.init(g_hInst, MAKEINTRESOURCE(IDB_BITMAP45));

		blocks.push_back(block.getColRect());
		blocks.push_back(block1.getColRect());

		bkg.init(g_hInst, MAKEINTRESOURCE(IDB_BITMAP37),clientRect);
		bkg.setLoc({ clientRect.right / 2, clientRect.bottom / 2 });

		page = 0;
		turn = 0;
		player_HP = 200;
		player_MP = 200;
		hdc = GetDC(hWnd);
		SetTimer(hWnd, 1, 100, NULL);
		

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
		break;
	case WM_KEYDOWN:
		if (page == 0) {
			switch (wParam)
			{
			case  'A':
				page = 1;
				break;
			}
		}
		else {
			switch (wParam) {
			case VK_LEFT:
				if (obj.getTurn()) {
					if (!obj.getChange()) {
						obj.setDirChange(true);
						obj.setChange(true);
						obj.changeState(1);
					}
					obj.moveC({ -1, 0 });
				}
				else if (obj1.getTurn()) {
					if (!obj1.getChange()) {
						obj1.setDirChange(true);
						obj1.setChange(true);
						obj1.changeState(1);
					}
					obj1.moveC({ -1, 0 });
				}
				break;
			case VK_RIGHT:
				if (obj.getTurn()) {
					if (!obj.getChange()) {
						obj.setDirChange(false);
						obj.setChange(true);
						obj.changeState(1);
					}
					obj.moveC({ 1, 0 });
				}
				else if (obj1.getTurn()) {
					if (!obj1.getChange()) {
						obj1.setDirChange(false);
						obj1.setChange(true);
						obj1.changeState(1);
					}
					obj1.moveC({ 1, 0 });
				}
				break;
			case VK_SPACE:
				if (obj.getTurn()) {
					if (!obj.getChange()) {
						obj.changeState(2);
					}
				}
				else if (obj1.getTurn()) {
					if (!obj1.getChange()) {
						obj1.changeState(2);
					}
				}
				break;
			}
		}
		break;
	case WM_KEYUP:
		if (page == 1) {
			switch (wParam) {
			case VK_SPACE:
				if (obj.getTurn()) {
					obj.changeState(0);
				}
				else if (obj1.getTurn()) {
					obj1.changeState(0);
				}
				changeTurn();
				break;
			case VK_LEFT:
			case VK_RIGHT:
				if (obj.getTurn()) {
					obj.setChange(false);
					obj.changeState(0);
				}
				else if (obj1.getTurn()) {
					obj1.setChange(false);
					obj1.changeState(0);
				}
				break;
			}
		}
		break;
	case WM_LBUTTONDOWN: {
		// 원하는 지점 클릭하면 좌표 나옴
		POINT p;
		p.x = LOWORD(lParam);
		p.y = HIWORD(lParam);
		cout << p.x << ", " << p.y << endl;
	}
		break;
	case WM_RBUTTONDOWN:
		break;
	case WM_TIMER:
		switch (wParam) {
		case 1:
			obj.update(blocks);
			obj1.update(blocks);
			break;
		}
		InvalidateRect(hWnd, NULL, false);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		if (page == 0) {
			DrawTitle(hdc, clientRect);
		}
		else {
			DrawAll(hdc, clientRect);
		}
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

void DrawAll(HDC hdc, RECT clientRect)
{
	HDC memdc = CreateCompatibleDC(hdc);
	HBITMAP hb = CreateCompatibleBitmap(hdc, clientRect.right, clientRect.bottom);
	SelectObject(memdc, hb);

	bkg.draw(memdc);
	block.draw(memdc);
	block1.draw(memdc);

	obj.draw(memdc);
	obj1.draw(memdc);

	HBRUSH hbrush = CreateSolidBrush(RGB(255, 0, 0));
	SelectObject(memdc, hbrush);
	for (RECT r : bullets) {
		Ellipse(memdc, r.left, r.top, r.right, r.bottom);
	}
	DeleteObject(hbrush);

#ifdef visibleCollision
	block.drawCol(memdc, clientRect);
	block1.drawCol(memdc, clientRect);
	obj.drawCol(memdc, clientRect);
	obj1.drawCol(memdc, clientRect);

#endif // visibleCollision
	HFONT hFont = CreateFont(40, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, _T("Impact"));  // 폰트 생성
	SelectObject(memdc, hFont);
	TCHAR text[] = L"Player";
	TCHAR newText[10];
	if (obj.getTurn()) {
		swprintf_s(newText, L"%s 1", text);
	}
	else if (obj1.getTurn()) {
		swprintf_s(newText, L"%s 2", text);
	}

	SetTextColor(memdc, RGB(1,1,1));
	TextOut(memdc, clientRect.right / 2 - 10, 10, newText, lstrlen(newText));

	HDC memdcimage = CreateCompatibleDC(memdc);
	RECT r{ 0, 0, 51,51 };
	FillRect(memdc,&r, (HBRUSH)GetStockObject(WHITE_BRUSH));
	oldbitmap[1] = (HBITMAP)SelectObject(memdcimage, windbitmap[1]);
	StretchBlt(memdc, 0, 0, 51, 51, memdcimage, 0, 0, 512, 512, SRCAND); // 바람
	oldbitmap[1] = (HBITMAP)SelectObject(memdcimage, windbitmap[0]);
	StretchBlt(memdc, 0, 0, 51, 51, memdcimage, 0, 0, 512, 512, SRCPAINT); // 바람

	TransparentBlt(hdc, 0, 0, clientRect.right, clientRect.bottom, memdc, 0, 0, clientRect.right, clientRect.bottom,RGB(0, 0, 0));
	
	DeleteObject(memdcimage);
	DeleteObject(hFont);
	DeleteObject(memdc);
	DeleteObject(hb);
}

void DrawTitle(HDC hdc, RECT clientRect)
{
	HDC memdc = CreateCompatibleDC(hdc);
	HBITMAP hb = CreateCompatibleBitmap(hdc, clientRect.right, clientRect.bottom);
	SelectObject(memdc, hb);

	HDC memdcimage = CreateCompatibleDC(memdc);

	SelectObject(memdcimage, hBitBackground2);
	StretchBlt(memdc, 0, 0, 800, 600, memdcimage, 0, 0, 160, 64, SRCCOPY); // 배경

	SelectObject(memdcimage, player_mask);
	StretchBlt(memdc, clientRect.right / 2 - 300, 100, 200, 200, memdcimage, 0, 0, 30, 30, SRCAND); // font

	SelectObject(memdcimage, player);
	StretchBlt(memdc, clientRect.right / 2 - 300, 100, 200, 200, memdcimage, 0, 0, 30, 30, SRCPAINT); // font
	
	SelectObject(memdcimage, player_mask);
	StretchBlt(memdc, clientRect.right / 2 + 100, 100, 200, 200, memdcimage, 30, 0, -30, 30, SRCAND); // font
	
	SelectObject(memdcimage, player2);
	StretchBlt(memdc, clientRect.right / 2 + 100, 100, 200, 200, memdcimage, 30, 0, -30, 30, SRCPAINT); // font
	
	SelectObject(memdcimage, v_mask);
	StretchBlt(memdc, clientRect.right / 2-100, 200, 100, 100, memdcimage, 0, 0, 45, 50, SRCAND); // font
	
	SelectObject(memdcimage, s_mask);
	StretchBlt(memdc, clientRect.right / 2, 200, 75, 100, memdcimage, 0, 0, 34, 48, SRCAND); // font

	SelectObject(memdcimage, v);
	StretchBlt(memdc, clientRect.right / 2-100, 200, 100, 100, memdcimage, 0, 0, 45, 50, SRCPAINT); // font

	SelectObject(memdcimage, s);
	StretchBlt(memdc, clientRect.right / 2, 200, 75, 100, memdcimage, 0, 0, 34, 48, SRCPAINT); // font

	SelectObject(memdcimage, titleMessage);
	TransparentBlt(memdc, clientRect.right /2 - 175, 400, 350, 50, memdcimage, 0, 0, 256, 37, RGB(24, 24, 27)); // font

	TransparentBlt(hdc, 0, 0, clientRect.right, clientRect.bottom, memdc, 0, 0, clientRect.right, clientRect.bottom, RGB(0, 0, 0));

	DeleteObject(memdcimage);
	DeleteObject(memdc);
	DeleteObject(hb);
}

void changeTurn()
{
	obj.setTurn(!obj.getTurn());
	obj1.setTurn(!obj1.getTurn());
}
