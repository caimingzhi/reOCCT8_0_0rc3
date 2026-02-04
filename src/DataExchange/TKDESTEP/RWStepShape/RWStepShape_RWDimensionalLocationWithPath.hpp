#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
class StepData_StepReaderData;
class Interface_Check;
class StepShape_DimensionalLocationWithPath;
class StepData_StepWriter;
class Interface_EntityIterator;

//! Read & Write tool for DimensionalLocationWithPath
class RWStepShape_RWDimensionalLocationWithPath
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_HIDDEN RWStepShape_RWDimensionalLocationWithPath();

  //! Reads DimensionalLocationWithPath
  Standard_HIDDEN void ReadStep(
    const occ::handle<StepData_StepReaderData>&               data,
    const int                                                 num,
    occ::handle<Interface_Check>&                             ach,
    const occ::handle<StepShape_DimensionalLocationWithPath>& ent) const;

  //! Writes DimensionalLocationWithPath
  Standard_HIDDEN void WriteStep(
    StepData_StepWriter&                                      SW,
    const occ::handle<StepShape_DimensionalLocationWithPath>& ent) const;

  //! Fills data for graph (shared items)
  Standard_HIDDEN void Share(const occ::handle<StepShape_DimensionalLocationWithPath>& ent,
                             Interface_EntityIterator&                                 iter) const;
};

