

#include <Storage_CallBack.hpp>
#include <Storage_TypedCallBack.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(app::storage::Storage_TypedCallBack, Standard_Transient)

app::storage::Storage_TypedCallBack::Storage_TypedCallBack()
    : myIndex(0)
{
}

app::storage::Storage_TypedCallBack::Storage_TypedCallBack(const TCollection_AsciiString&       aTypeName,
                                             const occ::handle<app::storage::Storage_CallBack>& aCallBack)
    : myIndex(0)
{
  myType     = aTypeName;
  myCallBack = aCallBack;
}

void app::storage::Storage_TypedCallBack::SetType(const TCollection_AsciiString& aType)
{
  myType = aType;
}

TCollection_AsciiString app::storage::Storage_TypedCallBack::Type() const
{
  return myType;
}

void app::storage::Storage_TypedCallBack::SetCallBack(const occ::handle<app::storage::Storage_CallBack>& aCallBack)
{
  myCallBack = aCallBack;
}

occ::handle<app::storage::Storage_CallBack> app::storage::Storage_TypedCallBack::CallBack() const
{
  return myCallBack;
}

void app::storage::Storage_TypedCallBack::SetIndex(const int anIndex)
{
  myIndex = anIndex;
}

int app::storage::Storage_TypedCallBack::Index() const
{
  return myIndex;
}
