#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
class StepData_StepReaderData;
class Interface_Check;
class StepShape_DimensionalCharacteristicRepresentation;
class StepData_StepWriter;
class Interface_EntityIterator;

//! Read & Write tool for DimensionalCharacteristicRepresentation
class RWStepShape_RWDimensionalCharacteristicRepresentation
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_HIDDEN RWStepShape_RWDimensionalCharacteristicRepresentation();

  //! Reads DimensionalCharacteristicRepresentation
  Standard_HIDDEN void ReadStep(
    const occ::handle<StepData_StepReaderData>&                           data,
    const int                                                             num,
    occ::handle<Interface_Check>&                                         ach,
    const occ::handle<StepShape_DimensionalCharacteristicRepresentation>& ent) const;

  //! Writes DimensionalCharacteristicRepresentation
  Standard_HIDDEN void WriteStep(
    StepData_StepWriter&                                                  SW,
    const occ::handle<StepShape_DimensionalCharacteristicRepresentation>& ent) const;

  //! Fills data for graph (shared items)
  Standard_HIDDEN void Share(
    const occ::handle<StepShape_DimensionalCharacteristicRepresentation>& ent,
    Interface_EntityIterator&                                             iter) const;
};

