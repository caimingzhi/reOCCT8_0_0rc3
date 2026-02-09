#pragma once

#include <IMeshTools_ModelBuilder.hpp>
#include <Standard_Type.hpp>
#include <TopoDS_Shape.hpp>

class BRepMesh_ModelBuilder : public IMeshTools_ModelBuilder
{
public:
  Standard_EXPORT BRepMesh_ModelBuilder();

  Standard_EXPORT ~BRepMesh_ModelBuilder() override;

  DEFINE_STANDARD_RTTIEXT(BRepMesh_ModelBuilder, IMeshTools_ModelBuilder)

protected:
  Standard_EXPORT occ::handle<IMeshData_Model> performInternal(
    const TopoDS_Shape&          theShape,
    const IMeshTools_Parameters& theParameters) override;
};
