#pragma once

#include <Standard.hpp>

#include <BRep_PointRepresentation.hpp>
#include <Standard_Real.hpp>
class Geom_Curve;
class TopLoc_Location;

class BRep_PointOnCurve : public BRep_PointRepresentation
{

public:
  Standard_EXPORT BRep_PointOnCurve(const double                   P,
                                    const occ::handle<Geom_Curve>& C,
                                    const TopLoc_Location&         L);

  Standard_EXPORT bool IsPointOnCurve() const override;

  Standard_EXPORT bool IsPointOnCurve(const occ::handle<Geom_Curve>& C,
                                      const TopLoc_Location&         L) const override;

  Standard_EXPORT const occ::handle<Geom_Curve>& Curve() const override;

  Standard_EXPORT void Curve(const occ::handle<Geom_Curve>& C) override;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(BRep_PointOnCurve, BRep_PointRepresentation)

private:
  occ::handle<Geom_Curve> myCurve;
};
