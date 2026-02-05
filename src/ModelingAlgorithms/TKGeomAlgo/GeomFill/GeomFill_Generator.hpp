#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GeomFill_Profiler.hpp>
class Geom_Surface;

//! Create a surface using generating lines. Inherits
//! profiler. The surface will be a BSplineSurface
//! passing by all the curves described in the
//! generator. The VDegree of the resulting surface is
//! 1.
class GeomFill_Generator : public GeomFill_Profiler
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomFill_Generator();

  //! Converts all curves to BSplineCurves.
  //! Set them to the common profile.
  //! Compute the surface (degv = 1).
  //! <PTol> is used to compare 2 knots.
  Standard_EXPORT void Perform(const double PTol) override;

  const occ::handle<Geom_Surface>& Surface() const;

private:
  occ::handle<Geom_Surface> mySurface;
};

inline const occ::handle<Geom_Surface>& GeomFill_Generator::Surface() const
{
  return mySurface;
}
