/*
* +-------------------------------------+
* File   : 事業クラス[Business.h]
* Author : 沈揆賢
* Date   : 2026/11/08
*
*
* 全ての事業の親クラス
* +-------------------------------------+
*/
#include "Business.h"
#include "jenga_player.h"

void Business::Initialize(void)
{
	m_frameCount = 0;
}

void Business::Update(void)
{
	if (CanRunBusiness() == false)
	{
		return;
	}

	m_frameCount++;
	if (m_frameCount > 60 * 10)
	{
		AddMoney(m_income);
		m_frameCount = 0;
	}
}


bool Business::CanRunBusiness(void)
{
	if (m_numEmployee >= m_numEmployeeNeeded)
	{
		return true;
	}

	return false;
}

int Business::GetRunPercent(void) const
{
	const int runTime = m_frameCount / 60;

	return ((float)runTime / 10.0f) * 100.0f;
}