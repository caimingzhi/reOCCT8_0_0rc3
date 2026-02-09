#include <BinTObjDrivers_XYZDriver.hpp>
#include <Message_Messenger.hpp>
#include <TDF_Attribute.hpp>
#include <BinObjMgt_Persistent.hpp>
#include <TObj_TXYZ.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BinTObjDrivers_XYZDriver, BinMDF_ADriver)

BinTObjDrivers_XYZDriver::BinTObjDrivers_XYZDriver(
  const occ::handle<Message_Messenger>& theMessageDriver)
    : BinMDF_ADriver(theMessageDriver, nullptr)
{
}

occ::handle<TDF_Attribute> BinTObjDrivers_XYZDriver::NewEmpty() const
{
  return new TObj_TXYZ;
}

bool BinTObjDrivers_XYZDriver::Paste(const BinObjMgt_Persistent&       theSource,
                                     const occ::handle<TDF_Attribute>& theTarget,
                                     BinObjMgt_RRelocationTable&) const
{
  occ::handle<TObj_TXYZ> aTarget = occ::down_cast<TObj_TXYZ>(theTarget);
  double                 aX, aY, aZ;
  if (!(theSource >> aX >> aY >> aZ))
    return false;
  aTarget->Set(gp_XYZ(aX, aY, aZ));
  return true;
}

void BinTObjDrivers_XYZDriver::Paste(const occ::handle<TDF_Attribute>& theSource,
                                     BinObjMgt_Persistent&             theTarget,
                                     NCollection_IndexedMap<occ::handle<Standard_Transient>>&) const
{
  occ::handle<TObj_TXYZ> aSource = occ::down_cast<TObj_TXYZ>(theSource);
  gp_XYZ                 aXYZ    = aSource->Get();
  theTarget << aXYZ.X() << aXYZ.Y() << aXYZ.Z();
}
