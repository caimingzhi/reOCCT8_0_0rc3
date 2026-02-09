

#include "XSAlgo_ShapeProcessor.hpp"

#include <BRepBuilderAPI_MakeEdge.hpp>
#include <BRepTools_ReShape.hpp>
#include <BRep_Builder.hpp>
#include <BRep_Tool.hpp>
#include <Geom_Curve.hpp>
#include <Interface_Static.hpp>
#include <Message_Msg.hpp>
#include <NCollection_List.hpp>
#include <Resource_Manager.hpp>
#include <ShapeAnalysis_Edge.hpp>
#include <ShapeBuild_Edge.hpp>
#include <ShapeExtend_MsgRegistrator.hpp>
#include <ShapeFix_Edge.hpp>
#include <ShapeProcess_ShapeContext.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TransferBRep.hpp>
#include <TransferBRep_ShapeBinder.hpp>
#include <TransferBRep_ShapeMapper.hpp>
#include <Transfer_FinderProcess.hpp>
#include <Transfer_TransientListBinder.hpp>
#include <Transfer_TransientProcess.hpp>
#include <UnitsMethods.hpp>

#include <sstream>
#include <unordered_set>

XSAlgo_ShapeProcessor::XSAlgo_ShapeProcessor(
  const XSAlgo_ShapeProcessor::ParameterMap& theParameters,
  const DE_ShapeFixParameters&               theShapeFixParameters)
    : myParameters(theParameters)
{
  FillParameterMap(theShapeFixParameters, false, myParameters);
}

XSAlgo_ShapeProcessor::XSAlgo_ShapeProcessor(const DE_ShapeFixParameters& theParameters)
{
  XSAlgo_ShapeProcessor::ParameterMap aMap;
  FillParameterMap(theParameters, false, aMap);
  myParameters = aMap;
}

TopoDS_Shape XSAlgo_ShapeProcessor::ProcessShape(const TopoDS_Shape&                  theShape,
                                                 const ShapeProcess::OperationsFlags& theOperations,
                                                 const Message_ProgressRange&         theProgress)
{
  if (theShape.IsNull())
  {
    return theShape;
  }

  initializeContext(theShape);
  return ShapeProcess::Perform(myContext, theOperations, theProgress) ? myContext->Result()
                                                                      : theShape;
}

void XSAlgo_ShapeProcessor::initializeContext(const TopoDS_Shape& theShape)
{
  myContext = new ShapeProcess_ShapeContext(theShape, nullptr);
  for (XSAlgo_ShapeProcessor::ParameterMap::Iterator aParameterIter(myParameters);
       aParameterIter.More();
       aParameterIter.Next())
  {
    myContext->ResourceManager()->SetResource(aParameterIter.Key().ToCString(),
                                              aParameterIter.Value().ToCString());
  }

  TCollection_AsciiString aResult;
  if (myParameters.Find("DetalizationLevel", aResult) && aResult.IsIntegerValue())
  {
    const TopAbs_ShapeEnum aDetalizationLevel =
      static_cast<TopAbs_ShapeEnum>(aResult.IntegerValue());
    myContext->SetDetalisation(aDetalizationLevel);
  }

  if (myParameters.Find("NonManifold", aResult) && aResult.IsIntegerValue())
  {
    const bool aNonManifold = static_cast<bool>(aResult.IntegerValue());
    myContext->SetNonManifold(aNonManifold);
  }
}

void XSAlgo_ShapeProcessor::addMessages(const occ::handle<ShapeExtend_MsgRegistrator>& theMessages,
                                        const TopoDS_Shape&                            theShape,
                                        occ::handle<Transfer_Binder>&                  theBinder)
{
  if (theMessages.IsNull())
  {
    return;
  }

  const NCollection_List<Message_Msg>* aShapeMessages = theMessages->MapShape().Seek(theShape);
  if (!aShapeMessages)
  {
    return;
  }

  for (NCollection_List<Message_Msg>::Iterator aMsgIter(*aShapeMessages); aMsgIter.More();
       aMsgIter.Next())
  {
    const Message_Msg& aMessage = aMsgIter.Value();
    theBinder->AddWarning(TCollection_AsciiString(aMessage.Value()).ToCString(),
                          TCollection_AsciiString(aMessage.Original()).ToCString());
  }
}

