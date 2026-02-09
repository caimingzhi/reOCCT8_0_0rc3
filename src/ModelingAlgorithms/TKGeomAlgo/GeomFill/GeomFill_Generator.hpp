#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GeomFill_Profiler.hpp>
class Geom_Surface;

class GeomFill_Generator : public GeomFill_Profiler
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomFill_Generator();

  Standard_EXPORT void Perform(const double PTol) override;

  const occ::handle<Geom_Surface>& Surface() const;

private:
  occ::handle<Geom_Surface> mySurface;
};

inline const occ::handle<Geom_Surface>& GeomFill_Generator::Surface() const
{
  return mySurface;
}
