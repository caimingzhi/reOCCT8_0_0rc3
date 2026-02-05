#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
class StepData_StepReaderData;
class Interface_Check;
class HeaderSection_FileDescription;
class StepData_StepWriter;

//! Read & Write Module for FileDescription
class RWHeaderSection_RWFileDescription
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT RWHeaderSection_RWFileDescription();

  Standard_EXPORT void ReadStep(const occ::handle<StepData_StepReaderData>&       data,
                                const int                                         num,
                                occ::handle<Interface_Check>&                     ach,
                                const occ::handle<HeaderSection_FileDescription>& ent) const;

  Standard_EXPORT void WriteStep(StepData_StepWriter&                              SW,
                                 const occ::handle<HeaderSection_FileDescription>& ent) const;
};
