#pragma once

#include <Standard_TypeDef.hpp>

class Message_ProgressScope;

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

#include <Message_ProgressIndicator.hpp>

inline bool Message_ProgressRange::IsActive() const
{
  return !myWasUsed && myParentScope && myParentScope->myProgress;
}

inline bool Message_ProgressRange::UserBreak() const
{
  return myParentScope && myParentScope->myProgress && myParentScope->myProgress->UserBreak();
}

inline void Message_ProgressRange::Close()
{
  if (!IsActive())
    return;

  myParentScope->myProgress->Increment(myDelta, *myParentScope);
  myParentScope = nullptr;
  myWasUsed     = true;
}
