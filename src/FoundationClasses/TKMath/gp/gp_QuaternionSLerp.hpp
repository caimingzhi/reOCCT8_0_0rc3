#pragma once

#include <gp_Quaternion.hpp>

class gp_QuaternionSLerp
{
public:
  static gp_Quaternion Interpolate(const gp_Quaternion& theQStart,
                                   const gp_Quaternion& theQEnd,
                                   double               theT)
  {
    gp_Quaternion      aResult;
    gp_QuaternionSLerp aLerp(theQStart, theQEnd);
    aLerp.Interpolate(theT, aResult);
    return aResult;
  }

public:
  gp_QuaternionSLerp() = default;

  gp_QuaternionSLerp(const gp_Quaternion& theQStart, const gp_Quaternion& theQEnd)
  {
    Init(theQStart, theQEnd);
  }

  void Init(const gp_Quaternion& theQStart, const gp_Quaternion& theQEnd)
  {
    InitFromUnit(theQStart.Normalized(), theQEnd.Normalized());
  }

  void InitFromUnit(const gp_Quaternion& theQStart, const gp_Quaternion& theQEnd)
  {
    myQStart        = theQStart;
    myQEnd          = theQEnd;
    double cosOmega = myQStart.Dot(myQEnd);
    if (cosOmega < 0.0)
    {
      cosOmega = -cosOmega;
      myQEnd   = -myQEnd;
    }
    if (cosOmega > 0.9999)
    {
      cosOmega = 0.9999;
    }
    myOmega            = std::acos(cosOmega);
    double invSinOmega = (1.0 / std::sin(myOmega));
    myQStart.Scale(invSinOmega);
    myQEnd.Scale(invSinOmega);
  }

  void Interpolate(double theT, gp_Quaternion& theResultQ) const
  {
    theResultQ = myQStart * std::sin((1.0 - theT) * myOmega) + myQEnd * std::sin(theT * myOmega);
  }

private:
  gp_Quaternion myQStart;
  gp_Quaternion myQEnd;
  double        myOmega;
};
