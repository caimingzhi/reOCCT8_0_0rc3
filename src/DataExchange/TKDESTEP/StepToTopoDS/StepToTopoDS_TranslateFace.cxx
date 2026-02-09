#include <BRep_Builder.hpp>
#include <BRep_TEdge.hpp>
#include <BRep_Tool.hpp>
#include <BRep_TVertex.hpp>
#include <BRepBuilderAPI_MakeFace.hpp>
#include <BRepTools.hpp>
#include <Geom2d_Curve.hpp>
#include <Geom_BoundedSurface.hpp>
#include <Geom_BSplineSurface.hpp>
#include <Geom_Plane.hpp>
#include <Geom_SphericalSurface.hpp>
#include <Geom_Surface.hpp>
#include <Geom_SurfaceOfRevolution.hpp>
#include <Geom_ToroidalSurface.hpp>
#include <GeomAbs_Shape.hpp>
#include <GeomAdaptor_Surface.hpp>
#include <MoniTool_Macros.hpp>
#include <Precision.hpp>
#include <ShapeAlgo.hpp>
#include <ShapeAlgo_AlgoContainer.hpp>
#include <StdFail_NotDone.hpp>
#include <StepData_Factors.hpp>
#include <StepGeom_BSplineSurface.hpp>
#include <StepGeom_BSplineSurfaceForm.hpp>
#include <StepGeom_OffsetSurface.hpp>
#include <StepGeom_Surface.hpp>
#include <StepShape_Edge.hpp>
#include <StepShape_EdgeCurve.hpp>
#include <StepShape_EdgeLoop.hpp>
#include <StepShape_FaceBound.hpp>
#include <StepShape_FaceOuterBound.hpp>
#include <StepShape_FaceSurface.hpp>
#include <StepShape_OrientedEdge.hpp>
#include <StepShape_PolyLoop.hpp>
#include <StepShape_VertexLoop.hpp>
#include <StepToGeom.hpp>
#include <StepToTopoDS.hpp>
#include <StepToTopoDS_NMTool.hpp>
#include <StepToTopoDS_Tool.hpp>
#include <StepToTopoDS_TranslateEdgeLoop.hpp>
#include <StepToTopoDS_TranslateFace.hpp>
#include <StepToTopoDS_TranslatePolyLoop.hpp>
#include <StepToTopoDS_TranslateVertexLoop.hpp>
#include <TCollection_HAsciiString.hpp>
#include <TopExp.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Iterator.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Vertex.hpp>
#include <TopoDS_Wire.hpp>
#include <Transfer_TransientProcess.hpp>
#include <TransferBRep_ShapeBinder.hpp>
#include <StepGeom_RectangularTrimmedSurface.hpp>
#include <StepGeom_ToroidalSurface.hpp>
#include <StepVisual_TriangulatedFace.hpp>
#include <StepVisual_ComplexTriangulatedFace.hpp>
#include <StepVisual_TriangulatedSurfaceSet.hpp>
#include <StepVisual_ComplexTriangulatedSurfaceSet.hpp>

namespace
{

  static void SetNodes(const occ::handle<Poly_Triangulation>&    theMesh,
                       occ::handle<NCollection_HArray1<gp_XYZ>>& theNodes,
                       const int                                 theNumPnindex,
                       occ::handle<NCollection_HArray1<int>>&    thePnindices,
                       const double                              theLengthFactor)
  {
    for (int aPnIndex = 1; aPnIndex <= theMesh->NbNodes(); ++aPnIndex)
    {
      const gp_XYZ& aPoint =
        theNodes->Value((theNumPnindex > 0) ? thePnindices->Value(aPnIndex) : aPnIndex);
      theMesh->SetNode(aPnIndex, theLengthFactor * aPoint);
    }
  }

