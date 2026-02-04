#pragma once


#include <Standard.hpp>
#include <Standard_Real.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_OutOfRange.hpp>

#include <cmath>

//! Template class for locating the closest point on a curve to a given point.
//! Among a set of sampled points on the curve, finds the one closest to the target.
//!
//! @tparam TheCurve the curve type
//! @tparam TheCurveTool the curve tool providing curve operations
//! @tparam ThePOnC the point-on-curve type
//! @tparam ThePoint the point type (gp_Pnt or gp_Pnt2d)
template <typename TheCurve, typename TheCurveTool, typename ThePOnC, typename ThePoint>
class Extrema_GCurveLocator
{
public:
  DEFINE_STANDARD_ALLOC

  //! Among a set of points {C(ui), i=1,NbU}, locate the point
  //! P=C(uj) such that:
  //! distance(P,C) = Min{distance(P,C(ui))}
  //! @param theP the target point
  //! @param theC the curve to sample
  //! @param theNbU the number of sample points
  //! @param thePapp the result point on curve
  static void Locate(const ThePoint& theP, const TheCurve& theC, const int theNbU, ThePOnC& thePapp)
  {
    if (theNbU < 2)
    {
      throw Standard_OutOfRange();
    }

    double   aU        = TheCurveTool::FirstParameter(theC);
    double   aPasU     = (TheCurveTool::LastParameter(theC) - aU) / (theNbU - 1);
    double   aDist2Min = RealLast();
    double   aUMin     = 0;
    ThePoint aPntMin;
    double   aDist2;
    ThePoint aPt;

    for (int aNoSample = 1; aNoSample < theNbU; aNoSample++, aU += aPasU)
    {
      aPt    = TheCurveTool::Value(theC, aU);
      aDist2 = aPt.SquareDistance(theP);
      if (aDist2 < aDist2Min)
      {
        aDist2Min = aDist2;
        aUMin     = aU;
        aPntMin   = aPt;
      }
    }
    thePapp.SetValues(aUMin, aPntMin);
  }

  //! Among a set of points {C(ui), i=1,NbU}, locate the point
  //! P=C(uj) such that:
  //! distance(P,C) = Min{distance(P,C(ui))}
  //! The search is done between theUmin and theUsup.
  //! @param theP the target point
  //! @param theC the curve to sample
  //! @param theNbU the number of sample points
  //! @param theUmin the minimum parameter value
  //! @param theUsup the maximum parameter value
  //! @param thePapp the result point on curve
  static void Locate(const ThePoint& theP,
                     const TheCurve& theC,
                     const int       theNbU,
                     const double    theUmin,
                     const double    theUsup,
                     ThePOnC&        thePapp)
  {
    if (theNbU < 2)
    {
      throw Standard_OutOfRange();
    }

    double aUinf  = TheCurveTool::FirstParameter(theC);
    double aUlast = TheCurveTool::LastParameter(theC);

    double aU1  = std::min(aUinf, aUlast);
    double aU2  = std::max(aUinf, aUlast);
    double aU11 = std::min(theUmin, theUsup);
    double aU12 = std::max(theUmin, theUsup);

    if (aU11 < aU1 - RealEpsilon())
      aU11 = aU1;
    if (aU12 > aU2 + RealEpsilon())
      aU12 = aU2;

    double   aU        = aU11;
    double   aPasU     = (aU12 - aU) / (theNbU - 1);
    double   aDist2Min = RealLast();
    double   aUMin     = 0;
    ThePoint aPntMin;
    double   aDist2;
    ThePoint aPt;

    for (int aNoSample = 1; aNoSample < theNbU; aNoSample++, aU += aPasU)
    {
      aPt    = TheCurveTool::Value(theC, aU);
      aDist2 = aPt.SquareDistance(theP);
      if (aDist2 < aDist2Min)
      {
        aDist2Min = aDist2;
        aUMin     = aU;
        aPntMin   = aPt;
      }
    }
    thePapp.SetValues(aUMin, aPntMin);
  }
};

