#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
class StepData_StepReaderData;
class Interface_Check;
class StepFEA_FeaModel3d;
class StepData_StepWriter;
class Interface_EntityIterator;

//! Read & Write tool for FeaModel3d
class RWStepFEA_RWFeaModel3d
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_HIDDEN RWStepFEA_RWFeaModel3d();

  //! Reads FeaModel3d
  Standard_HIDDEN void ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                const int                                   num,
                                occ::handle<Interface_Check>&               ach,
                                const occ::handle<StepFEA_FeaModel3d>&      ent) const;

  //! Writes FeaModel3d
  Standard_HIDDEN void WriteStep(StepData_StepWriter&                   SW,
                                 const occ::handle<StepFEA_FeaModel3d>& ent) const;

  //! Fills data for graph (shared items)
  Standard_HIDDEN void Share(const occ::handle<StepFEA_FeaModel3d>& ent,
                             Interface_EntityIterator&              iter) const;
};

