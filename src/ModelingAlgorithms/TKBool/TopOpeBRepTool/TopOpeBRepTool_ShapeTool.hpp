#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class TopoDS_Shape;
class gp_Pnt;
class Geom_Curve;
class TopoDS_Edge;
class Geom_Surface;
class TopoDS_Face;
class BRepAdaptor_Surface;
class BRepAdaptor_Curve;
class gp_Dir;

class TopOpeBRepTool_ShapeTool
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static double Tolerance(const TopoDS_Shape& S);

  Standard_EXPORT static gp_Pnt Pnt(const TopoDS_Shape& S);

  Standard_EXPORT static occ::handle<Geom_Curve> BASISCURVE(const occ::handle<Geom_Curve>& C);

  Standard_EXPORT static occ::handle<Geom_Curve> BASISCURVE(const TopoDS_Edge& E);

  Standard_EXPORT static occ::handle<Geom_Surface> BASISSURFACE(const occ::handle<Geom_Surface>& S);

  Standard_EXPORT static occ::handle<Geom_Surface> BASISSURFACE(const TopoDS_Face& F);

  Standard_EXPORT static void UVBOUNDS(const occ::handle<Geom_Surface>& S,
                                       bool&                            UPeri,
                                       bool&                            VPeri,
                                       double&                          Umin,
                                       double&                          Umax,
                                       double&                          Vmin,
                                       double&                          Vmax);

  Standard_EXPORT static void UVBOUNDS(const TopoDS_Face& F,
                                       bool&              UPeri,
                                       bool&              VPeri,
                                       double&            Umin,
                                       double&            Umax,
                                       double&            Vmin,
                                       double&            Vmax);

  Standard_EXPORT static void AdjustOnPeriodic(const TopoDS_Shape& S, double& u, double& v);

  Standard_EXPORT static bool Closed(const TopoDS_Shape& S1, const TopoDS_Shape& S2);

  Standard_EXPORT static double PeriodizeParameter(const double        par,
                                                   const TopoDS_Shape& EE,
                                                   const TopoDS_Shape& FF);

  Standard_EXPORT static bool ShapesSameOriented(const TopoDS_Shape& S1, const TopoDS_Shape& S2);

  Standard_EXPORT static bool SurfacesSameOriented(const BRepAdaptor_Surface& S1,
                                                   const BRepAdaptor_Surface& S2);

  Standard_EXPORT static bool FacesSameOriented(const TopoDS_Shape& F1, const TopoDS_Shape& F2);

  Standard_EXPORT static bool CurvesSameOriented(const BRepAdaptor_Curve& C1,
                                                 const BRepAdaptor_Curve& C2);

  Standard_EXPORT static bool EdgesSameOriented(const TopoDS_Shape& E1, const TopoDS_Shape& E2);

  Standard_EXPORT static double EdgeData(const BRepAdaptor_Curve& BRAC,
                                         const double             P,
                                         gp_Dir&                  T,
                                         gp_Dir&                  N,
                                         double&                  C);

  Standard_EXPORT static double EdgeData(const TopoDS_Shape& E,
                                         const double        P,
                                         gp_Dir&             T,
                                         gp_Dir&             N,
                                         double&             C);

  Standard_EXPORT static double Resolution3dU(const occ::handle<Geom_Surface>& SU,
                                              const double                     Tol2d);

  Standard_EXPORT static double Resolution3dV(const occ::handle<Geom_Surface>& SU,
                                              const double                     Tol2d);

  Standard_EXPORT static double Resolution3d(const occ::handle<Geom_Surface>& SU,
                                             const double                     Tol2d);

  Standard_EXPORT static double Resolution3d(const TopoDS_Face& F, const double Tol2d);
};
