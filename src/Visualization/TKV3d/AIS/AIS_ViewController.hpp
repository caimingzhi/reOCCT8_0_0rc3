#pragma once

#include <Aspect_WindowInputListener.hpp>
#include <Aspect_XRHapticActionData.hpp>
#include <Aspect_XRTrackedDeviceRole.hpp>
#include <AIS_DragAction.hpp>

#include <AIS_SelectionScheme.hpp>
#include <NCollection_DataMap.hpp>

enum AIS_MouseGesture
{
  AIS_MouseGesture_NONE,

  AIS_MouseGesture_SelectRectangle,

  AIS_MouseGesture_SelectLasso,

  AIS_MouseGesture_Zoom,

  AIS_MouseGesture_ZoomVertical,

  AIS_MouseGesture_ZoomWindow,

  AIS_MouseGesture_Pan,
  AIS_MouseGesture_RotateOrbit,
  AIS_MouseGesture_RotateView,
  AIS_MouseGesture_Drag,
};

enum AIS_NavigationMode
{
  AIS_NavigationMode_Orbit,
  AIS_NavigationMode_FirstPersonFlight,
  AIS_NavigationMode_FirstPersonWalk,
};

enum
{
  AIS_NavigationMode_LOWER = 0,
  AIS_NavigationMode_UPPER = AIS_NavigationMode_FirstPersonWalk
};

#include <Aspect_ScrollDelta.hpp>

#include <AIS_SelectionScheme.hpp>
#include <NCollection_Vec2.hpp>
#include <Standard_TypeDef.hpp>
#include <NCollection_Sequence.hpp>
#include <V3d_TypeOfOrientation.hpp>

enum AIS_ViewSelectionTool
{
  AIS_ViewSelectionTool_Picking,
  AIS_ViewSelectionTool_RubberBand,
  AIS_ViewSelectionTool_Polygon,
  AIS_ViewSelectionTool_ZoomWindow,
};

enum AIS_ViewInputBufferType
{
  AIS_ViewInputBufferType_UI,
  AIS_ViewInputBufferType_GL,
};

class AIS_ViewInputBuffer
{
public:
  bool IsNewGesture;

  NCollection_Sequence<Aspect_ScrollDelta> ZoomActions;

  struct _orientation
  {
    bool                  ToFitAll;
    bool                  ToSetViewOrient;
    V3d_TypeOfOrientation ViewOrient;

    _orientation()
        : ToFitAll(false),
          ToSetViewOrient(false),
          ViewOrient(V3d_Xpos)
    {
    }
  } Orientation;

  struct _highlighting
  {
    bool                  ToHilight;
    NCollection_Vec2<int> Point;

    _highlighting()
        : ToHilight(false)
    {
    }
  } MoveTo;

  struct _selection
  {
    AIS_ViewSelectionTool                       Tool;
    AIS_SelectionScheme                         Scheme;
    NCollection_Sequence<NCollection_Vec2<int>> Points;
    bool                                        ToApplyTool;

    _selection()
        : Tool(AIS_ViewSelectionTool_Picking),
          Scheme(AIS_SelectionScheme_UNKNOWN),
          ToApplyTool(false)
    {
    }
  } Selection;

  struct _panningParams
  {
    bool                  ToStart;
    NCollection_Vec2<int> PointStart;
    bool                  ToPan;
    NCollection_Vec2<int> Delta;

    _panningParams()
        : ToStart(false),
          ToPan(false)
    {
    }
  } Panning;

  struct _draggingParams
  {
    bool                  ToStart;
    bool                  ToConfirm;
    bool                  ToMove;
    bool                  ToStop;
    bool                  ToAbort;
    NCollection_Vec2<int> PointStart;
    NCollection_Vec2<int> PointTo;

    _draggingParams()
        : ToStart(false),
          ToConfirm(false),
          ToMove(false),
          ToStop(false),
          ToAbort(false)
    {
    }
  } Dragging;

  struct _orbitRotation
  {
    bool                     ToStart;
    NCollection_Vec2<double> PointStart;
    bool                     ToRotate;
    NCollection_Vec2<double> PointTo;

