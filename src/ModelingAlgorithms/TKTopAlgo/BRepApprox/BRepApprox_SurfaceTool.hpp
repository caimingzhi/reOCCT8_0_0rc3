#pragma once

#include <BRepAdaptor_Surface.hpp>
#include <GeomAbs_Shape.hpp>
#include <NCollection_Array1.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <GeomAbs_SurfaceType.hpp>
#include <gp_Pln.hpp>
#include <gp_Cylinder.hpp>
#include <gp_Cone.hpp>
#include <gp_Torus.hpp>
#include <gp_Sphere.hpp>
#include <gp_Ax1.hpp>
#include <gp_Dir.hpp>

class Geom_BezierSurface;
class Geom_BSplineSurface;

class BRepApprox_SurfaceTool
{
public:
  DEFINE_STANDARD_ALLOC

  static double FirstUParameter(const ::model::adapter::BRepAdaptor_Surface& S);

  static double FirstVParameter(const ::model::adapter::BRepAdaptor_Surface& S);

  static double LastUParameter(const ::model::adapter::BRepAdaptor_Surface& S);

  static double LastVParameter(const ::model::adapter::BRepAdaptor_Surface& S);

  static int NbUIntervals(const ::model::adapter::BRepAdaptor_Surface& S, const GeomAbs_Shape Sh);

  static int NbVIntervals(const ::model::adapter::BRepAdaptor_Surface& S, const GeomAbs_Shape Sh);

  static void UIntervals(const ::model::adapter::BRepAdaptor_Surface&  S,
                         NCollection_Array1<double>& T,
                         const GeomAbs_Shape         Sh);

  static void VIntervals(const ::model::adapter::BRepAdaptor_Surface&  S,
                         NCollection_Array1<double>& T,
                         const GeomAbs_Shape         Sh);

  static occ::handle<Adaptor3d_Surface> UTrim(const ::model::adapter::BRepAdaptor_Surface& S,
                                              const double               First,
                                              const double               Last,
                                              const double               Tol);

  static occ::handle<Adaptor3d_Surface> VTrim(const ::model::adapter::BRepAdaptor_Surface& S,
                                              const double               First,
                                              const double               Last,
                                              const double               Tol);

  static bool IsUClosed(const ::model::adapter::BRepAdaptor_Surface& S);

  static bool IsVClosed(const ::model::adapter::BRepAdaptor_Surface& S);

  static bool IsUPeriodic(const ::model::adapter::BRepAdaptor_Surface& S);

  static double UPeriod(const ::model::adapter::BRepAdaptor_Surface& S);

  static bool IsVPeriodic(const ::model::adapter::BRepAdaptor_Surface& S);

  static double VPeriod(const ::model::adapter::BRepAdaptor_Surface& S);

  static gp_Pnt Value(const ::model::adapter::BRepAdaptor_Surface& S, const double u, const double v);

  static void D0(const ::model::adapter::BRepAdaptor_Surface& S, const double u, const double v, gp_Pnt& P);

  static void D1(const ::model::adapter::BRepAdaptor_Surface& S,
                 const double               u,
                 const double               v,
                 gp_Pnt&                    P,
                 gp_Vec&                    D1u,
                 gp_Vec&                    D1v);

  static void D2(const ::model::adapter::BRepAdaptor_Surface& S,
                 const double               u,
                 const double               v,
                 gp_Pnt&                    P,
                 gp_Vec&                    D1U,
                 gp_Vec&                    D1V,
                 gp_Vec&                    D2U,
                 gp_Vec&                    D2V,
                 gp_Vec&                    D2UV);

  static void D3(const ::model::adapter::BRepAdaptor_Surface& S,
                 const double               u,
                 const double               v,
                 gp_Pnt&                    P,
                 gp_Vec&                    D1U,
                 gp_Vec&                    D1V,
                 gp_Vec&                    D2U,
                 gp_Vec&                    D2V,
                 gp_Vec&                    D2UV,
                 gp_Vec&                    D3U,
                 gp_Vec&                    D3V,
                 gp_Vec&                    D3UUV,
                 gp_Vec&                    D3UVV);

  static gp_Vec DN(const ::model::adapter::BRepAdaptor_Surface& S,
                   const double               u,
                   const double               v,
                   const int                  Nu,
                   const int                  Nv);

  static double UResolution(const ::model::adapter::BRepAdaptor_Surface& S, const double R3d);

  static double VResolution(const ::model::adapter::BRepAdaptor_Surface& S, const double R3d);

  static GeomAbs_SurfaceType GetType(const ::model::adapter::BRepAdaptor_Surface& S);

  static gp_Pln Plane(const ::model::adapter::BRepAdaptor_Surface& S);

  static gp_Cylinder Cylinder(const ::model::adapter::BRepAdaptor_Surface& S);

  static gp_Cone Cone(const ::model::adapter::BRepAdaptor_Surface& S);

  static gp_Torus Torus(const ::model::adapter::BRepAdaptor_Surface& S);

