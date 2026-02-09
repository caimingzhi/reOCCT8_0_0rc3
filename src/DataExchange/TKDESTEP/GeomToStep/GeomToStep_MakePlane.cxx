#include <Geom_Plane.hpp>
#include <GeomToStep_MakeAxis2Placement3d.hpp>
#include <GeomToStep_MakePlane.hpp>
#include <gp_Pln.hpp>
#include <StdFail_NotDone.hpp>
#include <StepGeom_Axis2Placement3d.hpp>
#include <StepGeom_Plane.hpp>
#include <TCollection_HAsciiString.hpp>

GeomToStep_MakePlane::GeomToStep_MakePlane(const gp_Pln& P, const StepData_Factors& theLocalFactors)
{
  occ::handle<StepGeom_Plane>            Plan = new StepGeom_Plane;
  occ::handle<StepGeom_Axis2Placement3d> aPosition;

  GeomToStep_MakeAxis2Placement3d MkAxis2(P.Position(), theLocalFactors);
  aPosition = MkAxis2.Value();
  Plan->SetPosition(aPosition);
  occ::handle<TCollection_HAsciiString> name = new TCollection_HAsciiString("");
  Plan->SetName(name);
  thePlane = Plan;
  done     = true;
}

GeomToStep_MakePlane::GeomToStep_MakePlane(const occ::handle<Geom_Plane>& Gpln,
                                           const StepData_Factors&        theLocalFactors)
{
  gp_Pln                                 P;
  occ::handle<StepGeom_Plane>            Plan = new StepGeom_Plane;
  occ::handle<StepGeom_Axis2Placement3d> aPosition;

  P = Gpln->Pln();

  GeomToStep_MakeAxis2Placement3d MkAxis2(P.Position(), theLocalFactors);
  aPosition = MkAxis2.Value();
  Plan->SetPosition(aPosition);
  occ::handle<TCollection_HAsciiString> name = new TCollection_HAsciiString("");
  Plan->SetName(name);
  thePlane = Plan;
  done     = true;
}

const occ::handle<StepGeom_Plane>& GeomToStep_MakePlane::Value() const
{
  StdFail_NotDone_Raise_if(!done, "GeomToStep_MakePlane::Value() - no result");
  return thePlane;
}
