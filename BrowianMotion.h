#pragma once
class MonteCarlo;

class CBrownianMotion
{
public:
	friend MonteCarlo;

	//Construtor
	CBrownianMotion(int o_MaxTerm, int o_NbScenarios, double o_delta)
	{
		NbScenarios = o_NbScenarios;
		MaxTerm = o_MaxTerm;
		dt = o_delta;
		W = new double* [NbScenarios];
		for (int i = 0; i < NbScenarios; i++)
		{
			W[i] = new double [MaxTerm];
			W[i][0]=0.0; 
		}
		
	};
	
	double NormalGenerator();
	void BrownianMotion();

	//Deconstructor
	~CBrownianMotion()
	{
		for (int i = 1; i < NbScenarios; i++)
		{
			delete[] W[i];
		}
		delete [] W;
	};

private:
	double **W;	
	int MaxTerm;
	int NbScenarios;
	double dt;
	double x, y, dist;
};


//Write a function to generate normal distributed random numbers w/ variance of t. t is the length of each step.
double CBrownianMotion::NormalGenerator()
{
	do
	{
		x = 2.0 * rand()*1.0/RAND_MAX - 1;	
		y = 2.0 * rand()*1.0/RAND_MAX - 1;	
		dist = x * x + y * y;
	}
	while (dist >= 1);
	return ( x * sqrt(-2.0 * log(dist) / dist));
};

void CBrownianMotion::BrownianMotion()
{		
	//Simulation
	double R = 0.0;
	for (int i = 0; i < NbScenarios; i++)
	{
		for (int j=1; j<MaxTerm; j++) 
		{
			R = NormalGenerator();
			W[i][j] = W[i][j-1] + R*sqrt(dt);
		}
	}
}
