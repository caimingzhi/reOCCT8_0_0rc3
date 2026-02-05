#include <Geom_BezierSurface.hpp>
#include <Geom_BoundedSurface.hpp>
#include <Geom_BSplineSurface.hpp>
#include <Geom_RectangularTrimmedSurface.hpp>
#include <GeomConvert.hpp>
#include <GeomToStep_MakeBoundedSurface.hpp>
#include <GeomToStep_MakeBSplineSurfaceWithKnots.hpp>
#include <GeomToStep_MakeBSplineSurfaceWithKnotsAndRationalBSplineSurface.hpp>
#include <GeomToStep_MakeRectangularTrimmedSurface.hpp>
#include <StdFail_NotDone.hpp>
#include <StepData_Factors.hpp>
#include <StepGeom_BoundedSurface.hpp>
#include <StepGeom_BSplineSurfaceWithKnots.hpp>
#include <StepGeom_BSplineSurfaceWithKnotsAndRationalBSplineSurface.hpp>
#include <StepGeom_RectangularTrimmedSurface.hpp>

//=============================================================================
// Creation d' une BoundedSurface de prostep a partir d' une BoundedSurface
// de Geom
//=============================================================================
GeomToStep_MakeBoundedSurface::GeomToStep_MakeBoundedSurface(
  const occ::handle<Geom_BoundedSurface>& S,
  const StepData_Factors&                 theLocalFactors)
{
  done = true;
  if (S->IsKind(STANDARD_TYPE(Geom_BSplineSurface)))
  {
    occ::handle<Geom_BSplineSurface> BS = occ::down_cast<Geom_BSplineSurface>(S);
    // UPDATE FMA 1-04-96
    if (S->IsUPeriodic() || S->IsVPeriodic())
    {
      occ::handle<Geom_BSplineSurface> newBS = occ::down_cast<Geom_BSplineSurface>(BS->Copy());
      newBS->SetUNotPeriodic();
      newBS->SetVNotPeriodic();
      BS = newBS;
    }
    if (BS->IsURational() || BS->IsVRational())
    {
      GeomToStep_MakeBSplineSurfaceWithKnotsAndRationalBSplineSurface MkRatBSplineS(
        BS,
        theLocalFactors);
      theBoundedSurface = MkRatBSplineS.Value();
    }
    else
    {
      GeomToStep_MakeBSplineSurfaceWithKnots MkBSplineS(BS, theLocalFactors);
      theBoundedSurface = MkBSplineS.Value();
    }
  }
  else if (S->IsKind(STANDARD_TYPE(Geom_BezierSurface)))
  {
    occ::handle<Geom_BezierSurface>  Sur = occ::down_cast<Geom_BezierSurface>(S);
    occ::handle<Geom_BSplineSurface> BS  = GeomConvert::SurfaceToBSplineSurface(Sur);
    if (BS->IsURational() || BS->IsVRational())
    {
      GeomToStep_MakeBSplineSurfaceWithKnotsAndRationalBSplineSurface MkRatBSplineS(
        BS,
        theLocalFactors);
      theBoundedSurface = MkRatBSplineS.Value();
    }
    else
    {
      GeomToStep_MakeBSplineSurfaceWithKnots MkBSplineS(BS, theLocalFactors);
      theBoundedSurface = MkBSplineS.Value();
    }
  }
  else if (S->IsKind(STANDARD_TYPE(Geom_RectangularTrimmedSurface)))
  {
    occ::handle<Geom_RectangularTrimmedSurface> Sur =
      occ::down_cast<Geom_RectangularTrimmedSurface>(S);
    GeomToStep_MakeRectangularTrimmedSurface MkRTSurf(Sur, theLocalFactors);
    theBoundedSurface = MkRTSurf.Value();
  }
  else
    done = false;
}

//=============================================================================
// renvoi des valeurs
//=============================================================================

const occ::handle<StepGeom_BoundedSurface>& GeomToStep_MakeBoundedSurface::Value() const
{
  StdFail_NotDone_Raise_if(!done, "GeomToStep_MakeBoundedSurface::Value() - no result");
  return theBoundedSurface;
}
