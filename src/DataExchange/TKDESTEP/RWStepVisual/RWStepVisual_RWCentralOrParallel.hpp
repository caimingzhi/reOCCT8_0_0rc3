#pragma once

#include <StepVisual_CentralOrParallel.hpp>
#include <Standard_CString.hpp>

namespace RWStepVisual_RWCentralOrParallel
{
  static constexpr char copCentral[]  = ".CENTRAL.";
  static constexpr char copParallel[] = ".PARALLEL.";

  //! Convert StepVisual_CentralOrParallel to string
  //! @param theSourceEnum The StepVisual_CentralOrParallel value to convert
  //! @return The corresponding string representation or nullptr if not found
  inline const char* ConvertToString(const StepVisual_CentralOrParallel theSourceEnum)
  {
    switch (theSourceEnum)
    {
      case StepVisual_copCentral:
        return copCentral;
      case StepVisual_copParallel:
        return copParallel;
    }
    return nullptr;
  }

  //! Convert string to StepVisual_CentralOrParallel
  //! @param theCentralOrParallelStr The string to convert
  //! @param theResultEnum The corresponding StepVisual_CentralOrParallel value
  //! @return true if the conversion was successful, false otherwise
  inline bool ConvertToEnum(const char*                   theCentralOrParallelStr,
                            StepVisual_CentralOrParallel& theResultEnum)
  {
    if (IsEqual(theCentralOrParallelStr, copCentral))
    {
      theResultEnum = StepVisual_copCentral;
    }
    else if (IsEqual(theCentralOrParallelStr, copParallel))
    {
      theResultEnum = StepVisual_copParallel;
    }
    else
    {
      return false;
    }
    return true;
  }
} // namespace RWStepVisual_RWCentralOrParallel