void XSAlgo_ShapeProcessor::MergeShapeTransferInfo(
  const occ::handle<Transfer_TransientProcess>& theTransientProcess,
  const NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>&
                                                 theModifiedShapesMap,
  const int                                      theFirstTPItemIndex,
  const occ::handle<ShapeExtend_MsgRegistrator>& theMessages)
{
  if (theModifiedShapesMap.IsEmpty())
  {
    return;
  }
  const bool aToPrint = !theMessages.IsNull() && !theMessages->MapShape().IsEmpty();
  for (int i = std::max(theFirstTPItemIndex, 1); i <= theTransientProcess->NbMapped(); ++i)
  {
    occ::handle<TransferBRep_ShapeBinder> aShapeBinder =
      occ::down_cast<TransferBRep_ShapeBinder>(theTransientProcess->MapItem(i));
    if (aShapeBinder.IsNull() || aShapeBinder->Result().IsNull())
    {
      continue;
    }

    const TopoDS_Shape anOriginalShape = aShapeBinder->Result();

    if (theModifiedShapesMap.IsBound(anOriginalShape))
    {
      aShapeBinder->SetResult(theModifiedShapesMap.Find(anOriginalShape));
    }
    else if (!anOriginalShape.Location().IsIdentity())
    {
      TopLoc_Location aNullLoc;
      TopoDS_Shape    aTemporaryShape = anOriginalShape.Located(aNullLoc);
      if (theModifiedShapesMap.IsBound(aTemporaryShape))
      {
        aShapeBinder->SetResult(theModifiedShapesMap.Find(aTemporaryShape));
      }
    }
    else
    {

      BRepTools_ReShape aReShaper;
      bool              aHasModifiedEdges = false;

      for (TopExp_Explorer anExpSE(anOriginalShape, TopAbs_EDGE); anExpSE.More(); anExpSE.Next())
      {
        if (theModifiedShapesMap.IsBound(anExpSE.Current()))
        {
          aHasModifiedEdges           = true;
          TopoDS_Shape aModifiedShape = theModifiedShapesMap.Find(anExpSE.Current());
          aReShaper.Replace(anExpSE.Current(), aModifiedShape);
        }
      }

      if (aHasModifiedEdges)
      {
        TopoDS_Shape aReshapedShape = aReShaper.Apply(anOriginalShape);
        aShapeBinder->SetResult(aReshapedShape);
      }
    }

    if (aToPrint)
    {
      addMessages(theMessages, anOriginalShape, aShapeBinder);
    }
  }
}

void XSAlgo_ShapeProcessor::MergeTransferInfo(
  const occ::handle<Transfer_TransientProcess>& theTransientProcess,
  const int                                     theFirstTPItemIndex) const
{
  if (myContext.IsNull())
  {
    return;
  }
  return MergeShapeTransferInfo(theTransientProcess,
                                myContext->Map(),
                                theFirstTPItemIndex,
                                myContext->Messages());
}

