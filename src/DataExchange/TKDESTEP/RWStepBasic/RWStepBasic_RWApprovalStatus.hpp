#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
class StepData_StepReaderData;
class Interface_Check;
class StepBasic_ApprovalStatus;
class StepData_StepWriter;

//! Read & Write Module for ApprovalStatus
class RWStepBasic_RWApprovalStatus
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_HIDDEN RWStepBasic_RWApprovalStatus();

  Standard_HIDDEN void ReadStep(const occ::handle<StepData_StepReaderData>&  data,
                                const int                                    num,
                                occ::handle<Interface_Check>&                ach,
                                const occ::handle<StepBasic_ApprovalStatus>& ent) const;

  Standard_HIDDEN void WriteStep(StepData_StepWriter&                         SW,
                                 const occ::handle<StepBasic_ApprovalStatus>& ent) const;
};

