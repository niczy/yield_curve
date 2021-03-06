﻿#pragma once

#include "Instrument.h"

class CCap : public CInstrument  //: public Instrument      //NEW Cap Class
{
private:
	double m_caprate;

public:
	CCap(double pymtfreq = 0.0, double Principal = 0.0, double Maturity = 0.0, double caprate = 0.0) 
		//: CInstrument(pymtfreq, Principal, Maturity)
	{
		m_caprate = caprate;
	}

	virtual double CashFlow(double MCRate,int n,int m) 
	{
		int N=100;
		FILE *f = NULL; 
		double Paramaters[100][8]; 
		double CF;
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
		getchar(); 
		fclose(f); 

		if (MCRate>Paramaters[n][6])
		{
			CF=(MCRate-Paramaters[n][6])*Paramaters[n][5];
		}
		else
		{
			CF=0;
		}
		return CF;
	}

};

	
