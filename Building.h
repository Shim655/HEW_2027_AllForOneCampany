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
	void Draw(void) const;

	void SetBusiness(BUSINESS_TYPE type);
	void IncreaseEmployee(void);

	static void SetCircleEffectTexture(void);
	static void ReleaseCircleEffectTexture(void);

	BUILDING_TYPE GetBuildingType(void) const
	{
		return m_type;
	}
	const Business* GetBusiness(void) const
	{
		return m_business.get();
	}

private:
	BUILDING_TYPE m_type;
	std::unique_ptr<Business>m_business{ nullptr };
};


