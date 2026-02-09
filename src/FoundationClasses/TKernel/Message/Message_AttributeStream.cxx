

#include <Message_AttributeStream.hpp>
#include <Standard_Dump.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Message_AttributeStream, Message_Attribute)

Message_AttributeStream::Message_AttributeStream(const Standard_SStream&        theStream,
                                                 const TCollection_AsciiString& theName)
    : Message_Attribute(theName)
{
  SetStream(theStream);
}

void Message_AttributeStream::SetStream(const Standard_SStream& theStream)
{
  myStream.str("");
  myStream << theStream.str().c_str();
}

void Message_AttributeStream::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)
  OCCT_DUMP_BASE_CLASS(theOStream, theDepth, Message_Attribute)

  OCCT_DUMP_STREAM_VALUE_DUMPED(theOStream, myStream)
}
