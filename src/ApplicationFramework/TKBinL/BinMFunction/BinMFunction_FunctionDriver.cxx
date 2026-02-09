#include <BinMDF_ADriver.hpp>
#include <BinMFunction_FunctionDriver.hpp>
#include <BinObjMgt_Persistent.hpp>
#include <BinObjMgt_RRelocationTable.hpp>
#include <Standard_Transient.hpp>
#include <NCollection_IndexedMap.hpp>
#include <Message_Messenger.hpp>
#include <Standard_Type.hpp>
#include <TDF_Attribute.hpp>
#include <TFunction_Function.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BinMFunction_FunctionDriver, BinMDF_ADriver)

BinMFunction_FunctionDriver::BinMFunction_FunctionDriver(
  const occ::handle<Message_Messenger>& theMsgDriver)
    : BinMDF_ADriver(theMsgDriver, STANDARD_TYPE(TFunction_Function)->Name())
{
}

occ::handle<TDF_Attribute> BinMFunction_FunctionDriver::NewEmpty() const
{
  return new TFunction_Function();
}

bool BinMFunction_FunctionDriver::Paste(const BinObjMgt_Persistent&       theSource,
                                        const occ::handle<TDF_Attribute>& theTarget,
                                        BinObjMgt_RRelocationTable&) const
{

  occ::handle<TFunction_Function> anAtt = occ::down_cast<TFunction_Function>(theTarget);
  Standard_GUID                   aGUID("00000000-0000-0000-0000-000000000000");
  bool                            ok = theSource >> aGUID;
  if (ok)
  {
    anAtt->SetDriverGUID(aGUID);
    int aValue;
    ok = theSource >> aValue;
    if (ok)
      anAtt->SetFailure(aValue);
  }
  return ok;
}

void BinMFunction_FunctionDriver::Paste(
  const occ::handle<TDF_Attribute>& theSource,
  BinObjMgt_Persistent&             theTarget,
  NCollection_IndexedMap<occ::handle<Standard_Transient>>&) const
{
  occ::handle<TFunction_Function> aS = occ::down_cast<TFunction_Function>(theSource);
  theTarget << aS->GetDriverGUID();
  theTarget << aS->GetFailure();
}
