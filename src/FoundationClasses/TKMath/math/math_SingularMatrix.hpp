#pragma once


#include <Standard_DefineException.hpp>
#include <Standard_SStream.hpp>
#include <Standard_Failure.hpp>

class math_SingularMatrix;
DEFINE_STANDARD_HANDLE(math_SingularMatrix, Standard_Failure)

#if !defined No_Exception && !defined No_math_SingularMatrix
  #define math_SingularMatrix_Raise_if(CONDITION, MESSAGE)                                         \
    if (CONDITION)                                                                                 \
      throw math_SingularMatrix(MESSAGE);
#else
  #define math_SingularMatrix_Raise_if(CONDITION, MESSAGE)
#endif

DEFINE_STANDARD_EXCEPTION(math_SingularMatrix, Standard_Failure)

