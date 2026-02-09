#include <BinMXCAFDoc_CentroidDriver.hpp>
#include <BinObjMgt_Persistent.hpp>
#include <Message_Messenger.hpp>
#include <Standard_Type.hpp>
#include <TDF_Attribute.hpp>
#include <XCAFDoc_Centroid.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BinMXCAFDoc_CentroidDriver, BinMDF_ADriver)

BinMXCAFDoc_CentroidDriver::BinMXCAFDoc_CentroidDriver(
  const occ::handle<Message_Messenger>& theMsgDriver)
    : BinMDF_ADriver(theMsgDriver, STANDARD_TYPE(XCAFDoc_Centroid)->Name())
{
}

occ::handle<TDF_Attribute> BinMXCAFDoc_CentroidDriver::NewEmpty() const
{
  return new XCAFDoc_Centroid();
}

bool BinMXCAFDoc_CentroidDriver::Paste(const BinObjMgt_Persistent&       theSource,
                                       const occ::handle<TDF_Attribute>& theTarget,
                                       BinObjMgt_RRelocationTable&) const
{
  occ::handle<XCAFDoc_Centroid> anAtt = occ::down_cast<XCAFDoc_Centroid>(theTarget);
  double                        x, y, z;
  bool                          isOk = theSource >> x >> y >> z;
  if (isOk)
  {
    gp_Pnt aPnt(x, y, z);
    anAtt->Set(aPnt);
  }
  return isOk;
}

void BinMXCAFDoc_CentroidDriver::Paste(
  const occ::handle<TDF_Attribute>& theSource,
  BinObjMgt_Persistent&             theTarget,
  NCollection_IndexedMap<occ::handle<Standard_Transient>>&) const
{
  occ::handle<XCAFDoc_Centroid> anAtt = occ::down_cast<XCAFDoc_Centroid>(theSource);
  gp_Pnt                        aPnt  = anAtt->Get();
  theTarget << aPnt.X() << aPnt.Y() << aPnt.Z();
}