  static void SetNormals(const occ::handle<Poly_Triangulation>&          theMesh,
                         const occ::handle<NCollection_HArray2<double>>& theNormals,
                         const int                                       theNormNum,
                         const int                                       theNumPnindex)
  {
    if (theNormals->RowLength() != 3)
    {
      return;
    }
    gp_XYZ aNorm;
    if (theNormNum == 1)
    {
      aNorm.SetX(theNormals->Value(1, 1));
      aNorm.SetY(theNormals->Value(1, 2));
      aNorm.SetZ(theNormals->Value(1, 3));
      for (int aPnIndex = 1; aPnIndex <= theNumPnindex; ++aPnIndex)
      {
        theMesh->SetNormal(aPnIndex, aNorm);
      }
    }
    else if (theNumPnindex == theNormNum)
    {
      for (int aNormIndex = 1; aNormIndex <= theNormNum; ++aNormIndex)
      {
        aNorm.SetX(theNormals->Value(aNormIndex, 1));
        aNorm.SetY(theNormals->Value(aNormIndex, 2));
        aNorm.SetZ(theNormals->Value(aNormIndex, 3));
        theMesh->SetNormal(aNormIndex, aNorm);
      }
    }
  }

  static void SetTriangles(
    const occ::handle<Poly_Triangulation>&                                   theMesh,
    const occ::handle<NCollection_HArray2<int>>&                             theTriangles,
    const int                                                                theTrianStripsNum,
    const occ::handle<NCollection_HArray1<occ::handle<Standard_Transient>>>& theTrianStrips,
    const int                                                                theTrianFansNum,
    const occ::handle<NCollection_HArray1<occ::handle<Standard_Transient>>>& theTrianFans)
  {
    if (theTrianStripsNum == 0 && theTrianFansNum == 0)
    {
      for (int aTrianIndex = 1; aTrianIndex <= theMesh->NbTriangles(); ++aTrianIndex)
      {
        theMesh->SetTriangle(aTrianIndex,
                             Poly_Triangle(theTriangles->Value(aTrianIndex, 1),
                                           theTriangles->Value(aTrianIndex, 2),
                                           theTriangles->Value(aTrianIndex, 3)));
      }
    }
    else
    {
      int aTriangleIndex = 1;
      for (int aTrianStripIndex = 1; aTrianStripIndex <= theTrianStripsNum; ++aTrianStripIndex)
      {
        occ::handle<NCollection_HArray1<int>> aTriangleStrip =
          occ::down_cast<NCollection_HArray1<int>>(theTrianStrips->Value(aTrianStripIndex));
        for (int anIndex = 3; anIndex <= aTriangleStrip->Length(); anIndex += 2)
        {
          if (aTriangleStrip->Value(anIndex) != aTriangleStrip->Value(anIndex - 2)
              && aTriangleStrip->Value(anIndex) != aTriangleStrip->Value(anIndex - 1))
          {
            theMesh->SetTriangle(aTriangleIndex++,
                                 Poly_Triangle(aTriangleStrip->Value(anIndex - 2),
                                               aTriangleStrip->Value(anIndex),
                                               aTriangleStrip->Value(anIndex - 1)));
          }
        }
        for (int anIndex = 4; anIndex <= aTriangleStrip->Length(); anIndex += 2)
        {
          if (aTriangleStrip->Value(anIndex) != aTriangleStrip->Value(anIndex - 2)
              && aTriangleStrip->Value(anIndex) != aTriangleStrip->Value(anIndex - 1))
          {
            theMesh->SetTriangle(aTriangleIndex++,
                                 Poly_Triangle(aTriangleStrip->Value(anIndex - 2),
                                               aTriangleStrip->Value(anIndex - 1),
                                               aTriangleStrip->Value(anIndex)));
          }
        }
      }
      for (int aTrianFanIndex = 1; aTrianFanIndex <= theTrianFansNum; ++aTrianFanIndex)
      {
        occ::handle<NCollection_HArray1<int>> aTriangleFan =
          occ::down_cast<NCollection_HArray1<int>>(theTrianFans->Value(aTrianFanIndex));
        for (int anIndex = 3; anIndex <= aTriangleFan->Length(); ++anIndex)
        {
          if (aTriangleFan->Value(anIndex) != aTriangleFan->Value(anIndex - 2)
              && aTriangleFan->Value(anIndex - 1) != aTriangleFan->Value(anIndex - 2))
          {
            theMesh->SetTriangle(aTriangleIndex++,
                                 Poly_Triangle(aTriangleFan->Value(1),
                                               aTriangleFan->Value(anIndex),
                                               aTriangleFan->Value(anIndex - 1)));
          }
        }
      }
    }
  }

