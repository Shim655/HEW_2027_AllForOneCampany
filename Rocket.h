/*
* +-------------------------------------+
* File   : [Rocket.h]
* Author : ’¾„Œ«
* Date   : 2026/11/07
*
*
* ƒƒPƒbƒg
* +-------------------------------------+
*/
#pragma once

#include "GameObject.h"

class Rocket : public GameObject
{
public:
	Rocket(DirectX::XMFLOAT2 position, DirectX::XMFLOAT2 size, float radius)
		: GameObject{ position, size, 0.0f }
		, m_radius{ radius }
	{

	}

	float GetRadius(void) const
	{
		return m_radius;
	}

private:
	float m_radius;
};