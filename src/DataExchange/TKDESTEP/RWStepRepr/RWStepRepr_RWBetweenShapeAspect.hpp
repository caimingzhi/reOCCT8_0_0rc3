#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>

class StepData_StepReaderData;
class Interface_Check;
class StepRepr_BetweenShapeAspect;
class StepData_StepWriter;
class Interface_EntityIterator;

//! Read & Write tool for BetweenShapeAspect
class RWStepRepr_RWBetweenShapeAspect
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_HIDDEN RWStepRepr_RWBetweenShapeAspect();

  //! Reads BetweenShapeAspect
  Standard_HIDDEN void ReadStep(const occ::handle<StepData_StepReaderData>&     data,
                                const int                                       num,
                                occ::handle<Interface_Check>&                   ach,
                                const occ::handle<StepRepr_BetweenShapeAspect>& ent) const;

  //! Writes BetweenShapeAspect
  Standard_HIDDEN void WriteStep(StepData_StepWriter&                            SW,
                                 const occ::handle<StepRepr_BetweenShapeAspect>& ent) const;

  //! Fills data for graph (shared items)
  Standard_HIDDEN void Share(const occ::handle<StepRepr_BetweenShapeAspect>& ent,
                             Interface_EntityIterator&                       iter) const;
};