  template <class Type>
  static void GetSimpleFaceElements(const Type&                               theFace,
                                    occ::handle<NCollection_HArray1<gp_XYZ>>& theNodes,
                                    occ::handle<NCollection_HArray2<double>>& theNormals,
                                    occ::handle<NCollection_HArray2<int>>&    theTriangles,
                                    int&                                      thePnIndNb,
                                    int&                                      theNormNb,
                                    int&                                      theTriNb,
                                    occ::handle<NCollection_HArray1<int>>&    thePnindices)
  {
    theNodes     = theFace->Coordinates()->Points();
    theNormals   = theFace->Normals();
    theTriangles = theFace->Triangles();
    thePnIndNb   = theFace->NbPnindex();
    theNormNb    = theFace->NbNormals();
    theTriNb     = theFace->NbTriangles();
    thePnindices = new NCollection_HArray1<int>(1, thePnIndNb);
    for (int anIndx = 1; anIndx <= thePnIndNb; ++anIndx)
    {
      thePnindices->SetValue(anIndx, theFace->PnindexValue(anIndx));
    }
  }

  template <class Type>
  static void GetComplexFaceElements(
    const Type&                                                        theFace,
    occ::handle<NCollection_HArray1<gp_XYZ>>&                          theNodes,
    occ::handle<NCollection_HArray2<double>>&                          theNormals,
    occ::handle<NCollection_HArray1<occ::handle<Standard_Transient>>>& theTriangleStrips,
    occ::handle<NCollection_HArray1<occ::handle<Standard_Transient>>>& theTriangleFans,
    int&                                                               thePnIndNb,
    int&                                                               theNormNb,
    int&                                                               theTriStripsNb,
    int&                                                               theTriFansNb,
    occ::handle<NCollection_HArray1<int>>&                             thePnindices)
  {
    theNodes          = theFace->Coordinates()->Points();
    theNormals        = theFace->Normals();
    theTriangleStrips = theFace->TriangleStrips();
    theTriangleFans   = theFace->TriangleFans();
    thePnIndNb        = theFace->NbPnindex();
    theNormNb         = theFace->NbNormals();
    theTriStripsNb    = theFace->NbTriangleStrips();
    theTriFansNb      = theFace->NbTriangleFans();
    thePnindices      = new NCollection_HArray1<int>(1, thePnIndNb);
    for (int anIndx = 1; anIndx <= thePnIndNb; ++anIndx)
    {
      thePnindices->SetValue(anIndx, theFace->PnindexValue(anIndx));
    }
  }

