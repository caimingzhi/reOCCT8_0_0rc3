#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Pnt2d.hpp>
#include <NCollection_Array1.hpp>
#include <Standard_Integer.hpp>
#include <GeomAbs_Shape.hpp>
#include <Approx_ParametrizationType.hpp>
class Geom2d_BSplineCurve;

class Geom2dAPI_PointsToBSpline
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Geom2dAPI_PointsToBSpline();

  Standard_EXPORT Geom2dAPI_PointsToBSpline(const NCollection_Array1<gp_Pnt2d>& Points,
                                            const int                           DegMin = 3,
                                            const int                           DegMax = 8,
                                            const GeomAbs_Shape Continuity             = GeomAbs_C2,
                                            const double        Tol2D                  = 1.0e-6);

  Standard_EXPORT Geom2dAPI_PointsToBSpline(const NCollection_Array1<double>& YValues,
                                            const double                      X0,
                                            const double                      DX,
                                            const int                         DegMin = 3,
                                            const int                         DegMax = 8,
                                            const GeomAbs_Shape Continuity           = GeomAbs_C2,
                                            const double        Tol2D                = 1.0e-6);

  Standard_EXPORT Geom2dAPI_PointsToBSpline(const NCollection_Array1<gp_Pnt2d>& Points,
                                            const Approx_ParametrizationType    ParType,
                                            const int                           DegMin = 3,
                                            const int                           DegMax = 8,
                                            const GeomAbs_Shape Continuity             = GeomAbs_C2,
                                            const double        Tol2D                  = 1.0e-3);

  Standard_EXPORT Geom2dAPI_PointsToBSpline(const NCollection_Array1<gp_Pnt2d>& Points,
                                            const NCollection_Array1<double>&   Parameters,
                                            const int                           DegMin = 3,
                                            const int                           DegMax = 8,
                                            const GeomAbs_Shape Continuity             = GeomAbs_C2,
                                            const double        Tol2D                  = 1.0e-3);

  Standard_EXPORT Geom2dAPI_PointsToBSpline(const NCollection_Array1<gp_Pnt2d>& Points,
                                            const double                        Weight1,
                                            const double                        Weight2,
                                            const double                        Weight3,
                                            const int                           DegMax = 8,
                                            const GeomAbs_Shape Continuity             = GeomAbs_C2,
                                            const double        Tol3D                  = 1.0e-3);

  Standard_EXPORT void Init(const NCollection_Array1<gp_Pnt2d>& Points,
                            const int                           DegMin     = 3,
                            const int                           DegMax     = 8,
                            const GeomAbs_Shape                 Continuity = GeomAbs_C2,
                            const double                        Tol2D      = 1.0e-6);

  Standard_EXPORT void Init(const NCollection_Array1<double>& YValues,
                            const double                      X0,
                            const double                      DX,
                            const int                         DegMin     = 3,
                            const int                         DegMax     = 8,
                            const GeomAbs_Shape               Continuity = GeomAbs_C2,
                            const double                      Tol2D      = 1.0e-6);

  Standard_EXPORT void Init(const NCollection_Array1<gp_Pnt2d>& Points,
                            const Approx_ParametrizationType    ParType,
                            const int                           DegMin     = 3,
                            const int                           DegMax     = 8,
                            const GeomAbs_Shape                 Continuity = GeomAbs_C2,
                            const double                        Tol2D      = 1.0e-3);

  Standard_EXPORT void Init(const NCollection_Array1<gp_Pnt2d>& Points,
                            const NCollection_Array1<double>&   Parameters,
                            const int                           DegMin     = 3,
                            const int                           DegMax     = 8,
                            const GeomAbs_Shape                 Continuity = GeomAbs_C2,
                            const double                        Tol2D      = 1.0e-3);

  Standard_EXPORT void Init(const NCollection_Array1<gp_Pnt2d>& Points,
                            const double                        Weight1,
                            const double                        Weight2,
                            const double                        Weight3,
                            const int                           DegMax     = 8,
                            const GeomAbs_Shape                 Continuity = GeomAbs_C2,
                            const double                        Tol2D      = 1.0e-3);

  Standard_EXPORT const occ::handle<Geom2d_BSplineCurve>& Curve() const;
  Standard_EXPORT operator occ::handle<Geom2d_BSplineCurve>() const;

  Standard_EXPORT bool IsDone() const;

private:
  bool                             myIsDone;
  occ::handle<Geom2d_BSplineCurve> myCurve;
};
