#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <GeomPlate_CurveConstraint.hpp>
#include <Standard_Integer.hpp>

//! same as CurveConstraint from GeomPlate
//! with BRepAdaptor_Surface instead of
//! GeomAdaptor_Surface
class BRepFill_CurveConstraint : public GeomPlate_CurveConstraint
{

public:
  //! Create a constraint
  //! Order is the order of the constraint. The possible values for order are -1,0,1,2.
  //! Order i means constraints Gi
  //! Npt is the number of points associated with the constraint.
  //! TolDist is the maximum error to satisfy for G0 constraints
  //! TolAng is the maximum error to satisfy for G1 constraints
  //! TolCurv is the maximum error to satisfy for G2 constraints
  //! These errors can be replaced by laws of criterion.
  Standard_EXPORT BRepFill_CurveConstraint(const occ::handle<Adaptor3d_CurveOnSurface>& Boundary,
                                           const int                                    Order,
                                           const int                                    NPt = 10,
                                           const double TolDist = 0.0001,
                                           const double TolAng  = 0.01,
                                           const double TolCurv = 0.1);

  Standard_EXPORT BRepFill_CurveConstraint(const occ::handle<Adaptor3d_Curve>& Boundary,
                                           const int                           Tang,
                                           const int                           NPt     = 10,
                                           const double                        TolDist = 0.0001);

  DEFINE_STANDARD_RTTIEXT(BRepFill_CurveConstraint, GeomPlate_CurveConstraint)
};