  static gp_Sphere Sphere(const ::model::adapter::BRepAdaptor_Surface& S);

  static occ::handle<Geom_BezierSurface> Bezier(const ::model::adapter::BRepAdaptor_Surface& S);

  static occ::handle<Geom_BSplineSurface> BSpline(const ::model::adapter::BRepAdaptor_Surface& S);

  static gp_Ax1 AxeOfRevolution(const ::model::adapter::BRepAdaptor_Surface& S);

  static gp_Dir Direction(const ::model::adapter::BRepAdaptor_Surface& S);

  static occ::handle<Adaptor3d_Curve> BasisCurve(const ::model::adapter::BRepAdaptor_Surface& S);

  Standard_EXPORT static int NbSamplesU(const ::model::adapter::BRepAdaptor_Surface& S);

  Standard_EXPORT static int NbSamplesV(const ::model::adapter::BRepAdaptor_Surface& S);

  Standard_EXPORT static int NbSamplesU(const ::model::adapter::BRepAdaptor_Surface& S,
                                        const double               u1,
                                        const double               u2);

  Standard_EXPORT static int NbSamplesV(const ::model::adapter::BRepAdaptor_Surface& S,
                                        const double               v1,
                                        const double               v2);
};

#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <gp_Pln.hpp>
#include <gp_Cylinder.hpp>
#include <gp_Cone.hpp>
#include <gp_Torus.hpp>
#include <gp_Sphere.hpp>
#include <gp_Ax1.hpp>
#include <gp_Dir.hpp>
#include <Geom_BezierSurface.hpp>
#include <Geom_BSplineSurface.hpp>
#include <Adaptor3d_Surface.hpp>
#include <Adaptor3d_Curve.hpp>

inline double BRepApprox_SurfaceTool::FirstUParameter(const ::model::adapter::BRepAdaptor_Surface& Surf)
{
  return Surf.FirstUParameter();
}

inline double BRepApprox_SurfaceTool::FirstVParameter(const ::model::adapter::BRepAdaptor_Surface& Surf)
{
  return Surf.FirstVParameter();
}

inline double BRepApprox_SurfaceTool::LastUParameter(const ::model::adapter::BRepAdaptor_Surface& Surf)
{
  return Surf.LastUParameter();
}

inline double BRepApprox_SurfaceTool::LastVParameter(const ::model::adapter::BRepAdaptor_Surface& Surf)
{
  return Surf.LastVParameter();
}

inline int BRepApprox_SurfaceTool::NbUIntervals(const ::model::adapter::BRepAdaptor_Surface& Surf,
                                                const GeomAbs_Shape        S)
{
  return Surf.NbUIntervals(S);
}

inline int BRepApprox_SurfaceTool::NbVIntervals(const ::model::adapter::BRepAdaptor_Surface& Surf,
                                                const GeomAbs_Shape        S)
{
  return Surf.NbVIntervals(S);
}

inline void BRepApprox_SurfaceTool::UIntervals(const ::model::adapter::BRepAdaptor_Surface&  Surf,
                                               NCollection_Array1<double>& Tab,
                                               const GeomAbs_Shape         S)
{
  Surf.UIntervals(Tab, S);
}

inline void BRepApprox_SurfaceTool::VIntervals(const ::model::adapter::BRepAdaptor_Surface&  Surf,
                                               NCollection_Array1<double>& Tab,
                                               const GeomAbs_Shape         S)
{
  Surf.VIntervals(Tab, S);
}

inline occ::handle<Adaptor3d_Surface> BRepApprox_SurfaceTool::UTrim(const ::model::adapter::BRepAdaptor_Surface& Surf,
                                                                    const double               F,
                                                                    const double               L,
                                                                    const double               Tol)
{
  return Surf.UTrim(F, L, Tol);
}

inline occ::handle<Adaptor3d_Surface> BRepApprox_SurfaceTool::VTrim(const ::model::adapter::BRepAdaptor_Surface& Surf,
                                                                    const double               F,
                                                                    const double               L,
                                                                    const double               Tol)
{
  return Surf.VTrim(F, L, Tol);
}

inline bool BRepApprox_SurfaceTool::IsUClosed(const ::model::adapter::BRepAdaptor_Surface& S)
{
  return S.IsUClosed();
}

inline bool BRepApprox_SurfaceTool::IsVClosed(const ::model::adapter::BRepAdaptor_Surface& S)
{
  return S.IsVClosed();
}

inline bool BRepApprox_SurfaceTool::IsUPeriodic(const ::model::adapter::BRepAdaptor_Surface& S)
{
  return S.IsUPeriodic();
}

inline double BRepApprox_SurfaceTool::UPeriod(const ::model::adapter::BRepAdaptor_Surface& S)
{
  return S.UPeriod();
}

inline bool BRepApprox_SurfaceTool::IsVPeriodic(const ::model::adapter::BRepAdaptor_Surface& S)
{
  return S.IsVPeriodic();
}

