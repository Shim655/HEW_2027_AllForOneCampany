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

void Building::Update(void)
{
	if (m_business == nullptr)
	{
		return;
	}

	GameObject::SetColor(GetColorCode(COLOR::ORANGE));
	m_business->Update();
}

void Building::SetBusiness(BUSINESS_TYPE type)
{
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
