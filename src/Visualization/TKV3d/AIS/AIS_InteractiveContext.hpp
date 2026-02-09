#pragma once

#include <AIS_InteractiveObject.hpp>
#include <AIS_GlobalStatus.hpp>
#include <NCollection_DataMap.hpp>
#include <AIS_DisplayMode.hpp>

#include <PrsMgr_DisplayStatus.hpp>

typedef PrsMgr_DisplayStatus AIS_DisplayStatus;

#include <AIS_KindOfInteractive.hpp>
#include <NCollection_List.hpp>
#include <AIS_Selection.hpp>

enum AIS_SelectionModesConcurrency
{
  AIS_SelectionModesConcurrency_Single,

  AIS_SelectionModesConcurrency_GlobalOrLocal,

  AIS_SelectionModesConcurrency_Multiple,
};

#include <AIS_SelectionScheme.hpp>

enum AIS_StatusOfDetection
{
  AIS_SOD_Error,
  AIS_SOD_Nothing,
  AIS_SOD_AllBad,
  AIS_SOD_Selected,
  AIS_SOD_OnlyOneDetected,
  AIS_SOD_OnlyOneGood,
  AIS_SOD_SeveralGood
};

enum AIS_StatusOfPick
{
  AIS_SOP_Error,
  AIS_SOP_NothingSelected,
  AIS_SOP_Removed,
  AIS_SOP_OneSelected,
  AIS_SOP_SeveralSelected
};

enum AIS_TypeOfIso
{
  AIS_TOI_IsoU,
  AIS_TOI_IsoV,
  AIS_TOI_Both
};

#include <Aspect_TypeOfFacingModel.hpp>
#include <NCollection_Vec2.hpp>
#include <Standard_TypeDef.hpp>
#include <Prs3d_Drawer.hpp>

enum Prs3d_TypeOfHighlight
{
  Prs3d_TypeOfHighlight_None = 0,
  Prs3d_TypeOfHighlight_Selected,
  Prs3d_TypeOfHighlight_Dynamic,
  Prs3d_TypeOfHighlight_LocalSelected,
  Prs3d_TypeOfHighlight_LocalDynamic,
  Prs3d_TypeOfHighlight_SubIntensity,
  Prs3d_TypeOfHighlight_NB
};

#include <PrsMgr_PresentationManager.hpp>
#include <SelectMgr_AndOrFilter.hpp>
#include <NCollection_IndexedMap.hpp>
#include <NCollection_Shared.hpp>
#include <SelectMgr_Filter.hpp>

enum SelectMgr_PickingStrategy
{
  SelectMgr_PickingStrategy_FirstAcceptable,

  SelectMgr_PickingStrategy_OnlyTopmost
};

#include <SelectMgr_SelectionManager.hpp>
#include <StdSelect_ViewerSelector3d.hpp>
#include <TCollection_AsciiString.hpp>
#include <gp_Pnt2d.hpp>
#include <NCollection_Array1.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Sequence.hpp>
#include <Quantity_Color.hpp>
class SelectMgr_EntityOwner;

class V3d_Viewer;
class V3d_View;
class TopLoc_Location;
class TCollection_ExtendedString;
class Prs3d_LineAspect;
class Prs3d_BasicAspect;
class TopoDS_Shape;
class SelectMgr_Filter;

class AIS_InteractiveContext : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(AIS_InteractiveContext, Standard_Transient)
public:
  Standard_EXPORT AIS_InteractiveContext(const occ::handle<V3d_Viewer>& MainViewer);

  Standard_EXPORT ~AIS_InteractiveContext() override;

  Standard_EXPORT PrsMgr_DisplayStatus
    DisplayStatus(const occ::handle<AIS_InteractiveObject>& anIobj) const;

  Standard_EXPORT void Status(const occ::handle<AIS_InteractiveObject>& anObj,
                              TCollection_ExtendedString&               astatus) const;

  Standard_EXPORT bool IsDisplayed(const occ::handle<AIS_InteractiveObject>& anIobj) const;

  Standard_EXPORT bool IsDisplayed(const occ::handle<AIS_InteractiveObject>& aniobj,
                                   const int                                 aMode) const;

  void SetAutoActivateSelection(const bool theIsAuto) { myIsAutoActivateSelMode = theIsAuto; }

  bool GetAutoActivateSelection() const { return myIsAutoActivateSelMode; }

  Standard_EXPORT void Display(const occ::handle<AIS_InteractiveObject>& theIObj,
                               const bool                                theToUpdateViewer);

  Standard_EXPORT void Display(
    const occ::handle<AIS_InteractiveObject>& theIObj,
    const int                                 theDispMode,
    const int                                 theSelectionMode,
    const bool                                theToUpdateViewer,
    const PrsMgr_DisplayStatus                theDispStatus = PrsMgr_DisplayStatus_None);

  Standard_EXPORT void Load(const occ::handle<AIS_InteractiveObject>& theObj,
                            const int                                 theSelectionMode = -1);

  Standard_EXPORT void Erase(const occ::handle<AIS_InteractiveObject>& theIObj,
                             const bool                                theToUpdateViewer);

  Standard_EXPORT void EraseAll(const bool theToUpdateViewer);

  Standard_EXPORT void DisplayAll(const bool theToUpdateViewer);

  Standard_EXPORT void EraseSelected(const bool theToUpdateViewer);

  Standard_EXPORT void DisplaySelected(const bool theToUpdateViewer);

  void ClearPrs(const occ::handle<AIS_InteractiveObject>& theIObj,
                const int                                 theMode,
                const bool                                theToUpdateViewer)
  {
    ClearGlobalPrs(theIObj, theMode, theToUpdateViewer);
  }

  Standard_EXPORT void Remove(const occ::handle<AIS_InteractiveObject>& theIObj,
                              const bool                                theToUpdateViewer);

  Standard_EXPORT void RemoveAll(const bool theToUpdateViewer);

  Standard_EXPORT void Redisplay(const occ::handle<AIS_InteractiveObject>& theIObj,
                                 const bool                                theToUpdateViewer,
                                 const bool                                theAllModes = false);

  Standard_EXPORT void Redisplay(const AIS_KindOfInteractive theTypeOfObject,
                                 const int                   theSignature,
                                 const bool                  theToUpdateViewer);

  Standard_EXPORT void RecomputePrsOnly(const occ::handle<AIS_InteractiveObject>& theIObj,
                                        const bool                                theToUpdateViewer,
                                        const bool theAllModes = false);

  Standard_EXPORT void RecomputeSelectionOnly(const occ::handle<AIS_InteractiveObject>& anIObj);

  Standard_EXPORT void Update(const occ::handle<AIS_InteractiveObject>& theIObj,
                              const bool                                theUpdateViewer);