void XSAlgo_ShapeProcessor::MergeShapeTransferInfo(
  const occ::handle<Transfer_FinderProcess>& theFinderProcess,
  const NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>&
                                                 theModifiedShapesMap,
  const occ::handle<ShapeExtend_MsgRegistrator>& theMessages)
{
  if (theModifiedShapesMap.IsEmpty())
  {
    return;
  }
  const bool aToPrint = !theMessages.IsNull() && !theMessages->MapShape().IsEmpty();

  for (NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>::Iterator
         ShapeShapeIterator(theModifiedShapesMap);
       ShapeShapeIterator.More();
       ShapeShapeIterator.Next())
  {
    const TopoDS_Shape anOriginalShape = ShapeShapeIterator.Key();
    const TopoDS_Shape aResultShape    = ShapeShapeIterator.Value();

    occ::handle<TransferBRep_ShapeMapper> aResultMapper =
      TransferBRep::ShapeMapper(theFinderProcess, aResultShape);
    occ::handle<Transfer_Binder> aResultBinder = theFinderProcess->Find(aResultMapper);

    if (aResultBinder.IsNull())
    {
      aResultBinder = new TransferBRep_ShapeBinder(aResultShape);

      if (anOriginalShape.ShapeType() > aResultShape.ShapeType())
      {
        TopoDS_Shape                              aSubShape;
        occ::handle<Transfer_TransientListBinder> aTransientListBinder =
          new Transfer_TransientListBinder;
        for (TopoDS_Iterator aSubShapeIter(aResultShape); aSubShapeIter.More();
             aSubShapeIter.Next())
        {
          const TopoDS_Shape           aCurrentSubShape = aSubShapeIter.Value();
          occ::handle<Transfer_Finder> aSubShapeMapper =
            TransferBRep::ShapeMapper(theFinderProcess, aCurrentSubShape);
          if (aSubShapeMapper.IsNull())
          {
            continue;
          }

          occ::handle<Standard_Transient> aTransientResult =
            theFinderProcess->FindTransient(aSubShapeMapper);
          if (aTransientResult.IsNull())
          {
            continue;
          }
          aTransientListBinder->AddResult(aTransientResult);
          aSubShape = aCurrentSubShape;
        }
        if (aTransientListBinder->NbTransients() == 1)
        {
          aResultBinder = new TransferBRep_ShapeBinder(aSubShape);
        }
        else if (aTransientListBinder->NbTransients() > 1)
        {
          aResultBinder->AddResult(aTransientListBinder);
        }
      }
    }

    occ::handle<TransferBRep_ShapeMapper> anOriginalMapper =
      TransferBRep::ShapeMapper(theFinderProcess, anOriginalShape);
    occ::handle<Transfer_Binder> anOriginalBinder = theFinderProcess->Find(anOriginalMapper);
    if (anOriginalBinder.IsNull())
    {
      theFinderProcess->Bind(anOriginalMapper, aResultBinder);
    }
    else
    {
      anOriginalBinder->AddResult(aResultBinder);
    }

    if (aToPrint)
    {
      addMessages(theMessages, anOriginalShape, aResultBinder);
    }
  }
}

void XSAlgo_ShapeProcessor::MergeTransferInfo(
  const occ::handle<Transfer_FinderProcess>& theFinderProcess) const
{
  if (myContext.IsNull())
  {
    return;
  }
  return MergeShapeTransferInfo(theFinderProcess, myContext->Map(), myContext->Messages());
}

TopoDS_Edge XSAlgo_ShapeProcessor::MakeEdgeOnCurve(const TopoDS_Edge& aSourceEdge)
{
  TopoDS_Edge aResult;

  occ::handle<Geom_Curve> aSourceGeomCurve;
  double                  aStartParam;
  double                  anEndParam;
  ShapeAnalysis_Edge      anEdgeAnalyzer;
  if (!anEdgeAnalyzer.Curve3d(aSourceEdge, aSourceGeomCurve, aStartParam, anEndParam, false))
  {
    return aResult;
  }
  const gp_Pnt            aCurveStartPt = aSourceGeomCurve->Value(aStartParam);
  const gp_Pnt            aCurveEndPt   = aSourceGeomCurve->Value(anEndParam);
  BRepBuilderAPI_MakeEdge anEdgeMaker(aSourceGeomCurve,
                                      aCurveStartPt,
                                      aCurveEndPt,
                                      aStartParam,
                                      anEndParam);
  ShapeBuild_Edge         SBE;
  SBE.SetRange3d(anEdgeMaker, aStartParam, anEndParam);
  aResult = anEdgeMaker.Edge();
  return aResult;
}

