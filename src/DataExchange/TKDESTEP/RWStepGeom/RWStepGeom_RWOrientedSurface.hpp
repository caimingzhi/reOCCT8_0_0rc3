#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
class StepData_StepReaderData;
class Interface_Check;
class StepGeom_OrientedSurface;
class StepData_StepWriter;
class Interface_EntityIterator;

//! Read & Write tool for OrientedSurface
class RWStepGeom_RWOrientedSurface
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_HIDDEN RWStepGeom_RWOrientedSurface();

  //! Reads OrientedSurface
  Standard_HIDDEN void ReadStep(const occ::handle<StepData_StepReaderData>&  data,
                                const int                                    num,
                                occ::handle<Interface_Check>&                ach,
                                const occ::handle<StepGeom_OrientedSurface>& ent) const;

  //! Writes OrientedSurface
  Standard_HIDDEN void WriteStep(StepData_StepWriter&                         SW,
                                 const occ::handle<StepGeom_OrientedSurface>& ent) const;

  //! Fills data for graph (shared items)
  Standard_HIDDEN void Share(const occ::handle<StepGeom_OrientedSurface>& ent,
                             Interface_EntityIterator&                    iter) const;
};