public:
  const occ::handle<Prs3d_Drawer>& HighlightStyle(const Prs3d_TypeOfHighlight theStyleType) const
  {
    return myStyles[theStyleType];
  }

  void SetHighlightStyle(const Prs3d_TypeOfHighlight      theStyleType,
                         const occ::handle<Prs3d_Drawer>& theStyle)
  {
    myStyles[theStyleType] = theStyle;
    if (theStyleType == Prs3d_TypeOfHighlight_None)
    {
      myDefaultDrawer = theStyle;
    }
  }

  const occ::handle<Prs3d_Drawer>& HighlightStyle() const
  {
    return myStyles[Prs3d_TypeOfHighlight_Dynamic];
  }

  void SetHighlightStyle(const occ::handle<Prs3d_Drawer>& theStyle)
  {
    myStyles[Prs3d_TypeOfHighlight_Dynamic] = theStyle;
  }

  const occ::handle<Prs3d_Drawer>& SelectionStyle() const
  {
    return myStyles[Prs3d_TypeOfHighlight_Selected];
  }

  void SetSelectionStyle(const occ::handle<Prs3d_Drawer>& theStyle)
  {
    myStyles[Prs3d_TypeOfHighlight_Selected] = theStyle;
  }

  Standard_EXPORT bool HighlightStyle(const occ::handle<AIS_InteractiveObject>& theObj,
                                      occ::handle<Prs3d_Drawer>&                theStyle) const;

  Standard_EXPORT bool HighlightStyle(const occ::handle<SelectMgr_EntityOwner>& theOwner,
                                      occ::handle<Prs3d_Drawer>&                theStyle) const;

  Standard_EXPORT bool IsHilighted(const occ::handle<AIS_InteractiveObject>& theObj) const;

  Standard_EXPORT bool IsHilighted(const occ::handle<SelectMgr_EntityOwner>& theOwner) const;

  Standard_EXPORT void HilightWithColor(const occ::handle<AIS_InteractiveObject>& theObj,
                                        const occ::handle<Prs3d_Drawer>&          theStyle,
                                        const bool theToUpdateViewer);

  Standard_EXPORT void Unhilight(const occ::handle<AIS_InteractiveObject>& theIObj,
                                 const bool                                theToUpdateViewer);

public:
  Standard_EXPORT Graphic3d_DisplayPriority
    DisplayPriority(const occ::handle<AIS_InteractiveObject>& theIObj) const;

  Standard_EXPORT void SetDisplayPriority(const occ::handle<AIS_InteractiveObject>& theIObj,
                                          const Graphic3d_DisplayPriority           thePriority);

  Standard_DEPRECATED("Deprecated since OCCT7.7, Graphic3d_DisplayPriority should be passed "
                      "instead of integer number to SetDisplayPriority()")

  void SetDisplayPriority(const occ::handle<AIS_InteractiveObject>& theIObj, const int thePriority)
  {
    SetDisplayPriority(theIObj, (Graphic3d_DisplayPriority)thePriority);
  }

  Standard_EXPORT Graphic3d_ZLayerId
    GetZLayer(const occ::handle<AIS_InteractiveObject>& theIObj) const;

  Standard_EXPORT void SetZLayer(const occ::handle<AIS_InteractiveObject>& theIObj,
                                 const Graphic3d_ZLayerId                  theLayerId);

  Standard_EXPORT void SetViewAffinity(const occ::handle<AIS_InteractiveObject>& theIObj,
                                       const occ::handle<V3d_View>&              theView,
                                       const bool                                theIsVisible);

public:
  int DisplayMode() const { return myDefaultDrawer->DisplayMode(); }

  Standard_EXPORT void SetDisplayMode(const int theMode, const bool theToUpdateViewer);

  Standard_EXPORT void SetDisplayMode(const occ::handle<AIS_InteractiveObject>& theIObj,
                                      const int                                 theMode,
                                      const bool                                theToUpdateViewer);

  Standard_EXPORT void UnsetDisplayMode(const occ::handle<AIS_InteractiveObject>& theIObj,
                                        const bool theToUpdateViewer);

public:
  Standard_EXPORT void SetLocation(const occ::handle<AIS_InteractiveObject>& theObject,
                                   const TopLoc_Location&                    theLocation);

  Standard_EXPORT void ResetLocation(const occ::handle<AIS_InteractiveObject>& theObject);

  Standard_EXPORT bool HasLocation(const occ::handle<AIS_InteractiveObject>& theObject) const;

  Standard_EXPORT TopLoc_Location
    Location(const occ::handle<AIS_InteractiveObject>& theObject) const;

  Standard_EXPORT void SetTransformPersistence(
    const occ::handle<AIS_InteractiveObject>&   theObject,
    const occ::handle<Graphic3d_TransformPers>& theTrsfPers);

