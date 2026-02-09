#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Pnt.hpp>
#include <NCollection_Array2.hpp>
#include <Standard_Integer.hpp>
#include <GeomAbs_Shape.hpp>
#include <Approx_ParametrizationType.hpp>
class Geom_BSplineSurface;

class GeomAPI_PointsToBSplineSurface
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomAPI_PointsToBSplineSurface();

  Standard_EXPORT GeomAPI_PointsToBSplineSurface(const NCollection_Array2<gp_Pnt>& Points,
                                                 const int                         DegMin = 3,
                                                 const int                         DegMax = 8,
                                                 const GeomAbs_Shape Continuity = GeomAbs_C2,
                                                 const double        Tol3D      = 1.0e-3);

  Standard_EXPORT GeomAPI_PointsToBSplineSurface(const NCollection_Array2<gp_Pnt>& Points,
                                                 const Approx_ParametrizationType  ParType,
                                                 const int                         DegMin = 3,
                                                 const int                         DegMax = 8,
                                                 const GeomAbs_Shape Continuity = GeomAbs_C2,
                                                 const double        Tol3D      = 1.0e-3);

  Standard_EXPORT GeomAPI_PointsToBSplineSurface(const NCollection_Array2<gp_Pnt>& Points,
                                                 const double                      Weight1,
                                                 const double                      Weight2,
                                                 const double                      Weight3,
                                                 const int                         DegMax = 8,
                                                 const GeomAbs_Shape Continuity = GeomAbs_C2,
                                                 const double        Tol3D      = 1.0e-3);

  Standard_EXPORT GeomAPI_PointsToBSplineSurface(const NCollection_Array2<double>& ZPoints,
                                                 const double                      X0,
                                                 const double                      dX,
                                                 const double                      Y0,
                                                 const double                      dY,
                                                 const int                         DegMin = 3,
                                                 const int                         DegMax = 8,
                                                 const GeomAbs_Shape Continuity = GeomAbs_C2,
                                                 const double        Tol3D      = 1.0e-3);

  Standard_EXPORT void Init(const NCollection_Array2<gp_Pnt>& Points,
                            const int                         DegMin     = 3,
                            const int                         DegMax     = 8,
                            const GeomAbs_Shape               Continuity = GeomAbs_C2,
                            const double                      Tol3D      = 1.0e-3);

  Standard_EXPORT void Interpolate(const NCollection_Array2<gp_Pnt>& Points,
                                   const bool                        thePeriodic = false);

  Standard_EXPORT void Interpolate(const NCollection_Array2<gp_Pnt>& Points,
                                   const Approx_ParametrizationType  ParType,
                                   const bool                        thePeriodic = false);

  Standard_EXPORT void Init(const NCollection_Array2<double>& ZPoints,
                            const double                      X0,
                            const double                      dX,
                            const double                      Y0,
                            const double                      dY,
                            const int                         DegMin     = 3,
                            const int                         DegMax     = 8,
                            const GeomAbs_Shape               Continuity = GeomAbs_C2,
                            const double                      Tol3D      = 1.0e-3);

  Standard_EXPORT void Interpolate(const NCollection_Array2<double>& ZPoints,
                                   const double                      X0,
                                   const double                      dX,
                                   const double                      Y0,
                                   const double                      dY);

  Standard_EXPORT void Init(const NCollection_Array2<gp_Pnt>& Points,
                            const Approx_ParametrizationType  ParType,
                            const int                         DegMin      = 3,
                            const int                         DegMax      = 8,
                            const GeomAbs_Shape               Continuity  = GeomAbs_C2,
                            const double                      Tol3D       = 1.0e-3,
                            const bool                        thePeriodic = false);

  Standard_EXPORT void Init(const NCollection_Array2<gp_Pnt>& Points,
                            const double                      Weight1,
                            const double                      Weight2,
                            const double                      Weight3,
                            const int                         DegMax     = 8,
                            const GeomAbs_Shape               Continuity = GeomAbs_C2,
                            const double                      Tol3D      = 1.0e-3);

  Standard_EXPORT const occ::handle<Geom_BSplineSurface>& Surface() const;
  Standard_EXPORT operator occ::handle<Geom_BSplineSurface>() const;

  Standard_EXPORT bool IsDone() const;

private:
  bool                             myIsDone;
  occ::handle<Geom_BSplineSurface> mySurface;
};
