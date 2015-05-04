#pragma once
#include "instrument.h"

class CTedSpread :public CInstrument  //: public Instrument      //NEW Cap Class
{
private:

public:
	double TEDspread(int term, double t   )
	{
		/*double Vt = 0;
		double libort = libor();
		double treasuryt = treasury(t);
		double Dt = GetDiscountFactor();
		If (libort > treasury)
		{
			Vt = Dt*(libort - treasuryt)
		}
		Else {Vt = 0}
		Return Vt;*/

		V = YL[i][j]-Y[i][j];
		if(V<0){V = 0;}
	}
};