public:
  Standard_EXPORT void SetPixelTolerance(const int thePrecision = 2);

  Standard_EXPORT int PixelTolerance() const;

  Standard_EXPORT void SetSelectionSensitivity(const occ::handle<AIS_InteractiveObject>& theObject,
                                               const int                                 theMode,
                                               const int theNewSensitivity);

  Standard_EXPORT occ::handle<V3d_View> LastActiveView() const;

  Standard_EXPORT AIS_StatusOfDetection MoveTo(const int                    theXPix,
                                               const int                    theYPix,
                                               const occ::handle<V3d_View>& theView,
                                               const bool                   theToRedrawOnUpdate);

  Standard_EXPORT AIS_StatusOfDetection MoveTo(const gp_Ax1&                theAxis,
                                               const occ::handle<V3d_View>& theView,
                                               const bool                   theToRedrawOnUpdate);

  Standard_EXPORT bool ClearDetected(bool theToRedrawImmediate = false);

  bool HasDetected() const { return !myLastPicked.IsNull(); }

  const occ::handle<SelectMgr_EntityOwner>& DetectedOwner() const { return myLastPicked; }

  occ::handle<AIS_InteractiveObject> DetectedInteractive() const
  {
    return occ::down_cast<AIS_InteractiveObject>(myLastPicked->Selectable());
  }

  Standard_DEPRECATED(
    "Local Context is deprecated - local selection should be used without Local Context")
  Standard_EXPORT bool HasDetectedShape() const;

  Standard_DEPRECATED(
    "Local Context is deprecated - local selection should be used without Local Context")
  Standard_EXPORT const TopoDS_Shape& DetectedShape() const;

  bool HasNextDetected() const
  {
    return !myDetectedSeq.IsEmpty() && myCurHighlighted <= myDetectedSeq.Upper();
  }

  Standard_EXPORT int HilightNextDetected(const occ::handle<V3d_View>& theView,
                                          const bool                   theToRedrawImmediate = true);

  Standard_EXPORT int HilightPreviousDetected(const occ::handle<V3d_View>& theView,
                                              const bool theToRedrawImmediate = true);

public:
  void InitDetected()
  {
    if (!myDetectedSeq.IsEmpty())
    {
      myCurDetected = NCollection_Sequence<int>::Lower();
    }
  }

  bool MoreDetected() const
  {
    return myCurDetected >= NCollection_Sequence<int>::Lower()
           && myCurDetected <= myDetectedSeq.Upper();
  }

  void NextDetected() { ++myCurDetected; }

  Standard_EXPORT occ::handle<SelectMgr_EntityOwner> DetectedCurrentOwner() const;

public:
  Standard_EXPORT AIS_StatusOfPick AddSelect(const occ::handle<SelectMgr_EntityOwner>& theObject);

  AIS_StatusOfPick AddSelect(const occ::handle<AIS_InteractiveObject>& theObject)
  {
    return AddSelect(theObject->GlobalSelOwner());
  }

  Standard_EXPORT AIS_StatusOfPick
    SelectRectangle(const NCollection_Vec2<int>& thePntMin,
                    const NCollection_Vec2<int>& thePntMax,
                    const occ::handle<V3d_View>& theView,
                    const AIS_SelectionScheme    theSelScheme = AIS_SelectionScheme_Replace);

  Standard_EXPORT AIS_StatusOfPick
    SelectPolygon(const NCollection_Array1<gp_Pnt2d>& thePolyline,
                  const occ::handle<V3d_View>&        theView,
                  const AIS_SelectionScheme           theSelScheme = AIS_SelectionScheme_Replace);

  Standard_EXPORT AIS_StatusOfPick
    SelectPoint(const NCollection_Vec2<int>& thePnt,
                const occ::handle<V3d_View>& theView,
                const AIS_SelectionScheme    theSelScheme = AIS_SelectionScheme_Replace);

  Standard_EXPORT AIS_StatusOfPick
    SelectDetected(const AIS_SelectionScheme theSelScheme = AIS_SelectionScheme_Replace);

  Standard_EXPORT Bnd_Box BoundingBoxOfSelection(const occ::handle<V3d_View>& theView) const;

  Standard_DEPRECATED("BoundingBoxOfSelection() should be called with View argument")

  Bnd_Box BoundingBoxOfSelection() const { return BoundingBoxOfSelection(occ::handle<V3d_View>()); }

  Standard_EXPORT AIS_StatusOfPick
    Select(const NCollection_Array1<occ::handle<SelectMgr_EntityOwner>>& theOwners,
           const AIS_SelectionScheme                                     theSelScheme);

  Standard_EXPORT void FitSelected(const occ::handle<V3d_View>& theView,
                                   const double                 theMargin,
                                   const bool                   theToUpdate);

  Standard_EXPORT void FitSelected(const occ::handle<V3d_View>& theView);

  bool ToHilightSelected() const { return myToHilightSelected; }

  void SetToHilightSelected(const bool toHilight) { myToHilightSelected = toHilight; }

  bool AutomaticHilight() const { return myAutoHilight; }

  void SetAutomaticHilight(bool theStatus) { myAutoHilight = theStatus; }

  Standard_EXPORT void SetSelected(const occ::handle<SelectMgr_EntityOwner>& theOwners,
                                   const bool                                theToUpdateViewer);

  Standard_EXPORT void SetSelected(const occ::handle<AIS_InteractiveObject>& theObject,
                                   const bool                                theToUpdateViewer);

  Standard_EXPORT void AddOrRemoveSelected(const occ::handle<AIS_InteractiveObject>& theObject,
                                           const bool theToUpdateViewer);

  Standard_EXPORT bool SetSelectedState(const occ::handle<SelectMgr_EntityOwner>& theOwner,
                                        const bool                                theIsSelected);

  Standard_EXPORT void HilightSelected(const bool theToUpdateViewer);

  Standard_EXPORT void UnhilightSelected(const bool theToUpdateViewer);

  void UpdateSelected(bool theToUpdateViewer) { HilightSelected(theToUpdateViewer); }

  Standard_EXPORT void ClearSelected(const bool theToUpdateViewer);

  Standard_EXPORT void AddOrRemoveSelected(const occ::handle<SelectMgr_EntityOwner>& theOwner,
                                           const bool theToUpdateViewer);

  bool IsSelected(const occ::handle<SelectMgr_EntityOwner>& theOwner) const
  {
    return !theOwner.IsNull() && theOwner->IsSelected();
  }

  Standard_EXPORT bool IsSelected(const occ::handle<AIS_InteractiveObject>& theObj) const;

  Standard_EXPORT occ::handle<AIS_InteractiveObject> FirstSelectedObject() const;

  int NbSelected() { return mySelection->Extent(); }

  void InitSelected() { mySelection->Init(); }

  bool MoreSelected() const { return mySelection->More(); }

  void NextSelected() { mySelection->Next(); }

  occ::handle<SelectMgr_EntityOwner> SelectedOwner() const
  {
    return !mySelection->More() ? occ::handle<SelectMgr_EntityOwner>() : mySelection->Value();
  }

  occ::handle<AIS_InteractiveObject> SelectedInteractive() const
  {
    return !mySelection->More()
             ? occ::handle<AIS_InteractiveObject>()
             : occ::down_cast<AIS_InteractiveObject>(mySelection->Value()->Selectable());
  }

  Standard_EXPORT bool HasSelectedShape() const;

  Standard_EXPORT TopoDS_Shape SelectedShape() const;

  bool HasApplicative() const { return SelectedInteractive()->HasOwner(); }

  occ::handle<Standard_Transient> Applicative() const { return SelectedInteractive()->GetOwner(); }

