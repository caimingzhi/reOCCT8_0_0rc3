#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <XmlObjMgt_Element.hpp>
#include <Standard_Integer.hpp>
#include <XmlObjMgt_DOMString.hpp>

class XmlObjMgt_Array1
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT XmlObjMgt_Array1(const int Low, const int Up);

  Standard_EXPORT XmlObjMgt_Array1(const XmlObjMgt_Element&   theParent,
                                   const XmlObjMgt_DOMString& theName);

  Standard_EXPORT void CreateArrayElement(XmlObjMgt_Element&         theParent,
                                          const XmlObjMgt_DOMString& theName);

  const XmlObjMgt_Element& Element() const;

  int Length() const;

  int Lower() const;

  int Upper() const;

  Standard_EXPORT void SetValue(const int Index, XmlObjMgt_Element& Value);

  Standard_EXPORT XmlObjMgt_Element Value(const int Index) const;

private:
  XmlObjMgt_Element myElement;
  int               myFirst;
  int               myLast;
};

inline const XmlObjMgt_Element& XmlObjMgt_Array1::Element() const
{
  return myElement;
}

inline int XmlObjMgt_Array1::Length() const
{
  return myLast - myFirst + 1;
}

inline int XmlObjMgt_Array1::Lower() const
{
  return myFirst;
}

inline int XmlObjMgt_Array1::Upper() const
{
  return myLast;
}
