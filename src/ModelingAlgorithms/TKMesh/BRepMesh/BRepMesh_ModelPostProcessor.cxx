#include <BRepMesh_ModelPostProcessor.hpp>

#include <BRepMesh_ShapeTool.hpp>
#include <IMeshData_Model.hpp>
#include <IMeshData_Edge.hpp>
#include <IMeshData_PCurve.hpp>
#include <IMeshTools_Parameters.hpp>
#include <OSD_Parallel.hpp>
#include <BRepLib.hpp>
#include <Poly_TriangulationParameters.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BRepMesh_ModelPostProcessor, IMeshTools_ModelAlgo)

namespace
{

  class PolygonCommitter
  {
  public:
    PolygonCommitter(const occ::handle<IMeshData_Model>& theModel)
        : myModel(theModel)
    {
    }

    void operator()(const int theEdgeIndex) const
    {
      const IMeshData::IEdgeHandle& aDEdge = myModel->GetEdge(theEdgeIndex);
      if (aDEdge->GetCurve()->ParametersNb() == 0)
        return;

      if (aDEdge->IsFree())
      {
        if (!aDEdge->IsSet(IMeshData_Reused))
        {
          commitPolygon3D(aDEdge);
        }
      }
      else
      {
        commitPolygons(aDEdge);
      }
    }

  private:
    void commitPolygon3D(const IMeshData::IEdgeHandle& theDEdge) const
    {
      const IMeshData::ICurveHandle& aCurve = theDEdge->GetCurve();

      NCollection_Array1<gp_Pnt> aNodes(1, aCurve->ParametersNb());
      NCollection_Array1<double> aUVNodes(1, aCurve->ParametersNb());
      for (int i = 1; i <= aCurve->ParametersNb(); ++i)
      {
        aNodes(i)   = aCurve->GetPoint(i - 1);
        aUVNodes(i) = aCurve->GetParameter(i - 1);
      }

      occ::handle<Poly_Polygon3D> aPoly3D = new Poly_Polygon3D(aNodes, aUVNodes);
      aPoly3D->Deflection(theDEdge->GetDeflection());

      BRepMesh_ShapeTool::UpdateEdge(theDEdge->GetEdge(), aPoly3D);
    }

    void commitPolygons(const IMeshData::IEdgeHandle& theDEdge) const
    {

      IMeshData::IDMapOfIFacePtrsListOfIPCurves aMapOfPCurves;
      for (int aPCurveIt = 0; aPCurveIt < theDEdge->PCurvesNb(); ++aPCurveIt)
      {
        const IMeshData::IPCurveHandle& aPCurve   = theDEdge->GetPCurve(aPCurveIt);
        const IMeshData::IFacePtr&      aDFacePtr = aPCurve->GetFace();
        const IMeshData::IFaceHandle    aDFace    = aDFacePtr;
        if (aDFace->IsSet(IMeshData_Failure) || aDFace->IsSet(IMeshData_Reused))
        {
          continue;
        }

        if (!aMapOfPCurves.Contains(aDFacePtr))
        {
          aMapOfPCurves.Add(aDFacePtr, IMeshData::ListOfIPCurves());
        }

        IMeshData::ListOfIPCurves& aPCurves = aMapOfPCurves.ChangeFromKey(aDFacePtr);
        aPCurves.Append(aPCurve);
      }

      const TopoDS_Edge&                                  aEdge = theDEdge->GetEdge();
      IMeshData::IDMapOfIFacePtrsListOfIPCurves::Iterator aPolygonIt(aMapOfPCurves);
      for (; aPolygonIt.More(); aPolygonIt.Next())
      {
        const TopoDS_Face& aFace = aPolygonIt.Key()->GetFace();

        TopLoc_Location                        aLoc;
        const occ::handle<Poly_Triangulation>& aTriangulation =
          BRep_Tool::Triangulation(aFace, aLoc);

        if (!aTriangulation.IsNull())
        {
          const IMeshData::ListOfIPCurves& aPCurves = aPolygonIt.Value();
          if (aPCurves.Size() == 2)
          {
            BRepMesh_ShapeTool::UpdateEdge(
              aEdge,
              collectPolygon(aPCurves.First(), theDEdge->GetDeflection()),
              collectPolygon(aPCurves.Last(), theDEdge->GetDeflection()),
              aTriangulation,
              aLoc);
          }
          else
          {
            BRepMesh_ShapeTool::UpdateEdge(
              aEdge,
              collectPolygon(aPCurves.First(), theDEdge->GetDeflection()),
              aTriangulation,
              aLoc);
          }
        }
      }
    }

    occ::handle<Poly_PolygonOnTriangulation> collectPolygon(
      const IMeshData::IPCurveHandle& thePCurve,
      const double                    theDeflection) const
    {
      NCollection_Array1<int>    aNodes(1, thePCurve->ParametersNb());
      NCollection_Array1<double> aParams(1, thePCurve->ParametersNb());
      for (int i = 1; i <= thePCurve->ParametersNb(); ++i)
      {
        aNodes(i)  = thePCurve->GetIndex(i - 1);
        aParams(i) = thePCurve->GetParameter(i - 1);
      }

      occ::handle<Poly_PolygonOnTriangulation> aPolygon =
        new Poly_PolygonOnTriangulation(aNodes, aParams);

      aPolygon->Deflection(theDeflection);
      return aPolygon;
    }

  private:
    occ::handle<IMeshData_Model> myModel;
  };

  class DeflectionEstimator
  {
  public:
    DeflectionEstimator(const occ::handle<IMeshData_Model>& theModel,
                        const IMeshTools_Parameters&        theParams)
        : myModel(theModel),
          myParams(new Poly_TriangulationParameters(theParams.Deflection,
                                                    theParams.Angle,
                                                    theParams.MinSize))
    {
    }

    void operator()(const int theFaceIndex) const
    {
      const IMeshData::IFaceHandle& aDFace = myModel->GetFace(theFaceIndex);
      if (aDFace->IsSet(IMeshData_Failure) || aDFace->IsSet(IMeshData_Reused))
      {
        return;
      }

      BRepLib::UpdateDeflection(aDFace->GetFace());

      TopLoc_Location                        aLoc;
      const occ::handle<Poly_Triangulation>& aTriangulation =
        BRep_Tool::Triangulation(aDFace->GetFace(), aLoc);

      if (!aTriangulation.IsNull())
      {
        aTriangulation->Parameters(myParams);
      }
    }

  private:
    occ::handle<IMeshData_Model>              myModel;
    occ::handle<Poly_TriangulationParameters> myParams;
  };
} // namespace

BRepMesh_ModelPostProcessor::BRepMesh_ModelPostProcessor() = default;

BRepMesh_ModelPostProcessor::~BRepMesh_ModelPostProcessor() = default;

bool BRepMesh_ModelPostProcessor::performInternal(const occ::handle<IMeshData_Model>& theModel,
                                                  const IMeshTools_Parameters&        theParameters,
                                                  const Message_ProgressRange&        theRange)
{
  (void)theRange;
  if (theModel.IsNull())
  {
    return false;
  }

  OSD_Parallel::For(0, theModel->EdgesNb(), PolygonCommitter(theModel), true);

  OSD_Parallel::For(0,
                    theModel->FacesNb(),
                    DeflectionEstimator(theModel, theParameters),
                    !theParameters.InParallel);
  return true;
}
