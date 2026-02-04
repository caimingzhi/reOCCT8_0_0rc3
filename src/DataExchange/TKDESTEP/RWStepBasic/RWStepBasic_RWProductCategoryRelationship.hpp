#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
class StepData_StepReaderData;
class Interface_Check;
class StepBasic_ProductCategoryRelationship;
class StepData_StepWriter;
class Interface_EntityIterator;

//! Read & Write tool for ProductCategoryRelationship
class RWStepBasic_RWProductCategoryRelationship
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_HIDDEN RWStepBasic_RWProductCategoryRelationship();

  //! Reads ProductCategoryRelationship
  Standard_HIDDEN void ReadStep(
    const occ::handle<StepData_StepReaderData>&               data,
    const int                                                 num,
    occ::handle<Interface_Check>&                             ach,
    const occ::handle<StepBasic_ProductCategoryRelationship>& ent) const;

  //! Writes ProductCategoryRelationship
  Standard_HIDDEN void WriteStep(
    StepData_StepWriter&                                      SW,
    const occ::handle<StepBasic_ProductCategoryRelationship>& ent) const;

  //! Fills data for graph (shared items)
  Standard_HIDDEN void Share(const occ::handle<StepBasic_ProductCategoryRelationship>& ent,
                             Interface_EntityIterator&                                 iter) const;
};

