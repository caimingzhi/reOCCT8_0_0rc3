#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <BRepAdaptor_Surface.hpp>
#include <Standard_Integer.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <gp_Dir.hpp>
#include <LProp_Status.hpp>
class LProp_BadContinuity;
class Standard_DomainError;
class Standard_OutOfRange;
class LProp_NotDefined;
class BRepAdaptor_Surface;
class BRepLProp_SurfaceTool;
class gp_Pnt;
class gp_Vec;
class gp_Dir;

class BRepLProp_SLProps
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepLProp_SLProps(const BRepAdaptor_Surface& S,
                                    const double               U,
                                    const double               V,
                                    const int                  N,
                                    const double               Resolution);

  Standard_EXPORT BRepLProp_SLProps(const BRepAdaptor_Surface& S,
                                    const int                  N,
                                    const double               Resolution);

  Standard_EXPORT BRepLProp_SLProps(const int N, const double Resolution);

  Standard_EXPORT void SetSurface(const BRepAdaptor_Surface& S);

  Standard_EXPORT void SetParameters(const double U, const double V);

  Standard_EXPORT const gp_Pnt& Value() const;

  Standard_EXPORT const gp_Vec& D1U();

  Standard_EXPORT const gp_Vec& D1V();

  Standard_EXPORT const gp_Vec& D2U();

  Standard_EXPORT const gp_Vec& D2V();

  Standard_EXPORT const gp_Vec& DUV();

  Standard_EXPORT bool IsTangentUDefined();

  Standard_EXPORT void TangentU(gp_Dir& D);

  Standard_EXPORT bool IsTangentVDefined();

  Standard_EXPORT void TangentV(gp_Dir& D);

  Standard_EXPORT bool IsNormalDefined();

  Standard_EXPORT const gp_Dir& Normal();

  Standard_EXPORT bool IsCurvatureDefined();

  Standard_EXPORT bool IsUmbilic();

  Standard_EXPORT double MaxCurvature();

  Standard_EXPORT double MinCurvature();

  Standard_EXPORT void CurvatureDirections(gp_Dir& MaxD, gp_Dir& MinD);

  Standard_EXPORT double MeanCurvature();

  Standard_EXPORT double GaussianCurvature();

private:
  BRepAdaptor_Surface mySurf;
  double              myU;
  double              myV;
  int                 myDerOrder;
  int                 myCN;
  double              myLinTol;
  gp_Pnt              myPnt;
  gp_Vec              myD1u;
  gp_Vec              myD1v;
  gp_Vec              myD2u;
  gp_Vec              myD2v;
  gp_Vec              myDuv;
  gp_Dir              myNormal;
  double              myMinCurv;
  double              myMaxCurv;
  gp_Dir              myDirMinCurv;
  gp_Dir              myDirMaxCurv;
  double              myMeanCurv;
  double              myGausCurv;
  int                 mySignificantFirstDerivativeOrderU;
  int                 mySignificantFirstDerivativeOrderV;
  LProp_Status        myUTangentStatus;
  LProp_Status        myVTangentStatus;
  LProp_Status        myNormalStatus;
  LProp_Status        myCurvatureStatus;
};
