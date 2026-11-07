/*
* +-------------------------------------+
* File   : [UI_Score.cpp]
* Author : 沈揆賢
* Date   : 2026/11/03
*
*
* スコア表示
* +-------------------------------------+
*/
#include "UI_Score.h"
#include "sprite.h"
#include "texture.h"
#include "text.h"
#include "jenga_player.h"
using namespace DirectX;

void UI_Score::Initialize(void)
{
}

void UI_Score::Finalize(void)
{
}

void UI_Score::Update(void)
{
}

void UI_Score::Draw(void) const
{
	const XMFLOAT2 position = GameObject::GetPosition();
	const int money = GetMoney();
	const int numEmployee = GetNumEmployee();

	const std::wstring textMoney = std::wstring{ L"資金：$" } + std::to_wstring(money);
	const std::wstring textEmployee = std::wstring{ L"社員数：" } + std::to_wstring(numEmployee);

	DrawSpriteText(textMoney, position);
	DrawSpriteText(textEmployee, { position.x,position.y + 30.0f });
}
