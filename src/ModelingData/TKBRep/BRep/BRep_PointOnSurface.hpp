#pragma once


#include <Standard.hpp>

#include <Standard_Real.hpp>
#include <BRep_PointsOnSurface.hpp>
class Geom_Surface;
class TopLoc_Location;

//! Representation by two parameters on a surface.
class BRep_PointOnSurface : public BRep_PointsOnSurface
{

public:
  Standard_EXPORT BRep_PointOnSurface(const double                     P1,
                                      const double                     P2,
                                      const occ::handle<Geom_Surface>& S,
                                      const TopLoc_Location&           L);

  Standard_EXPORT bool IsPointOnSurface() const override;

  Standard_EXPORT bool IsPointOnSurface(const occ::handle<Geom_Surface>& S,
                                        const TopLoc_Location&           L) const override;

  Standard_EXPORT double Parameter2() const override;

  Standard_EXPORT void Parameter2(const double P) override;

  DEFINE_STANDARD_RTTIEXT(BRep_PointOnSurface, BRep_PointsOnSurface)

private:
  double myParameter2;
};

