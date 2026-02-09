#pragma once

#include <LDOM_Document.hpp>
#include <LDOM_OSStream.hpp>

class LDOM_XmlReader;

class LDOMParser
{
public:
  LDOMParser()
      : myReader(nullptr),
        myCurrentData(16384)
  {
  }

  virtual Standard_EXPORT ~LDOMParser();

  Standard_EXPORT LDOM_Document getDocument();

  Standard_EXPORT bool parse(const char* const aFileName);

  Standard_EXPORT bool parse(std::istream& anInput,
                             const bool    theTagPerStep  = false,
                             const bool    theWithoutRoot = false);

  Standard_EXPORT const TCollection_AsciiString& GetError(TCollection_AsciiString& aData) const;

  Standard_EXPORT LDOM_OSStream::BOMType GetBOM() const;

protected:
  Standard_EXPORT virtual bool startElement();

  Standard_EXPORT virtual bool endElement();

  Standard_EXPORT LDOM_Element getCurrentElement() const;

private:
  bool ParseDocument(Standard_IStream& theIStream, const bool theWithoutRoot = false);

  bool ParseElement(Standard_IStream& theIStream, bool& theDocStart);

  LDOMParser(const LDOMParser& theOther) = delete;

  LDOMParser& operator=(const LDOMParser& theOther) = delete;

private:
  LDOM_XmlReader*              myReader;
  occ::handle<LDOM_MemManager> myDocument;
  LDOM_OSStream                myCurrentData;
  TCollection_AsciiString      myError;
};
