#pragma once

#include <StepBasic_AheadOrBehind.hpp>
#include <Standard_CString.hpp>

namespace RWStepBasic_RWAheadOrBehind
{
  static constexpr char aobAhead[]  = ".AHEAD.";
  static constexpr char aobExact[]  = ".EXACT.";
  static constexpr char aobBehind[] = ".BEHIND.";

  inline const char* ConvertToString(const StepBasic_AheadOrBehind theSourceEnum)
  {
    switch (theSourceEnum)
    {
      case StepBasic_aobAhead:
        return aobAhead;
      case StepBasic_aobExact:
        return aobExact;
      case StepBasic_aobBehind:
        return aobBehind;
    }
    return nullptr;
  }

  inline bool ConvertToEnum(const char* theAheadOrBehindStr, StepBasic_AheadOrBehind& theResultEnum)
  {
    if (IsEqual(theAheadOrBehindStr, aobAhead))
    {
      theResultEnum = StepBasic_aobAhead;
    }
    else if (IsEqual(theAheadOrBehindStr, aobExact))
    {
      theResultEnum = StepBasic_aobExact;
    }
    else if (IsEqual(theAheadOrBehindStr, aobBehind))
    {
      theResultEnum = StepBasic_aobBehind;
    }
    else
    {
      return false;
    }
    return true;
  }

} // namespace RWStepBasic_RWAheadOrBehind
