#pragma once

#include <Adaptor3d_Surface.hpp>
#include <LProp_Status.hpp>

class LProp3d_SLProps
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT LProp3d_SLProps(const occ::handle<Adaptor3d_Surface>& S,
                                  const double                          U,
                                  const double                          V,
                                  const int                             N,
                                  const double                          Resolution);

  Standard_EXPORT LProp3d_SLProps(const occ::handle<Adaptor3d_Surface>& S,
                                  const int                             N,
                                  const double                          Resolution);

  Standard_EXPORT LProp3d_SLProps(const int N, const double Resolution);

  Standard_EXPORT void SetSurface(const occ::handle<Adaptor3d_Surface>& S);

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
  occ::handle<Adaptor3d_Surface> mySurf;
  double                         myU;
  double                         myV;
  int                            myDerOrder;
  int                            myCN;
  double                         myLinTol;
  gp_Pnt                         myPnt;
  gp_Vec                         myD1u;
  gp_Vec                         myD1v;
  gp_Vec                         myD2u;
  gp_Vec                         myD2v;
  gp_Vec                         myDuv;
  gp_Dir                         myNormal;
  double                         myMinCurv;
  double                         myMaxCurv;
  gp_Dir                         myDirMinCurv;
  gp_Dir                         myDirMaxCurv;
  double                         myMeanCurv;
  double                         myGausCurv;
  int                            mySignificantFirstDerivativeOrderU;
  int                            mySignificantFirstDerivativeOrderV;
  LProp_Status                   myUTangentStatus;
  LProp_Status                   myVTangentStatus;
  LProp_Status                   myNormalStatus;
  LProp_Status                   myCurvatureStatus;
};
