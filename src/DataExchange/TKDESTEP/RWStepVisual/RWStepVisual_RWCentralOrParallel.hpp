#pragma once

#include <StepVisual_CentralOrParallel.hpp>
#include <Standard_CString.hpp>

namespace RWStepVisual_RWCentralOrParallel
{
  static constexpr char copCentral[]  = ".CENTRAL.";
  static constexpr char copParallel[] = ".PARALLEL.";

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
