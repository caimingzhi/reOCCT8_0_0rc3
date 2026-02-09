#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BRepPrim_Torus.hpp>
#include <BRepPrimAPI_MakeOneAxis.hpp>
class gp_Ax2;

class BRepPrimAPI_MakeTorus : public BRepPrimAPI_MakeOneAxis
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepPrimAPI_MakeTorus(const double R1, const double R2);

  Standard_EXPORT BRepPrimAPI_MakeTorus(const double R1, const double R2, const double angle);

  Standard_EXPORT BRepPrimAPI_MakeTorus(const double R1,
                                        const double R2,
                                        const double angle1,
                                        const double angle2);

  Standard_EXPORT BRepPrimAPI_MakeTorus(const double R1,
                                        const double R2,
                                        const double angle1,
                                        const double angle2,
                                        const double angle);

  Standard_EXPORT BRepPrimAPI_MakeTorus(const gp_Ax2& Axes, const double R1, const double R2);

  Standard_EXPORT BRepPrimAPI_MakeTorus(const gp_Ax2& Axes,
                                        const double  R1,
                                        const double  R2,
                                        const double  angle);

  Standard_EXPORT BRepPrimAPI_MakeTorus(const gp_Ax2& Axes,
                                        const double  R1,
                                        const double  R2,
                                        const double  angle1,
                                        const double  angle2);

  Standard_EXPORT BRepPrimAPI_MakeTorus(const gp_Ax2& Axes,
                                        const double  R1,
                                        const double  R2,
                                        const double  angle1,
                                        const double  angle2,
                                        const double  angle);

  Standard_EXPORT void* OneAxis() override;

  Standard_EXPORT BRepPrim_Torus& Torus();

private:
  BRepPrim_Torus myTorus;
};
