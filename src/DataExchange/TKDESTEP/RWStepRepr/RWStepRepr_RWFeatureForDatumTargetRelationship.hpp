#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
class StepData_StepReaderData;
class Interface_Check;
class StepRepr_FeatureForDatumTargetRelationship;
class StepData_StepWriter;
class Interface_EntityIterator;

class RWStepRepr_RWFeatureForDatumTargetRelationship
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_HIDDEN RWStepRepr_RWFeatureForDatumTargetRelationship();

  Standard_HIDDEN void ReadStep(
    const occ::handle<StepData_StepReaderData>&                    data,
    const int                                                      num,
    occ::handle<Interface_Check>&                                  ach,
    const occ::handle<StepRepr_FeatureForDatumTargetRelationship>& ent) const;

  Standard_HIDDEN void WriteStep(
    StepData_StepWriter&                                           SW,
    const occ::handle<StepRepr_FeatureForDatumTargetRelationship>& ent) const;

  Standard_HIDDEN void Share(const occ::handle<StepRepr_FeatureForDatumTargetRelationship>& ent,
                             Interface_EntityIterator& iter) const;
};
