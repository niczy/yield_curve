#pragma once

class CDomesticPricing
{
public:
CDomesticPricing(int currency)
	: m_Currency(currency)
	, m_maxTerm(10)
	, m_dt(1/12)
	, m_NbScenarios(10)
{
	if(currency == 0)
		ObjectCountUS++;
	else
		ObjectCountCN++;
}

	~CDomesticPricing(void)
	{}

	static int ObjectCountUS;
	static int ObjectCountCN;

protected:
	char m_Currency;
	int m_maxTerm;
	double m_dt;
	double m_NbScenarios;	

public:
	void deleteMethod(CDomesticPricing)
	{
	}

	/*void constructMethods()
	{
		if(this->m_Currency == 0)
		{
			//CYieldCurve MyYieldCurve_US;
			CTrinomialTree MyTrinomialTree_US(...);
			CBrownianMotion MyBrownianMotion_US(...);
			CMonteCarlo MyMonteCarlo_US(...);
		}
		else if(this->m_Currency == 1)
		{
			//CYieldCurve MyYieldCurve_CN;
			CMonteCarlo MyMonteCarlo_CN(...);
			CBrownianMotion MyBrownianMotion_CN(...);
			CTrinomialTree MyTrinomialTree_CN(...);
			
		}
	}*/

};

