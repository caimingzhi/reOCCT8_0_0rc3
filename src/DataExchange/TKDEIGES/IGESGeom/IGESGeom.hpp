#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class IGESGeom_Protocol;

//! This package consists of B-Rep and CSG Solid entities
class IGESGeom
{
public:
  DEFINE_STANDARD_ALLOC

  //! Prepares dynamic data (Protocol, Modules) for this package
  Standard_EXPORT static void Init();

  //! Returns the Protocol for this Package
  Standard_EXPORT static occ::handle<IGESGeom_Protocol> Protocol();
};

