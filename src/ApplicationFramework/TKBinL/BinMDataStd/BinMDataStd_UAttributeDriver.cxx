#include <BinMDataStd_UAttributeDriver.hpp>
#include <BinObjMgt_Persistent.hpp>
#include <Message_Messenger.hpp>
#include <Standard_Type.hpp>
#include <TDataStd_UAttribute.hpp>
#include <TDF_Attribute.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BinMDataStd_UAttributeDriver, BinMDF_ADriver)

//=================================================================================================

BinMDataStd_UAttributeDriver::BinMDataStd_UAttributeDriver(
  const occ::handle<Message_Messenger>& theMsgDriver)
    : BinMDF_ADriver(theMsgDriver, nullptr)
{
}

//=================================================================================================

occ::handle<TDF_Attribute> BinMDataStd_UAttributeDriver::NewEmpty() const
{
  return (new TDataStd_UAttribute());
}

//=================================================================================================

bool BinMDataStd_UAttributeDriver::Paste(const BinObjMgt_Persistent&       theSource,
                                         const occ::handle<TDF_Attribute>& theTarget,
                                         BinObjMgt_RRelocationTable&) const
{
  occ::handle<TDataStd_UAttribute> anUAttr = occ::down_cast<TDataStd_UAttribute>(theTarget);
  Standard_GUID                    aGUID;
  bool                             ok = theSource >> aGUID;
  if (ok)
    anUAttr->SetID(aGUID);
  return ok;
}

//=================================================================================================

void BinMDataStd_UAttributeDriver::Paste(
  const occ::handle<TDF_Attribute>& theSource,
  BinObjMgt_Persistent&             theTarget,
  NCollection_IndexedMap<occ::handle<Standard_Transient>>&) const
{
  occ::handle<TDataStd_UAttribute> anUAttr = occ::down_cast<TDataStd_UAttribute>(theSource);
  theTarget << anUAttr->ID();
}