  static occ::handle<Poly_Triangulation> CreatePolyTriangulation(
    const occ::handle<StepVisual_TessellatedItem>& theTI,
    const StepData_Factors&                        theLocalFactors)
  {
    occ::handle<Poly_Triangulation> aMesh;
    if (theTI.IsNull())
    {
      return occ::handle<Poly_Triangulation>();
    }

    occ::handle<NCollection_HArray1<gp_XYZ>> aNodes;
    occ::handle<NCollection_HArray2<double>> aNormals;
    occ::handle<NCollection_HArray2<int>>    aTriangles;
    int                                      aNumPnindex = 0;
    int                                      aNormNum    = 0;
    int                                      aTrianNum   = 0;
    occ::handle<NCollection_HArray1<int>>    aPnindices;

    occ::handle<NCollection_HArray1<occ::handle<Standard_Transient>>> aTriaStrips;
    occ::handle<NCollection_HArray1<occ::handle<Standard_Transient>>> aTriaFans;
    int                                                               aTrianStripsNum = 0;
    int                                                               aTrianFansNum   = 0;

    if (theTI->IsKind(STANDARD_TYPE(StepVisual_TriangulatedFace)))
    {
      occ::handle<StepVisual_TriangulatedFace> aTF =
        occ::down_cast<StepVisual_TriangulatedFace>(theTI);
      GetSimpleFaceElements(aTF,
                            aNodes,
                            aNormals,
                            aTriangles,
                            aNumPnindex,
                            aNormNum,
                            aTrianNum,
                            aPnindices);
    }
    else if (theTI->IsKind(STANDARD_TYPE(StepVisual_TriangulatedSurfaceSet)))
    {
      occ::handle<StepVisual_TriangulatedSurfaceSet> aTSS =
        occ::down_cast<StepVisual_TriangulatedSurfaceSet>(theTI);
      GetSimpleFaceElements(aTSS,
                            aNodes,
                            aNormals,
                            aTriangles,
                            aNumPnindex,
                            aNormNum,
                            aTrianNum,
                            aPnindices);
    }
    else if (theTI->IsKind(STANDARD_TYPE(StepVisual_ComplexTriangulatedFace)))
    {
      occ::handle<StepVisual_ComplexTriangulatedFace> aTF =
        occ::down_cast<StepVisual_ComplexTriangulatedFace>(theTI);
      GetComplexFaceElements(aTF,
                             aNodes,
                             aNormals,
                             aTriaStrips,
                             aTriaFans,
                             aNumPnindex,
                             aNormNum,
                             aTrianStripsNum,
                             aTrianFansNum,
                             aPnindices);
    }
    else if (theTI->IsKind(STANDARD_TYPE(StepVisual_ComplexTriangulatedSurfaceSet)))
    {
      occ::handle<StepVisual_ComplexTriangulatedSurfaceSet> aTSS =
        occ::down_cast<StepVisual_ComplexTriangulatedSurfaceSet>(theTI);
      GetComplexFaceElements(aTSS,
                             aNodes,
                             aNormals,
                             aTriaStrips,
                             aTriaFans,
                             aNumPnindex,
                             aNormNum,
                             aTrianStripsNum,
                             aTrianFansNum,
                             aPnindices);
    }
    else
    {
      return occ::handle<Poly_Triangulation>();
    }

    const bool aHasUVNodes = false;
    const bool aHasNormals = (aNormNum > 0);
    const int  aNbNodes    = (aNumPnindex > 0) ? aNumPnindex : aNodes->Length();

    if (aTrianStripsNum == 0 && aTrianFansNum == 0)
    {
      aMesh = new Poly_Triangulation(aNbNodes, aTrianNum, aHasUVNodes, aHasNormals);
    }
    else
    {
      int aNbTriaStrips = 0;
      int aNbTriaFans   = 0;

      for (int aTrianStripIndex = 1; aTrianStripIndex <= aTrianStripsNum; ++aTrianStripIndex)
      {
        occ::handle<NCollection_HArray1<int>> aTriangleStrip =
          occ::down_cast<NCollection_HArray1<int>>(aTriaStrips->Value(aTrianStripIndex));
        for (int anIndex = 3; anIndex <= aTriangleStrip->Length(); anIndex += 2)
        {
          if (aTriangleStrip->Value(anIndex) != aTriangleStrip->Value(anIndex - 2)
              && aTriangleStrip->Value(anIndex) != aTriangleStrip->Value(anIndex - 1))
            ++aNbTriaStrips;
        }
        for (int anIndex = 4; anIndex <= aTriangleStrip->Length(); anIndex += 2)
        {
          if (aTriangleStrip->Value(anIndex) != aTriangleStrip->Value(anIndex - 2)
              && aTriangleStrip->Value(anIndex) != aTriangleStrip->Value(anIndex - 1))
            ++aNbTriaStrips;
        }
      }

      for (int aTrianFanIndex = 1; aTrianFanIndex <= aTrianFansNum; ++aTrianFanIndex)
      {
        occ::handle<NCollection_HArray1<int>> aTriangleFan =
          occ::down_cast<NCollection_HArray1<int>>(aTriaFans->Value(aTrianFanIndex));
        aNbTriaFans += aTriangleFan->Length() - 2;
      }

      aMesh =
        new Poly_Triangulation(aNbNodes, aNbTriaStrips + aNbTriaFans, aHasUVNodes, aHasNormals);
    }

    SetNodes(aMesh, aNodes, aNumPnindex, aPnindices, theLocalFactors.LengthFactor());

    if (aHasNormals)
    {
      SetNormals(aMesh, aNormals, aNormNum, aNbNodes);
    }

    SetTriangles(aMesh, aTriangles, aTrianStripsNum, aTriaStrips, aTrianFansNum, aTriaFans);

    return aMesh;
  }
} // namespace

