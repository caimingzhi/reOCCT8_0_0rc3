

#include <MoniTool_DataInfo.hpp>
#include <Standard_Transient.hpp>

occ::handle<Standard_Type> MoniTool_DataInfo::Type(const occ::handle<Standard_Transient>& ent)
{
  return ent->DynamicType();
}

const char* MoniTool_DataInfo::TypeName(const occ::handle<Standard_Transient>& ent)
{
  return ent->DynamicType()->Name();
}
