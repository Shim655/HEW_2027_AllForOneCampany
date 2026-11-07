/*
* +-------------------------------------+
* File   : Ž–‹ÆƒNƒ‰ƒX[Business.h]
* Author : ’¾„Œ«
* Date   : 2026/11/04
*
*
* Ž–‹Æ000
* +-------------------------------------+
*/
#include "Business_000.h"
#include "player.h"


void Business_000::Initialize(void)
{
	m_frameCount = 0;
}

void Business_000::Update(void)
{
	m_frameCount++;
	if (m_frameCount > 60 * 10)
	{
		AddMoney(Business::GetIncome());
		m_frameCount = 0;
	}
}
