#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class StepData_Protocol;

class StepData
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static occ::handle<StepData_Protocol> HeaderProtocol();

  Standard_EXPORT static void AddHeaderProtocol(const occ::handle<StepData_Protocol>& headerproto);

  Standard_EXPORT static void Init();

  Standard_EXPORT static occ::handle<StepData_Protocol> Protocol();
};
