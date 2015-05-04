#pragma once
#include "TrinomialTree.h"
#include "BrowianMotion.h"

class MonteCarlo
{
public:
	double **r;
	double **rStar;
	double **dF;

	//Constructor
	MonteCarlo(int o_maxSenarios,int o_maxTerms, double o_sigma, double o_a, double o_delta)
	{
		maxSenarios = o_maxSenarios;
		maxTerms = o_maxTerms;
		sigma = o_sigma;
		a = o_a;
		delta = o_delta;

		rStar = new double *[maxSenarios];
		r = new double *[maxSenarios];
		dF = new double *[maxSenarios];
		s = 0.0;
	};

	//Function
	void CalcMC(CBrownianMotion &BM, CTrinomialTree &MyTree)
	{

		for(int i = 0; i < maxSenarios; i++)
		{
			rStar[i] = new double [maxTerms];
			r[i] = new double [maxTerms];
			dF[i] = new double [maxTerms];
			rStar[i][0] = 0.0;
			r[i][0] = 0.0;
			dF[i][0] = 1;
			s = 0;
			for(int j = 1; j < maxTerms; j++)
			{
				rStar[i][j] = rStar[i][j-1]+(0-a*rStar[i][j-1])*delta + sqrt(delta)*sigma*(BM.W[i][j]-BM.W[i][j-1]);
				r[i][j] = MyTree.GetAlpha(i) + rStar[i][j];
			}


			for(int j = 0; j < maxTerms; j++){
				//S = sum(r(i,j))
				s += r[i][j];
				dF[i][j] = exp(-s*delta);
			}
			
		}		
	};

	//Destructor
	~MonteCarlo()
	{
		for (int i = 1; i < maxTerms; i++)
			{
				delete [] rStar[i];
				delete [] r[i];
				delete [] dF[i];
			}
			delete [] rStar;
			delete [] r;
			delete [] dF;
	};

private:
	int maxSenarios,maxTerms; 
	double sigma,a,delta;
	double s;
};