    _orbitRotation()
        : ToStart(false),
          ToRotate(false)
    {
    }
  } OrbitRotation;

  struct _viewRotation
  {
    bool                     ToStart;
    NCollection_Vec2<double> PointStart;
    bool                     ToRotate;
    NCollection_Vec2<double> PointTo;

    _viewRotation()
        : ToStart(false),
          ToRotate(false)
    {
    }
  } ViewRotation;

  struct _zrotateParams
  {
    NCollection_Vec2<int> Point;
    double                Angle;
    bool                  ToRotate;

    _zrotateParams()
        : Angle(0.0),
          ToRotate(false)
    {
    }
  } ZRotate;

public:
  AIS_ViewInputBuffer()
      : IsNewGesture(false)
  {
  }

  void Reset()
  {
    Orientation.ToFitAll        = false;
    Orientation.ToSetViewOrient = false;
    MoveTo.ToHilight            = false;
    Selection.ToApplyTool       = false;
    IsNewGesture                = false;
    ZoomActions.Clear();
    Panning.ToStart        = false;
    Panning.ToPan          = false;
    Dragging.ToStart       = false;
    Dragging.ToConfirm     = false;
    Dragging.ToMove        = false;
    Dragging.ToStop        = false;
    Dragging.ToAbort       = false;
    OrbitRotation.ToStart  = false;
    OrbitRotation.ToRotate = false;
    ViewRotation.ToStart   = false;
    ViewRotation.ToRotate  = false;
    ZRotate.ToRotate       = false;
  }
};

enum AIS_RotationMode
{
  AIS_RotationMode_BndBoxActive,
  AIS_RotationMode_PickLast,
  AIS_RotationMode_PickCenter,
  AIS_RotationMode_CameraAt,
  AIS_RotationMode_BndBoxScene,
};

enum
{
  AIS_RotationMode_LOWER = 0,
  AIS_RotationMode_UPPER = AIS_RotationMode_BndBoxScene,
};

#include <Standard_Real.hpp>

enum AIS_WalkTranslation
{
  AIS_WalkTranslation_Forward = 0,
  AIS_WalkTranslation_Side,
  AIS_WalkTranslation_Up,
};

enum AIS_WalkRotation
{
  AIS_WalkRotation_Yaw = 0,
  AIS_WalkRotation_Pitch,
  AIS_WalkRotation_Roll,
};

struct AIS_WalkPart
{
  double Value;
  double Pressure;
  double Duration;

  bool IsEmpty() const { return std::abs(Value) <= RealSmall(); }

  AIS_WalkPart()
      : Value(0.0),
        Pressure(1.0),
        Duration(0.0)
  {
  }
};

struct AIS_WalkDelta
{

  AIS_WalkDelta()
      : myIsDefined(false),
        myIsJumping(false),
        myIsCrouching(false),
        myIsRunning(false)
  {
  }

  const AIS_WalkPart& operator[](AIS_WalkTranslation thePart) const
  {
    return myTranslation[thePart];
  }

  AIS_WalkPart& operator[](AIS_WalkTranslation thePart) { return myTranslation[thePart]; }

  const AIS_WalkPart& operator[](AIS_WalkRotation thePart) const { return myRotation[thePart]; }

  AIS_WalkPart& operator[](AIS_WalkRotation thePart) { return myRotation[thePart]; }

  bool IsJumping() const { return myIsJumping; }

  void SetJumping(bool theIsJumping) { myIsJumping = theIsJumping; }

  bool IsCrouching() const { return myIsCrouching; }

  void SetCrouching(bool theIsCrouching) { myIsCrouching = theIsCrouching; }

  bool IsRunning() const { return myIsRunning; }

  void SetRunning(bool theIsRunning) { myIsRunning = theIsRunning; }

  bool IsDefined() const { return myIsDefined || !IsEmpty(); }

  void SetDefined(bool theIsDefined) { myIsDefined = theIsDefined; }

  bool IsEmpty() const { return !ToMove() && !ToRotate(); }

