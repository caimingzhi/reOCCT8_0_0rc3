#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class Geom_Curve;
class Adaptor3d_Curve;
class Geom_Surface;
class Adaptor3d_Surface;

//! this package contains the geometric definition of
//! curve and surface necessary to use algorithms.
class GeomAdaptor
{
public:
  DEFINE_STANDARD_ALLOC

  //! Inherited from GHCurve. Provides a curve
  //! handled by reference.
  //! Build a Geom_Curve using the information from the
  //! Curve from Adaptor3d
  Standard_EXPORT static occ::handle<Geom_Curve> MakeCurve(const Adaptor3d_Curve& C);

  //! Build a Geom_Surface using the information from the Surface from Adaptor3d
  //! @param theS - Surface adaptor to convert.
  //! @param theTrimFlag - True if perform trim surface values by adaptor and false otherwise.
  Standard_EXPORT static occ::handle<Geom_Surface> MakeSurface(const Adaptor3d_Surface& theS,
                                                               const bool theTrimFlag = true);
};
