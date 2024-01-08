#define _CRT_SECURE_NO_WARNINGS
#define debug
//#define visibleCollision
#include <tchar.h>
#include <stdio.h>

#include "resource.h"
#include "Character.h"
#include "BackGround.h"
#include "Block.h"
#include "Bullet.h"
#include "Item.h"
#include "Ui.h"


// todo
// 1. divide
// - set bitmap
// - framework
// - variable
// 2. improvement
// - move animation
// - previous key do not recognize
// - bmp bkgColor (white) clear
// - map expand
// - Item expand

// 1. make Class Stage, and cascase objs
 
#define MPdamage 5
#define HPDamage 105
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
void DrawEnd(HDC hdc, RECT clientRect);
void changeTurn();
void setBulletLoc();
void checkCol();
void checkItemCol();
void setImgs();
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
vector<Block> block;
vector<RECT> bullets;
HBITMAP hbit;
HBITMAP titleMessage, hBitBackground, hBitBackground2, oldbitmap[4], windbitmap[2], HP, HP_M, MP, MP_M, power_gage[2], bullet_image, bullet_image_mask, font, player, player_mask, player2, hbitBackgroun2, v, s, v_mask, s_mask;
vector<Item> item;
Bullet bullet;


Ui stage1;
// ui list : wind, hp Max, mp Max, left hp, left mp, charge gage, font(for timer) 

