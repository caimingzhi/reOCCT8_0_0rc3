#pragma once


#include <Standard_DefineException.hpp>
#include <Standard_SStream.hpp>
#include <Standard_DomainError.hpp>

//! An attempt was made to modify a Shape already
//! shared or protected.

#if !defined No_Exception && !defined No_TopoDS_FrozenShape
  #define TopoDS_FrozenShape_Raise_if(CONDITION, MESSAGE)                                          \
    if (CONDITION)                                                                                 \
      throw TopoDS_FrozenShape(MESSAGE);
#else
  #define TopoDS_FrozenShape_Raise_if(CONDITION, MESSAGE)
#endif

DEFINE_STANDARD_EXCEPTION(TopoDS_FrozenShape, Standard_DomainError)

