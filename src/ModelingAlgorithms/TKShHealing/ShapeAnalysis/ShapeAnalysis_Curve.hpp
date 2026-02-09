#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array1.hpp>
#include <gp_Pnt2d.hpp>
#include <NCollection_Sequence.hpp>
class Geom_Curve;
class gp_Pnt;
class Adaptor3d_Curve;
class Geom2d_Curve;
class Bnd_Box2d;
class gp_XYZ;

class ShapeAnalysis_Curve
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT double Project(const occ::handle<Geom_Curve>& C3D,
                                 const gp_Pnt&                  P3D,
                                 const double                   preci,
                                 gp_Pnt&                        proj,
                                 double&                        param,
                                 const bool                     AdjustToEnds = true) const;

  Standard_EXPORT double Project(const Adaptor3d_Curve& C3D,
                                 const gp_Pnt&          P3D,
                                 const double           preci,
                                 gp_Pnt&                proj,
                                 double&                param,
                                 const bool             AdjustToEnds = true) const;

  Standard_EXPORT double Project(const occ::handle<Geom_Curve>& C3D,
                                 const gp_Pnt&                  P3D,
                                 const double                   preci,
                                 gp_Pnt&                        proj,
                                 double&                        param,
                                 const double                   cf,
                                 const double                   cl,
                                 const bool                     AdjustToEnds = true) const;

  Standard_EXPORT double ProjectAct(const Adaptor3d_Curve& C3D,
                                    const gp_Pnt&          P3D,
                                    const double           preci,
                                    gp_Pnt&                proj,
                                    double&                param) const;

  Standard_EXPORT double NextProject(const double                   paramPrev,
                                     const occ::handle<Geom_Curve>& C3D,
                                     const gp_Pnt&                  P3D,
                                     const double                   preci,
                                     gp_Pnt&                        proj,
                                     double&                        param,
                                     const double                   cf,
                                     const double                   cl,
                                     const bool                     AdjustToEnds = true) const;

  Standard_EXPORT double NextProject(const double           paramPrev,
                                     const Adaptor3d_Curve& C3D,
                                     const gp_Pnt&          P3D,
                                     const double           preci,
                                     gp_Pnt&                proj,
                                     double&                param) const;

  Standard_EXPORT bool ValidateRange(const occ::handle<Geom_Curve>& Crv,
                                     double&                        First,
                                     double&                        Last,
                                     const double                   prec) const;

  Standard_EXPORT void FillBndBox(const occ::handle<Geom2d_Curve>& C2d,
                                  const double                     First,
                                  const double                     Last,
                                  const int                        NPoints,
                                  const bool                       Exact,
                                  Bnd_Box2d&                       Box) const;

  Standard_EXPORT int SelectForwardSeam(const occ::handle<Geom2d_Curve>& C1,
                                        const occ::handle<Geom2d_Curve>& C2) const;

  Standard_EXPORT static bool IsPlanar(const NCollection_Array1<gp_Pnt>& pnts,
                                       gp_XYZ&                           Normal,
                                       const double                      preci = 0);

  Standard_EXPORT static bool IsPlanar(const occ::handle<Geom_Curve>& curve,
                                       gp_XYZ&                        Normal,
                                       const double                   preci = 0);

  Standard_EXPORT static bool GetSamplePoints(const occ::handle<Geom2d_Curve>& curve,
                                              const double                     first,
                                              const double                     last,
                                              NCollection_Sequence<gp_Pnt2d>&  seq);

  Standard_EXPORT static bool GetSamplePoints(const occ::handle<Geom_Curve>& curve,
                                              const double                   first,
                                              const double                   last,
                                              NCollection_Sequence<gp_Pnt>&  seq);

  Standard_EXPORT static bool IsClosed(const occ::handle<Geom_Curve>& curve,
                                       const double                   preci = -1);

  Standard_EXPORT static bool IsPeriodic(const occ::handle<Geom_Curve>& curve);

  Standard_EXPORT static bool IsPeriodic(const occ::handle<Geom2d_Curve>& curve);
};
