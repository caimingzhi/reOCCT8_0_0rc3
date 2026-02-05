#pragma once

#include <LDOM_Node.hpp>

class LDOM_BasicAttribute;

//  Class LDOM_Attr
//

class LDOM_Attr : public LDOM_Node
{
public:
  // ---------- PUBLIC METHODS ----------

  LDOM_Attr() = default;

  //    Empty constructor

  LDOM_Attr(const LDOM_Attr& anOther)

    = default;

  //    Copy constructor

  LDOM_Attr& operator=(const LDOM_NullPtr* aNull)
  {
    return (LDOM_Attr&)LDOM_Node::operator=(aNull);
  }

  //    Nullify

  LDOM_Attr& operator=(const LDOM_Attr& anOther)
  {
    return (LDOM_Attr&)LDOM_Node::operator=(anOther);
  }

  //    Assignment

  LDOMString getName() const { return getNodeName(); }

  LDOMString getValue() const { return getNodeValue(); }

  Standard_EXPORT void setValue(const LDOMString& aValue);

protected:
  friend class LDOM_Element;
  // ---------- PROTECTED METHODS ----------

  LDOM_Attr(const LDOM_BasicAttribute& anAttr, const occ::handle<LDOM_MemManager>& aDoc);

private:
  // ---------- PRIVATE FIELDS ----------
};
