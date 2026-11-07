/*
* +-------------------------------------+
* File   : [UI_GetEmployee.cpp]
* Author : ’¾„Œ«
* Date   : 2026/11/03
*
*
* ‰Ÿ‚·‚ÆŽÐˆõ‚ðŒÙ—p‚·‚é
* +-------------------------------------+
*/
#include "UI_GetEmployee.h"
#include "sprite.h"
#include "texture.h"
#include "mouse.h"
#include "color.h"
#include "text.h"
#include "player.h"
using namespace DirectX;

static constexpr int PRICE = 100;


void UI_GetEmployee::Initialize(void)
{
	GameObject::SetTextureID(LoadTexture(L"asset\\Princess.png"));
}

void UI_GetEmployee::Finalize(void)
{
	ReleaseTexture(GameObject::GetTextureID());
}

void UI_GetEmployee::Update(void)
{
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
		//ƒ{ƒ^ƒ“‚ð‰Ÿ‚µ‚½‚Æ‚«‚Ìˆ—
		GameObject::SetColor(GetColorCode(COLOR::WHITE));

		if (GetMoney() >= PRICE)
		{
			AddMoney(-PRICE);
			AddEmployee();
		}



	}
}

void UI_GetEmployee::Draw(void) const
{
	const XMFLOAT2 position = GameObject::GetPosition();
	const std::wstring text = std::wstring{ L"$" } + std::to_wstring(PRICE);
	DrawSpriteText(text, { position.x - 50.0f,position.y - 100.0f });

	DrawSprite(
		position, GameObject::GetSize(), GameObject::GetRotation(),
		GameObject::GetTextureID(),
		GameObject::GetColor());
}
