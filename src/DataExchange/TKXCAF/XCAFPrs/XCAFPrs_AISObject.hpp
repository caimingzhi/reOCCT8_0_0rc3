#pragma once

#include <AIS_ColoredShape.hpp>

#include <TDF_Label.hpp>

class XCAFPrs_Style;

class XCAFPrs_AISObject : public AIS_ColoredShape
{
public:
  Standard_EXPORT XCAFPrs_AISObject(const TDF_Label& theLabel);

  const TDF_Label& GetLabel() const { return myLabel; }

  void SetLabel(const TDF_Label& theLabel) { myLabel = theLabel; }

  Standard_EXPORT virtual void DispatchStyles(const bool theToSyncStyles = false);

  Standard_EXPORT void SetMaterial(const Graphic3d_MaterialAspect& theMaterial) override;

protected:
  Standard_EXPORT void Compute(const occ::handle<PrsMgr_PresentationManager>& thePrsMgr,
                               const occ::handle<Prs3d_Presentation>&         thePrs,
                               const int                                      theMode) override;

  Standard_EXPORT virtual void DefaultStyle(XCAFPrs_Style& theStyle) const;

protected:
  static void setStyleToDrawer(const occ::handle<Prs3d_Drawer>& theDrawer,
                               const XCAFPrs_Style&             theStyle,
                               const XCAFPrs_Style&             theDefStyle,
                               const Graphic3d_MaterialAspect&  theDefMaterial);

protected:
  TDF_Label myLabel;

  bool myToSyncStyles;

public:
  DEFINE_STANDARD_RTTIEXT(XCAFPrs_AISObject, AIS_ColoredShape)
};
