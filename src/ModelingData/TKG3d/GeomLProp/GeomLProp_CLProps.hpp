#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Real.hpp>
#include <Standard_Integer.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <gp_Dir.hpp>
#include <LProp_Status.hpp>
#include <Standard_Boolean.hpp>
class Geom_Curve;
class LProp_BadContinuity;
class Standard_DomainError;
class Standard_OutOfRange;
class LProp_NotDefined;
class gp_Vec;
class gp_Pnt;
class gp_Dir;
class GeomLProp_CurveTool;

class GeomLProp_CLProps
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomLProp_CLProps(const occ::handle<Geom_Curve>& C,
                                    const int                      N,
                                    const double                   Resolution);

  Standard_EXPORT GeomLProp_CLProps(const occ::handle<Geom_Curve>& C,
                                    const double                   U,
                                    const int                      N,
                                    const double                   Resolution);

  Standard_EXPORT GeomLProp_CLProps(const int N, const double Resolution);

  Standard_EXPORT void SetParameter(const double U);

  Standard_EXPORT void SetCurve(const occ::handle<Geom_Curve>& C);

  Standard_EXPORT const gp_Pnt& Value() const;

  Standard_EXPORT const gp_Vec& D1();

  Standard_EXPORT const gp_Vec& D2();

  Standard_EXPORT const gp_Vec& D3();

  Standard_EXPORT bool IsTangentDefined();

  Standard_EXPORT void Tangent(gp_Dir& D);

  Standard_EXPORT double Curvature();

  Standard_EXPORT void Normal(gp_Dir& N);

  Standard_EXPORT void CentreOfCurvature(gp_Pnt& P);

private:
  occ::handle<Geom_Curve> myCurve;
  double                  myU;
  int                     myDerOrder;
  double                  myCN;
  double                  myLinTol;
  gp_Pnt                  myPnt;
  gp_Vec                  myDerivArr[3];
  gp_Dir                  myTangent;
  double                  myCurvature;
  LProp_Status            myTangentStatus;
  int                     mySignificantFirstDerivativeOrder;
};
