#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class StepData_StepReaderData;
class Interface_Check;
class StepData_StepWriter;
class Interface_EntityIterator;
class StepKinematics_RevolutePairValue;

//! Read & Write tool for RevolutePairValue
class RWStepKinematics_RWRevolutePairValue
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_HIDDEN RWStepKinematics_RWRevolutePairValue();

  Standard_HIDDEN void ReadStep(const occ::handle<StepData_StepReaderData>&          theData,
                                const int                                            theNum,
                                occ::handle<Interface_Check>&                        theArch,
                                const occ::handle<StepKinematics_RevolutePairValue>& theEnt) const;

  Standard_HIDDEN void WriteStep(StepData_StepWriter&                                 theSW,
                                 const occ::handle<StepKinematics_RevolutePairValue>& theEnt) const;

  Standard_HIDDEN void Share(const occ::handle<StepKinematics_RevolutePairValue>& theEnt,
                             Interface_EntityIterator&                            iter) const;
};
