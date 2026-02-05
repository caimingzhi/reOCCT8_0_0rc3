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

//! Defines points as constraints to be used to deform a surface.
class GeomPlate_PointConstraint : public Standard_Transient
{

public:
  //! Constructs a point constraint object defined by Pt, a 3D point
  //! Order gives the order of constraint, one of:
  //! -   -1 i.e. none, or 0 i.e.G0 when assigned to Pt
  //! -   -1 i.e. none, 0 i.e. G0, 1 i.e. G1, 2 i.e. G2 when
  //! assigned to U, V and Surf.
  //! In this constructor, only TolDist is given.
  //! Distance tolerance represents the greatest distance
  //! allowed between the constraint and the target surface.
  //! Angular tolerance represents the largest angle allowed
  //! between the constraint and the target surface. Curvature
  //! tolerance represents the greatest difference in curvature
  //! allowed between the constraint and the target surface.
  //! Raises ConstructionError if Order is not 0 or -1
  Standard_EXPORT GeomPlate_PointConstraint(const gp_Pnt& Pt,
                                            const int     Order,
                                            const double  TolDist = 0.0001);

  //! Constructs a point constraint object defined by
  //! the intersection point of U and V on the surface Surf.
  //! Order gives the order of constraint, one of:
  //! -   -1 i.e. none, or 0 i.e.G0 when assigned to Pt
  //! -   -1 i.e. none, 0 i.e. G0, 1 i.e. G1, 2 i.e. G2 when
  //! assigned to U, V and Surf.
  //! In this constructor the surface to be generated must
  //! respect several tolerance values only:
  //! -   the distance tolerance TolDist
  //! -   the angular tolerance TolAng
  //! -   the curvature tolerance, TolCurv.
  //! Distance tolerance represents the greatest distance
  //! allowed between the constraint and the target surface.
  //! Angular tolerance represents the largest angle allowed
  //! between the constraint and the target surface. Curvature
  //! tolerance represents the greatest difference in curvature
  //! allowed between the constraint and the target surface.Creates a punctual constraint.
  Standard_EXPORT GeomPlate_PointConstraint(const double                     U,
                                            const double                     V,
                                            const occ::handle<Geom_Surface>& Surf,
                                            const int                        Order,
                                            const double                     TolDist = 0.0001,
                                            const double                     TolAng  = 0.01,
                                            const double                     TolCurv = 0.1);

  Standard_EXPORT void SetOrder(const int Order);

  //! Returns the order of constraint: G0, G1, and G2,
  //! controlled respectively by G0Criterion G1Criterion and G2Criterion.
  Standard_EXPORT int Order() const;

  //! Allows you to set the G0 criterion. This is the law
  //! defining the greatest distance allowed between the
  //! constraint and the target surface. If this criterion is not
  //! set, {TolDist, the distance tolerance from the constructor, is used
  Standard_EXPORT void SetG0Criterion(const double TolDist);

  //! Allows you to set the G1 criterion. This is the law
  //! defining the greatest angle allowed between the
  //! constraint and the target surface. If this criterion is not
  //! set, TolAng, the angular tolerance from the constructor, is used.
  //! Raises ConstructionError if the point is not on the surface
  Standard_EXPORT void SetG1Criterion(const double TolAng);

  //! Allows you to set the G2 criterion. This is the law
  //! defining the greatest difference in curvature allowed
  //! between the constraint and the target surface. If this
  //! criterion is not set, TolCurv, the curvature tolerance from
  //! the constructor, is used.
  //! Raises ConstructionError if the point is not on the surface
  Standard_EXPORT void SetG2Criterion(const double TolCurv);

  //! Returns the G0 criterion. This is the greatest distance
  //! allowed between the constraint and the target surface.
  Standard_EXPORT double G0Criterion() const;

  //! Returns the G1 criterion. This is the greatest angle
  //! allowed between the constraint and the target surface.
  //! Raises ConstructionError if the point is not on the surface.
  Standard_EXPORT double G1Criterion() const;

  //! Returns the G2 criterion. This is the greatest difference
  //! in curvature allowed between the constraint and the target surface.
  //! Raises ConstructionError if the point is not on the surface
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