StepToTopoDS_TranslateFace::StepToTopoDS_TranslateFace()
    : myError(StepToTopoDS_TranslateFaceOther)
{
  done = false;
}

StepToTopoDS_TranslateFace::StepToTopoDS_TranslateFace(const occ::handle<StepShape_FaceSurface>& FS,
                                                       StepToTopoDS_Tool&                        T,
                                                       StepToTopoDS_NMTool&    NMTool,
                                                       const StepData_Factors& theLocalFactors)
{
  Init(FS, T, NMTool, theLocalFactors);
}

StepToTopoDS_TranslateFace::StepToTopoDS_TranslateFace(
  const occ::handle<StepVisual_TessellatedFace>& theTF,
  StepToTopoDS_Tool&                             theTool,
  StepToTopoDS_NMTool&                           theNMTool,
  const bool                                     theReadTessellatedWhenNoBRepOnly,
  bool&                                          theHasGeom,
  const StepData_Factors&                        theLocalFactors)
{
  Init(theTF, theTool, theNMTool, theReadTessellatedWhenNoBRepOnly, theHasGeom, theLocalFactors);
}

StepToTopoDS_TranslateFace::StepToTopoDS_TranslateFace(
  const occ::handle<StepVisual_TessellatedSurfaceSet>& theTSS,
  StepToTopoDS_Tool&                                   theTool,
  StepToTopoDS_NMTool&                                 theNMTool,
  const StepData_Factors&                              theLocalFactors)
{
  Init(theTSS, theTool, theNMTool, theLocalFactors);
}

static inline bool isReversed(const occ::handle<StepGeom_Surface>& theStepSurf)
{
  if (theStepSurf->IsKind(STANDARD_TYPE(StepGeom_RectangularTrimmedSurface)))
  {
    return isReversed(
      occ::down_cast<StepGeom_RectangularTrimmedSurface>(theStepSurf)->BasisSurface());
  }
  else
  {
    occ::handle<StepGeom_ToroidalSurface> aStepTorSur =
      occ::down_cast<StepGeom_ToroidalSurface>(theStepSurf);
    return !aStepTorSur.IsNull() && aStepTorSur->MajorRadius() < 0.;
  }
}