float aim_x, aim_y;
int power_x, power_y;
int act;
bool drawLine{};
bool gameOver{};
DWORD startTime; // 시작 시간
bool drawCol{  };
DWORD elapsedTime = 0; // 경과 시간 (단위: 밀리초)
DWORD timeLimit = 10000; // 제한 시간 (단위: 밀리초, 여기서는 10초)
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc, memdc, memdcimage;
	static TCHAR str[100];
	static int page;
	static int store_angle;
	static int angle;
	static int plus;
	static int a;
	static int time;
	static int random;
	static int windpower;
	static int turn;
	
	RECT clientRect;
	GetClientRect(hWnd, &clientRect);


	switch (iMessage) {
	case WM_CREATE:
#ifdef debug
		AllocConsole();
		_tfreopen(_T("CONOUT$"), _T("w"), stdout);
		_tfreopen(_T("CONIN$"), _T("r"), stdin);
		_tfreopen(_T("CONERR$"), _T("w"), stderr);
#endif
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
		obj.setLoc({ 100, clientRect.bottom / 2});
		obj.init(g_hInst, MAKEINTRESOURCE(IDB_BITMAP36));
		obj.setTurn(true);
		
		obj1.setLoc({ clientRect.right - 100, clientRect.bottom / 2 });
		obj1.setDirChange(true);
		obj1.init(g_hInst, MAKEINTRESOURCE(IDB_BITMAP43));
		obj1.setTurn(false);
		{
			Item i;
			i.setLoc({ 400, 100 });
			i.init(g_hInst, MAKEINTRESOURCE(IDB_BITMAP40));
			item.push_back(i);
		}
		for (int i = 0; i < 14; i++) {
			Block b;
			b.setLoc({ i * 60+30, 400		});
			b.init(g_hInst, MAKEINTRESOURCE(IDB_BITMAP45));
			blocks.push_back(b.getColRect());
			block.push_back(b);
		}

		bkg.init(g_hInst, MAKEINTRESOURCE(IDB_BITMAP37),clientRect);
		bkg.setLoc({ clientRect.right / 2, clientRect.bottom / 2 });

		page = 0;
		turn = 0;
		hdc = GetDC(hWnd);
		SetTimer(hWnd, 1, 100, NULL);
		
		bullet.init(g_hInst, MAKEINTRESOURCE(IDB_BITMAP2), obj.getCenter(), 10);
		bullet.setDraw(false);

		random = rand() % 8 + 1; //바람 방향 9가지 8방향
		a = 0;
		plus = 0;
		act = 0;
		time = 0;
		angle = 0;
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
				startTime = GetTickCount();
				break;
			}
		}
		else {
			switch (wParam) {
			case 'Z':
				if (obj.getTurn()) {
					obj.useItem();
				}
				else {
					obj1.useItem();
				}
				break;
			case 'Q':
				drawCol = !drawCol;
				break;
			case VK_LEFT:
				if (obj.getTurn()) {
						if (!obj.getChange()) {
							obj.setDirChange(true);
							obj.setChange(true);
							obj.changeState(1);
						}
						if (obj.getMP() > 0) {
						obj.moveC({ -1, 0 });
						obj.damageMP(MPdamage);
					}
				}
				else if (obj1.getTurn()) {
						if (!obj1.getChange()) {
							obj1.setDirChange(true);
							obj1.setChange(true);
							obj1.changeState(1);
						}
						if (obj1.getMP() > 0) {
						obj1.moveC({ -1, 0 });
						obj1.damageMP(MPdamage);
					}
				}
				break;
			case VK_RIGHT:
				if (obj.getTurn()) {
						if (!obj.getChange()) {
							obj.setDirChange(false);
							obj.setChange(true);
							obj.changeState(1);
						}
						if (obj.getMP() > 0) {
						obj.moveC({ 1, 0 });
						obj.damageMP(MPdamage);
					}
				}
				else if (obj1.getTurn()) {
					if (!obj1.getChange()) {
							obj1.setDirChange(false);
							obj1.setChange(true);
							obj1.changeState(1);
						}
					if (obj1.getMP() > 0) {
						obj1.moveC({ 1, 0 });
						obj1.damageMP(MPdamage);
					}
				}
				break;
			case VK_SPACE:
				if (act == 0) {
					drawLine = true;
					store_angle = angle;
					act = 1;
				}
				else if (act == 2) {
					power_x = bullet.windpower_x(power_x, random, windpower, turn);
					power_y = bullet.windpower_y(power_y, random, windpower);
					bullet.setDraw(true);
					if (obj.getTurn()) {
						obj.changeState(0);
					}
					else {
						obj1.changeState(0);
					}
					drawLine = false;
					act = 3;
				}
				else if (act == 1) {
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
					act = 2;
				}
				plus = 0;
				break;
			case VK_UP:
				if (act == 0) {
					drawLine = true;
					aim_x = bullet.anlgepoint_x(angle--);
					aim_y = bullet.anlgepoint_y(angle);

				}
				break;
			case VK_DOWN:
				if (act == 0) {
					drawLine = true;
					aim_x = bullet.anlgepoint_x(angle++);
					aim_y = bullet.anlgepoint_y(angle);
				}
				break;
				//위아래키로 에임각 조정
			}
		}
		break;
	case WM_KEYUP:
		if (page == 1) {
			switch (wParam) {
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
	case WM_TIMER: {
		DWORD currentTime = GetTickCount64();;
		elapsedTime = currentTime - startTime;
		// 제한 시간 체크
		if (act != 3) {
			if (elapsedTime >= timeLimit) {
				startTime = GetTickCount64(); // 시작 시간 재설정
				angle = 0;
				power_x = 0;
				power_y = 0;
				time = 0;
				act = 0;
				plus = 0;
				windpower = rand() % 10;
				random = rand() % 8 + 1;
				bullet.windbitmap(g_hInst, &windbitmap[0], &windbitmap[1], random);

				aim_x = -aim_x;
				changeTurn();
			}
		}
		switch (wParam) {
		case 1:
			if (bullet.getDraw()) {
				checkCol();
			}
			checkItemCol();
			for (Item& i : item) {
				i.update(blocks);
			}
			obj.update(blocks);
			obj1.update(blocks);
			bullet.update();
			setBulletLoc();
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
					int x;
					if (obj.getTurn()) {
						if (obj.getDirChange()) {
							x = bullet.Player2_bullet_xmove(bullet.getCenter().x, angle, power_x * 2, time);
						}
						else {
							x = bullet.bullet_xmove(bullet.getCenter().x, angle, power_x * 2, time);
						}
					}
					else {
						if (obj1.getDirChange()) {
							x = bullet.Player2_bullet_xmove(bullet.getCenter().x, angle, power_x * 2, time);
						}
						else {
							x = bullet.bullet_xmove(bullet.getCenter().x, angle, power_x * 2, time);
						}
					}
					bullet.setLoc({ x,
						(int)bullet.bullet_ymove(bullet.getCenter().y, angle, power_y * 2, time) });

					if (bullet.getCenter().y > 600) {
						angle = 0;
						power_x = 0;
						power_y = 0;
						time = 0;
						act = 0;
						plus = 0;
						windpower = rand() % 10;
						random = rand() % 8 + 1;
						bullet.windbitmap(g_hInst, &windbitmap[0], &windbitmap[1], random);

						aim_x = -aim_x;
						changeTurn();
						bullet.setDraw(false);
						startTime = GetTickCount64();
					}
				}//총알 궤적
			}
			break;
		}
		InvalidateRect(hWnd, NULL, false);
		break;
	}
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		if (page == 0) {
			DrawTitle(hdc, clientRect);
		}
		else {
			DrawAll(hdc, clientRect);
			if (gameOver) {
				KillTimer(hWnd, 1);
				DrawEnd(hdc, clientRect);
			}
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
	for (Block b : block) {
		b.draw(memdc);
	}
	for (Item& i : item) {
		i.draw(memdc);
	}
	obj.draw(memdc);
	obj1.draw(memdc);

	if (drawCol) {
		for (Block b : block) {
			b.drawCol(memdc, clientRect);
		}
		obj.drawCol(memdc, clientRect);
		obj1.drawCol(memdc, clientRect);
		bullet.drawCol(memdc, clientRect);
		for (Item& i : item) {
			i.drawCol(memdc, clientRect);
		}
	}
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


	swprintf_s(newText, L"%d", 10 - elapsedTime / (timeLimit/10));
	TextOut(memdc, clientRect.right - 50, 10, newText, lstrlen(newText));


	swprintf_s(newText, L"%d", obj.getItem());
	TextOut(memdc, 302, 500, newText, lstrlen(newText));

	swprintf_s(newText, L"%d", obj1.getItem());
	TextOut(memdc, clientRect.right - 48, 500, newText, lstrlen(newText));

	HDC memdcimage = CreateCompatibleDC(memdc);
	RECT r{ 0, 0, 51,51 };
	FillRect(memdc,&r, (HBRUSH)GetStockObject(WHITE_BRUSH));
	oldbitmap[1] = (HBITMAP)SelectObject(memdcimage, windbitmap[1]);
	StretchBlt(memdc, 0, 0, 51, 51, memdcimage, 0, 0, 512, 512, SRCAND); // 바람
	oldbitmap[1] = (HBITMAP)SelectObject(memdcimage, windbitmap[0]);
	StretchBlt(memdc, 0, 0, 51, 51, memdcimage, 0, 0, 512, 512, SRCPAINT); // 바람

	

	HPEN hpen = CreatePen(PS_SOLID, 2, RGB(1, 1, 1));
	SelectObject(memdc, hpen);
	if (drawLine) {
		if (bullet.getDirChange()) {
			MoveToEx(memdc, bullet.getCenter().x - 10, bullet.getCenter().y + 10, NULL);
			LineTo(memdc, bullet.getCenter().x - 10 * aim_x - 20, 20 * aim_y + bullet.getCenter().y);
		}
		else {
			MoveToEx(memdc, bullet.getCenter().x + 10, bullet.getCenter().y + 10, NULL);
			LineTo(memdc, bullet.getCenter().x + 10 * aim_x + 20, 20 * aim_y + bullet.getCenter().y);
		}
	}
	SelectObject(memdcimage, power_gage[1]);
	StretchBlt(memdc, bullet.getCenter().x, bullet.getCenter().y - 60, 10, 50, memdcimage, 0, 0, 10, 88, SRCCOPY); // 닳은 power
	SelectObject(memdcimage, power_gage[0]);
	StretchBlt(memdc, bullet.getCenter().x , bullet.getCenter().y-10 - power_x, 10, power_x, memdcimage, 0, 0, 10, 88, SRCCOPY); // power

	if (bullet.getDraw()) {
		bullet.draw(memdc);
	}

	{//player 1
		SelectObject(memdcimage, player);
		TransparentBlt(memdc, 0, 450, 100, 100, memdcimage, 0, 0, 30, 30, RGB(0, 0, 0)); // font
		SelectObject(memdcimage, MP_M);
		StretchBlt(memdc, 100, 525, 200, 25, memdcimage, 0, 0, 88, 10, SRCCOPY); // 닳은 MP
		StretchBlt(memdc, 100, 500, 200, 25, memdcimage, 0, 0, 88, 10, SRCCOPY); // 닳은 HP
		SelectObject(memdcimage, MP);
		StretchBlt(memdc, 100, 525, obj.getMP(), 25, memdcimage, 0, 0, 88, 10, SRCCOPY); // MP
		SelectObject(memdcimage, HP_M);
		StretchBlt(memdc, 100, 500, obj.getHP(), 25, memdcimage, 0, 0, 88, 10, SRCCOPY); // HP
	}
	{//player 2
		SelectObject(memdcimage, player2);
		TransparentBlt(memdc, clientRect.right - 350, 450, 100, 100, memdcimage, 0, 0, 30, 30, RGB(0, 0, 0)); // font
		SelectObject(memdcimage, MP_M);
		StretchBlt(memdc, clientRect.right - 250, 525, 200, 25, memdcimage, 0, 0, 88, 10, SRCCOPY); // 닳은 MP
		StretchBlt(memdc, clientRect.right - 250, 500, 200, 25, memdcimage, 0, 0, 88, 10, SRCCOPY); // 닳은 HP
		SelectObject(memdcimage, MP);
		StretchBlt(memdc, clientRect.right - 250, 525, obj1.getMP(), 25, memdcimage, 0, 0, 88, 10, SRCCOPY); // MP
		SelectObject(memdcimage, HP_M);
		StretchBlt(memdc, clientRect.right - 250, 500, obj1.getHP(), 25, memdcimage, 0, 0, 88, 10, SRCCOPY); // HP
	}
	TransparentBlt(hdc, 0, 0, clientRect.right, clientRect.bottom, memdc, 0, 0, clientRect.right, clientRect.bottom,RGB(0, 0, 0));

	DeleteObject(hpen);
	DeleteObject(memdcimage);
	DeleteObject(hFont);
	DeleteObject(memdc);
	DeleteObject(hb);
}