bool XSAlgo_ShapeProcessor::CheckPCurve(const TopoDS_Edge& theEdge,
                                        const TopoDS_Face& theFace,
                                        const double       thePrecision,
                                        const bool         theIsSeam)
{
  ShapeAnalysis_Edge anEdgeAnalyzer;

  double                    aCurve2DParam1;
  double                    aCurve2DParam2;
  occ::handle<Geom2d_Curve> aCurve2D;
  if (!anEdgeAnalyzer.PCurve(theEdge, theFace, aCurve2D, aCurve2DParam1, aCurve2DParam2, false))
  {
    return false;
  }

  occ::handle<Geom_Surface> aSurface = BRep_Tool::Surface(theFace);
  double                    aFaceSurfaceU1, aFaceSurfaceU2, aFaceSurfaceV1, aFaceSurfaceV2;
  aSurface->Bounds(aFaceSurfaceU1, aFaceSurfaceU2, aFaceSurfaceV1, aFaceSurfaceV2);
  const gp_Pnt2d aCurve2DPoint1 = aCurve2D->Value(aCurve2DParam1);
  const gp_Pnt2d aCurve2DPoint2 = aCurve2D->Value(aCurve2DParam2);

  const double anEdgeSpanX = std::abs(aCurve2DPoint1.X() - aCurve2DPoint2.X());
  const double anEdgeSpanY = std::abs(aCurve2DPoint1.Y() - aCurve2DPoint2.Y());

  if (anEdgeSpanX / 8. > (aFaceSurfaceU2 / 6. - aFaceSurfaceU1 / 6.)
      || anEdgeSpanY / 8. > (aFaceSurfaceV2 / 6. - aFaceSurfaceV1 / 6.))
  {
    ShapeBuild_Edge().RemovePCurve(theEdge, theFace);
    return false;
  }

  occ::handle<Geom_Curve> aCurve3D;
  double                  aCurve3DParam1;
  double                  aCurve3DParam2;
  anEdgeAnalyzer.Curve3d(theEdge, aCurve3D, aCurve3DParam1, aCurve3DParam2, false);

  const gp_Pnt        aCurve3DPoint1 = aSurface->Value(aCurve2DPoint1.X(), aCurve2DPoint1.Y());
  const gp_Pnt        aCurve3DPoint2 = aSurface->Value(aCurve2DPoint2.X(), aCurve2DPoint2.Y());
  const TopoDS_Vertex aVertex1       = TopExp::FirstVertex(theEdge);
  const TopoDS_Vertex aVertex2       = TopExp::LastVertex(theEdge);
  const gp_Pnt        aPV1 =
    (aCurve3D.IsNull() ? BRep_Tool::Pnt(aVertex1) : aCurve3D->Value(aCurve3DParam1));
  const gp_Pnt aPV2 =
    (aCurve3D.IsNull() ? BRep_Tool::Pnt(aVertex2) : aCurve3D->Value(aCurve3DParam2));
  const double aDist11 = aPV1.Distance(aCurve3DPoint1);
  const double aDist22 = aPV2.Distance(aCurve3DPoint2);

  if ((aDist11 > thePrecision) || (aDist22 > thePrecision))
  {
    ShapeBuild_Edge().RemovePCurve(theEdge, theFace);
    return false;
  }

  if (aCurve3D.IsNull())
  {
    return false;
  }
  TopoDS_Edge aTmpEdge = MakeEdgeOnCurve(theEdge);

  BRep_Builder              aBuilder;
  occ::handle<Geom2d_Curve> aSeamPCurve;
  if (theIsSeam)
  {
    double      aSeamPCurveParam1;
    double      aSeamPCurveParam2;
    TopoDS_Edge aReversedEdge = TopoDS::Edge(theEdge.Reversed());
    if (!anEdgeAnalyzer
           .PCurve(aReversedEdge, theFace, aSeamPCurve, aSeamPCurveParam1, aSeamPCurveParam2, false)
        || aSeamPCurve == aCurve2D)
    {
      aSeamPCurve = occ::down_cast<Geom2d_Curve>(aCurve2D->Copy());
    }
    aBuilder.UpdateEdge(aTmpEdge, aCurve2D, aSeamPCurve, theFace, 0.);
  }
  else
  {
    aBuilder.UpdateEdge(aTmpEdge, aCurve2D, theFace, 0.);
  }
  aBuilder.Range(aTmpEdge, theFace, aCurve2DParam1, aCurve2DParam2);
  aBuilder.SameRange(aTmpEdge, false);
  if (Interface_Static::IVal("read.stdsameparameter.mode"))
  {
    aBuilder.SameParameter(aTmpEdge, false);
  }

  occ::handle<ShapeFix_Edge> anEdgeFixer = new ShapeFix_Edge;
  anEdgeFixer->FixSameParameter(aTmpEdge);
  double aTolerance         = BRep_Tool::Tolerance(aTmpEdge);
  bool   aSameRangeFlag     = BRep_Tool::SameRange(aTmpEdge);
  bool   aSameParameterFlag = BRep_Tool::SameParameter(aTmpEdge);

  if (aTolerance > std::min(1., 2. * thePrecision) || !aSameRangeFlag)
  {

    TopoDS_Edge anEdgePr = MakeEdgeOnCurve(theEdge);
    anEdgeFixer->FixAddPCurve(anEdgePr, theFace, theIsSeam, thePrecision);
    anEdgeFixer->FixSameParameter(anEdgePr);
    const double aTolerancePr = BRep_Tool::Tolerance(anEdgePr);

    if (aTolerancePr < aTolerance || !aSameRangeFlag)
    {
      aSameRangeFlag     = BRep_Tool::SameRange(anEdgePr);
      aSameParameterFlag = BRep_Tool::SameParameter(anEdgePr);
      aTolerance         = aTolerancePr;
      aTmpEdge           = anEdgePr;
    }
  }

  anEdgeAnalyzer.PCurve(aTmpEdge, theFace, aCurve2D, aCurve2DParam1, aCurve2DParam2, false);
  if (theIsSeam)
  {
    double      aReversedTmpEdgeParam1;
    double      aReversedTmpEdgeParam2;
    TopoDS_Edge aReversedTmpEdge = TopoDS::Edge(aTmpEdge.Reversed());
    anEdgeAnalyzer.PCurve(aReversedTmpEdge,
                          theFace,
                          aSeamPCurve,
                          aReversedTmpEdgeParam1,
                          aReversedTmpEdgeParam2,
                          false);
    if (theEdge.Orientation() == TopAbs_REVERSED)
    {
      aBuilder.UpdateEdge(theEdge, aSeamPCurve, aCurve2D, theFace, aTolerance);
    }
    else
    {
      aBuilder.UpdateEdge(theEdge, aCurve2D, aSeamPCurve, theFace, aTolerance);
    }
  }
  else
  {
    aBuilder.UpdateEdge(theEdge, aCurve2D, theFace, aTolerance);
  }

  aBuilder.UpdateVertex(aVertex1, aTolerance);
  aBuilder.UpdateVertex(aVertex2, aTolerance);
  aBuilder.Range(theEdge, theFace, aCurve2DParam1, aCurve2DParam2);
  if (BRep_Tool::SameRange(theEdge))
  {
    aBuilder.SameRange(theEdge, aSameRangeFlag);
  }
  if (BRep_Tool::SameParameter(theEdge))
  {
    aBuilder.SameParameter(theEdge, aSameParameterFlag);
  }

  return true;
}

