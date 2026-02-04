#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
class StepData_StepReaderData;
class Interface_Check;
class StepBasic_ProductConceptContext;
class StepData_StepWriter;
class Interface_EntityIterator;

//! Read & Write tool for ProductConceptContext
class RWStepBasic_RWProductConceptContext
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_HIDDEN RWStepBasic_RWProductConceptContext();

  //! Reads ProductConceptContext
  Standard_HIDDEN void ReadStep(const occ::handle<StepData_StepReaderData>&         data,
                                const int                                           num,
                                occ::handle<Interface_Check>&                       ach,
                                const occ::handle<StepBasic_ProductConceptContext>& ent) const;

  //! Writes ProductConceptContext
  Standard_HIDDEN void WriteStep(StepData_StepWriter&                                SW,
                                 const occ::handle<StepBasic_ProductConceptContext>& ent) const;

  //! Fills data for graph (shared items)
  Standard_HIDDEN void Share(const occ::handle<StepBasic_ProductConceptContext>& ent,
                             Interface_EntityIterator&                           iter) const;
};

