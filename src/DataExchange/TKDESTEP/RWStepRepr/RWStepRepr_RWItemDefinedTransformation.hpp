#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
class StepData_StepReaderData;
class Interface_Check;
class StepRepr_ItemDefinedTransformation;
class StepData_StepWriter;
class Interface_EntityIterator;

//! Read & Write Module for ItemDefinedTransformation
class RWStepRepr_RWItemDefinedTransformation
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_HIDDEN RWStepRepr_RWItemDefinedTransformation();

  Standard_HIDDEN void ReadStep(const occ::handle<StepData_StepReaderData>&            data,
                                const int                                              num,
                                occ::handle<Interface_Check>&                          ach,
                                const occ::handle<StepRepr_ItemDefinedTransformation>& ent) const;

  Standard_HIDDEN void WriteStep(StepData_StepWriter&                                   SW,
                                 const occ::handle<StepRepr_ItemDefinedTransformation>& ent) const;

  Standard_HIDDEN void Share(const occ::handle<StepRepr_ItemDefinedTransformation>& ent,
                             Interface_EntityIterator&                              iter) const;
};

