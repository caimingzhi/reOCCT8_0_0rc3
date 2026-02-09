#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class IGESDraw_Protocol;

class IGESDraw
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void Init();

  Standard_EXPORT static occ::handle<IGESDraw_Protocol> Protocol();
};
