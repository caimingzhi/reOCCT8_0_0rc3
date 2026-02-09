#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class StepAP214_Protocol;

class StepAP214
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static occ::handle<StepAP214_Protocol> Protocol();
};
