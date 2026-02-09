#pragma once

#include <Standard_Transient.hpp>
#include <NCollection_DefineAlloc.hpp>
#include <TCollection_AsciiString.hpp>

class Message_Attribute : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(Message_Attribute, Standard_Transient)
public:
  Standard_EXPORT Message_Attribute(
    const TCollection_AsciiString& theName = TCollection_AsciiString::EmptyString());

  Standard_EXPORT virtual const char* GetMessageKey() const;

  const TCollection_AsciiString& GetName() const { return myName; }

  void SetName(const TCollection_AsciiString& theName) { myName = theName; }

  virtual Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

private:
  TCollection_AsciiString myName;
};
