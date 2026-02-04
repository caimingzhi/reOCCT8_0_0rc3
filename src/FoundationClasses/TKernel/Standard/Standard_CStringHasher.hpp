#pragma once


#include <Standard_CString.hpp>
#include <Standard_HashUtils.hpp>
#include <Standard_TypeDef.hpp>

class Standard_CStringHasher
{
public:
  size_t operator()(const char* theString) const noexcept
  {
    const int aLen = static_cast<int>(strlen(theString));
    if (aLen < 4)
    {
      return opencascade::FNVHash::hash_combine(*theString, aLen);
    }
    return opencascade::hashBytes(theString, aLen);
  }

  bool operator()(const char* theString1, const char* theString2) const noexcept
  {
    return strcmp(theString1, theString2) == 0;
  }
};

