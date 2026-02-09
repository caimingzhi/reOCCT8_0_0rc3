#include <Geom_SurfaceOfRevolution.hpp>
#include <GeomToStep_MakeAxis1Placement.hpp>
#include <GeomToStep_MakeCurve.hpp>
#include <GeomToStep_MakeSurfaceOfRevolution.hpp>
#include <gp_Ax1.hpp>
#include <StdFail_NotDone.hpp>
#include <StepData_Factors.hpp>
#include <StepGeom_Axis1Placement.hpp>
#include <StepGeom_Curve.hpp>
#include <StepGeom_SurfaceOfRevolution.hpp>
#include <TCollection_HAsciiString.hpp>

GeomToStep_MakeSurfaceOfRevolution::GeomToStep_MakeSurfaceOfRevolution(
  const occ::handle<Geom_SurfaceOfRevolution>& S,
  const StepData_Factors&                      theLocalFactors)
{
  occ::handle<StepGeom_SurfaceOfRevolution> Surf;
  occ::handle<StepGeom_Curve>               aSweptCurve;
  occ::handle<StepGeom_Axis1Placement>      aAxisPosition;

  GeomToStep_MakeCurve          MkSwept(S->BasisCurve(), theLocalFactors);
  GeomToStep_MakeAxis1Placement MkAxis1(S->Axis(), theLocalFactors);
  aSweptCurve                                = MkSwept.Value();
  aAxisPosition                              = MkAxis1.Value();
  Surf                                       = new StepGeom_SurfaceOfRevolution;
  occ::handle<TCollection_HAsciiString> name = new TCollection_HAsciiString("");
  Surf->Init(name, aSweptCurve, aAxisPosition);
  theSurfaceOfRevolution = Surf;
  done                   = true;
}

const occ::handle<StepGeom_SurfaceOfRevolution>& GeomToStep_MakeSurfaceOfRevolution::Value() const
{
  StdFail_NotDone_Raise_if(!done, "GeomToStep_MakeSurfaceOfRevolution::Value() - no result");
  return theSurfaceOfRevolution;
}
