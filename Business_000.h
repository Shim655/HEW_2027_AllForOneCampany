/*
* +-------------------------------------+
* File   : –‹ÆƒNƒ‰ƒX[Business.h]
* Author : ’¾„Œ«
* Date   : 2026/11/04
*
*
* –‹Æ000
* +-------------------------------------+
*/
#pragma once

#include "Business.h"

class Business_000 : public Business
{
public:
	Business_000(int numEmployeeNeeded, int income)
		: Business(numEmployeeNeeded, income)
	{

	}

	void Initialize(void) override;
	void Update(void) override;

private:
	int m_frameCount{ 0 };
};