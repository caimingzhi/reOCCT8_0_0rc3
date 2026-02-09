

#include <StdPersistent_PPrsStd.hpp>

void StdPersistent_PPrsStd::AISPresentation::Import(
  const occ::handle<TDataXtd_Presentation>& theAttribute) const
{
  theAttribute->SetDisplayed(myIsDisplayed);

  occ::handle<TCollection_HExtendedString> aDriverGUID = myDriverGUID->ExtString();
  if (aDriverGUID)
    theAttribute->SetDriverGUID(Standard_GUID(aDriverGUID->String().ToExtString()));

  if (myColor != -1)
    theAttribute->SetColor(static_cast<Quantity_NameOfColor>((int)myColor));
  else
    theAttribute->UnsetColor();

  if (myMaterial != -1)
    theAttribute->SetMaterialIndex(myMaterial);
  else
    theAttribute->UnsetMaterial();

  if (myTransparency != -1.)
    theAttribute->SetTransparency(myTransparency);
  else
    theAttribute->UnsetTransparency();

  if (myWidth != -1.)
    theAttribute->SetWidth(myWidth);
  else
    theAttribute->UnsetWidth();
}

void StdPersistent_PPrsStd::AISPresentation_1::Import(
  const occ::handle<TDataXtd_Presentation>& theAttribute) const
{
  AISPresentation::Import(theAttribute);
  theAttribute->SetMode(myMode);
}
