#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class HeaderSection_Protocol;

class HeaderSection
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static occ::handle<HeaderSection_Protocol> Protocol();
};