XSAlgo_ShapeProcessor::ProcessingData XSAlgo_ShapeProcessor::ReadProcessingData(
  const TCollection_AsciiString& theFileResourceName,
  const TCollection_AsciiString& theScopeResourceName)
{
  const char* aFileName = Interface_Static::CVal(theFileResourceName.ToCString());
  occ::handle<ShapeProcess_ShapeContext> aContext =
    new ShapeProcess_ShapeContext(TopoDS_Shape(), aFileName);
  if (!aContext->ResourceManager()->IsInitialized())
  {

    Interface_Static::FillMap(aContext->ResourceManager()->GetMap());
  }
  const TCollection_AsciiString aScope = Interface_Static::CVal(theScopeResourceName.ToCString());

  XSAlgo_ShapeProcessor::ParameterMap                                          aResultParameters;
  ShapeProcess::OperationsFlags                                                aResultFlags;
  const NCollection_DataMap<TCollection_AsciiString, TCollection_AsciiString>& aMap =
    aContext->ResourceManager()->GetMap();

  for (NCollection_DataMap<TCollection_AsciiString, TCollection_AsciiString>::Iterator anIter(aMap);
       anIter.More();
       anIter.Next())
  {
    TCollection_AsciiString aKey = anIter.Key();
    if (!aKey.StartsWith(aScope))
    {

      continue;
    }

    aKey = aKey.SubString(aScope.Length() + 2, aKey.Length());

    if (aKey.IsEqual("exec.op"))
    {

      int                           aTokenCount = 1;
      TCollection_AsciiString       aToken;
      const TCollection_AsciiString aSeparators(" \t,;");

      while (!(aToken = anIter.Value().Token(aSeparators.ToCString(), aTokenCount)).IsEmpty())
      {
        std::pair<ShapeProcess::Operation, bool> anOperationFlag =
          ShapeProcess::ToOperationFlag(aToken.ToCString());
        if (anOperationFlag.second)
        {
          aResultFlags.set(anOperationFlag.first);
        }
        aTokenCount++;
      }
    }
    else
    {
      aResultParameters.Bind(aKey, anIter.Value());
    }
  }
  return {aResultParameters, aResultFlags};
}

