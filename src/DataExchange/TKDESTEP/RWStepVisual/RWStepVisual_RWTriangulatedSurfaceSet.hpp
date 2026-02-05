#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class StepData_StepReaderData;
class Interface_Check;
class StepData_StepWriter;
class Interface_EntityIterator;
class StepVisual_TriangulatedSurfaceSet;

//! Read & Write tool for TriangulatedSurfaceSet
class RWStepVisual_RWTriangulatedSurfaceSet
{
public:
  DEFINE_STANDARD_ALLOC

  //! default constructor
  Standard_HIDDEN RWStepVisual_RWTriangulatedSurfaceSet();

  Standard_HIDDEN void ReadStep(const occ::handle<StepData_StepReaderData>&           theData,
                                const int                                             theNum,
                                occ::handle<Interface_Check>&                         theCheck,
                                const occ::handle<StepVisual_TriangulatedSurfaceSet>& theEnt) const;

  Standard_HIDDEN void WriteStep(
    StepData_StepWriter&                                  theSW,
    const occ::handle<StepVisual_TriangulatedSurfaceSet>& theEnt) const;

  Standard_HIDDEN void Share(const occ::handle<StepVisual_TriangulatedSurfaceSet>& theEnt,
                             Interface_EntityIterator&                             theIter) const;
};
