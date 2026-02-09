#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Pnt.hpp>
#include <NCollection_Array1.hpp>
#include <Standard_Integer.hpp>
#include <GeomAbs_Shape.hpp>
#include <Approx_ParametrizationType.hpp>
class Geom_BSplineCurve;

class GeomAPI_PointsToBSpline
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomAPI_PointsToBSpline();

  Standard_EXPORT GeomAPI_PointsToBSpline(const NCollection_Array1<gp_Pnt>& Points,
                                          const int                         DegMin     = 3,
                                          const int                         DegMax     = 8,
                                          const GeomAbs_Shape               Continuity = GeomAbs_C2,
                                          const double                      Tol3D      = 1.0e-3);

  Standard_EXPORT GeomAPI_PointsToBSpline(const NCollection_Array1<gp_Pnt>& Points,
                                          const Approx_ParametrizationType  ParType,
                                          const int                         DegMin     = 3,
                                          const int                         DegMax     = 8,
                                          const GeomAbs_Shape               Continuity = GeomAbs_C2,
                                          const double                      Tol3D      = 1.0e-3);

  Standard_EXPORT GeomAPI_PointsToBSpline(const NCollection_Array1<gp_Pnt>& Points,
                                          const NCollection_Array1<double>& Parameters,
                                          const int                         DegMin     = 3,
                                          const int                         DegMax     = 8,
                                          const GeomAbs_Shape               Continuity = GeomAbs_C2,
                                          const double                      Tol3D      = 1.0e-3);

  Standard_EXPORT GeomAPI_PointsToBSpline(const NCollection_Array1<gp_Pnt>& Points,
                                          const double                      Weight1,
                                          const double                      Weight2,
                                          const double                      Weight3,
                                          const int                         DegMax     = 8,
                                          const GeomAbs_Shape               Continuity = GeomAbs_C2,
                                          const double                      Tol3D      = 1.0e-3);

  Standard_EXPORT void Init(const NCollection_Array1<gp_Pnt>& Points,
                            const int                         DegMin     = 3,
                            const int                         DegMax     = 8,
                            const GeomAbs_Shape               Continuity = GeomAbs_C2,
                            const double                      Tol3D      = 1.0e-3);

  Standard_EXPORT void Init(const NCollection_Array1<gp_Pnt>& Points,
                            const Approx_ParametrizationType  ParType,
                            const int                         DegMin     = 3,
                            const int                         DegMax     = 8,
                            const GeomAbs_Shape               Continuity = GeomAbs_C2,
                            const double                      Tol3D      = 1.0e-3);

  Standard_EXPORT void Init(const NCollection_Array1<gp_Pnt>& Points,
                            const NCollection_Array1<double>& Parameters,
                            const int                         DegMin     = 3,
                            const int                         DegMax     = 8,
                            const GeomAbs_Shape               Continuity = GeomAbs_C2,
                            const double                      Tol3D      = 1.0e-3);

  Standard_EXPORT void Init(const NCollection_Array1<gp_Pnt>& Points,
                            const double                      Weight1,
                            const double                      Weight2,
                            const double                      Weight3,
                            const int                         DegMax     = 8,
                            const GeomAbs_Shape               Continuity = GeomAbs_C2,
                            const double                      Tol3D      = 1.0e-3);

  Standard_EXPORT const occ::handle<Geom_BSplineCurve>& Curve() const;
  Standard_EXPORT operator occ::handle<Geom_BSplineCurve>() const;

  Standard_EXPORT bool IsDone() const;

private:
  bool                           myIsDone;
  occ::handle<Geom_BSplineCurve> myCurve;
};
