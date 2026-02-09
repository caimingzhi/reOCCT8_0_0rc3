#pragma once

#include <Draw_Interpretor.hpp>
#include <Geom_Geometry.hpp>
#include <Geom_Surface.hpp>
#include <Geom2d_Curve.hpp>

class Geom_BezierCurve;
class Geom_BezierSurface;
class Geom_BSplineCurve;
class Geom_BSplineSurface;
class Geom2d_BezierCurve;
class Geom2d_BSplineCurve;
class Poly_Polygon2D;
class Poly_Polygon3D;
class Poly_Triangulation;
struct DrawTrSurf_Params;

class DrawTrSurf
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void Set(const char* Name, const gp_Pnt& G);

  Standard_EXPORT static void Set(const char* Name, const gp_Pnt2d& G);

  Standard_EXPORT static void Set(const char*                       Name,
                                  const occ::handle<Geom_Geometry>& G,
                                  const bool                        isSenseMarker = true);

  template <class T>
  static void Set(const char*           Name,
                  const occ::handle<T>& Arg,
                  typename opencascade::std::enable_if<
                    opencascade::std::is_base_of<Geom_Geometry, T>::value>::type* = nullptr)
  {
    Set(Name, (const occ::handle<Geom_Geometry>&)Arg);
  }

  Standard_EXPORT static void Set(const char*                      Name,
                                  const occ::handle<Geom2d_Curve>& C,
                                  const bool                       isSenseMarker = true);

  template <class T>
  static void Set(const char*           Name,
                  const occ::handle<T>& Arg,
                  typename opencascade::std::enable_if<
                    opencascade::std::is_base_of<Geom2d_Curve, T>::value>::type* = nullptr)
  {
    Set(Name, (const occ::handle<Geom2d_Curve>&)Arg);
  }

  Standard_EXPORT static void Set(const char* Name, const occ::handle<Poly_Triangulation>& T);

  Standard_EXPORT static void Set(const char* Name, const occ::handle<Poly_Polygon3D>& P);

  Standard_EXPORT static void Set(const char* Name, const occ::handle<Poly_Polygon2D>& P);

  Standard_EXPORT static occ::handle<Geom_Geometry> Get(const char*& Name);

  Standard_EXPORT static bool GetPoint(const char*& Name, gp_Pnt& P);

  Standard_EXPORT static bool GetPoint2d(const char*& Name, gp_Pnt2d& P);

  Standard_EXPORT static occ::handle<Geom_Curve> GetCurve(const char*& Name);

  Standard_EXPORT static occ::handle<Geom_BezierCurve> GetBezierCurve(const char*& Name);

  Standard_EXPORT static occ::handle<Geom_BSplineCurve> GetBSplineCurve(const char*& Name);

  Standard_EXPORT static occ::handle<Geom2d_Curve> GetCurve2d(const char*& Name);

  Standard_EXPORT static occ::handle<Geom2d_BezierCurve> GetBezierCurve2d(const char*& Name);

  Standard_EXPORT static occ::handle<Geom2d_BSplineCurve> GetBSplineCurve2d(const char*& Name);

  Standard_EXPORT static occ::handle<Geom_Surface> GetSurface(const char*& Name);

  Standard_EXPORT static occ::handle<Geom_BezierSurface> GetBezierSurface(const char*& Name);

  Standard_EXPORT static occ::handle<Geom_BSplineSurface> GetBSplineSurface(const char*& Name);

  Standard_EXPORT static occ::handle<Poly_Triangulation> GetTriangulation(const char*& Name);

  Standard_EXPORT static occ::handle<Poly_Polygon3D> GetPolygon3D(const char*& Name);

  Standard_EXPORT static occ::handle<Poly_Polygon2D> GetPolygon2D(const char*& Name);

  Standard_EXPORT static DrawTrSurf_Params& Parameters();

  Standard_EXPORT static void BasicCommands(Draw_Interpretor& I);
};
