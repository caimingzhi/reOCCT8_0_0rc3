#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GeomAbs_Shape.hpp>
#include <LocalAnalysis_StatusErrorType.hpp>
class Geom_Curve;
class GeomLProp_CLProps;

class LocalAnalysis_CurveContinuity
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT LocalAnalysis_CurveContinuity(const occ::handle<Geom_Curve>& Curv1,
                                                const double                   u1,
                                                const occ::handle<Geom_Curve>& Curv2,
                                                const double                   u2,
                                                const GeomAbs_Shape            Order,
                                                const double                   EpsNul  = 0.001,
                                                const double                   EpsC0   = 0.001,
                                                const double                   EpsC1   = 0.001,
                                                const double                   EpsC2   = 0.001,
                                                const double                   EpsG1   = 0.001,
                                                const double                   EpsG2   = 0.001,
                                                const double                   Percent = 0.01,
                                                const double                   Maxlen  = 10000);

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT LocalAnalysis_StatusErrorType StatusError() const;

  Standard_EXPORT GeomAbs_Shape ContinuityStatus() const;

  Standard_EXPORT double C0Value() const;

  Standard_EXPORT double C1Angle() const;

  Standard_EXPORT double C1Ratio() const;

  Standard_EXPORT double C2Angle() const;

  Standard_EXPORT double C2Ratio() const;

  Standard_EXPORT double G1Angle() const;

  Standard_EXPORT double G2Angle() const;

  Standard_EXPORT double G2CurvatureVariation() const;

  Standard_EXPORT bool IsC0() const;

  Standard_EXPORT bool IsC1() const;

  Standard_EXPORT bool IsC2() const;

  Standard_EXPORT bool IsG1() const;

  Standard_EXPORT bool IsG2() const;

private:
  Standard_EXPORT void CurvC0(GeomLProp_CLProps& Curv1, GeomLProp_CLProps& Curv2);

  Standard_EXPORT void CurvC1(GeomLProp_CLProps& Curv1, GeomLProp_CLProps& Curv2);

  Standard_EXPORT void CurvC2(GeomLProp_CLProps& Curv1, GeomLProp_CLProps& Curv2);

  Standard_EXPORT void CurvG1(GeomLProp_CLProps& Curv1, GeomLProp_CLProps& Curv2);

  Standard_EXPORT void CurvG2(GeomLProp_CLProps& Curv1, GeomLProp_CLProps& Curv2);

  double                        myContC0;
  double                        myContC1;
  double                        myContC2;
  double                        myContG1;
  double                        myContG2;
  double                        myCourbC1;
  double                        myCourbC2;
  double                        myG2Variation;
  double                        myLambda1;
  double                        myLambda2;
  GeomAbs_Shape                 myTypeCont;
  double                        myepsnul;
  double                        myepsC0;
  double                        myepsC1;
  double                        myepsC2;
  double                        myepsG1;
  double                        myepsG2;
  double                        myMaxLon;
  double                        myperce;
  bool                          myIsDone;
  LocalAnalysis_StatusErrorType myErrorStatus;
};
