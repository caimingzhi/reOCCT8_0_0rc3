#include <Geom_ConicalSurface.hpp>
#include <Geom_CylindricalSurface.hpp>
#include <Geom_Plane.hpp>
#include <Geom_RectangularTrimmedSurface.hpp>
#include <Geom_SphericalSurface.hpp>
#include <Geom_SurfaceOfRevolution.hpp>
#include <Geom_ToroidalSurface.hpp>
#include <GeomToStep_MakeRectangularTrimmedSurface.hpp>
#include <GeomToStep_MakeSurface.hpp>
#include <StdFail_NotDone.hpp>
#include <StepData_Factors.hpp>
#include <StepGeom_RectangularTrimmedSurface.hpp>
#include <StepGeom_Surface.hpp>
#include <TCollection_HAsciiString.hpp>

//=============================================================================
// Creation d' une rectangular_trimmed_surface de STEP
// a partir d' une RectangularTrimmedSurface de Geom
//=============================================================================
GeomToStep_MakeRectangularTrimmedSurface::GeomToStep_MakeRectangularTrimmedSurface(
  const occ::handle<Geom_RectangularTrimmedSurface>& RTSurf,
  const StepData_Factors&                            theLocalFactors)
{

  occ::handle<StepGeom_RectangularTrimmedSurface> StepRTS = new StepGeom_RectangularTrimmedSurface;

  occ::handle<TCollection_HAsciiString> aName = new TCollection_HAsciiString("");

  GeomToStep_MakeSurface mkSurf(RTSurf->BasisSurface(), theLocalFactors);
  if (!mkSurf.IsDone())
  {
    done = false;
    return;
  }
  const occ::handle<StepGeom_Surface>& StepSurf = mkSurf.Value();

  double U1, U2, V1, V2;
  RTSurf->Bounds(U1, U2, V1, V2);

  // -----------------------------------------
  // Modification of the Trimming Parameters ?
  // -----------------------------------------

  double                    AngleFact  = 180. / M_PI;
  double                    uFact      = 1.;
  double                    vFact      = 1.;
  double                    LengthFact = theLocalFactors.LengthFactor();
  occ::handle<Geom_Surface> theSurf    = RTSurf->BasisSurface();
  if (theSurf->IsKind(STANDARD_TYPE(Geom_CylindricalSurface)))
  {
    uFact = AngleFact;
    vFact = 1. / LengthFact;
  }
  else if (theSurf->IsKind(STANDARD_TYPE(Geom_SurfaceOfRevolution)))
  {
    uFact = AngleFact;
  }
  else if (theSurf->IsKind(STANDARD_TYPE(Geom_ToroidalSurface))
           || theSurf->IsKind(STANDARD_TYPE(Geom_SphericalSurface)))
  {
    uFact = AngleFact;
    vFact = AngleFact;
  }
  else if (theSurf->IsKind(STANDARD_TYPE(Geom_ConicalSurface)))
  {
    occ::handle<Geom_ConicalSurface> conicS = occ::down_cast<Geom_ConicalSurface>(theSurf);
    double                           semAng = conicS->SemiAngle();
    uFact                                   = AngleFact;
    vFact                                   = std::cos(semAng) / LengthFact;
  }
  else if (theSurf->IsKind(STANDARD_TYPE(Geom_Plane)))
  {
    uFact = vFact = 1. / LengthFact;
  }

  U1 = U1 * uFact;
  U2 = U2 * uFact;
  V1 = V1 * vFact;
  V2 = V2 * vFact;

  StepRTS->Init(aName, StepSurf, U1, U2, V1, V2, true, true);
  theRectangularTrimmedSurface = StepRTS;
  done                         = true;
}

//=============================================================================
// renvoi des valeurs
//=============================================================================

const occ::handle<StepGeom_RectangularTrimmedSurface>& GeomToStep_MakeRectangularTrimmedSurface::
  Value() const
{
  StdFail_NotDone_Raise_if(!done, "GeomToStep_MakeRectangularTrimmedSurface::Value() - no result");
  return theRectangularTrimmedSurface;
}
