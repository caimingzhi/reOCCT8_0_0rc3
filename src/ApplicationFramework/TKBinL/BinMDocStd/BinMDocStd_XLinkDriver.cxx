#include <BinMDF_ADriver.hpp>
#include <BinMDocStd_XLinkDriver.hpp>
#include <BinObjMgt_Persistent.hpp>
#include <BinObjMgt_RRelocationTable.hpp>
#include <Standard_Transient.hpp>
#include <NCollection_IndexedMap.hpp>
#include <Message_Messenger.hpp>
#include <Standard_Type.hpp>
#include <TDF_Attribute.hpp>
#include <TDocStd_XLink.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BinMDocStd_XLinkDriver, BinMDF_ADriver)

BinMDocStd_XLinkDriver::BinMDocStd_XLinkDriver(const occ::handle<Message_Messenger>& theMsgDriver)
    : BinMDF_ADriver(theMsgDriver, STANDARD_TYPE(TDocStd_XLink)->Name())
{
}

occ::handle<TDF_Attribute> BinMDocStd_XLinkDriver::NewEmpty() const
{
  return new TDocStd_XLink();
}

bool BinMDocStd_XLinkDriver::Paste(const BinObjMgt_Persistent&       theSource,
                                   const occ::handle<TDF_Attribute>& theTarget,
                                   BinObjMgt_RRelocationTable&) const
{
  TCollection_AsciiString aStr;
  bool                    ok = theSource >> aStr;
  if (ok)
  {
    occ::handle<TDocStd_XLink> anAtt = occ::down_cast<TDocStd_XLink>(theTarget);
    anAtt->DocumentEntry(aStr);
    aStr.Clear();
    ok = theSource >> aStr;
    if (ok)
      anAtt->LabelEntry(aStr);
  }
  return ok;
}

void BinMDocStd_XLinkDriver::Paste(const occ::handle<TDF_Attribute>& theSource,
                                   BinObjMgt_Persistent&             theTarget,
                                   NCollection_IndexedMap<occ::handle<Standard_Transient>>&) const
{
  occ::handle<TDocStd_XLink> anAtt = occ::down_cast<TDocStd_XLink>(theSource);
  theTarget << anAtt->DocumentEntry() << anAtt->LabelEntry();
}
