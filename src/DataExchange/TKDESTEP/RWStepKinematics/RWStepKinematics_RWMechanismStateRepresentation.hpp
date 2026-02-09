#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
class StepData_StepReaderData;
class Interface_Check;
class StepKinematics_MechanismStateRepresentation;
class StepData_StepWriter;
class Interface_EntityIterator;

class RWStepKinematics_RWMechanismStateRepresentation
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_HIDDEN RWStepKinematics_RWMechanismStateRepresentation();

  Standard_HIDDEN void ReadStep(
    const occ::handle<StepData_StepReaderData>&                     theData,
    const int                                                       theNum,
    occ::handle<Interface_Check>&                                   theArch,
    const occ::handle<StepKinematics_MechanismStateRepresentation>& theEnt) const;

  Standard_HIDDEN void WriteStep(
    StepData_StepWriter&                                            theSW,
    const occ::handle<StepKinematics_MechanismStateRepresentation>& theEnt) const;

  Standard_HIDDEN void Share(const occ::handle<StepKinematics_MechanismStateRepresentation>& theEnt,
                             Interface_EntityIterator& iter) const;
};
