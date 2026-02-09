#pragma once

#include <Standard_OStream.hpp>
#include <Standard_TypeDef.hpp>

class LDOM_Document;
class LDOM_Node;
class LDOMBasicString;

class LDOM_XmlWriter
{
public:
  Standard_EXPORT LDOM_XmlWriter(const char* theEncoding = nullptr);

  Standard_EXPORT ~LDOM_XmlWriter();

  void SetIndentation(const int theIndent) { myIndent = theIndent; }

  Standard_EXPORT void Write(Standard_OStream& theOStream, const LDOM_Document& theDoc);

  Standard_EXPORT void Write(Standard_OStream& theOStream, const LDOM_Node& theNode);

private:
  LDOM_XmlWriter(const LDOM_XmlWriter& anOther) = delete;

  LDOM_XmlWriter& operator=(const LDOM_XmlWriter& anOther) = delete;

  void Write(Standard_OStream& theOStream, const LDOMBasicString& theString);
  void Write(Standard_OStream& theOStream, const char* theString);
  void Write(Standard_OStream& theOStream, const char theChar);

  void WriteAttribute(Standard_OStream& theOStream, const LDOM_Node& theAtt);

private:
  char* myEncodingName;
  int   myIndent;
  int   myCurIndent;
  char* myABuffer;
  int   myABufferLen;
};
