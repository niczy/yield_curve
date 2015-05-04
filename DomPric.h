#pragma once

class CDomesticPricing
{
public:
	static int ObjectCountUS;
	int m_maxTerm;
	double m_dt;
	double m_NbScenarios;

	CDomesticPricing(int currency): m_Currency(currency), m_maxTerm(12), m_dt(0.08333333333333), m_NbScenarios(10)
	{
	if(currency == 0)
		ObjectCountUS++;
	}

	~CDomesticPricing(void)
	{}

private:
	int m_Currency;

};