void StepToTopoDS_TranslateFace::Init(const occ::handle<StepShape_FaceSurface>& theFaceSurface,
                                      StepToTopoDS_Tool&                        theTopoDSTool,
                                      StepToTopoDS_NMTool&                      theTopoDSToolNM,
                                      const StepData_Factors&                   theLocalFactors)
{
  done = true;
  if (theTopoDSTool.IsBound(theFaceSurface))
  {
    myResult = TopoDS::Face(theTopoDSTool.Find(theFaceSurface));
    myError  = StepToTopoDS_TranslateFaceDone;
    done     = true;
    return;
  }

  occ::handle<Transfer_TransientProcess> aMessageHandler = theTopoDSTool.TransientProcess();

  occ::handle<StepGeom_Surface> aStepGeomSurface = theFaceSurface->FaceGeometry();

  if (aStepGeomSurface.IsNull())
  {
    aMessageHandler->AddFail(aStepGeomSurface, " Surface has not been created");
    myError = StepToTopoDS_TranslateFaceOther;
    done    = false;
    return;
  }

  if (theTopoDSToolNM.IsActive() && theTopoDSToolNM.IsBound(aStepGeomSurface))
  {
    TopoDS_Shape anExistingShape = theTopoDSToolNM.Find(aStepGeomSurface);

    anExistingShape.Reverse();
    myResult = anExistingShape;
    myError  = StepToTopoDS_TranslateFaceDone;
    done     = true;
    return;
  }

  if (aStepGeomSurface->IsKind(STANDARD_TYPE(StepGeom_OffsetSurface)))
  {
    aMessageHandler->AddWarning(aStepGeomSurface, " Type OffsetSurface is out of scope of AP 214");
  }

  occ::handle<Geom_Surface> aGeomSurface =
    StepToGeom::MakeSurface(aStepGeomSurface, theLocalFactors);
  if (aGeomSurface.IsNull())
  {
    aMessageHandler->AddFail(aStepGeomSurface, " Surface has not been created");
    myError = StepToTopoDS_TranslateFaceOther;
    done    = false;
    return;
  }

  if (!occ::down_cast<StepGeom_BSplineSurface>(aStepGeomSurface).IsNull())
  {
    occ::handle<Geom_Surface> periodicSurf =
      ShapeAlgo::AlgoContainer()->ConvertToPeriodic(aGeomSurface);
    if (!periodicSurf.IsNull())
    {
      aMessageHandler->AddWarning(aStepGeomSurface, "Surface forced to be periodic");
      aGeomSurface = periodicSurf;
    }
  }

  const bool aSameSense =
    isReversed(aStepGeomSurface) ? !theFaceSurface->SameSense() : theFaceSurface->SameSense();

  theTopoDSTool.AddContinuity(aGeomSurface);

  TopoDS_Face  aResultFace;
  BRep_Builder aFaceBuilder;
  aFaceBuilder.MakeFace(aResultFace, aGeomSurface, Precision::Confusion());

  for (int aBoundIndex = 1; aBoundIndex <= theFaceSurface->NbBounds(); ++aBoundIndex)
  {
    occ::handle<StepShape_FaceBound> aFaceBound = theFaceSurface->BoundsValue(aBoundIndex);
    if (aFaceBound.IsNull())
    {
      continue;
    }
    occ::handle<StepShape_Loop> aFaceLoop = aFaceBound->Bound();
    if (aFaceLoop.IsNull())
    {
      continue;
    }

    if (aFaceLoop->IsKind(STANDARD_TYPE(StepShape_VertexLoop)))
    {

      if ((aGeomSurface->IsKind(STANDARD_TYPE(Geom_SphericalSurface))
           || aGeomSurface->IsKind(STANDARD_TYPE(Geom_BSplineSurface))
           || aGeomSurface->IsKind(STANDARD_TYPE(Geom_SurfaceOfRevolution)))
          && (theFaceSurface->NbBounds() == 1))
      {

        BRepBuilderAPI_MakeFace anAuxiliaryFaceBuilder(aGeomSurface, Precision());
        for (TopoDS_Iterator aFaceIt(anAuxiliaryFaceBuilder); aFaceIt.More(); aFaceIt.Next())
        {
          aFaceBuilder.Add(aResultFace, aFaceIt.Value());
        }
        continue;
      }

      if (aGeomSurface->IsKind(STANDARD_TYPE(Geom_ToroidalSurface)))
      {
        continue;
      }

      occ::handle<StepShape_VertexLoop> aVertexLoop =
        occ::down_cast<StepShape_VertexLoop>(aFaceLoop);
      if (aGeomSurface->IsKind(STANDARD_TYPE(Geom_Plane)))
      {
        aMessageHandler->AddWarning(aVertexLoop, "VertexLoop on plane is ignored");
        continue;
      }

      StepToTopoDS_TranslateVertexLoop aVertexLoopTranslator;
      aVertexLoopTranslator.SetPrecision(Precision());
      aVertexLoopTranslator.SetMaxTol(MaxTol());
      aVertexLoopTranslator.Init(aVertexLoop, theTopoDSTool, theTopoDSToolNM, theLocalFactors);
      if (aVertexLoopTranslator.IsDone())
      {
        aFaceBuilder.Add(aResultFace, aVertexLoopTranslator.Value());
      }
      else
      {
        aMessageHandler->AddWarning(aVertexLoop, " a VertexLoop not mapped to TopoDS");
      }
    }

    else if (aFaceLoop->IsKind(STANDARD_TYPE(StepShape_PolyLoop)))
    {
      occ::handle<StepShape_PolyLoop> aPolyLoop = occ::down_cast<StepShape_PolyLoop>(aFaceLoop);
      aResultFace.Orientation(theFaceSurface->SameSense() ? TopAbs_FORWARD : TopAbs_REVERSED);
      StepToTopoDS_TranslatePolyLoop aPolyLoopTranslator;
      aPolyLoopTranslator.SetPrecision(Precision());
      aPolyLoopTranslator.SetMaxTol(MaxTol());
      aPolyLoopTranslator.Init(aPolyLoop,
                               theTopoDSTool,
                               aGeomSurface,
                               aResultFace,
                               theLocalFactors);
      if (aPolyLoopTranslator.IsDone())
      {
        TopoDS_Wire aPolyLoopWire = TopoDS::Wire(aPolyLoopTranslator.Value());
        aPolyLoopWire.Orientation(aFaceBound->Orientation() ? TopAbs_FORWARD : TopAbs_REVERSED);
        aFaceBuilder.Add(aResultFace, aPolyLoopWire);
      }
      else
      {
        aMessageHandler->AddWarning(aPolyLoop, " a PolyLoop not mapped to TopoDS");
      }
    }

    else if (aFaceLoop->IsKind(STANDARD_TYPE(StepShape_EdgeLoop)))
    {
      StepToTopoDS_TranslateEdgeLoop anEdgeLoopTranslator;
      anEdgeLoopTranslator.SetPrecision(Precision());
      anEdgeLoopTranslator.SetMaxTol(MaxTol());
      anEdgeLoopTranslator.Init(aFaceBound,
                                aResultFace,
                                aGeomSurface,
                                aStepGeomSurface,
                                aSameSense,
                                theTopoDSTool,
                                theTopoDSToolNM,
                                theLocalFactors);

      if (anEdgeLoopTranslator.IsDone())
      {
        TopoDS_Wire anEdgeLoopWire = TopoDS::Wire(anEdgeLoopTranslator.Value());

        if (aFaceBound->Orientation())
        {
          anEdgeLoopWire.Orientation(aSameSense ? TopAbs_FORWARD : TopAbs_REVERSED);
        }
        else
        {
          anEdgeLoopWire.Orientation(aSameSense ? TopAbs_REVERSED : TopAbs_FORWARD);
        }

        aFaceBuilder.Add(aResultFace, anEdgeLoopWire);
      }
      else
      {

        aMessageHandler->AddFail(aFaceLoop, " EdgeLoop not mapped to TopoDS");

        if (aFaceBound->IsKind(STANDARD_TYPE(StepShape_FaceOuterBound)))
        {
          aMessageHandler->AddWarning(theFaceSurface, "No Outer Bound : Face not done");
        }
        continue;
      }
    }
    else
    {

      aMessageHandler->AddFail(aFaceLoop, " Type of loop not yet implemented");
      continue;
    }
  }

  aResultFace.Orientation(theFaceSurface->SameSense() ? TopAbs_FORWARD : TopAbs_REVERSED);
  theTopoDSTool.Bind(theFaceSurface, aResultFace);

  if (theTopoDSToolNM.IsActive())
  {
    theTopoDSToolNM.Bind(aStepGeomSurface, aResultFace);
  }

  myResult = aResultFace;
  myError  = StepToTopoDS_TranslateFaceDone;
  done     = true;
}

