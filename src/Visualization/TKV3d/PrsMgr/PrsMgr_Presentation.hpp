#pragma once

#include <Prs3d_Presentation.hpp>

class PrsMgr_PresentationManager;
class PrsMgr_PresentableObject;
class Graphic3d_Camera;
class Prs3d_Drawer;

class PrsMgr_Presentation : public Graphic3d_Structure
{
  DEFINE_STANDARD_RTTIEXT(PrsMgr_Presentation, Graphic3d_Structure)
  friend class PrsMgr_PresentationManager;
  friend class PrsMgr_PresentableObject;

public:
  Standard_EXPORT ~PrsMgr_Presentation() override;

  Standard_DEPRECATED("Dummy to simplify porting - returns self")

  Prs3d_Presentation* Presentation() { return this; }

  const occ::handle<PrsMgr_PresentationManager>& PresentationManager() const
  {
    return myPresentationManager;
  }

  void SetUpdateStatus(const bool theUpdateStatus) { myMustBeUpdated = theUpdateStatus; }

  bool MustBeUpdated() const { return myMustBeUpdated; }

  int Mode() const { return myMode; }

  Standard_EXPORT void Display() override;

  Standard_EXPORT void Erase() override;

  Standard_EXPORT void Highlight(const occ::handle<Prs3d_Drawer>& theStyle);

  Standard_EXPORT void Unhighlight();

  bool IsDisplayed() const override { return base_type::IsDisplayed() && base_type::IsVisible(); }

  Standard_EXPORT void Clear(const bool theWithDestruction = true) override;

  Standard_EXPORT void Compute() override;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

protected:
  Standard_EXPORT PrsMgr_Presentation(
    const occ::handle<PrsMgr_PresentationManager>& thePresentationManager,
    const occ::handle<PrsMgr_PresentableObject>&   thePresentableObject,
    const int                                      theMode);

  Standard_EXPORT void display(const bool theIsHighlight);

  Standard_EXPORT void computeHLR(const occ::handle<Graphic3d_Camera>& theProjector,
                                  occ::handle<Graphic3d_Structure>&    theGivenStruct) override;

  Standard_EXPORT void RecomputeTransformation(
    const occ::handle<Graphic3d_Camera>& theProjector) override;

protected:
  occ::handle<PrsMgr_PresentationManager> myPresentationManager;
  PrsMgr_PresentableObject*               myPresentableObject;
  int                                     myBeforeHighlightState;
  int                                     myMode;
  bool                                    myMustBeUpdated;
};
