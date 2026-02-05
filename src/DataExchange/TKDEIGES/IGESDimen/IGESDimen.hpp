#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class IGESDimen_Protocol;

//! This package represents Entities applied to Dimensions
//! ie. Annotation Entities and attached Properties and
//! Associativities.
class IGESDimen
{
public:
  DEFINE_STANDARD_ALLOC

  //! Prepares dynamic data (Protocol, Modules) for this package
  Standard_EXPORT static void Init();

  //! Returns the Protocol for this Package
  Standard_EXPORT static occ::handle<IGESDimen_Protocol> Protocol();
};
