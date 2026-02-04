#pragma once


#include <IMeshTools_ModelAlgo.hpp>
#include <IMeshTools_Parameters.hpp>
#include <IMeshTools_MeshAlgoFactory.hpp>

//! Class implements functionality starting triangulation of model's faces.
//! Each face is processed separately and can be executed in parallel mode.
//! Uses mesh algo factory passed as initializer to create instance of triangulation
//! algorithm according to type of surface of target face.
class BRepMesh_FaceDiscret : public IMeshTools_ModelAlgo
{
public:
  //! Constructor.
  Standard_EXPORT BRepMesh_FaceDiscret(
    const occ::handle<IMeshTools_MeshAlgoFactory>& theAlgoFactory);

  //! Destructor.
  Standard_EXPORT ~BRepMesh_FaceDiscret() override;

  DEFINE_STANDARD_RTTIEXT(BRepMesh_FaceDiscret, IMeshTools_ModelAlgo)

protected:
  //! Performs processing of faces of the given model.
  Standard_EXPORT bool performInternal(const occ::handle<IMeshData_Model>& theModel,
                                       const IMeshTools_Parameters&        theParameters,
                                       const Message_ProgressRange&        theRange) override;

private:
  //! Checks existing discretization of the face and updates data model.
  void process(const int theFaceIndex, const Message_ProgressRange& theRange) const;

private:
  class FaceListFunctor;

private:
  occ::handle<IMeshTools_MeshAlgoFactory> myAlgoFactory;
  occ::handle<IMeshData_Model>            myModel;
  IMeshTools_Parameters                   myParameters;
};

