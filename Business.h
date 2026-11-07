/*
* +-------------------------------------+
* File   : 事業クラス[Business.h]
* Author : 沈揆賢
* Date   : 2026/11/04
*
*
* 全ての事業の親クラス
* +-------------------------------------+
*/
#pragma once

enum class BUSINESS_TYPE
{
	NONE,
	_000,
	_001,
};

class Business
{
public:
	Business() = delete;
	Business(int numEmployeeNeeded, int income)
		: m_numEmployeeNeeded{ numEmployeeNeeded }
		, m_income{ income }
	{

	}
	virtual ~Business() = default;

	virtual void Initialize(void) = 0;
	virtual void Update(void) = 0;

	int GetNumEmployeeNeeded(void) const
	{
		return m_numEmployeeNeeded;
	}
	int GetIncome(void) const
	{
		return m_income;
	}

private:
	int m_numEmployeeNeeded{ 0 };
	int m_income{ 0 };
};