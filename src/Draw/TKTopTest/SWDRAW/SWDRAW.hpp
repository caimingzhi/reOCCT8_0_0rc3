#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Draw_Interpretor.hpp>
#include <Standard_CString.hpp>

class SWDRAW
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void Init(Draw_Interpretor& theCommands);

  Standard_EXPORT static const char* GroupName();
};
