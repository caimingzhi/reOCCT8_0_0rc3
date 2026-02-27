

#include <Standard_Type.hpp>
#include <Storage_Root.hpp>
#include <Storage_Schema.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(app::storage::Storage_Root, Standard_Transient)

app::storage::Storage_Root::Storage_Root()
    : myRef(0)
{
}

app::storage::Storage_Root::Storage_Root(const TCollection_AsciiString&          theName,
                           const occ::handle<Standard_Persistent>& theObject)
    : myName(theName),
      myObject(theObject),
      myRef(0)
{
}

app::storage::Storage_Root::Storage_Root(const TCollection_AsciiString& theName,
                           const int                      theRef,
                           const TCollection_AsciiString& theType)
    : myName(theName),
      myType(theType),
      myRef(theRef)
{
}

void app::storage::Storage_Root::SetName(const TCollection_AsciiString& theName)
{
  myName = theName;
}

TCollection_AsciiString app::storage::Storage_Root::Name() const
{
  return myName;
}

void app::storage::Storage_Root::SetObject(const occ::handle<Standard_Persistent>& anObject)
{
  myObject = anObject;
}

occ::handle<Standard_Persistent> app::storage::Storage_Root::Object() const
{
  return myObject;
}

TCollection_AsciiString app::storage::Storage_Root::Type() const
{
  return myType;
}

void app::storage::Storage_Root::SetReference(const int aRef)
{
  myRef = aRef;
}

int app::storage::Storage_Root::Reference() const
{
  return myRef;
}

void app::storage::Storage_Root::SetType(const TCollection_AsciiString& aType)
{
  myType = aType;
}