void XSAlgo_ShapeProcessor::FillParameterMap(const DE_ShapeFixParameters&         theParameters,
                                             const bool                           theIsReplace,
                                             XSAlgo_ShapeProcessor::ParameterMap& theMap)
{
  SetParameter("FixShape.Tolerance3d", theParameters.Tolerance3d, theIsReplace, theMap);
  SetParameter("FixShape.MaxTolerance3d", theParameters.MaxTolerance3d, theIsReplace, theMap);
  SetParameter("FixShape.MinTolerance3d", theParameters.MinTolerance3d, theIsReplace, theMap);
  SetParameter("DetalizationLevel",
               TCollection_AsciiString(static_cast<int>(theParameters.DetalizationLevel)),
               theIsReplace,
               theMap);
  SetParameter("NonManifold",
               TCollection_AsciiString(static_cast<int>(theParameters.NonManifold)),
               theIsReplace,
               theMap);
  SetParameter("FixShape.FixFreeShellMode", theParameters.FixFreeShellMode, theIsReplace, theMap);
  SetParameter("FixShape.FixFreeFaceMode", theParameters.FixFreeFaceMode, theIsReplace, theMap);
  SetParameter("FixShape.FixFreeWireMode", theParameters.FixFreeWireMode, theIsReplace, theMap);
  SetParameter("FixShape.FixSameParameterMode",
               theParameters.FixSameParameterMode,
               theIsReplace,
               theMap);
  SetParameter("FixShape.FixSolidMode", theParameters.FixSolidMode, theIsReplace, theMap);
  SetParameter("FixShape.FixShellOrientationMode",
               theParameters.FixShellOrientationMode,
               theIsReplace,
               theMap);
  SetParameter("FixShape.CreateOpenSolidMode",
               theParameters.CreateOpenSolidMode,
               theIsReplace,
               theMap);
  SetParameter("FixShape.FixShellMode", theParameters.FixShellMode, theIsReplace, theMap);
  SetParameter("FixShape.FixFaceOrientationMode",
               theParameters.FixFaceOrientationMode,
               theIsReplace,
               theMap);
  SetParameter("FixShape.FixFaceMode", theParameters.FixFaceMode, theIsReplace, theMap);
  SetParameter("FixShape.FixWireMode", theParameters.FixWireMode, theIsReplace, theMap);
  SetParameter("FixShape.FixOrientationMode",
               theParameters.FixOrientationMode,
               theIsReplace,
               theMap);
  SetParameter("FixShape.FixAddNaturalBoundMode",
               theParameters.FixAddNaturalBoundMode,
               theIsReplace,
               theMap);
  SetParameter("FixShape.FixMissingSeamMode",
               theParameters.FixMissingSeamMode,
               theIsReplace,
               theMap);
  SetParameter("FixShape.FixSmallAreaWireMode",
               theParameters.FixSmallAreaWireMode,
               theIsReplace,
               theMap);
  SetParameter("FixShape.RemoveSmallAreaFaceMode",
               theParameters.RemoveSmallAreaFaceMode,
               theIsReplace,
               theMap);
  SetParameter("FixShape.FixIntersectingWiresMode",
               theParameters.FixIntersectingWiresMode,
               theIsReplace,
               theMap);
  SetParameter("FixShape.FixLoopWiresMode", theParameters.FixLoopWiresMode, theIsReplace, theMap);
  SetParameter("FixShape.FixSplitFaceMode", theParameters.FixSplitFaceMode, theIsReplace, theMap);
  SetParameter("FixShape.AutoCorrectPrecisionMode",
               theParameters.AutoCorrectPrecisionMode,
               theIsReplace,
               theMap);
  SetParameter("FixShape.ModifyTopologyMode",
               theParameters.ModifyTopologyMode,
               theIsReplace,
               theMap);
  SetParameter("FixShape.ModifyGeometryMode",
               theParameters.ModifyGeometryMode,
               theIsReplace,
               theMap);
  SetParameter("FixShape.ClosedWireMode", theParameters.ClosedWireMode, theIsReplace, theMap);
  SetParameter("FixShape.PreferencePCurveMode",
               theParameters.PreferencePCurveMode,
               theIsReplace,
               theMap);
  SetParameter("FixShape.FixReorderMode", theParameters.FixReorderMode, theIsReplace, theMap);
  SetParameter("FixShape.FixSmallMode", theParameters.FixSmallMode, theIsReplace, theMap);
  SetParameter("FixShape.FixConnectedMode", theParameters.FixConnectedMode, theIsReplace, theMap);
  SetParameter("FixShape.FixEdgeCurvesMode", theParameters.FixEdgeCurvesMode, theIsReplace, theMap);
  SetParameter("FixShape.FixDegeneratedMode",
               theParameters.FixDegeneratedMode,
               theIsReplace,
               theMap);
  SetParameter("FixShape.FixLackingMode", theParameters.FixLackingMode, theIsReplace, theMap);
  SetParameter("FixShape.FixSelfIntersectionMode",
               theParameters.FixSelfIntersectionMode,
               theIsReplace,
               theMap);
  SetParameter("FixShape.RemoveLoopMode", theParameters.RemoveLoopMode, theIsReplace, theMap);
  SetParameter("FixShape.FixReversed2dMode", theParameters.FixReversed2dMode, theIsReplace, theMap);
  SetParameter("FixShape.FixRemovePCurveMode",
               theParameters.FixRemovePCurveMode,
               theIsReplace,
               theMap);
  SetParameter("FixShape.FixRemoveCurve3dMode",
               theParameters.FixRemoveCurve3dMode,
               theIsReplace,
               theMap);
  SetParameter("FixShape.FixAddPCurveMode", theParameters.FixAddPCurveMode, theIsReplace, theMap);
  SetParameter("FixShape.FixAddCurve3dMode", theParameters.FixAddCurve3dMode, theIsReplace, theMap);
  SetParameter("FixShape.FixSeamMode", theParameters.FixSeamMode, theIsReplace, theMap);
  SetParameter("FixShape.FixShiftedMode", theParameters.FixShiftedMode, theIsReplace, theMap);
  SetParameter("FixShape.FixEdgeSameParameterMode",
               theParameters.FixEdgeSameParameterMode,
               theIsReplace,
               theMap);
  SetParameter("FixShape.FixNotchedEdgesMode",
               theParameters.FixNotchedEdgesMode,
               theIsReplace,
               theMap);
  SetParameter("FixShape.FixTailMode", theParameters.FixTailMode, theIsReplace, theMap);
  SetParameter("FixShape.MaxTailAngle", theParameters.MaxTailAngle, theIsReplace, theMap);
  SetParameter("FixShape.MaxTailWidth", theParameters.MaxTailWidth, theIsReplace, theMap);
  SetParameter("FixShape.FixSelfIntersectingEdgeMode",
               theParameters.FixSelfIntersectingEdgeMode,
               theIsReplace,
               theMap);
  SetParameter("FixShape.FixIntersectingEdgesMode",
               theParameters.FixIntersectingEdgesMode,
               theIsReplace,
               theMap);
  SetParameter("FixShape.FixNonAdjacentIntersectingEdgesMode",
               theParameters.FixNonAdjacentIntersectingEdgesMode,
               theIsReplace,
               theMap);
  SetParameter("FixShape.FixVertexPositionMode",
               theParameters.FixVertexPositionMode,
               theIsReplace,
               theMap);
  SetParameter("FixShape.FixVertexToleranceMode",
               theParameters.FixVertexToleranceMode,
               theIsReplace,
               theMap);
}

