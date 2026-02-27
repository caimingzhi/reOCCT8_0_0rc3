#pragma once

#include <Standard_Assert.hpp>
#include <Standard_TypeDef.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>
#include <Precision.hpp>
#include <TCollection_AsciiString.hpp>

namespace System { namespace log {
class Message_ProgressRange;
}} // namespace System::log

namespace System { namespace log {
class Message_ProgressIndicator;
}} // namespace System::log


namespace System { namespace log {
class Message_ProgressScope
{
public:
  class NullString;

public:
  Message_ProgressScope()
      : myProgress(nullptr),
        myParent(nullptr),
        myName(nullptr),
        myStart(0.),
        myPortion(1.),
        myMax(1.),
        myValue(0.),
        myIsActive(false),
        myIsOwnName(false),
        myIsInfinite(false)
  {
  }

  Message_ProgressScope(const Message_ProgressRange&   theRange,
                        const TCollection_AsciiString& theName,
                        double                         theMax,
                        bool                           isInfinite = false);

  template <size_t N>
  Message_ProgressScope(const Message_ProgressRange& theRange,
                        const char (&theName)[N],
                        double theMax,
                        bool   isInfinite = false);

  Message_ProgressScope(const Message_ProgressRange& theRange,
                        const NullString*            theName,
                        double                       theMax,
                        bool                         isInfinite = false);

  void SetName(const TCollection_AsciiString& theName)
  {
    if (myIsOwnName)
    {
      Standard::Free(myName);
      myIsOwnName = false;
    }
    myName = nullptr;
    if (!theName.IsEmpty())
    {
      myIsOwnName = true;
      myName      = (char*)Standard::AllocateOptimal(size_t(theName.Length()) + size_t(1));
      char* aName = (char*)myName;
      memcpy(aName, theName.ToCString(), theName.Length());
      aName[theName.Length()] = '\0';
    }
  }

  template <size_t N>
  void SetName(const char (&theName)[N])
  {
    if (myIsOwnName)
    {
      Standard::Free(myName);
      myIsOwnName = false;
    }
    myName = theName;
  }

public:
  bool UserBreak() const;

  bool More() const { return !UserBreak(); }

  Message_ProgressRange Next(double theStep = 1.);

public:
  void Show();

  bool IsActive() const { return myIsActive; }

  const char* Name() const { return myName; }

  const Message_ProgressScope* Parent() const { return myParent; }

  double MaxValue() const { return myMax; }

  double Value() const;

  bool IsInfinite() const { return myIsInfinite; }

  double GetPortion() const { return myPortion; }

public:
  ~Message_ProgressScope()
  {
    Close();
    if (myIsOwnName)
    {
      Standard::Free(myName);
      myIsOwnName = false;
      myName      = nullptr;
    }
  }

  void Close();

  DEFINE_STANDARD_ALLOC

private:
  Message_ProgressScope(Message_ProgressIndicator* theProgress);

  double localToGlobal(const double theVal) const;

private:
  Message_ProgressScope(const Message_ProgressScope& theOther) = delete;

  Message_ProgressScope& operator=(const Message_ProgressScope& theOther) = delete;

private:
  Message_ProgressIndicator*   myProgress;
  const Message_ProgressScope* myParent;
  const char*                  myName;

  double myStart;

  double myPortion;

  double myMax;
  double myValue;

  bool myIsActive;
  bool myIsOwnName;
  bool myIsInfinite;

private:
  friend class Message_ProgressIndicator;
  friend class Message_ProgressRange;
};
}} // namespace System::log


#include <Message_ProgressRange.hpp>

inline System::log::Message_ProgressScope::Message_ProgressScope(System::log::Message_ProgressIndicator* theProgress)
    : myProgress(theProgress),
      myParent(nullptr),
      myName(nullptr),
      myStart(0.),
      myPortion(1.),
      myMax(1.),
      myValue(0.),
      myIsActive(theProgress != nullptr),
      myIsOwnName(false),
      myIsInfinite(false)
{
}

inline System::log::Message_ProgressScope::Message_ProgressScope(const System::log::Message_ProgressRange&   theRange,
                                                    const TCollection_AsciiString& theName,
                                                    double                         theMax,
                                                    bool                           isInfinite)
    : myProgress(theRange.myParentScope != nullptr ? theRange.myParentScope->myProgress : nullptr),
      myParent(theRange.myParentScope),
      myName(nullptr),
      myStart(theRange.myStart),
      myPortion(theRange.myDelta),
      myMax((std::max)(1.e-6, theMax)),
      myValue(0.),
      myIsActive(myProgress != nullptr && !theRange.myWasUsed),
      myIsOwnName(false),
      myIsInfinite(isInfinite)
{
  SetName(theName);
  Standard_ASSERT_VOID(!theRange.myWasUsed,
                       "System::log::Message_ProgressRange is used to initialize more than one scope");
  theRange.myWasUsed = true;
}

