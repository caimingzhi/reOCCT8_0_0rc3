#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
class Geom_Curve;
class gp_Pnt;
class Geom2d_Curve;
class gp_Pnt2d;
class Geom_BSplineCurve;
class Geom2d_BSplineCurve;

class ShapeConstruct_Curve
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT bool AdjustCurve(const occ::handle<Geom_Curve>& C3D,
                                   const gp_Pnt&                  P1,
                                   const gp_Pnt&                  P2,
                                   const bool                     take1 = true,
                                   const bool                     take2 = true) const;

  Standard_EXPORT bool AdjustCurveSegment(const occ::handle<Geom_Curve>& C3D,
                                          const gp_Pnt&                  P1,
                                          const gp_Pnt&                  P2,
                                          const double                   U1,
                                          const double                   U2) const;

  Standard_EXPORT bool AdjustCurve2d(const occ::handle<Geom2d_Curve>& C2D,
                                     const gp_Pnt2d&                  P1,
                                     const gp_Pnt2d&                  P2,
                                     const bool                       take1 = true,
                                     const bool                       take2 = true) const;

  Standard_EXPORT occ::handle<Geom_BSplineCurve> ConvertToBSpline(const occ::handle<Geom_Curve>& C,
                                                                  const double first,
                                                                  const double last,
                                                                  const double prec) const;

  Standard_EXPORT occ::handle<Geom2d_BSplineCurve> ConvertToBSpline(
    const occ::handle<Geom2d_Curve>& C,
    const double                     first,
    const double                     last,
    const double                     prec) const;

  Standard_EXPORT static bool FixKnots(occ::handle<NCollection_HArray1<double>>& knots);

  Standard_EXPORT static bool FixKnots(NCollection_Array1<double>& knots);
};
