#pragma once

#include <math_FunctionWithDerivative.hpp>

class math_TrigonometricEquationFunction : public math_FunctionWithDerivative
{
  double myAA;
  double myBB;
  double myCC;
  double myDD;
  double myEE;

public:
  math_TrigonometricEquationFunction(const double A,
                                     const double B,
                                     const double C,
                                     const double D,
                                     const double E)
      : myAA(A),
        myBB(B),
        myCC(C),
        myDD(D),
        myEE(E)
  {
  }

  bool Value(const double X, double& F) override
  {
    double CN = cos(X), SN = sin(X);

    F = CN * (myAA * CN + (myBB + myBB) * SN + myCC) + myDD * SN + myEE;
    return true;
  }

  bool Derivative(const double X, double& D) override
  {
    double CN = std::cos(X), SN = std::sin(X);

    D = -myAA * CN * SN + myBB * (CN * CN - SN * SN);
    D += D;
    D += -myCC * SN + myDD * CN;
    return true;
  }

  bool Values(const double X, double& F, double& D) override
  {
    double CN = std::cos(X), SN = std::sin(X);

    double AACN = myAA * CN;
    double BBSN = myBB * SN;

    F = AACN * CN + BBSN * (CN + CN) + myCC * CN + myDD * SN + myEE;
    D = -AACN * SN + myBB * (CN * CN - SN * SN);
    D += D;
    D += -myCC * SN + myDD * CN;
    return true;
  }
};
