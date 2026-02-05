#pragma once

#include <gp_Trsf.hpp>
#include <gp_QuaternionNLerp.hpp>
#include <NCollection_Lerp.hpp>
#include <Precision.hpp>

//! Linear interpolation tool for transformation defined by gp_Trsf.
//!
//! In general case, there is a no well-defined interpolation between arbitrary transformations,
//! because desired transient values might vary depending on application needs.
//!
//! This tool performs independent interpolation of three logical
//! transformation parts - rotation (using gp_QuaternionNLerp), translation and scale factor.
//! Result of such interpolation might be not what application expects,
//! thus this tool might be considered for simple cases or for interpolating between small
//! intervals.
template <>
class NCollection_Lerp<gp_Trsf>
{
public:
  //! Empty constructor
  NCollection_Lerp() = default;

  //! Main constructor.
  NCollection_Lerp(const gp_Trsf& theStart, const gp_Trsf& theEnd) { Init(theStart, theEnd); }

  //! Initialize values.
  void Init(const gp_Trsf& theStart, const gp_Trsf& theEnd)
  {
    myTrsfStart = theStart;
    myTrsfEnd   = theEnd;
    myLocLerp.Init(theStart.TranslationPart(), theEnd.TranslationPart());
    myRotLerp.Init(theStart.GetRotation(), theEnd.GetRotation());
    myScaleLerp.Init(theStart.ScaleFactor(), theEnd.ScaleFactor());
  }

  //! Compute interpolated value between two values.
  //! @param theT normalized interpolation coefficient within [0, 1] range,
  //!             with 0 pointing to first value and 1 to the second value.
  //! @param[out] theResult  interpolated value
  void Interpolate(double theT, gp_Trsf& theResult) const
  {
    if (std::abs(theT - 0.0) < Precision::Confusion())
    {
      theResult = myTrsfStart;
      return;
    }
    else if (std::abs(theT - 1.0) < Precision::Confusion())
    {
      theResult = myTrsfEnd;
      return;
    }

    gp_XYZ        aLoc;
    gp_Quaternion aRot;
    double        aScale = 1.0;
    myLocLerp.Interpolate(theT, aLoc);
    myRotLerp.Interpolate(theT, aRot);
    myScaleLerp.Interpolate(theT, aScale);
    theResult = gp_Trsf();
    theResult.SetRotation(aRot);
    theResult.SetTranslationPart(aLoc);
    theResult.SetScaleFactor(aScale);
  }

private:
  NCollection_Lerp<gp_XYZ> myLocLerp;
  NCollection_Lerp<double> myScaleLerp;
  gp_QuaternionNLerp       myRotLerp;
  gp_Trsf                  myTrsfStart;
  gp_Trsf                  myTrsfEnd;
};
