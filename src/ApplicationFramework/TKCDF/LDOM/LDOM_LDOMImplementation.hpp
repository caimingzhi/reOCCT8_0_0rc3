#pragma once

#include <LDOM_Document.hpp>

class LDOM_DocumentType;

//  Block of comments describing class LDOM_LDOMImplementation
//

class LDOM_LDOMImplementation
{
public:
  // ---------- PUBLIC METHODS ----------

  static Standard_EXPORT LDOM_Document createDocument(const LDOMString&        aNamespaceURI,
                                                      const LDOMString&        aQualifiedName,
                                                      const LDOM_DocumentType& aDocType);
};
