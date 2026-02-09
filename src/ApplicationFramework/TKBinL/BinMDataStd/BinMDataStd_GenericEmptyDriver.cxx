

#include <BinMDataStd_GenericEmptyDriver.hpp>
#include <BinMDF_ADriver.hpp>
#include <BinObjMgt_Persistent.hpp>
#include <BinObjMgt_RRelocationTable.hpp>
#include <Standard_Transient.hpp>
#include <NCollection_IndexedMap.hpp>
#include <Message_Messenger.hpp>
#include <Standard_Type.hpp>
#include <TDataStd_GenericEmpty.hpp>
#include <TDF_Attribute.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BinMDataStd_GenericEmptyDriver, BinMDF_ADriver)

BinMDataStd_GenericEmptyDriver::BinMDataStd_GenericEmptyDriver(
  const occ::handle<Message_Messenger>& theMsgDriver)
    : BinMDF_ADriver(theMsgDriver, STANDARD_TYPE(TDataStd_GenericEmpty)->Name())
{
}

occ::handle<TDF_Attribute> BinMDataStd_GenericEmptyDriver::NewEmpty() const
{
  return occ::handle<TDF_Attribute>();
}

const occ::handle<Standard_Type>& BinMDataStd_GenericEmptyDriver::SourceType() const
{
  return Standard_Type::Instance<TDataStd_GenericEmpty>();
}

bool BinMDataStd_GenericEmptyDriver::Paste(const BinObjMgt_Persistent&,
                                           const occ::handle<TDF_Attribute>&,
                                           BinObjMgt_RRelocationTable&) const
{
  return true;
}

void BinMDataStd_GenericEmptyDriver::Paste(
  const occ::handle<TDF_Attribute>&,
  BinObjMgt_Persistent&,
  NCollection_IndexedMap<occ::handle<Standard_Transient>>&) const
{
}
