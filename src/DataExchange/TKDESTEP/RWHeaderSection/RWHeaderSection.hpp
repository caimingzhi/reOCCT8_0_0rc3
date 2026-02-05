#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class RWHeaderSection
{
public:
  DEFINE_STANDARD_ALLOC

  //! enforced the initialisation of the libraries
  Standard_EXPORT static void Init();
};
