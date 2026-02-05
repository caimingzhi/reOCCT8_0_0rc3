#pragma once

#include <Standard_DefineException.hpp>
#include <Standard_SStream.hpp>
#include <Standard_RangeError.hpp>

#if !defined No_Exception && !defined No_Prs3d_InvalidAngle
  #define Prs3d_InvalidAngle_Raise_if(CONDITION, MESSAGE)                                          \
    if (CONDITION)                                                                                 \
      throw Prs3d_InvalidAngle(MESSAGE);
#else
  #define Prs3d_InvalidAngle_Raise_if(CONDITION, MESSAGE)
#endif

DEFINE_STANDARD_EXCEPTION(Prs3d_InvalidAngle, Standard_RangeError)
