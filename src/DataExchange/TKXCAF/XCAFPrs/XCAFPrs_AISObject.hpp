#pragma once

#include <AIS_ColoredShape.hpp>

#include <TDF_Label.hpp>

class XCAFPrs_Style;

//! Implements AIS_InteractiveObject functionality for shape in DECAF document.
class XCAFPrs_AISObject : public AIS_ColoredShape
{
public:
  //! Creates an object to visualise the shape label.
  Standard_EXPORT XCAFPrs_AISObject(const TDF_Label& theLabel);

  //! Returns the label which was visualised by this presentation
  const TDF_Label& GetLabel() const { return myLabel; }

  //! Assign the label to this presentation
  //! (but does not mark it outdated with SetToUpdate()).
  void SetLabel(const TDF_Label& theLabel) { myLabel = theLabel; }

  //! Fetch the Shape from associated Label and fill the map of sub-shapes styles.
  //! By default, this method is called implicitly within first ::Compute().
  //! Application might call this method explicitly to manipulate styles afterwards.
  //! @param theToSyncStyles flag indicating if method ::Compute() should call this method again
  //!                        on first compute or re-compute
  Standard_EXPORT virtual void DispatchStyles(const bool theToSyncStyles = false);

  //! Sets the material aspect.
  //! This method assigns the new default material without overriding XDE styles.
  //! Re-computation of existing presentation is not required after calling this method.
  Standard_EXPORT void SetMaterial(const Graphic3d_MaterialAspect& theMaterial) override;

protected:
  //! Redefined method to compute presentation.
  Standard_EXPORT void Compute(const occ::handle<PrsMgr_PresentationManager>& thePrsMgr,
                               const occ::handle<Prs3d_Presentation>&         thePrs,
                               const int                                      theMode) override;

  //! Fills out a default style object which is used when styles are
  //! not explicitly defined in the document.
  //! By default, the style uses white color for curves and surfaces.
  Standard_EXPORT virtual void DefaultStyle(XCAFPrs_Style& theStyle) const;

protected:
  //! Assign style to drawer.
  static void setStyleToDrawer(const occ::handle<Prs3d_Drawer>& theDrawer,
                               const XCAFPrs_Style&             theStyle,
                               const XCAFPrs_Style&             theDefStyle,
                               const Graphic3d_MaterialAspect&  theDefMaterial);

protected:
  TDF_Label myLabel; //!< label pointing onto the shape
  // clang-format off
  bool myToSyncStyles; //!< flag indicating that shape and sub-shapes should be updates within Compute()
  // clang-format on

public:
  DEFINE_STANDARD_RTTIEXT(XCAFPrs_AISObject, AIS_ColoredShape)
};
