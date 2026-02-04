#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepData_SelectReal.hpp>

//! For immediate members of TrimmingSelect, i.e. :
//! ParameterValue (a Real)
class StepGeom_TrimmingMember : public StepData_SelectReal
{

public:
  Standard_EXPORT StepGeom_TrimmingMember();

  Standard_EXPORT bool HasName() const override;

  Standard_EXPORT const char* Name() const override;

  Standard_EXPORT bool SetName(const char* name) override;

  DEFINE_STANDARD_RTTIEXT(StepGeom_TrimmingMember, StepData_SelectReal)
};

