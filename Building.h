/*
* +-------------------------------------+
* File   : ÉrÉãÉNÉâÉX[Building.h]
* Author : íæùÑå´
* Date   : 2026/11/02
*
*
*
* +-------------------------------------+
*/
#pragma once

#include <memory>
#include "GameObject.h"
#include "Business.h"

enum class BUILDING_TYPE
{
	_0,
	_1,
	_2,
};

class Building : public GameObject
{
public:
	Building(DirectX::XMFLOAT2 position, float rotation, BUILDING_TYPE type)
		: GameObject(position, {50.0f,100.0f}, rotation)
		, m_type{ type }
	{

	}

	void Update(void);

	void SetBusiness(BUSINESS_TYPE type);

	BUILDING_TYPE GetBuildingType(void) const
	{
		return m_type;
	}

private:
	BUILDING_TYPE m_type;
	std::unique_ptr<Business>m_business{ nullptr };
};


