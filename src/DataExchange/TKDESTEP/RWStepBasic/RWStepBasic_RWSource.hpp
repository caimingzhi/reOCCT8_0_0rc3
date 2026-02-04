#pragma once


#include <StepBasic_Source.hpp>
#include <Standard_CString.hpp>

namespace RWStepBasic_RWSource
{
static constexpr char sBought[]   = ".BOUGHT.";
static constexpr char sNotKnown[] = ".NOT_KNOWN.";
static constexpr char sMade[]     = ".MADE.";

//! Convert StepBasic_Source to string
//! @param theSourceEnum The StepBasic_Source value to convert
//! @return The corresponding string representation or nullptr if not found
inline const char* ConvertToString(const StepBasic_Source theSourceEnum)
{
  switch (theSourceEnum)
  {
    case StepBasic_sBought:
      return sBought;
    case StepBasic_sNotKnown:
      return sNotKnown;
    case StepBasic_sMade:
      return sMade;
  }
  return nullptr;
}

//! Convert string to StepBasic_Source
//! @param theSourceStr The string to convert
//! @param theResultEnum The corresponding StepBasic_Source value
//! @return true if the conversion was successful, false otherwise
inline bool ConvertToEnum(const char* theSourceStr, StepBasic_Source& theResultEnum)
{
  if (IsEqual(theSourceStr, sBought))
  {
    theResultEnum = StepBasic_sBought;
  }
  else if (IsEqual(theSourceStr, sNotKnown))
  {
    theResultEnum = StepBasic_sNotKnown;
  }
  else if (IsEqual(theSourceStr, sMade))
  {
    theResultEnum = StepBasic_sMade;
  }
  else
  {
    return false;
  }
  return true;
}
} // namespace RWStepBasic_RWSource

