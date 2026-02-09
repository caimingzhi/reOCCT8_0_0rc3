#pragma once

#include <IMeshTools_ModelAlgo.hpp>
#include <IMeshData_Types.hpp>

class BRepMesh_ModelPreProcessor : public IMeshTools_ModelAlgo
{
public:
  Standard_EXPORT BRepMesh_ModelPreProcessor();

  Standard_EXPORT ~BRepMesh_ModelPreProcessor() override;

  DEFINE_STANDARD_RTTIEXT(BRepMesh_ModelPreProcessor, IMeshTools_ModelAlgo)

protected:
  Standard_EXPORT bool performInternal(const occ::handle<IMeshData_Model>& theModel,
                                       const IMeshTools_Parameters&        theParameters,
                                       const Message_ProgressRange&        theRange) override;
};
