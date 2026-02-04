#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepBasic_Document.hpp>

class StepBasic_DigitalDocument : public StepBasic_Document
{

public:
  Standard_EXPORT StepBasic_DigitalDocument();

  DEFINE_STANDARD_RTTIEXT(StepBasic_DigitalDocument, StepBasic_Document)
};

