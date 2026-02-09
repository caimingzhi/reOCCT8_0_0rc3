#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <GeomLProp_SLProps.hpp>
#include <gp_Pnt.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Vec.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Transient.hpp>
class Geom_Surface;

class GeomPlate_PointConstraint : public Standard_Transient
{

public:
  Standard_EXPORT GeomPlate_PointConstraint(const gp_Pnt& Pt,
                                            const int     Order,
                                            const double  TolDist = 0.0001);

  Standard_EXPORT GeomPlate_PointConstraint(const double                     U,
                                            const double                     V,
                                            const occ::handle<Geom_Surface>& Surf,
                                            const int                        Order,
                                            const double                     TolDist = 0.0001,
                                            const double                     TolAng  = 0.01,
                                            const double                     TolCurv = 0.1);

  Standard_EXPORT void SetOrder(const int Order);

  Standard_EXPORT int Order() const;

  Standard_EXPORT void SetG0Criterion(const double TolDist);

  Standard_EXPORT void SetG1Criterion(const double TolAng);

  Standard_EXPORT void SetG2Criterion(const double TolCurv);

  Standard_EXPORT double G0Criterion() const;

  Standard_EXPORT double G1Criterion() const;

  Standard_EXPORT double G2Criterion() const;

  Standard_EXPORT void D0(gp_Pnt& P) const;

  Standard_EXPORT void D1(gp_Pnt& P, gp_Vec& V1, gp_Vec& V2) const;

  Standard_EXPORT void D2(gp_Pnt& P, gp_Vec& V1, gp_Vec& V2, gp_Vec& V3, gp_Vec& V4, gp_Vec& V5)
    const;

  Standard_EXPORT bool HasPnt2dOnSurf() const;

  Standard_EXPORT void SetPnt2dOnSurf(const gp_Pnt2d& Pnt);

  Standard_EXPORT gp_Pnt2d Pnt2dOnSurf() const;

  Standard_EXPORT GeomLProp_SLProps& LPropSurf();

  DEFINE_STANDARD_RTTIEXT(GeomPlate_PointConstraint, Standard_Transient)

protected:
  int myOrder;

private:
  GeomLProp_SLProps         myLProp;
  gp_Pnt                    myPoint;
  gp_Pnt2d                  myPt2d;
  occ::handle<Geom_Surface> mySurf;
  gp_Vec                    myD11;
  gp_Vec                    myD12;
  gp_Vec                    myD21;
  gp_Vec                    myD22;
  gp_Vec                    myD23;
  double                    myU;
  double                    myV;
  double                    myTolDist;
  double                    myTolAng;
  double                    myTolCurv;
  bool                      hasPnt2dOnSurf;
};
