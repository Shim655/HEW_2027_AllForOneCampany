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
#include <DirectXMath.h>
#include <SpriteBatch.h>
#include <SpriteFont.h>
#include <memory>
#include <string>
#include "renderer.h"
#include "camera.h"
using namespace DirectX;


static std::unique_ptr<SpriteBatch>g_spriteBatch;
static std::unique_ptr<SpriteFont>g_spriteFont;

void InitializeText(void)
{
	g_spriteBatch = std::make_unique<SpriteBatch>(GetDeviceContext());
	g_spriteFont = std::make_unique<SpriteFont>(GetDevice(), L"asset\\jp_font.spritefont");
}

void FinalizeText(void)
{

}

void DrawSpriteText(const std::wstring& text, XMFLOAT2 position, float scale, XMFLOAT4 color)
{
	g_spriteBatch->Begin();

	const XMVECTOR textColor = { color.x,color.y,color.z,color.w };
	const float rotation = 0.0f;

	g_spriteFont->DrawString(
		g_spriteBatch.get(),
		text.c_str(),
		position,
		textColor,
		rotation,
		{ 0.0f,0.0f },
		scale
	);

	g_spriteBatch->End();

	ResetRenderer();
}

void DrawSpriteTextScroll(const std::wstring& text, XMFLOAT2 position, float scale, float rotation, XMFLOAT4 color)
{
	//カメラ
	const XMFLOAT3 camera = GetCameraOffset();
	const float centerX = SCREEN_WIDTH * 0.5f;
	const float centerY = SCREEN_HEIGHT * 0.5f;
	position.x += camera.x;
	position.y += camera.y;
	position.x = centerX + (position.x - centerX) * camera.z;
	position.y = centerY + (position.y - centerY) * camera.z;
	scale *= camera.z;


	g_spriteBatch->Begin();

	const XMVECTOR textColor = { color.x,color.y,color.z,color.w };
	g_spriteFont->DrawString(
		g_spriteBatch.get(),
		text.c_str(),
		position,
		textColor,
		rotation,
		{ 0.0f,0.0f },
		scale
	);

	g_spriteBatch->End();

	ResetRenderer();
}