public:
  Standard_DEPRECATED(
    "Deprecated method - Graphic3d_ZLayerId with IsImmediate flag should be used instead")
  Standard_EXPORT bool BeginImmediateDraw();

  Standard_DEPRECATED(
    "Deprecated method - Graphic3d_ZLayerId with IsImmediate flag should be used instead")
  Standard_EXPORT bool ImmediateAdd(const occ::handle<AIS_InteractiveObject>& theObj,
                                    const int                                 theMode = 0);

  Standard_DEPRECATED(
    "Deprecated method - Graphic3d_ZLayerId with IsImmediate flag should be used instead")
  Standard_EXPORT bool EndImmediateDraw(const occ::handle<V3d_View>& theView);

  Standard_DEPRECATED(
    "Deprecated method - Graphic3d_ZLayerId with IsImmediate flag should be used instead")
  Standard_EXPORT bool EndImmediateDraw();

  Standard_DEPRECATED(
    "Deprecated method - Graphic3d_ZLayerId with IsImmediate flag should be used instead")
  Standard_EXPORT bool IsImmediateModeOn() const;

  void RedrawImmediate(const occ::handle<V3d_Viewer>& theViewer)
  {
    myMainPM->RedrawImmediate(theViewer);
  }

public:
  Standard_EXPORT void SetSelectionModeActive(
    const occ::handle<AIS_InteractiveObject>& theObj,
    const int                                 theMode,
    const bool                                theToActivate,
    const AIS_SelectionModesConcurrency theConcurrency = AIS_SelectionModesConcurrency_Multiple,
    const bool                          theIsForce     = false);

  void Activate(const occ::handle<AIS_InteractiveObject>& theObj,
                const int                                 theMode    = 0,
                const bool                                theIsForce = false)
  {
    SetSelectionModeActive(theObj,
                           theMode,
                           true,
                           AIS_SelectionModesConcurrency_GlobalOrLocal,
                           theIsForce);
  }

  Standard_EXPORT void Activate(const int theMode, const bool theIsForce = false);

  void Deactivate(const occ::handle<AIS_InteractiveObject>& theObj)
  {
    SetSelectionModeActive(theObj, -1, false, AIS_SelectionModesConcurrency_Single);
  }

  void Deactivate(const occ::handle<AIS_InteractiveObject>& theObj, const int theMode)
  {
    SetSelectionModeActive(theObj, theMode, false);
  }

  Standard_EXPORT void Deactivate(const int theMode);

  Standard_EXPORT void Deactivate();

  Standard_EXPORT void ActivatedModes(const occ::handle<AIS_InteractiveObject>& anIobj,
                                      NCollection_List<int>&                    theList) const;

  Standard_EXPORT void EntityOwners(
    occ::handle<NCollection_Shared<NCollection_IndexedMap<occ::handle<SelectMgr_EntityOwner>>>>&
                                              theOwners,
    const occ::handle<AIS_InteractiveObject>& theIObj,
    const int                                 theMode = -1) const;

public:
  SelectMgr_FilterType FilterType() const { return myFilters->FilterType(); }

  void SetFilterType(const SelectMgr_FilterType theFilterType)
  {
    myFilters->SetFilterType(theFilterType);
  }

  const NCollection_List<occ::handle<SelectMgr_Filter>>& Filters() const
  {
    return myFilters->StoredFilters();
  }

  const occ::handle<SelectMgr_AndOrFilter>& GlobalFilter() const { return myFilters; }

  void AddFilter(const occ::handle<SelectMgr_Filter>& theFilter) { myFilters->Add(theFilter); }

  void RemoveFilter(const occ::handle<SelectMgr_Filter>& theFilter)
  {
    myFilters->Remove(theFilter);
  }

  void RemoveFilters() { myFilters->Clear(); }

  SelectMgr_PickingStrategy PickingStrategy() const { return myPickingStrategy; }

  void SetPickingStrategy(const SelectMgr_PickingStrategy theStrategy)
  {
    myPickingStrategy = theStrategy;
  }

