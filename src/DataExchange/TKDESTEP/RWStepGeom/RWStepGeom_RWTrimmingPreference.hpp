#pragma once

#include <StepGeom_TrimmingPreference.hpp>
#include <Standard_CString.hpp>

namespace RWStepGeom_RWTrimmingPreference
{
  static constexpr char tpParameter[]   = ".PARAMETER.";
  static constexpr char tpUnspecified[] = ".UNSPECIFIED.";
  static constexpr char tpCartesian[]   = ".CARTESIAN.";

  inline const char* ConvertToString(const StepGeom_TrimmingPreference theSourceEnum)
  {
    switch (theSourceEnum)
    {
      case StepGeom_tpParameter:
        return tpParameter;
      case StepGeom_tpUnspecified:
        return tpUnspecified;
      case StepGeom_tpCartesian:
        return tpCartesian;
    }
    return nullptr;
  }

  inline bool ConvertToEnum(const char*                  thePreferenceStr,
                            StepGeom_TrimmingPreference& theResultEnum)
  {
    if (IsEqual(thePreferenceStr, tpParameter))
    {
      theResultEnum = StepGeom_tpParameter;
    }
    else if (IsEqual(thePreferenceStr, tpUnspecified))
    {
      theResultEnum = StepGeom_tpUnspecified;
    }
    else if (IsEqual(thePreferenceStr, tpCartesian))
    {
      theResultEnum = StepGeom_tpCartesian;
    }
    else
    {
      return false;
    }
    return true;
  }
} // namespace RWStepGeom_RWTrimmingPreference
