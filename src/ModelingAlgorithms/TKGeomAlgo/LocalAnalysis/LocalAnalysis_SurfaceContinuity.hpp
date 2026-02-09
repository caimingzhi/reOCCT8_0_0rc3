#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GeomAbs_Shape.hpp>
#include <LocalAnalysis_StatusErrorType.hpp>
class Geom_Surface;
class Geom2d_Curve;
class GeomLProp_SLProps;

class LocalAnalysis_SurfaceContinuity
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT LocalAnalysis_SurfaceContinuity(const occ::handle<Geom_Surface>& Surf1,
                                                  const double                     u1,
                                                  const double                     v1,
                                                  const occ::handle<Geom_Surface>& Surf2,
                                                  const double                     u2,
                                                  const double                     v2,
                                                  const GeomAbs_Shape              Order,
                                                  const double                     EpsNul  = 0.001,
                                                  const double                     EpsC0   = 0.001,
                                                  const double                     EpsC1   = 0.001,
                                                  const double                     EpsC2   = 0.001,
                                                  const double                     EpsG1   = 0.001,
                                                  const double                     Percent = 0.01,
                                                  const double                     Maxlen  = 10000);

  Standard_EXPORT LocalAnalysis_SurfaceContinuity(const occ::handle<Geom2d_Curve>& curv1,
                                                  const occ::handle<Geom2d_Curve>& curv2,
                                                  const double                     U,
                                                  const occ::handle<Geom_Surface>& Surf1,
                                                  const occ::handle<Geom_Surface>& Surf2,
                                                  const GeomAbs_Shape              Order,
                                                  const double                     EpsNul  = 0.001,
                                                  const double                     EpsC0   = 0.001,
                                                  const double                     EpsC1   = 0.001,
                                                  const double                     EpsC2   = 0.001,
                                                  const double                     EpsG1   = 0.001,
                                                  const double                     Percent = 0.01,
                                                  const double                     Maxlen  = 10000);

  Standard_EXPORT LocalAnalysis_SurfaceContinuity(const double EpsNul  = 0.001,
                                                  const double EpsC0   = 0.001,
                                                  const double EpsC1   = 0.001,
                                                  const double EpsC2   = 0.001,
                                                  const double EpsG1   = 0.001,
                                                  const double Percent = 0.01,
                                                  const double Maxlen  = 10000);

  Standard_EXPORT void ComputeAnalysis(GeomLProp_SLProps&  Surf1,
                                       GeomLProp_SLProps&  Surf2,
                                       const GeomAbs_Shape Order);

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT GeomAbs_Shape ContinuityStatus() const;

  Standard_EXPORT LocalAnalysis_StatusErrorType StatusError() const;

  Standard_EXPORT double C0Value() const;

  Standard_EXPORT double C1UAngle() const;

  Standard_EXPORT double C1URatio() const;

  Standard_EXPORT double C1VAngle() const;

  Standard_EXPORT double C1VRatio() const;

  Standard_EXPORT double C2UAngle() const;

  Standard_EXPORT double C2URatio() const;

  Standard_EXPORT double C2VAngle() const;

  Standard_EXPORT double C2VRatio() const;

  Standard_EXPORT double G1Angle() const;

  Standard_EXPORT double G2CurvatureGap() const;

  Standard_EXPORT bool IsC0() const;

  Standard_EXPORT bool IsC1() const;

  Standard_EXPORT bool IsC2() const;

  Standard_EXPORT bool IsG1() const;

  Standard_EXPORT bool IsG2() const;

private:
  Standard_EXPORT void SurfC0(const GeomLProp_SLProps& Surf1, const GeomLProp_SLProps& Surf2);

  Standard_EXPORT void SurfC1(GeomLProp_SLProps& Surf1, GeomLProp_SLProps& Surf2);

  Standard_EXPORT void SurfC2(GeomLProp_SLProps& Surf1, GeomLProp_SLProps& Surf2);

  Standard_EXPORT void SurfG1(GeomLProp_SLProps& Surf1, GeomLProp_SLProps& Surf2);

  Standard_EXPORT void SurfG2(GeomLProp_SLProps& Surf1, GeomLProp_SLProps& Surf2);

  double                        myContC0;
  double                        myContC1U;
  double                        myContC1V;
  double                        myContC2U;
  double                        myContC2V;
  double                        myContG1;
  double                        myLambda1U;
  double                        myLambda2U;
  double                        myLambda1V;
  double                        myLambda2V;
  double                        myETA1;
  double                        myETA2;
  double                        myETA;
  double                        myZETA1;
  double                        myZETA2;
  double                        myZETA;
  double                        myAlpha;
  GeomAbs_Shape                 myTypeCont;
  double                        myepsC0;
  double                        myepsnul;
  double                        myepsC1;
  double                        myepsC2;
  double                        myepsG1;
  double                        myperce;
  double                        mymaxlen;
  double                        myGap;
  bool                          myIsDone;
  LocalAnalysis_StatusErrorType myErrorStatus;
};
