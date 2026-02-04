#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <StepVisual_TessellatedCurveSet.hpp>
class StepData_StepReaderData;
class Interface_Check;
// class StepVisual_TessellatedCurveSet;
class StepData_StepWriter;
class Interface_EntityIterator;

//! Read & Write Module for AnnotationOccurrence
class RWStepVisual_RWTessellatedCurveSet
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_HIDDEN RWStepVisual_RWTessellatedCurveSet();

  Standard_HIDDEN void ReadStep(const occ::handle<StepData_StepReaderData>&        data,
                                const int                                          num,
                                occ::handle<Interface_Check>&                      ach,
                                const occ::handle<StepVisual_TessellatedCurveSet>& ent) const;

  Standard_HIDDEN void WriteStep(StepData_StepWriter&                               SW,
                                 const occ::handle<StepVisual_TessellatedCurveSet>& ent) const;

  Standard_HIDDEN void Share(const occ::handle<StepVisual_TessellatedCurveSet>& ent,
                             Interface_EntityIterator&                          iter) const;
};
