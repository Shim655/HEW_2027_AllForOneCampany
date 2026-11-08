/*
* +-------------------------------------+
* File   : ƒrƒ‹ƒNƒ‰ƒX[Building.cpp]
* Author : ’¾„Œ«
* Date   : 2026/11/02
*
*
*
* +-------------------------------------+
*/
#include "Building.h"
#include "Business_000.h"
#include "color.h"
#include "sprite.h"
#include "texture.h"
#include "text.h"
using namespace DirectX;

static int g_circleEffectTextureID{ -1 };


void Building::Update(void)
{
	if (m_business == nullptr)
	{
		return;
	}

	GameObject::SetColor(GetColorCode(COLOR::ORANGE));
	m_business->Update();
}

void Building::Draw(void) const
{
	if (m_business == nullptr)
	{
		return;
	}

	const XMFLOAT2 position = GameObject::GetRigidBody()->GetPosition();

	if (m_business->CanRunBusiness())
	{
		DrawSpriteCirclePercentScroll(
			position,
			40.0f,
			m_business->GetRunPercent(),
			g_circleEffectTextureID);
	}
	else
	{
		const std::wstring text = std::to_wstring(m_business->GetNumEmployee()) + std::wstring{ L"/" } + std::to_wstring(m_business->GetNumEmployeeNeeded());
		DrawSpriteTextScroll(text, { position.x - 25.0f,position.y - 15.0f }, 0.8f);
	}
}

void Building::SetBusiness(BUSINESS_TYPE type)
{
	if (m_business)
	{
		return;
	}

	switch (type)
	{
	case BUSINESS_TYPE::_000:
		m_business = std::make_unique< Business_000>(1, 100);
		break;

	case BUSINESS_TYPE::_001:
		break;

	default:
		break;
	}

	m_business->Initialize();
}

void Building::IncreaseEmployee(void)
{
	if (m_business == nullptr)
	{
		return;
	}

	m_business->IncreaseEmployee();
}

void Building::SetCircleEffectTexture(void)
{
	g_circleEffectTextureID = LoadTexture(L"asset\\Fade.png");
}

void Building::ReleaseCircleEffectTexture(void)
{
	ReleaseTexture(g_circleEffectTextureID);
}
