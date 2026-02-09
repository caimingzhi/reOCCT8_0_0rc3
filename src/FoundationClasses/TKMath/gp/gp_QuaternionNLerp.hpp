#pragma once

#include <gp_Quaternion.hpp>

class gp_QuaternionNLerp
{
public:
  static gp_Quaternion Interpolate(const gp_Quaternion& theQStart,
                                   const gp_Quaternion& theQEnd,
                                   double               theT)
  {
    gp_Quaternion      aResult;
    gp_QuaternionNLerp aLerp(theQStart, theQEnd);
    aLerp.Interpolate(theT, aResult);
    return aResult;
  }

public:
  gp_QuaternionNLerp() = default;

  gp_QuaternionNLerp(const gp_Quaternion& theQStart, const gp_Quaternion& theQEnd)
  {
    Init(theQStart, theQEnd);
  }

  void Init(const gp_Quaternion& theQStart, const gp_Quaternion& theQEnd)
  {
    InitFromUnit(theQStart.Normalized(), theQEnd.Normalized());
  }

  void InitFromUnit(const gp_Quaternion& theQStart, const gp_Quaternion& theQEnd)
  {
    myQStart       = theQStart;
    myQEnd         = theQEnd;
    double anInner = myQStart.Dot(myQEnd);
    if (anInner < 0.0)
    {
      myQEnd = -myQEnd;
    }
    myQEnd -= myQStart;
  }

  void Interpolate(double theT, gp_Quaternion& theResultQ) const
  {
    theResultQ = myQStart + myQEnd * theT;
  }

private:
  gp_Quaternion myQStart;
  gp_Quaternion myQEnd;
};