  bool ToMove() const
  {
    return !myTranslation[AIS_WalkTranslation_Forward].IsEmpty()
           || !myTranslation[AIS_WalkTranslation_Side].IsEmpty()
           || !myTranslation[AIS_WalkTranslation_Up].IsEmpty();
  }

  bool ToRotate() const
  {
    return !myRotation[AIS_WalkRotation_Yaw].IsEmpty()
           || !myRotation[AIS_WalkRotation_Pitch].IsEmpty()
           || !myRotation[AIS_WalkRotation_Roll].IsEmpty();
  }

private:
  AIS_WalkPart myTranslation[3];
  AIS_WalkPart myRotation[3];
  bool         myIsDefined;
  bool         myIsJumping;
  bool         myIsCrouching;
  bool         myIsRunning;
};

#include <gp_Pnt.hpp>
#include <gp_Quaternion.hpp>
#include <NCollection_Vec3.hpp>
#include <Standard_TypeDef.hpp>
#include <NCollection_Array1.hpp>
#include <OSD_Timer.hpp>
#include <Precision.hpp>
#include <Quantity_ColorRGBA.hpp>

class AIS_Animation;
class AIS_AnimationCamera;
class AIS_InteractiveObject;
class AIS_InteractiveContext;
class AIS_Point;
class AIS_RubberBand;
class AIS_XRTrackedDevice;
class SelectMgr_EntityOwner;
class V3d_View;
class WNT_HIDSpaceMouse;

class AIS_ViewController : public Aspect_WindowInputListener
{
public:
  Standard_EXPORT AIS_ViewController();

  Standard_EXPORT ~AIS_ViewController() override;

  const AIS_ViewInputBuffer& InputBuffer(AIS_ViewInputBufferType theType) const
  {
    return theType == AIS_ViewInputBufferType_UI ? myUI : myGL;
  }

  AIS_ViewInputBuffer& ChangeInputBuffer(AIS_ViewInputBufferType theType)
  {
    return theType == AIS_ViewInputBufferType_UI ? myUI : myGL;
  }

  const occ::handle<AIS_AnimationCamera>& ViewAnimation() const { return myViewAnimation; }

  void SetViewAnimation(const occ::handle<AIS_AnimationCamera>& theAnimation)
  {
    myViewAnimation = theAnimation;
  }

  Standard_EXPORT void AbortViewAnimation();

  const occ::handle<AIS_Animation>& ObjectsAnimation() const { return myObjAnimation; }

  void SetObjectsAnimation(const occ::handle<AIS_Animation>& theAnimation)
  {
    myObjAnimation = theAnimation;
  }

  bool ToPauseObjectsAnimation() const { return myToPauseObjAnimation; }

  void SetPauseObjectsAnimation(bool theToPause) { myToPauseObjAnimation = theToPause; }

  bool IsContinuousRedraw() const { return myIsContinuousRedraw; }

  void SetContinuousRedraw(bool theToEnable) { myIsContinuousRedraw = theToEnable; }

public:
  AIS_RotationMode RotationMode() const { return myRotationMode; }

  void SetRotationMode(AIS_RotationMode theMode) { myRotationMode = theMode; }

  AIS_NavigationMode NavigationMode() const { return myNavigationMode; }

  Standard_EXPORT void SetNavigationMode(AIS_NavigationMode theMode);

  float MouseAcceleration() const { return myMouseAccel; }

  void SetMouseAcceleration(float theRatio) { myMouseAccel = theRatio; }

  float OrbitAcceleration() const { return myOrbitAccel; }

  void SetOrbitAcceleration(float theRatio) { myOrbitAccel = theRatio; }

  bool ToShowPanAnchorPoint() const { return myToShowPanAnchorPoint; }

  void SetShowPanAnchorPoint(bool theToShow) { myToShowPanAnchorPoint = theToShow; }

  bool ToShowRotateCenter() const { return myToShowRotateCenter; }

  void SetShowRotateCenter(bool theToShow) { myToShowRotateCenter = theToShow; }

  bool ToLockOrbitZUp() const { return myToLockOrbitZUp; }

