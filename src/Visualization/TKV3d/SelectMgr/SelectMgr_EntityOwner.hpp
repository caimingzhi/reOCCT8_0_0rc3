#pragma once

#include <AIS_SelectionScheme.hpp>
#include <Aspect_VKey.hpp>
#include <PrsMgr_PresentationManager.hpp>
#include <SelectMgr_SelectableObject.hpp>
#include <TopLoc_Location.hpp>

class V3d_Viewer;

class SelectMgr_EntityOwner : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(SelectMgr_EntityOwner, Standard_Transient)
public:
  Standard_EXPORT SelectMgr_EntityOwner(const int aPriority = 0);

  Standard_EXPORT SelectMgr_EntityOwner(const occ::handle<SelectMgr_SelectableObject>& aSO,
                                        const int aPriority = 0);

  Standard_EXPORT SelectMgr_EntityOwner(const occ::handle<SelectMgr_EntityOwner>& theOwner,
                                        const int                                 aPriority = 0);

  int Priority() const { return mypriority; }

  void SetPriority(int thePriority) { mypriority = thePriority; }

  bool HasSelectable() const { return mySelectable != nullptr; }

  virtual occ::handle<SelectMgr_SelectableObject> Selectable() const { return mySelectable; }

  virtual void SetSelectable(const occ::handle<SelectMgr_SelectableObject>& theSelObj)
  {
    mySelectable = theSelObj.get();
  }

  virtual bool HandleMouseClick(const NCollection_Vec2<int>& thePoint,
                                Aspect_VKeyMouse             theButton,
                                Aspect_VKeyFlags             theModifiers,
                                bool                         theIsDoubleClick)
  {
    (void)thePoint;
    (void)theButton;
    (void)theModifiers;
    (void)theIsDoubleClick;
    return false;
  }

  virtual bool IsHilighted(const occ::handle<PrsMgr_PresentationManager>& thePrsMgr,
                           const int                                      theMode = 0) const
  {
    return mySelectable != nullptr && thePrsMgr->IsHighlighted(mySelectable, theMode);
  }

  Standard_EXPORT virtual void HilightWithColor(
    const occ::handle<PrsMgr_PresentationManager>& thePrsMgr,
    const occ::handle<Prs3d_Drawer>&               theStyle,
    const int                                      theMode = 0);

  virtual void Unhilight(const occ::handle<PrsMgr_PresentationManager>& thePrsMgr,
                         const int                                      theMode = 0)
  {
    (void)theMode;
    if (mySelectable != nullptr)
    {
      thePrsMgr->Unhighlight(mySelectable);
    }
  }

  virtual void Clear(const occ::handle<PrsMgr_PresentationManager>& thePrsMgr,
                     const int                                      theMode = 0)
  {
    (void)thePrsMgr;
    (void)theMode;
  }

  virtual bool HasLocation() const
  {
    return mySelectable != nullptr && mySelectable->HasTransformation();
  }

  virtual TopLoc_Location Location() const
  {
    return mySelectable != nullptr && mySelectable->HasTransformation()
             ? TopLoc_Location(mySelectable->Transformation())
             : TopLoc_Location();
  }

  virtual void SetLocation(const TopLoc_Location& theLocation) { (void)theLocation; }

  bool IsSelected() const { return myIsSelected; }

  void SetSelected(const bool theIsSelected) { myIsSelected = theIsSelected; }

  Standard_EXPORT bool Select(const AIS_SelectionScheme theSelScheme,
                              const bool                theIsDetected) const;

  Standard_DEPRECATED("Deprecated method - IsSelected() should be used instead")

  int State() const { return myIsSelected ? 1 : 0; }

  void State(const int theStatus) { myIsSelected = (theStatus == 1); }

  virtual bool IsAutoHilight() const
  {
    return mySelectable == nullptr || mySelectable->IsAutoHilight();
  }

  virtual bool IsForcedHilight() const { return false; }

  virtual void SetZLayer(const Graphic3d_ZLayerId theLayerId) { (void)theLayerId; }

  virtual void UpdateHighlightTrsf(const occ::handle<V3d_Viewer>&                 theViewer,
                                   const occ::handle<PrsMgr_PresentationManager>& theManager,
                                   const int                                      theDispMode)
  {
    if (mySelectable != nullptr)
    {
      theManager->UpdateHighlightTrsf(theViewer, mySelectable, theDispMode);
    }
  }

  bool IsSameSelectable(const occ::handle<SelectMgr_SelectableObject>& theOther) const
  {
    return mySelectable == theOther.get();
  }

  bool ComesFromDecomposition() const { return myFromDecomposition; }

  void SetComesFromDecomposition(const bool theIsFromDecomposition)
  {
    myFromDecomposition = theIsFromDecomposition;
  }

  Standard_EXPORT virtual void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

public:
  Standard_DEPRECATED("Deprecated method - SetSelectable() should be used instead")

  void Set(const occ::handle<SelectMgr_SelectableObject>& theSelObj) { SetSelectable(theSelObj); }

  Standard_DEPRECATED("Deprecated method - SetPriority() should be used instead")

  void Set(const int thePriority) { SetPriority(thePriority); }

protected:
  SelectMgr_SelectableObject* mySelectable;

  int  mypriority;
  bool myIsSelected;
  bool myFromDecomposition;
};
