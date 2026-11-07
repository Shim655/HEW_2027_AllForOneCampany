/*
* +-------------------------------------+
* File   : 色コード[color.h]
* Author : 沈揆賢
* Date   : 2026/10/10
*
*
* 色コード : https://www.colordic.org/
*
* +-------------------------------------+
*/
#pragma once

#include <DirectXMath.h>

enum class COLOR
{
	WHITE,
	BLACK,
	RED,
	BLUE,
	YELLOW,
	ORANGE,
	GREEN,
	DARKBLUE,
	PURPLE
};

DirectX::XMFLOAT4 GetColorCode(COLOR color, float alfa = 1.0f);