#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
class StepData_StepReaderData;
class Interface_Check;
class StepRepr_MaterialProperty;
class StepData_StepWriter;
class Interface_EntityIterator;

//! Read & Write tool for MaterialProperty
class RWStepRepr_RWMaterialProperty
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_HIDDEN RWStepRepr_RWMaterialProperty();

  //! Reads MaterialProperty
  Standard_HIDDEN void ReadStep(const occ::handle<StepData_StepReaderData>&   data,
                                const int                                     num,
                                occ::handle<Interface_Check>&                 ach,
                                const occ::handle<StepRepr_MaterialProperty>& ent) const;

  //! Writes MaterialProperty
  Standard_HIDDEN void WriteStep(StepData_StepWriter&                          SW,
                                 const occ::handle<StepRepr_MaterialProperty>& ent) const;

  //! Fills data for graph (shared items)
  Standard_HIDDEN void Share(const occ::handle<StepRepr_MaterialProperty>& ent,
                             Interface_EntityIterator&                     iter) const;
};
