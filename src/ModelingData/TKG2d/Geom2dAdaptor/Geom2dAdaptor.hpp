#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class Geom2d_Curve;
class Adaptor2d_Curve2d;

//! this package contains the geometric definition of
//! 2d curves compatible with the Adaptor package
//! templates.
class Geom2dAdaptor
{
public:
  DEFINE_STANDARD_ALLOC

  //! Inherited from GHCurve. Provides a curve
  //! handled by reference.
  //! Creates a 2d curve from a HCurve2d. This
  //! cannot process the OtherCurves.
  Standard_EXPORT static occ::handle<Geom2d_Curve> MakeCurve(const Adaptor2d_Curve2d& HC);
};

