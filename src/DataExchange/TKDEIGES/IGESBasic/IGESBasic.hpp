#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class IGESBasic_Protocol;

//! This package represents basic entities from IGES
class IGESBasic
{
public:
  DEFINE_STANDARD_ALLOC

  //! Prepares dynqmic data (Protocol, Modules) for this package
  Standard_EXPORT static void Init();

  //! Returns the Protocol for this Package
  Standard_EXPORT static occ::handle<IGESBasic_Protocol> Protocol();
};
