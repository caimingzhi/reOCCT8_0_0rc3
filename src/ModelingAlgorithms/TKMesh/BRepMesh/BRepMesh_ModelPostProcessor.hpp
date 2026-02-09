#pragma once

#include <IMeshTools_ModelAlgo.hpp>
#include <IMeshData_Types.hpp>

class BRepMesh_ModelPostProcessor : public IMeshTools_ModelAlgo
{
public:
  Standard_EXPORT BRepMesh_ModelPostProcessor();

  Standard_EXPORT ~BRepMesh_ModelPostProcessor() override;

  DEFINE_STANDARD_RTTIEXT(BRepMesh_ModelPostProcessor, IMeshTools_ModelAlgo)

protected:
  Standard_EXPORT bool performInternal(const occ::handle<IMeshData_Model>& theModel,
                                       const IMeshTools_Parameters&        theParameters,
                                       const Message_ProgressRange&        theRange) override;
};
