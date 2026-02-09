#pragma once

#include <StepGeom_TransitionCode.hpp>
#include <Standard_CString.hpp>

namespace RWStepGeom_RWTransitionCode
{
  static constexpr char tcDiscontinuous[]                 = ".DISCONTINUOUS.";
  static constexpr char tcContSameGradientSameCurvature[] = ".CONT_SAME_GRADIENT_SAME_CURVATURE.";
  static constexpr char tcContSameGradient[]              = ".CONT_SAME_GRADIENT.";
  static constexpr char tcContinuous[]                    = ".CONTINUOUS.";

  inline const char* ConvertToString(const StepGeom_TransitionCode theTransitionCodeEnum)
  {
    switch (theTransitionCodeEnum)
    {
      case StepGeom_tcDiscontinuous:
        return tcDiscontinuous;
      case StepGeom_tcContSameGradientSameCurvature:
        return tcContSameGradientSameCurvature;
      case StepGeom_tcContSameGradient:
        return tcContSameGradient;
      case StepGeom_tcContinuous:
        return tcContinuous;
    }
    return nullptr;
  }

  inline bool ConvertToEnum(const char*              theTransitionCodeStr,
                            StepGeom_TransitionCode& theResultEnum)
  {
    if (IsEqual(theTransitionCodeStr, tcDiscontinuous))
    {
      theResultEnum = StepGeom_tcDiscontinuous;
    }
    else if (IsEqual(theTransitionCodeStr, tcContSameGradientSameCurvature))
    {
      theResultEnum = StepGeom_tcContSameGradientSameCurvature;
    }
    else if (IsEqual(theTransitionCodeStr, tcContSameGradient))
    {
      theResultEnum = StepGeom_tcContSameGradient;
    }
    else if (IsEqual(theTransitionCodeStr, tcContinuous))
    {
      theResultEnum = StepGeom_tcContinuous;
    }
    else
    {
      return false;
    }
    return true;
  }
} // namespace RWStepGeom_RWTransitionCode
