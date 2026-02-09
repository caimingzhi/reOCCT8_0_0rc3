#pragma once

#define XML_BUFFER_SIZE 20480

#include <LDOM_BasicElement.hpp>
#include <LDOM_OSStream.hpp>

class TCollection_AsciiString;

class LDOM_XmlReader
{
public:
  enum RecordType
  {
    XML_UNKNOWN,
    XML_HEADER,
    XML_DOCTYPE,
    XML_COMMENT,
    XML_START_ELEMENT,
    XML_END_ELEMENT,
    XML_FULL_ELEMENT,
    XML_TEXT,
    XML_CDATA,
    XML_EOF
  };

  LDOM_XmlReader(const occ::handle<LDOM_MemManager>& aDocument,
                 TCollection_AsciiString&            anErrorString,
                 const bool                          theTagPerStep = false);

  RecordType ReadRecord(Standard_IStream& theIStream, LDOM_OSStream& theData, bool& theDocStart);

  LDOM_BasicElement& GetElement() const { return *myElement; }

  void CreateElement(const char* theName, const int theLen);

  static bool getInteger(LDOMBasicString& theValue, const char* theStart, const char* theEnd);

  LDOM_OSStream::BOMType GetBOM() const { return myBOM; }

private:
  LDOM_XmlReader(const LDOM_XmlReader& theOther) = delete;

  LDOM_XmlReader& operator=(const LDOM_XmlReader& theOther) = delete;

private:
  bool                         myEOF;
  TCollection_AsciiString&     myError;
  occ::handle<LDOM_MemManager> myDocument;
  LDOM_BasicElement*           myElement;
  const LDOM_BasicNode*        myLastChild;
  const char*                  myPtr;
  const char*                  myEndPtr;
  char                         myBuffer[XML_BUFFER_SIZE + 4];
  bool                         myTagPerStep;
  LDOM_OSStream::BOMType       myBOM;
};
