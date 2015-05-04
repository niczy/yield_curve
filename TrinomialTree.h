#pragma once
#include<math.h>
#include<stdlib.h>
const int Nabc = 15;

class CTrinomialTree
{
private:
	double m_a;
	double m_SmoothDF[360];
	double m_vol;
	double dr;
	double dt;
	int j_max;
	int j_min;
	int NextNode[1000];
	double pu[Nabc][2*Nabc+1];
	double pm[Nabc][2*Nabc+1];
	double pd[Nabc][2*Nabc+1];
	double alpha[Nabc];
	double Q[Nabc+1][2*Nabc+1];

public:
	CTrinomialTree(double a, double smoothDF[], double sigma);
	~CTrinomialTree(void);
	void ConstructTree();
	double GetR_ij(int i, int j)
	{
		return alpha[i] + j*dr;
	}
	
	double GetAlpha(int i)
	{
		return alpha[i]	;	
	}

	double GetQ_ij(int i, int j)
	{
		return Q[i][j];
	}

	double OutputTree();
	int max(int n, int m)
	{
		if(n>m)
			return n;
		else
			return m;
	}

	int min(int n, int m)
	{
		if(n<m)
			return n;
		else
			return m;
	}

};

