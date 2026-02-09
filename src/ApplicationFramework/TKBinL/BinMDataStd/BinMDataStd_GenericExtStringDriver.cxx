

#include <BinMDataStd_GenericExtStringDriver.hpp>
#include <Message_Messenger.hpp>
#include <Standard_Type.hpp>
#include <TDataStd_Name.hpp>
#include <TDF_Attribute.hpp>
#include <BinMDataStd.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BinMDataStd_GenericExtStringDriver, BinMDF_ADriver)

BinMDataStd_GenericExtStringDriver::BinMDataStd_GenericExtStringDriver(
  const occ::handle<Message_Messenger>& theMessageDriver)
    : BinMDF_ADriver(theMessageDriver, STANDARD_TYPE(TDataStd_GenericExtString)->Name())
{
}

occ::handle<TDF_Attribute> BinMDataStd_GenericExtStringDriver::NewEmpty() const
{
  return new TDataStd_Name;
}

const occ::handle<Standard_Type>& BinMDataStd_GenericExtStringDriver::SourceType() const
{
  return Standard_Type::Instance<TDataStd_GenericExtString>();
}

bool BinMDataStd_GenericExtStringDriver::Paste(const BinObjMgt_Persistent&       Source,
                                               const occ::handle<TDF_Attribute>& Target,
                                               BinObjMgt_RRelocationTable&       RelocTable) const
{
  occ::handle<TDataStd_GenericExtString> aStrAttr =
    occ::down_cast<TDataStd_GenericExtString>(Target);
  TCollection_ExtendedString aStr;
  bool                       ok = Source >> aStr;
  if (ok)
    aStrAttr->Set(aStr);
  if (RelocTable.GetHeaderData()->StorageVersion().IntegerValue()
      >= TDocStd_FormatVersion_VERSION_9)
  {
    const int&    aPos = Source.Position();
    Standard_GUID aGuid;
    ok = Source >> aGuid;
    if (!ok)
    {
      Source.SetPosition(aPos);
      ok = true;
    }
    else
    {
      aStrAttr->SetID(aGuid);
    }
  }
  return ok;
}

void BinMDataStd_GenericExtStringDriver::Paste(
  const occ::handle<TDF_Attribute>& Source,
  BinObjMgt_Persistent&             Target,
  NCollection_IndexedMap<occ::handle<Standard_Transient>>&) const
{
  occ::handle<TDataStd_GenericExtString> aStrAttr =
    occ::down_cast<TDataStd_GenericExtString>(Source);
  Target << aStrAttr->Get();

  Target << aStrAttr->ID();
}
