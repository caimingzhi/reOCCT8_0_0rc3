#pragma once


#include <IMeshTools_ModelAlgo.hpp>
#include <IMeshData_Types.hpp>

//! Class implements functionality of model pre-processing tool.
//! Nullifies existing polygonal data in case if model elements
//! have IMeshData_Outdated status.
class BRepMesh_ModelPreProcessor : public IMeshTools_ModelAlgo
{
public:
  //! Constructor.
  Standard_EXPORT BRepMesh_ModelPreProcessor();

  //! Destructor.
  Standard_EXPORT ~BRepMesh_ModelPreProcessor() override;

  DEFINE_STANDARD_RTTIEXT(BRepMesh_ModelPreProcessor, IMeshTools_ModelAlgo)

protected:
  //! Performs processing of edges of the given model.
  Standard_EXPORT bool performInternal(const occ::handle<IMeshData_Model>& theModel,
                                       const IMeshTools_Parameters&        theParameters,
                                       const Message_ProgressRange&        theRange) override;
};

