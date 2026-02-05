#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
class StepData_StepReaderData;
class Interface_Check;
class StepElement_SurfaceSectionField;
class StepData_StepWriter;
class Interface_EntityIterator;

//! Read & Write tool for SurfaceSectionField
class RWStepElement_RWSurfaceSectionField
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_HIDDEN RWStepElement_RWSurfaceSectionField();

  //! Reads SurfaceSectionField
  Standard_HIDDEN void ReadStep(const occ::handle<StepData_StepReaderData>&         data,
                                const int                                           num,
                                occ::handle<Interface_Check>&                       ach,
                                const occ::handle<StepElement_SurfaceSectionField>& ent) const;

  //! Writes SurfaceSectionField
  Standard_HIDDEN void WriteStep(StepData_StepWriter&                                SW,
                                 const occ::handle<StepElement_SurfaceSectionField>& ent) const;

  //! Fills data for graph (shared items)
  Standard_HIDDEN void Share(const occ::handle<StepElement_SurfaceSectionField>& ent,
                             Interface_EntityIterator&                           iter) const;
};