template <size_t N>
System::log::Message_ProgressScope::Message_ProgressScope(const System::log::Message_ProgressRange& theRange,
                                             const char (&theName)[N],
                                             double theMax,
                                             bool   isInfinite)
    : myProgress(theRange.myParentScope != nullptr ? theRange.myParentScope->myProgress : nullptr),
      myParent(theRange.myParentScope),
      myName(theName),
      myStart(theRange.myStart),
      myPortion(theRange.myDelta),
      myMax((std::max)(1.e-6, theMax)),
      myValue(0.),
      myIsActive(myProgress != nullptr && !theRange.myWasUsed),
      myIsOwnName(false),
      myIsInfinite(isInfinite)
{
  Standard_ASSERT_VOID(!theRange.myWasUsed,
                       "System::log::Message_ProgressRange is used to initialize more than one scope");
  theRange.myWasUsed = true;
}

inline System::log::Message_ProgressScope::Message_ProgressScope(const System::log::Message_ProgressRange& theRange,
                                                    const NullString*,
                                                    double theMax,
                                                    bool   isInfinite)
    : myProgress(theRange.myParentScope != nullptr ? theRange.myParentScope->myProgress : nullptr),
      myParent(theRange.myParentScope),
      myName(nullptr),
      myStart(theRange.myStart),
      myPortion(theRange.myDelta),
      myMax((std::max)(1.e-6, theMax)),
      myValue(0.),
      myIsActive(myProgress != nullptr && !theRange.myWasUsed),
      myIsOwnName(false),
      myIsInfinite(isInfinite)
{
  Standard_ASSERT_VOID(!theRange.myWasUsed,
                       "System::log::Message_ProgressRange is used to initialize more than one scope");
  theRange.myWasUsed = true;
}

inline void System::log::Message_ProgressScope::Close()
{
  if (!myIsActive)
  {
    return;
  }

  double aCurr  = localToGlobal(myValue);
  myValue       = (myIsInfinite ? math::precision::Precision::Infinite() : myMax);
  double aDelta = myPortion - aCurr;
  if (aDelta > 0.)
  {
    myProgress->Increment(aDelta, *this);
  }
  Standard_ASSERT_VOID(myParent == 0 || myParent->myIsActive,
                       "Parent progress scope has been closed before child");

  myIsActive = false;
}

inline bool System::log::Message_ProgressScope::UserBreak() const
{
  return myProgress && myProgress->UserBreak();
}

inline System::log::Message_ProgressRange System::log::Message_ProgressScope::Next(double theStep)
{
  if (myIsActive && theStep > 0.)
  {
    double aCurr  = localToGlobal(myValue);
    double aNext  = localToGlobal(myValue += theStep);
    double aDelta = aNext - aCurr;
    if (aDelta > 0.)
    {
      return System::log::Message_ProgressRange(*this, myStart + aCurr, aDelta);
    }
  }
  return System::log::Message_ProgressRange();
}

inline void System::log::Message_ProgressScope::Show()
{
  if (myIsActive)
  {
    myProgress->Show(*this, true);
  }
}

inline double System::log::Message_ProgressScope::localToGlobal(const double theVal) const
{
  if (theVal <= 0.)
    return 0.;

  if (!myIsInfinite)
  {
    if (myMax - theVal < RealSmall())
      return myPortion;
    return myPortion * theVal / myMax;
  }

  double x = theVal / myMax;

  return myPortion * x / (1. + x);
}

inline double System::log::Message_ProgressScope::Value() const
{
  if (!myIsActive)
  {
    return myIsInfinite ? math::precision::Precision::Infinite() : myMax;
  }

  double aVal = myProgress->GetPosition() - myStart;

  if (aVal <= 0.)
    return 0.;

  double aDist = myPortion - aVal;
  if (aDist <= math::precision::Precision::Confusion())
    return myIsInfinite ? math::precision::Precision::Infinite() : myMax;

  return std::ceil(myMax * aVal / (myIsInfinite ? aDist : myPortion) - math::precision::Precision::Confusion());
}
