#include <BinMXCAFDoc_GraphNodeDriver.hpp>
#include <BinObjMgt_Persistent.hpp>
#include <Message_Messenger.hpp>
#include <Standard_Type.hpp>
#include <TDF_Attribute.hpp>
#include <XCAFDoc_GraphNode.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BinMXCAFDoc_GraphNodeDriver, BinMDF_ADriver)

BinMXCAFDoc_GraphNodeDriver::BinMXCAFDoc_GraphNodeDriver(
  const occ::handle<Message_Messenger>& theMsgDriver)
    : BinMDF_ADriver(theMsgDriver, STANDARD_TYPE(XCAFDoc_GraphNode)->Name())
{
}

occ::handle<TDF_Attribute> BinMXCAFDoc_GraphNodeDriver::NewEmpty() const
{
  return new XCAFDoc_GraphNode();
}

bool BinMXCAFDoc_GraphNodeDriver::Paste(const BinObjMgt_Persistent&       theSource,
                                        const occ::handle<TDF_Attribute>& theTarget,
                                        BinObjMgt_RRelocationTable&       theRelocTable) const
{
  occ::handle<XCAFDoc_GraphNode> aT = occ::down_cast<XCAFDoc_GraphNode>(theTarget);
  int                            anID;

  if (!(theSource >> anID))
    return false;
  while (anID != -1)
  {
    occ::handle<XCAFDoc_GraphNode> aNode;
    if (theRelocTable.IsBound(anID))
    {
      aNode = occ::down_cast<XCAFDoc_GraphNode>(theRelocTable.Find(anID));
    }
    else
    {
      aNode = occ::down_cast<XCAFDoc_GraphNode>(aT->NewEmpty());
      theRelocTable.Bind(anID, aNode);
    }
    aT->SetFather(aNode);

    if (!(theSource >> anID))
      return false;
  }

  if (!(theSource >> anID))
    return false;
  while (anID != -1)
  {
    occ::handle<XCAFDoc_GraphNode> aNode;
    if (theRelocTable.IsBound(anID))
    {
      aNode = occ::down_cast<XCAFDoc_GraphNode>(theRelocTable.Find(anID));
    }
    else
    {
      aNode = occ::down_cast<XCAFDoc_GraphNode>(aT->NewEmpty());
      theRelocTable.Bind(anID, aNode);
    }
    aT->SetChild(aNode);

    if (!(theSource >> anID))
      return false;
  }

  Standard_GUID aGUID;
  if (!(theSource >> aGUID))
    return false;
  aT->SetGraphID(aGUID);

  return true;
}

void BinMXCAFDoc_GraphNodeDriver::Paste(
  const occ::handle<TDF_Attribute>&                        theSource,
  BinObjMgt_Persistent&                                    theTarget,
  NCollection_IndexedMap<occ::handle<Standard_Transient>>& theRelocTable) const
{
  occ::handle<XCAFDoc_GraphNode> aS = occ::down_cast<XCAFDoc_GraphNode>(theSource);
  int                            i, aNb, anID;

  aNb = aS->NbFathers();
  for (i = 1; i <= aNb; i++)
  {
    occ::handle<XCAFDoc_GraphNode> aNode = aS->GetFather(i);
    anID                                 = theRelocTable.Add(aNode);
    theTarget << anID;
  }
  theTarget.PutInteger(-1);

  aNb = aS->NbChildren();
  for (i = 1; i <= aNb; i++)
  {
    occ::handle<XCAFDoc_GraphNode> aNode = aS->GetChild(i);
    anID                                 = theRelocTable.Add(aNode);
    theTarget << anID;
  }
  theTarget.PutInteger(-1);

  theTarget << aS->ID();
}
