#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepShape_ConnectedFaceSet.hpp>

class StepShape_ClosedShell : public StepShape_ConnectedFaceSet
{

public:
  //! Returns a ClosedShell
  Standard_EXPORT StepShape_ClosedShell();

  DEFINE_STANDARD_RTTIEXT(StepShape_ClosedShell, StepShape_ConnectedFaceSet)
};

