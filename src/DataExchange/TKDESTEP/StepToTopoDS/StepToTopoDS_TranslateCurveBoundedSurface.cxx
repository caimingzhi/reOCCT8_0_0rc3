#include <BRep_Builder.hpp>
#include <BRepBuilderAPI_MakeFace.hpp>
#include <Geom_BoundedSurface.hpp>
#include <Precision.hpp>
#include <ShapeAlgo.hpp>
#include <ShapeAlgo_AlgoContainer.hpp>
#include <StepData_Factors.hpp>
#include <StepGeom_BoundaryCurve.hpp>
#include <StepGeom_BSplineSurface.hpp>
#include <StepGeom_CurveBoundedSurface.hpp>
#include <StepGeom_SurfaceBoundary.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepToGeom.hpp>
#include <StepToTopoDS_TranslateCompositeCurve.hpp>
#include <StepToTopoDS_TranslateCurveBoundedSurface.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>
#include <Transfer_TransientProcess.hpp>

//=================================================================================================

StepToTopoDS_TranslateCurveBoundedSurface::StepToTopoDS_TranslateCurveBoundedSurface() = default;

//=================================================================================================

StepToTopoDS_TranslateCurveBoundedSurface::StepToTopoDS_TranslateCurveBoundedSurface(
  const occ::handle<StepGeom_CurveBoundedSurface>& CBS,
  const occ::handle<Transfer_TransientProcess>&    TP,
  const StepData_Factors&                          theLocalFactors)
{
  Init(CBS, TP, theLocalFactors);
}

//=================================================================================================

bool StepToTopoDS_TranslateCurveBoundedSurface::Init(
  const occ::handle<StepGeom_CurveBoundedSurface>& CBS,
  const occ::handle<Transfer_TransientProcess>&    TP,
  const StepData_Factors&                          theLocalFactors)
{
  myFace.Nullify();
  if (CBS.IsNull())
    return false;

  // translate basis surface
  occ::handle<StepGeom_Surface> S    = CBS->BasisSurface();
  occ::handle<Geom_Surface>     Surf = StepToGeom::MakeSurface(S, theLocalFactors);
  if (Surf.IsNull())
  {
    TP->AddFail(CBS, "Basis surface not translated");
    return false;
  }

  // abv 30.06.00: trj4_k1_geo-tu.stp #108: do as in TranslateFace
  // pdn to force bsplsurf to be periodic
  occ::handle<StepGeom_BSplineSurface> sgbss = occ::down_cast<StepGeom_BSplineSurface>(S);
  if (!sgbss.IsNull())
  {
    occ::handle<Geom_Surface> periodicSurf = ShapeAlgo::AlgoContainer()->ConvertToPeriodic(Surf);
    if (!periodicSurf.IsNull())
    {
      TP->AddWarning(S, "Surface forced to be periodic");
      Surf = periodicSurf;
    }
  }

  // create face
  BRep_Builder B;
  B.MakeFace(myFace, Surf, Precision::Confusion());

  // add natural bound if implicit
  if (CBS->ImplicitOuter())
  {
    if (Surf->IsKind(STANDARD_TYPE(Geom_BoundedSurface)))
    {
      BRepBuilderAPI_MakeFace mf(Surf, Precision::Confusion());
      myFace = mf.Face();
    }
    else
      TP->AddWarning(CBS, "Cannot make natural bounds on infinite surface");
  }

  // translate boundaries
  occ::handle<NCollection_HArray1<StepGeom_SurfaceBoundary>> bnd = CBS->Boundaries();
  int                                                        nb  = bnd->Length();
  for (int i = 1; i <= nb; i++)
  {
    occ::handle<StepGeom_CompositeCurve> cc = bnd->Value(i).BoundaryCurve();
    if (cc.IsNull())
      continue;
    StepToTopoDS_TranslateCompositeCurve TrCC(cc, TP, S, Surf, theLocalFactors);
    if (!TrCC.IsDone())
    {
      TP->AddWarning(CBS, "Boundary not translated");
      continue;
    }
    B.Add(myFace, TrCC.Value());
  }

  done = !myFace.IsNull();
  return done;
}

//=================================================================================================

const TopoDS_Face& StepToTopoDS_TranslateCurveBoundedSurface::Value() const
{
  return myFace;
}
