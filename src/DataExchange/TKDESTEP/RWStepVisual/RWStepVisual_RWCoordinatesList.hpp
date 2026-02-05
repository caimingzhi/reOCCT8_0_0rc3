#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <StepData_StepReaderData.hpp>
class Interface_Check;
class StepVisual_CoordinatesList;
class StepData_StepWriter;

//! Read & Write Module for AnnotationOccurrence
class RWStepVisual_RWCoordinatesList
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_HIDDEN RWStepVisual_RWCoordinatesList();

  Standard_HIDDEN void ReadStep(const occ::handle<StepData_StepReaderData>&    data,
                                const int                                      num,
                                occ::handle<Interface_Check>&                  ach,
                                const occ::handle<StepVisual_CoordinatesList>& ent) const;

  Standard_HIDDEN void WriteStep(StepData_StepWriter&                           SW,
                                 const occ::handle<StepVisual_CoordinatesList>& ent) const;
};
