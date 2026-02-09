#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Real.hpp>
#include <Standard_Boolean.hpp>
class Geom_Surface;

class ShapeCustom_Surface
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT ShapeCustom_Surface();

  Standard_EXPORT ShapeCustom_Surface(const occ::handle<Geom_Surface>& S);

  Standard_EXPORT void Init(const occ::handle<Geom_Surface>& S);

  double Gap() const;

  Standard_EXPORT occ::handle<Geom_Surface> ConvertToAnalytical(const double tol,
                                                                const bool   substitute);

  Standard_EXPORT occ::handle<Geom_Surface> ConvertToPeriodic(const bool   substitute,
                                                              const double preci = -1);

private:
  occ::handle<Geom_Surface> mySurf;
  double                    myGap;
};

inline double ShapeCustom_Surface::Gap() const
{
  return myGap;
}
