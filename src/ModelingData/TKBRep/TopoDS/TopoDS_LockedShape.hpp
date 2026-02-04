#pragma once


#include <Standard_DefineException.hpp>
#include <Standard_SStream.hpp>
#include <Standard_DomainError.hpp>

//! An attempt was made to modify a geometry of Shape already
//! shared or protected.

#if !defined No_Exception && !defined No_TopoDS_LockedShape
  #define TopoDS_LockedShape_Raise_if(CONDITION, MESSAGE)                                          \
    if (CONDITION)                                                                                 \
      throw TopoDS_LockedShape(MESSAGE);
#else
  #define TopoDS_LockedShape_Raise_if(CONDITION, MESSAGE)
#endif

DEFINE_STANDARD_EXCEPTION(TopoDS_LockedShape, Standard_DomainError)