public:
  const occ::handle<Prs3d_Drawer>& DefaultDrawer() const { return myDefaultDrawer; }

  void SetDefaultDrawer(const occ::handle<Prs3d_Drawer>& theDrawer)
  {
    myDefaultDrawer                      = theDrawer;
    myStyles[Prs3d_TypeOfHighlight_None] = myDefaultDrawer;
  }

  const occ::handle<V3d_Viewer>& CurrentViewer() const { return myMainVwr; }

  const occ::handle<SelectMgr_SelectionManager>& SelectionManager() const { return mgrSelector; }

  const occ::handle<PrsMgr_PresentationManager>& MainPrsMgr() const { return myMainPM; }

  const occ::handle<StdSelect_ViewerSelector3d>& MainSelector() const
  {
    return mgrSelector->Selector();
  }

  Standard_EXPORT void UpdateCurrentViewer();

  Standard_EXPORT void DisplayedObjects(
    NCollection_List<occ::handle<AIS_InteractiveObject>>& aListOfIO) const;

  Standard_EXPORT void DisplayedObjects(
    const AIS_KindOfInteractive                           theWhichKind,
    const int                                             theWhichSignature,
    NCollection_List<occ::handle<AIS_InteractiveObject>>& theListOfIO) const;

  Standard_EXPORT void ErasedObjects(
    NCollection_List<occ::handle<AIS_InteractiveObject>>& theListOfIO) const;

  Standard_EXPORT void ErasedObjects(
    const AIS_KindOfInteractive                           theWhichKind,
    const int                                             theWhichSignature,
    NCollection_List<occ::handle<AIS_InteractiveObject>>& theListOfIO) const;

  Standard_EXPORT void ObjectsByDisplayStatus(
    const PrsMgr_DisplayStatus                            theStatus,
    NCollection_List<occ::handle<AIS_InteractiveObject>>& theListOfIO) const;

  Standard_EXPORT void ObjectsByDisplayStatus(
    const AIS_KindOfInteractive                           WhichKind,
    const int                                             WhichSignature,
    const PrsMgr_DisplayStatus                            theStatus,
    NCollection_List<occ::handle<AIS_InteractiveObject>>& theListOfIO) const;

  Standard_EXPORT void ObjectsInside(
    NCollection_List<occ::handle<AIS_InteractiveObject>>& aListOfIO,
    const AIS_KindOfInteractive                           WhichKind = AIS_KindOfInteractive_None,
    const int                                             WhichSignature = -1) const;

  NCollection_DataMap<occ::handle<AIS_InteractiveObject>, occ::handle<AIS_GlobalStatus>>::Iterator
    ObjectIterator() const
  {
    return NCollection_DataMap<occ::handle<AIS_InteractiveObject>,
                               occ::handle<AIS_GlobalStatus>>::Iterator(myObjects);
  }

  Standard_EXPORT void RebuildSelectionStructs();

  Standard_EXPORT void Disconnect(
    const occ::handle<AIS_InteractiveObject>& theAssembly,
    const occ::handle<AIS_InteractiveObject>& theObjToDisconnect = nullptr);

  Standard_EXPORT void ObjectsForView(
    NCollection_List<occ::handle<AIS_InteractiveObject>>& theListOfIO,
    const occ::handle<V3d_View>&                          theView,
    const bool                                            theIsVisibleInView,
    const PrsMgr_DisplayStatus theStatus = PrsMgr_DisplayStatus_None) const;

  Standard_EXPORT virtual gp_Pnt GravityPoint(const occ::handle<V3d_View>& theView) const;

public:
  Standard_EXPORT void DisplayActiveSensitive(const occ::handle<V3d_View>& aView);

  Standard_EXPORT void ClearActiveSensitive(const occ::handle<V3d_View>& aView);

  Standard_EXPORT void DisplayActiveSensitive(const occ::handle<AIS_InteractiveObject>& anObject,
                                              const occ::handle<V3d_View>&              aView);

public:
  Standard_EXPORT void SetLocalAttributes(const occ::handle<AIS_InteractiveObject>& theIObj,
                                          const occ::handle<Prs3d_Drawer>&          theDrawer,
                                          const bool theToUpdateViewer);

  Standard_EXPORT void UnsetLocalAttributes(const occ::handle<AIS_InteractiveObject>& theIObj,
                                            const bool theToUpdateViewer);

  Standard_EXPORT void SetCurrentFacingModel(
    const occ::handle<AIS_InteractiveObject>& aniobj,
    const Aspect_TypeOfFacingModel            aModel = Aspect_TOFM_BOTH_SIDE);

  Standard_EXPORT bool HasColor(const occ::handle<AIS_InteractiveObject>& aniobj) const;

  Standard_EXPORT void Color(const occ::handle<AIS_InteractiveObject>& aniobj,
                             Quantity_Color&                           acolor) const;

  Standard_EXPORT void SetColor(const occ::handle<AIS_InteractiveObject>& theIObj,
                                const Quantity_Color&                     theColor,
                                const bool                                theToUpdateViewer);

  Standard_EXPORT void UnsetColor(const occ::handle<AIS_InteractiveObject>& theIObj,
                                  const bool                                theToUpdateViewer);

  Standard_EXPORT virtual double Width(const occ::handle<AIS_InteractiveObject>& aniobj) const;

  Standard_EXPORT virtual void SetWidth(const occ::handle<AIS_InteractiveObject>& theIObj,
                                        const double                              theValue,
                                        const bool theToUpdateViewer);

  Standard_EXPORT virtual void UnsetWidth(const occ::handle<AIS_InteractiveObject>& theIObj,
                                          const bool theToUpdateViewer);

  Standard_EXPORT void SetMaterial(const occ::handle<AIS_InteractiveObject>& theIObj,
                                   const Graphic3d_MaterialAspect&           theMaterial,
                                   const bool                                theToUpdateViewer);

  Standard_EXPORT void UnsetMaterial(const occ::handle<AIS_InteractiveObject>& theIObj,
                                     const bool                                theToUpdateViewer);

  Standard_EXPORT void SetTransparency(const occ::handle<AIS_InteractiveObject>& theIObj,
                                       const double                              theValue,
                                       const bool                                theToUpdateViewer);

  Standard_EXPORT void UnsetTransparency(const occ::handle<AIS_InteractiveObject>& theIObj,
                                         const bool theToUpdateViewer);

  Standard_EXPORT void SetPolygonOffsets(const occ::handle<AIS_InteractiveObject>& theIObj,
                                         const int                                 theMode,
                                         const float                               theFactor,
                                         const float                               theUnits,
                                         const bool theToUpdateViewer);

  Standard_EXPORT bool HasPolygonOffsets(const occ::handle<AIS_InteractiveObject>& anObj) const;

  Standard_EXPORT void PolygonOffsets(const occ::handle<AIS_InteractiveObject>& anObj,
                                      int&                                      aMode,
                                      float&                                    aFactor,
                                      float&                                    aUnits) const;

