#include <BRepMesh_EdgeDiscret.hpp>
#include <BRepMesh_Deflection.hpp>
#include <IMeshData_Model.hpp>
#include <IMeshData_Face.hpp>
#include <IMeshData_PCurve.hpp>
#include <TopExp.hpp>
#include <BRepMesh_ShapeTool.hpp>
#include <BRepMesh_EdgeTessellationExtractor.hpp>
#include <IMeshData_ParametersListArrayAdaptor.hpp>
#include <BRepMesh_CurveTessellator.hpp>
#include <OSD_Parallel.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BRepMesh_EdgeDiscret, IMeshTools_ModelAlgo)

BRepMesh_EdgeDiscret::BRepMesh_EdgeDiscret() = default;

BRepMesh_EdgeDiscret::~BRepMesh_EdgeDiscret() = default;

occ::handle<IMeshTools_CurveTessellator> BRepMesh_EdgeDiscret::CreateEdgeTessellator(
  const IMeshData::IEdgeHandle& theDEdge,
  const IMeshTools_Parameters&  theParameters,
  const int                     theMinPointsNb)
{
  return new BRepMesh_CurveTessellator(theDEdge, theParameters, theMinPointsNb);
}

occ::handle<IMeshTools_CurveTessellator> BRepMesh_EdgeDiscret::CreateEdgeTessellator(
  const IMeshData::IEdgeHandle& theDEdge,
  const TopAbs_Orientation      theOrientation,
  const IMeshData::IFaceHandle& theDFace,
  const IMeshTools_Parameters&  theParameters,
  const int                     theMinPointsNb)
{
  return theDEdge->GetSameParam()
           ? new BRepMesh_CurveTessellator(theDEdge, theParameters, theMinPointsNb)
           : new BRepMesh_CurveTessellator(theDEdge,
                                           theOrientation,
                                           theDFace,
                                           theParameters,
                                           theMinPointsNb);
}

occ::handle<IMeshTools_CurveTessellator> BRepMesh_EdgeDiscret::CreateEdgeTessellationExtractor(
  const IMeshData::IEdgeHandle& theDEdge,
  const IMeshData::IFaceHandle& theDFace)
{
  return new BRepMesh_EdgeTessellationExtractor(theDEdge, theDFace);
}

bool BRepMesh_EdgeDiscret::performInternal(const occ::handle<IMeshData_Model>& theModel,
                                           const IMeshTools_Parameters&        theParameters,
                                           const Message_ProgressRange&        theRange)
{
  (void)theRange;
  myModel      = theModel;
  myParameters = theParameters;

  if (myModel.IsNull())
  {
    return false;
  }

  OSD_Parallel::For(0, myModel->EdgesNb(), *this, !myParameters.InParallel);

  myModel.Nullify();
  return true;
}

void BRepMesh_EdgeDiscret::process(const int theEdgeIndex) const
{
  const IMeshData::IEdgeHandle& aDEdge = myModel->GetEdge(theEdgeIndex);
  try
  {
    OCC_CATCH_SIGNALS

    BRepMesh_Deflection::ComputeDeflection(aDEdge, myModel->GetMaxSize(), myParameters);

    occ::handle<IMeshTools_CurveTessellator> aEdgeTessellator;
    if (!aDEdge->IsFree())
    {

      double aMinDeflection  = RealLast();
      int    aMinPCurveIndex = -1;
      for (int aPCurveIt = 0; aPCurveIt < aDEdge->PCurvesNb(); ++aPCurveIt)
      {
        const IMeshData::IPCurveHandle& aPCurve = aDEdge->GetPCurve(aPCurveIt);
        const double aTmpDeflection = checkExistingPolygonAndUpdateStatus(aDEdge, aPCurve);
        if (aTmpDeflection < aMinDeflection)
        {

          aMinDeflection  = aTmpDeflection;
          aMinPCurveIndex = aPCurveIt;
        }

        BRepMesh_ShapeTool::CheckAndUpdateFlags(aDEdge, aPCurve);
      }

      if (aMinPCurveIndex != -1)
      {
        aDEdge->SetDeflection(aMinDeflection);
        const IMeshData::IFaceHandle aDFace = aDEdge->GetPCurve(aMinPCurveIndex)->GetFace();
        aEdgeTessellator                    = CreateEdgeTessellationExtractor(aDEdge, aDFace);
      }
      else
      {
        const IMeshData::IPCurveHandle& aPCurve = aDEdge->GetPCurve(0);
        const IMeshData::IFaceHandle    aDFace  = aPCurve->GetFace();
        aEdgeTessellator = BRepMesh_EdgeDiscret::CreateEdgeTessellator(aDEdge,
                                                                       aPCurve->GetOrientation(),
                                                                       aDFace,
                                                                       myParameters);
      }
    }
    else
    {
      TopLoc_Location                    aLoc;
      const occ::handle<Poly_Polygon3D>& aPoly3D = BRep_Tool::Polygon3D(aDEdge->GetEdge(), aLoc);
      if (!aPoly3D.IsNull())
      {
        if (aPoly3D->HasParameters()
            && BRepMesh_Deflection::IsConsistent(aPoly3D->Deflection(),
                                                 aDEdge->GetDeflection(),
                                                 myParameters.AllowQualityDecrease))
        {

          aDEdge->SetStatus(IMeshData_Reused);
          return;
        }
        else
        {
          aDEdge->SetStatus(IMeshData_Outdated);
        }
      }

      aEdgeTessellator = CreateEdgeTessellator(aDEdge, myParameters);
    }

    Tessellate3d(aDEdge, aEdgeTessellator, true);
    if (!aDEdge->IsFree())
    {
      Tessellate2d(aDEdge, true);
    }
  }
  catch (Standard_Failure const&)
  {
    aDEdge->SetStatus(IMeshData_Failure);
  }
}

