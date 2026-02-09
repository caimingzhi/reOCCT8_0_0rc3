#include <LDOM_LDOMImplementation.hpp>

LDOM_Document LDOM_LDOMImplementation::createDocument(const LDOMString&,
                                                      const LDOMString& aQualifiedName,
                                                      const LDOM_DocumentType&)
{
  return LDOM_Document::createDocument(aQualifiedName);
}
