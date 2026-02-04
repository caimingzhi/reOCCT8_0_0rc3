#pragma once


#include <Standard_DefineException.hpp>
#include <Standard_SStream.hpp>
#include <Standard_DomainError.hpp>

#if !defined No_Exception && !defined No_BRepExtrema_UnCompatibleShape
  #define BRepExtrema_UnCompatibleShape_Raise_if(CONDITION, MESSAGE)                               \
    if (CONDITION)                                                                                 \
      throw BRepExtrema_UnCompatibleShape(MESSAGE);
#else
  #define BRepExtrema_UnCompatibleShape_Raise_if(CONDITION, MESSAGE)
#endif

DEFINE_STANDARD_EXCEPTION(BRepExtrema_UnCompatibleShape, Standard_DomainError)

