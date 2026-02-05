#include <Geom_ConicalSurface.hpp>
#include <GeomToStep_MakeAxis2Placement3d.hpp>
#include <GeomToStep_MakeConicalSurface.hpp>
#include <Standard_DomainError.hpp>
#include <StdFail_NotDone.hpp>
#include <StepData_Factors.hpp>
#include <StepGeom_Axis2Placement3d.hpp>
#include <StepGeom_ConicalSurface.hpp>
#include <TCollection_HAsciiString.hpp>

//=============================================================================
// Creation d' une conical_surface de prostep a partir d' une ConicalSurface
// de Geom
//=============================================================================
GeomToStep_MakeConicalSurface::GeomToStep_MakeConicalSurface(
  const occ::handle<Geom_ConicalSurface>& CS,
  const StepData_Factors&                 theLocalFactors)

{
  occ::handle<StepGeom_ConicalSurface>   CSstep = new StepGeom_ConicalSurface;
  occ::handle<StepGeom_Axis2Placement3d> aPosition;
  double                                 aRadius, aSemiAngle;

  GeomToStep_MakeAxis2Placement3d MkAxis(CS->Position(), theLocalFactors);
  aPosition  = MkAxis.Value();
  aRadius    = CS->RefRadius();
  aSemiAngle = CS->SemiAngle();
  if (aSemiAngle < 0. || aSemiAngle > M_PI / 2.)
  {
    throw Standard_DomainError("Conicalsurface not STEP conformant");
  }

  occ::handle<TCollection_HAsciiString> name = new TCollection_HAsciiString("");
  CSstep->Init(name, aPosition, aRadius / theLocalFactors.LengthFactor(), aSemiAngle);
  theConicalSurface = CSstep;
  done              = true;
}

//=============================================================================
// renvoi des valeurs
//=============================================================================

const occ::handle<StepGeom_ConicalSurface>& GeomToStep_MakeConicalSurface::Value() const
{
  StdFail_NotDone_Raise_if(!done, "GeomToStep_MakeConicalSurface::Value() - no result");
  return theConicalSurface;
}
