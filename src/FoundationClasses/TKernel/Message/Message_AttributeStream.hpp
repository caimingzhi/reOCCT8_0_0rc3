#pragma once

#include <Message_Attribute.hpp>
#include <TCollection_AsciiString.hpp>

#include <Standard_SStream.hpp>

//! Alert object storing stream value
class Message_AttributeStream : public Message_Attribute
{
  DEFINE_STANDARD_RTTIEXT(Message_AttributeStream, Message_Attribute)
public:
  //! Constructor with string argument
  Standard_EXPORT Message_AttributeStream(
    const Standard_SStream&        theStream,
    const TCollection_AsciiString& theName = TCollection_AsciiString::EmptyString());

  //! Returns stream value
  const Standard_SStream& Stream() const { return myStream; }

  //! Sets stream value
  Standard_EXPORT void SetStream(const Standard_SStream& theStream);

  //! Dumps the content of me into the stream
  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

private:
  Standard_SStream myStream; //!< container of values
};