void StepToTopoDS_TranslateFace::Init(const occ::handle<StepVisual_TessellatedFace>& theTF,
                                      StepToTopoDS_Tool&                             theTool,
                                      StepToTopoDS_NMTool&                           theNMTool,
                                      const bool              theReadTessellatedWhenNoBRepOnly,
                                      bool&                   theHasGeom,
                                      const StepData_Factors& theLocalFactors)
{
  if (theTF.IsNull())
    return;

  occ::handle<Transfer_TransientProcess> aTP = theTool.TransientProcess();

  BRep_Builder aB;
  TopoDS_Face  aF;

  if (theTF->HasGeometricLink())
  {
    occ::handle<TransferBRep_ShapeBinder> aBinder =
      occ::down_cast<TransferBRep_ShapeBinder>(aTP->Find(theTF->GeometricLink().Face()));
    if (aBinder)
    {
      aF         = aBinder->Face();
      theHasGeom = true;
    }
    if (!aF.IsNull() && !BRep_Tool::Surface(aF).IsNull() && theReadTessellatedWhenNoBRepOnly)
    {

      return;
    }
  }

  if (aF.IsNull())
  {
    aB.MakeFace(aF);
    theHasGeom = false;
  }

  occ::handle<Poly_Triangulation> aMesh;
  if (DeclareAndCast(StepVisual_TriangulatedFace, aTriaF, theTF))
  {
    aMesh = createMesh(aTriaF, theLocalFactors);
  }
  else if (DeclareAndCast(StepVisual_ComplexTriangulatedFace, aCompTriaF, theTF))
  {
    aMesh = createMesh(aCompTriaF, theLocalFactors);
  }
  else
  {
    aTP->AddWarning(theTF, " Triangulated or ComplexTriangulated entity is supported only.");
    return;
  }

  if (aMesh.IsNull())
  {
    aTP->AddWarning(theTF, " Poly triangulation is not set to TopoDS face.");
    return;
  }

  aB.UpdateFace(aF, aMesh);

  if (theNMTool.IsActive())
    theNMTool.Bind(theTF, aF);

  aTP->Bind(theTF, new TransferBRep_ShapeBinder(aF));

  myResult = aF;
  myError  = StepToTopoDS_TranslateFaceDone;
  done     = true;
}

