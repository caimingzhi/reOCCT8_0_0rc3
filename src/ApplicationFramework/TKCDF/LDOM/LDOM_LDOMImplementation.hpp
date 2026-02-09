#pragma once

#include <LDOM_Document.hpp>

class LDOM_DocumentType;

class LDOM_LDOMImplementation
{
public:
  static Standard_EXPORT LDOM_Document createDocument(const LDOMString&        aNamespaceURI,
                                                      const LDOMString&        aQualifiedName,
                                                      const LDOM_DocumentType& aDocType);
};
