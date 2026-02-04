#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepBasic_Group.hpp>

//! Representation of STEP entity Class
class StepAP214_Class : public StepBasic_Group
{

public:
  //! Empty constructor
  Standard_EXPORT StepAP214_Class();

  DEFINE_STANDARD_RTTIEXT(StepAP214_Class, StepBasic_Group)
};

