#pragma once

#include <Aspect_VKey.hpp>

#include <NCollection_Array1.hpp>
#include <OSD_Timer.hpp>
#include <Standard_Transient.hpp>

#include <shared_mutex>

class Aspect_VKeySet : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(Aspect_VKeySet, Standard_Transient)
public:
  Standard_EXPORT Aspect_VKeySet();

  Aspect_VKeyFlags Modifiers() const
  {
    std::shared_lock<std::shared_mutex> aLock(myLock);
    return myModifiers;
  }

  double DownTime(Aspect_VKey theKey) const
  {
    std::shared_lock<std::shared_mutex> aLock(myLock);
    return myKeys[theKey].TimeDown;
  }

  double TimeUp(Aspect_VKey theKey) const
  {
    std::shared_lock<std::shared_mutex> aLock(myLock);
    return myKeys[theKey].TimeUp;
  }

  bool IsFreeKey(Aspect_VKey theKey) const
  {
    std::shared_lock<std::shared_mutex> aLock(myLock);
    return myKeys[theKey].KStatus == KeyStatus_Free;
  }

  bool IsKeyDown(Aspect_VKey theKey) const
  {
    std::shared_lock<std::shared_mutex> aLock(myLock);
    return myKeys[theKey].KStatus == KeyStatus_Pressed;
  }

  std::shared_mutex& Mutex() { return myLock; }

public:
  Standard_EXPORT void Reset();

  Standard_EXPORT void KeyDown(Aspect_VKey theKey, double theTime, double thePressure = 1.0);

  Standard_EXPORT void KeyUp(Aspect_VKey theKey, double theTime);

  Standard_EXPORT void KeyFromAxis(Aspect_VKey theNegative,
                                   Aspect_VKey thePositive,
                                   double      theTime,
                                   double      thePressure);

  bool HoldDuration(Aspect_VKey theKey, double theTime, double& theDuration)
  {
    double aPressure = -1.0;
    return HoldDuration(theKey, theTime, theDuration, aPressure);
  }

  Standard_EXPORT bool HoldDuration(Aspect_VKey theKey,
                                    double      theTime,
                                    double&     theDuration,
                                    double&     thePressure);

private:
  void KeyDown_Unlocked(Aspect_VKey theKey, double theTime, double thePressure);

  void KeyUp_Unlocked(Aspect_VKey theKey, double theTime);

private:
  enum KeyStatus
  {
    KeyStatus_Free,
    KeyStatus_Pressed,
    KeyStatus_Released,
  };

  struct KeyState
  {
    KeyState()
        : TimeDown(0.0),
          TimeUp(0.0),
          Pressure(1.0),
          KStatus(KeyStatus_Free)
    {
    }

    void Reset()
    {
      KStatus  = KeyStatus_Free;
      TimeDown = 0.0;
      TimeUp   = 0.0;
      Pressure = 1.0;
    }

    double    TimeDown;
    double    TimeUp;
    double    Pressure;
    KeyStatus KStatus;
  };

private:
  NCollection_Array1<KeyState> myKeys;
  mutable std::shared_mutex    myLock;
  Aspect_VKeyFlags             myModifiers;
};
