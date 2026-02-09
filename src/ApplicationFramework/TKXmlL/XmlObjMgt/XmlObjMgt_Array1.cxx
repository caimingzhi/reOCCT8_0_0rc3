#include <XmlObjMgt.hpp>
#include <XmlObjMgt_Array1.hpp>
#include <XmlObjMgt_Document.hpp>
#include <XmlObjMgt_DOMString.hpp>

IMPLEMENT_DOMSTRING(LowerString, "lower")
IMPLEMENT_DOMSTRING(UpperString, "upper")
IMPLEMENT_DOMSTRING(IndString, "index")

XmlObjMgt_Array1::XmlObjMgt_Array1(const XmlObjMgt_Element&   theParent,
                                   const XmlObjMgt_DOMString& theName)
    : myElement(XmlObjMgt::FindChildByName(theParent, theName)),
      myFirst(1),
      myLast(0)
{
  if (myElement != nullptr)
  {
    if (!myElement.getAttribute(::LowerString()).GetInteger(myFirst))
      myFirst = 1;
    if (!myElement.getAttribute(::UpperString()).GetInteger(myLast))
      myLast = 1;
  }
}

XmlObjMgt_Array1::XmlObjMgt_Array1(const int aFirst, const int aLast)
    : myFirst(aFirst),
      myLast(aLast)
{
}

void XmlObjMgt_Array1::CreateArrayElement(XmlObjMgt_Element&         theParent,
                                          const XmlObjMgt_DOMString& theName)
{
  if (myLast > 0)
  {

    XmlObjMgt_Document anOwnerDoc = XmlObjMgt_Document(theParent.getOwnerDocument());
    myElement                     = anOwnerDoc.createElement(theName);
    theParent.appendChild(myElement);
    if (myLast > 1)
    {
      myElement.setAttribute(::UpperString(), myLast);
      if (myFirst != 1)
        myElement.setAttribute(::LowerString(), myFirst);
    }
  }
}

void XmlObjMgt_Array1::SetValue(const int theIndex, XmlObjMgt_Element& theValue)
{
  myElement.appendChild(theValue);
  theValue.setAttribute(::IndString(), theIndex);
}

XmlObjMgt_Element XmlObjMgt_Array1::Value(const int theIndex) const
{
  XmlObjMgt_Element anElem;

  if (theIndex >= myFirst && theIndex <= myLast)
  {
    int       ind;
    LDOM_Node aNode = myElement.getFirstChild();
    while (!aNode.isNull())
    {
      if (aNode.getNodeType() == LDOM_Node::ELEMENT_NODE)
      {
        anElem = (XmlObjMgt_Element&)aNode;
        if (anElem.getAttribute(::IndString()).GetInteger(ind))
          if (ind == theIndex)
            break;
      }
      aNode = aNode.getNextSibling();
    }
  }
  return anElem;
}
