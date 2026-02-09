#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <BRepCheck_Result.hpp>
class TopoDS_Solid;
class TopoDS_Shape;

class BRepCheck_Solid : public BRepCheck_Result
{

public:
  Standard_EXPORT BRepCheck_Solid(const TopoDS_Solid& theS);

  Standard_EXPORT void InContext(const TopoDS_Shape& theContextShape) override;

  Standard_EXPORT void Minimum() override;

  Standard_EXPORT void Blind() override;

  DEFINE_STANDARD_RTTIEXT(BRepCheck_Solid, BRepCheck_Result)
};
