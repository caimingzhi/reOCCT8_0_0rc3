#include <Geom_SurfaceOfLinearExtrusion.hpp>
#include <Geom_SurfaceOfRevolution.hpp>
#include <Geom_SweptSurface.hpp>
#include <GeomToStep_MakeSurfaceOfLinearExtrusion.hpp>
#include <GeomToStep_MakeSurfaceOfRevolution.hpp>
#include <GeomToStep_MakeSweptSurface.hpp>
#include <StdFail_NotDone.hpp>
#include <StepData_Factors.hpp>
#include <StepGeom_SurfaceOfLinearExtrusion.hpp>
#include <StepGeom_SurfaceOfRevolution.hpp>
#include <StepGeom_SweptSurface.hpp>
#include <TCollection_HAsciiString.hpp>

GeomToStep_MakeSweptSurface::GeomToStep_MakeSweptSurface(const occ::handle<Geom_SweptSurface>& S,
                                                         const StepData_Factors& theLocalFactors)
{
  done = true;
  if (S->IsKind(STANDARD_TYPE(Geom_SurfaceOfLinearExtrusion)))
  {
    occ::handle<Geom_SurfaceOfLinearExtrusion> Sur =
      occ::down_cast<Geom_SurfaceOfLinearExtrusion>(S);
    GeomToStep_MakeSurfaceOfLinearExtrusion MkLinear(Sur, theLocalFactors);
    theSweptSurface = MkLinear.Value();
  }
  else if (S->IsKind(STANDARD_TYPE(Geom_SurfaceOfRevolution)))
  {
    occ::handle<Geom_SurfaceOfRevolution> Sur = occ::down_cast<Geom_SurfaceOfRevolution>(S);
    GeomToStep_MakeSurfaceOfRevolution    MkRevol(Sur, theLocalFactors);
    theSweptSurface = MkRevol.Value();
  }
  else
    done = false;
}

const occ::handle<StepGeom_SweptSurface>& GeomToStep_MakeSweptSurface::Value() const
{
  StdFail_NotDone_Raise_if(!done, "GeomToStep_MakeSweptSurface::Value() - no result");
  return theSweptSurface;
}