public:
  Standard_EXPORT void SetTrihedronSize(const double theSize, const bool theToUpdateViewer);

  Standard_EXPORT double TrihedronSize() const;

public:
  Standard_EXPORT void SetPlaneSize(const double theSizeX,
                                    const double theSizeY,
                                    const bool   theToUpdateViewer);

  Standard_EXPORT void SetPlaneSize(const double theSize, const bool theToUpdateViewer);

  Standard_EXPORT bool PlaneSize(double& XSize, double& YSize) const;

public:
  Standard_EXPORT void SetDeviationCoefficient(const occ::handle<AIS_InteractiveObject>& theIObj,
                                               const double theCoefficient,
                                               const bool   theToUpdateViewer);

  Standard_EXPORT void SetDeviationAngle(const occ::handle<AIS_InteractiveObject>& theIObj,
                                         const double                              theAngle,
                                         const bool theToUpdateViewer);

  Standard_EXPORT void SetAngleAndDeviation(const occ::handle<AIS_InteractiveObject>& theIObj,
                                            const double                              theAngle,
                                            const bool theToUpdateViewer);

  void SetDeviationCoefficient(const double theCoefficient)
  {
    myDefaultDrawer->SetDeviationCoefficient(theCoefficient);
  }

  double DeviationCoefficient() const { return myDefaultDrawer->DeviationCoefficient(); }

  void SetDeviationAngle(const double theAngle) { myDefaultDrawer->SetDeviationAngle(theAngle); }

  double DeviationAngle() const { return myDefaultDrawer->DeviationAngle(); }

public:
  const occ::handle<Prs3d_LineAspect>& HiddenLineAspect() const
  {
    return myDefaultDrawer->HiddenLineAspect();
  }

  void SetHiddenLineAspect(const occ::handle<Prs3d_LineAspect>& theAspect) const
  {
    myDefaultDrawer->SetHiddenLineAspect(theAspect);
  }

  bool DrawHiddenLine() const { return myDefaultDrawer->DrawHiddenLine(); }

  void EnableDrawHiddenLine() const { myDefaultDrawer->EnableDrawHiddenLine(); }

  void DisableDrawHiddenLine() const { myDefaultDrawer->DisableDrawHiddenLine(); }

public:
  Standard_EXPORT void SetIsoNumber(const int NbIsos, const AIS_TypeOfIso WhichIsos = AIS_TOI_Both);

  Standard_EXPORT int IsoNumber(const AIS_TypeOfIso WhichIsos = AIS_TOI_Both);

  void IsoOnPlane(const bool theToSwitchOn) { myDefaultDrawer->SetIsoOnPlane(theToSwitchOn); }

  bool IsoOnPlane() const { return myDefaultDrawer->IsoOnPlane(); }

  Standard_EXPORT void IsoOnTriangulation(const bool                                theIsEnabled,
                                          const occ::handle<AIS_InteractiveObject>& theObject);

  void IsoOnTriangulation(const bool theToSwitchOn)
  {
    myDefaultDrawer->SetIsoOnTriangulation(theToSwitchOn);
  }

  bool IsoOnTriangulation() const { return myDefaultDrawer->IsoOnTriangulation(); }

public:
  Standard_DEPRECATED("Deprecated method Display() with obsolete argument "
                      "theToAllowDecomposition")

  void Display(const occ::handle<AIS_InteractiveObject>& theIObj,
               const int                                 theDispMode,
               const int                                 theSelectionMode,
               const bool                                theToUpdateViewer,
               const bool                                theToAllowDecomposition,
               const PrsMgr_DisplayStatus                theDispStatus = PrsMgr_DisplayStatus_None)
  {
    (void)theToAllowDecomposition;
    Display(theIObj, theDispMode, theSelectionMode, theToUpdateViewer, theDispStatus);
  }

  Standard_DEPRECATED("Deprecated method Load() with obsolete last argument "
                      "theToAllowDecomposition")

  void Load(const occ::handle<AIS_InteractiveObject>& theObj, int theSelectionMode, bool)
  {
    Load(theObj, theSelectionMode);
  }

  Standard_DEPRECATED("Deprecated method Hilight()")

  void Hilight(const occ::handle<AIS_InteractiveObject>& theObj, const bool theIsToUpdateViewer)
  {
    return HilightWithColor(theObj, myStyles[Prs3d_TypeOfHighlight_Dynamic], theIsToUpdateViewer);
  }

  Standard_DEPRECATED(
    "Deprecated method - presentation attributes should be assigned directly to object")
  Standard_EXPORT void SetSelectedAspect(const occ::handle<Prs3d_BasicAspect>& theAspect,
                                         const bool                            theToUpdateViewer);

  Standard_DEPRECATED("This method is deprecated - SelectRectangle() taking "
                      "AIS_SelectionScheme_Replace should be called instead")
  Standard_EXPORT AIS_StatusOfPick Select(const int                    theXPMin,
                                          const int                    theYPMin,
                                          const int                    theXPMax,
                                          const int                    theYPMax,
                                          const occ::handle<V3d_View>& theView,
                                          const bool                   theToUpdateViewer);

  Standard_DEPRECATED("This method is deprecated - SelectPolygon() taking "
                      "AIS_SelectionScheme_Replace should be called instead")
  Standard_EXPORT AIS_StatusOfPick Select(const NCollection_Array1<gp_Pnt2d>& thePolyline,
                                          const occ::handle<V3d_View>&        theView,
                                          const bool                          theToUpdateViewer);

  Standard_DEPRECATED("This method is deprecated - SelectDetected() taking "
                      "AIS_SelectionScheme_Replace should be called instead")
  Standard_EXPORT AIS_StatusOfPick Select(const bool theToUpdateViewer);

  Standard_DEPRECATED("This method is deprecated - SelectDetected() taking AIS_SelectionScheme_XOR "
                      "should be called instead")
  Standard_EXPORT AIS_StatusOfPick ShiftSelect(const bool theToUpdateViewer);

  Standard_DEPRECATED("This method is deprecated - SelectPolygon() taking AIS_SelectionScheme_XOR "
                      "should be called instead")
  Standard_EXPORT AIS_StatusOfPick ShiftSelect(const NCollection_Array1<gp_Pnt2d>& thePolyline,
                                               const occ::handle<V3d_View>&        theView,
                                               const bool theToUpdateViewer);

  Standard_DEPRECATED("This method is deprecated - SelectRectangle() taking "
                      "AIS_SelectionScheme_XOR should be called instead")
  Standard_EXPORT AIS_StatusOfPick ShiftSelect(const int                    theXPMin,
                                               const int                    theYPMin,
                                               const int                    theXPMax,
                                               const int                    theYPMax,
                                               const occ::handle<V3d_View>& theView,
                                               const bool                   theToUpdateViewer);

