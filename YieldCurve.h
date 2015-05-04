#pragma once
// member function
#include "math.h"
#include "spline.h"

using namespace std;
class CYieldCurve {
private:
    tk::spline s;
    vector<double> X;
    vector<double> Y;
    
public:
    CYieldCurve(std::vector<double> _X, std::vector<double> _Y) {
        s.set_points(_X,Y); // currently it is required that X is already sorted
        X = _X;
        Y = _Y;
    }
    
    double getSmootedYield(int date) {
        return s(date);
    }
    
    double getDiscountFactor(int month) {
        return exp(-getSmootedYield(0) * month / 12 / 100);
    }
    
    double getSpeedOfMeanReversion() {
        return 0.2;
    }

    vector<double> getX() {
      return X;
    }

    vector<double> getY() {
      return Y;
    }
};

