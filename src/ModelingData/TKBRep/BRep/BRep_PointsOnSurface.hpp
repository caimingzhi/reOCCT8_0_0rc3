#pragma once

#include <Standard.hpp>

#include <BRep_PointRepresentation.hpp>
#include <Standard_Real.hpp>
class Geom_Surface;
class TopLoc_Location;

//! Root for points on surface.
class BRep_PointsOnSurface : public BRep_PointRepresentation
{

public:
  Standard_EXPORT const occ::handle<Geom_Surface>& Surface() const override;

  Standard_EXPORT void Surface(const occ::handle<Geom_Surface>& S) override;

  //! Dumps the content of me into the stream
  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(BRep_PointsOnSurface, BRep_PointRepresentation)

protected:
  Standard_EXPORT BRep_PointsOnSurface(const double                     P,
                                       const occ::handle<Geom_Surface>& S,
                                       const TopLoc_Location&           L);

private:
  occ::handle<Geom_Surface> mySurface;
};
