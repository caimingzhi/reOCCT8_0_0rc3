#include <Geom_CylindricalSurface.hpp>
#include <GeomToStep_MakeAxis2Placement3d.hpp>
#include <GeomToStep_MakeCylindricalSurface.hpp>
#include <StdFail_NotDone.hpp>
#include <StepData_Factors.hpp>
#include <StepGeom_Axis2Placement3d.hpp>
#include <StepGeom_CylindricalSurface.hpp>
#include <TCollection_HAsciiString.hpp>

//=============================================================================
// Creation d' une conical_surface de prostep a partir d' une
// CylindricalSurface de Geom
//=============================================================================
GeomToStep_MakeCylindricalSurface::GeomToStep_MakeCylindricalSurface(
  const occ::handle<Geom_CylindricalSurface>& CS,
  const StepData_Factors&                     theLocalFactors)
{
  occ::handle<StepGeom_CylindricalSurface> CSstep;
  occ::handle<StepGeom_Axis2Placement3d>   aPosition;
  double                                   aRadius;

  GeomToStep_MakeAxis2Placement3d MkAxis2(CS->Position(), theLocalFactors);
  aPosition                                  = MkAxis2.Value();
  aRadius                                    = CS->Radius();
  CSstep                                     = new StepGeom_CylindricalSurface;
  occ::handle<TCollection_HAsciiString> name = new TCollection_HAsciiString("");
  CSstep->Init(name, aPosition, aRadius / theLocalFactors.LengthFactor());
  theCylindricalSurface = CSstep;
  done                  = true;
}

//=============================================================================
// renvoi des valeurs
//=============================================================================

const occ::handle<StepGeom_CylindricalSurface>& GeomToStep_MakeCylindricalSurface::Value() const
{
  StdFail_NotDone_Raise_if(!done, "GeomToStep_MakeCylindricalSurface::Value() - no result");
  return theCylindricalSurface;
}
