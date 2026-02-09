

#include <IFSelect_SelectType.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IFSelect_SelectType, IFSelect_SelectAnyType)

IFSelect_SelectType::IFSelect_SelectType()
{
  thetype = STANDARD_TYPE(Standard_Transient);
}

IFSelect_SelectType::IFSelect_SelectType(const occ::handle<Standard_Type>& atype)
{
  thetype = atype;
}

void IFSelect_SelectType::SetType(const occ::handle<Standard_Type>& atype)
{
  thetype = atype;
}

occ::handle<Standard_Type> IFSelect_SelectType::TypeForMatch() const
{
  return thetype;
}

TCollection_AsciiString IFSelect_SelectType::ExtractLabel() const
{
  return TCollection_AsciiString(thetype->Name());
}