  void SetLockOrbitZUp(bool theToForceUp) { myToLockOrbitZUp = theToForceUp; }

  bool ToAllowTouchZRotation() const { return myToAllowTouchZRotation; }

  void SetAllowTouchZRotation(bool theToEnable) { myToAllowTouchZRotation = theToEnable; }

  bool ToAllowRotation() const { return myToAllowRotation; }

  void SetAllowRotation(bool theToEnable) { myToAllowRotation = theToEnable; }

  bool ToAllowPanning() const { return myToAllowPanning; }

  void SetAllowPanning(bool theToEnable) { myToAllowPanning = theToEnable; }

  bool ToAllowZooming() const { return myToAllowZooming; }

  void SetAllowZooming(bool theToEnable) { myToAllowZooming = theToEnable; }

  bool ToAllowZFocus() const { return myToAllowZFocus; }

  void SetAllowZFocus(bool theToEnable) { myToAllowZFocus = theToEnable; }

  bool ToAllowHighlight() const { return myToAllowHighlight; }

  void SetAllowHighlight(bool theToEnable) { myToAllowHighlight = theToEnable; }

  bool ToAllowDragging() const { return myToAllowDragging; }

  void SetAllowDragging(bool theToEnable) { myToAllowDragging = theToEnable; }

  bool ToStickToRayOnZoom() const { return myToStickToRayOnZoom; }

  void SetStickToRayOnZoom(bool theToEnable) { myToStickToRayOnZoom = theToEnable; }

  bool ToStickToRayOnRotation() const { return myToStickToRayOnRotation; }

  void SetStickToRayOnRotation(bool theToEnable) { myToStickToRayOnRotation = theToEnable; }

  bool ToInvertPitch() const { return myToInvertPitch; }

  void SetInvertPitch(bool theToInvert) { myToInvertPitch = theToInvert; }

  float WalkSpeedAbsolute() const { return myWalkSpeedAbsolute; }

  void SetWalkSpeedAbsolute(float theSpeed) { myWalkSpeedAbsolute = theSpeed; }

  float WalkSpeedRelative() const { return myWalkSpeedRelative; }

  void SetWalkSpeedRelative(float theFactor) { myWalkSpeedRelative = theFactor; }

  float ThrustSpeed() const { return myThrustSpeed; }

  void SetThrustSpeed(float theSpeed) { myThrustSpeed = theSpeed; }

  bool HasPreviousMoveTo() const { return myPrevMoveTo != NCollection_Vec2<int>(-1); }

  const NCollection_Vec2<int>& PreviousMoveTo() const { return myPrevMoveTo; }

  void ResetPreviousMoveTo() { myPrevMoveTo = NCollection_Vec2<int>(-1); }

  bool ToDisplayXRAuxDevices() const { return myToDisplayXRAuxDevices; }

  void SetDisplayXRAuxDevices(bool theToDisplay) { myToDisplayXRAuxDevices = theToDisplay; }

  bool ToDisplayXRHands() const { return myToDisplayXRHands; }

  void SetDisplayXRHands(bool theToDisplay) { myToDisplayXRHands = theToDisplay; }

public:
  using Aspect_WindowInputListener::ChangeKeys;
  using Aspect_WindowInputListener::Keys;

  Standard_EXPORT void KeyDown(Aspect_VKey theKey,
                               double      theTime,
                               double      thePressure = 1.0) override;

  Standard_EXPORT void KeyUp(Aspect_VKey theKey, double theTime) override;

  Standard_EXPORT void KeyFromAxis(Aspect_VKey theNegative,
                                   Aspect_VKey thePositive,
                                   double      theTime,
                                   double      thePressure) override;

  Standard_EXPORT AIS_WalkDelta FetchNavigationKeys(double theCrouchRatio, double theRunRatio);

public:
  const NCollection_DataMap<unsigned int, AIS_MouseGesture>& MouseGestureMap() const
  {
    return myMouseGestureMap;
  }

