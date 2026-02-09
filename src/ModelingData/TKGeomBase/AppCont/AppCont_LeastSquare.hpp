#pragma once

#include <AppCont_Function.hpp>
#include <AppParCurves_MultiCurve.hpp>
#include <math_Matrix.hpp>
#include <NCollection_Array1.hpp>
#include <AppParCurves_Constraint.hpp>
#include <math_Vector.hpp>

struct PeriodicityInfo
{
  bool   isPeriodic;
  double myPeriod;
};

class AppCont_LeastSquare
{
public:
  Standard_EXPORT AppCont_LeastSquare(const AppCont_Function&       SSP,
                                      const double                  U0,
                                      const double                  U1,
                                      const AppParCurves_Constraint FirstCons,
                                      const AppParCurves_Constraint LastCons,
                                      const int                     Deg,
                                      const int                     NbPoints);

  Standard_EXPORT const AppParCurves_MultiCurve& Value();

  Standard_EXPORT void Error(double& F, double& MaxE3d, double& MaxE2d) const;

  Standard_EXPORT bool IsDone() const;

private:
  void FixSingleBorderPoint(const AppCont_Function&       theSSP,
                            const double                  theU,
                            const double                  theU0,
                            const double                  theU1,
                            NCollection_Array1<gp_Pnt2d>& theFix2d,
                            NCollection_Array1<gp_Pnt>&   theFix);

  AppParCurves_MultiCurve             mySCU;
  math_Matrix                         myPoints;
  math_Matrix                         myPoles;
  math_Vector                         myParam;
  math_Matrix                         myVB;
  NCollection_Array1<PeriodicityInfo> myPerInfo;
  bool                                myDone;
  int                                 myDegre;
  int                                 myNbdiscret, myNbP, myNbP2d;
};