void DrawEnd(HDC hdc, RECT clientRect) {
	HDC memdc = CreateCompatibleDC(hdc);
	HBITMAP hb = CreateCompatibleBitmap(hdc, clientRect.right, clientRect.bottom);
	SelectObject(memdc, hb);

	HFONT hFont = CreateFont(40, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, _T("Impact"));  // 폰트 생성
	SelectObject(memdc, hFont);
	TCHAR text[] = L"Player";
	TCHAR newText[20];
	if (obj.getTurn()) {
		swprintf_s(newText, L"%s 1 Win", text);
	}
	else if (obj1.getTurn()) {
		swprintf_s(newText, L"%s 2 Win", text);
	}
	SetTextColor(memdc, RGB(1, 1, 1));
	TextOut(memdc, clientRect.right / 2 - 100, clientRect.bottom / 2 - 50, newText, lstrlen(newText));

	TransparentBlt(hdc, 0, 0, clientRect.right, clientRect.bottom, memdc, 0, 0, clientRect.right, clientRect.bottom, RGB(0, 0, 0));
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
	drawLine = false;
	obj.setTurn(!obj.getTurn());
	obj1.setTurn(!obj1.getTurn());
	setBulletLoc();
	if (obj.getTurn()) {
		obj1.changeState(0);
		obj.setMP(200);
	}
	else {
		obj.changeState(0);
		obj1.setMP(200);
	}
}

