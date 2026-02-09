

#include <MoniTool_Element.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(MoniTool_Element, Standard_Transient)

MoniTool_Element::MoniTool_Element()
    : thecode(0)
{
}

void MoniTool_Element::SetHashCode(const size_t code)
{
  thecode = code;
}

size_t MoniTool_Element::GetHashCode() const
{
  return thecode;
}

occ::handle<Standard_Type> MoniTool_Element::ValueType() const
{
  return DynamicType();
}

const char* MoniTool_Element::ValueTypeName() const
{
  return "(finder)";
}

const MoniTool_AttrList& MoniTool_Element::ListAttr() const
{
  return theattrib;
}

MoniTool_AttrList& MoniTool_Element::ChangeAttr()
{
  return theattrib;
}
