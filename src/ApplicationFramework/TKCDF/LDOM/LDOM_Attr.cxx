#include <LDOM_Attr.hpp>
#include <LDOM_BasicAttribute.hpp>

//=================================================================================================

LDOM_Attr::LDOM_Attr(const LDOM_BasicAttribute& anAttr, const occ::handle<LDOM_MemManager>& aDoc)
    : LDOM_Node(anAttr, aDoc)
{
}

//=================================================================================================

void LDOM_Attr::setValue(const LDOMString& aValue)
{
  LDOM_BasicAttribute& anAttr = (LDOM_BasicAttribute&)Origin();
  anAttr.SetValue(aValue, myDocument);
}
