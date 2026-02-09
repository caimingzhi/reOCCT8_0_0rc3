#pragma once

#include <Media_Timer.hpp>
typedef Media_Timer AIS_AnimationTimer;

#include <NCollection_Sequence.hpp>
#include <TCollection_AsciiString.hpp>

struct AIS_AnimationProgress
{
  double Pts;
  double LocalPts;

  double LocalNormalized;

  AIS_AnimationProgress()
      : Pts(-1.0),
        LocalPts(-1.0),
        LocalNormalized(-1.0)
  {
  }
};

class AIS_Animation : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(AIS_Animation, Standard_Transient)
public:
  Standard_EXPORT AIS_Animation(const TCollection_AsciiString& theAnimationName);

  Standard_EXPORT ~AIS_Animation() override;

  const TCollection_AsciiString& Name() const { return myName; }

public:
  double StartPts() const { return myPtsStart; }

  void SetStartPts(const double thePtsStart) { myPtsStart = thePtsStart; }

  double Duration() const { return (std::max)(myOwnDuration, myChildrenDuration); }

  Standard_EXPORT void UpdateTotalDuration();

  bool HasOwnDuration() const { return myOwnDuration > 0.0; }

  double OwnDuration() const { return myOwnDuration; }

  void SetOwnDuration(const double theDuration) { myOwnDuration = theDuration; }

  Standard_EXPORT void Add(const occ::handle<AIS_Animation>& theAnimation);

  Standard_EXPORT void Clear();

  Standard_EXPORT occ::handle<AIS_Animation> Find(
    const TCollection_AsciiString& theAnimationName) const;

  Standard_EXPORT bool Remove(const occ::handle<AIS_Animation>& theAnimation);

  Standard_EXPORT bool Replace(const occ::handle<AIS_Animation>& theAnimationOld,
                               const occ::handle<AIS_Animation>& theAnimationNew);

  Standard_EXPORT void CopyFrom(const occ::handle<AIS_Animation>& theOther);

  const NCollection_Sequence<occ::handle<AIS_Animation>>& Children() const { return myAnimations; }

public:
  Standard_EXPORT virtual void StartTimer(const double theStartPts,
                                          const double thePlaySpeed,
                                          const bool   theToUpdate,
                                          const bool   theToStopTimer = false);

  Standard_EXPORT virtual double UpdateTimer();

  double ElapsedTime() const { return !myTimer.IsNull() ? myTimer->ElapsedTime() : 0.0; }

  const occ::handle<Media_Timer>& Timer() const { return myTimer; }

  void SetTimer(const occ::handle<Media_Timer>& theTimer) { myTimer = theTimer; }

public:
  Standard_EXPORT virtual void Start(const bool theToUpdate);

  Standard_EXPORT virtual void Pause();

  Standard_EXPORT virtual void Stop();

  bool IsStopped() { return myState != AnimationState_Started; }

  Standard_EXPORT virtual bool Update(const double thePts);

protected:
  Standard_EXPORT virtual void updateWithChildren(const AIS_AnimationProgress& thePosition);

  virtual void update(const AIS_AnimationProgress& theProgress) { (void)theProgress; }

protected:
  enum AnimationState
  {
    AnimationState_Started,
    AnimationState_Stopped,
    AnimationState_Paused
  };

protected:
  occ::handle<Media_Timer> myTimer;

  TCollection_AsciiString                          myName;
  NCollection_Sequence<occ::handle<AIS_Animation>> myAnimations;

  AnimationState myState;
  double         myPtsStart;
  double         myOwnDuration;
  double         myChildrenDuration;
};
