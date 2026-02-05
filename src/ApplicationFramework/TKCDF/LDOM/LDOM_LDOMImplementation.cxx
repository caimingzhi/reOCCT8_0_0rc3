#include <LDOM_LDOMImplementation.hpp>

//=================================================================================================

LDOM_Document LDOM_LDOMImplementation::createDocument(const LDOMString& /*aNamespaceURI*/,
                                                      const LDOMString& aQualifiedName,
                                                      const LDOM_DocumentType& /*aDocType*/)
{
  return LDOM_Document::createDocument(aQualifiedName);
}
