#include <Geom_SphericalSurface.hpp>
#include <GeomToStep_MakeAxis2Placement3d.hpp>
#include <GeomToStep_MakeSphericalSurface.hpp>
#include <StdFail_NotDone.hpp>
#include <StepData_Factors.hpp>
#include <StepGeom_Axis2Placement3d.hpp>
#include <StepGeom_SphericalSurface.hpp>
#include <TCollection_HAsciiString.hpp>

GeomToStep_MakeSphericalSurface::GeomToStep_MakeSphericalSurface(
  const occ::handle<Geom_SphericalSurface>& S,
  const StepData_Factors&                   theLocalFactors)
{
  occ::handle<StepGeom_SphericalSurface> Surf;
  occ::handle<StepGeom_Axis2Placement3d> aPosition;
  double                                 aRadius;

  GeomToStep_MakeAxis2Placement3d MkAxis2(S->Position(), theLocalFactors);
  aPosition                                  = MkAxis2.Value();
  aRadius                                    = S->Radius();
  Surf                                       = new StepGeom_SphericalSurface;
  occ::handle<TCollection_HAsciiString> name = new TCollection_HAsciiString("");
  Surf->Init(name, aPosition, aRadius / theLocalFactors.LengthFactor());
  theSphericalSurface = Surf;
  done                = true;
}

const occ::handle<StepGeom_SphericalSurface>& GeomToStep_MakeSphericalSurface::Value() const
{
  StdFail_NotDone_Raise_if(!done, "GeomToStep_MakeSphericalSurface::Value() - no result");
  return theSphericalSurface;
}
