#include <BinMDataStd_IntegerDriver.hpp>
#include <Message_Messenger.hpp>
#include <Standard_Type.hpp>
#include <TDataStd_Integer.hpp>
#include <TDF_Attribute.hpp>
#include <BinMDataStd.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BinMDataStd_IntegerDriver, BinMDF_ADriver)

BinMDataStd_IntegerDriver::BinMDataStd_IntegerDriver(
  const occ::handle<Message_Messenger>& theMsgDriver)
    : BinMDF_ADriver(theMsgDriver, STANDARD_TYPE(TDataStd_Integer)->Name())
{
}

occ::handle<TDF_Attribute> BinMDataStd_IntegerDriver::NewEmpty() const
{
  return new TDataStd_Integer();
}

bool BinMDataStd_IntegerDriver::Paste(const BinObjMgt_Persistent&       theSource,
                                      const occ::handle<TDF_Attribute>& theTarget,
                                      BinObjMgt_RRelocationTable&       theRT) const
{
  occ::handle<TDataStd_Integer> anAtt = occ::down_cast<TDataStd_Integer>(theTarget);
  int                           aValue;
  bool                          ok = theSource >> aValue;
  if (ok)
    anAtt->Set(aValue);
  if (theRT.GetHeaderData()->StorageVersion().IntegerValue() >= TDocStd_FormatVersion_VERSION_9)
  {
    const int&    aPos = theSource.Position();
    Standard_GUID aGuid;
    ok = theSource >> aGuid;
    if (!ok)
    {
      theSource.SetPosition(aPos);
      ok = true;
    }
    else
    {
      anAtt->SetID(aGuid);
    }
  }
  else
    anAtt->SetID(TDataStd_Integer::GetID());
  return ok;
}

void BinMDataStd_IntegerDriver::Paste(
  const occ::handle<TDF_Attribute>& theSource,
  BinObjMgt_Persistent&             theTarget,
  NCollection_IndexedMap<occ::handle<Standard_Transient>>&) const
{
  occ::handle<TDataStd_Integer> anAtt = occ::down_cast<TDataStd_Integer>(theSource);
  theTarget << anAtt->Get();

  if (anAtt->ID() != TDataStd_Integer::GetID())
    theTarget << anAtt->ID();
}
