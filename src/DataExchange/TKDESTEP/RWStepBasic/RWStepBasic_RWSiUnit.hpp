#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <Standard_Boolean.hpp>
#include <StepBasic_SiPrefix.hpp>
#include <StepBasic_SiUnitName.hpp>
class StepData_StepReaderData;
class Interface_Check;
class StepBasic_SiUnit;
class StepData_StepWriter;
class TCollection_AsciiString;

class RWStepBasic_RWSiUnit
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_HIDDEN RWStepBasic_RWSiUnit();

  Standard_HIDDEN void ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                const int                                   num,
                                occ::handle<Interface_Check>&               ach,
                                const occ::handle<StepBasic_SiUnit>&        ent) const;

  Standard_HIDDEN void WriteStep(StepData_StepWriter&                 SW,
                                 const occ::handle<StepBasic_SiUnit>& ent) const;
};
