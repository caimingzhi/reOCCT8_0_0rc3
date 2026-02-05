#pragma once

// #define XML_BUFFER_SIZE 1000
#define XML_BUFFER_SIZE 20480

#include <LDOM_BasicElement.hpp>
#include <LDOM_OSStream.hpp>

class TCollection_AsciiString;

//  Class LDOM_XmlReader
//

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

  // ---------- PUBLIC METHODS ----------
  LDOM_XmlReader(const occ::handle<LDOM_MemManager>& aDocument,
                 TCollection_AsciiString&            anErrorString,
                 const bool                          theTagPerStep = false);
  // Constructor - takes a file descriptor for input
  // Constructor - takes an std::istream for input

  RecordType ReadRecord(Standard_IStream& theIStream, LDOM_OSStream& theData, bool& theDocStart);

  // reading a markup or other element of XML format

  LDOM_BasicElement& GetElement() const { return *myElement; }

  // get the last element retrieved from the stream

  void CreateElement(const char* theName, const int theLen);

  static bool getInteger(LDOMBasicString& theValue, const char* theStart, const char* theEnd);

  // try convert string theStart to LDOM_AsciiInteger, return False on success

  // Returns the byte order mask defined at the start of a stream
  LDOM_OSStream::BOMType GetBOM() const { return myBOM; }

private:
  // ---------- PRIVATE (PROHIBITED) METHODS ----------
  LDOM_XmlReader(const LDOM_XmlReader& theOther) = delete;
  // Copy constructor

  LDOM_XmlReader& operator=(const LDOM_XmlReader& theOther) = delete;
  // Assignment

private:
  // ---------- PRIVATE FIELDS ----------

  bool                         myEOF;
  TCollection_AsciiString&     myError;
  occ::handle<LDOM_MemManager> myDocument;
  LDOM_BasicElement*           myElement;
  const LDOM_BasicNode*        myLastChild; // optim. reading attributes
  const char*                  myPtr;
  const char*                  myEndPtr;
  char                         myBuffer[XML_BUFFER_SIZE + 4];
  bool                         myTagPerStep;
  LDOM_OSStream::BOMType       myBOM;
};
