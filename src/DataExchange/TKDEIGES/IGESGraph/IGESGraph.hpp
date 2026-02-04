#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class IGESGraph_Protocol;

//! This package contains the group of classes necessary
//! to define Graphic data among Structure Entities.
//! (e.g., Fonts, Colors, Screen management ...)
class IGESGraph
{
public:
  DEFINE_STANDARD_ALLOC

  //! Prepares dynamic data (Protocol, Modules) for this package
  Standard_EXPORT static void Init();

  //! Returns the Protocol for this Package
  Standard_EXPORT static occ::handle<IGESGraph_Protocol> Protocol();
};

