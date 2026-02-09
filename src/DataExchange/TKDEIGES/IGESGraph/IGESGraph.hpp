#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class IGESGraph_Protocol;

class IGESGraph
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void Init();

  Standard_EXPORT static occ::handle<IGESGraph_Protocol> Protocol();
};
