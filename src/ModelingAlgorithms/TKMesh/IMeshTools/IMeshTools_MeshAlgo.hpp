#pragma once


#include <Standard_Transient.hpp>
#include <IMeshData_Types.hpp>
#include <Message_ProgressRange.hpp>

struct IMeshTools_Parameters;

//! Interface class providing API for algorithms intended to create mesh for discrete face.
class IMeshTools_MeshAlgo : public Standard_Transient
{
public:
  //! Destructor.
  ~IMeshTools_MeshAlgo() override = default;

  //! Performs processing of the given face.
  Standard_EXPORT virtual void Perform(const IMeshData::IFaceHandle& theDFace,
                                       const IMeshTools_Parameters&  theParameters,
                                       const Message_ProgressRange&  theRange) = 0;

  DEFINE_STANDARD_RTTIEXT(IMeshTools_MeshAlgo, Standard_Transient)

protected:
  //! Constructor.
  IMeshTools_MeshAlgo() {}
};

