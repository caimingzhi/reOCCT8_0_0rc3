#pragma once

#include <Message_ProgressScope.hpp>

class Message_LazyProgressScope : protected Message_ProgressScope
{
public:
  Message_LazyProgressScope(const Message_ProgressRange& theRange,
                            const char*                  theName,
                            const double                 theMax,
                            const double                 thePatchStep,
                            const bool                   theIsInf = false)
      : Message_ProgressScope(theRange, theName, theMax, theIsInf),
        myPatchStep(thePatchStep),
        myPatchProgress(0.0),
        myIsLazyAborted(false)
  {
  }

  void Next()
  {
    if (++myPatchProgress < myPatchStep)
    {
      return;
    }

    myPatchProgress = 0.0;
    Message_ProgressScope::Next(myPatchStep);
    IsAborted();
  }

  bool More() const { return !myIsLazyAborted; }

  bool IsAborted()
  {
    myIsLazyAborted = myIsLazyAborted || !Message_ProgressScope::More();
    return myIsLazyAborted;
  }

protected:
  double myPatchStep;
  double myPatchProgress;
  bool   myIsLazyAborted;
};
