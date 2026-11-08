/*
* +-------------------------------------+
* File   : [UI_GetBuilding.cpp]
* Author : 沈揆賢
* Date   : 2026/11/01
*
*
* 押すと建物が出るボタン
* +-------------------------------------+
*/
#include "UI_GetBuilding.h"
#include "sprite.h"
#include "texture.h"
#include "mouse.h"
#include "color.h"
#include "text.h"
#include "jenga_player.h"
#include "EmergencyManager.h"
using namespace DirectX;

static constexpr int PRICE = 100;


void UI_GetBuilding::Initialize(void)
{
	GameObject::SetTextureID(LoadTexture(L"asset\\block.png"));
}

void UI_GetBuilding::Finalize(void)
{
	ReleaseTexture(GameObject::GetTextureID());
}

void UI_GetBuilding::Update(void)
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

		if (GetMoney() >= PRICE)
		{
			AddMoney(-PRICE);
			PlayerGetBuilding(BUILDING_TYPE::_0);
		}
	}
}

void UI_GetBuilding::Draw(void) const
{
	if (GetIsEmergency())
	{
		return;
	}

	const XMFLOAT2 position = GameObject::GetPosition();
	const std::wstring text = std::wstring{ L"$" } + std::to_wstring(PRICE);
	DrawSpriteText(text, { position.x - 50.0f,position.y - 100.0f });

	DrawSprite(
		GameObject::GetPosition(), GameObject::GetSize(), GameObject::GetRotation(),
		GameObject::GetTextureID(),
		GameObject::GetColor());
}
