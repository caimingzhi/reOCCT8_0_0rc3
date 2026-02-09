#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <GeomPlate_CurveConstraint.hpp>
#include <Standard_Integer.hpp>

class BRepFill_CurveConstraint : public GeomPlate_CurveConstraint
{

public:
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
