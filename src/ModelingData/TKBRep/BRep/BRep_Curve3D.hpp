#pragma once

#include <Standard.hpp>

#include <BRep_GCurve.hpp>
#include <Standard_Real.hpp>
class Geom_Curve;
class TopLoc_Location;
class gp_Pnt;
class BRep_CurveRepresentation;

class BRep_Curve3D : public BRep_GCurve
{

public:
  Standard_EXPORT BRep_Curve3D(const occ::handle<Geom_Curve>& C, const TopLoc_Location& L);

  Standard_EXPORT void D0(const double U, gp_Pnt& P) const override;

  Standard_EXPORT bool IsCurve3D() const override;

  Standard_EXPORT const occ::handle<Geom_Curve>& Curve3D() const override;

  Standard_EXPORT void Curve3D(const occ::handle<Geom_Curve>& C) override;

  Standard_EXPORT occ::handle<BRep_CurveRepresentation> Copy() const override;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(BRep_Curve3D, BRep_GCurve)

private:
  occ::handle<Geom_Curve> myCurve;
};
