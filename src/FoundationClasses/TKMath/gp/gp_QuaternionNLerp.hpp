#pragma once

#include <gp_Quaternion.hpp>

//! Class perform linear interpolation (approximate rotation interpolation),
//! result quaternion nonunit, its length lay between. sqrt(2)/2 and 1.0
class gp_QuaternionNLerp
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
    gp_QuaternionNLerp aLerp(theQStart, theQEnd);
    aLerp.Interpolate(theT, aResult);
    return aResult;
  }

public:
  //! Empty constructor,
  gp_QuaternionNLerp() = default;

  //! Constructor with initialization.
  gp_QuaternionNLerp(const gp_Quaternion& theQStart, const gp_Quaternion& theQEnd)
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
    myQStart       = theQStart;
    myQEnd         = theQEnd;
    double anInner = myQStart.Dot(myQEnd);
    if (anInner < 0.0)
    {
      myQEnd = -myQEnd;
    }
    myQEnd -= myQStart;
  }

  //! Set interpolated quaternion for theT position (from 0.0 to 1.0)
  void Interpolate(double theT, gp_Quaternion& theResultQ) const
  {
    theResultQ = myQStart + myQEnd * theT;
  }

private:
  gp_Quaternion myQStart;
  gp_Quaternion myQEnd;
};
