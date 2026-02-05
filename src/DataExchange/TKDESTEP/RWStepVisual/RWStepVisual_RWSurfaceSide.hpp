#pragma once

#include <StepVisual_SurfaceSide.hpp>
#include <Standard_CString.hpp>

namespace RWStepVisual_RWSurfaceSide
{
  static constexpr char ssNegative[] = ".NEGATIVE.";
  static constexpr char ssPositive[] = ".POSITIVE.";
  static constexpr char ssBoth[]     = ".BOTH.";

  //! Convert StepVisual_SurfaceSide to string
  //! @param theSourceEnum The StepVisual_SurfaceSide value to convert
  //! @return The corresponding string representation or nullptr if not found
  inline const char* ConvertToString(const StepVisual_SurfaceSide theSourceEnum)
  {
    switch (theSourceEnum)
    {
      case StepVisual_ssNegative:
        return ssNegative;
      case StepVisual_ssPositive:
        return ssPositive;
      case StepVisual_ssBoth:
        return ssBoth;
    }
    return nullptr;
  }

  //! Convert string to StepVisual_SurfaceSide
  //! @param theSideStr The string to convert
  //! @param theResultEnum The corresponding StepVisual_SurfaceSide value
  //! @return true if the conversion was successful, false otherwise
  inline bool ConvertToEnum(const char* theSideStr, StepVisual_SurfaceSide& theResultEnum)
  {
    if (IsEqual(theSideStr, ssNegative))
    {
      theResultEnum = StepVisual_ssNegative;
    }
    else if (IsEqual(theSideStr, ssPositive))
    {
      theResultEnum = StepVisual_ssPositive;
    }
    else if (IsEqual(theSideStr, ssBoth))
    {
      theResultEnum = StepVisual_ssBoth;
    }
    else
    {
      return false;
    }
    return true;
  }
} // namespace RWStepVisual_RWSurfaceSide
