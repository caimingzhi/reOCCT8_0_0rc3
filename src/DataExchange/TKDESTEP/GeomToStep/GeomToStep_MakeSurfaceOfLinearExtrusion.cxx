#include <Geom_SurfaceOfLinearExtrusion.hpp>
#include <GeomToStep_MakeCurve.hpp>
#include <GeomToStep_MakeSurfaceOfLinearExtrusion.hpp>
#include <GeomToStep_MakeVector.hpp>
#include <gp_Vec.hpp>
#include <StdFail_NotDone.hpp>
#include <StepData_Factors.hpp>
#include <StepGeom_Curve.hpp>
#include <StepGeom_SurfaceOfLinearExtrusion.hpp>
#include <StepGeom_Vector.hpp>
#include <TCollection_HAsciiString.hpp>

GeomToStep_MakeSurfaceOfLinearExtrusion::GeomToStep_MakeSurfaceOfLinearExtrusion(
  const occ::handle<Geom_SurfaceOfLinearExtrusion>& S,
  const StepData_Factors&                           theLocalFactors)
{
  occ::handle<StepGeom_SurfaceOfLinearExtrusion> Surf;
  occ::handle<StepGeom_Curve>                    aSweptCurve;
  occ::handle<StepGeom_Vector>                   aExtrusionAxis;

  GeomToStep_MakeCurve  MkCurve(S->BasisCurve(), theLocalFactors);
  GeomToStep_MakeVector MkVector(gp_Vec(S->Direction()), theLocalFactors);

  aSweptCurve    = MkCurve.Value();
  aExtrusionAxis = MkVector.Value();

  Surf                                       = new StepGeom_SurfaceOfLinearExtrusion;
  occ::handle<TCollection_HAsciiString> name = new TCollection_HAsciiString("");
  Surf->Init(name, aSweptCurve, aExtrusionAxis);
  theSurfaceOfLinearExtrusion = Surf;
  done                        = true;
}

const occ::handle<StepGeom_SurfaceOfLinearExtrusion>& GeomToStep_MakeSurfaceOfLinearExtrusion::
  Value() const
{
  StdFail_NotDone_Raise_if(!done, "GeomToStep_MakeSurfaceOfLinearExtrusion::Value() - no result");
  return theSurfaceOfLinearExtrusion;
}
