#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Draw_Interpretor.hpp>

class TObjDRAW
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void Init(Draw_Interpretor& di);

  Standard_EXPORT static void Factory(Draw_Interpretor& theDI);
};
