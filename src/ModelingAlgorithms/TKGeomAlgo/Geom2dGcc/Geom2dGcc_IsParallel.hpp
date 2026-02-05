#pragma once

#include <Standard_SStream.hpp>
#include <Standard_DomainError.hpp>

#if !defined No_Exception && !defined No_Geom2dGcc_IsParallel
  #define Geom2dGcc_IsParallel_Raise_if(CONDITION, MESSAGE)                                        \
    if (CONDITION)                                                                                 \
      throw Geom2dGcc_IsParallel(MESSAGE);
#else
  #define Geom2dGcc_IsParallel_Raise_if(CONDITION, MESSAGE)
#endif

DEFINE_STANDARD_EXCEPTION(Geom2dGcc_IsParallel, Standard_DomainError)
