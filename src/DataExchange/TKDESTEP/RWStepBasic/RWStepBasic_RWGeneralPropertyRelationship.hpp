#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
class StepData_StepReaderData;
class Interface_Check;
class StepBasic_GeneralProperty;
class StepData_StepWriter;
class Interface_EntityIterator;

class StepBasic_GeneralPropertyRelationship;

class RWStepBasic_RWGeneralPropertyRelationship
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_HIDDEN RWStepBasic_RWGeneralPropertyRelationship();

  Standard_HIDDEN void ReadStep(
    const occ::handle<StepData_StepReaderData>&               theData,
    const int                                                 theNum,
    occ::handle<Interface_Check>&                             theAch,
    const occ::handle<StepBasic_GeneralPropertyRelationship>& theEnt) const;

  Standard_HIDDEN void WriteStep(
    StepData_StepWriter&                                      theSW,
    const occ::handle<StepBasic_GeneralPropertyRelationship>& theEnt) const;

  Standard_HIDDEN void Share(const occ::handle<StepBasic_GeneralPropertyRelationship>& theEnt,
                             Interface_EntityIterator& theIter) const;
};
