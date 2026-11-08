/*
* +-------------------------------------+
* File   : テキスト出力[text.cpp]
* Author : 沈揆賢
* Date   : 2026/11/03
*
*
*
* +-------------------------------------+
*/
#pragma once
#include <DirectXMath.h>
#include <string>

void InitializeText(void);
void FinalizeText(void);
void DrawSpriteText(const std::wstring& text, DirectX::XMFLOAT2 position, float scale = 1.0f, DirectX::XMFLOAT4 color = { 1.0f,1.0f,1.0f,1.0f });
void DrawSpriteTextScroll(const std::wstring& text, DirectX::XMFLOAT2 position, float scale = 1.0f, float rotation = 0.0f, DirectX::XMFLOAT4 color = { 1.0f,1.0f,1.0f,1.0f });
