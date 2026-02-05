#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class IGESDraw_Protocol;

//! This package contains the group of classes necessary for
//! Structure Entities implied in Drawings and Structured
//! Graphics (Sets for drawing, Drawings and Views).
class IGESDraw
{
public:
  DEFINE_STANDARD_ALLOC

  //! Prepares dynamic data (Protocol, Modules) for this package
  Standard_EXPORT static void Init();

  //! Returns the Protocol for this Package
  Standard_EXPORT static occ::handle<IGESDraw_Protocol> Protocol();
};
