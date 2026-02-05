#include <Geom_ToroidalSurface.hpp>
#include <GeomToStep_MakeAxis2Placement3d.hpp>
#include <GeomToStep_MakeToroidalSurface.hpp>
#include <StdFail_NotDone.hpp>
#include <StepData_Factors.hpp>
#include <StepGeom_ToroidalSurface.hpp>
#include <TCollection_HAsciiString.hpp>

//=============================================================================
// Creation d' une toroidal_surface de prostep a partir d' une ToroidalSurface
// de Geom
//=============================================================================
GeomToStep_MakeToroidalSurface::GeomToStep_MakeToroidalSurface(
  const occ::handle<Geom_ToroidalSurface>& S,
  const StepData_Factors&                  theLocalFactors)
{
  occ::handle<StepGeom_ToroidalSurface>  Surf;
  occ::handle<StepGeom_Axis2Placement3d> aPosition;
  double                                 aMajorRadius, aMinorRadius;

  GeomToStep_MakeAxis2Placement3d MkAxis2(S->Position(), theLocalFactors);
  aPosition                                  = MkAxis2.Value();
  aMajorRadius                               = S->MajorRadius();
  aMinorRadius                               = S->MinorRadius();
  Surf                                       = new StepGeom_ToroidalSurface;
  occ::handle<TCollection_HAsciiString> name = new TCollection_HAsciiString("");
  double                                fact = theLocalFactors.LengthFactor();
  Surf->Init(name, aPosition, aMajorRadius / fact, aMinorRadius / fact);
  theToroidalSurface = Surf;
  done               = true;
}

//=============================================================================
// renvoi des valeurs
//=============================================================================

const occ::handle<StepGeom_ToroidalSurface>& GeomToStep_MakeToroidalSurface::Value() const
{
  StdFail_NotDone_Raise_if(!done, "GeomToStep_MakeToroidalSurface::Value() - no result");
  return theToroidalSurface;
}