  NCollection_DataMap<unsigned int, AIS_MouseGesture>& ChangeMouseGestureMap()
  {
    return myMouseGestureMap;
  }

  const NCollection_DataMap<unsigned int, AIS_SelectionScheme>& MouseSelectionSchemes() const
  {
    return myMouseSelectionSchemes;
  }

  NCollection_DataMap<unsigned int, AIS_SelectionScheme>& ChangeMouseSelectionSchemes()
  {
    return myMouseSelectionSchemes;
  }

  double MouseDoubleClickInterval() const { return myMouseDoubleClickInt; }

  void SetMouseDoubleClickInterval(double theSeconds) { myMouseDoubleClickInt = theSeconds; }

  Standard_EXPORT virtual void SelectInViewer(
    const NCollection_Vec2<int>& thePnt,
    const AIS_SelectionScheme    theScheme = AIS_SelectionScheme_Replace);

  Standard_EXPORT virtual void SelectInViewer(
    const NCollection_Sequence<NCollection_Vec2<int>>& thePnts,
    const AIS_SelectionScheme                          theScheme = AIS_SelectionScheme_Replace);

  Standard_EXPORT virtual void UpdateRubberBand(const NCollection_Vec2<int>& thePntFrom,
                                                const NCollection_Vec2<int>& thePntTo);

  Standard_EXPORT virtual void UpdatePolySelection(const NCollection_Vec2<int>& thePnt,
                                                   bool                         theToAppend);

  Standard_EXPORT virtual bool UpdateZoom(const Aspect_ScrollDelta& theDelta);

  Standard_EXPORT virtual bool UpdateZRotation(double theAngle);

  Standard_EXPORT bool UpdateMouseScroll(const Aspect_ScrollDelta& theDelta) override;

  Standard_EXPORT bool UpdateMouseButtons(const NCollection_Vec2<int>& thePoint,
                                          Aspect_VKeyMouse             theButtons,
                                          Aspect_VKeyFlags             theModifiers,
                                          bool                         theIsEmulated) override;

  Standard_EXPORT bool UpdateMousePosition(const NCollection_Vec2<int>& thePoint,
                                           Aspect_VKeyMouse             theButtons,
                                           Aspect_VKeyFlags             theModifiers,
                                           bool                         theIsEmulated) override;

  Standard_EXPORT virtual bool UpdateMouseClick(const NCollection_Vec2<int>& thePoint,
                                                Aspect_VKeyMouse             theButton,
                                                Aspect_VKeyFlags             theModifiers,
                                                bool                         theIsDoubleClick);

  using Aspect_WindowInputListener::PressMouseButton;
  using Aspect_WindowInputListener::ReleaseMouseButton;

  using Aspect_WindowInputListener::LastMouseFlags;
  using Aspect_WindowInputListener::LastMousePosition;
  using Aspect_WindowInputListener::PressedMouseButtons;

public:
  float TouchToleranceScale() const { return myTouchToleranceScale; }

  void SetTouchToleranceScale(float theTolerance) { myTouchToleranceScale = theTolerance; }

  Standard_EXPORT void AddTouchPoint(size_t                          theId,
                                     const NCollection_Vec2<double>& thePnt,
                                     bool theClearBefore = false) override;

  Standard_EXPORT bool RemoveTouchPoint(size_t theId, bool theClearSelectPnts = false) override;

  Standard_EXPORT void UpdateTouchPoint(size_t                          theId,
                                        const NCollection_Vec2<double>& thePnt) override;

  using Aspect_WindowInputListener::HasTouchPoints;

public:
  Standard_EXPORT bool Update3dMouse(const WNT_HIDSpaceMouse& theEvent) override;

public:
  void ProcessExpose() override {}

  void ProcessConfigure(bool theIsResized) override { (void)theIsResized; }

  void ProcessInput() override {}

  void ProcessFocus(bool theIsActivated) override
  {
    if (!theIsActivated)
    {
      ResetViewInput();
    }
  }

  void ProcessClose() override {}

public:
  using Aspect_WindowInputListener::EventTime;

  Standard_EXPORT virtual void ResetViewInput();

