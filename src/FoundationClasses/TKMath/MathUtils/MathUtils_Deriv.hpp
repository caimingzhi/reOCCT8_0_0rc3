#pragma once

#include <math_Vector.hpp>
#include <math_Matrix.hpp>
#include <MathUtils_Core.hpp>

#include <cmath>

namespace MathUtils
{

  template <typename Function>
  bool CentralDifference(Function& theFunc, double theX, double& theDeriv, double theStep = 1.0e-8)
  {
    double aFPlus  = 0.0;
    double aFMinus = 0.0;

    if (!theFunc.Value(theX + theStep, aFPlus))
    {
      return false;
    }
    if (!theFunc.Value(theX - theStep, aFMinus))
    {
      return false;
    }

    theDeriv = (aFPlus - aFMinus) / (2.0 * theStep);
    return true;
  }

  template <typename Function>
  bool ForwardDifference(Function& theFunc,
                         double    theX,
                         double    theFx,
                         double&   theDeriv,
                         double    theStep = 1.0e-8)
  {
    double aFPlus = 0.0;

    if (!theFunc.Value(theX + theStep, aFPlus))
    {
      return false;
    }

    theDeriv = (aFPlus - theFx) / theStep;
    return true;
  }

  template <typename Function>
  bool NumericalGradient(Function&    theFunc,
                         math_Vector& theX,
                         math_Vector& theGrad,
                         double       theStep = 1.0e-8)
  {
    const int aLower = theX.Lower();
    const int aUpper = theX.Upper();

    for (int i = aLower; i <= aUpper; ++i)
    {
      const double aXi     = theX(i);
      double       aFPlus  = 0.0;
      double       aFMinus = 0.0;

      theX(i) = aXi + theStep;
      if (!theFunc.Value(theX, aFPlus))
      {
        theX(i) = aXi;
        return false;
      }

      theX(i) = aXi - theStep;
      if (!theFunc.Value(theX, aFMinus))
      {
        theX(i) = aXi;
        return false;
      }

      theX(i) = aXi;

      theGrad(i) = (aFPlus - aFMinus) / (2.0 * theStep);
    }

    return true;
  }

  template <typename Function>
  bool NumericalGradientAdaptive(Function&    theFunc,
                                 math_Vector& theX,
                                 math_Vector& theGrad,
                                 double       theRelStep = 1.0e-8)
  {
    const int aLower = theX.Lower();
    const int aUpper = theX.Upper();

    for (int i = aLower; i <= aUpper; ++i)
    {
      const double aXi = theX(i);

      const double aStep = theRelStep * std::max(1.0, std::abs(aXi));

      double aFPlus  = 0.0;
      double aFMinus = 0.0;

      theX(i) = aXi + aStep;
      if (!theFunc.Value(theX, aFPlus))
      {
        theX(i) = aXi;
        return false;
      }

      theX(i) = aXi - aStep;
      if (!theFunc.Value(theX, aFMinus))
      {
        theX(i) = aXi;
        return false;
      }

      theX(i)    = aXi;
      theGrad(i) = (aFPlus - aFMinus) / (2.0 * aStep);
    }

    return true;
  }

  template <typename Function>
  bool NumericalJacobian(Function&    theFunc,
                         math_Vector& theX,
                         math_Matrix& theJac,
                         double       theStep = 1.0e-8)
  {
    const int aNbRows = theJac.RowNumber();
    const int aNbCols = theJac.ColNumber();

    math_Vector aFPlus(1, aNbRows);
    math_Vector aFMinus(1, aNbRows);

    for (int j = 1; j <= aNbCols; ++j)
    {
      const int    aIdx = theX.Lower() + j - 1;
      const double aXj  = theX(aIdx);

      theX(aIdx) = aXj + theStep;
      if (!theFunc.Value(theX, aFPlus))
      {
        theX(aIdx) = aXj;
        return false;
      }

      theX(aIdx) = aXj - theStep;
      if (!theFunc.Value(theX, aFMinus))
      {
        theX(aIdx) = aXj;
        return false;
      }

      theX(aIdx) = aXj;

      for (int i = 1; i <= aNbRows; ++i)
      {
        theJac(i, j) = (aFPlus(i) - aFMinus(i)) / (2.0 * theStep);
      }
    }

    return true;
  }

  template <typename Function>
  bool NumericalHessian(Function&    theFunc,
                        math_Vector& theX,
                        math_Matrix& theHess,
                        double       theStep = 1.0e-5)
  {
    const int aLower = theX.Lower();
    const int aUpper = theX.Upper();

    double aFx = 0.0;
    if (!theFunc.Value(theX, aFx))
    {
      return false;
    }

    for (int i = aLower; i <= aUpper; ++i)
    {
      const double aXi     = theX(i);
      double       aFPlus  = 0.0;
      double       aFMinus = 0.0;

      theX(i) = aXi + theStep;
      if (!theFunc.Value(theX, aFPlus))
      {
        theX(i) = aXi;
        return false;
      }

      theX(i) = aXi - theStep;
      if (!theFunc.Value(theX, aFMinus))
      {
        theX(i) = aXi;
        return false;
      }

      theX(i) = aXi;

      const int aMatIdx         = i - aLower + 1;
      theHess(aMatIdx, aMatIdx) = (aFPlus - 2.0 * aFx + aFMinus) / (theStep * theStep);
    }

    for (int i = aLower; i <= aUpper; ++i)
    {
      for (int j = i + 1; j <= aUpper; ++j)
      {
        const double aXi  = theX(i);
        const double aXj  = theX(j);
        double       aFpp = 0.0, aFpm = 0.0, aFmp = 0.0, aFmm = 0.0;

        theX(i) = aXi + theStep;
        theX(j) = aXj + theStep;
        if (!theFunc.Value(theX, aFpp))
        {
          theX(i) = aXi;
          theX(j) = aXj;
          return false;
        }

        theX(j) = aXj - theStep;
        if (!theFunc.Value(theX, aFpm))
        {
          theX(i) = aXi;
          theX(j) = aXj;
          return false;
        }

        theX(i) = aXi - theStep;
        if (!theFunc.Value(theX, aFmm))
        {
          theX(i) = aXi;
          theX(j) = aXj;
          return false;
        }

        theX(j) = aXj + theStep;
        if (!theFunc.Value(theX, aFmp))
        {
          theX(i) = aXi;
          theX(j) = aXj;
          return false;
        }

        theX(i) = aXi;
        theX(j) = aXj;

        const int    aMatI = i - aLower + 1;
        const int    aMatJ = j - aLower + 1;
        const double aHij  = (aFpp - aFpm - aFmp + aFmm) / (4.0 * theStep * theStep);

        theHess(aMatI, aMatJ) = aHij;
        theHess(aMatJ, aMatI) = aHij;
      }
    }

    return true;
  }

  template <typename Function>
  bool SecondDerivative(Function& theFunc,
                        double    theX,
                        double    theFx,
                        double&   theD2f,
                        double    theStep = 1.0e-5)
  {
    double aFPlus  = 0.0;
    double aFMinus = 0.0;

    if (!theFunc.Value(theX + theStep, aFPlus))
    {
      return false;
    }
    if (!theFunc.Value(theX - theStep, aFMinus))
    {
      return false;
    }

    theD2f = (aFPlus - 2.0 * theFx + aFMinus) / (theStep * theStep);
    return true;
  }

} // namespace MathUtils
