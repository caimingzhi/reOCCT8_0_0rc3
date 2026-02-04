#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
class StepData_StepReaderData;
class Interface_Check;
class StepDimTol_AngularityTolerance;
class StepData_StepWriter;
class Interface_EntityIterator;

//! Read & Write tool for AngularityTolerance
class RWStepDimTol_RWAngularityTolerance
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_HIDDEN RWStepDimTol_RWAngularityTolerance();

  //! Reads AngularityTolerance
  Standard_HIDDEN void ReadStep(const occ::handle<StepData_StepReaderData>&        data,
                                const int                                          num,
                                occ::handle<Interface_Check>&                      ach,
                                const occ::handle<StepDimTol_AngularityTolerance>& ent) const;

  //! Writes AngularityTolerance
  Standard_HIDDEN void WriteStep(StepData_StepWriter&                               SW,
                                 const occ::handle<StepDimTol_AngularityTolerance>& ent) const;

  //! Fills data for graph (shared items)
  Standard_HIDDEN void Share(const occ::handle<StepDimTol_AngularityTolerance>& ent,
                             Interface_EntityIterator&                          iter) const;
};

