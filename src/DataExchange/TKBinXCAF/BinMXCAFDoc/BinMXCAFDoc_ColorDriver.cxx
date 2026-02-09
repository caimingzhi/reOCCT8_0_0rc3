#include <BinMXCAFDoc_ColorDriver.hpp>
#include <BinObjMgt_Persistent.hpp>
#include <Message_Messenger.hpp>
#include <Standard_Type.hpp>
#include <TDF_Attribute.hpp>
#include <XCAFDoc_Color.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BinMXCAFDoc_ColorDriver, BinMDF_ADriver)

BinMXCAFDoc_ColorDriver::BinMXCAFDoc_ColorDriver(const occ::handle<Message_Messenger>& theMsgDriver)
    : BinMDF_ADriver(theMsgDriver, STANDARD_TYPE(XCAFDoc_Color)->Name())
{
}

occ::handle<TDF_Attribute> BinMXCAFDoc_ColorDriver::NewEmpty() const
{
  return new XCAFDoc_Color();
}

bool BinMXCAFDoc_ColorDriver::Paste(const BinObjMgt_Persistent&       theSource,
                                    const occ::handle<TDF_Attribute>& theTarget,
                                    BinObjMgt_RRelocationTable&) const
{
  occ::handle<XCAFDoc_Color> anAtt = occ::down_cast<XCAFDoc_Color>(theTarget);
  double                     R, G, B;
  float                      alpha;
  bool                       isOk = theSource >> R >> G >> B;
  if (isOk)
  {
    bool isRGBA = theSource >> alpha;
    if (!isRGBA)
      alpha = 1.0;
    anAtt->Set(R, G, B, alpha);
  }
  return isOk;
}

void BinMXCAFDoc_ColorDriver::Paste(const occ::handle<TDF_Attribute>& theSource,
                                    BinObjMgt_Persistent&             theTarget,
                                    NCollection_IndexedMap<occ::handle<Standard_Transient>>&) const
{
  occ::handle<XCAFDoc_Color> anAtt = occ::down_cast<XCAFDoc_Color>(theSource);
  double                     R, G, B;
  float                      alpha;
  anAtt->GetRGB(R, G, B);
  alpha = anAtt->GetAlpha();
  theTarget << R << G << B << alpha;
}
