#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <BRepPrim_Sphere.hpp>
#include <BRepPrimAPI_MakeOneAxis.hpp>
class gp_Pnt;
class gp_Ax2;

class BRepPrimAPI_MakeSphere : public BRepPrimAPI_MakeOneAxis
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepPrimAPI_MakeSphere(const double R);

  Standard_EXPORT BRepPrimAPI_MakeSphere(const double R, const double angle);

  Standard_EXPORT BRepPrimAPI_MakeSphere(const double R, const double angle1, const double angle2);

  Standard_EXPORT BRepPrimAPI_MakeSphere(const double R,
                                         const double angle1,
                                         const double angle2,
                                         const double angle3);

  Standard_EXPORT BRepPrimAPI_MakeSphere(const gp_Pnt& Center, const double R);

  Standard_EXPORT BRepPrimAPI_MakeSphere(const gp_Pnt& Center, const double R, const double angle);

  Standard_EXPORT BRepPrimAPI_MakeSphere(const gp_Pnt& Center,
                                         const double  R,
                                         const double  angle1,
                                         const double  angle2);

  Standard_EXPORT BRepPrimAPI_MakeSphere(const gp_Pnt& Center,
                                         const double  R,
                                         const double  angle1,
                                         const double  angle2,
                                         const double  angle3);

  Standard_EXPORT BRepPrimAPI_MakeSphere(const gp_Ax2& Axis, const double R);

  Standard_EXPORT BRepPrimAPI_MakeSphere(const gp_Ax2& Axis, const double R, const double angle);

  Standard_EXPORT BRepPrimAPI_MakeSphere(const gp_Ax2& Axis,
                                         const double  R,
                                         const double  angle1,
                                         const double  angle2);

  Standard_EXPORT BRepPrimAPI_MakeSphere(const gp_Ax2& Axis,
                                         const double  R,
                                         const double  angle1,
                                         const double  angle2,
                                         const double  angle3);

  Standard_EXPORT void* OneAxis() override;

  Standard_EXPORT BRepPrim_Sphere& Sphere();

private:
  BRepPrim_Sphere mySphere;
};
