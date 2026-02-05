#include <PCDM_DOMHeaderParser.hpp>

//=======================================================================
// function : SetStartElementName
// purpose  : set the name of the element which would stop parsing when detected
//=======================================================================

void PCDM_DOMHeaderParser::SetStartElementName(const TCollection_AsciiString& aStartElementName)
{
  myStartElementName = LDOMString(aStartElementName.ToCString());
}

//=======================================================================
// function : SetEndElementName
// purpose  : set the name of the element which would stop parsing when parsed
//=======================================================================

void PCDM_DOMHeaderParser::SetEndElementName(const TCollection_AsciiString& anEndElementName)
{
  myEndElementName = LDOMString(anEndElementName.ToCString());
}

//=================================================================================================

bool PCDM_DOMHeaderParser::startElement()
{
  if (myStartElementName == nullptr)
    return false;
  myElement = getCurrentElement();
  return (myElement.getTagName().equals(myStartElementName));
}

//=================================================================================================

bool PCDM_DOMHeaderParser::endElement()
{
  if (myEndElementName == nullptr)
    return false;
  myElement = getCurrentElement();
  return (myElement.getTagName().equals(myEndElementName));
}
