#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <BRepCheck_Result.hpp>
class TopoDS_Vertex;
class TopoDS_Shape;

class BRepCheck_Vertex : public BRepCheck_Result
{

public:
  Standard_EXPORT BRepCheck_Vertex(const TopoDS_Vertex& V);

  Standard_EXPORT void InContext(const TopoDS_Shape& ContextShape) override;

  Standard_EXPORT void Minimum() override;

  Standard_EXPORT void Blind() override;

  Standard_EXPORT double Tolerance();

  DEFINE_STANDARD_RTTIEXT(BRepCheck_Vertex, BRepCheck_Result)
};
