#include <Message_Messenger.hpp>
#include <Standard_PCharacter.hpp>
#include <Standard_Type.hpp>
#include <TDF_Label.hpp>
#include <TDF_Tool.hpp>
#include <XCAFDoc_GraphNode.hpp>
#include <XmlMXCAFDoc_GraphNodeDriver.hpp>
#include <XmlObjMgt.hpp>
#include <XmlObjMgt_Persistent.hpp>

IMPLEMENT_STANDARD_RTTIEXT(XmlMXCAFDoc_GraphNodeDriver, XmlMDF_ADriver)
IMPLEMENT_DOMSTRING(TreeIdString, "treeid")
IMPLEMENT_DOMSTRING(ChildrenString, "children")
IMPLEMENT_DOMSTRING(FathersString, "fathers")

XmlMXCAFDoc_GraphNodeDriver::XmlMXCAFDoc_GraphNodeDriver(
  const occ::handle<Message_Messenger>& theMsgDriver)
    : XmlMDF_ADriver(theMsgDriver, "xcaf", "GraphNode")
{
}

occ::handle<TDF_Attribute> XmlMXCAFDoc_GraphNodeDriver::NewEmpty() const
{
  return (new XCAFDoc_GraphNode());
}

bool XmlMXCAFDoc_GraphNodeDriver::Paste(const XmlObjMgt_Persistent&       theSource,
                                        const occ::handle<TDF_Attribute>& theTarget,
                                        XmlObjMgt_RRelocationTable&       theRelocTable) const
{
  occ::handle<XCAFDoc_GraphNode> aT        = occ::down_cast<XCAFDoc_GraphNode>(theTarget);
  const XmlObjMgt_Element&       anElement = theSource;

  XmlObjMgt_DOMString aGUIDStr = anElement.getAttribute(::TreeIdString());
  Standard_GUID       aGUID(static_cast<const char*>(aGUIDStr.GetString()));
  aT->SetGraphID(aGUID);

  XmlObjMgt_DOMString            aDOMStr;
  occ::handle<XCAFDoc_GraphNode> aTChild;

  aDOMStr = anElement.getAttribute(::FathersString());
  if (aDOMStr != nullptr)
  {
    const char* aChildren = static_cast<const char*>(aDOMStr.GetString());
    int         aNb       = 0;
    if (!XmlObjMgt::GetInteger(aChildren, aNb))
      return false;

    while (aNb > 0)
    {

      if (theRelocTable.IsBound(aNb))
      {
        aTChild = occ::down_cast<XCAFDoc_GraphNode>(theRelocTable.Find(aNb));
        if (aTChild.IsNull())
          return false;
      }
      else
      {
        aTChild = new XCAFDoc_GraphNode;
        theRelocTable.Bind(aNb, aTChild);
      }

      aTChild->SetGraphID(aGUID);
      aT->SetFather(aTChild);

      if (!XmlObjMgt::GetInteger(aChildren, aNb))
        aNb = 0;
    }
  }

  aDOMStr = anElement.getAttribute(::ChildrenString());
  if (aDOMStr != nullptr)
  {
    const char* aChildren = static_cast<const char*>(aDOMStr.GetString());
    int         aNb       = 0;
    if (!XmlObjMgt::GetInteger(aChildren, aNb))
      return false;

    while (aNb > 0)
    {

      if (theRelocTable.IsBound(aNb))
      {
        aTChild = occ::down_cast<XCAFDoc_GraphNode>(theRelocTable.Find(aNb));
        if (aTChild.IsNull())
          return false;
      }
      else
      {
        aTChild = new XCAFDoc_GraphNode;
        theRelocTable.Bind(aNb, aTChild);
      }

      aTChild->SetGraphID(aGUID);
      aT->SetChild(aTChild);

      if (!XmlObjMgt::GetInteger(aChildren, aNb))
        aNb = 0;
    }
  }

  return true;
}

void XmlMXCAFDoc_GraphNodeDriver::Paste(const occ::handle<TDF_Attribute>& theSource,
                                        XmlObjMgt_Persistent&             theTarget,
                                        XmlObjMgt_SRelocationTable&       theRelocTable) const
{
  occ::handle<XCAFDoc_GraphNode> aS = occ::down_cast<XCAFDoc_GraphNode>(theSource);
  if (aS.IsNull())
    return;

  char                aGuidStr[40];
  Standard_PCharacter pGuidStr;

  pGuidStr = (Standard_PCharacter)aGuidStr;
  aS->ID().ToCString(pGuidStr);
  theTarget.Element().setAttribute(::TreeIdString(), aGuidStr);

  int                            aNb;
  TCollection_AsciiString        aStr;
  occ::handle<XCAFDoc_GraphNode> aF;
  int                            i;

  for (i = 1; i <= aS->NbFathers(); i++)
  {
    aF = aS->GetFather(i);
    if (!aF.IsNull())
    {
      aNb = theRelocTable.FindIndex(aF);
      if (aNb == 0)
      {
        aNb = theRelocTable.Add(aF);
      }
      TCollection_AsciiString aNbStr(aNb);
      aStr += aNbStr + " ";
    }
  }
  if (aStr.Length() > 0)
    theTarget.Element().setAttribute(::FathersString(), aStr.ToCString());

  aStr.Clear();
  for (i = 1; i <= aS->NbChildren(); i++)
  {
    aF = aS->GetChild(i);
    if (!aF.IsNull())
    {
      aNb = theRelocTable.FindIndex(aF);
      if (aNb == 0)
      {
        aNb = theRelocTable.Add(aF);
      }
      TCollection_AsciiString aNbStr(aNb);
      aStr += aNbStr + " ";
    }
  }
  if (aStr.Length() > 0)
    theTarget.Element().setAttribute(::ChildrenString(), aStr.ToCString());
}
