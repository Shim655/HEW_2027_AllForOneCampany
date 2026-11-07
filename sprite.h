/*
* +-------------------------------------+
* File   : É|ÉäÉSÉìï`âÊ[sprite.h]
* Author : íæùÑå´
* Date   : 2026/10/10
*
*
*
* +-------------------------------------+
*/
#pragma once

#include <DirectXMath.h>

void InitSprite(void);
void UninitSprite(void);

void DrawSprite(DirectX::XMFLOAT2 position, DirectX::XMFLOAT2 size, float rotation, int textureID, DirectX::XMFLOAT4 color = { 1.0f,1.0f,1.0f,1.0f });
void DrawSpriteScroll(DirectX::XMFLOAT2 position, DirectX::XMFLOAT2 size, float rotation, int textureID, DirectX::XMFLOAT4 color = { 1.0f,1.0f,1.0f,1.0f });
void DrawSpriteZoom(DirectX::XMFLOAT2 position, DirectX::XMFLOAT2 size, float rotation, int textureID, DirectX::XMFLOAT4 color);
void DrawSpriteCirclePercentScroll(DirectX::XMFLOAT2 position, float radius, int percent, int textureID);
void DrawSpriteAnime(
	DirectX::XMFLOAT2 position, DirectX::XMFLOAT2 size, DirectX::XMFLOAT2 textureCoordinate, DirectX::XMFLOAT2 textureSize,
	int textureID, bool flip = false, DirectX::XMFLOAT4 color = { 1.0f,1.0f,1.0f,1.0f });
