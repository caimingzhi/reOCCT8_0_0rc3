#pragma once

#include <IMeshTools_ModelAlgo.hpp>
#include <IMeshTools_Parameters.hpp>
#include <IMeshTools_MeshAlgoFactory.hpp>

class BRepMesh_FaceDiscret : public IMeshTools_ModelAlgo
{
public:
  Standard_EXPORT BRepMesh_FaceDiscret(
    const occ::handle<IMeshTools_MeshAlgoFactory>& theAlgoFactory);

  Standard_EXPORT ~BRepMesh_FaceDiscret() override;

  DEFINE_STANDARD_RTTIEXT(BRepMesh_FaceDiscret, IMeshTools_ModelAlgo)

protected:
  Standard_EXPORT bool performInternal(const occ::handle<IMeshData_Model>& theModel,
                                       const IMeshTools_Parameters&        theParameters,
                                       const Message_ProgressRange&        theRange) override;

private:
  void process(const int theFaceIndex, const Message_ProgressRange& theRange) const;

private:
  class FaceListFunctor;

private:
  occ::handle<IMeshTools_MeshAlgoFactory> myAlgoFactory;
  occ::handle<IMeshData_Model>            myModel;
  IMeshTools_Parameters                   myParameters;
};
