#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
class StepData_StepReaderData;
class Interface_Check;
class StepRepr_CompositeShapeAspect;
class StepData_StepWriter;
class Interface_EntityIterator;

//! Read & Write tool for CompositeShapeAspect
class RWStepRepr_RWCompositeShapeAspect
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_HIDDEN RWStepRepr_RWCompositeShapeAspect();

  //! Reads CompositeShapeAspect
  Standard_HIDDEN void ReadStep(const occ::handle<StepData_StepReaderData>&       data,
                                const int                                         num,
                                occ::handle<Interface_Check>&                     ach,
                                const occ::handle<StepRepr_CompositeShapeAspect>& ent) const;

  //! Writes CompositeShapeAspect
  Standard_HIDDEN void WriteStep(StepData_StepWriter&                              SW,
                                 const occ::handle<StepRepr_CompositeShapeAspect>& ent) const;

  //! Fills data for graph (shared items)
  Standard_HIDDEN void Share(const occ::handle<StepRepr_CompositeShapeAspect>& ent,
                             Interface_EntityIterator&                         iter) const;
};
