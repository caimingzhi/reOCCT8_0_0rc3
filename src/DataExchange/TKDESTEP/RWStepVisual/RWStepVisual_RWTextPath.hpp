#pragma once

#include <StepVisual_TextPath.hpp>
#include <Standard_CString.hpp>

namespace RWStepVisual_RWTextPath
{

  static constexpr char tpUp[]    = ".UP.";
  static constexpr char tpRight[] = ".RIGHT.";
  static constexpr char tpDown[]  = ".DOWN.";
  static constexpr char tpLeft[]  = ".LEFT.";

  //! Convert StepVisual_TextPath to string
  //! @param theSourceEnum The StepVisual_TextPath value to convert
  //! @return The corresponding string representation or nullptr if not found
  inline const char* ConvertToString(const StepVisual_TextPath theSourceEnum)
  {
    switch (theSourceEnum)
    {
      case StepVisual_tpUp:
        return tpUp;
      case StepVisual_tpRight:
        return tpRight;
      case StepVisual_tpDown:
        return tpDown;
      case StepVisual_tpLeft:
        return tpLeft;
    }
    return nullptr;
  }

  //! Convert string to StepVisual_TextPath
  //! @param thePathStr The string to convert
  //! @param theResultEnum The corresponding StepVisual_TextPath value
  //! @return true if the conversion was successful, false otherwise
  inline bool ConvertToEnum(const char* thePathStr, StepVisual_TextPath& theResultEnum)
  {
    if (IsEqual(thePathStr, tpUp))
    {
      theResultEnum = StepVisual_tpUp;
    }
    else if (IsEqual(thePathStr, tpRight))
    {
      theResultEnum = StepVisual_tpRight;
    }
    else if (IsEqual(thePathStr, tpDown))
    {
      theResultEnum = StepVisual_tpDown;
    }
    else if (IsEqual(thePathStr, tpLeft))
    {
      theResultEnum = StepVisual_tpLeft;
    }
    else
    {
      return false;
    }
    return true;
  }
} // namespace RWStepVisual_RWTextPath
