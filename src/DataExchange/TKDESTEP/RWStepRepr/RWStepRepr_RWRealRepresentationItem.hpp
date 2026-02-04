#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Real.hpp>
class StepData_StepReaderData;
class Interface_Check;
class StepRepr_RealRepresentationItem;
class StepData_StepWriter;

//! Read & Write Module for RealRepresentationItem
class RWStepRepr_RWRealRepresentationItem
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_HIDDEN RWStepRepr_RWRealRepresentationItem();

  Standard_HIDDEN void ReadStep(const occ::handle<StepData_StepReaderData>&         theData,
                                const int                                           theNum,
                                occ::handle<Interface_Check>&                       theAch,
                                const occ::handle<StepRepr_RealRepresentationItem>& theEnt) const;

  Standard_HIDDEN void WriteStep(StepData_StepWriter&                                theSW,
                                 const occ::handle<StepRepr_RealRepresentationItem>& theEnt) const;
};
