#pragma once

#include <LDOM_Attr.hpp>
#include <LDOM_NodeList.hpp>

class LDOM_BasicElement;

class LDOM_Element : public LDOM_Node
{
public:
  LDOM_Element() = default;

  LDOM_Element(const LDOM_Element& anOther)

    = default;

  LDOM_Element& operator=(const LDOM_Element& anOther)
  {
    return (LDOM_Element&)LDOM_Node::operator=(anOther);
  }

  LDOM_Element& operator=(const LDOM_NullPtr* aNull)
  {
    return (LDOM_Element&)LDOM_Node::operator=(aNull);
  }

  LDOMString getTagName() const { return getNodeName(); }

  Standard_EXPORT LDOMString getAttribute(const LDOMString& aName) const;

  Standard_EXPORT LDOM_Attr getAttributeNode(const LDOMString& aName) const;

  Standard_EXPORT LDOM_NodeList getElementsByTagName(const LDOMString& aName) const;

  Standard_EXPORT void setAttribute(const LDOMString& aName, const LDOMString& aValue);

  Standard_EXPORT void setAttributeNode(const LDOM_Attr& aNewAttr);

  Standard_EXPORT void removeAttribute(const LDOMString& aName);

  Standard_EXPORT LDOM_Element GetChildByTagName(const LDOMString& aTagName) const;

  Standard_EXPORT LDOM_Element GetSiblingByTagName() const;

  Standard_EXPORT void ReplaceElement(const LDOM_Element& anOther);

  Standard_EXPORT LDOM_NodeList GetAttributesList() const;

protected:
  friend class LDOM_Document;
  friend class LDOMParser;

  LDOM_Element(const LDOM_BasicElement& anElem, const occ::handle<LDOM_MemManager>& aDoc);

private:
};
