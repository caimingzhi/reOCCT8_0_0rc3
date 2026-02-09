#pragma once

#include <AIS_InteractiveObject.hpp>
#include <Graphic3d_AspectLine3d.hpp>
#include <Graphic3d_AspectMarker3d.hpp>
#include <SelectMgr_EntityOwner.hpp>

class Select3D_SensitiveSphere;

class AIS_LightSource : public AIS_InteractiveObject
{
  friend class AIS_LightSourceOwner;
  DEFINE_STANDARD_RTTIEXT(AIS_LightSource, AIS_InteractiveObject)
public:
  Standard_EXPORT AIS_LightSource(const occ::handle<Graphic3d_CLight>& theLightSource);

  const occ::handle<Graphic3d_CLight>& Light() const { return myLightSource; }

  void SetLight(const occ::handle<Graphic3d_CLight>& theLight)
  {
    myLightSource = theLight;
    SetToUpdate();
  }

public:
  bool ToDisplayName() const { return myToDisplayName; }

  void SetDisplayName(bool theToDisplay)
  {
    if (myToDisplayName != theToDisplay)
    {
      myToDisplayName = theToDisplay;
      SetToUpdate();
    }
  }

  bool ToDisplayRange() const { return myToDisplayRange; }

  void SetDisplayRange(bool theToDisplay)
  {
    if (myToDisplayRange != theToDisplay)
    {
      myToDisplayRange = theToDisplay;
      SetToUpdate();
    }
  }

  double Size() const { return mySize; }

  void SetSize(double theSize)
  {
    if (mySize != theSize)
    {
      mySize = theSize;
      SetToUpdate();
    }
  }

  int ArcSize() const { return mySensSphereArcSize; }

  void SetArcSize(int theSize)
  {
    if (mySensSphereArcSize != theSize)
    {
      mySensSphereArcSize = theSize;
      SetToUpdate();
    }
  }

  bool IsZoomable() const { return myIsZoomable; }

  void SetZoomable(bool theIsZoomable)
  {
    if (myIsZoomable != theIsZoomable)
    {
      myIsZoomable = theIsZoomable;
      SetToUpdate();
    }
  }

  void SetDraggable(bool theIsDraggable)
  {
    if (myIsDraggable != theIsDraggable)
    {
      myIsDraggable = theIsDraggable;
    }
  }

  bool ToSwitchOnClick() const { return myToSwitchOnClick; }

  void SetSwitchOnClick(bool theToHandle) { myToSwitchOnClick = theToHandle; }

  int NbArrows() const { return myNbArrows; }

  void SetNbArrows(int theNbArrows)
  {
    if (myNbArrows != theNbArrows)
    {
      myNbArrows = theNbArrows;
      SetToUpdate();
    }
  }

  const occ::handle<Graphic3d_MarkerImage>& MarkerImage(bool theIsEnabled) const
  {
    return myMarkerImages[theIsEnabled ? 1 : 0];
  }

  Aspect_TypeOfMarker MarkerType(bool theIsEnabled) const
  {
    return myMarkerTypes[theIsEnabled ? 1 : 0];
  }

  void SetMarkerImage(const occ::handle<Graphic3d_MarkerImage>& theImage, bool theIsEnabled)
  {
    myMarkerImages[theIsEnabled ? 1 : 0] = theImage;
    myMarkerTypes[theIsEnabled ? 1 : 0]  = !theImage.IsNull()
                                             ? Aspect_TOM_USERDEFINED
                                             : (theIsEnabled ? Aspect_TOM_O_POINT : Aspect_TOM_O_X);
  }

  void SetMarkerType(Aspect_TypeOfMarker theType, bool theIsEnabled)
  {
    myMarkerTypes[theIsEnabled ? 1 : 0] = theType;
  }

  int NbSplitsQuadric() const { return myNbSplitsQuadric; }

  void SetNbSplitsQuadric(int theNbSplits) { myNbSplitsQuadric = theNbSplits; }

