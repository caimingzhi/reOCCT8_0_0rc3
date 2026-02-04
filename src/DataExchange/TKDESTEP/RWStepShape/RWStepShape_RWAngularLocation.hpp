#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
class StepData_StepReaderData;
class Interface_Check;
class StepShape_AngularLocation;
class StepData_StepWriter;
class Interface_EntityIterator;

//! Read & Write tool for AngularLocation
class RWStepShape_RWAngularLocation
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_HIDDEN RWStepShape_RWAngularLocation();

  //! Reads AngularLocation
  Standard_HIDDEN void ReadStep(const occ::handle<StepData_StepReaderData>&   data,
                                const int                                     num,
                                occ::handle<Interface_Check>&                 ach,
                                const occ::handle<StepShape_AngularLocation>& ent) const;

  //! Writes AngularLocation
  Standard_HIDDEN void WriteStep(StepData_StepWriter&                          SW,
                                 const occ::handle<StepShape_AngularLocation>& ent) const;

  //! Fills data for graph (shared items)
  Standard_HIDDEN void Share(const occ::handle<StepShape_AngularLocation>& ent,
                             Interface_EntityIterator&                     iter) const;
};

