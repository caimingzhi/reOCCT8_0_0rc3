#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class IGESAppli_Protocol;

//! This package represents collection of miscellaneous
//! entities from IGES
class IGESAppli
{
public:
  DEFINE_STANDARD_ALLOC

  //! Prepares dynamic data (Protocol, Modules) for this package
  Standard_EXPORT static void Init();

  //! Returns the Protocol for this Package
  Standard_EXPORT static occ::handle<IGESAppli_Protocol> Protocol();
};

