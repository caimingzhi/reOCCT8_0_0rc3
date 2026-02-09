#pragma once

#include <Graphic3d_StructureManager.hpp>
#include <Graphic3d_ZLayerId.hpp>
#include <NCollection_List.hpp>
#include <Prs3d_Presentation.hpp>

class Graphic3d_Structure;
typedef Graphic3d_Structure Prs3d_Presentation;

class TopLoc_Datum3D;
class Prs3d_Drawer;
class PrsMgr_Presentation;
class PrsMgr_PresentableObject;
class V3d_Viewer;

class PrsMgr_PresentationManager : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(PrsMgr_PresentationManager, Standard_Transient)
public:
  Standard_EXPORT PrsMgr_PresentationManager(
    const occ::handle<Graphic3d_StructureManager>& theStructureManager);

  Standard_EXPORT void Display(const occ::handle<PrsMgr_PresentableObject>& thePrsObject,
                               const int                                    theMode = 0);

  Standard_EXPORT void Erase(const occ::handle<PrsMgr_PresentableObject>& thePrsObject,
                             const int                                    theMode = 0);

  Standard_EXPORT virtual void Clear(const occ::handle<PrsMgr_PresentableObject>& thePrsObject,
                                     const int                                    theMode = 0);

  Standard_EXPORT void SetVisibility(const occ::handle<PrsMgr_PresentableObject>& thePrsObject,
                                     const int                                    theMode,
                                     const bool                                   theValue);

  Standard_EXPORT void Unhighlight(const occ::handle<PrsMgr_PresentableObject>& thePrsObject);

  Standard_EXPORT void SetDisplayPriority(const occ::handle<PrsMgr_PresentableObject>& thePrsObject,
                                          const int                                    theMode,
                                          const Graphic3d_DisplayPriority theNewPrior) const;

  Standard_EXPORT Graphic3d_DisplayPriority
    DisplayPriority(const occ::handle<PrsMgr_PresentableObject>& thePrsObject,
                    const int                                    theMode) const;

  Standard_EXPORT void SetZLayer(const occ::handle<PrsMgr_PresentableObject>& thePrsObject,
                                 const Graphic3d_ZLayerId                     theLayerId);

  Standard_EXPORT Graphic3d_ZLayerId
    GetZLayer(const occ::handle<PrsMgr_PresentableObject>& thePrsObject) const;

  Standard_EXPORT bool IsDisplayed(const occ::handle<PrsMgr_PresentableObject>& thePrsObject,
                                   const int                                    theMode = 0) const;

  Standard_EXPORT bool IsHighlighted(const occ::handle<PrsMgr_PresentableObject>& thePrsObject,
                                     const int theMode = 0) const;

  Standard_EXPORT void Update(const occ::handle<PrsMgr_PresentableObject>& thePrsObject,
                              const int                                    theMode = 0) const;

  Standard_EXPORT void BeginImmediateDraw();

  Standard_EXPORT void ClearImmediateDraw();

  Standard_EXPORT void AddToImmediateList(const occ::handle<Prs3d_Presentation>& thePrs);

  Standard_EXPORT void EndImmediateDraw(const occ::handle<V3d_Viewer>& theViewer);

  Standard_EXPORT void RedrawImmediate(const occ::handle<V3d_Viewer>& theViewer);

  bool IsImmediateModeOn() const { return myImmediateModeOn > 0; }

  Standard_EXPORT void Color(
    const occ::handle<PrsMgr_PresentableObject>& thePrsObject,
    const occ::handle<Prs3d_Drawer>&             theStyle,
    const int                                    theMode   = 0,
    const occ::handle<PrsMgr_PresentableObject>& theSelObj = nullptr,
    const Graphic3d_ZLayerId theImmediateStructLayerId     = Graphic3d_ZLayerId_Topmost);

  Standard_EXPORT void Connect(const occ::handle<PrsMgr_PresentableObject>& thePrsObject,
                               const occ::handle<PrsMgr_PresentableObject>& theOtherObject,
                               const int                                    theMode      = 0,
                               const int                                    theOtherMode = 0);

  Standard_EXPORT void Transform(const occ::handle<PrsMgr_PresentableObject>& thePrsObject,
                                 const occ::handle<TopLoc_Datum3D>&           theTransformation,
                                 const int                                    theMode = 0);

  const occ::handle<Graphic3d_StructureManager>& StructureManager() const
  {
    return myStructureManager;
  }

  Standard_EXPORT bool HasPresentation(const occ::handle<PrsMgr_PresentableObject>& thePrsObject,
                                       const int theMode = 0) const;

  Standard_EXPORT occ::handle<PrsMgr_Presentation> Presentation(
    const occ::handle<PrsMgr_PresentableObject>& thePrsObject,
    const int                                    theMode     = 0,
    const bool                                   theToCreate = false,
    const occ::handle<PrsMgr_PresentableObject>& theSelObj   = nullptr) const;

  Standard_EXPORT void UpdateHighlightTrsf(
    const occ::handle<V3d_Viewer>&               theViewer,
    const occ::handle<PrsMgr_PresentableObject>& theObj,
    const int                                    theMode   = 0,
    const occ::handle<PrsMgr_PresentableObject>& theSelObj = nullptr);

protected:
  Standard_EXPORT bool RemovePresentation(const occ::handle<PrsMgr_PresentableObject>& thePrsObject,
                                          const int                                    theMode = 0);

private:
  void displayImmediate(const occ::handle<V3d_Viewer>& theViewer);

protected:
  occ::handle<Graphic3d_StructureManager>           myStructureManager;
  int                                               myImmediateModeOn;
  NCollection_List<occ::handle<Prs3d_Presentation>> myImmediateList;
  NCollection_List<occ::handle<Prs3d_Presentation>> myViewDependentImmediateList;
};
