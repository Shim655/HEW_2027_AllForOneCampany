/*
* +-------------------------------------+
* File   : main[main.cpp]
* Author : 沈揆賢
* Date   : 2026/10/10
*
*
*
* +-------------------------------------+
*/

//+-----------------------------+
//	ライブラリのリンク
//+-----------------------------+
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"dinput8.lib")
#ifdef _DEBUG
#pragma comment(lib,"box2dd.lib")
#pragma comment(lib,"DirectXTKd.lib")
#else
#pragma comment(lib,"box2d.lib")
#pragma comment(lib,"DirectXTK.lib")
#endif


#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <box2d.h>

#include "main.h"
#include "renderer.h"
#include "sprite.h"
#include "texture.h"
#include "sound.h"
#include "keyboard.h"
#include "mouse.h"
#include "camera.h"
#include "text.h"
#include "game.h"
using namespace DirectX;



//+-----------------------------+
//	定数定義
//+-----------------------------+
#define CLASS_NAME "GameWindow"
#define WINDOW_CAPTION "HEW_2027"

//+-----------------------------+
//	プロトタイプ宣言
//+-----------------------------+
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void Initialize(HINSTANCE hInstance, HWND hWnd);
void Finalize();
void Update();
void Draw();

static XMFLOAT2 g_windowSize{ (float)SCREEN_WIDTH,(float)SCREEN_HEIGHT };

XMFLOAT2 GetWindowSize(void)
{
	return g_windowSize;
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// COMの初期化
	CoInitializeEx(nullptr, COINIT_MULTITHREADED);

	WNDCLASS  wc = {};
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = CLASS_NAME;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	RegisterClass(&wc);


	RECT windowrect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	DWORD windowStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;
	AdjustWindowRect(&windowrect, windowStyle, FALSE);

	// ウインドウのクライアント領域の幅と高さを計算
	int windowWidth = windowrect.right - windowrect.left;
	int windowHeight = windowrect.bottom - windowrect.top;

	HWND hWnd = CreateWindow(
		CLASS_NAME,
		WINDOW_CAPTION,
		windowStyle,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		windowWidth,
		windowHeight,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	Initialize(hInstance, hWnd);

	// ウインドウの表示
	ShowWindow(hWnd, nCmdShow);

	//フレームレート処理
	DWORD dwExecLastTime;
	DWORD dwCurrentTime;
	timeBeginPeriod(1);
	dwExecLastTime = timeGetTime();
	dwCurrentTime = 0;

	// メッセージループ
	MSG msg = {};
	do
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			dwCurrentTime = timeGetTime();

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{
#if _DEBUG
				XMINT2 mousePosition = GetMousePosition();
				char messageFPS[256];

				sprintf_s(messageFPS, "FPS: %d / Mouse(x: %d y: %d)", 1000 / (dwCurrentTime - dwExecLastTime), mousePosition.x, mousePosition.y);
				SetWindowText(hWnd, messageFPS);
#endif
				dwExecLastTime = dwCurrentTime;

				Update();
				Clear();
				Draw();
				Present();
			}
		}
	} while (msg.message != WM_QUIT);

	Finalize();

	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_ACTIVATEAPP:
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
	case WM_KEYUP:
	case WM_SYSKEYUP:
		Keyboard_ProcessMessage(uMsg, wParam, lParam);
		break;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);

		SetTextColor(hdc, RGB(0, 0, 0));
		SetBkColor(hdc, RGB(0, 0, 255));
		TextOut(hdc, 50, 50, "Hello Windows!", 14);

		EndPaint(hWnd, &ps);
	}
	return 0;

	case WM_CLOSE:
		if (MessageBox(hWnd, "本当に終了してよろしいですか？", "確認", MB_OKCANCEL | MB_DEFBUTTON2) == IDOK)
		{
			DestroyWindow(hWnd);
		}
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_MOUSEMOVE:
	case WM_MOUSEWHEEL:
	case WM_LBUTTONUP:
	case WM_LBUTTONDOWN:
	case WM_LBUTTONDBLCLK:
	case WM_MBUTTONUP:
	case WM_MBUTTONDOWN:
	case WM_MBUTTONDBLCLK:
	case WM_RBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONDBLCLK:
		Mouse_ProcessMessage(uMsg, wParam, lParam);
		break;

	case WM_SIZE:
		RECT rect{};
		GetClientRect(hWnd, &rect);
		const float clientWidth = (float)(rect.right - rect.left);
		const float clientHeight = (float)(rect.bottom - rect.top);
		g_windowSize = { clientWidth,clientHeight };
		break;
	};

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

void Initialize(HINSTANCE hInstance, HWND hWnd)
{
	g_windowSize = { (float)SCREEN_WIDTH,(float)SCREEN_HEIGHT };

	//DirectX初期化
	InitRenderer(hInstance, hWnd, FALSE);
	InitSprite();
	InitializeTexture();
	InitSound(hWnd);

	Keyboard_Initialize();
	Mouse_Initialize();

	InitializeCamera();
	InitializeText();
	InitializeGame();
}

void Finalize()
{
	FinalizeGame();
	FinalizeText();

	//DirectXの終了処理
	UninitSound();
	FinalizeTexture();
	UninitSprite();
	UninitRenderer();
}

void Update()
{
	UpdateCamera();
	UpdateGame();

	Keyboard_Update();
	Mouse_Update();
}

void Draw()
{
	DrawGame();
}
