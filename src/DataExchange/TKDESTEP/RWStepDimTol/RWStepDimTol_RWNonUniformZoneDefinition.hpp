#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>

class StepData_StepReaderData;
class Interface_Check;
class StepDimTol_NonUniformZoneDefinition;
class StepData_StepWriter;
class Interface_EntityIterator;

//! Read & Write tool for NonUniformZoneDefinition
class RWStepDimTol_RWNonUniformZoneDefinition
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_HIDDEN RWStepDimTol_RWNonUniformZoneDefinition();

  //! Reads NonUniformZoneDefinition
  Standard_HIDDEN void ReadStep(const occ::handle<StepData_StepReaderData>&             data,
                                const int                                               num,
                                occ::handle<Interface_Check>&                           ach,
                                const occ::handle<StepDimTol_NonUniformZoneDefinition>& ent) const;

  //! Writes NonUniformZoneDefinition
  Standard_HIDDEN void WriteStep(StepData_StepWriter&                                    SW,
                                 const occ::handle<StepDimTol_NonUniformZoneDefinition>& ent) const;

  //! Fills data for graph (shared items)
  Standard_HIDDEN void Share(const occ::handle<StepDimTol_NonUniformZoneDefinition>& ent,
                             Interface_EntityIterator&                               iter) const;
};
