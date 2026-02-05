#pragma once

#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class StepData_StepReaderData;
class Interface_Check;
class StepVisual_RepositionedTessellatedGeometricSet;
class StepData_StepWriter;
class Interface_EntityIterator;

//! Read & Write tool for complex RepositionedTessellatedGeometricSet
class RWStepVisual_RWRepositionedTessellatedGeometricSet
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  RWStepVisual_RWRepositionedTessellatedGeometricSet() {};

  //! Reads RepositionedTessellatedGeometricSet
  Standard_HIDDEN void ReadStep(
    const occ::handle<StepData_StepReaderData>&                        theData,
    const int                                                          theNum,
    occ::handle<Interface_Check>&                                      theAch,
    const occ::handle<StepVisual_RepositionedTessellatedGeometricSet>& theEnt) const;

  //! Writes RepositionedTessellatedGeometricSet
  Standard_HIDDEN void WriteStep(
    StepData_StepWriter&                                               theSW,
    const occ::handle<StepVisual_RepositionedTessellatedGeometricSet>& theEnt) const;

  //! Fills data for graph (shared items)
  Standard_HIDDEN void Share(
    const occ::handle<StepVisual_RepositionedTessellatedGeometricSet>& theEnt,
    Interface_EntityIterator&                                          theIter) const;
};
