#pragma once

#include <StepShape_BooleanOperator.hpp>
#include <Standard_CString.hpp>

namespace RWStepShape_RWBooleanOperator
{
  static constexpr char boDifference[]   = ".DIFFERENCE.";
  static constexpr char boIntersection[] = ".INTERSECTION.";
  static constexpr char boUnion[]        = ".UNION.";

  //! Convert StepShape_BooleanOperator to string
  //! @param theSourceEnum The StepShape_BooleanOperator value to convert
  //! @return The corresponding string representation or nullptr if not found
  inline const char* ConvertToString(const StepShape_BooleanOperator theSourceEnum)
  {
    switch (theSourceEnum)
    {
      case StepShape_boDifference:
        return boDifference;
      case StepShape_boIntersection:
        return boIntersection;
      case StepShape_boUnion:
        return boUnion;
    }
    return nullptr;
  }

  //! Convert string to StepShape_BooleanOperator
  //! @param theOperatorStr The string to convert
  //! @param theResultEnum The corresponding StepShape_BooleanOperator value
  //! @return true if the conversion was successful, false otherwise
  inline bool ConvertToEnum(const char* theOperatorStr, StepShape_BooleanOperator& theResultEnum)
  {
    if (IsEqual(theOperatorStr, boDifference))
    {
      theResultEnum = StepShape_boDifference;
    }
    else if (IsEqual(theOperatorStr, boIntersection))
    {
      theResultEnum = StepShape_boIntersection;
    }
    else if (IsEqual(theOperatorStr, boUnion))
    {
      theResultEnum = StepShape_boUnion;
    }
    else
    {
      return false;
    }
    return true;
  }
} // namespace RWStepShape_RWBooleanOperator
