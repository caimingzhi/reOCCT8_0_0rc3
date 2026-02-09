#pragma once

#include <Message_Attribute.hpp>
#include <TCollection_AsciiString.hpp>

#include <Standard_SStream.hpp>

class Message_AttributeStream : public Message_Attribute
{
  DEFINE_STANDARD_RTTIEXT(Message_AttributeStream, Message_Attribute)
public:
  Standard_EXPORT Message_AttributeStream(
    const Standard_SStream&        theStream,
    const TCollection_AsciiString& theName = TCollection_AsciiString::EmptyString());

  const Standard_SStream& Stream() const { return myStream; }

  Standard_EXPORT void SetStream(const Standard_SStream& theStream);

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

private:
  Standard_SStream myStream;
};