  Standard_EXPORT virtual void UpdateViewOrientation(V3d_TypeOfOrientation theOrientation,
                                                     bool                  theToFitAll);

  Standard_EXPORT virtual void FlushViewEvents(const occ::handle<AIS_InteractiveContext>& theCtx,
                                               const occ::handle<V3d_View>&               theView,
                                               bool theToHandle = false);

  Standard_EXPORT virtual void HandleViewEvents(const occ::handle<AIS_InteractiveContext>& theCtx,
                                                const occ::handle<V3d_View>&               theView);

public:
  Standard_EXPORT virtual void OnSelectionChanged(const occ::handle<AIS_InteractiveContext>& theCtx,
                                                  const occ::handle<V3d_View>& theView);

  Standard_EXPORT virtual void OnObjectDragged(const occ::handle<AIS_InteractiveContext>& theCtx,
                                               const occ::handle<V3d_View>&               theView,
                                               AIS_DragAction theAction);

  Standard_EXPORT virtual void OnSubviewChanged(const occ::handle<AIS_InteractiveContext>& theCtx,
                                                const occ::handle<V3d_View>& theOldView,
                                                const occ::handle<V3d_View>& theNewView);

  Standard_EXPORT virtual bool PickPoint(gp_Pnt&                                    thePnt,
                                         const occ::handle<AIS_InteractiveContext>& theCtx,
                                         const occ::handle<V3d_View>&               theView,
                                         const NCollection_Vec2<int>&               theCursor,
                                         bool theToStickToPickRay);

  Standard_EXPORT virtual bool PickAxis(gp_Pnt&                                    theTopPnt,
                                        const occ::handle<AIS_InteractiveContext>& theCtx,
                                        const occ::handle<V3d_View>&               theView,
                                        const gp_Ax1&                              theAxis);

  Standard_EXPORT virtual gp_Pnt GravityPoint(const occ::handle<AIS_InteractiveContext>& theCtx,
                                              const occ::handle<V3d_View>&               theView);

  Standard_EXPORT virtual void FitAllAuto(const occ::handle<AIS_InteractiveContext>& theCtx,
                                          const occ::handle<V3d_View>&               theView);

public:
  Standard_EXPORT virtual void handleViewOrientationKeys(
    const occ::handle<AIS_InteractiveContext>& theCtx,
    const occ::handle<V3d_View>&               theView);

  Standard_EXPORT virtual AIS_WalkDelta handleNavigationKeys(
    const occ::handle<AIS_InteractiveContext>& theCtx,
    const occ::handle<V3d_View>&               theView);

  Standard_EXPORT virtual void handleCameraActions(
    const occ::handle<AIS_InteractiveContext>& theCtx,
    const occ::handle<V3d_View>&               theView,
    const AIS_WalkDelta&                       theWalk);

  Standard_EXPORT virtual void handleMoveTo(const occ::handle<AIS_InteractiveContext>& theCtx,
                                            const occ::handle<V3d_View>&               theView);

  bool toAskNextFrame() const { return myToAskNextFrame; }

  void setAskNextFrame(bool theToDraw = true) { myToAskNextFrame = theToDraw; }

  bool hasPanningAnchorPoint() const { return !Precision::IsInfinite(myPanPnt3d.X()); }

  const gp_Pnt& panningAnchorPoint() const { return myPanPnt3d; }

  void setPanningAnchorPoint(const gp_Pnt& thePnt) { myPanPnt3d = thePnt; }

  Standard_EXPORT virtual void handlePanning(const occ::handle<V3d_View>& theView);

  Standard_EXPORT virtual void handleZRotate(const occ::handle<V3d_View>& theView);

  double MinZoomDistance() const { return myMinCamDistance; }

  void SetMinZoomDistance(double theDist) { myMinCamDistance = theDist; }

  Standard_EXPORT virtual void handleZoom(const occ::handle<V3d_View>& theView,
                                          const Aspect_ScrollDelta&    theParams,
                                          const gp_Pnt*                thePnt);

