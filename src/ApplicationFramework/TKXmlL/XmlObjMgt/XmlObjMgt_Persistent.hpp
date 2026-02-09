#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <XmlObjMgt_Element.hpp>
#include <Standard_Integer.hpp>
#include <XmlObjMgt_DOMString.hpp>

class XmlObjMgt_Persistent
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT XmlObjMgt_Persistent();

  Standard_EXPORT XmlObjMgt_Persistent(const XmlObjMgt_Element& theElement);

  Standard_EXPORT XmlObjMgt_Persistent(const XmlObjMgt_Element&   theElement,
                                       const XmlObjMgt_DOMString& theRef);

  Standard_EXPORT void CreateElement(XmlObjMgt_Element&         theParent,
                                     const XmlObjMgt_DOMString& theType,
                                     const int                  theID);

  Standard_EXPORT void SetId(const int theId);

  const XmlObjMgt_Element& Element() const;
  inline                   operator const XmlObjMgt_Element&() const;

  XmlObjMgt_Element& Element();
  inline             operator XmlObjMgt_Element&();

  int Id() const;

private:
  XmlObjMgt_Element myElement;
  int               myID;
};

inline const XmlObjMgt_Element& XmlObjMgt_Persistent::Element() const
{
  return myElement;
}

inline XmlObjMgt_Element& XmlObjMgt_Persistent::Element()
{
  return myElement;
}

inline XmlObjMgt_Persistent::operator const XmlObjMgt_Element&() const
{
  return myElement;
}

inline XmlObjMgt_Persistent::operator XmlObjMgt_Element&()
{
  return myElement;
}

inline int XmlObjMgt_Persistent::Id() const
{
  return myID;
}
