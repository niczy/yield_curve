#include "TedSpread.h"

CTedSpread::CTedSpread(CYieldCurve* _liborYieldCurves, CYieldCurve* _treasuryYieldCurves){
    // Pass in a array of CYieldCurve.
    liborYieldCurves = _liborYieldCurves;
    treasuryYieldCurves = _treasuryYieldCurves;
}

CTedSpread::~CTedSpread() {}

// term:
// 0 : 1Month
// 1: 3 Month.
// 2: 6 Month
// Should be the index of corresponding months defined in month[]
//    int month[] = {1, 3, 6, 12, 24, 36, 60, 84, 120, 240, 360};
// t should be int. O means today, 1 means tomorrow. t means t days after.
double CTedSpread::TEDspread(int term, int t){
  double libort = liborYieldCurves[term].getSmootedYield(t);
  double treasuryt = treasuryYieldCurves[term].getSmootedYield(t); 
  if (libort > treasuryt) {
    return (libort - treasuryt) * treasuryYieldCurves[term].getDiscountFactor(t);
  } else {
    return 0;
  }
}
