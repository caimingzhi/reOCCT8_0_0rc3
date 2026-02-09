#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class StepData_StepReaderData;
class Interface_Check;
class StepData_StepWriter;
class Interface_EntityIterator;
class StepVisual_TessellatedShapeRepresentationWithAccuracyParameters;

class RWStepVisual_RWTessellatedShapeRepresentationWithAccuracyParameters
{

public:
  DEFINE_STANDARD_ALLOC

  Standard_HIDDEN RWStepVisual_RWTessellatedShapeRepresentationWithAccuracyParameters();

  Standard_HIDDEN void ReadStep(
    const occ::handle<StepData_StepReaderData>&                                         theData,
    const int                                                                           theNum,
    occ::handle<Interface_Check>&                                                       theCheck,
    const occ::handle<StepVisual_TessellatedShapeRepresentationWithAccuracyParameters>& theEnt)
    const;

  Standard_HIDDEN void WriteStep(
    StepData_StepWriter&                                                                theSW,
    const occ::handle<StepVisual_TessellatedShapeRepresentationWithAccuracyParameters>& theEnt)
    const;

  Standard_HIDDEN void Share(
    const occ::handle<StepVisual_TessellatedShapeRepresentationWithAccuracyParameters>& theEnt,
    Interface_EntityIterator& theIter) const;
};
