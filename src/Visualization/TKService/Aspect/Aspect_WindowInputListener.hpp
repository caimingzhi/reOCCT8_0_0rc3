#pragma once

#include <Aspect_VKeySet.hpp>

#include <NCollection_Vec2.hpp>

class Aspect_Touch
{
public:
  NCollection_Vec2<double> From;
  NCollection_Vec2<double> To;

  bool IsPreciseDevice;

  NCollection_Vec2<double> Delta() const { return To - From; }

  Aspect_Touch()
      : From(0.0, 0.0),
        To(0.0, 0.0),
        IsPreciseDevice(false)
  {
  }

  Aspect_Touch(const NCollection_Vec2<double>& thePnt, bool theIsPreciseDevice)
      : From(thePnt),
        To(thePnt),
        IsPreciseDevice(theIsPreciseDevice)
  {
  }

  Aspect_Touch(double theX, double theY, bool theIsPreciseDevice)
      : From(theX, theY),
        To(theX, theY),
        IsPreciseDevice(theIsPreciseDevice)
  {
  }
};

#include <NCollection_IndexedDataMap.hpp>
#include <NCollection_Vec2.hpp>
#include <Standard_TypeDef.hpp>
#include <NCollection_Vec3.hpp>
#include <NCollection_Vec4.hpp>
#include <NCollection_Mat4.hpp>

struct Aspect_ScrollDelta;
class WNT_HIDSpaceMouse;

class Aspect_WindowInputListener
{
public:
  Standard_EXPORT virtual ~Aspect_WindowInputListener();

  double EventTime() const { return myEventTimer.ElapsedTime(); }

  virtual void ProcessExpose() = 0;

  virtual void ProcessConfigure(bool theIsResized) = 0;

  virtual void ProcessInput() = 0;

  virtual void ProcessFocus(bool theIsActivated) = 0;

  virtual void ProcessClose() = 0;

public:
  const Aspect_VKeySet& Keys() const { return myKeys; }

  Aspect_VKeySet& ChangeKeys() { return myKeys; }

  Standard_EXPORT virtual void KeyDown(Aspect_VKey theKey,
                                       double      theTime,
                                       double      thePressure = 1.0) = 0;

  Standard_EXPORT virtual void KeyUp(Aspect_VKey theKey, double theTime) = 0;

  Standard_EXPORT virtual void KeyFromAxis(Aspect_VKey theNegative,
                                           Aspect_VKey thePositive,
                                           double      theTime,
                                           double      thePressure) = 0;

public:
  virtual bool UpdateMouseScroll(const Aspect_ScrollDelta& theDelta) = 0;

  virtual bool UpdateMouseButtons(const NCollection_Vec2<int>& thePoint,
                                  Aspect_VKeyMouse             theButtons,
                                  Aspect_VKeyFlags             theModifiers,
                                  bool                         theIsEmulated) = 0;

  virtual bool UpdateMousePosition(const NCollection_Vec2<int>& thePoint,
                                   Aspect_VKeyMouse             theButtons,
                                   Aspect_VKeyFlags             theModifiers,
                                   bool                         theIsEmulated) = 0;

  bool PressMouseButton(const NCollection_Vec2<int>& thePoint,
                        Aspect_VKeyMouse             theButton,
                        Aspect_VKeyFlags             theModifiers,
                        bool                         theIsEmulated)
  {
    return UpdateMouseButtons(thePoint, myMousePressed | theButton, theModifiers, theIsEmulated);
  }

  bool ReleaseMouseButton(const NCollection_Vec2<int>& thePoint,
                          Aspect_VKeyMouse             theButton,
                          Aspect_VKeyFlags             theModifiers,
                          bool                         theIsEmulated)
  {
    Aspect_VKeyMouse aButtons = myMousePressed & (~theButton);
    return UpdateMouseButtons(thePoint, aButtons, theModifiers, theIsEmulated);
  }

  Aspect_VKeyMouse PressedMouseButtons() const { return myMousePressed; }

  Aspect_VKeyFlags LastMouseFlags() const { return myMouseModifiers; }

  const NCollection_Vec2<int>& LastMousePosition() const { return myMousePositionLast; }

public:
  bool HasTouchPoints() const { return !myTouchPoints.IsEmpty(); }

  const NCollection_IndexedDataMap<size_t, Aspect_Touch>& TouchPoints() const
  {
    return myTouchPoints;
  }

  Standard_EXPORT virtual void AddTouchPoint(size_t                          theId,
                                             const NCollection_Vec2<double>& thePnt,
                                             bool theClearBefore = false);

  Standard_EXPORT virtual bool RemoveTouchPoint(size_t theId, bool theClearSelectPnts = false);

  Standard_EXPORT virtual void UpdateTouchPoint(size_t                          theId,
                                                const NCollection_Vec2<double>& thePnt);

public:
  float Get3dMouseTranslationScale() const { return my3dMouseAccelTrans; }

  void Set3dMouseTranslationScale(float theScale) { my3dMouseAccelTrans = theScale; }

  float Get3dMouseRotationScale() const { return my3dMouseAccelRotate; }

  void Set3dMouseRotationScale(float theScale) { my3dMouseAccelRotate = theScale; }

  bool To3dMousePreciseInput() const { return my3dMouseIsQuadric; }

  void Set3dMousePreciseInput(bool theIsQuadric) { my3dMouseIsQuadric = theIsQuadric; }

  const NCollection_Vec3<bool>& Get3dMouseIsNoRotate() const { return my3dMouseNoRotate; }

  NCollection_Vec3<bool>& Change3dMouseIsNoRotate() { return my3dMouseNoRotate; }

  const NCollection_Vec3<bool>& Get3dMouseToReverse() const { return my3dMouseToReverse; }

  NCollection_Vec3<bool>& Change3dMouseToReverse() { return my3dMouseToReverse; }

  virtual bool Update3dMouse(const WNT_HIDSpaceMouse& theEvent) = 0;

  Standard_EXPORT virtual bool update3dMouseTranslation(const WNT_HIDSpaceMouse& theEvent);

  Standard_EXPORT virtual bool update3dMouseRotation(const WNT_HIDSpaceMouse& theEvent);

  Standard_EXPORT virtual bool update3dMouseKeys(const WNT_HIDSpaceMouse& theEvent);

protected:
  Standard_EXPORT Aspect_WindowInputListener();

protected:
  OSD_Timer myEventTimer;

protected:
  Aspect_VKeySet myKeys;

protected:
  NCollection_Vec2<int> myMousePositionLast;
  Aspect_VKeyMouse      myMousePressed;
  Aspect_VKeyFlags      myMouseModifiers;

protected:
  NCollection_IndexedDataMap<size_t, Aspect_Touch> myTouchPoints;

protected:
  bool                   my3dMouseButtonState[32];
  NCollection_Vec3<bool> my3dMouseNoRotate;
  NCollection_Vec3<bool> my3dMouseToReverse;
  float                  my3dMouseAccelTrans;
  float                  my3dMouseAccelRotate;
  bool                   my3dMouseIsQuadric;
};
