/*
* +-------------------------------------+
* File   : [Inseki.h]
* Author : ’¾„Œ«
* Date   : 2026/11/07
*
*
* è¦Î
* +-------------------------------------+
*/
#pragma once

#include "GameObject.h"

class Inseki : public GameObject
{
public:
	Inseki(DirectX::XMFLOAT2 position, DirectX::XMFLOAT2 size, float radius)
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