void setBulletLoc()
{
	if (obj.getTurn()) {
		if (obj.getDirChange()) {
			bullet.setDirChange(true);
			bullet.setLoc({ obj.getColRect().left, obj.getCenter().y + 10 });
		}
		else {
			bullet.setDirChange(false);
			bullet.setLoc({ obj.getColRect().right, obj.getCenter().y + 10 });
		}
	}
	else {
		if (obj1.getDirChange()) {
			bullet.setDirChange(true);
			bullet.setLoc({ obj1.getColRect().left, obj1.getCenter().y + 10 });
		}
		else {
			bullet.setDirChange(false);
			bullet.setLoc({ obj1.getColRect().right, obj1.getCenter().y + 10 });
		}
	}
}

void checkCol()
{
	RECT rectA = bullet.getColRect();
	RECT rectB;

	rectB = obj.getColRect();
	if (rectA.right <= rectB.left || rectA.left >= rectB.right ||
		rectA.bottom <= rectB.top || rectA.top >= rectB.bottom) {
		// 충돌하지 않음
	}
	else {
		// 충돌함
		bullet.setDraw(false);
		obj.damageHP(HPDamage);
		if (obj.getHP() <= 0) {
			gameOver = true;
		}
	}
	rectB = obj1.getColRect();
	if (rectA.right <= rectB.left || rectA.left >= rectB.right ||
		rectA.bottom <= rectB.top || rectA.top >= rectB.bottom) {
		// 충돌하지 않음
	}
	else {
		// 충돌함
		bullet.setDraw(false);
		obj1.damageHP(HPDamage);
		if (obj1.getHP() <= 0) {
			gameOver = true;
		}
	}
}

void checkItemCol() {
	RECT rectA;
	RECT rectB;
	vector<int> itindex;
	for(int i = 0; i < item.size(); i++){
		Item it = item[i];
		rectA = it.getColRect();
		rectB = obj.getColRect();
		if (rectA.right <= rectB.left || rectA.left >= rectB.right ||
			rectA.bottom <= rectB.top || rectA.top >= rectB.bottom) {
			// 충돌하지 않음
		}
		else {
			// 충돌함
			obj.addItem();
			itindex.push_back(i);
		}
		rectB = obj1.getColRect();
		if (rectA.right <= rectB.left || rectA.left >= rectB.right ||
			rectA.bottom <= rectB.top || rectA.top >= rectB.bottom) {
			// 충돌하지 않음
		}
		else {
			// 충돌함
			obj1.addItem();
			itindex.push_back(i);
		}
	}

	for (int i = itindex.size(); i > 0; i--) {
		item.erase(item.begin() + (i - 1));
	}
}

void setImgs()
{
	stage1.setBmp(g_hInst, IDB_BITMAP4, IDB_BITMAP5, 0);
	//6, 9, 11 is Max
	stage1.setBmp(g_hInst, IDB_BITMAP7, IDB_BITMAP6, 1);
	stage1.setBmp(g_hInst, IDB_BITMAP8, IDB_BITMAP9, 2);
	stage1.setBmp(g_hInst, IDB_BITMAP10, IDB_BITMAP11, 3);
}
