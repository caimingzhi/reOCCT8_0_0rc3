#pragma once

#include <gp_Pnt.hpp>
#include <NCollection_Sequence.hpp>
#include <math_Function.hpp>
#include <math_MultipleVarFunction.hpp>
#include <Adaptor3d_Curve.hpp>
#include <Adaptor2d_Curve2d.hpp>

class GCPnts_TangentialDeflection
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GCPnts_TangentialDeflection();

  Standard_EXPORT GCPnts_TangentialDeflection(const Adaptor3d_Curve& theC,
                                              const double           theAngularDeflection,
                                              const double           theCurvatureDeflection,
                                              const int              theMinimumOfPoints = 2,
                                              const double           theUTol            = 1.0e-9,
                                              const double           theMinLen          = 1.0e-7);

  Standard_EXPORT GCPnts_TangentialDeflection(const Adaptor3d_Curve& theC,
                                              const double           theFirstParameter,
                                              const double           theLastParameter,
                                              const double           theAngularDeflection,
                                              const double           theCurvatureDeflection,
                                              const int              theMinimumOfPoints = 2,
                                              const double           theUTol            = 1.0e-9,
                                              const double           theMinLen          = 1.0e-7);

  Standard_EXPORT GCPnts_TangentialDeflection(const Adaptor2d_Curve2d& theC,
                                              const double             theAngularDeflection,
                                              const double             theCurvatureDeflection,
                                              const int                theMinimumOfPoints = 2,
                                              const double             theUTol            = 1.0e-9,
                                              const double             theMinLen          = 1.0e-7);

  Standard_EXPORT GCPnts_TangentialDeflection(const Adaptor2d_Curve2d& theC,
                                              const double             theFirstParameter,
                                              const double             theLastParameter,
                                              const double             theAngularDeflection,
                                              const double             theCurvatureDeflection,
                                              const int                theMinimumOfPoints = 2,
                                              const double             theUTol            = 1.0e-9,
                                              const double             theMinLen          = 1.0e-7);

  Standard_EXPORT void Initialize(const Adaptor3d_Curve& theC,
                                  const double           theAngularDeflection,
                                  const double           theCurvatureDeflection,
                                  const int              theMinimumOfPoints = 2,
                                  const double           theUTol            = 1.0e-9,
                                  const double           theMinLen          = 1.0e-7);

  Standard_EXPORT void Initialize(const Adaptor3d_Curve& theC,
                                  const double           theFirstParameter,
                                  const double           theLastParameter,
                                  const double           theAngularDeflection,
                                  const double           theCurvatureDeflection,
                                  const int              theMinimumOfPoints = 2,
                                  const double           theUTol            = 1.0e-9,
                                  const double           theMinLen          = 1.0e-7);

  Standard_EXPORT void Initialize(const Adaptor2d_Curve2d& theC,
                                  const double             theAngularDeflection,
                                  const double             theCurvatureDeflection,
                                  const int                theMinimumOfPoints = 2,
                                  const double             theUTol            = 1.0e-9,
                                  const double             theMinLen          = 1.0e-7);

  Standard_EXPORT void Initialize(const Adaptor2d_Curve2d& theC,
                                  const double             theFirstParameter,
                                  const double             theLastParameter,
                                  const double             theAngularDeflection,
                                  const double             theCurvatureDeflection,
                                  const int                theMinimumOfPoints = 2,
                                  const double             theUTol            = 1.0e-9,
                                  const double             theMinLen          = 1.0e-7);

  Standard_EXPORT int AddPoint(const gp_Pnt& thePnt,
                               const double  theParam,
                               const bool    theIsReplace = true);

  int NbPoints() const { return myParameters.Length(); }

  double Parameter(const int I) const { return myParameters.Value(I); }

  gp_Pnt Value(const int I) const { return myPoints.Value(I); }

  Standard_EXPORT static double ArcAngularStep(const double theRadius,
                                               const double theLinearDeflection,
                                               const double theAngularDeflection,
                                               const double theMinLength);

private:
  template <class TheCurve>
  void initialize(const TheCurve& theC,
                  const double    theFirstParameter,
                  const double    theLastParameter,
                  const double    theAngularDeflection,
                  const double    theCurvatureDeflection,
                  const int       theMinimumOfPoints,
                  const double    theUTol,
                  const double    theMinLen);

  template <class TheCurve>
  void PerformLinear(const TheCurve& theC);

  template <class TheCurve>
  void PerformCircular(const TheCurve& theC);

  template <class TheCurve>
  void PerformCurve(const TheCurve& theC);

  template <class TheCurve>
  void EvaluateDu(const TheCurve& theC,
                  const double    theU,
                  gp_Pnt&         theP,
                  double&         theDu,
                  bool&           theNotDone) const;

  template <class TheCurve>
  void EstimDefl(const TheCurve& theC,
                 const double    theU1,
                 const double    theU2,
                 double&         theMaxDefl,
                 double&         theUMax);

private:
  double                       myAngularDeflection;
  double                       myCurvatureDeflection;
  double                       myUTol;
  int                          myMinNbPnts;
  double                       myMinLen;
  double                       myLastU;
  double                       myFirstu;
  NCollection_Sequence<gp_Pnt> myPoints;
  NCollection_Sequence<double> myParameters;
};