void XSAlgo_ShapeProcessor::SetShapeFixParameters(
  const DE_ShapeFixParameters&               theParameters,
  const XSAlgo_ShapeProcessor::ParameterMap& theAdditionalParameters,
  XSAlgo_ShapeProcessor::ParameterMap&       theTargetParameterMap)
{
  theTargetParameterMap.Clear();
  XSAlgo_ShapeProcessor::FillParameterMap(theParameters, true, theTargetParameterMap);
  for (XSAlgo_ShapeProcessor::ParameterMap::Iterator aParamIter(theAdditionalParameters);
       aParamIter.More();
       aParamIter.Next())
  {
    if (!theTargetParameterMap.IsBound(aParamIter.Key()))
    {
      theTargetParameterMap.Bind(aParamIter.Key(), aParamIter.Value());
    }
  }
}

void XSAlgo_ShapeProcessor::SetParameter(const char*                          theKey,
                                         const DE_ShapeFixParameters::FixMode theValue,
                                         const bool                           theIsReplace,
                                         XSAlgo_ShapeProcessor::ParameterMap& theMap)
{
  SetParameter(
    theKey,
    TCollection_AsciiString(static_cast<int>(
      static_cast<std::underlying_type<DE_ShapeFixParameters::FixMode>::type>(theValue))),
    theIsReplace,
    theMap);
}

void XSAlgo_ShapeProcessor::SetParameter(const char*                          theKey,
                                         const double                         theValue,
                                         const bool                           theIsReplace,
                                         XSAlgo_ShapeProcessor::ParameterMap& theMap)
{
  SetParameter(theKey, TCollection_AsciiString(theValue), theIsReplace, theMap);
}

void XSAlgo_ShapeProcessor::SetParameter(const char*                          theKey,
                                         const TCollection_AsciiString&       theValue,
                                         const bool                           theIsReplace,
                                         XSAlgo_ShapeProcessor::ParameterMap& theMap)
{
  if (theIsReplace)
  {
    theMap.Bind(theKey, theValue);
  }
  else
  {
    if (!theMap.IsBound(theKey))
    {
      theMap.Bind(theKey, theValue);
    }
  }
}

void XSAlgo_ShapeProcessor::PrepareForTransfer()
{
  UnitsMethods::SetCasCadeLengthUnit(Interface_Static::IVal("xstep.cascade.unit"));
}
