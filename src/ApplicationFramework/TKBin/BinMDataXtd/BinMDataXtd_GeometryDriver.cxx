#include <BinMDataXtd_GeometryDriver.hpp>
#include <BinObjMgt_Persistent.hpp>
#include <Message_Messenger.hpp>
#include <Standard_Type.hpp>
#include <TDataXtd_Geometry.hpp>
#include <TDF_Attribute.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BinMDataXtd_GeometryDriver, BinMDF_ADriver)

BinMDataXtd_GeometryDriver::BinMDataXtd_GeometryDriver(
  const occ::handle<Message_Messenger>& theMsgDriver)
    : BinMDF_ADriver(theMsgDriver, nullptr)
{
}

occ::handle<TDF_Attribute> BinMDataXtd_GeometryDriver::NewEmpty() const
{
  return (new TDataXtd_Geometry());
}

bool BinMDataXtd_GeometryDriver::Paste(const BinObjMgt_Persistent&       theSource,
                                       const occ::handle<TDF_Attribute>& theTarget,
                                       BinObjMgt_RRelocationTable&) const
{
  occ::handle<TDataXtd_Geometry> aT = occ::down_cast<TDataXtd_Geometry>(theTarget);

  int  aType;
  bool ok = theSource >> aType;
  if (ok)
    aT->SetType((TDataXtd_GeometryEnum)aType);

  return ok;
}

void BinMDataXtd_GeometryDriver::Paste(
  const occ::handle<TDF_Attribute>& theSource,
  BinObjMgt_Persistent&             theTarget,
  NCollection_IndexedMap<occ::handle<Standard_Transient>>&) const
{
  occ::handle<TDataXtd_Geometry> aG = occ::down_cast<TDataXtd_Geometry>(theSource);
  theTarget << (int)aG->GetType();
}
