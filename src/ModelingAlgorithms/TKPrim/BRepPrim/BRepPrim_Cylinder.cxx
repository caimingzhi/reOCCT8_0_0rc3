#include <BRepPrim_Cylinder.hpp>
#include <Geom2d_Line.hpp>
#include <Geom_CylindricalSurface.hpp>
#include <Geom_Line.hpp>
#include <gp.hpp>
#include <gp_Ax2.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <Precision.hpp>
#include <TopoDS_Face.hpp>

BRepPrim_Cylinder::BRepPrim_Cylinder(const gp_Ax2& Position,
                                     const double  Radius,
                                     const double  Height)
    : BRepPrim_Revolution(Position, 0, Height),
      myRadius(Radius)
{
  SetMeridian();
}

BRepPrim_Cylinder::BRepPrim_Cylinder(const double Radius)
    : BRepPrim_Revolution(gp::XOY(), RealFirst(), RealLast()),
      myRadius(Radius)
{
  SetMeridian();
}

BRepPrim_Cylinder::BRepPrim_Cylinder(const gp_Pnt& Center, const double Radius)
    : BRepPrim_Revolution(gp_Ax2(Center, gp_Dir(gp_Dir::D::Z), gp_Dir(gp_Dir::D::X)),
                          RealFirst(),
                          RealLast()),
      myRadius(Radius)
{
  SetMeridian();
}

BRepPrim_Cylinder::BRepPrim_Cylinder(const gp_Ax2& Axes, const double Radius)
    : BRepPrim_Revolution(Axes, RealFirst(), RealLast()),
      myRadius(Radius)
{
  SetMeridian();
}

BRepPrim_Cylinder::BRepPrim_Cylinder(const double R, const double H)
    : BRepPrim_Revolution(gp::XOY(), 0, H),
      myRadius(R)
{
  SetMeridian();
}

BRepPrim_Cylinder::BRepPrim_Cylinder(const gp_Pnt& Center, const double R, const double H)
    : BRepPrim_Revolution(gp_Ax2(Center, gp_Dir(gp_Dir::D::Z), gp_Dir(gp_Dir::D::X)), 0, H),
      myRadius(R)
{
  SetMeridian();
}

TopoDS_Face BRepPrim_Cylinder::MakeEmptyLateralFace() const
{
  occ::handle<Geom_CylindricalSurface> C = new Geom_CylindricalSurface(Axes(), myRadius);
  TopoDS_Face                          F;
  myBuilder.Builder().MakeFace(F, C, Precision::Confusion());
  return F;
}

void BRepPrim_Cylinder::SetMeridian()
{
  gp_Vec V = Axes().XDirection();
  V.Multiply(myRadius);
  gp_Ax1 A = Axes().Axis();
  A.Translate(V);
  occ::handle<Geom_Line>   L   = new Geom_Line(A);
  occ::handle<Geom2d_Line> L2d = new Geom2d_Line(gp_Pnt2d(myRadius, 0), gp_Dir2d(gp_Dir2d::D::Y));
  Meridian(L, L2d);
}
