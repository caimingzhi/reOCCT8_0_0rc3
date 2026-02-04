#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TCollection_AsciiString.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Transient.hpp>
class Storage_CallBack;

class Storage_TypedCallBack : public Standard_Transient
{

public:
  Standard_EXPORT Storage_TypedCallBack();

  Standard_EXPORT Storage_TypedCallBack(const TCollection_AsciiString&       aTypeName,
                                        const occ::handle<Storage_CallBack>& aCallBack);

  Standard_EXPORT void SetType(const TCollection_AsciiString& aType);

  Standard_EXPORT TCollection_AsciiString Type() const;

  Standard_EXPORT void SetCallBack(const occ::handle<Storage_CallBack>& aCallBack);

  Standard_EXPORT occ::handle<Storage_CallBack> CallBack() const;

  Standard_EXPORT void SetIndex(const int anIndex);

  Standard_EXPORT int Index() const;

  DEFINE_STANDARD_RTTIEXT(Storage_TypedCallBack, Standard_Transient)

private:
  TCollection_AsciiString       myType;
  occ::handle<Storage_CallBack> myCallBack;
  int                           myIndex;
};

