#pragma once


#include <IMeshTools_ModelBuilder.hpp>
#include <Standard_Type.hpp>
#include <TopoDS_Shape.hpp>

//! Class implements interface representing tool for discrete model building.
//!
//! The following statuses should be used by default:
//! Message_Done1 - model has been successfully built.
//! Message_Fail1 - empty shape.
//! Message_Fail2 - model has not been build due to unexpected reason.
class BRepMesh_ModelBuilder : public IMeshTools_ModelBuilder
{
public:
  //! Constructor.
  Standard_EXPORT BRepMesh_ModelBuilder();

  //! Destructor.
  Standard_EXPORT ~BRepMesh_ModelBuilder() override;

  DEFINE_STANDARD_RTTIEXT(BRepMesh_ModelBuilder, IMeshTools_ModelBuilder)

protected:
  //! Creates discrete model for the given shape.
  //! Returns nullptr in case of failure.
  Standard_EXPORT occ::handle<IMeshData_Model> performInternal(
    const TopoDS_Shape&          theShape,
    const IMeshTools_Parameters& theParameters) override;
};

