#pragma once

#include <Standard_TypeDef.hpp>

namespace System { namespace log {
class Message_ProgressScope;
}} // namespace System::log


namespace System { namespace log {
class Message_ProgressRange
{
public:
  Message_ProgressRange()
      : myParentScope(nullptr),
        myStart(0.),
        myDelta(0.),
        myWasUsed(false)
  {
  }

  Message_ProgressRange(const Message_ProgressRange& theOther)
      : myParentScope(theOther.myParentScope),
        myStart(theOther.myStart),
        myDelta(theOther.myDelta),
        myWasUsed(theOther.myWasUsed)
  {

    theOther.myWasUsed = true;
  }

  Message_ProgressRange& operator=(const Message_ProgressRange& theOther)
  {
    myParentScope      = theOther.myParentScope;
    myStart            = theOther.myStart;
    myDelta            = theOther.myDelta;
    myWasUsed          = theOther.myWasUsed;
    theOther.myWasUsed = true;
    return *this;
  }

  bool UserBreak() const;

  bool More() const { return !UserBreak(); }

  bool IsActive() const;

  void Close();

  ~Message_ProgressRange() { Close(); }

private:
  Message_ProgressRange(const Message_ProgressScope& theParent, double theStart, double theDelta)
      : myParentScope(&theParent),
        myStart(theStart),
        myDelta(theDelta),
        myWasUsed(false)
  {
  }

private:
  const Message_ProgressScope* myParentScope;
  double                       myStart;
  double                       myDelta;

  mutable bool myWasUsed;

  friend class Message_ProgressScope;
};
}} // namespace System::log


#include <Message_ProgressIndicator.hpp>

inline bool System::log::Message_ProgressRange::IsActive() const
{
  return !myWasUsed && myParentScope && myParentScope->myProgress;
}

inline bool System::log::Message_ProgressRange::UserBreak() const
{
  return myParentScope && myParentScope->myProgress && myParentScope->myProgress->UserBreak();
}

inline void System::log::Message_ProgressRange::Close()
{
  if (!IsActive())
    return;

  myParentScope->myProgress->Increment(myDelta, *myParentScope);
  myParentScope = nullptr;
  myWasUsed     = true;
}
