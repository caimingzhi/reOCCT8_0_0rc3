#include <BinMDataXtd_PresentationDriver.hpp>

#include <TDataXtd_Presentation.hpp>
#include <BinObjMgt_Persistent.hpp>
#include <Message_Messenger.hpp>
#include <Quantity_Color.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BinMDataXtd_PresentationDriver, BinMDF_ADriver)

BinMDataXtd_PresentationDriver::BinMDataXtd_PresentationDriver(
  const occ::handle<Message_Messenger>& theMsgDriver)
    : BinMDF_ADriver(theMsgDriver, STANDARD_TYPE(TDataXtd_Presentation)->Name())
{
}

occ::handle<TDF_Attribute> BinMDataXtd_PresentationDriver::NewEmpty() const
{
  return new TDataXtd_Presentation();
}

bool BinMDataXtd_PresentationDriver::Paste(const BinObjMgt_Persistent&       theSource,
                                           const occ::handle<TDF_Attribute>& theTarget,
                                           BinObjMgt_RRelocationTable&) const
{
  bool                               ok          = false;
  occ::handle<TDataXtd_Presentation> anAttribute = occ::down_cast<TDataXtd_Presentation>(theTarget);

  int aValue;
  ok = theSource >> aValue;
  if (!ok)
    return ok;
  anAttribute->SetDisplayed(aValue != 0);

  Standard_GUID aGUID;
  ok = theSource >> aGUID;
  if (!ok)
    return ok;
  anAttribute->SetDriverGUID(aGUID);

  ok = theSource >> aValue;
  if (!ok)
    return ok;
  if (aValue != -1)
  {
    Quantity_NameOfColor aNameOfColor = TDataXtd_Presentation::getColorNameFromOldEnum(aValue);
    if (aNameOfColor <= Quantity_NOC_WHITE)
    {
      anAttribute->SetColor(aNameOfColor);
    }
  }
  else
  {
    anAttribute->UnsetColor();
  }

  ok = theSource >> aValue;
  if (!ok)
    return ok;
  if (aValue != -1)
    anAttribute->SetMaterialIndex(aValue);
  else
    anAttribute->UnsetMaterial();

  double aRValue;
  ok = theSource >> aRValue;
  if (!ok)
    return ok;
  if (aRValue != -1.)
    anAttribute->SetTransparency(aRValue);
  else
    anAttribute->UnsetTransparency();

  ok = theSource >> aRValue;
  if (!ok)
    return ok;
  if (aRValue != -1.)
    anAttribute->SetWidth(aRValue);
  else
    anAttribute->UnsetWidth();

  ok = theSource >> aValue;
  if (!ok)
    return ok;
  if (aValue != -1)
    anAttribute->SetMode(aValue);
  else
    anAttribute->UnsetMode();

  return true;
}

void BinMDataXtd_PresentationDriver::Paste(
  const occ::handle<TDF_Attribute>& theSource,
  BinObjMgt_Persistent&             theTarget,
  NCollection_IndexedMap<occ::handle<Standard_Transient>>&) const
{
  occ::handle<TDataXtd_Presentation> anAttribute = occ::down_cast<TDataXtd_Presentation>(theSource);

  theTarget.PutBoolean(anAttribute->IsDisplayed());

  theTarget.PutGUID(anAttribute->GetDriverGUID());

  if (anAttribute->HasOwnColor())
  {
    const int anOldEnum = TDataXtd_Presentation::getOldColorNameFromNewEnum(anAttribute->Color());
    theTarget.PutInteger(anOldEnum);
  }
  else
  {
    theTarget.PutInteger(-1);
  }

  if (anAttribute->HasOwnMaterial())
    theTarget.PutInteger(anAttribute->MaterialIndex());
  else
    theTarget.PutInteger(-1);

  if (anAttribute->HasOwnTransparency())
    theTarget.PutReal(anAttribute->Transparency());
  else
    theTarget.PutReal(-1.);

  if (anAttribute->HasOwnWidth())
    theTarget.PutReal(anAttribute->Width());
  else
    theTarget.PutReal(-1.);

  if (anAttribute->HasOwnMode())
    theTarget.PutInteger(anAttribute->Mode());
  else
    theTarget.PutInteger(-1);
}
