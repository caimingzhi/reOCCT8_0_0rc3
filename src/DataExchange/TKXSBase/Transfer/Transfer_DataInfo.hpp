#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Type.hpp>
class Standard_Transient;

class Transfer_DataInfo
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static occ::handle<Standard_Type> Type(
    const occ::handle<Standard_Transient>& ent);

  Standard_EXPORT static const char* TypeName(const occ::handle<Standard_Transient>& ent);
};
