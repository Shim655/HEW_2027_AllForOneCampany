/*
* +-------------------------------------+
* File   : É}ÉEÉXì¸óÕ[mouse.cpp]
* Author : íæùÑå´
* Date   : 2026/10/10
*
*
*
* +-------------------------------------+
*/
#include "main.h"
#include "mouse.h"

using namespace DirectX;

static constexpr int NUM_MOUSE_STATE = static_cast<int>(MOUSE::SIZE_MOUSE);

struct Mouse
{
	bool mouseStates[NUM_MOUSE_STATE]{ false };
	XMINT2 mousePosition{ 0,0 };
};

static Mouse g_mouse;
static Mouse g_oldMouse;

void Mouse_Initialize(void)
{
	for (bool& state : g_mouse.mouseStates)
	{
		state = false;
	}

	g_mouse.mousePosition = XMINT2(0, 0);

	g_oldMouse = g_mouse;

}

void Mouse_Update(void)
{
	g_oldMouse = g_mouse;

	for (bool& state : g_mouse.mouseStates)
	{
		state = false;
	}
}

void Mouse_ProcessMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_MOUSEMOVE:
		const XMFLOAT2 windowSize = GetWindowSize();

		g_mouse.mousePosition.x = LOWORD(lParam) * ((float)SCREEN_WIDTH / windowSize.x);
		g_mouse.mousePosition.y = HIWORD(lParam) * ((float)SCREEN_HEIGHT / windowSize.y);
		break;

	case WM_MOUSEWHEEL:
	{
		int wheel = GET_WHEEL_DELTA_WPARAM(wParam);
		if (wheel > 0)
		{
			g_mouse.mouseStates[static_cast<int>(MOUSE::WHEEL_UP)] = true;
		}
		else
		{
			g_mouse.mouseStates[static_cast<int>(MOUSE::WHEEL_DOWN)] = true;
		}
	}
	break;

	case WM_LBUTTONUP:
		g_mouse.mouseStates[static_cast<int>(MOUSE::BUTTON_LEFT_UP)] = true;
		break;

	case WM_LBUTTONDOWN:
		g_mouse.mouseStates[static_cast<int>(MOUSE::BUTTON_LEFT_DOWN)] = true;
		break;

	case WM_LBUTTONDBLCLK:
		g_mouse.mouseStates[static_cast<int>(MOUSE::BUTTON_LEFT_DBLCLK)] = true;
		break;

	case WM_MBUTTONUP:
		g_mouse.mouseStates[static_cast<int>(MOUSE::BUTTON_MIDDLE_UP)] = true;
		break;

	case WM_MBUTTONDOWN:
		g_mouse.mouseStates[static_cast<int>(MOUSE::BUTTON_MIDDLE_DOWN)] = true;
		break;

	case WM_MBUTTONDBLCLK:
		g_mouse.mouseStates[static_cast<int>(MOUSE::BUTTON_MIDDLE_DBLCLK)] = true;
		break;

	case WM_RBUTTONUP:
		g_mouse.mouseStates[static_cast<int>(MOUSE::BUTTON_RIGHT_UP)] = true;
		break;

	case WM_RBUTTONDOWN:
		g_mouse.mouseStates[static_cast<int>(MOUSE::BUTTON_RIGHT_DOWN)] = true;
		break;

	case WM_RBUTTONDBLCLK:
		g_mouse.mouseStates[static_cast<int>(MOUSE::BUTTON_RIGHT_DBLCLK)] = true;
		break;

	default:
		break;
	}
}

bool GetMouseState(MOUSE state)
{
	const int stateAsked = static_cast<int>(state);

	return g_oldMouse.mouseStates[stateAsked];
}

XMINT2 GetMousePosition(void)
{
	return g_oldMouse.mousePosition;
}
