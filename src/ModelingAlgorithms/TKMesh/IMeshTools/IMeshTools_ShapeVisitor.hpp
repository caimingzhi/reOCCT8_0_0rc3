#pragma once

#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>

class TopoDS_Face;
class TopoDS_Edge;

class IMeshTools_ShapeVisitor : public Standard_Transient
{
public:
  ~IMeshTools_ShapeVisitor() override = default;

  Standard_EXPORT virtual void Visit(const TopoDS_Face& theFace) = 0;

  Standard_EXPORT virtual void Visit(const TopoDS_Edge& theEdge) = 0;

  DEFINE_STANDARD_RTTIEXT(IMeshTools_ShapeVisitor, Standard_Transient)

protected:
  IMeshTools_ShapeVisitor() {}
};
