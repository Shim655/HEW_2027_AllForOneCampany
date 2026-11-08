/*
* +-------------------------------------+
* File   : [UI_GetBusiness.cpp]
* Author : 沈揆賢
* Date   : 2026/11/05
*
*
* 押すと事業をゲットする
* +-------------------------------------+
*/
#include "UI_GetBusiness.h"
#include "sprite.h"
#include "texture.h"
#include "mouse.h"
#include "color.h"
#include "text.h"
#include "jenga_player.h"
#include "EmergencyManager.h"
using namespace DirectX;

static constexpr int NUM_EMPLOYEE_NEEDED = 1;


void UI_GetBusiness::Initialize(void)
{
	GameObject::SetTextureID(LoadTexture(L"asset\\UI_Heart_Full.png"));
}

void UI_GetBusiness::Finalize(void)
{
	ReleaseTexture(GameObject::GetTextureID());
}

void UI_GetBusiness::Update(void)
{
	if (GetIsEmergency())
	{
		return;
	}

	if (GameObject::IsOnMouse() == false)
	{
		GameObject::SetColor(GetColorCode(COLOR::WHITE));
		return;
	}

	if (GetMouseState(MOUSE::BUTTON_LEFT_DOWN))
	{
		GameObject::SetColor(GetColorCode(COLOR::WHITE, 0.5f));
	}
	if (GetMouseState(MOUSE::BUTTON_LEFT_UP))
	{
		//ボタンを押したときの処理
		GameObject::SetColor(GetColorCode(COLOR::WHITE));

		PlayerGetBusiness(BUSINESS_TYPE::_000);
	}
}

void UI_GetBusiness::Draw(void) const
{
	if (GetIsEmergency())
	{
		return;
	}

	const XMFLOAT2 position = GameObject::GetPosition();
	const std::wstring text0 = std::wstring{ L"必要社員数：" } + std::to_wstring(NUM_EMPLOYEE_NEEDED);
	const std::wstring text1 = std::wstring{ L"収益：" } + std::to_wstring(100);
	DrawSpriteText(text0, { position.x - 70.0f,position.y - 130.0f });
	DrawSpriteText(text1, { position.x - 70.0f,position.y - 100.0f });

	DrawSprite(
		GameObject::GetPosition(), GameObject::GetSize(), GameObject::GetRotation(),
		GameObject::GetTextureID(),
		GameObject::GetColor());
}
