

#include <Standard_Transient.hpp>
#include <Transfer_DataInfo.hpp>

occ::handle<Standard_Type> Transfer_DataInfo::Type(const occ::handle<Standard_Transient>& ent)
{
  return ent->DynamicType();
}

const char* Transfer_DataInfo::TypeName(const occ::handle<Standard_Transient>& ent)
{
  return ent->DynamicType()->Name();
}
