#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
class StepData_StepReaderData;
class Interface_Check;
class StepFEA_FeaMassDensity;
class StepData_StepWriter;
class Interface_EntityIterator;

//! Read & Write tool for FeaMassDensity
class RWStepFEA_RWFeaMassDensity
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_HIDDEN RWStepFEA_RWFeaMassDensity();

  //! Reads FeaMassDensity
  Standard_HIDDEN void ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                const int                                   num,
                                occ::handle<Interface_Check>&               ach,
                                const occ::handle<StepFEA_FeaMassDensity>&  ent) const;

  //! Writes FeaMassDensity
  Standard_HIDDEN void WriteStep(StepData_StepWriter&                       SW,
                                 const occ::handle<StepFEA_FeaMassDensity>& ent) const;

  //! Fills data for graph (shared items)
  Standard_HIDDEN void Share(const occ::handle<StepFEA_FeaMassDensity>& ent,
                             Interface_EntityIterator&                  iter) const;
};
