#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class IGESAppli_Protocol;

class IGESAppli
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void Init();

  Standard_EXPORT static occ::handle<IGESAppli_Protocol> Protocol();
};
