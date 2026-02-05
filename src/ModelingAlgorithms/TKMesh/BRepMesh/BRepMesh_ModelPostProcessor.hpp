#pragma once

#include <IMeshTools_ModelAlgo.hpp>
#include <IMeshData_Types.hpp>

//! Class implements functionality of model post-processing tool.
//! Stores polygons on triangulations to TopoDS_Edge.
class BRepMesh_ModelPostProcessor : public IMeshTools_ModelAlgo
{
public:
  //! Constructor.
  Standard_EXPORT BRepMesh_ModelPostProcessor();

  //! Destructor.
  Standard_EXPORT ~BRepMesh_ModelPostProcessor() override;

  DEFINE_STANDARD_RTTIEXT(BRepMesh_ModelPostProcessor, IMeshTools_ModelAlgo)

protected:
  //! Performs processing of edges of the given model.
  Standard_EXPORT bool performInternal(const occ::handle<IMeshData_Model>& theModel,
                                       const IMeshTools_Parameters&        theParameters,
                                       const Message_ProgressRange&        theRange) override;
};