inline double BRepApprox_SurfaceTool::VPeriod(const ::model::adapter::BRepAdaptor_Surface& S)
{
  return S.VPeriod();
}

inline gp_Pnt BRepApprox_SurfaceTool::Value(const ::model::adapter::BRepAdaptor_Surface& S,
                                            const double               U,
                                            const double               V)
{
  return S.Value(U, V);
}

inline void BRepApprox_SurfaceTool::D0(const ::model::adapter::BRepAdaptor_Surface& S,
                                       const double               U,
                                       const double               V,
                                       gp_Pnt&                    P)
{
  S.D0(U, V, P);
}

inline void BRepApprox_SurfaceTool::D1(const ::model::adapter::BRepAdaptor_Surface& S,
                                       const double               U,
                                       const double               V,
                                       gp_Pnt&                    P,
                                       gp_Vec&                    D1U,
                                       gp_Vec&                    D1V)
{
  S.D1(U, V, P, D1U, D1V);
}

inline void BRepApprox_SurfaceTool::D2(const ::model::adapter::BRepAdaptor_Surface& S,
                                       const double               U,
                                       const double               V,
                                       gp_Pnt&                    P,
                                       gp_Vec&                    D1U,
                                       gp_Vec&                    D1V,
                                       gp_Vec&                    D2U,
                                       gp_Vec&                    D2V,
                                       gp_Vec&                    D2UV)
{
  S.D2(U, V, P, D1U, D1V, D2U, D2V, D2UV);
}

inline void BRepApprox_SurfaceTool::D3(const ::model::adapter::BRepAdaptor_Surface& S,
                                       const double               U,
                                       const double               V,
                                       gp_Pnt&                    P,
                                       gp_Vec&                    D1U,
                                       gp_Vec&                    D1V,
                                       gp_Vec&                    D2U,
                                       gp_Vec&                    D2V,
                                       gp_Vec&                    D2UV,
                                       gp_Vec&                    D3U,
                                       gp_Vec&                    D3V,
                                       gp_Vec&                    D3UUV,
                                       gp_Vec&                    D3UVV)
{
  S.D3(U, V, P, D1U, D1V, D2U, D2V, D2UV, D3U, D3V, D3UUV, D3UVV);
}

inline gp_Vec BRepApprox_SurfaceTool::DN(const ::model::adapter::BRepAdaptor_Surface& S,
                                         const double               U,
                                         const double               V,
                                         const int                  Nu,
                                         const int                  Nv)
{
  return S.DN(U, V, Nu, Nv);
}

inline double BRepApprox_SurfaceTool::UResolution(const ::model::adapter::BRepAdaptor_Surface& S, const double R3d)
{
  return S.UResolution(R3d);
}

inline double BRepApprox_SurfaceTool::VResolution(const ::model::adapter::BRepAdaptor_Surface& S, const double R3d)
{
  return S.VResolution(R3d);
}

inline GeomAbs_SurfaceType BRepApprox_SurfaceTool::GetType(const ::model::adapter::BRepAdaptor_Surface& S)
{
  return S.GetType();
}

inline gp_Pln BRepApprox_SurfaceTool::Plane(const ::model::adapter::BRepAdaptor_Surface& S)
{
  return S.Plane();
}

inline gp_Cylinder BRepApprox_SurfaceTool::Cylinder(const ::model::adapter::BRepAdaptor_Surface& S)
{
  return S.Cylinder();
}

inline gp_Cone BRepApprox_SurfaceTool::Cone(const ::model::adapter::BRepAdaptor_Surface& S)
{
  return S.Cone();
}

inline gp_Sphere BRepApprox_SurfaceTool::Sphere(const ::model::adapter::BRepAdaptor_Surface& S)
{
  return S.Sphere();
}

inline gp_Torus BRepApprox_SurfaceTool::Torus(const ::model::adapter::BRepAdaptor_Surface& S)
{
  return S.Torus();
}

inline occ::handle<Geom_BezierSurface> BRepApprox_SurfaceTool::Bezier(const ::model::adapter::BRepAdaptor_Surface& S)
{
  return (S.Bezier());
}

inline occ::handle<Geom_BSplineSurface> BRepApprox_SurfaceTool::BSpline(
  const ::model::adapter::BRepAdaptor_Surface& S)
{
  return (S.BSpline());
}

inline gp_Ax1 BRepApprox_SurfaceTool::AxeOfRevolution(const ::model::adapter::BRepAdaptor_Surface& S)
{
  return (S.AxeOfRevolution());
}

inline gp_Dir BRepApprox_SurfaceTool::Direction(const ::model::adapter::BRepAdaptor_Surface& S)
{
  return (S.Direction());
}

inline occ::handle<Adaptor3d_Curve> BRepApprox_SurfaceTool::BasisCurve(const ::model::adapter::BRepAdaptor_Surface& S)
{
  return (S.BasisCurve());
}
