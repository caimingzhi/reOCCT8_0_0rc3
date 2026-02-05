#pragma once

#include <StepGeom_TrimmingPreference.hpp>
#include <Standard_CString.hpp>

namespace RWStepGeom_RWTrimmingPreference
{
  static constexpr char tpParameter[]   = ".PARAMETER.";
  static constexpr char tpUnspecified[] = ".UNSPECIFIED.";
  static constexpr char tpCartesian[]   = ".CARTESIAN.";

  //! Convert StepGeom_TrimmingPreference to string
  //! @param theSourceEnum The StepGeom_TrimmingPreference value to convert
  //! @return The corresponding string representation or nullptr if not found
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

  //! Convert string to StepGeom_TrimmingPreference
  //! @param thePreferenceStr The string to convert
  //! @param theResultEnum The corresponding StepGeom_TrimmingPreference value
  //! @return true if the conversion was successful, false otherwise
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
