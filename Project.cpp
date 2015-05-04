#include <iostream>
#include <algorithm>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <string>
#include <vector>

using namespace std;

#include "DomPric.h"
#include "spline.h"
#include "BrowianMotion.h"
#include "MonteCarlo.h"
#include "YieldCurve.h"
#include "TrinomialTree.h"
#include "Instrument.h"
#include "Cap.h"
#include "Bond.h"

int CDomesticPricing::ObjectCountUS(0);
int getType(int n);
double getMaturity(int n);

int main()
{
	int indicatorAddOrDelete(1);
	int indicatorType(1);
	char indicatorYN('Y');
	double principal(0);
	int currency(0);
	int type(0);
	double maturity(0);
	double coupon(0);
	double caprate(0);
	int pymtfreq(0);
	int NbObject(0);
	int NbDelete(0);
	CBond MyBond;
	CCap MyCap;

	CDomesticPricing DomesticPricing_US(0);
	CBrownianMotion BM(DomesticPricing_US.m_maxTerm, DomesticPricing_US.m_NbScenarios, DomesticPricing_US.m_dt);								//fixed values
	BM.BrownianMotion();

	int TOTAL_TIME = 11;
    string MATU[] = {"1 Mo", "3 Mo", "6 Mo", "1 Yr", "2 Yr", "3 Yr", "5 Yr", "7 Yr", "10 Yr", "20 Yr", "30 Yr"};
    int month[] = {1, 3, 6, 12, 24, 36, 60, 84, 120, 240, 360};
    vector<vector<double> > X(TOTAL_TIME), Y(TOTAL_TIME);
    string market;
   	string inputFileName = "USTREASURY-YIELD.csv";
    
    // Read data
    ifstream infile(inputFileName);
    string line;
    getline(infile, line);
    
    int count = 0;
    while (getline(infile, line)) {
        count--;
        int commaIdx = line.find(",");
        line = line.substr(commaIdx+1);
        try {
            for (int i = 0; i < TOTAL_TIME; i++) {
                double value = stod(line);
                X[i].push_back(count);
                Y[i].push_back(value);
                line = line.substr(line.find(",") + 1);
            }
        } catch (...) {
        }
    }
    for (int i = 0; i < TOTAL_TIME; i++) {
        reverse(X[i].begin(), X[i].end());
        reverse(Y[i].begin(), Y[i].end());
    }
    infile.close();


    int TOTAL_TIMEL = 5;
    string MATUL[] = {"1 Mo", "2 Mo", "3 Mo", "6 Mo", "12 Mo"};
    int monthL[] = {1, 2, 3, 6, 12};
    vector<vector<double> > XL(TOTAL_TIME), YL(TOTAL_TIME);
    string marketL;
    string inputFileNameL = "LIBOR.csv";
    
    // Read data
    ifstream infileL(inputFileNameL);
    string lineL;
    getline(infileL, lineL);
    
    int countL = 0;
    while (getline(infileL, lineL)) {
        countL--;
        int commaIdxL = lineL.find(",");
        lineL = lineL.substr(commaIdxL+1);
        try {
            for (int i = 0; i < TOTAL_TIMEL; i++) {
                double valueL = stod(lineL);
                XL[i].push_back(countL);
                YL[i].push_back(valueL);
                lineL = lineL.substr(lineL.find(",") + 1);
            }
        } catch (...) {
        }
    }
    for (int i = 0; i < TOTAL_TIMEL; i++) {
        reverse(XL[i].begin(), XL[i].end());
        reverse(YL[i].begin(), YL[i].end());
    }
    infileL.close();
    /*for (int i = 0 ; i < TOTAL_TIME; i++) {
        CYieldCurve *curve = new CYieldCurve(X[i], Y[i]);
        cout << "Yield for "  << MATU[i] << " at today is " << curve->getSmootedYield(0) <<
        " discount factor is " << curve->getDiscountFactor(month[i]) << endl; //output of discountfactor
    }*/

    // Caculate historical volatility.
    double sum = 0.0;
    for (int i = 0; i < Y[0].size(); i++) {
        sum += Y[0][i];
    }
    double avg = sum / Y[0].size();
    double s = 0.0;
    for (int i = 0; i < Y[0].size(); i++) {
        s += pow(Y[0][i] - avg, 2);
    }
    s /= Y[0].size() - 1;
    s = s * 4.6904158/100; //s is monthly volatility

	//Use Constrcutor
	MonteCarlo mc(DomesticPricing_US.m_NbScenarios,DomesticPricing_US.m_maxTerm, s ,0.2,DomesticPricing_US.m_dt); //alfa comes from the tree
	double df[360];
	for(int i = 0; i<360; i++)
	{
		df[i] = 1 - i*0.002;
	}

	CTrinomialTree MyTree(0.2,df,s);
	MyTree.ConstructTree();

	//Get 2-D dynamic Monte Carlo array
	mc.CalcMC(BM,MyTree);

	/*//Display result														//take that out later
	for (int i = 0; i < DomesticPricing_US.m_NbScenarios; i++)
	{
		for(int j= 0; j < DomesticPricing_US.m_maxTerm; j++)
		{
			cout << i << j << ". " << mc.r[i][j] << endl;
			cout << i << j << ". " << mc.dF[i][j] << endl;
		}
	}
	*/
	// Display initial portfolio and then ask for input!
	MyCap.readInstrument();
	cout << endl;

for(;;)
{
	cout << "Is the portfolio complete? (Y/N) ";
	cin >> indicatorYN;

	if(('Y' ==  indicatorYN) || ( 'y' == indicatorYN))
	{
	break;
	}
	else 
	{
	}

	cout << "Do you want to add an instrument (1) or delete an instrument (2) from the file? ";
	cin >> indicatorAddOrDelete;

	switch(indicatorAddOrDelete)
	{
		case 1: cout << "What type of instrument do you want to add to the Portfolio? A Bond (1) or a Cap (2)?\n ";
				  cin >> indicatorType;

				  switch(indicatorType)
				  {
				  case 1:   for(;;)
							{ 
								cout << "Please enter the the currency of the bond (0 for United States):\n ";
								cin >> currency;
								if(currency == 0)
									break;
								else
									cout << "Please enter only 0 for United States! ";
									continue;
							}
							
							type = 0;

							for(;;)
							{ 
								cout << "Please enter the principal of the bond:\n ";
								cin >> principal;
								if(principal <= 0)
									{cout << "Please enter a positive value for the principal. ";
									continue;}
								else
									break;
							}

							for(;;)
							{ 
								cout << "Please enter the maturity of the bond in months with a maximum maturity of 30 years:\n ";
								cin >> maturity;

								if (maturity > 360)
								{	cout << "The maximum maturity is 30 years. Please enter a matury of less than 360 months! ";
									continue;}
								else if(maturity <= 0)
									{cout << "The maturity must be positive! ";
									continue;}
								else
									break;
							}

							for(;;)
							{ 
							cout << "Please enter the coupon of the bond:\n ";
							cin >> coupon;

							if(coupon < 0)
							{cout << "Please enter a positive coupon! ";
							continue;}
							else
								break;
							}
							
							for(;;)
							{ 
							cout << "Please enter the payment frequency of the bond as times per year (1, 2, 3, 4, 6, 12):\n ";
							cin >> pymtfreq;

							if((12%pymtfreq) != 0)
							{ cout << "Please enter either 1, 2, 3, 4, 6 or 12 as payment frequency per year! ";
							continue;}
							else break;
							}

							MyBond.addInstrumenttoFile(currency, type,coupon, maturity, principal, 0, pymtfreq);
							break;

				  case 2: for(;;)
							{ 
								cout << "Please enter the the currency of the cap (0 for United States):\n ";
								cin >> currency;
								if(currency == 0)
									break;
								else
									cout << "Please enter only 0 for United States! ";
									continue;
							}
							type = 1;

														for(;;)
							{ 
								cout << "Please enter the principal of the cap:\n ";
								cin >> principal;
								if(principal <= 0)
									{cout << "Please enter a positive value for the principal. ";
									continue;}
								else
									break;
							}


							for(;;)
							{ 
							cout << "Please enter the caprate of the cap:\n ";
							cin >> caprate;

							if(coupon < 0)
							{cout << "Please enter a positive caprate! ";
							continue;}
							else
								break;
							}

							for(;;)
							{ 
								cout << "Please enter the maturity of the cap in months with a maximum maturity of 30 years:\n ";
								cin >> maturity;

								if (maturity > 360)
								{	cout << "The maximum maturity is 30 years. Please enter a matury of less than 360 months! ";
									continue;}
								else if(maturity <= 0)
									{cout << "The maturity must be positive! ";
									continue;}
								else
									break;
							}

							for(;;)
							{ 
							cout << "Please enter the payment frequency of the cap as times per year (1, 2, 3, 4, 6, 12):\n ";
							cin >> pymtfreq;

							if((12%pymtfreq) != 0)
							{ cout << "Please enter either 1, 2, 3, 4, 6 or 12 as payment frequency per year! ";
							continue;}
							else break;
							}

							MyCap.addInstrumenttoFile(currency, type,0, maturity, principal, caprate, pymtfreq);
							break;

				  default: cout << "Please enter either B for Bond or C for Cap. " << endl;
							
				  }
				  break;

		case 2: cout << "What object do you want to delete? Please enter number of object. ";
				  cin >> NbDelete;

				  MyCap.deleteInstrumentfromFile(NbDelete);
				  break;

		default: cout << "Please enter either A to insert an instrument or B to delete an instrument. ";
	
	}
}
	cout << "Which object do you wanna price? Please enter a number: " << endl;
	cin >> NbObject;
	type = getType(NbObject-1);

	maturity = getMaturity(NbObject-1);

	if(type == 1) 
	{
		cout << "The price of instrument Nr. " << NbObject << " using Monte Carlo simulation is: " << MyCap.PriceMC(NbObject, DomesticPricing_US.m_NbScenarios, maturity,mc,type) << endl;
		//cout << "The price of instrument Nr. " << NbObject << " using Trinomial Trees is: " << MyCap.PriceTree(NbObject) << endl;
	}
	else if(type == 0)
	{
		cout << "The price of instrument Nr. " << NbObject << " using Monte Carlo simulation is: " << MyBond.PriceMC(NbObject, DomesticPricing_US.m_NbScenarios, maturity,mc,type) << endl;
		//cout << "The price of instrument Nr. " << NbObject << " using Trinomial Trees is: " << MyCap.PriceTree(NbObject) << endl;
	}

	system("pause");
	return 0;
}


int getType(int n)
{
		int N=100;
		FILE *f = NULL; 
		double Paramaters[100][8]; 
		f=fopen("instrument.txt","r"); 
		if(f==NULL)
		{
			cout<<"Error, there is no file!"<<endl;
		} 

		for (int i=0;i<N;i++)
		{
			for (int j=0;j<8;j++)
			{
				fscanf(f,"%lf",&Paramaters[i][j]);
			}
		}

		fclose(f); 
		return Paramaters[n][2];
}

double getMaturity(int n)
{
		int N=100;
		FILE *f = NULL; 
		double Paramaters[100][8]; 
		f=fopen("instrument.txt","r"); 
		if(f==NULL)
		{
			cout<<"Error, there is no file!"<<endl;
		} 

		for (int i=0;i<N;i++)
		{
			for (int j=0;j<8;j++)
			{
				fscanf(f,"%lf",&Paramaters[i][j]);
			}
		}

		fclose(f); 
		return Paramaters[n][4];
}
