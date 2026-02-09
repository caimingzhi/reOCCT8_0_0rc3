

#include <StdObjMgt_Persistent.hpp>
#include <Standard_Type.hpp>
#include <StdStorage_Root.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StdStorage_Root, Standard_Transient)

StdStorage_Root::StdStorage_Root()
    : myRef(0)
{
}

StdStorage_Root::StdStorage_Root(const TCollection_AsciiString&           theName,
                                 const occ::handle<StdObjMgt_Persistent>& theObject)
    : myName(theName),
      myType(theObject->PName()),
      myObject(theObject),
      myRef(0)
{
}

StdStorage_Root::StdStorage_Root(const TCollection_AsciiString& theName,
                                 const int                      theRef,
                                 const TCollection_AsciiString& theType)
    : myName(theName),
      myType(theType),
      myRef(theRef)
{
}

void StdStorage_Root::SetName(const TCollection_AsciiString& theName)
{
  myName = theName;
}

TCollection_AsciiString StdStorage_Root::Name() const
{
  return myName;
}

void StdStorage_Root::SetObject(const occ::handle<StdObjMgt_Persistent>& anObject)
{
  myObject = anObject;
}

occ::handle<StdObjMgt_Persistent> StdStorage_Root::Object() const
{
  return myObject;
}

TCollection_AsciiString StdStorage_Root::Type() const
{
  return myType;
}

void StdStorage_Root::SetReference(const int aRef)
{
  myRef = aRef;
}

int StdStorage_Root::Reference() const
{
  return myRef;
}

void StdStorage_Root::SetType(const TCollection_AsciiString& aType)
{
  myType = aType;
}