void StepToTopoDS_TranslateFace::Init(const occ::handle<StepVisual_TessellatedSurfaceSet>& theTSS,
                                      StepToTopoDS_Tool&                                   theTool,
                                      StepToTopoDS_NMTool&    theNMTool,
                                      const StepData_Factors& theLocalFactors)
{
  if (theTSS.IsNull())
    return;

  occ::handle<Transfer_TransientProcess> aTP = theTool.TransientProcess();
  BRep_Builder                           aB;
  TopoDS_Face                            aF;
  aB.MakeFace(aF);

  occ::handle<Poly_Triangulation> aMesh;
  if (DeclareAndCast(StepVisual_TriangulatedSurfaceSet, aTriaSS, theTSS))
  {
    aMesh = createMesh(aTriaSS, theLocalFactors);
  }
  else if (DeclareAndCast(StepVisual_ComplexTriangulatedSurfaceSet, aCompTriaSS, theTSS))
  {
    aMesh = createMesh(aCompTriaSS, theLocalFactors);
  }
  else
  {
    aTP->AddWarning(theTSS, " Triangulated or ComplexTriangulated entity is supported only.");
    return;
  }
  if (aMesh.IsNull())
  {
    aTP->AddWarning(theTSS, " Poly triangulation is not set to TopoDS face.");
    return;
  }
  aB.UpdateFace(aF, aMesh);
  if (theNMTool.IsActive())
    theNMTool.Bind(theTSS, aF);

  myResult = aF;
  myError  = StepToTopoDS_TranslateFaceDone;
  done     = true;
}

occ::handle<Poly_Triangulation> StepToTopoDS_TranslateFace::createMesh(
  const occ::handle<StepVisual_TessellatedItem>& theTI,
  const StepData_Factors&                        theLocalFactors) const
{
  return CreatePolyTriangulation(theTI, theLocalFactors);
}

const TopoDS_Shape& StepToTopoDS_TranslateFace::Value() const
{
  StdFail_NotDone_Raise_if(!done, "StepToTopoDS_TranslateFace::Value() - no result");
  return myResult;
}

StepToTopoDS_TranslateFaceError StepToTopoDS_TranslateFace::Error() const
{
  return myError;
}
