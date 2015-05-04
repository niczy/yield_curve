#include "TrinomialTree.h"
#include<math.h>
#include <iostream> 
using namespace std;

CTrinomialTree::CTrinomialTree(double a, double smoothDF[], double sigma)
{
	dt = 0.08333333333;
	m_a = a;
	for(int i = 0; i < 360; i++)
	{
		m_SmoothDF[i] = smoothDF[i];
	}
	m_vol = sigma;
	dr = m_vol * sqrt(3*dt);
	j_max = (int)(0.184/(m_a*dt));
	j_min = -j_max;
}


CTrinomialTree::~CTrinomialTree(void)
{
}

void CTrinomialTree::ConstructTree()
{
	for (int i = 0; i <= Nabc; i++)
	{
		for(int j = 0; j <= 2*Nabc; j++)
		{
			Q[i][j] = 0;
			pu[i][j] = 0;
			pd[i][j] = 0;
			pm[i][j] = 0;
		}
	}

	//first stage
	NextNode[Nabc+j_min-1] = Nabc + j_min;
	NextNode[Nabc+j_max+1] = Nabc + j_max;
	for(int j = j_min; j <= j_max; j++)
	{
		NextNode[j+Nabc] = j+Nabc;
	}

	for(int i = 0; i < Nabc; i++)
	{
		for(int j = i+Nabc; j >= Nabc-i; j--)
		{
			if(j == 2*(j_max+1))
			{
				pu[i][j] = 1.16666667 + (pow(m_a*(j_max+1)*dt, 2) - 3*m_a*(j_max+1)*dt)*0.5;
				pm[i][j] = -0.33333333 - pow(m_a*(j_max+1)*dt, 2) + 2*m_a*(j_max+1)*dt;
			}
			else if(j == 0)
			{
				pu[i][j] = 0.16666667 + (pow(m_a*(j_min-1)*dt, 2) + m_a*(j_min-1)*dt)*0.5;
				pm[i][j] = -0.33333333 - pow(m_a*(j_min-1)*dt, 2) - 2*m_a*(j_min-1)*dt;
			}
			else
			{
				pu[i][j] = 0.16666667 + (pow(m_a*(j-j_max-1)*dt, 2) - m_a*(j-j_max-1)*dt)*0.5;
				pm[i][j] = 0.66666667 - pow(m_a*(j-j_max-1)*dt, 2);
			}
			pd[i][j] = 1 - pu[i][j] - pm[i][j];
		}
	
	}

	//second stage
	Q[0][Nabc] = 1;
	double sum;
	for(int i = 0; i < Nabc; i++)
	{
		sum = 0;
		for(int j = 0; j <= 2*Nabc; j++)
		{
			sum = sum + Q[i][j]*exp(-(j-Nabc)*dr*dt);
		}
		alpha[i] = (log(sum) - log(m_SmoothDF[i+1]))/dt;

		for(int k = max(-i+Nabc, Nabc+j_min-1); k <= min(Nabc+i, Nabc+j_max+1); k++)
		{
			Q[i+1][NextNode[k]+1] = Q[i+1][(NextNode[k]+1)] + Q[i][k]*pu[i][k]*exp(-(alpha[i]+(k-Nabc)*dr)*dt);
			Q[i+1][NextNode[k]] = Q[i+1][NextNode[k]] + Q[i][k]*pm[i][k]*exp(-(alpha[i]+(k-Nabc)*dr)*dt);
			Q[i+1][(NextNode[k]-1)] = Q[i+1][(NextNode[k]-1)] + Q[i][k]*pd[i][k]*exp(-(alpha[i]+(k-Nabc)*dr)*dt);
		}
	}
	return;
}


/*void CTrinomialTree::ValidateTree()
{
	cout << "Verification: " <<endl;
	for(int m = 1; m < Nabc+1; m++)
	{
		double V[Nabc+1][2*Nabc+1];

		for(int j = 0; j <=Nabc;j++)
			V[m][j] = 1;

		for(int i = m-1; i >=0; i--)
		{
			for(int j = max(-i+Nabc, Nabc+j_min-1); j <= min(Nabc+i, Nabc+j_max+1); j++)
			//for(int j = max(-i, j_min-1); j <= min(i, j_max+1); j++)
			{
				V[i][j] = pu[i][j] * V[i+1][NextNode[j]+1] * exp(-(alpha[i]+(j+Nabc)*dr)*dt) 
					+ pm[i][j] * V[i+1][NextNode[j]] * exp(-(alpha[i]+(j+Nabc)*dr)*dt)
					+ pd[i][j] * V[i+1][NextNode[j]-1] * exp(-(alpha[i]+(j+Nabc)*dr)*dt);
			}
		}
		cout << m << ": " << V[0][0] <<endl;
	}
}*/


	