#pragma once

#include <Standard_TypeDef.hpp>

class LDOM_CharReference
{
public:
  static char* Decode(char* theSrc, int& theLen);

  static char* Encode(const char* theSrc, int& theLen, const bool isAttribute);

private:
  static int myTab[256];
};
