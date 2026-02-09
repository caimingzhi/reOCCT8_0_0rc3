#pragma once

#include <Adaptor3d_CurveOnSurface.hpp>
#include <GeomLProp_SLProps.hpp>

class Geom2d_Curve;
class Law_Function;
class gp_Pnt;
class gp_Vec;

class GeomPlate_CurveConstraint : public Standard_Transient
{

public:
  Standard_EXPORT GeomPlate_CurveConstraint();

  Standard_EXPORT GeomPlate_CurveConstraint(const occ::handle<Adaptor3d_Curve>& Boundary,
                                            const int                           Order,
                                            const int                           NPt     = 10,
                                            const double                        TolDist = 0.0001,
                                            const double                        TolAng  = 0.01,
                                            const double                        TolCurv = 0.1);

  Standard_EXPORT void SetOrder(const int Order);

  Standard_EXPORT int Order() const;

  Standard_EXPORT int NbPoints() const;

  Standard_EXPORT void SetNbPoints(const int NewNb);

  Standard_EXPORT void SetG0Criterion(const occ::handle<Law_Function>& G0Crit);

  Standard_EXPORT void SetG1Criterion(const occ::handle<Law_Function>& G1Crit);

  Standard_EXPORT void SetG2Criterion(const occ::handle<Law_Function>& G2Crit);

  Standard_EXPORT double G0Criterion(const double U) const;

  Standard_EXPORT double G1Criterion(const double U) const;

  Standard_EXPORT double G2Criterion(const double U) const;

  Standard_EXPORT double FirstParameter() const;

  Standard_EXPORT double LastParameter() const;

  Standard_EXPORT double Length() const;

  Standard_EXPORT GeomLProp_SLProps& LPropSurf(const double U);

  Standard_EXPORT void D0(const double U, gp_Pnt& P) const;

  Standard_EXPORT void D1(const double U, gp_Pnt& P, gp_Vec& V1, gp_Vec& V2) const;

  Standard_EXPORT void D2(const double U,
                          gp_Pnt&      P,
                          gp_Vec&      V1,
                          gp_Vec&      V2,
                          gp_Vec&      V3,
                          gp_Vec&      V4,
                          gp_Vec&      V5) const;

  Standard_EXPORT occ::handle<Adaptor3d_Curve> Curve3d() const;

  Standard_EXPORT void SetCurve2dOnSurf(const occ::handle<Geom2d_Curve>& Curve2d);

  Standard_EXPORT occ::handle<Geom2d_Curve> Curve2dOnSurf() const;

  Standard_EXPORT void SetProjectedCurve(const occ::handle<Adaptor2d_Curve2d>& Curve2d,
                                         const double                          TolU,
                                         const double                          TolV);

  Standard_EXPORT occ::handle<Adaptor2d_Curve2d> ProjectedCurve() const;

  DEFINE_STANDARD_RTTIEXT(GeomPlate_CurveConstraint, Standard_Transient)

protected:
  occ::handle<Adaptor3d_CurveOnSurface> myFrontiere;
  int                                   myNbPoints;
  int                                   myOrder;
  occ::handle<Adaptor3d_Curve>          my3dCurve;
  int                                   myTang;
  occ::handle<Geom2d_Curve>             my2dCurve;
  occ::handle<Adaptor2d_Curve2d>        myHCurve2d;
  occ::handle<Law_Function>             myG0Crit;
  occ::handle<Law_Function>             myG1Crit;
  occ::handle<Law_Function>             myG2Crit;
  bool                                  myConstG0;
  bool                                  myConstG1;
  bool                                  myConstG2;
  GeomLProp_SLProps                     myLProp;
  double                                myTolDist;
  double                                myTolAng;
  double                                myTolCurv;
  double                                myTolU;
  double                                myTolV;
};
