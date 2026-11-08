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

	virtual void Initialize(void);
	virtual void Update(void);

	void IncreaseEmployee(void)
	{
		m_numEmployee++;
	}

	bool CanRunBusiness(void);
	int GetRunPercent(void) const;

	int GetNumEmployeeNeeded(void) const
	{
		return m_numEmployeeNeeded;
	}
	int GetNumEmployee(void) const
	{
		return m_numEmployee;
	}
	int GetIncome(void) const
	{
		return m_income;
	}

private:
	int m_frameCount{ 0 };
	int m_numEmployeeNeeded{ 0 };
	int m_numEmployee{ 0 };
	int m_income{ 0 };
};