#pragma once

#include <Standard.hpp>

#include <BRep_GCurve.hpp>
#include <Standard_Real.hpp>
class Geom_Curve;
class TopLoc_Location;
class gp_Pnt;
class BRep_CurveRepresentation;

//! Representation of a curve by a 3D curve.
class BRep_Curve3D : public BRep_GCurve
{

public:
  Standard_EXPORT BRep_Curve3D(const occ::handle<Geom_Curve>& C, const TopLoc_Location& L);

  //! Computes the point at parameter U.
  Standard_EXPORT void D0(const double U, gp_Pnt& P) const override;

  //! Returns True.
  Standard_EXPORT bool IsCurve3D() const override;

  Standard_EXPORT const occ::handle<Geom_Curve>& Curve3D() const override;

  Standard_EXPORT void Curve3D(const occ::handle<Geom_Curve>& C) override;

  //! Return a copy of this representation.
  Standard_EXPORT occ::handle<BRep_CurveRepresentation> Copy() const override;

  //! Dumps the content of me into the stream
  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(BRep_Curve3D, BRep_GCurve)

private:
  occ::handle<Geom_Curve> myCurve;
};
