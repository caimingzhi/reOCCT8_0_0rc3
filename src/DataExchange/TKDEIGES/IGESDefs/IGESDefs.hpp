#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class IGESDefs_Protocol;

//! To embody general definitions of Entities
//! (Parameters, Tables ...)
class IGESDefs
{
public:
  DEFINE_STANDARD_ALLOC

  //! Prepares dynamic data (Protocol, Modules) for this package
  Standard_EXPORT static void Init();

  //! Returns the Protocol for this Package
  Standard_EXPORT static occ::handle<IGESDefs_Protocol> Protocol();
};

