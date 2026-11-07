/*
* +-------------------------------------+
* File   : 色コード[color.cpp]
* Author : 沈揆賢
* Date   : 2026/10/10
*
*
* 色コード : https://www.colordic.org/
*
* +-------------------------------------+
*/
#include "color.h"

using namespace DirectX;

XMFLOAT4 GetColorCode(COLOR color,float alfa)
{
	switch (color)
	{
	case COLOR::WHITE:
		return XMFLOAT4(255.0f / 255, 255.0f / 255, 255.0f / 255, alfa);
	case COLOR::BLACK:
		return XMFLOAT4(0.0f / 255, 0.0f / 255, 0.0f / 255, alfa);
	case COLOR::RED:
		return XMFLOAT4(255.0f / 255, 0.0f / 255, 0.0f / 255, alfa);
	case COLOR::BLUE:
		return XMFLOAT4(0.0f / 255, 0.0f / 255, 255.0f / 255, alfa);
	case COLOR::YELLOW:
		return XMFLOAT4(255.0f / 255, 255.0f / 255, 0.0f / 255, alfa);
	case COLOR::ORANGE:
		return XMFLOAT4(255.0f / 255, 165.0f / 255, 0.0f / 255, alfa);
	case COLOR::GREEN:
		return XMFLOAT4(0.0f / 255, 128.0f / 255, 0.0f / 255, alfa);
	case COLOR::DARKBLUE:
		return XMFLOAT4(0.0f / 255, 0.0f / 255, 139.0f / 255, alfa);
	case COLOR::PURPLE:
		return XMFLOAT4(128.0f / 255, 0.0f / 255, 128.0f / 255, alfa);
	default:
		return XMFLOAT4(255.0f / 255, 255.0f / 255, 255.0f / 255, alfa);
		break;
	}
}