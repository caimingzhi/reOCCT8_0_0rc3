#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
class StepData_StepReaderData;
class Interface_Check;
class StepVisual_DraughtingModel;
class StepData_StepWriter;
class Interface_EntityIterator;

//! Read & Write tool for DraughtingModel
class RWStepVisual_RWDraughtingModel
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_HIDDEN RWStepVisual_RWDraughtingModel();

  //! Reads DraughtingModel
  Standard_HIDDEN void ReadStep(const occ::handle<StepData_StepReaderData>&    data,
                                const int                                      num,
                                occ::handle<Interface_Check>&                  ach,
                                const occ::handle<StepVisual_DraughtingModel>& ent) const;

  //! Writes DraughtingModel
  Standard_HIDDEN void WriteStep(StepData_StepWriter&                           SW,
                                 const occ::handle<StepVisual_DraughtingModel>& ent) const;

  //! Fills data for graph (shared items)
  Standard_HIDDEN void Share(const occ::handle<StepVisual_DraughtingModel>& ent,
                             Interface_EntityIterator&                      iter) const;
};
