#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
class StepData_StepReaderData;
class Interface_Check;
class StepGeom_CurveBoundedSurface;
class StepData_StepWriter;
class Interface_EntityIterator;

//! Read & Write tool for CurveBoundedSurface
class RWStepGeom_RWCurveBoundedSurface
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_HIDDEN RWStepGeom_RWCurveBoundedSurface();

  //! Reads CurveBoundedSurface
  Standard_HIDDEN void ReadStep(const occ::handle<StepData_StepReaderData>&      data,
                                const int                                        num,
                                occ::handle<Interface_Check>&                    ach,
                                const occ::handle<StepGeom_CurveBoundedSurface>& ent) const;

  //! Writes CurveBoundedSurface
  Standard_HIDDEN void WriteStep(StepData_StepWriter&                             SW,
                                 const occ::handle<StepGeom_CurveBoundedSurface>& ent) const;

  //! Fills data for graph (shared items)
  Standard_HIDDEN void Share(const occ::handle<StepGeom_CurveBoundedSurface>& ent,
                             Interface_EntityIterator&                        iter) const;
};
