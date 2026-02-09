#include <PCDM_DOMHeaderParser.hpp>

void PCDM_DOMHeaderParser::SetStartElementName(const TCollection_AsciiString& aStartElementName)
{
  myStartElementName = LDOMString(aStartElementName.ToCString());
}

void PCDM_DOMHeaderParser::SetEndElementName(const TCollection_AsciiString& anEndElementName)
{
  myEndElementName = LDOMString(anEndElementName.ToCString());
}

bool PCDM_DOMHeaderParser::startElement()
{
  if (myStartElementName == nullptr)
    return false;
  myElement = getCurrentElement();
  return (myElement.getTagName().equals(myStartElementName));
}

bool PCDM_DOMHeaderParser::endElement()
{
  if (myEndElementName == nullptr)
    return false;
  myElement = getCurrentElement();
  return (myElement.getTagName().equals(myEndElementName));
}
