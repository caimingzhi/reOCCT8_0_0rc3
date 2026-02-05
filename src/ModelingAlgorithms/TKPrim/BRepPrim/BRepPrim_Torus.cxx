#include <BRepPrim_Torus.hpp>
#include <Geom2d_Circle.hpp>
#include <Geom_Circle.hpp>
#include <Geom_ToroidalSurface.hpp>
#include <gp.hpp>
#include <gp_Ax2.hpp>
#include <gp_Ax2d.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <Precision.hpp>
#include <TopoDS_Face.hpp>

//=================================================================================================

BRepPrim_Torus::BRepPrim_Torus(const gp_Ax2& Position, const double Major, const double Minor)
    : BRepPrim_Revolution(Position, 0, 2 * M_PI),
      myMajor(Major),
      myMinor(Minor)
{
  SetMeridian();
}

//=================================================================================================

BRepPrim_Torus::BRepPrim_Torus(const double Major, const double Minor)
    : BRepPrim_Revolution(gp::XOY(), 0, 2 * M_PI),
      myMajor(Major),
      myMinor(Minor)
{
  SetMeridian();
}

//=================================================================================================

BRepPrim_Torus::BRepPrim_Torus(const gp_Pnt& Center, const double Major, const double Minor)
    : BRepPrim_Revolution(gp_Ax2(Center, gp_Dir(gp_Dir::D::Z), gp_Dir(gp_Dir::D::X)), 0, 2 * M_PI),
      myMajor(Major),
      myMinor(Minor)
{
  SetMeridian();
}

//=================================================================================================

TopoDS_Face BRepPrim_Torus::MakeEmptyLateralFace() const
{
  occ::handle<Geom_ToroidalSurface> T = new Geom_ToroidalSurface(Axes(), myMajor, myMinor);
  TopoDS_Face                       F;
  myBuilder.Builder().MakeFace(F, T, Precision::Confusion());
  return F;
}

//=================================================================================================

void BRepPrim_Torus::SetMeridian()
{
  gp_Dir D = Axes().YDirection();
  D.Reverse();
  gp_Ax2 A(Axes().Location(), D, Axes().XDirection());
  gp_Vec V = Axes().XDirection();
  V.Multiply(myMajor);
  A.Translate(V);
  occ::handle<Geom_Circle>   C = new Geom_Circle(A, myMinor);
  occ::handle<Geom2d_Circle> C2d =
    new Geom2d_Circle(gp_Ax2d(gp_Pnt2d(myMajor, 0), gp_Dir2d(gp_Dir2d::D::X)), myMinor);
  Meridian(C, C2d);
}
