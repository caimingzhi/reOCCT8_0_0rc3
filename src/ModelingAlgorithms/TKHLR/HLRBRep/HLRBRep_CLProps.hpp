#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Standard_Integer.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Vec2d.hpp>
#include <gp_Dir2d.hpp>
#include <LProp_Status.hpp>
class LProp_BadContinuity;
class Standard_DomainError;
class Standard_OutOfRange;
class LProp_NotDefined;
class gp_Vec2d;
class gp_Pnt2d;
class gp_Dir2d;
class HLRBRep_CLPropsATool;
class HLRBRep_Curve;

class HLRBRep_CLProps
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT HLRBRep_CLProps(const HLRBRep_Curve*& C, const int N, const double Resolution);

  Standard_EXPORT HLRBRep_CLProps(const HLRBRep_Curve*& C,
                                  const double          U,
                                  const int             N,
                                  const double          Resolution);

  Standard_EXPORT HLRBRep_CLProps(const int N, const double Resolution);

  Standard_EXPORT void SetParameter(const double U);

  Standard_EXPORT void SetCurve(const HLRBRep_Curve*& C);

  Standard_EXPORT const gp_Pnt2d& Value() const;

  Standard_EXPORT const gp_Vec2d& D1();

  Standard_EXPORT const gp_Vec2d& D2();

  Standard_EXPORT const gp_Vec2d& D3();

  Standard_EXPORT bool IsTangentDefined();

  Standard_EXPORT void Tangent(gp_Dir2d& D);

  Standard_EXPORT double Curvature();

  Standard_EXPORT void Normal(gp_Dir2d& N);

  Standard_EXPORT void CentreOfCurvature(gp_Pnt2d& P);

private:
  const HLRBRep_Curve* myCurve;
  double               myU;
  int                  myDerOrder;
  double               myCN;
  double               myLinTol;
  gp_Pnt2d             myPnt;
  gp_Vec2d             myDerivArr[3];
  gp_Dir2d             myTangent;
  double               myCurvature;
  LProp_Status         myTangentStatus;
  int                  mySignificantFirstDerivativeOrder;
};
