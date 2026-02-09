#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Draw_Interpretor.hpp>

class XDEDRAW
{
  DEFINE_STANDARD_ALLOC
public:
  Standard_EXPORT static void Init(Draw_Interpretor& di);

  Standard_EXPORT static void Factory(Draw_Interpretor& theDI);
};
