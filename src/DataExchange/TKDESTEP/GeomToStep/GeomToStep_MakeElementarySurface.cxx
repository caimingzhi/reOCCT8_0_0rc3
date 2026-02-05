#include <Geom_ConicalSurface.hpp>
#include <Geom_CylindricalSurface.hpp>
#include <Geom_ElementarySurface.hpp>
#include <Geom_Plane.hpp>
#include <Geom_SphericalSurface.hpp>
#include <Geom_ToroidalSurface.hpp>
#include <GeomToStep_MakeConicalSurface.hpp>
#include <GeomToStep_MakeCylindricalSurface.hpp>
#include <GeomToStep_MakeElementarySurface.hpp>
#include <GeomToStep_MakePlane.hpp>
#include <GeomToStep_MakeSphericalSurface.hpp>
#include <GeomToStep_MakeToroidalSurface.hpp>
#include <StdFail_NotDone.hpp>
#include <StepData_Factors.hpp>
#include <StepGeom_ConicalSurface.hpp>
#include <StepGeom_CylindricalSurface.hpp>
#include <StepGeom_ElementarySurface.hpp>
#include <StepGeom_Plane.hpp>
#include <StepGeom_SphericalSurface.hpp>
#include <StepGeom_ToroidalSurface.hpp>

//=============================================================================
// Creation d' une ElementarySurface de prostep a partir d' une
// ElementarySurface de Geom
//=============================================================================
GeomToStep_MakeElementarySurface::GeomToStep_MakeElementarySurface(
  const occ::handle<Geom_ElementarySurface>& S,
  const StepData_Factors&                    theLocalFactors)
{
  done = true;
  if (S->IsKind(STANDARD_TYPE(Geom_CylindricalSurface)))
  {
    occ::handle<Geom_CylindricalSurface> Sur = occ::down_cast<Geom_CylindricalSurface>(S);
    GeomToStep_MakeCylindricalSurface    MkCylindrical(Sur, theLocalFactors);
    theElementarySurface = MkCylindrical.Value();
  }
  else if (S->IsKind(STANDARD_TYPE(Geom_ConicalSurface)))
  {
    occ::handle<Geom_ConicalSurface> Sur = occ::down_cast<Geom_ConicalSurface>(S);
    GeomToStep_MakeConicalSurface    MkConical(Sur, theLocalFactors);
    theElementarySurface = MkConical.Value();
  }
  else if (S->IsKind(STANDARD_TYPE(Geom_SphericalSurface)))
  {
    occ::handle<Geom_SphericalSurface> Sur = occ::down_cast<Geom_SphericalSurface>(S);
    GeomToStep_MakeSphericalSurface    MkSpherical(Sur, theLocalFactors);
    theElementarySurface = MkSpherical.Value();
  }
  else if (S->IsKind(STANDARD_TYPE(Geom_ToroidalSurface)))
  {
    occ::handle<Geom_ToroidalSurface> Sur = occ::down_cast<Geom_ToroidalSurface>(S);
    GeomToStep_MakeToroidalSurface    MkToroidal(Sur, theLocalFactors);
    theElementarySurface = MkToroidal.Value();
  }
  else if (S->IsKind(STANDARD_TYPE(Geom_Plane)))
  {
    occ::handle<Geom_Plane> Sur = occ::down_cast<Geom_Plane>(S);
    GeomToStep_MakePlane    MkPlane(Sur, theLocalFactors);
    theElementarySurface = MkPlane.Value();
  }
  else
    done = false;
}

//=============================================================================
// renvoi des valeurs
//=============================================================================

const occ::handle<StepGeom_ElementarySurface>& GeomToStep_MakeElementarySurface::Value() const
{
  StdFail_NotDone_Raise_if(!done, "GeomToStep_MakeElementarySurface::Value() - no result");
  return theElementarySurface;
}