  Standard_EXPORT virtual void handleZFocusScroll(const occ::handle<V3d_View>& theView,
                                                  const Aspect_ScrollDelta&    theParams);

  Standard_EXPORT virtual void handleOrbitRotation(const occ::handle<V3d_View>& theView,
                                                   const gp_Pnt&                thePnt,
                                                   bool                         theToLockZUp);

  Standard_EXPORT virtual void handleViewRotation(const occ::handle<V3d_View>& theView,
                                                  double                       theYawExtra,
                                                  double                       thePitchExtra,
                                                  double                       theRoll,
                                                  bool theToRestartOnIncrement);

  Standard_EXPORT virtual void handleViewRedraw(const occ::handle<AIS_InteractiveContext>& theCtx,
                                                const occ::handle<V3d_View>&               theView);

public:
  Standard_EXPORT virtual void handleXRInput(const occ::handle<AIS_InteractiveContext>& theCtx,
                                             const occ::handle<V3d_View>&               theView,
                                             const AIS_WalkDelta&                       theWalk);

  Standard_EXPORT virtual void handleXRTurnPad(const occ::handle<AIS_InteractiveContext>& theCtx,
                                               const occ::handle<V3d_View>&               theView);

  Standard_EXPORT virtual void handleXRTeleport(const occ::handle<AIS_InteractiveContext>& theCtx,
                                                const occ::handle<V3d_View>&               theView);

  Standard_EXPORT virtual void handleXRPicking(const occ::handle<AIS_InteractiveContext>& theCtx,
                                               const occ::handle<V3d_View>&               theView);

  Standard_EXPORT virtual void handleXRHighlight(const occ::handle<AIS_InteractiveContext>& theCtx,
                                                 const occ::handle<V3d_View>& theView);

  Standard_EXPORT virtual void handleXRPresentations(
    const occ::handle<AIS_InteractiveContext>& theCtx,
    const occ::handle<V3d_View>&               theView);

  Standard_EXPORT virtual int handleXRMoveTo(const occ::handle<AIS_InteractiveContext>& theCtx,
                                             const occ::handle<V3d_View>&               theView,
                                             const gp_Trsf&                             thePose,
                                             const bool theToHighlight);

protected:
  Standard_EXPORT virtual void flushBuffers(const occ::handle<AIS_InteractiveContext>& theCtx,
                                            const occ::handle<V3d_View>&               theView);

  Standard_EXPORT virtual void flushGestures(const occ::handle<AIS_InteractiveContext>& theCtx,
                                             const occ::handle<V3d_View>&               theView);

  void updateEventsTime(double& thePrevTime, double& theCurrTime)
  {
    thePrevTime      = myLastEventsTime;
    myLastEventsTime = EventTime();
    theCurrTime      = myLastEventsTime;
  }

  Standard_EXPORT virtual void handleSelectionPick(
    const occ::handle<AIS_InteractiveContext>& theCtx,
    const occ::handle<V3d_View>&               theView);

  Standard_EXPORT virtual void handleDynamicHighlight(
    const occ::handle<AIS_InteractiveContext>& theCtx,
    const occ::handle<V3d_View>&               theView);

  Standard_EXPORT virtual void handleSelectionPoly(
    const occ::handle<AIS_InteractiveContext>& theCtx,
    const occ::handle<V3d_View>&               theView);

  Standard_EXPORT virtual void contextLazyMoveTo(const occ::handle<AIS_InteractiveContext>& theCtx,
                                                 const occ::handle<V3d_View>&               theView,
                                                 const NCollection_Vec2<int>&               thePnt);

protected:
  AIS_ViewInputBuffer myUI;
  AIS_ViewInputBuffer myGL;

  double myLastEventsTime;
  bool   myToAskNextFrame;
  bool   myIsContinuousRedraw;

