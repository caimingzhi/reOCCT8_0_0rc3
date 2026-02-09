#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BRepPrim_Cone.hpp>
#include <BRepPrimAPI_MakeOneAxis.hpp>
class gp_Ax2;

class BRepPrimAPI_MakeCone : public BRepPrimAPI_MakeOneAxis
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepPrimAPI_MakeCone(const double R1, const double R2, const double H);

  Standard_EXPORT BRepPrimAPI_MakeCone(const double R1,
                                       const double R2,
                                       const double H,
                                       const double angle);

  Standard_EXPORT BRepPrimAPI_MakeCone(const gp_Ax2& Axes,
                                       const double  R1,
                                       const double  R2,
                                       const double  H);

  Standard_EXPORT BRepPrimAPI_MakeCone(const gp_Ax2& Axes,
                                       const double  R1,
                                       const double  R2,
                                       const double  H,
                                       const double  angle);

  Standard_EXPORT void* OneAxis() override;

  Standard_EXPORT BRepPrim_Cone& Cone();

private:
  BRepPrim_Cone myCone;
};
