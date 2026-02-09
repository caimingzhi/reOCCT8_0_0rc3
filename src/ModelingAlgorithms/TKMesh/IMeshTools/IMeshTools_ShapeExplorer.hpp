#pragma once

#include <IMeshData_Shape.hpp>
#include <Standard_Type.hpp>
#include <IMeshTools_ShapeVisitor.hpp>
#include <TopoDS_Shape.hpp>

class IMeshTools_ShapeExplorer : public IMeshData_Shape
{
public:
  Standard_EXPORT IMeshTools_ShapeExplorer(const TopoDS_Shape& theShape);

  Standard_EXPORT ~IMeshTools_ShapeExplorer() override;

  Standard_EXPORT virtual void Accept(const occ::handle<IMeshTools_ShapeVisitor>& theVisitor);

  DEFINE_STANDARD_RTTIEXT(IMeshTools_ShapeExplorer, IMeshData_Shape)
};
