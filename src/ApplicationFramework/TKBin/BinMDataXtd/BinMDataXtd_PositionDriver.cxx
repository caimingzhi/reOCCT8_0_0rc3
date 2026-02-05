#include <BinMDataXtd_PositionDriver.hpp>

#include <Standard_Type.hpp>
#include <TDataXtd_Position.hpp>
#include <TDF_Attribute.hpp>
#include <BinObjMgt_Persistent.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BinMDataXtd_PositionDriver, BinMDF_ADriver)

//=================================================================================================

BinMDataXtd_PositionDriver::BinMDataXtd_PositionDriver(
  const occ::handle<Message_Messenger>& theMsgDriver)
    : BinMDF_ADriver(theMsgDriver, STANDARD_TYPE(TDataXtd_Position)->Name())
{
}

//=================================================================================================

occ::handle<TDF_Attribute> BinMDataXtd_PositionDriver::NewEmpty() const
{
  return new TDataXtd_Position();
}

//=======================================================================
// function : Paste
// purpose  : persistent -> transient (retrieve)
//=======================================================================

bool BinMDataXtd_PositionDriver::Paste(const BinObjMgt_Persistent&       theSource,
                                       const occ::handle<TDF_Attribute>& theTarget,
                                       BinObjMgt_RRelocationTable&) const
{
  occ::handle<TDataXtd_Position> anAtt = occ::down_cast<TDataXtd_Position>(theTarget);
  double                         aValue;
  bool                           ok = theSource >> aValue;
  if (!ok)
    return ok;
  gp_Pnt aPosition(0., 0., 0.);
  aPosition.SetX(aValue);

  ok = theSource >> aValue;
  if (!ok)
    return ok;
  aPosition.SetY(aValue);

  ok = theSource >> aValue;
  if (!ok)
    return ok;
  aPosition.SetZ(aValue);

  anAtt->SetPosition(aPosition);

  return ok;
}

//=======================================================================
// function : Paste
// purpose  : transient -> persistent (store)
//=======================================================================

void BinMDataXtd_PositionDriver::Paste(
  const occ::handle<TDF_Attribute>& theSource,
  BinObjMgt_Persistent&             theTarget,
  NCollection_IndexedMap<occ::handle<Standard_Transient>>&) const
{
  occ::handle<TDataXtd_Position> anAtt = occ::down_cast<TDataXtd_Position>(theSource);

  theTarget << anAtt->GetPosition().X();
  theTarget << anAtt->GetPosition().Y();
  theTarget << anAtt->GetPosition().Z();
}
