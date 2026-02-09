#include <BRepPrimAPI_MakeTorus.hpp>
#include <gp_Ax2.hpp>

BRepPrimAPI_MakeTorus::BRepPrimAPI_MakeTorus(const double R1, const double R2)
    : myTorus(R1, R2)
{
}

BRepPrimAPI_MakeTorus::BRepPrimAPI_MakeTorus(const double R1, const double R2, const double angle)
    : myTorus(R1, R2)
{
  myTorus.Angle(angle);
}

BRepPrimAPI_MakeTorus::BRepPrimAPI_MakeTorus(const double R1,
                                             const double R2,
                                             const double angle1,
                                             const double angle2)
    : myTorus(R1, R2)
{
  myTorus.VMin(angle1);
  myTorus.VMax(angle2);
}

BRepPrimAPI_MakeTorus::BRepPrimAPI_MakeTorus(const double R1,
                                             const double R2,
                                             const double angle1,
                                             const double angle2,
                                             const double angle)
    : myTorus(R1, R2)
{
  myTorus.VMin(angle1);
  myTorus.VMax(angle2);
  myTorus.Angle(angle);
}

BRepPrimAPI_MakeTorus::BRepPrimAPI_MakeTorus(const gp_Ax2& Axes, const double R1, const double R2)
    : myTorus(Axes, R1, R2)
{
}

BRepPrimAPI_MakeTorus::BRepPrimAPI_MakeTorus(const gp_Ax2& Axes,
                                             const double  R1,
                                             const double  R2,
                                             const double  angle)
    : myTorus(Axes, R1, R2)
{
  myTorus.Angle(angle);
}

BRepPrimAPI_MakeTorus::BRepPrimAPI_MakeTorus(const gp_Ax2& Axes,
                                             const double  R1,
                                             const double  R2,
                                             const double  angle1,
                                             const double  angle2)
    : myTorus(Axes, R1, R2)
{
  myTorus.VMin(angle1);
  myTorus.VMax(angle2);
}

BRepPrimAPI_MakeTorus::BRepPrimAPI_MakeTorus(const gp_Ax2& Axes,
                                             const double  R1,
                                             const double  R2,
                                             const double  angle1,
                                             const double  angle2,
                                             const double  angle)
    : myTorus(Axes, R1, R2)
{
  myTorus.VMin(angle1);
  myTorus.VMax(angle2);
  myTorus.Angle(angle);
}

void* BRepPrimAPI_MakeTorus::OneAxis()
{
  return &myTorus;
}

BRepPrim_Torus& BRepPrimAPI_MakeTorus::Torus()
{
  return myTorus;
}
