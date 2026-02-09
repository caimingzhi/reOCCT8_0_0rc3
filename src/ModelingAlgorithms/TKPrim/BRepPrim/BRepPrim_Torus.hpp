#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BRepPrim_Revolution.hpp>
class gp_Ax2;
class gp_Pnt;
class TopoDS_Face;

class BRepPrim_Torus : public BRepPrim_Revolution
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepPrim_Torus(const gp_Ax2& Position, const double Major, const double Minor);

  Standard_EXPORT BRepPrim_Torus(const double Major, const double Minor);

  Standard_EXPORT BRepPrim_Torus(const gp_Pnt& Center, const double Major, const double Minor);

  Standard_EXPORT TopoDS_Face MakeEmptyLateralFace() const override;

private:
  Standard_EXPORT void SetMeridian();

  double myMajor;
  double myMinor;
};
