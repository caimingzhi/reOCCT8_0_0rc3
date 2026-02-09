#pragma once

template <class T>
class NCollection_Lerp
{
public:
  static T Interpolate(const T& theStart, const T& theEnd, double theT)
  {
    T                aResult;
    NCollection_Lerp aLerp(theStart, theEnd);
    aLerp.Interpolate(theT, aResult);
    return aResult;
  }

public:
  NCollection_Lerp()
      : myStart(),
        myEnd()
  {
  }

  NCollection_Lerp(const T& theStart, const T& theEnd) { Init(theStart, theEnd); }

  void Init(const T& theStart, const T& theEnd)
  {
    myStart = theStart;
    myEnd   = theEnd;
  }

  void Interpolate(double theT, T& theResult) const
  {
    theResult = (1.0 - theT) * myStart + theT * myEnd;
  }

private:
  T myStart;
  T myEnd;
};
