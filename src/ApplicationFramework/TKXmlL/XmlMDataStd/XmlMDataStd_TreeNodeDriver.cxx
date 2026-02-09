#include <Message_Messenger.hpp>
#include <NCollection_LocalArray.hpp>
#include <Standard_Type.hpp>
#include <TDataStd_TreeNode.hpp>
#include <TDF_Attribute.hpp>
#include <TDocStd_FormatVersion.hpp>
#include <XmlMDataStd_TreeNodeDriver.hpp>
#include <XmlObjMgt.hpp>
#include <XmlObjMgt_Persistent.hpp>

IMPLEMENT_STANDARD_RTTIEXT(XmlMDataStd_TreeNodeDriver, XmlMDF_ADriver)
IMPLEMENT_DOMSTRING(TreeIdString, "treeid")
IMPLEMENT_DOMSTRING(ChildrenString, "children")

XmlMDataStd_TreeNodeDriver::XmlMDataStd_TreeNodeDriver(
  const occ::handle<Message_Messenger>& theMsgDriver)
    : XmlMDF_ADriver(theMsgDriver, nullptr)
{
}

occ::handle<TDF_Attribute> XmlMDataStd_TreeNodeDriver::NewEmpty() const
{
  return (new TDataStd_TreeNode());
}

bool XmlMDataStd_TreeNodeDriver::Paste(const XmlObjMgt_Persistent&       theSource,
                                       const occ::handle<TDF_Attribute>& theTarget,
                                       XmlObjMgt_RRelocationTable&       theRelocTable) const
{
  occ::handle<TDataStd_TreeNode> aT        = occ::down_cast<TDataStd_TreeNode>(theTarget);
  const XmlObjMgt_Element&       anElement = theSource;

  Standard_GUID       aGUID;
  XmlObjMgt_DOMString aGUIDStr = anElement.getAttribute(::TreeIdString());
  if (aGUIDStr.Type() == XmlObjMgt_DOMString::LDOM_NULL)
    aGUID = TDataStd_TreeNode::GetDefaultTreeID();
  else
    aGUID = Standard_GUID(static_cast<const char*>(aGUIDStr.GetString()));
  aT->SetTreeID(aGUID);

  occ::handle<TDataStd_TreeNode> aTChild;

  XmlObjMgt_DOMString aChildrenStr = anElement.getAttribute(::ChildrenString());
  if (aChildrenStr != nullptr)
  {
    const char* aChildren = static_cast<const char*>(aChildrenStr.GetString());
    int         aNb       = 0;
    if (!XmlObjMgt::GetInteger(aChildren, aNb))
      return false;

    while (aNb > 0)
    {

      if (theRelocTable.IsBound(aNb))
      {
        aTChild = occ::down_cast<TDataStd_TreeNode>(theRelocTable.Find(aNb));
        if (aTChild.IsNull())
          return false;
      }
      else
      {
        aTChild = new TDataStd_TreeNode;
        theRelocTable.Bind(aNb, aTChild);
      }

      aTChild->SetTreeID(aGUID);
      aT->Append(aTChild);

      if (!XmlObjMgt::GetInteger(aChildren, aNb))
        aNb = 0;
    }
  }
  return true;
}

void XmlMDataStd_TreeNodeDriver::Paste(const occ::handle<TDF_Attribute>& theSource,
                                       XmlObjMgt_Persistent&             theTarget,
                                       XmlObjMgt_SRelocationTable&       theRelocTable) const
{
  occ::handle<TDataStd_TreeNode> aS = occ::down_cast<TDataStd_TreeNode>(theSource);

  if (aS->ID() != TDataStd_TreeNode::GetDefaultTreeID()
      || theRelocTable.GetHeaderData()->StorageVersion().IntegerValue()
           < TDocStd_FormatVersion_VERSION_8)
  {
    char                aGuidStr[40];
    Standard_PCharacter pGuidStr = aGuidStr;
    aS->ID().ToCString(pGuidStr);
    theTarget.Element().setAttribute(::TreeIdString(), aGuidStr);
  }

  int nbChildren = aS->NbChildren();

  int                          iChar = 0;
  NCollection_LocalArray<char> str;
  if (nbChildren)
    str.Allocate(11 * nbChildren + 1);

  occ::handle<TDataStd_TreeNode> aF = aS->First();
  while (!aF.IsNull())
  {
    int aNb = theRelocTable.FindIndex(aF);
    if (aNb == 0)
    {
      aNb = theRelocTable.Add(aF);
    }

    iChar += Sprintf(&(str[iChar]), "%d ", aNb);

    aF = aF->Next();
  }

  if (nbChildren)
  {
    theTarget.Element().setAttribute(::ChildrenString(), (char*)str);
  }
}
