#pragma once


#include <Standard.hpp>

#include <BRep_PointsOnSurface.hpp>
#include <Standard_Real.hpp>
class Geom2d_Curve;
class Geom_Surface;
class TopLoc_Location;

//! Representation by a parameter on a curve on a
//! surface.
class BRep_PointOnCurveOnSurface : public BRep_PointsOnSurface
{

public:
  Standard_EXPORT BRep_PointOnCurveOnSurface(const double                     P,
                                             const occ::handle<Geom2d_Curve>& C,
                                             const occ::handle<Geom_Surface>& S,
                                             const TopLoc_Location&           L);

  //! Returns True
  Standard_EXPORT bool IsPointOnCurveOnSurface() const override;

  Standard_EXPORT bool IsPointOnCurveOnSurface(const occ::handle<Geom2d_Curve>& PC,
                                               const occ::handle<Geom_Surface>& S,
                                               const TopLoc_Location&           L) const override;

  Standard_EXPORT const occ::handle<Geom2d_Curve>& PCurve() const override;

  Standard_EXPORT void PCurve(const occ::handle<Geom2d_Curve>& C) override;

  //! Dumps the content of me into the stream
  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(BRep_PointOnCurveOnSurface, BRep_PointsOnSurface)

private:
  occ::handle<Geom2d_Curve> myPCurve;
};

