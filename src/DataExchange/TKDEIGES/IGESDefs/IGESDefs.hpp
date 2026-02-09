#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class IGESDefs_Protocol;

class IGESDefs
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void Init();

  Standard_EXPORT static occ::handle<IGESDefs_Protocol> Protocol();
};
