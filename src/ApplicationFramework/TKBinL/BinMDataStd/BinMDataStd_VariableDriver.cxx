#include <BinMDataStd_VariableDriver.hpp>
#include <BinObjMgt_Persistent.hpp>
#include <Message_Messenger.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>
#include <TDataStd_Variable.hpp>
#include <TDF_Attribute.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BinMDataStd_VariableDriver, BinMDF_ADriver)

//=================================================================================================

BinMDataStd_VariableDriver::BinMDataStd_VariableDriver(
  const occ::handle<Message_Messenger>& theMsgDriver)
    : BinMDF_ADriver(theMsgDriver, nullptr)
{
}

//=================================================================================================

occ::handle<TDF_Attribute> BinMDataStd_VariableDriver::NewEmpty() const
{
  return (new TDataStd_Variable());
}

//=================================================================================================

bool BinMDataStd_VariableDriver::Paste(const BinObjMgt_Persistent&       theSource,
                                       const occ::handle<TDF_Attribute>& theTarget,
                                       BinObjMgt_RRelocationTable&) const
{
  occ::handle<TDataStd_Variable> aV = occ::down_cast<TDataStd_Variable>(theTarget);

  bool isConstant;
  if (!(theSource >> isConstant))
    return false;
  aV->Constant(isConstant);

  TCollection_AsciiString anStr;
  if (!(theSource >> anStr))
    return false;
  aV->Unit(anStr);

  return true;
}

//=================================================================================================

void BinMDataStd_VariableDriver::Paste(
  const occ::handle<TDF_Attribute>& theSource,
  BinObjMgt_Persistent&             theTarget,
  NCollection_IndexedMap<occ::handle<Standard_Transient>>&) const
{
  occ::handle<TDataStd_Variable> aV = occ::down_cast<TDataStd_Variable>(theSource);
  theTarget << aV->IsConstant() << aV->Unit();
}
