

#include <BinMXCAFDoc_VisMaterialToolDriver.hpp>

#include <XCAFDoc_VisMaterialTool.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BinMXCAFDoc_VisMaterialToolDriver, BinMDF_ADriver)

BinMXCAFDoc_VisMaterialToolDriver::BinMXCAFDoc_VisMaterialToolDriver(
  const occ::handle<Message_Messenger>& theMsgDriver)
    : BinMDF_ADriver(theMsgDriver, STANDARD_TYPE(XCAFDoc_VisMaterialTool)->Name())
{
}

occ::handle<TDF_Attribute> BinMXCAFDoc_VisMaterialToolDriver::NewEmpty() const
{
  return new XCAFDoc_VisMaterialTool();
}

bool BinMXCAFDoc_VisMaterialToolDriver::Paste(const BinObjMgt_Persistent&,
                                              const occ::handle<TDF_Attribute>&,
                                              BinObjMgt_RRelocationTable&) const
{
  return true;
}

void BinMXCAFDoc_VisMaterialToolDriver::Paste(
  const occ::handle<TDF_Attribute>&,
  BinObjMgt_Persistent&,
  NCollection_IndexedMap<occ::handle<Standard_Transient>>&) const
{
}
