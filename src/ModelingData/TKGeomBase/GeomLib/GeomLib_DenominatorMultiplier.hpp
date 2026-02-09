#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <NCollection_Array1.hpp>
#include <Standard_Real.hpp>
class Geom_BSplineSurface;

class GeomLib_DenominatorMultiplier
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomLib_DenominatorMultiplier(const occ::handle<Geom_BSplineSurface>& Surface,
                                                const NCollection_Array1<double>&       KnotVector);

  Standard_EXPORT double Value(const double UParameter, const double VParameter) const;

private:
  occ::handle<Geom_BSplineSurface> mySurface;
  NCollection_Array1<double>       myKnotFlatVector;
};
