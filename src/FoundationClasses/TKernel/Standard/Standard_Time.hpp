#pragma once


#include <Standard_TypeDef.hpp>

// ------------------------------------------------------------------
// IsEqual : Returns true if two time values are equal
// ------------------------------------------------------------------
template <typename TheTimeType>
typename opencascade::std::enable_if<opencascade::std::is_same<TheTimeType, std::time_t>::value
                                       && !opencascade::std::is_same<size_t, std::time_t>::value
                                       && !opencascade::std::is_same<int, std::time_t>::value,
                                     bool>::type
  IsEqual(const TheTimeType theOne, const TheTimeType theTwo)
{
  return theOne == theTwo;
}

