#pragma once

#include <LDOMParser.hpp>

class PCDM_DOMHeaderParser : public LDOMParser
{
public:
  void SetStartElementName(const TCollection_AsciiString& aStartElementName);

  void SetEndElementName(const TCollection_AsciiString& anEndElementName);

  bool startElement() override;

  bool endElement() override;

  const LDOM_Element& GetElement() const { return myElement; }

private:
  LDOM_Element myElement;
  LDOMString   myStartElementName;
  LDOMString   myEndElementName;
};
