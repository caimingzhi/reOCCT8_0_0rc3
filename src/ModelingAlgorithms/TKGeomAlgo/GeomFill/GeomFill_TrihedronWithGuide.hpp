#pragma once

#include <Standard.hpp>

#include <GeomFill_TrihedronLaw.hpp>
#include <Standard_Real.hpp>

//! To define Trihedron along one Curve with a guide
class GeomFill_TrihedronWithGuide : public GeomFill_TrihedronLaw
{

public:
  Standard_EXPORT virtual occ::handle<Adaptor3d_Curve> Guide() const = 0;

  Standard_EXPORT virtual void Origine(const double Param1, const double Param2) = 0;

  //! Returns the current point on guide
  //! found by D0, D1 or D2.
  Standard_EXPORT gp_Pnt CurrentPointOnGuide() const;

  DEFINE_STANDARD_RTTIEXT(GeomFill_TrihedronWithGuide, GeomFill_TrihedronLaw)

protected:
  occ::handle<Adaptor3d_Curve> myGuide;
  occ::handle<Adaptor3d_Curve> myTrimG;
  gp_Pnt                       myCurPointOnGuide;
};
