#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class StepData_StepReaderData;
class Interface_Check;
class StepVisual_RepositionedTessellatedItem;
class StepData_StepWriter;

//! Read & Write tool for RepositionedTessellatedItem
class RWStepVisual_RWRepositionedTessellatedItem
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  RWStepVisual_RWRepositionedTessellatedItem() {};

  //! Reads RepositionedTessellatedItem
  Standard_HIDDEN void ReadStep(
    const occ::handle<StepData_StepReaderData>&                theData,
    const int                                                  theNum,
    occ::handle<Interface_Check>&                              theAch,
    const occ::handle<StepVisual_RepositionedTessellatedItem>& theEnt) const;

  //! Writes RepositionedTessellatedItem
  Standard_HIDDEN void WriteStep(
    StepData_StepWriter&                                       theSW,
    const occ::handle<StepVisual_RepositionedTessellatedItem>& theEnt) const;
};