double BRepMesh_EdgeDiscret::checkExistingPolygonAndUpdateStatus(
  const IMeshData::IEdgeHandle&   theDEdge,
  const IMeshData::IPCurveHandle& thePCurve) const
{
  const TopoDS_Edge& aEdge = theDEdge->GetEdge();
  const TopoDS_Face& aFace = thePCurve->GetFace()->GetFace();

  TopLoc_Location                        aLoc;
  const occ::handle<Poly_Triangulation>& aFaceTriangulation = BRep_Tool::Triangulation(aFace, aLoc);

  double aDeflection = RealLast();
  if (aFaceTriangulation.IsNull())
  {
    return aDeflection;
  }

  const occ::handle<Poly_PolygonOnTriangulation>& aPolygon =
    BRep_Tool::PolygonOnTriangulation(aEdge, aFaceTriangulation, aLoc);

  if (!aPolygon.IsNull())
  {
    bool isConsistent = aPolygon->HasParameters()
                        && BRepMesh_Deflection::IsConsistent(aPolygon->Deflection(),
                                                             theDEdge->GetDeflection(),
                                                             myParameters.AllowQualityDecrease);

    if (!isConsistent)
    {

      theDEdge->SetStatus(IMeshData_Outdated);
    }
    else
    {
      aDeflection = aPolygon->Deflection();
    }
  }

  return aDeflection;
}

void BRepMesh_EdgeDiscret::Tessellate3d(
  const IMeshData::IEdgeHandle&                   theDEdge,
  const occ::handle<IMeshTools_CurveTessellator>& theTessellator,
  const bool                                      theUpdateEnds)
{

  const IMeshData::ICurveHandle& aCurve = theDEdge->GetCurve();

  const TopoDS_Edge& aEdge = theDEdge->GetEdge();
  TopoDS_Vertex      aFirstVertex, aLastVertex;
  TopExp::Vertices(aEdge, aFirstVertex, aLastVertex);

  if (aFirstVertex.IsNull() || aLastVertex.IsNull())
    return;

  if (theUpdateEnds)
  {
    gp_Pnt aPoint;
    double aParam;
    theTessellator->Value(1, aPoint, aParam);
    aCurve->AddPoint(BRep_Tool::Pnt(aFirstVertex), aParam);
  }

  if (!theDEdge->GetDegenerated())
  {
    for (int i = 2; i < theTessellator->PointsNb(); ++i)
    {
      gp_Pnt aPoint;
      double aParam;
      if (!theTessellator->Value(i, aPoint, aParam))
        continue;

      if (theUpdateEnds)
      {
        aCurve->AddPoint(aPoint, aParam);
      }
      else
      {
        aCurve->InsertPoint(aCurve->ParametersNb() - 1, aPoint, aParam);
      }
    }
  }

  if (theUpdateEnds)
  {
    gp_Pnt aPoint;
    double aParam;
    theTessellator->Value(theTessellator->PointsNb(), aPoint, aParam);
    aCurve->AddPoint(BRep_Tool::Pnt(aLastVertex), aParam);
  }
}

void BRepMesh_EdgeDiscret::Tessellate2d(const IMeshData::IEdgeHandle& theDEdge,
                                        const bool                    theUpdateEnds)
{
  const IMeshData::ICurveHandle& aCurve = theDEdge->GetCurve();
  for (int aPCurveIt = 0; aPCurveIt < theDEdge->PCurvesNb(); ++aPCurveIt)
  {
    const IMeshData::IPCurveHandle&     aPCurve = theDEdge->GetPCurve(aPCurveIt);
    const IMeshData::IFaceHandle        aDFace  = aPCurve->GetFace();
    IMeshData::ICurveArrayAdaptorHandle aCurveArray(new IMeshData::ICurveArrayAdaptor(aCurve));
    BRepMesh_EdgeParameterProvider<IMeshData::ICurveArrayAdaptorHandle> aProvider(
      theDEdge,
      aPCurve->GetOrientation(),
      aDFace,
      aCurveArray);

    const occ::handle<Adaptor2d_Curve2d>& aGeomPCurve = aProvider.GetPCurve();

    int aParamIdx, aParamNb;
    if (theUpdateEnds)
    {
      aParamIdx = 0;
      aParamNb  = aCurve->ParametersNb();
    }
    else
    {
      aParamIdx = 1;
      aParamNb  = aCurve->ParametersNb() - 1;
    }

    for (; aParamIdx < aParamNb; ++aParamIdx)
    {
      const double aParam = aProvider.Parameter(aParamIdx, aCurve->GetPoint(aParamIdx));

      gp_Pnt2d aPoint2d;
      aGeomPCurve->D0(aParam, aPoint2d);
      if (theUpdateEnds)
      {
        aPCurve->AddPoint(aPoint2d, aParam);
      }
      else
      {
        aPCurve->InsertPoint(aPCurve->ParametersNb() - 1, aPoint2d, aParam);
      }
    }
  }
}
