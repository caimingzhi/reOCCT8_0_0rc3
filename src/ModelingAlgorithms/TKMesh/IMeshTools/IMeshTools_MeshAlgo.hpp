#pragma once

#include <Standard_Transient.hpp>
#include <IMeshData_Types.hpp>
#include <Message_ProgressRange.hpp>

struct IMeshTools_Parameters;

class IMeshTools_MeshAlgo : public Standard_Transient
{
public:
  ~IMeshTools_MeshAlgo() override = default;

  Standard_EXPORT virtual void Perform(const IMeshData::IFaceHandle& theDFace,
                                       const IMeshTools_Parameters&  theParameters,
                                       const Message_ProgressRange&  theRange) = 0;

  DEFINE_STANDARD_RTTIEXT(IMeshTools_MeshAlgo, Standard_Transient)

protected:
  IMeshTools_MeshAlgo() {}
};
