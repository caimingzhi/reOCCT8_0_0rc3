#pragma once

#include <Draw_Interpretor.hpp>

class D3DHostTest
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void Commands(Draw_Interpretor& theDI);

  Standard_EXPORT static void Factory(Draw_Interpretor& theDI);
};