  int NbSplitsArrow() const { return myNbSplitsArrow; }

  void SetNbSplitsArrow(int theNbSplits) { myNbSplitsArrow = theNbSplits; }

  AIS_KindOfInteractive Type() const override { return AIS_KindOfInteractive_LightSource; }

protected:
  bool AcceptDisplayMode(const int theMode) const override { return theMode == 0 || theMode == 1; }

  Standard_EXPORT void Compute(const occ::handle<PrsMgr_PresentationManager>& thePrsMgr,
                               const occ::handle<Prs3d_Presentation>&         thePrs,
                               const int                                      theMode) override;

  Standard_EXPORT void ComputeSelection(const occ::handle<SelectMgr_Selection>& theSel,
                                        const int                               theMode) override;

  Standard_EXPORT bool ProcessDragging(const occ::handle<AIS_InteractiveContext>& theCtx,
                                       const occ::handle<V3d_View>&               theView,
                                       const occ::handle<SelectMgr_EntityOwner>&  theOwner,
                                       const NCollection_Vec2<int>&               theDragFrom,
                                       const NCollection_Vec2<int>&               theDragTo,
                                       const AIS_DragAction theAction) override;

  Standard_EXPORT void setLocalTransformation(const occ::handle<TopLoc_Datum3D>& theTrsf) override;

  Standard_EXPORT virtual void updateLightLocalTransformation();

  Standard_EXPORT virtual void updateLightTransformPersistence();

  Standard_EXPORT virtual void updateLightAspects();

  Standard_EXPORT virtual void computeAmbient(const occ::handle<Prs3d_Presentation>& thePrs,
                                              const int                              theMode);

  Standard_EXPORT virtual void computeDirectional(const occ::handle<Prs3d_Presentation>& thePrs,
                                                  const int                              theMode);

  Standard_EXPORT virtual void computePositional(const occ::handle<Prs3d_Presentation>& thePrs,
                                                 const int                              theMode);

  Standard_EXPORT virtual void computeSpot(const occ::handle<Prs3d_Presentation>& thePrs,
                                           const int                              theMode);

protected:
  occ::handle<Graphic3d_CLight> myLightSource;

  occ::handle<Graphic3d_AspectMarker3d> myDisabledMarkerAspect;
  occ::handle<Graphic3d_AspectLine3d>   myArrowLineAspectShadow;
  occ::handle<Graphic3d_MarkerImage>    myMarkerImages[2];
  occ::handle<Select3D_SensitiveSphere> mySensSphere;
  Aspect_TypeOfMarker                   myMarkerTypes[2];
  Aspect_TypeOfMarker                   myCodirMarkerType;
  Aspect_TypeOfMarker                   myOpposMarkerType;

  gp_Trsf myLocTrsfStart;
  double  mySize;
  int     myNbArrows;
  int     myNbSplitsQuadric;
  int     myNbSplitsArrow;
  int     mySensSphereArcSize;
  bool    myIsZoomable;
  bool    myIsDraggable;

  bool myToDisplayName;
  bool myToDisplayRange;
  bool myToSwitchOnClick;
};

class AIS_LightSourceOwner : public SelectMgr_EntityOwner
{
  DEFINE_STANDARD_RTTIEXT(AIS_LightSourceOwner, SelectMgr_EntityOwner)
public:
  Standard_EXPORT AIS_LightSourceOwner(const occ::handle<AIS_LightSource>& theObject,
                                       int                                 thePriority = 5);

  Standard_EXPORT bool HandleMouseClick(const NCollection_Vec2<int>& thePoint,
                                        Aspect_VKeyMouse             theButton,
                                        Aspect_VKeyFlags             theModifiers,
                                        bool                         theIsDoubleClick) override;

  Standard_EXPORT void HilightWithColor(const occ::handle<PrsMgr_PresentationManager>& thePrsMgr,
                                        const occ::handle<Prs3d_Drawer>&               theStyle,
                                        const int theMode) override;

  Standard_EXPORT bool IsForcedHilight() const override;
};
