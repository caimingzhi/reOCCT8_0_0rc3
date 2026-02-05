#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
class StepData_StepReaderData;
class Interface_Check;
class StepFEA_FeaShellMembraneBendingCouplingStiffness;
class StepData_StepWriter;
class Interface_EntityIterator;

//! Read & Write tool for FeaShellMembraneBendingCouplingStiffness
class RWStepFEA_RWFeaShellMembraneBendingCouplingStiffness
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_HIDDEN RWStepFEA_RWFeaShellMembraneBendingCouplingStiffness();

  //! Reads FeaShellMembraneBendingCouplingStiffness
  Standard_HIDDEN void ReadStep(
    const occ::handle<StepData_StepReaderData>&                          data,
    const int                                                            num,
    occ::handle<Interface_Check>&                                        ach,
    const occ::handle<StepFEA_FeaShellMembraneBendingCouplingStiffness>& ent) const;

  //! Writes FeaShellMembraneBendingCouplingStiffness
  Standard_HIDDEN void WriteStep(
    StepData_StepWriter&                                                 SW,
    const occ::handle<StepFEA_FeaShellMembraneBendingCouplingStiffness>& ent) const;

  //! Fills data for graph (shared items)
  Standard_HIDDEN void Share(
    const occ::handle<StepFEA_FeaShellMembraneBendingCouplingStiffness>& ent,
    Interface_EntityIterator&                                            iter) const;
};
