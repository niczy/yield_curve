// add delete test2.cpp : Defines the entry point for the console application.
//
#pragma once
#include "YieldCurve.h"

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


	void addInstrumenttoFile(double B, double C,double D,double E,double F,double G,double H)
		//B:Currency, C:Type, D:Coupon, E: Maturity, F:Principal, G:Caprate, H:Frequency
		{
		cout<<"add called"<<endl;
		cout<<"The portfolio includes the following instruments."<<endl;
		int N=100;
		int k=0;
		FILE *f = NULL; 
		double Paramaters[100][8]; 
		f=fopen("instrument.txt","r"); 
		if(f==NULL)
		{
			cout<<"Error, there is no file!"<<endl;
		} 

		cout.width(6);
		cout<<"Number";
		cout.width(10);
		cout<<"Currency";
		cout.width(10);
		cout<<"Type";
		cout.width(10);
		cout<<"Coupon";
		cout.width(10);
		cout<<"Maturity";
		cout.width(10);
		cout<<"Principal";
		cout.width(10);
		cout<<"CapRate";
		cout.width(10);
		cout<<"Frequency"<<endl;

		for (int i=0;i<N;i++)
		{
			for (int j=0;j<8;j++)
			{
				fscanf(f,"%lf",&Paramaters[i][j]);
			}
		}

		for (int i=0;i<N;i++)
		{
			if (Paramaters[i][0]<=100 && Paramaters[i][0]>=0)
				k++;
		}

		Paramaters[k][0]=k+1;
		Paramaters[k][1]=B;
		Paramaters[k][2]=C;
		Paramaters[k][3]=D;
		Paramaters[k][4]=E;
		Paramaters[k][5]=F;
		Paramaters[k][6]=G;
		Paramaters[k][7]=H;

		f=fopen("instrument.txt","wt");		//д���ļ�
		if(f==NULL)
		{
			printf("There is no file!\n");
			return;
		}
		else 
		{
			for (int i=0;i<=k;i++)
			{
				for(int j=0;j<8;j++)
				{
					if (j==0)
					{
						cout.width(6);
						cout<<Paramaters[i][j];
						fprintf(f,"%9.7f ",Paramaters[i][j]);
					}
					else
					{
						cout.width(10);
						cout<<Paramaters[i][j];
						fprintf(f,"%9.7f ",Paramaters[i][j]);
					}
				}
				fprintf(f,"%c",'\n');
				cout<<endl;
			}
		}
		cout<<endl;

		fclose(f);
	}

	void deleteInstrumentfromFile(double num)
	{
		cout<<"delete called"<<endl;
		cout<<"The portfolio includes the following instruments."<<endl;
		int N=100;
		int k=0,t;
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

		for (int i=0;i<N;i++)
		{
			if (Paramaters[i][0]<=100 && Paramaters[i][0]>=0)
				k++;
		}

		for (int i=num-1; i<k-1;i++)
		{
			for (int j=1;j<8;j++)
			{

				Paramaters[i][j]=Paramaters[i+1][j];
			}
		}

		fclose(f);
		f=fopen("instrument.txt","wt");

		cout.width(6);
		cout<<"Number";
		cout.width(10);
		cout<<"Currency";
		cout.width(10);
		cout<<"Type";
		cout.width(10);
		cout<<"Coupon";
		cout.width(10);
		cout<<"Maturity";
		cout.width(10);
		cout<<"Principal";
		cout.width(10);
		cout<<"CapRate";
		cout.width(10);
		cout<<"Frequency"<<endl;

		for (int i=0;i<k-1;i++)
		{
			for(int j=0;j<8;j++)
			{

				if (j==0)
				{
					cout.width(6);
					cout<<Paramaters[i][j];
					fprintf(f,"%9.7f ",Paramaters[i][j]);
				}
				else
				{
					cout.width(10);
					cout<<Paramaters[i][j];
					fprintf(f,"%9.7f ",Paramaters[i][j]);
				}
			}
			cout<<endl;
			fprintf(f,"%c",'\n');
		}
		fclose(f);
	}

	void readInstrument()
	{
		cout<<"read called"<<endl;

		cout<<"The portfolio includes the following instruments."<<endl;
		cout.width(6);
		cout<<"Number";
		cout.width(10);
		cout<<"Currency";
		cout.width(10);
		cout<<"Type";
		cout.width(10);
		cout<<"Coupon";
		cout.width(10);
		cout<<"Maturity";
		cout.width(10);
		cout<<"Principal";
		cout.width(10);
		cout<<"CapRate";
		cout.width(10);
		cout<<"Frequency"<<endl;

		int N=100;
		int k=0;
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

		for (int i=0;i<N;i++)
		{
			if (Paramaters[i][0]<=100 && Paramaters[i][0]>=0)
				k++;
		}

		for (int i=0;i<k;i++)
		{
			for (int j=0;j<8;j++)
			{
				if (j==0)
				{
					cout.width(6);
					cout<<Paramaters[i][j];
				}
				else
				{
					cout.width(10);
					cout<<Paramaters[i][j];
				}
			}
			cout<<endl;
		}
		cout<<endl;
		fclose(f); 
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
