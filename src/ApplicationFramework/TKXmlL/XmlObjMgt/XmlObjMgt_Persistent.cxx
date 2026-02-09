#include <XmlObjMgt.hpp>
#include <XmlObjMgt_Document.hpp>
#include <XmlObjMgt_Persistent.hpp>

XmlObjMgt_Persistent::XmlObjMgt_Persistent()
    : myID(0)
{
}

XmlObjMgt_Persistent::XmlObjMgt_Persistent(const XmlObjMgt_Element& theElement)
    : myElement(theElement),
      myID(0)
{
  if (theElement != nullptr)
    theElement.getAttribute(XmlObjMgt::IdString()).GetInteger(myID);
}

XmlObjMgt_Persistent::XmlObjMgt_Persistent(const XmlObjMgt_Element&   theElement,
                                           const XmlObjMgt_DOMString& theRef)
    : myID(0)
{
  if (theElement != nullptr)
  {
    int aRefID;
    if (theElement.getAttribute(theRef).GetInteger(aRefID))
    {
      myElement = XmlObjMgt::FindChildElement(theElement, aRefID);
      if (myElement != nullptr)
        myElement.getAttribute(XmlObjMgt::IdString()).GetInteger(myID);
    }
  }
}

void XmlObjMgt_Persistent::CreateElement(XmlObjMgt_Element&         theParent,
                                         const XmlObjMgt_DOMString& theType,
                                         const int                  theID)
{

  XmlObjMgt_Document anOwnerDoc = XmlObjMgt_Document(theParent.getOwnerDocument());
  myElement                     = anOwnerDoc.createElement(theType);
  theParent.appendChild(myElement);
  SetId(theID);
}

void XmlObjMgt_Persistent::SetId(const int theId)
{
  myID = theId;
  myElement.setAttribute(XmlObjMgt::IdString(), theId);
}
