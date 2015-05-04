// add delete test2.cpp : Defines the entry point for the console application.
//
#pragma once
#include <iostream>
#include "YieldCurve.h"
#include "Instrument.h"


using namespace std;
class CBond : public CInstrument
{
	private:
		double Principal,Couponrate,Coupon;
		int Maturity,Frequency,j,k;
		double *p;

	public:
		CBond(double pymtfreq = 0.0, double Principal = 0.0, double Maturity = 0.0, double Couponrate = 0.0) 
			//: CInstrument(pymtfreq, Principal, Maturity)
		{
			Coupon = Couponrate;
		}

		~CBond()
		{
		// delete [] CashFlow;
		}


	virtual double CashFlow(double r,int n,int t) 
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

		Maturity=Paramaters[n-1][4];  // assumes maturity is entered in months
		Frequency=Paramaters[n-1][7];
		Couponrate=Paramaters[n-1][3];
		Principal=Paramaters[n-1][5];
		j=Maturity;
		k=12/Frequency;
		Coupon=Couponrate*Principal/Frequency;

		//CYieldCurve yc;
		double *CashFlow;
		CashFlow= new double[j];
		for (int i=1;i<=j;i++)
		{
			CashFlow[i-1]=0; //initialize the cashflow at time i
			if (i%k==0 &&i!=0)
			{
				  if (i==j)
				  {
					CashFlow[i-1]= (Couponrate*Principal + Principal);//*yc.getDiscountFactor(i-1); // the last cashflow, cashflow= coupon +par
				  }
				  else
				  {
					CashFlow[i-1]=Couponrate*Principal;//*yc.getDiscountFactor(i-1);  //payment month, cashflow=coupon
				  }
			}
			else
				CashFlow[i-1]=0;  //non-payment-month, cashflow=0
		}
	
		/*for (int b=1;b<=j;b++)
		{
			cout<<CashFlow[b-1] << "\t";	
	    }
		cout<<CashFlow[t-1]<<endl;*/
		return CashFlow[t];
	}
};
