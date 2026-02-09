#pragma once

#include <gp_Trsf.hpp>
#include <gp_QuaternionNLerp.hpp>
#include <NCollection_Lerp.hpp>
#include <Precision.hpp>

template <>
class NCollection_Lerp<gp_Trsf>
{
public:
  NCollection_Lerp() = default;

  NCollection_Lerp(const gp_Trsf& theStart, const gp_Trsf& theEnd) { Init(theStart, theEnd); }

  void Init(const gp_Trsf& theStart, const gp_Trsf& theEnd)
  {
    myTrsfStart = theStart;
    myTrsfEnd   = theEnd;
    myLocLerp.Init(theStart.TranslationPart(), theEnd.TranslationPart());
    myRotLerp.Init(theStart.GetRotation(), theEnd.GetRotation());
    myScaleLerp.Init(theStart.ScaleFactor(), theEnd.ScaleFactor());
  }

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
