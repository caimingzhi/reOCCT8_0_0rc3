#include <BRepPrim_Cone.hpp>
#include <Geom2d_Line.hpp>
#include <Geom_ConicalSurface.hpp>
#include <Geom_Line.hpp>
#include <gp.hpp>
#include <gp_Ax2.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <Precision.hpp>
#include <Standard_DomainError.hpp>
#include <TopoDS_Face.hpp>

BRepPrim_Cone::BRepPrim_Cone(const double  Angle,
                             const gp_Ax2& Position,
                             const double  Height,
                             const double  Radius)
    : BRepPrim_Revolution(Position, 0, 0),
      myHalfAngle(Angle),
      myRadius(Radius)
{
  if (Height < Precision::Confusion())
    throw Standard_DomainError("cone with null height");
  if (myHalfAngle * Height < Precision::Confusion())
    throw Standard_DomainError("cone with null angle");
  if ((M_PI / 2 - myHalfAngle) * Height < Precision::Confusion())
    throw Standard_DomainError("cone with angle > PI/2");

  VMax(Height / std::cos(myHalfAngle));
  VMin(0.);
  SetMeridian();
}

BRepPrim_Cone::BRepPrim_Cone(const double Angle)
    : BRepPrim_Revolution(gp::XOY(), 0, RealLast()),
      myHalfAngle(Angle),
      myRadius(0.)
{
  if ((Angle < 0) || (Angle > M_PI / 2))
    throw Standard_DomainError("cone with angle <0 or > PI/2");
  VMin(0.);
  SetMeridian();
}

BRepPrim_Cone::BRepPrim_Cone(const double Angle, const gp_Pnt& Apex)
    : BRepPrim_Revolution(gp_Ax2(Apex, gp_Dir(gp_Dir::D::Z), gp_Dir(gp_Dir::D::X)), 0, RealLast()),
      myHalfAngle(Angle),
      myRadius(0.)
{
  if ((Angle < 0) || (Angle > M_PI / 2))
    throw Standard_DomainError("cone with angle <0 or > PI/2");
  VMin(0.);
  SetMeridian();
}

BRepPrim_Cone::BRepPrim_Cone(const double Angle, const gp_Ax2& Axes)
    : BRepPrim_Revolution(Axes, 0, RealLast()),
      myHalfAngle(Angle)
{
  if ((Angle < 0) || (Angle > M_PI / 2))
    throw Standard_DomainError("cone with angle <0 or > PI/2");
  VMin(0.);
  SetMeridian();
}

BRepPrim_Cone::BRepPrim_Cone(const double R1, const double R2, const double H)
    : BRepPrim_Revolution(gp::XOY(), 0, 0)
{
  SetParameters(R1, R2, H);
  SetMeridian();
}

BRepPrim_Cone::BRepPrim_Cone(const gp_Pnt& Center, const double R1, const double R2, const double H)
    : BRepPrim_Revolution(gp_Ax2(Center, gp_Dir(gp_Dir::D::Z), gp_Dir(gp_Dir::D::X)), 0, 0)
{
  SetParameters(R1, R2, H);
  SetMeridian();
}

BRepPrim_Cone::BRepPrim_Cone(const gp_Ax2& Axes, const double R1, const double R2, const double H)
    : BRepPrim_Revolution(Axes, 0, 0)
{
  SetParameters(R1, R2, H);
  SetMeridian();
}

TopoDS_Face BRepPrim_Cone::MakeEmptyLateralFace() const
{
  occ::handle<Geom_ConicalSurface> C = new Geom_ConicalSurface(Axes(), myHalfAngle, myRadius);
  TopoDS_Face                      F;
  myBuilder.Builder().MakeFace(F, C, Precision::Confusion());
  return F;
}

void BRepPrim_Cone::SetMeridian()
{
  gp_Ax1 A = Axes().Axis();
  A.Rotate(gp_Ax1(Axes().Location(), Axes().YDirection()), myHalfAngle);
  gp_Vec V(Axes().XDirection());
  V *= myRadius;
  A.Translate(V);
  occ::handle<Geom_Line>   L = new Geom_Line(A);
  occ::handle<Geom2d_Line> L2d =
    new Geom2d_Line(gp_Pnt2d(myRadius, 0), gp_Dir2d(std::sin(myHalfAngle), std::cos(myHalfAngle)));
  Meridian(L, L2d);
}

void BRepPrim_Cone::SetParameters(const double R1, const double R2, const double H)
{
  if (((R1 != 0) && (R1 < Precision::Confusion())) || ((R2 != 0) && (R2 < Precision::Confusion())))
    throw Standard_DomainError("cone with negative or too small radius");
  if (std::abs(R1 - R2) < Precision::Confusion())
    throw Standard_DomainError("cone with two identic radii");
  if (H < Precision::Confusion())
    throw Standard_DomainError("cone with negative or null height");

  myRadius    = R1;
  myHalfAngle = std::atan((R2 - R1) / H);

  VMin(0.);
  VMax(std::sqrt(H * H + (R2 - R1) * (R2 - R1)));
}
