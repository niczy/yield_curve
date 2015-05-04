#pragma once
#include "MonteCarlo.h"
#include "TrinomialTree.h"
class MonteCarlo;
class CTrinomialTree;

class CInstrument
{
	public:
	CInstrument(double pymtfreq = 0, double Principal = 0, double Maturity = 0)
		: m_pymtFreq(pymtfreq)
		, m_Principal(Principal)
		, m_Maturity(Maturity)
		{}

	~CInstrument(void)
	{}

	virtual void addInstrumenttoFile(void)
	{
	}

	virtual void readInstrumentfromFile(void)
	{
	}

	virtual void deleteInstrumentfromFile(void)
	{
	}
	
	virtual void Cashflows(void)
	{
	}

	protected:
		double m_pymtFreq;
		double m_Principal;
		double m_Maturity;


	

	/*double PriceTree(int n, double Maturity, CTrinomialTree &MyTree)
	{
		double sum(0);
		for(int i = 0; i < Maturity ; i++)
		{
			for(int j = Nabc; j < ; j++)
			{
				sum += MyTree.GetQ_ij(i,j) * this->CashFlow(0.1, n, i);
			}

		}
	}*/
	//{ddouble sum MyTree.getQPrice * Cashflow(r,j)};

private:
	double m_QPrice;
	double m_DF;

public:
	virtual double CashFlow(double Rate, int n, int m);

	double PriceMC(int n, double NbScenarios, double Maturity, MonteCarlo &aMC)				
          //n is object number in list // needs MonteCarlo to be friends
	{
		double sum(0);
		double sum2(0);
		for(int k = 0; k < NbScenarios; k++)
		{	
			sum = 0;
			for(int i = 0; i < Maturity; i++)			//m is number of cash flows
			{
				double mcrate = aMC.r[k][i];
                                sum += CashFlow(mcrate, n, i) * aMC.dF[k][i];
			}
			sum2 += sum;
		}
		return sum2/NbScenarios;
	};
};