public:
  Standard_DEPRECATED("Local Context is deprecated - local selection should be used without Local "
                      "Context")

  void SetCurrentObject(const occ::handle<AIS_InteractiveObject>& theIObj,
                        const bool                                theToUpdateViewer)
  {
    SetSelected(theIObj, theToUpdateViewer);
  }

  Standard_DEPRECATED("Local Context is deprecated - local selection should be used without Local "
                      "Context")

  void AddOrRemoveCurrentObject(const occ::handle<AIS_InteractiveObject>& theObj,
                                const bool                                theIsToUpdateViewer)
  {
    AddOrRemoveSelected(theObj, theIsToUpdateViewer);
  }

  Standard_DEPRECATED("Local Context is deprecated - local selection should be used without Local "
                      "Context")

  void UpdateCurrent() { UpdateSelected(true); }

  Standard_DEPRECATED(
    "Local Context is deprecated - local selection should be used without Local Context")

  bool IsCurrent(const occ::handle<AIS_InteractiveObject>& theObject) const
  {
    return IsSelected(theObject);
  }

  Standard_DEPRECATED("Local Context is deprecated - local selection should be used without Local "
                      "Context")

  void InitCurrent() { InitSelected(); }

  Standard_DEPRECATED(
    "Local Context is deprecated - local selection should be used without Local Context")

  bool MoreCurrent() const { return MoreSelected(); }

  Standard_DEPRECATED("Local Context is deprecated - local selection should be used without Local "
                      "Context")

  void NextCurrent() { NextSelected(); }

  Standard_DEPRECATED(
    "Local Context is deprecated - local selection should be used without Local Context")

  occ::handle<AIS_InteractiveObject> Current() const { return SelectedInteractive(); }

  Standard_DEPRECATED(
    "Local Context is deprecated - local selection should be used without Local Context")

  int NbCurrents() { return NbSelected(); }

  Standard_DEPRECATED("Local Context is deprecated - local selection should be used without Local "
                      "Context")

  void HilightCurrents(const bool theToUpdateViewer) { HilightSelected(theToUpdateViewer); }

  Standard_DEPRECATED("Local Context is deprecated - local selection should be used without Local "
                      "Context")

  void UnhilightCurrents(const bool theToUpdateViewer) { UnhilightSelected(theToUpdateViewer); }

  Standard_DEPRECATED("Local Context is deprecated - local selection should be used without Local "
                      "Context")

  void ClearCurrents(const bool theToUpdateViewer) { ClearSelected(theToUpdateViewer); }

  Standard_DEPRECATED(
    "Local Context is deprecated - ::DetectedCurrentOwner() should be called instead")
  Standard_EXPORT const TopoDS_Shape& DetectedCurrentShape() const;

  Standard_DEPRECATED(
    "Local Context is deprecated - ::DetectedCurrentOwner() should be called instead")
  Standard_EXPORT occ::handle<AIS_InteractiveObject> DetectedCurrentObject() const;

public:
  const Quantity_Color& SubIntensityColor() const
  {
    return myStyles[Prs3d_TypeOfHighlight_SubIntensity]->Color();
  }

  void SetSubIntensityColor(const Quantity_Color& theColor)
  {
    myStyles[Prs3d_TypeOfHighlight_SubIntensity]->SetColor(theColor);
  }

  Standard_EXPORT void SubIntensityOn(const occ::handle<AIS_InteractiveObject>& theIObj,
                                      const bool                                theToUpdateViewer);

  Standard_EXPORT void SubIntensityOff(const occ::handle<AIS_InteractiveObject>& theIObj,
                                       const bool                                theToUpdateViewer);

  const occ::handle<AIS_Selection>& Selection() const { return mySelection; }

  void SetSelection(const occ::handle<AIS_Selection>& theSelection) { mySelection = theSelection; }

  Standard_EXPORT virtual void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

