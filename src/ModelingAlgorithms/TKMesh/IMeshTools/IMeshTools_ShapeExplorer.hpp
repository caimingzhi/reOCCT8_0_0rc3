#pragma once

#include <IMeshData_Shape.hpp>
#include <Standard_Type.hpp>
#include <IMeshTools_ShapeVisitor.hpp>
#include <TopoDS_Shape.hpp>

//! Explores TopoDS_Shape for parts to be meshed - faces and free edges.
class IMeshTools_ShapeExplorer : public IMeshData_Shape
{
public:
  //! Constructor.
  Standard_EXPORT IMeshTools_ShapeExplorer(const TopoDS_Shape& theShape);

  //! Destructor.
  Standard_EXPORT ~IMeshTools_ShapeExplorer() override;

  //! Starts exploring of a shape.
  Standard_EXPORT virtual void Accept(const occ::handle<IMeshTools_ShapeVisitor>& theVisitor);

  DEFINE_STANDARD_RTTIEXT(IMeshTools_ShapeExplorer, IMeshData_Shape)
};
