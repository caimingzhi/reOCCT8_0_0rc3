#pragma once

#include <gp_Quaternion.hpp>

//! Perform Spherical Linear Interpolation of the quaternions,
//! return unit length quaternion.
class gp_QuaternionSLerp
{
public:
  //! Compute interpolated quaternion between two quaternions.
  //! @param theStart first  quaternion
  //! @param theEnd   second quaternion
  //! @param theT normalized interpolation coefficient within 0..1 range,
  //!             with 0 pointing to theStart and 1 to theEnd.
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
  //! Empty constructor,
  gp_QuaternionSLerp() = default;

  //! Constructor with initialization.
  gp_QuaternionSLerp(const gp_Quaternion& theQStart, const gp_Quaternion& theQEnd)
  {
    Init(theQStart, theQEnd);
  }

  //! Initialize the tool with Start and End values.
  void Init(const gp_Quaternion& theQStart, const gp_Quaternion& theQEnd)
  {
    InitFromUnit(theQStart.Normalized(), theQEnd.Normalized());
  }

  //! Initialize the tool with Start and End unit quaternions.
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

  //! Set interpolated quaternion for theT position (from 0.0 to 1.0)
  void Interpolate(double theT, gp_Quaternion& theResultQ) const
  {
    theResultQ = myQStart * std::sin((1.0 - theT) * myOmega) + myQEnd * std::sin(theT * myOmega);
  }

private:
  gp_Quaternion myQStart;
  gp_Quaternion myQEnd;
  double        myOmega;
};