protected:
  Standard_EXPORT void GetDefModes(const occ::handle<AIS_InteractiveObject>& anIobj,
                                   int&                                      Dmode,
                                   int&                                      HiMod,
                                   int&                                      SelMode) const;

  Standard_EXPORT void EraseGlobal(const occ::handle<AIS_InteractiveObject>& theIObj,
                                   const bool                                theToUpdateViewer);

  Standard_EXPORT void ClearGlobal(const occ::handle<AIS_InteractiveObject>& theIObj,
                                   const bool                                theToUpdateViewer);

  Standard_EXPORT void ClearGlobalPrs(const occ::handle<AIS_InteractiveObject>& theObj,
                                      const int                                 theMode,
                                      const bool                                theToUpdateViewer);

  Standard_EXPORT void InitAttributes();

  Standard_EXPORT AIS_StatusOfDetection moveTo(const occ::handle<V3d_View>& theView,
                                               const bool                   theToRedrawOnUpdate);

  Standard_EXPORT bool isDetected(const occ::handle<AIS_InteractiveObject>& theObject);

  Standard_EXPORT void unselectOwners(const occ::handle<AIS_InteractiveObject>& theObject);

  Standard_EXPORT void highlightWithColor(const occ::handle<SelectMgr_EntityOwner>& theOwner,
                                          const occ::handle<V3d_Viewer>& theViewer = nullptr);

  Standard_EXPORT void highlightSelected(const occ::handle<SelectMgr_EntityOwner>& theOwner);

  Standard_EXPORT void highlightOwners(
    const NCollection_List<occ::handle<SelectMgr_EntityOwner>>& theOwners,
    const occ::handle<Prs3d_Drawer>&                            theStyle);

  Standard_EXPORT void highlightGlobal(const occ::handle<AIS_InteractiveObject>& theObj,
                                       const occ::handle<Prs3d_Drawer>&          theStyle,
                                       const int                                 theDispMode);

  Standard_EXPORT void unhighlightSelected(const bool theIsToHilightSubIntensity = false);

  Standard_EXPORT void unhighlightOwners(
    const NCollection_List<occ::handle<SelectMgr_EntityOwner>>& theOwners,
    const bool                                                  theIsToHilightSubIntensity = false);

  Standard_EXPORT void unhighlightGlobal(const occ::handle<AIS_InteractiveObject>& theObj);

  Standard_EXPORT void turnOnSubintensity(
    const occ::handle<AIS_InteractiveObject>& theObject          = nullptr,
    const int                                 theDispMode        = -1,
    const bool                                theIsDisplayedOnly = true) const;

  Standard_EXPORT void highlightWithSubintensity(
    const occ::handle<AIS_InteractiveObject>& theObject,
    const int                                 theMode) const;

  Standard_EXPORT void highlightWithSubintensity(const occ::handle<SelectMgr_EntityOwner>& theOwner,
                                                 const int theMode) const;

  const occ::handle<Prs3d_Drawer>& getHiStyle(
    const occ::handle<AIS_InteractiveObject>& theObj,
    const occ::handle<SelectMgr_EntityOwner>& theOwner) const
  {
    const occ::handle<Prs3d_Drawer>& aHiDrawer = theObj->DynamicHilightAttributes();
    if (!aHiDrawer.IsNull())
    {
      return aHiDrawer;
    }

    return myStyles[!theOwner.IsNull() && theOwner->ComesFromDecomposition()
                      ? Prs3d_TypeOfHighlight_LocalDynamic
                      : Prs3d_TypeOfHighlight_Dynamic];
  }

  Standard_EXPORT bool isSlowHiStyle(const occ::handle<SelectMgr_EntityOwner>& theOwner,
                                     const occ::handle<V3d_Viewer>&            theViewer) const;

  const occ::handle<Prs3d_Drawer>& getSelStyle(
    const occ::handle<AIS_InteractiveObject>& theObj,
    const occ::handle<SelectMgr_EntityOwner>& theOwner) const
  {
    const occ::handle<Prs3d_Drawer>& aHiDrawer = theObj->HilightAttributes();
    if (!aHiDrawer.IsNull())
    {
      return aHiDrawer;
    }

    return myStyles[!theOwner.IsNull() && theOwner->ComesFromDecomposition()
                      ? Prs3d_TypeOfHighlight_LocalSelected
                      : Prs3d_TypeOfHighlight_Selected];
  }

  Standard_EXPORT void setContextToObject(const occ::handle<AIS_InteractiveObject>& theObj);

  int getHilightMode(const occ::handle<AIS_InteractiveObject>& theObj,
                     const occ::handle<Prs3d_Drawer>&          theStyle,
                     const int                                 theDispMode) const
  {
    if (!theStyle.IsNull() && theStyle->DisplayMode() != -1
        && theObj->AcceptDisplayMode(theStyle->DisplayMode()))
    {
      return theStyle->DisplayMode();
    }
    else if (theDispMode != -1)
    {
      return theDispMode;
    }
    else if (theObj->HasDisplayMode())
    {
      return theObj->DisplayMode();
    }
    return myDefaultDrawer->DisplayMode();
  }

  void clearDynamicHighlight() const
  {
    if (myLastPicked.IsNull())
      return;

    myLastPicked->Selectable()->ClearDynamicHighlight(myMainPM);
  }

  Standard_EXPORT void setObjectStatus(const occ::handle<AIS_InteractiveObject>& theIObj,
                                       const PrsMgr_DisplayStatus                theStatus,
                                       const int                                 theDispyMode,
                                       const int                                 theSelectionMode);

protected:
  NCollection_DataMap<occ::handle<AIS_InteractiveObject>, occ::handle<AIS_GlobalStatus>> myObjects;
  occ::handle<SelectMgr_SelectionManager> mgrSelector;
  occ::handle<PrsMgr_PresentationManager> myMainPM;
  occ::handle<V3d_Viewer>                 myMainVwr;
  V3d_View*                               myLastActiveView;
  occ::handle<SelectMgr_EntityOwner>      myLastPicked;
  bool                                    myToHilightSelected;
  occ::handle<AIS_Selection>              mySelection;
  occ::handle<SelectMgr_AndOrFilter>      myFilters;

  occ::handle<Prs3d_Drawer> myDefaultDrawer;
  occ::handle<Prs3d_Drawer> myStyles[Prs3d_TypeOfHighlight_NB];
  NCollection_Sequence<int> myDetectedSeq;
  int                       myCurDetected;
  int                       myCurHighlighted;
  SelectMgr_PickingStrategy myPickingStrategy;
  bool                      myAutoHilight;
  bool                      myIsAutoActivateSelMode;
};
