#include <BRepBuilderAPI.hpp>
#include <BRepPrim_Revolution.hpp>
#include <BRepPrimAPI_MakeRevolution.hpp>
#include <Geom2d_Curve.hpp>
#include <Geom_Curve.hpp>
#include <Geom_Plane.hpp>
#include <GeomProjLib.hpp>
#include <gp_Ax2.hpp>

//=================================================================================================

static occ::handle<Geom2d_Curve> Project(const occ::handle<Geom_Curve>& M, const gp_Ax3& Axis)
{
  occ::handle<Geom2d_Curve> C;
  C = GeomProjLib::Curve2d(M, new Geom_Plane(Axis));
  return C;
}

static occ::handle<Geom2d_Curve> Project(const occ::handle<Geom_Curve>& M)
{
  return Project(M, gp_Ax2(gp::Origin(), -gp::DY(), gp::DX()));
}

//=================================================================================================

BRepPrimAPI_MakeRevolution::BRepPrimAPI_MakeRevolution(const occ::handle<Geom_Curve>& Meridian)
    : myRevolution(gp::XOY(),
                   Meridian->FirstParameter(),
                   Meridian->LastParameter(),
                   Meridian,
                   Project(Meridian))
{
}

//=================================================================================================

BRepPrimAPI_MakeRevolution::BRepPrimAPI_MakeRevolution(const occ::handle<Geom_Curve>& Meridian,
                                                       const double                   angle)
    : myRevolution(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(gp_Dir::D::Z), gp_Dir(gp_Dir::D::X)),
                   Meridian->FirstParameter(),
                   Meridian->LastParameter(),
                   Meridian,
                   Project(Meridian))
{
  myRevolution.Angle(angle);
}

//=================================================================================================

BRepPrimAPI_MakeRevolution::BRepPrimAPI_MakeRevolution(const occ::handle<Geom_Curve>& Meridian,
                                                       const double                   VMin,
                                                       const double                   VMax)
    : myRevolution(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(gp_Dir::D::Z), gp_Dir(gp_Dir::D::X)),
                   VMin,
                   VMax,
                   Meridian,
                   Project(Meridian))
{
}

//=================================================================================================

BRepPrimAPI_MakeRevolution::BRepPrimAPI_MakeRevolution(const occ::handle<Geom_Curve>& Meridian,
                                                       const double                   VMin,
                                                       const double                   VMax,
                                                       const double                   angle)
    : myRevolution(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(gp_Dir::D::Z), gp_Dir(gp_Dir::D::X)),
                   VMin,
                   VMax,
                   Meridian,
                   Project(Meridian))
{
  myRevolution.Angle(angle);
}

//=================================================================================================

BRepPrimAPI_MakeRevolution::BRepPrimAPI_MakeRevolution(const gp_Ax2&                  Axes,
                                                       const occ::handle<Geom_Curve>& Meridian)
    : myRevolution(Axes,
                   Meridian->FirstParameter(),
                   Meridian->LastParameter(),
                   Meridian,
                   Project(Meridian))
{
}

//=================================================================================================

BRepPrimAPI_MakeRevolution::BRepPrimAPI_MakeRevolution(const gp_Ax2&                  Axes,
                                                       const occ::handle<Geom_Curve>& Meridian,
                                                       const double                   angle)
    : myRevolution(Axes,
                   Meridian->FirstParameter(),
                   Meridian->LastParameter(),
                   Meridian,
                   Project(Meridian))
{
  myRevolution.Angle(angle);
}

//=================================================================================================

BRepPrimAPI_MakeRevolution::BRepPrimAPI_MakeRevolution(const gp_Ax2&                  Axes,
                                                       const occ::handle<Geom_Curve>& Meridian,
                                                       const double                   VMin,
                                                       const double                   VMax)
    : myRevolution(Axes, VMin, VMax, Meridian, Project(Meridian))
{
}

//=================================================================================================

BRepPrimAPI_MakeRevolution::BRepPrimAPI_MakeRevolution(const gp_Ax2&                  Axes,
                                                       const occ::handle<Geom_Curve>& Meridian,
                                                       const double                   VMin,
                                                       const double                   VMax,
                                                       const double                   angle)
    : myRevolution(Axes, VMin, VMax, Meridian, Project(Meridian))
{
  myRevolution.Angle(angle);
}

//=================================================================================================

void* BRepPrimAPI_MakeRevolution::OneAxis()
{
  return &myRevolution;
}

//=================================================================================================

BRepPrim_Revolution& BRepPrimAPI_MakeRevolution::Revolution()
{
  return myRevolution;
}
