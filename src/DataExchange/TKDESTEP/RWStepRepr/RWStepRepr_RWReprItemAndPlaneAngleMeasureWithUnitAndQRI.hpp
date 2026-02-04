#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
class StepData_StepReaderData;
class Interface_Check;
class StepRepr_ReprItemAndPlaneAngleMeasureWithUnitAndQRI;
class StepData_StepWriter;

//! Read & Write Module for ReprItemAndPlaneAngleMeasureWithUnitAndQRI
class RWStepRepr_RWReprItemAndPlaneAngleMeasureWithUnitAndQRI
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_HIDDEN RWStepRepr_RWReprItemAndPlaneAngleMeasureWithUnitAndQRI();

  Standard_HIDDEN void ReadStep(
    const occ::handle<StepData_StepReaderData>&                             data,
    const int                                                               num,
    occ::handle<Interface_Check>&                                           ach,
    const occ::handle<StepRepr_ReprItemAndPlaneAngleMeasureWithUnitAndQRI>& ent) const;

  Standard_HIDDEN void WriteStep(
    StepData_StepWriter&                                                    SW,
    const occ::handle<StepRepr_ReprItemAndPlaneAngleMeasureWithUnitAndQRI>& ent) const;
};
