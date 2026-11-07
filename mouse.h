/*
* +-------------------------------------+
* File   : É}ÉEÉXì¸óÕ[mouse.h]
* Author : íæùÑå´
* Date   : 2026/10/10
*
*
*
* +-------------------------------------+
*/
#pragma once

#include <Windows.h>
#include <DirectXMath.h>

enum class MOUSE
{
	BUTTON_LEFT_UP,
	BUTTON_LEFT_DOWN,
	BUTTON_LEFT_DBLCLK,
	BUTTON_MIDDLE_UP,
	BUTTON_MIDDLE_DOWN,
	BUTTON_MIDDLE_DBLCLK,
	BUTTON_RIGHT_UP,
	BUTTON_RIGHT_DOWN,
	BUTTON_RIGHT_DBLCLK,
	WHEEL_UP,
	WHEEL_DOWN,
	SIZE_MOUSE
};

void Mouse_Initialize(void);
void Mouse_Update(void);
void Mouse_ProcessMessage(UINT message, WPARAM wParam, LPARAM lParam);
bool GetMouseState(MOUSE state);
DirectX::XMINT2 GetMousePosition(void);