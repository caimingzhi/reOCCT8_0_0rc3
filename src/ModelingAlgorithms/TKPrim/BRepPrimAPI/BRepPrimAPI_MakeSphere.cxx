#include <BRepBuilderAPI.hpp>
#include <BRepPrimAPI_MakeSphere.hpp>
#include <gp.hpp>
#include <gp_Ax2.hpp>
#include <gp_Dir.hpp>
#include <gp_Pnt.hpp>

BRepPrimAPI_MakeSphere::BRepPrimAPI_MakeSphere(const double R)
    : mySphere(gp::XOY(), R)
{
}

BRepPrimAPI_MakeSphere::BRepPrimAPI_MakeSphere(const double R, const double angle)
    : mySphere(gp_Ax2(gp::Origin(), (angle < 0. ? -1 : 1) * gp::DZ(), gp::DX()), R)
{
  mySphere.Angle(std::abs(angle));
}

BRepPrimAPI_MakeSphere::BRepPrimAPI_MakeSphere(const double R,
                                               const double angle1,
                                               const double angle2)
    : mySphere(R)
{
  mySphere.VMin(angle1);
  mySphere.VMax(angle2);
}

BRepPrimAPI_MakeSphere::BRepPrimAPI_MakeSphere(const double R,
                                               const double angle1,
                                               const double angle2,
                                               const double angle3)
    : mySphere(R)
{
  mySphere.VMin(angle1);
  mySphere.VMax(angle2);
  mySphere.Angle(angle3);
}

BRepPrimAPI_MakeSphere::BRepPrimAPI_MakeSphere(const gp_Pnt& Center, const double R)
    : mySphere(gp_Ax2(Center, gp_Dir(gp_Dir::D::Z), gp_Dir(gp_Dir::D::X)), R)
{
}

BRepPrimAPI_MakeSphere::BRepPrimAPI_MakeSphere(const gp_Pnt& Center,
                                               const double  R,
                                               const double  angle)
    : mySphere(gp_Ax2(Center, gp_Dir(gp_Dir::D::Z), gp_Dir(gp_Dir::D::X)), R)
{
  mySphere.Angle(angle);
}

BRepPrimAPI_MakeSphere::BRepPrimAPI_MakeSphere(const gp_Pnt& Center,
                                               const double  R,
                                               const double  angle1,
                                               const double  angle2)
    : mySphere(gp_Ax2(Center, gp_Dir(gp_Dir::D::Z), gp_Dir(gp_Dir::D::X)), R)
{
  mySphere.VMin(angle1);
  mySphere.VMax(angle2);
}

BRepPrimAPI_MakeSphere::BRepPrimAPI_MakeSphere(const gp_Pnt& Center,
                                               const double  R,
                                               const double  angle1,
                                               const double  angle2,
                                               const double  angle3)
    : mySphere(gp_Ax2(Center, gp_Dir(gp_Dir::D::Z), gp_Dir(gp_Dir::D::X)), R)
{
  mySphere.VMin(angle1);
  mySphere.VMax(angle2);
  mySphere.Angle(angle3);
}

BRepPrimAPI_MakeSphere::BRepPrimAPI_MakeSphere(const gp_Ax2& Axis, const double R)
    : mySphere(Axis, R)
{
}

BRepPrimAPI_MakeSphere::BRepPrimAPI_MakeSphere(const gp_Ax2& Axis,
                                               const double  R,
                                               const double  angle)
    : mySphere(Axis, R)
{
  mySphere.Angle(angle);
}

BRepPrimAPI_MakeSphere::BRepPrimAPI_MakeSphere(const gp_Ax2& Axis,
                                               const double  R,
                                               const double  angle1,
                                               const double  angle2)
    : mySphere(Axis, R)
{
  mySphere.VMin(angle1);
  mySphere.VMax(angle2);
}

BRepPrimAPI_MakeSphere::BRepPrimAPI_MakeSphere(const gp_Ax2& Axis,
                                               const double  R,
                                               const double  angle1,
                                               const double  angle2,
                                               const double  angle3)
    : mySphere(Axis, R)
{
  mySphere.VMin(angle1);
  mySphere.VMax(angle2);
  mySphere.Angle(angle3);
}

void* BRepPrimAPI_MakeSphere::OneAxis()
{
  return &mySphere;
}

BRepPrim_Sphere& BRepPrimAPI_MakeSphere::Sphere()
{
  return mySphere;
}
