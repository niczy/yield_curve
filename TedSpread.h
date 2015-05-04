#pragma once
#include "instrument.h"
#include "YieldCurve.h"

class CTedSpread: public CInstrument {
private:
      CYieldCurve* liborYieldCurves;
      CYieldCurve* treasuryYieldCurves;

public:
  CTedSpread(CYieldCurve* _liborYieldCurves, CYieldCurve* _treasuryYieldCurves);
  ~CTedSpread();
  double TEDspread(int term, int t);
};

