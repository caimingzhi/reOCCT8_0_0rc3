#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class StepData_StepReaderData;
class Interface_Check;
class StepData_StepWriter;
class Interface_EntityIterator;
class StepVisual_TessellatedConnectingEdge;

//! Read & Write tool for TessellatedConnectingEdge
class RWStepVisual_RWTessellatedConnectingEdge
{

public:
  DEFINE_STANDARD_ALLOC

  Standard_HIDDEN RWStepVisual_RWTessellatedConnectingEdge();

  Standard_HIDDEN void ReadStep(
    const occ::handle<StepData_StepReaderData>&              theData,
    const int                                                theNum,
    occ::handle<Interface_Check>&                            theCheck,
    const occ::handle<StepVisual_TessellatedConnectingEdge>& theEnt) const;

  Standard_HIDDEN void WriteStep(
    StepData_StepWriter&                                     theSW,
    const occ::handle<StepVisual_TessellatedConnectingEdge>& theEnt) const;

  Standard_HIDDEN void Share(const occ::handle<StepVisual_TessellatedConnectingEdge>& theEnt,
                             Interface_EntityIterator& theIter) const;
};
