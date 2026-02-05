#include <BinMDF_TagSourceDriver.hpp>
#include <BinObjMgt_Persistent.hpp>
#include <Message_Messenger.hpp>
#include <Standard_Type.hpp>
#include <TDF_Attribute.hpp>
#include <TDF_TagSource.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BinMDF_TagSourceDriver, BinMDF_ADriver)

//=================================================================================================

BinMDF_TagSourceDriver::BinMDF_TagSourceDriver(const occ::handle<Message_Messenger>& theMsgDriver)
    : BinMDF_ADriver(theMsgDriver, nullptr)
{
}

//=================================================================================================

occ::handle<TDF_Attribute> BinMDF_TagSourceDriver::NewEmpty() const
{
  return (new TDF_TagSource());
}

//=======================================================================
// function : Paste
// purpose  : persistent -> transient (retrieve)
//=======================================================================
bool BinMDF_TagSourceDriver::Paste(const BinObjMgt_Persistent&       theSource,
                                   const occ::handle<TDF_Attribute>& theTarget,
                                   BinObjMgt_RRelocationTable&) const
{
  occ::handle<TDF_TagSource> aTag = occ::down_cast<TDF_TagSource>(theTarget);
  int                        aValue;
  bool                       ok = theSource >> aValue;
  if (ok)
    aTag->Set(aValue);
  return ok;
}

//=======================================================================
// function : Paste
// purpose  : transient -> persistent (store)
//=======================================================================
void BinMDF_TagSourceDriver::Paste(const occ::handle<TDF_Attribute>& theSource,
                                   BinObjMgt_Persistent&             theTarget,
                                   NCollection_IndexedMap<occ::handle<Standard_Transient>>&) const
{
  occ::handle<TDF_TagSource> aTag = occ::down_cast<TDF_TagSource>(theSource);
  theTarget << aTag->Get();
}
