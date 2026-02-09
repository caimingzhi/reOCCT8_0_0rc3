

#include <IGESDefs_Protocol.hpp>

#include <IGESDefs_AssociativityDef.hpp>
#include <IGESDefs_AttributeDef.hpp>
#include <IGESDefs_AttributeTable.hpp>
#include <IGESDefs_GenericData.hpp>
#include <IGESDefs_MacroDef.hpp>
#include <IGESDefs_TabularData.hpp>
#include <IGESDefs_UnitsData.hpp>
#include <IGESGraph.hpp>
#include <IGESGraph_Protocol.hpp>
#include <Interface_Protocol.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESDefs_Protocol, IGESData_Protocol)

IGESDefs_Protocol::IGESDefs_Protocol() = default;

int IGESDefs_Protocol::NbResources() const
{
  return 1;
}

occ::handle<Interface_Protocol> IGESDefs_Protocol::Resource(const int) const
{
  occ::handle<Interface_Protocol> res = IGESGraph::Protocol();
  return res;
}

int IGESDefs_Protocol::TypeNumber(const occ::handle<Standard_Type>& atype) const
{
  if (atype == STANDARD_TYPE(IGESDefs_AssociativityDef))
    return 1;
  else if (atype == STANDARD_TYPE(IGESDefs_AttributeDef))
    return 2;
  else if (atype == STANDARD_TYPE(IGESDefs_AttributeTable))
    return 3;
  else if (atype == STANDARD_TYPE(IGESDefs_GenericData))
    return 4;
  else if (atype == STANDARD_TYPE(IGESDefs_MacroDef))
    return 5;
  else if (atype == STANDARD_TYPE(IGESDefs_TabularData))
    return 6;
  else if (atype == STANDARD_TYPE(IGESDefs_UnitsData))
    return 7;
  return 0;
}
