

#include <Storage_CallBack.hpp>
#include <Storage_TypedCallBack.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Storage_TypedCallBack, Standard_Transient)

Storage_TypedCallBack::Storage_TypedCallBack()
    : myIndex(0)
{
}

Storage_TypedCallBack::Storage_TypedCallBack(const TCollection_AsciiString&       aTypeName,
                                             const occ::handle<Storage_CallBack>& aCallBack)
    : myIndex(0)
{
  myType     = aTypeName;
  myCallBack = aCallBack;
}

void Storage_TypedCallBack::SetType(const TCollection_AsciiString& aType)
{
  myType = aType;
}

TCollection_AsciiString Storage_TypedCallBack::Type() const
{
  return myType;
}

void Storage_TypedCallBack::SetCallBack(const occ::handle<Storage_CallBack>& aCallBack)
{
  myCallBack = aCallBack;
}

occ::handle<Storage_CallBack> Storage_TypedCallBack::CallBack() const
{
  return myCallBack;
}

void Storage_TypedCallBack::SetIndex(const int anIndex)
{
  myIndex = anIndex;
}

int Storage_TypedCallBack::Index() const
{
  return myIndex;
}
