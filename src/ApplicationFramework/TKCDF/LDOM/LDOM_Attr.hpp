#pragma once

#include <LDOM_Node.hpp>

class LDOM_BasicAttribute;

class LDOM_Attr : public LDOM_Node
{
public:
  LDOM_Attr() = default;

  LDOM_Attr(const LDOM_Attr& anOther)

    = default;

  LDOM_Attr& operator=(const LDOM_NullPtr* aNull)
  {
    return (LDOM_Attr&)LDOM_Node::operator=(aNull);
  }

  LDOM_Attr& operator=(const LDOM_Attr& anOther)
  {
    return (LDOM_Attr&)LDOM_Node::operator=(anOther);
  }

  LDOMString getName() const { return getNodeName(); }

  LDOMString getValue() const { return getNodeValue(); }

  Standard_EXPORT void setValue(const LDOMString& aValue);

protected:
  friend class LDOM_Element;

  LDOM_Attr(const LDOM_BasicAttribute& anAttr, const occ::handle<LDOM_MemManager>& aDoc);

private:
};
