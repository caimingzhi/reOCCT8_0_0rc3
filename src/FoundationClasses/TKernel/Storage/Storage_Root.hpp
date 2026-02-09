#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TCollection_AsciiString.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Transient.hpp>
class Standard_Persistent;

class Storage_Root : public Standard_Transient
{

public:
  Standard_EXPORT Storage_Root();

  Standard_EXPORT Storage_Root(const TCollection_AsciiString&          theName,
                               const occ::handle<Standard_Persistent>& theObject);

  Standard_EXPORT Storage_Root(const TCollection_AsciiString& theName,
                               const int                      theRef,
                               const TCollection_AsciiString& theType);

  Standard_EXPORT void SetName(const TCollection_AsciiString& theName);

  Standard_EXPORT TCollection_AsciiString Name() const;

  Standard_EXPORT void SetObject(const occ::handle<Standard_Persistent>& anObject);

  Standard_EXPORT occ::handle<Standard_Persistent> Object() const;

  Standard_EXPORT TCollection_AsciiString Type() const;

  Standard_EXPORT void SetReference(const int aRef);

  Standard_EXPORT int Reference() const;

  Standard_EXPORT void SetType(const TCollection_AsciiString& aType);

  friend class Storage_Schema;

  DEFINE_STANDARD_RTTIEXT(Storage_Root, Standard_Transient)

private:
  TCollection_AsciiString          myName;
  TCollection_AsciiString          myType;
  occ::handle<Standard_Persistent> myObject;
  int                              myRef;
};