  double             myMinCamDistance;
  AIS_RotationMode   myRotationMode;
  AIS_NavigationMode myNavigationMode;
  float              myMouseAccel;
  float              myOrbitAccel;
  bool               myToShowPanAnchorPoint;
  bool               myToShowRotateCenter;
  bool               myToLockOrbitZUp;
  bool               myToInvertPitch;
  bool               myToAllowTouchZRotation;
  bool               myToAllowRotation;
  bool               myToAllowPanning;
  bool               myToAllowZooming;
  bool               myToAllowZFocus;
  bool               myToAllowHighlight;
  bool               myToAllowDragging;
  bool               myToStickToRayOnZoom;
  bool               myToStickToRayOnRotation;

  float myWalkSpeedAbsolute;
  float myWalkSpeedRelative;
  float myThrustSpeed;
  bool  myHasThrust;

  occ::handle<AIS_AnimationCamera>   myViewAnimation;
  occ::handle<AIS_Animation>         myObjAnimation;
  bool                               myToPauseObjAnimation;
  occ::handle<AIS_RubberBand>        myRubberBand;
  occ::handle<SelectMgr_EntityOwner> myDragOwner;
  occ::handle<AIS_InteractiveObject> myDragObject;
  NCollection_Vec2<int>              myPrevMoveTo;
  bool                               myHasHlrOnBeforeRotation;

protected:
  NCollection_Array1<occ::handle<AIS_XRTrackedDevice>> myXRPrsDevices;

  Quantity_Color             myXRLaserTeleColor;
  Quantity_Color             myXRLaserPickColor;
  Aspect_XRTrackedDeviceRole myXRLastTeleportHand;
  Aspect_XRTrackedDeviceRole myXRLastPickingHand;
  Aspect_XRHapticActionData  myXRTeleportHaptic;
  Aspect_XRHapticActionData  myXRPickingHaptic;
  Aspect_XRHapticActionData  myXRSelectHaptic;
  double                     myXRLastPickDepthLeft;
  double                     myXRLastPickDepthRight;
  double                     myXRTurnAngle;

  bool myToDisplayXRAuxDevices;
  bool myToDisplayXRHands;

protected:
  double myMouseClickThreshold;
  double myMouseDoubleClickInt;
  float  myScrollZoomRatio;

  NCollection_DataMap<unsigned int, AIS_MouseGesture>    myMouseGestureMap;
  NCollection_DataMap<unsigned int, AIS_MouseGesture>    myMouseGestureMapDrag;
  AIS_MouseGesture                                       myMouseActiveGesture;
  NCollection_DataMap<unsigned int, AIS_SelectionScheme> myMouseSelectionSchemes;
  bool                                                   myMouseActiveIdleRotation;
  NCollection_Vec2<int>                                  myMousePressPoint;
  NCollection_Vec2<int>                                  myMouseProgressPoint;
  OSD_Timer                                              myMouseClickTimer;
  int                                                    myMouseClickCounter;
  int                                                    myMouseSingleButton;
  bool                                                   myMouseStopDragOnUnclick;

protected:
  float myTouchToleranceScale;
  float myTouchClickThresholdPx;
  float myTouchRotationThresholdPx;
  float myTouchZRotationThreshold;
  float myTouchPanThresholdPx;
  float myTouchZoomThresholdPx;
  float myTouchZoomRatio;
  float myTouchDraggingThresholdPx;

  Aspect_Touch myTouchClick;
  OSD_Timer    myTouchDoubleTapTimer;

  NCollection_Vec2<double> myStartPanCoord;
  NCollection_Vec2<double> myStartRotCoord;
  int                      myNbTouchesLast;
  bool                     myUpdateStartPointPan;
  bool                     myUpdateStartPointRot;
  bool                     myUpdateStartPointZRot;

protected:
  occ::handle<AIS_Point> myAnchorPointPrs1;
  occ::handle<AIS_Point> myAnchorPointPrs2;
  gp_Pnt                 myPanPnt3d;
  gp_Pnt                 myRotatePnt3d;
  gp_Dir                 myCamStartOpUp;
  gp_Dir                 myCamStartOpDir;
  gp_Pnt                 myCamStartOpEye;
  gp_Pnt                 myCamStartOpCenter;
  gp_Vec                 myCamStartOpToCenter;
  gp_Vec                 myCamStartOpToEye;
  double                 myCurrentRollAngle;
};
