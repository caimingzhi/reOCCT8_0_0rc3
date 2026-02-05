#pragma once

#include <Standard_DefineException.hpp>
#include <Standard_SStream.hpp>
#include <Standard_DomainError.hpp>

//! An incorrect insertion was attempted.

#if !defined No_Exception && !defined No_TopoDS_UnCompatibleShapes
  #define TopoDS_UnCompatibleShapes_Raise_if(CONDITION, MESSAGE)                                   \
    if (CONDITION)                                                                                 \
      throw TopoDS_UnCompatibleShapes(MESSAGE);
#else
  #define TopoDS_UnCompatibleShapes_Raise_if(CONDITION, MESSAGE)
#endif

DEFINE_STANDARD_EXCEPTION(TopoDS_UnCompatibleShapes, Standard_DomainError)
