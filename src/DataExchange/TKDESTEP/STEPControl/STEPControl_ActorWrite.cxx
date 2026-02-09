

#include <BRep_Builder.hpp>
#include <BRep_Tool.hpp>
#include <BRep_TEdge.hpp>
#include <BRepTools_Modifier.hpp>
#include <Geom_Curve.hpp>
#include <Geom_Line.hpp>
#include <Geom_Plane.hpp>
#include <Geom_Surface.hpp>
#include <GeomToStep_MakeAxis2Placement3d.hpp>
#include <GeomToStep_MakeCartesianTransformationOperator.hpp>
#include <MoniTool_Macros.hpp>
#include <Interface_MSG.hpp>
#include <Message_ProgressScope.hpp>
#include <ShapeAnalysis_ShapeTolerance.hpp>
#include <ShapeProcess_ShapeContext.hpp>
#include <Standard_Type.hpp>
#include <StepBasic_ApplicationProtocolDefinition.hpp>
#include <StepBasic_Product.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <STEPConstruct_Assembly.hpp>
#include <STEPConstruct_Part.hpp>
#include <STEPConstruct_UnitContext.hpp>
#include <STEPControl_ActorWrite.hpp>
#include <STEPControl_StepModelType.hpp>
#include <StepData_StepModel.hpp>
#include <StepGeom_Axis2Placement3d.hpp>
#include <StepGeom_CartesianTransformationOperator3d.hpp>
#include <StepGeom_GeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx.hpp>
#include <StepGeom_Point.hpp>
#include <StepRepr_ShapeRepresentationRelationship.hpp>
#include <StepShape_AdvancedBrepShapeRepresentation.hpp>
#include <StepShape_BrepWithVoids.hpp>
#include <StepShape_FacetedBrep.hpp>
#include <StepShape_FacetedBrepAndBrepWithVoids.hpp>
#include <StepShape_FacetedBrepShapeRepresentation.hpp>
#include <StepShape_GeometricallyBoundedWireframeShapeRepresentation.hpp>
#include <StepShape_GeometricCurveSet.hpp>
#include <StepShape_GeometricSetSelect.hpp>
#include <StepShape_ManifoldSolidBrep.hpp>
#include <StepShape_ManifoldSurfaceShapeRepresentation.hpp>
#include <StepShape_NonManifoldSurfaceShapeRepresentation.hpp>
#include <StepShape_ShapeDefinitionRepresentation.hpp>
#include <StepShape_ShapeRepresentation.hpp>
#include <StepShape_ShellBasedSurfaceModel.hpp>
#include <StepShape_VertexPoint.hpp>
#include <StepVisual_TessellatedItem.hpp>
#include <StepVisual_TessellatedShapeRepresentation.hpp>
#include <StepVisual_TessellatedSolid.hpp>
#include <TCollection_HAsciiString.hpp>
#include <Standard_Transient.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <TopExp.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Compound.hpp>
#include <TopoDS_Iterator.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Solid.hpp>
#include <TopoDSToStep_FacetedTool.hpp>
#include <TopoDSToStep_MakeBrepWithVoids.hpp>
#include <TopoDSToStep_MakeFacetedBrep.hpp>
#include <TopoDSToStep_MakeFacetedBrepAndBrepWithVoids.hpp>
#include <TopoDSToStep_MakeGeometricCurveSet.hpp>
#include <TopoDSToStep_MakeManifoldSolidBrep.hpp>
#include <TopoDSToStep_MakeShellBasedSurfaceModel.hpp>
#include <TopoDSToStep_MakeStepVertex.hpp>
#include <TopoDSToStep_Tool.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <Transfer_Binder.hpp>
#include <Transfer_Finder.hpp>
#include <Transfer_FinderProcess.hpp>
#include <Transfer_SimpleBinderOfTransient.hpp>
#include <TransferBRep.hpp>
#include <TransferBRep_ShapeMapper.hpp>
#include <UnitsMethods.hpp>
#include <XSAlgo.hpp>
#include <XSAlgo_ShapeProcessor.hpp>

IMPLEMENT_STANDARD_RTTIEXT(STEPControl_ActorWrite, Transfer_ActorOfFinderProcess)

#ifdef OCCT_DEBUG
static void DumpWhatIs(const TopoDS_Shape& S)
{

  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> aMapOfShape;
  aMapOfShape.Add(S);
  NCollection_List<TopoDS_Shape> aListOfShape;
  aListOfShape.Append(S);
  NCollection_List<TopoDS_Shape>::Iterator itL(aListOfShape);
  int nbSolids = 0, nbShells = 0, nbOpenShells = 0, nbFaces = 0, nbWires = 0, nbEdges = 0,
      nbVertexes = 0;

  for (; itL.More(); itL.Next())
  {
    TopoDS_Iterator it(itL.Value());
    for (; it.More(); it.Next())
    {
      TopoDS_Shape aSubShape = it.Value();
      if (!aMapOfShape.Add(aSubShape))
        continue;
      aListOfShape.Append(aSubShape);
      if (aSubShape.ShapeType() == TopAbs_SOLID)
        nbSolids++;
      if (aSubShape.ShapeType() == TopAbs_SHELL)
      {
        if (!aSubShape.Closed())
          nbOpenShells++;
        nbShells++;
      }
      if (aSubShape.ShapeType() == TopAbs_FACE)
        nbFaces++;
      if (aSubShape.ShapeType() == TopAbs_WIRE)
        nbWires++;
      if (aSubShape.ShapeType() == TopAbs_EDGE)
        nbEdges++;
      if (aSubShape.ShapeType() == TopAbs_VERTEX)
        nbVertexes++;
    }
  }

  std::cout << "//What is?// NB SOLIDS: " << nbSolids << std::endl;
  std::cout << "//What is?// NB SHELLS: " << nbShells << std::endl;
  std::cout << "//What is?//    OPEN SHELLS: " << nbOpenShells << std::endl;
  std::cout << "//What is?//    CLOSED SHELLS: " << nbShells - nbOpenShells << std::endl;
  std::cout << "//What is?// NB FACES: " << nbFaces << std::endl;
  std::cout << "//What is?// NB WIRES: " << nbWires << std::endl;
  std::cout << "//What is?// NB EDGES: " << nbEdges << std::endl;
  std::cout << "//What is?// NB VERTEXES: " << nbVertexes << std::endl;
}
#endif

static bool hasGeometry(const TopoDS_Shape& theShape)
{
  TopAbs_ShapeEnum aType = theShape.ShapeType();

  if (aType == TopAbs_VERTEX)
  {
    return true;
  }
  else if (aType == TopAbs_EDGE)
  {
    occ::handle<BRep_TEdge> TE = occ::down_cast<BRep_TEdge>(theShape.TShape());
    NCollection_List<occ::handle<BRep_CurveRepresentation>>::Iterator itrc(TE->Curves());

    while (itrc.More())
    {
      const occ::handle<BRep_CurveRepresentation>& CR = itrc.Value();
      bool aHasGeometry = (CR->IsCurve3D() && !CR->Curve3D().IsNull()) || CR->IsCurveOnSurface()
                          || CR->IsRegularity() || (CR->IsPolygon3D() && !CR->Polygon3D().IsNull())
                          || CR->IsPolygonOnTriangulation() || CR->IsPolygonOnSurface();
      if (!aHasGeometry)
        return false;
      itrc.Next();
    }
    return true;
  }
  else if (aType == TopAbs_FACE)
  {
    occ::handle<BRep_TFace> TF = occ::down_cast<BRep_TFace>(theShape.TShape());
    if (!TF->Surface().IsNull())
    {
      return true;
    }
  }
  else
  {
    TopoDS_Iterator anIt(theShape, false, false);
    for (; anIt.More(); anIt.Next())
    {
      const TopoDS_Shape& aShape       = anIt.Value();
      bool                aHasGeometry = hasGeometry(aShape);
      if (!aHasGeometry)
        return false;
    }
    return true;
  }

  return false;
}

static bool IsManifoldShape(const TopoDS_Shape& theShape)
{

  bool aResult = true;

  TopoDS_Compound aDirectShapes;
  BRep_Builder    aBrepBuilder;
  aBrepBuilder.MakeCompound(aDirectShapes);

  TopoDS_Iterator anIt(theShape);
  for (; anIt.More(); anIt.Next())
  {
    const TopoDS_Shape& aDirectChild = anIt.Value();
    if (aDirectChild.ShapeType() != TopAbs_COMPOUND)
      aBrepBuilder.Add(aDirectShapes, aDirectChild);
  }

#ifdef OCCT_DEBUG
  DumpWhatIs(aDirectShapes);
#endif

  NCollection_IndexedDataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
    aMapEdgeFaces;
  TopExp::MapShapesAndAncestors(aDirectShapes, TopAbs_EDGE, TopAbs_FACE, aMapEdgeFaces);

  int aNbEdges = aMapEdgeFaces.Extent();
#ifdef OCCT_DEBUG
  std::cout << "Checking whether the topology passed is manifold..." << std::endl;
#endif

  for (int i = 1; i <= aNbEdges; i++)
  {
    TopoDS_Edge aCurrentEdge = TopoDS::Edge(aMapEdgeFaces.FindKey(i));
    if (!BRep_Tool::Degenerated(aCurrentEdge))
    {
      int aNbAncestors = aMapEdgeFaces.FindFromIndex(i).Extent();
      if (aNbAncestors > 2)
      {
        aResult = false;
        break;
      }
    }
  }

#ifdef OCCT_DEBUG
  std::cout << "Check result: " << (aResult ? "TRUE" : "FALSE") << std::endl;
#endif

  return aResult;
}

STEPControl_ActorWrite::STEPControl_ActorWrite()
    : mygroup(0),
      mytoler(-1.)
{
  SetMode(STEPControl_ShellBasedSurfaceModel);
}

occ::handle<StepShape_NonManifoldSurfaceShapeRepresentation> STEPControl_ActorWrite::
  getNMSSRForGroup(const occ::handle<NCollection_HSequence<TopoDS_Shape>>& shapeGroup,
                   const occ::handle<Transfer_FinderProcess>&              FP,
                   bool&                                                   isNMSSRCreated) const
{
  occ::handle<StepShape_NonManifoldSurfaceShapeRepresentation> aResult;

  if (!shapeGroup.IsNull())
  {
    for (int i = 1; i <= shapeGroup->Length(); i++)
    {
      TopoDS_Shape                          aCurrentShape = shapeGroup->Value(i);
      occ::handle<TransferBRep_ShapeMapper> mapper = TransferBRep::ShapeMapper(FP, aCurrentShape);
      if (FP->FindTypedTransient(mapper,
                                 STANDARD_TYPE(StepShape_NonManifoldSurfaceShapeRepresentation),
                                 aResult))
        break;
    }
  }

  if (aResult.IsNull())
  {
#ifdef OCCT_DEBUG
    std::cout << "\nNew NMSSR created" << std::endl;
#endif
    aResult        = new StepShape_NonManifoldSurfaceShapeRepresentation;
    isNMSSRCreated = true;
  }
  else
  {
#ifdef OCCT_DEBUG
    std::cout << "\nExisting NMSSR is used" << std::endl;
#endif
    isNMSSRCreated = false;
  }

  return aResult;
}

void STEPControl_ActorWrite::mergeInfoForNM(const occ::handle<Transfer_FinderProcess>& theFP,
                                            const occ::handle<Standard_Transient>& theInfo) const
{
  occ::handle<ShapeProcess_ShapeContext> aContext =
    occ::down_cast<ShapeProcess_ShapeContext>(theInfo);
  if (aContext.IsNull())
    return;

  const NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>& aMap =
    aContext->Map();
  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>::Iterator aShapeShapeIt(
    aMap);

  for (; aShapeShapeIt.More(); aShapeShapeIt.Next())
  {
    TopoDS_Shape anOrig = aShapeShapeIt.Key(), aRes = aShapeShapeIt.Value();
    if (anOrig.ShapeType() != TopAbs_FACE)
      continue;

    occ::handle<TransferBRep_ShapeMapper> anOrigMapper = TransferBRep::ShapeMapper(theFP, anOrig);
    occ::handle<Transfer_Binder>          anOrigBinder = theFP->Find(anOrigMapper);
    if (anOrigBinder.IsNull())
      continue;

    occ::handle<TransferBRep_ShapeMapper> aResMapper = TransferBRep::ShapeMapper(theFP, aRes);
    theFP->Bind(aResMapper, anOrigBinder);
  }
}

bool STEPControl_ActorWrite::separateShapeToSoloVertex(
  const TopoDS_Shape&                 theShape,
  NCollection_Sequence<TopoDS_Shape>& theVertices)
{
  if (theShape.IsNull())
  {
    return false;
  }
  switch (theShape.ShapeType())
  {
    case TopAbs_COMPOUND:
    {
      for (TopoDS_Iterator anIter(theShape); anIter.More(); anIter.Next())
      {
        if (!separateShapeToSoloVertex(anIter.Value(), theVertices))
        {
          return false;
        }
      }
      break;
    }
    case TopAbs_VERTEX:
    {
      theVertices.Append(theShape);
      break;
    }
    default:
    {
      theVertices.Clear();
      return false;
    }
  }
  return true;
}

void STEPControl_ActorWrite::SetMode(const STEPControl_StepModelType M)
{
  switch (M)
  {
    case STEPControl_AsIs:
      ModeTrans() = 0;
      break;
    case STEPControl_ManifoldSolidBrep:
      ModeTrans() = 3;
      break;
    case STEPControl_BrepWithVoids:
      ModeTrans() = 5;
      break;
    case STEPControl_FacetedBrep:
      ModeTrans() = 1;
      break;
    case STEPControl_FacetedBrepAndBrepWithVoids:
      ModeTrans() = 6;
      break;
    case STEPControl_ShellBasedSurfaceModel:
      ModeTrans() = 2;
      break;
    case STEPControl_GeometricCurveSet:
      ModeTrans() = 4;
      break;
    case STEPControl_Hybrid:
      ModeTrans() = 0;
      break;
    default:
      break;
  }
}

STEPControl_StepModelType STEPControl_ActorWrite::Mode() const
{
  switch (themodetrans)
  {
    case 0:
      return STEPControl_AsIs;
    case 1:
      return STEPControl_FacetedBrep;
    case 2:
      return STEPControl_ShellBasedSurfaceModel;
    case 3:
      return STEPControl_ManifoldSolidBrep;
    case 4:
      return STEPControl_GeometricCurveSet;
    case 5:
      return STEPControl_BrepWithVoids;
    case 6:
      return STEPControl_FacetedBrepAndBrepWithVoids;
    default:
      break;
  }
  return STEPControl_AsIs;
}

void STEPControl_ActorWrite::SetGroupMode(const int mode)
{
  if (mode >= 0)
    mygroup = mode;
}

int STEPControl_ActorWrite::GroupMode() const
{
  return mygroup;
}

void STEPControl_ActorWrite::SetTolerance(const double Tol)
{
  mytoler = Tol;
}

bool STEPControl_ActorWrite::Recognize(const occ::handle<Transfer_Finder>& start)
{
  STEPControl_StepModelType             mymode = Mode();
  occ::handle<TransferBRep_ShapeMapper> mapper = occ::down_cast<TransferBRep_ShapeMapper>(start);
  if (mapper.IsNull())
    return false;
  if (mymode == STEPControl_AsIs)
    return true;

  bool yasolid = false, yashell = false, yaface = false;

  TopoDS_Shape theShape, aShape;

  theShape = mapper->Value();

  if (theShape.ShapeType() == TopAbs_COMPOUND)
  {

    TopExp_Explorer SolidExp, ShellExp, FaceExp;

    for (SolidExp.Init(theShape, TopAbs_SOLID); SolidExp.More(); SolidExp.Next())
      yasolid = true;
    for (ShellExp.Init(theShape, TopAbs_SHELL, TopAbs_SOLID); ShellExp.More(); ShellExp.Next())
      yashell = true;
    for (FaceExp.Init(theShape, TopAbs_FACE, TopAbs_SHELL); FaceExp.More(); FaceExp.Next())
      yaface = true;
  }
  else if (theShape.ShapeType() == TopAbs_SOLID)
    yasolid = true;
  else if (theShape.ShapeType() == TopAbs_SHELL)
    yashell = true;
  else if (theShape.ShapeType() == TopAbs_FACE)
    yaface = true;
  else if (mymode != STEPControl_GeometricCurveSet)
    return false;

  if (mymode == STEPControl_FacetedBrep || mymode == STEPControl_FacetedBrepAndBrepWithVoids)
  {
    for (TopExp_Explorer ffac(theShape, TopAbs_FACE); ffac.More(); ffac.Next())
    {
      const TopoDS_Face&        F = TopoDS::Face(ffac.Current());
      TopLoc_Location           locbid;
      occ::handle<Geom_Surface> surf = BRep_Tool::Surface(F, locbid);
      if (surf.IsNull() || !surf->IsKind(STANDARD_TYPE(Geom_Plane)))
        return false;
    }
    for (TopExp_Explorer fedg(theShape, TopAbs_EDGE); fedg.More(); fedg.Next())
    {
      const TopoDS_Edge&      E = TopoDS::Edge(fedg.Current());
      TopLoc_Location         locbid;
      double                  first, last;
      occ::handle<Geom_Curve> curv = BRep_Tool::Curve(E, locbid, first, last);
      if (curv.IsNull() || !curv->IsKind(STANDARD_TYPE(Geom_Line)))
        return false;
    }
  }

  switch (mymode)
  {
    case STEPControl_ManifoldSolidBrep:
      return (yasolid || yashell);
    case STEPControl_BrepWithVoids:
    case STEPControl_FacetedBrep:
    case STEPControl_FacetedBrepAndBrepWithVoids:
      return yasolid;
    case STEPControl_ShellBasedSurfaceModel:
      return (yasolid || yashell || yaface);
    case STEPControl_GeometricCurveSet:
      return true;
    default:
      break;
  }
  return false;
}

occ::handle<Transfer_Binder> STEPControl_ActorWrite::Transfer(
  const occ::handle<Transfer_Finder>&        start,
  const occ::handle<Transfer_FinderProcess>& FP,
  const Message_ProgressRange&               theProgress)
{
  occ::handle<TransferBRep_ShapeMapper> mapper = occ::down_cast<TransferBRep_ShapeMapper>(start);

  if (mapper.IsNull())
    return NullResult();
  TopoDS_Shape shape = mapper->Value();

  occ::handle<StepData_StepModel> model = occ::down_cast<StepData_StepModel>(FP->Model());
  if (!model.IsNull())
    myContext.SetModel(model);
  myContext.AddAPD(false);
  myContext.SetLevel(1);
  if (!model->IsInitializedUnit())
  {
    XSAlgo_ShapeProcessor::PrepareForTransfer();
    model->SetLocalLengthUnit(UnitsMethods::GetCasCadeLengthUnit());
  }
  double aLFactor = model->WriteLengthUnit();
  aLFactor /= model->LocalLengthUnit();
  const int        anglemode = model->InternalParameters.AngleUnit;
  StepData_Factors aLocalFactors;
  aLocalFactors.InitializeFactors(aLFactor, (anglemode <= 1 ? 1. : M_PI / 180.), 1.);

  STEPConstruct_Part SDRTool;
  SDRTool.MakeSDR(nullptr, myContext.GetProductName(), myContext.GetAPD()->Application(), model);
  occ::handle<StepShape_ShapeDefinitionRepresentation> sdr = SDRTool.SDRValue();

  occ::handle<Transfer_Binder> resbind =
    TransferShape(mapper, sdr, FP, aLocalFactors, nullptr, true, theProgress);

  occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>> roots =
    myContext.GetRootsForPart(SDRTool);
  occ::handle<Transfer_Binder> resprod = TransientResult(myContext.GetAPD());
  for (int i = 1; i <= roots->Length(); i++)
    resprod->AddResult(TransientResult(roots->Value(i)));
  resprod->AddResult(resbind);

  myContext.NextIndex();
  return resprod;
}

static double UsedTolerance(occ::handle<StepData_StepModel>& theStepModel,
                            const double                     mytoler,
                            const TopoDS_Shape&              theShape)
{

  double Tol    = mytoler;
  int    tolmod = theStepModel->InternalParameters.WritePrecisionMode;
  if (Tol <= 0 && tolmod == 2)
    Tol = theStepModel->InternalParameters.WritePrecisionVal;
  if (Tol <= 0)
  {
    ShapeAnalysis_ShapeTolerance stu;
    Tol = stu.Tolerance(theShape, tolmod);

    Tol = Interface_MSG::Intervalled(Tol * 1.5);
  }
  if (Tol == 0)
    Tol = 1.e-07;

  return Tol;
}

bool STEPControl_ActorWrite::IsAssembly(const occ::handle<StepData_StepModel>& theModel,
                                        TopoDS_Shape&                          S) const
{
  if (!GroupMode() || S.ShapeType() != TopAbs_COMPOUND)
    return false;

  if (theModel->InternalParameters.WriteVertexMode == 0)
  {
    if (S.ShapeType() == TopAbs_COMPOUND)
    {
      bool            IsOnlyVertices = true;
      TopoDS_Iterator anItr(S);
      for (; anItr.More(); anItr.Next())
      {
        if (anItr.Value().ShapeType() != TopAbs_VERTEX)
        {
          IsOnlyVertices = false;
          break;
        }
      }
      if (IsOnlyVertices)
        return false;
    }
  }
  if (GroupMode() == 1)
    return true;
  TopoDS_Iterator it(S);
  if (!it.More())
    return false;
  TopoDS_Shape shape = it.Value();
  it.Next();
  if (it.More())
    return true;
  S = shape;
  return IsAssembly(theModel, S);
}

static bool transferVertex(const occ::handle<Transfer_FinderProcess>&                      FP,
                           occ::handle<NCollection_HArray1<StepShape_GeometricSetSelect>>& aGSS,
                           const TopoDS_Shape&                                             aShVrtx,
                           const int                                                       theNum,
                           const StepData_Factors& theLocalFactors)
{
  bool IsDone = false;
  NCollection_DataMap<TopoDS_Shape, occ::handle<Standard_Transient>, TopTools_ShapeMapHasher> aMap;
  occ::handle<StepData_StepModel> aStepModel = occ::down_cast<StepData_StepModel>(FP->Model());
  TopoDSToStep_Tool           aTool(aMap, true, aStepModel->InternalParameters.WriteSurfaceCurMode);
  TopoDSToStep_MakeStepVertex aMkVrtx(TopoDS::Vertex(aShVrtx), aTool, FP, theLocalFactors);

  if (!aMkVrtx.IsDone())
    return IsDone;

  occ::handle<StepShape_VertexPoint> aVP =
    occ::down_cast<StepShape_VertexPoint>(aTool.Find(aShVrtx));
  if (aVP.IsNull())
    return IsDone;

  StepShape_GeometricSetSelect select;
  select.SetValue(aVP->VertexGeometry());

  aGSS->SetValue(theNum, select);
  IsDone = true;
  return IsDone;
}

occ::handle<Transfer_Binder> STEPControl_ActorWrite::TransferShape(
  const occ::handle<Transfer_Finder>&                         start,
  const occ::handle<StepShape_ShapeDefinitionRepresentation>& SDR0,
  const occ::handle<Transfer_FinderProcess>&                  FP,
  const StepData_Factors&                                     theLocalFactors,
  const occ::handle<NCollection_HSequence<TopoDS_Shape>>&     shapeGroup,
  const bool                                                  isManifold,
  const Message_ProgressRange&                                theProgress)
{
  STEPControl_StepModelType             mymode = Mode();
  occ::handle<TransferBRep_ShapeMapper> mapper = occ::down_cast<TransferBRep_ShapeMapper>(start);
  occ::handle<Transfer_Binder>          binder;
  occ::handle<StepData_StepModel> aStepModel = occ::down_cast<StepData_StepModel>(FP->Model());

  bool useExistingNMSSR = false;

  if (mapper.IsNull())
    return binder;
  TopoDS_Shape theShape = mapper->Value();

  if (theShape.IsNull())
    return binder;

  binder = FP->Find(start);
  if (!binder.IsNull())
  {
    if (!binder->HasResult())
      binder.Nullify();
  }
  if (!binder.IsNull())
  {

#ifdef OCCT_DEBUG
    std::cout << "Warning: STEPControl_ActorWrite::TransferShape(): shape already translated"
              << std::endl;
#endif
  }

  if (IsAssembly(aStepModel, theShape))
    return TransferCompound(start, SDR0, FP, theLocalFactors, theProgress);

  Message_ProgressScope aPSRoot(theProgress, nullptr, 2);

  bool                         isNMMode = aStepModel->InternalParameters.WriteNonmanifold != 0;
  occ::handle<Transfer_Binder> aNMBinder;
  if (isNMMode && !GroupMode() && theShape.ShapeType() == TopAbs_COMPOUND)
  {
    TopoDS_Compound aNMCompound;
    TopoDS_Compound aManifoldCompound;
    BRep_Builder    brepBuilder;

    brepBuilder.MakeCompound(aManifoldCompound);
    brepBuilder.MakeCompound(aNMCompound);

    bool isOnlyNonManifold = false;

    if (!IsManifoldShape(theShape))
    {
      aNMCompound       = TopoDS::Compound(theShape);
      isOnlyNonManifold = true;
    }
    else
    {
      NCollection_List<TopoDS_Shape> aListOfShapes;
      NCollection_List<TopoDS_Shape> aListOfManifoldShapes;
      aListOfShapes.Append(theShape);

      NCollection_List<TopoDS_Shape>::Iterator itL(aListOfShapes);
      for (; itL.More(); itL.Next())
      {
        TopoDS_Shape    aParentShape = itL.Value();
        TopoDS_Iterator it(aParentShape);
        for (; it.More(); it.Next())
        {
          TopoDS_Shape aSubShape = it.Value();
          if (aSubShape.ShapeType() == TopAbs_COMPOUND && !IsManifoldShape(aSubShape))
            aNMCompound = TopoDS::Compound(aSubShape);
          else if (aSubShape.ShapeType() == TopAbs_COMPOUND)
            aListOfShapes.Append(aSubShape);
          else
            aListOfManifoldShapes.Append(aSubShape);
        }
      }

      for (itL.Initialize(aListOfManifoldShapes); itL.More(); itL.Next())
      {
        TopoDS_Shape aCurrentManiShape = itL.Value();
        brepBuilder.Add(aManifoldCompound, aCurrentManiShape);
      }
    }

    theShape = aManifoldCompound;

    occ::handle<NCollection_HSequence<TopoDS_Shape>> RepItemSeq =
      new NCollection_HSequence<TopoDS_Shape>();

    occ::handle<NCollection_HSequence<TopoDS_Shape>> NonManifoldGroup =
      new NCollection_HSequence<TopoDS_Shape>();

    for (TopoDS_Iterator iter(aNMCompound); iter.More(); iter.Next())
    {
      const TopoDS_Shape& aSubShape = iter.Value();
      if (aSubShape.ShapeType() == TopAbs_SOLID)
      {
        for (TopoDS_Iterator aSubIter(aSubShape); aSubIter.More(); aSubIter.Next())
        {
          TopoDS_Shell aSubShell = TopoDS::Shell(aSubIter.Value());
          aSubShell.Closed(true);
          RepItemSeq->Append(aSubShell);
          NonManifoldGroup->Append(aSubShell);
        }
      }
      else if (!isManifold && (aSubShape.ShapeType() == TopAbs_SHELL))
      {
        RepItemSeq->Append(aSubShape);
        NonManifoldGroup->Append(aSubShape);
      }
      else
        RepItemSeq->Append(iter.Value());
    }

    int aNMItemsNb = RepItemSeq->Length();

    if (aNMItemsNb > 0)
    {

      occ::handle<StepShape_ShapeDefinitionRepresentation> sdr;
      if (isOnlyNonManifold)
        sdr = SDR0;
      else
      {
        STEPConstruct_Part SDRTool;
        SDRTool.MakeSDR(nullptr,
                        myContext.GetProductName(),
                        myContext.GetAPD()->Application(),
                        aStepModel);
        sdr = SDRTool.SDRValue();
      }

      aNMBinder = TransientResult(sdr);

      Message_ProgressScope aPS(aPSRoot.Next(), nullptr, aNMItemsNb);
      for (int i = 1; i <= aNMItemsNb && aPS.More(); i++)
      {
        occ::handle<TransferBRep_ShapeMapper> aMapper =
          TransferBRep::ShapeMapper(FP, RepItemSeq->Value(i));
        TransferShape(aMapper, sdr, FP, theLocalFactors, NonManifoldGroup, false, aPS.Next());
      }

      if (isOnlyNonManifold)
        return aNMBinder;
    }
  }

  if (aPSRoot.UserBreak())
    return occ::handle<Transfer_Binder>();

  occ::handle<NCollection_HSequence<TopoDS_Shape>> RepItemSeq =
    new NCollection_HSequence<TopoDS_Shape>();

  bool isSeparateVertices = aStepModel->InternalParameters.WriteVertexMode == 0;

  bool isOnlyVertices = false;
  if (theShape.ShapeType() == TopAbs_COMPOUND && isSeparateVertices)
  {
    TopoDS_Compound aNewShape, aCompOfVrtx;
    BRep_Builder    aBuilder;
    aBuilder.MakeCompound(aNewShape);
    aBuilder.MakeCompound(aCompOfVrtx);
    NCollection_Sequence<TopoDS_Shape> aVertices;
    isOnlyVertices = separateShapeToSoloVertex(theShape, aVertices);
    if (!isOnlyVertices)
    {
      for (TopoDS_Iterator anCompIt(theShape); anCompIt.More(); anCompIt.Next())
      {
        const TopoDS_Shape&                aCurSh = anCompIt.Value();
        NCollection_Sequence<TopoDS_Shape> aVerticesOfSubSh;
        if (separateShapeToSoloVertex(aCurSh, aVerticesOfSubSh))
        {
          aVertices.Append(aVerticesOfSubSh);
        }
        else
        {
          aBuilder.Add(aNewShape, aCurSh);
        }
      }
      theShape = aNewShape;
    }
    for (NCollection_HSequence<TopoDS_Shape>::Iterator anIterV(aVertices); anIterV.More();
         anIterV.Next())
    {
      aBuilder.Add(aCompOfVrtx, anIterV.Value());
    }
    if (!aVertices.IsEmpty())
    {
      RepItemSeq->Append(aCompOfVrtx);
    }
  }

  if (theShape.ShapeType() == TopAbs_COMPOUND)
  {
    TopExp_Explorer SolidExp, ShellExp, FaceExp;
    if (mymode != STEPControl_GeometricCurveSet)
    {
      for (SolidExp.Init(theShape, TopAbs_SOLID); SolidExp.More(); SolidExp.Next())
      {
        RepItemSeq->Append(TopoDS::Solid(SolidExp.Current()));
      }
      for (ShellExp.Init(theShape, TopAbs_SHELL, TopAbs_SOLID); ShellExp.More(); ShellExp.Next())
      {
        RepItemSeq->Append(TopoDS::Shell(ShellExp.Current()));
      }

      for (FaceExp.Init(theShape, TopAbs_FACE, TopAbs_SHELL); FaceExp.More(); FaceExp.Next())
      {
        RepItemSeq->Append(TopoDS::Face(FaceExp.Current()));
      }
    }
    else
    {
      if (!isOnlyVertices)
        RepItemSeq->Append(theShape);
    }
    if (mymode == STEPControl_AsIs)
    {
      TopExp_Explorer WireExp, EdgeExp;
      for (WireExp.Init(theShape, TopAbs_WIRE, TopAbs_FACE); WireExp.More(); WireExp.Next())
        RepItemSeq->Append(TopoDS::Wire(WireExp.Current()));
      for (EdgeExp.Init(theShape, TopAbs_EDGE, TopAbs_WIRE); EdgeExp.More(); EdgeExp.Next())
        RepItemSeq->Append(TopoDS::Edge(EdgeExp.Current()));
    }
  }
  else if (theShape.ShapeType() == TopAbs_SOLID)
  {
    RepItemSeq->Append(TopoDS::Solid(theShape));
  }
  else if (theShape.ShapeType() == TopAbs_SHELL)
  {
    RepItemSeq->Append(TopoDS::Shell(theShape));
  }
  else if (theShape.ShapeType() == TopAbs_FACE)
  {
    RepItemSeq->Append(TopoDS::Face(theShape));
  }
  else if (theShape.ShapeType() == TopAbs_COMPSOLID)
  {
    FP->AddWarning(start, "NonManifold COMPSOLID was translated like a set of SOLIDs");
    if (GroupMode() > 0)
      return TransferCompound(start, SDR0, FP, theLocalFactors, aPSRoot.Next());
    else
    {
      TopExp_Explorer SolidExp;
      for (SolidExp.Init(theShape, TopAbs_SOLID); SolidExp.More(); SolidExp.Next())
      {
        RepItemSeq->Append(TopoDS::Solid(SolidExp.Current()));
      }
    }
  }

  else if (mymode != STEPControl_GeometricCurveSet && mymode != STEPControl_AsIs)
  {
    FP->AddFail(start, "The Shape is not a SOLID, nor a SHELL, nor a FACE");
    return binder;
  }
  else
    RepItemSeq->Append(theShape);

  double Tol = UsedTolerance(aStepModel, mytoler, theShape);

  int                                                                 nbs = RepItemSeq->Length();
  occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>> ItemSeq =
    new NCollection_HSequence<occ::handle<Standard_Transient>>();

  ItemSeq->Append(myContext.GetDefaultAxis());
  STEPControl_StepModelType trmode = mymode;
  Message_ProgressScope     aPS(aPSRoot.Next(), nullptr, nbs);
  for (int i = 1; i <= nbs && aPS.More(); i++)
  {
    TopoDS_Shape xShape = RepItemSeq->Value(i);

    if (mymode == STEPControl_AsIs)
    {
      switch (xShape.ShapeType())
      {
        case TopAbs_SOLID:
          trmode = STEPControl_ManifoldSolidBrep;
          break;
        case TopAbs_SHELL:
          trmode = STEPControl_ShellBasedSurfaceModel;
          break;
        case TopAbs_FACE:
          trmode = STEPControl_ShellBasedSurfaceModel;
          break;
        default:
          trmode = STEPControl_GeometricCurveSet;
          break;
      }
    }

    Message_ProgressScope aPS1(aPS.Next(), nullptr, 2);

    TopoDS_Shape aShape = xShape;

    XSAlgo_ShapeProcessor::ParameterMap aParameters = GetShapeFixParameters();
    XSAlgo_ShapeProcessor::SetParameter("FixShape.Tolerance3d", Tol, true, aParameters);
    XSAlgo_ShapeProcessor::SetParameter("FixShape.MaxTolerance3d",
                                        aStepModel->InternalParameters.ReadMaxPrecisionVal,
                                        true,
                                        aParameters);
    XSAlgo_ShapeProcessor aShapeProcessor(aParameters);

    if (hasGeometry(aShape))
    {
      aShape = aShapeProcessor.ProcessShape(xShape, GetShapeProcessFlags().first, aPS1.Next());

      if (aPS1.UserBreak())
      {
        return occ::handle<Transfer_Binder>();
      }
    }

    if (!isManifold)
    {
      mergeInfoForNM(FP, aShapeProcessor.GetContext());
    }

    occ::handle<StepGeom_GeometricRepresentationItem> item, itemTess;
    switch (trmode)
    {
      case STEPControl_ManifoldSolidBrep:
      {
        if (aShape.ShapeType() == TopAbs_SOLID)
        {
          TopoDS_Solid aSolid = TopoDS::Solid(aShape);

          int nbShells = 0;
          for (TopoDS_Iterator It(aSolid); It.More(); It.Next())
            if (It.Value().ShapeType() == TopAbs_SHELL)
              nbShells++;
          if (nbShells > 1)
          {
            TopoDSToStep_MakeBrepWithVoids MkBRepWithVoids(aSolid,
                                                           FP,
                                                           theLocalFactors,
                                                           aPS1.Next());
            MkBRepWithVoids.Tolerance() = Tol;
            if (MkBRepWithVoids.IsDone())
            {
              item     = MkBRepWithVoids.Value();
              itemTess = MkBRepWithVoids.TessellatedValue();
            }
            else
              nbShells = 1;
          }
          if (nbShells == 1)
          {
            TopoDSToStep_MakeManifoldSolidBrep MkManifoldSolidBrep(aSolid,
                                                                   FP,
                                                                   theLocalFactors,
                                                                   aPS1.Next());
            MkManifoldSolidBrep.Tolerance() = Tol;
            if (MkManifoldSolidBrep.IsDone())
            {
              item     = MkManifoldSolidBrep.Value();
              itemTess = MkManifoldSolidBrep.TessellatedValue();
            }
          }
        }
        else if (aShape.ShapeType() == TopAbs_SHELL)
        {
          TopoDS_Shell                       aShell = TopoDS::Shell(aShape);
          TopoDSToStep_MakeManifoldSolidBrep MkManifoldSolidBrep(aShell,
                                                                 FP,
                                                                 theLocalFactors,
                                                                 aPS1.Next());
          MkManifoldSolidBrep.Tolerance() = Tol;
          if (MkManifoldSolidBrep.IsDone())
          {
            item     = MkManifoldSolidBrep.Value();
            itemTess = MkManifoldSolidBrep.TessellatedValue();
          }
        }
        break;
      }
      case STEPControl_BrepWithVoids:
      {
        if (aShape.ShapeType() == TopAbs_SOLID)
        {
          TopoDS_Solid                   aSolid = TopoDS::Solid(aShape);
          TopoDSToStep_MakeBrepWithVoids MkBRepWithVoids(aSolid, FP, theLocalFactors, aPS1.Next());
          MkBRepWithVoids.Tolerance() = Tol;
          if (MkBRepWithVoids.IsDone())
          {
            item     = MkBRepWithVoids.Value();
            itemTess = MkBRepWithVoids.TessellatedValue();
          }
        }
        break;
      }
      case STEPControl_FacetedBrep:
      {
        TopoDSToStep_FacetedError facErr = TopoDSToStep_FacetedTool::CheckTopoDSShape(aShape);
        if (facErr != TopoDSToStep_FacetedDone)
        {
          FP->AddFail(start, "Error in Faceted Shape from TopoDS");
          if (facErr == TopoDSToStep_SurfaceNotPlane)
          {
            FP->AddFail(start, "-- The TopoDS_Face is not plane");
          }
          else if (facErr == TopoDSToStep_PCurveNotLinear)
          {
            FP->AddFail(start, "-- The Face contains non linear PCurves");
          }
          return binder;
        }
        if (aShape.ShapeType() == TopAbs_SOLID)
        {
          TopoDS_Solid                 aSolid = TopoDS::Solid(aShape);
          TopoDSToStep_MakeFacetedBrep MkFacetedBrep(aSolid, FP, theLocalFactors, aPS1.Next());
          MkFacetedBrep.Tolerance() = Tol;
          if (MkFacetedBrep.IsDone())
          {
            item     = MkFacetedBrep.Value();
            itemTess = MkFacetedBrep.TessellatedValue();
          }
        }
        break;
      }
      case STEPControl_FacetedBrepAndBrepWithVoids:
      {
        TopoDSToStep_FacetedError facErr = TopoDSToStep_FacetedTool::CheckTopoDSShape(aShape);
        if (facErr != TopoDSToStep_FacetedDone)
        {
          FP->AddFail(start, "Error in Faceted Shape from TopoDS");
          if (facErr == TopoDSToStep_SurfaceNotPlane)
          {
            FP->AddFail(start, "-- The TopoDS_Face is not plane");
          }
          else if (facErr == TopoDSToStep_PCurveNotLinear)
          {
            FP->AddFail(start, "-- The Face contains non linear PCurves");
          }
          return binder;
        }
        if (aShape.ShapeType() == TopAbs_SOLID)
        {
          TopoDS_Solid                                 aSolid = TopoDS::Solid(aShape);
          TopoDSToStep_MakeFacetedBrepAndBrepWithVoids MkFacetedBrepAndBrepWithVoids(
            aSolid,
            FP,
            theLocalFactors,
            aPS1.Next());
          MkFacetedBrepAndBrepWithVoids.Tolerance() = Tol;
          if (MkFacetedBrepAndBrepWithVoids.IsDone())
          {
            item     = MkFacetedBrepAndBrepWithVoids.Value();
            itemTess = MkFacetedBrepAndBrepWithVoids.TessellatedValue();
          }
        }
        break;
      }
      case STEPControl_ShellBasedSurfaceModel:
      {
        if (aShape.ShapeType() == TopAbs_SOLID)
        {
          TopoDS_Solid                            aSolid = TopoDS::Solid(aShape);
          TopoDSToStep_MakeShellBasedSurfaceModel MkShellBasedSurfaceModel(aSolid,
                                                                           FP,
                                                                           theLocalFactors,
                                                                           aPS1.Next());
          MkShellBasedSurfaceModel.Tolerance() = Tol;
          if (MkShellBasedSurfaceModel.IsDone())
          {
            item     = MkShellBasedSurfaceModel.Value();
            itemTess = MkShellBasedSurfaceModel.TessellatedValue();
          }
        }
        else if (aShape.ShapeType() == TopAbs_SHELL)
        {
          TopoDS_Shell aShell = TopoDS::Shell(aShape);

          TopoDSToStep_MakeShellBasedSurfaceModel MkShellBasedSurfaceModel(aShell,
                                                                           FP,
                                                                           theLocalFactors,
                                                                           aPS1.Next());
          MkShellBasedSurfaceModel.Tolerance() = Tol;
          if (MkShellBasedSurfaceModel.IsDone())
          {
            item     = MkShellBasedSurfaceModel.Value();
            itemTess = MkShellBasedSurfaceModel.TessellatedValue();
          }
        }
        else if (aShape.ShapeType() == TopAbs_FACE)
        {
          TopoDS_Face                             aFace = TopoDS::Face(aShape);
          TopoDSToStep_MakeShellBasedSurfaceModel MkShellBasedSurfaceModel(aFace,
                                                                           FP,
                                                                           theLocalFactors,
                                                                           aPS1.Next());
          MkShellBasedSurfaceModel.Tolerance() = Tol;
          if (MkShellBasedSurfaceModel.IsDone())
          {
            item     = MkShellBasedSurfaceModel.Value();
            itemTess = MkShellBasedSurfaceModel.TessellatedValue();
          }
        }
        break;
      }
      case STEPControl_GeometricCurveSet:
      {
        TopoDSToStep_MakeGeometricCurveSet MkGeometricCurveSet(aShape, FP, theLocalFactors);
        MkGeometricCurveSet.Tolerance() = Tol;
        if (MkGeometricCurveSet.IsDone())
        {
          item = MkGeometricCurveSet.Value();
        }

        else if (aShape.ShapeType() == TopAbs_COMPOUND || aShape.ShapeType() == TopAbs_VERTEX)
        {

          int             aNbVrtx = 0;
          int             curNb   = 0;
          TopExp_Explorer anExp(aShape, TopAbs_VERTEX);
          for (; anExp.More(); anExp.Next())
          {
            if (anExp.Current().ShapeType() != TopAbs_VERTEX)
              continue;
            aNbVrtx++;
          }
          if (aNbVrtx)
          {

            occ::handle<NCollection_HArray1<StepShape_GeometricSetSelect>> aGSS =
              new NCollection_HArray1<StepShape_GeometricSetSelect>(1, aNbVrtx);
            occ::handle<TCollection_HAsciiString>    empty  = new TCollection_HAsciiString("");
            occ::handle<StepShape_GeometricCurveSet> aGCSet = new StepShape_GeometricCurveSet;
            aGCSet->SetName(empty);

            for (anExp.ReInit(); anExp.More(); anExp.Next())
            {
              const TopoDS_Shape& aVertex = anExp.Current();
              if (aVertex.ShapeType() != TopAbs_VERTEX)
                continue;
              curNb++;
              transferVertex(FP, aGSS, aVertex, curNb, theLocalFactors);
            }
            aGCSet->SetElements(aGSS);
            item = aGCSet;
          }
        }

        break;
      }
      default:
        break;
    }
    if (item.IsNull() && itemTess.IsNull())
      continue;

    if (!item.IsNull())
    {
      ItemSeq->Append(item);
      occ::handle<TransferBRep_ShapeMapper> submapper;
      if (xShape.IsSame(mapper->Value()))
        submapper = occ::down_cast<TransferBRep_ShapeMapper>(start);
      if (submapper.IsNull())
        submapper = TransferBRep::ShapeMapper(FP, xShape);
      occ::handle<Transfer_Binder> subbind = FP->Find(submapper);
      if (subbind.IsNull())
      {
        subbind = TransientResult(item);
        FP->Bind(submapper, subbind);
      }
      else
        subbind->AddResult(TransientResult(item));
    }
    if (!itemTess.IsNull())
    {
      ItemSeq->Append(itemTess);
      occ::handle<TransferBRep_ShapeMapper> submapper;
      if (xShape.IsSame(mapper->Value()))
        submapper = occ::down_cast<TransferBRep_ShapeMapper>(start);
      if (submapper.IsNull())
        submapper = TransferBRep::ShapeMapper(FP, xShape);
      occ::handle<Transfer_Binder> subbind = FP->Find(submapper);
      if (subbind.IsNull())
      {
        subbind = TransientResult(itemTess);
        FP->Bind(submapper, subbind);
      }
      else
        subbind->AddResult(TransientResult(itemTess));
    }

    aShapeProcessor.MergeTransferInfo(FP);
  }

  int nCc1 = ItemSeq->Length();
  if (nCc1 < 1)
  {
    FP->AddFail(start, "The Shape has not the appropriate type");
    return binder;
  }
  occ::handle<StepShape_ShapeRepresentation> shapeRep;
  if (theShape.ShapeType() == TopAbs_SHAPE)
  {
    shapeRep = new StepShape_ShapeRepresentation;
  }
  else
  {
    switch (mymode)
    {
      case STEPControl_ManifoldSolidBrep:
        shapeRep = new StepShape_AdvancedBrepShapeRepresentation;
        break;
      case STEPControl_FacetedBrep:
        shapeRep = new StepShape_FacetedBrepShapeRepresentation;
        break;

      case STEPControl_ShellBasedSurfaceModel:
        if (isManifold)
          shapeRep = new StepShape_ManifoldSurfaceShapeRepresentation;
        else
        {
          bool isNewNMSSRCreated;
          shapeRep         = this->getNMSSRForGroup(shapeGroup, FP, isNewNMSSRCreated);
          useExistingNMSSR = !isNewNMSSRCreated;
        }
        break;
      case STEPControl_GeometricCurveSet:
        shapeRep = new StepShape_GeometricallyBoundedWireframeShapeRepresentation;
        break;
      case STEPControl_AsIs:
      {
        if (nbs == 1)
        {
          if (trmode == STEPControl_ManifoldSolidBrep)
            shapeRep = new StepShape_AdvancedBrepShapeRepresentation;
          else if (trmode == STEPControl_ShellBasedSurfaceModel)

            if (isManifold)
              shapeRep = new StepShape_ManifoldSurfaceShapeRepresentation;
            else
            {
              bool isNewNMSSRCreated;
              shapeRep         = this->getNMSSRForGroup(shapeGroup, FP, isNewNMSSRCreated);
              useExistingNMSSR = !isNewNMSSRCreated;
            }
          else if (trmode == STEPControl_GeometricCurveSet)
            shapeRep = new StepShape_GeometricallyBoundedWireframeShapeRepresentation;
          else if (trmode == STEPControl_FacetedBrep)
            shapeRep = new StepShape_FacetedBrepShapeRepresentation;
        }
        else
          shapeRep = new StepShape_ShapeRepresentation;
      }
      break;
      default:
        break;
    }
  }
  if (shapeRep.IsNull())
  {
    occ::handle<Transfer_Binder> resb;
    return resb;
  }

  occ::handle<NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>> items =
    new NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>(1, nCc1);

  for (int rep = 1; rep <= nCc1; rep++)
  {
    occ::handle<StepRepr_RepresentationItem> repit =
      GetCasted(StepRepr_RepresentationItem, ItemSeq->Value(rep));
    items->SetValue(rep, repit);
  }
  int ap = aStepModel->InternalParameters.WriteSchema;
  NCollection_Sequence<occ::handle<Transfer_Binder>> aSeqBindRelation;
  if (ap == 3 && nbs > 1)
  {
    int j = 1;
    if (items->Value(j)->IsKind(STANDARD_TYPE(StepGeom_Axis2Placement3d)))
    {
      occ::handle<NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>> axis =
        new NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>(1, 1);
      axis->SetValue(1, items->Value(j++));
      shapeRep->SetItems(axis);
    }
    for (; j <= items->Length(); j++)
    {

      occ::handle<StepShape_ShapeRepresentation> ShapeRepr1;
      if (items->Value(j)->IsKind(STANDARD_TYPE(StepShape_ManifoldSolidBrep)))
        ShapeRepr1 = new StepShape_AdvancedBrepShapeRepresentation;
      else if (items->Value(j)->IsKind(STANDARD_TYPE(StepShape_ShellBasedSurfaceModel)))
        ShapeRepr1 = new StepShape_ManifoldSurfaceShapeRepresentation;
      else if (items->Value(j)->IsKind(STANDARD_TYPE(StepShape_GeometricCurveSet)))
        ShapeRepr1 = new StepShape_GeometricallyBoundedWireframeShapeRepresentation;
      else if (items->Value(j)->IsKind(STANDARD_TYPE(StepShape_FacetedBrep)))
        ShapeRepr1 = new StepShape_FacetedBrepShapeRepresentation;
      else if (items->Value(j)->IsKind(STANDARD_TYPE(StepVisual_TessellatedItem)))
        ShapeRepr1 = new StepVisual_TessellatedShapeRepresentation;
      else
        ShapeRepr1 = new StepShape_ShapeRepresentation;

      occ::handle<NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>> repr1 =
        new NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>(1, 2);
      repr1->SetValue(1, myContext.GetDefaultAxis());
      repr1->SetValue(2, items->Value(j));
      ShapeRepr1->SetItems(repr1);
      STEPConstruct_UnitContext mk1;
      mk1.Init(Tol, aStepModel, theLocalFactors);
      ShapeRepr1->SetContextOfItems(mk1.Value());
      ShapeRepr1->SetName(new TCollection_HAsciiString(""));

      occ::handle<StepRepr_ShapeRepresentationRelationship> aShapeRel =
        new StepRepr_ShapeRepresentationRelationship;
      occ::handle<TCollection_HAsciiString> aName  = new TCollection_HAsciiString("");
      occ::handle<TCollection_HAsciiString> aDescr = new TCollection_HAsciiString("");
      aShapeRel->SetName(aName);
      aShapeRel->SetDescription(aDescr);
      aShapeRel->SetRep2(shapeRep);
      aShapeRel->SetRep1(ShapeRepr1);

      aSeqBindRelation.Append(TransientResult(aShapeRel));
    }
  }
  else
  {
    int nC = 0;
    for (int i = 1; i <= items->Length(); i++)
    {
      if (!items->Value(i)->IsKind(STANDARD_TYPE(StepVisual_TessellatedItem)))
        continue;
      ++nC;
    }
    if (nC > 0)
    {
      occ::handle<NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>> itemsTess =
        new NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>(1, nC);
      int i = 1;
      for (int j = 1; j <= items->Length(); j++)
      {
        if (!items->Value(j)->IsKind(STANDARD_TYPE(StepVisual_TessellatedItem)))
          continue;
        itemsTess->SetValue(i++, items->Value(j));
      }

      occ::handle<StepShape_ShapeRepresentation> shapeTessRepr =
        new StepVisual_TessellatedShapeRepresentation;
      shapeTessRepr->SetItems(itemsTess);
      STEPConstruct_UnitContext mk1;
      mk1.Init(Tol, aStepModel, theLocalFactors);
      shapeTessRepr->SetContextOfItems(mk1.Value());
      shapeTessRepr->SetName(new TCollection_HAsciiString(""));

      aSeqBindRelation.Append(TransientResult(shapeTessRepr));
    }
    if (!useExistingNMSSR)
      shapeRep->SetItems(items);
    else
    {

      occ::handle<NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>> oldItems =
        shapeRep->Items();
      occ::handle<NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>> newItems =
        new NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>(1,
                                                                          oldItems->Length() + 1);
      int el = 1;
      for (int i = 1; i <= oldItems->Length(); i++)
        newItems->SetValue(el++, oldItems->Value(i));
      newItems->SetValue(el, items->Value(items->Length()));
      shapeRep->SetItems(newItems);
    }
  }

  STEPConstruct_UnitContext mk;
  mk.Init(Tol, aStepModel, theLocalFactors);
  shapeRep->SetContextOfItems(mk.Value());
  shapeRep->SetName(new TCollection_HAsciiString(""));

  if (!useExistingNMSSR)
  {
    SDR0->SetUsedRepresentation(shapeRep);

    occ::handle<Transfer_Binder> resbind = TransientResult(shapeRep);
    binder                               = FP->Find(start);
    if (!binder.IsNull())
    {
      resbind->AddResult(binder);
      FP->Rebind(start, resbind);
    }
    for (int k = 1; k <= aSeqBindRelation.Length(); k++)
      resbind->AddResult(aSeqBindRelation.Value(k));

    if (!aNMBinder.IsNull())
      resbind->AddResult(aNMBinder);

    return resbind;
  }
  else
    return FP->Find(start);
}

occ::handle<Transfer_Binder> STEPControl_ActorWrite::TransferCompound(
  const occ::handle<Transfer_Finder>&                         start,
  const occ::handle<StepShape_ShapeDefinitionRepresentation>& SDR0,
  const occ::handle<Transfer_FinderProcess>&                  FP,
  const StepData_Factors&                                     theLocalFactors,
  const Message_ProgressRange&                                theProgress)
{
  occ::handle<TransferBRep_ShapeMapper> mapper = occ::down_cast<TransferBRep_ShapeMapper>(start);
  occ::handle<Transfer_Binder>          binder;
  if (mapper.IsNull())
    return binder;
  TopoDS_Shape theShape = mapper->Value();

  occ::handle<StepData_StepModel> aStepModel = occ::down_cast<StepData_StepModel>(FP->Model());

  bool isNMMode = aStepModel->InternalParameters.WriteNonmanifold != 0;
  bool isManifold;
  if (isNMMode)
    isManifold = IsManifoldShape(theShape);
  else
    isManifold = true;

  occ::handle<NCollection_HSequence<TopoDS_Shape>> RepItemSeq =
    new NCollection_HSequence<TopoDS_Shape>();

  occ::handle<NCollection_HSequence<TopoDS_Shape>> NonManifoldGroup =
    new NCollection_HSequence<TopoDS_Shape>();
  bool isSeparateVertices = (aStepModel->InternalParameters.WriteVertexMode == 0);

  int             nbFreeVrtx = 0;
  TopoDS_Compound aCompOfVrtx;
  BRep_Builder    aB;
  aB.MakeCompound(aCompOfVrtx);

#ifdef OCCT_DEBUG
  if (!isManifold)
    std::cout << "Exploding Solids to Shells if any..." << std::endl;
#endif

  for (TopoDS_Iterator iter(theShape); iter.More(); iter.Next())
  {
    const TopoDS_Shape& aSubShape = iter.Value();
    if (aSubShape.ShapeType() != TopAbs_VERTEX || !isSeparateVertices)
    {

      if (!isManifold && aSubShape.ShapeType() == TopAbs_SOLID)
      {
        for (TopoDS_Iterator aSubIter(aSubShape); aSubIter.More(); aSubIter.Next())
        {
          TopoDS_Shell aSubShell = TopoDS::Shell(aSubIter.Value());
          aSubShell.Closed(true);
          RepItemSeq->Append(aSubShell);
          NonManifoldGroup->Append(aSubShell);
        }
      }
      else if (!isManifold
               && (aSubShape.ShapeType() == TopAbs_SHELL || aSubShape.ShapeType() == TopAbs_FACE))
      {
        RepItemSeq->Append(aSubShape);
        NonManifoldGroup->Append(aSubShape);
      }
      else
        RepItemSeq->Append(aSubShape);

      continue;
    }
    aB.Add(aCompOfVrtx, iter.Value());
    nbFreeVrtx++;
  }
  if (nbFreeVrtx)
    RepItemSeq->Append(aCompOfVrtx);

  occ::handle<StepShape_ShapeRepresentation> shapeRep =
    occ::down_cast<StepShape_ShapeRepresentation>(SDR0->UsedRepresentation());
  if (shapeRep.IsNull())
  {
    shapeRep = new StepShape_ShapeRepresentation;
    SDR0->SetUsedRepresentation(shapeRep);
  }

  binder = TransientResult(SDR0);

  binder->AddResult(TransientResult(shapeRep));

  int                                                                 i, nbs = RepItemSeq->Length();
  occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>> ItemSeq =
    new NCollection_HSequence<occ::handle<Standard_Transient>>();
  ItemSeq->Append(myContext.GetDefaultAxis());
  myContext.NextLevel();
  Message_ProgressScope aPS(theProgress, nullptr, nbs);
  for (i = 1; i <= nbs && aPS.More(); i++)
  {
    occ::handle<TransferBRep_ShapeMapper> subs =
      TransferBRep::ShapeMapper(FP, RepItemSeq->Value(i));
    occ::handle<StepGeom_GeometricRepresentationItem> AX1;

    occ::handle<Transfer_Binder> bnd = TransferSubShape(subs,
                                                        SDR0,
                                                        AX1,
                                                        FP,
                                                        theLocalFactors,
                                                        NonManifoldGroup,
                                                        isManifold,
                                                        aPS.Next());

    if (!AX1.IsNull())
      ItemSeq->Append(AX1);

    while (!bnd.IsNull())
    {
      occ::handle<Transfer_SimpleBinderOfTransient> bx =
        occ::down_cast<Transfer_SimpleBinderOfTransient>(bnd);
      if (!bx.IsNull())
      {
        binder->AddResult(TransientResult(bx->Result()));
      }
      bnd = bnd->NextResult();
    }
  }
  myContext.PrevLevel();

  int nsub = ItemSeq->Length();
  occ::handle<NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>> items =
    new NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>(1, nsub);

  for (int rep = 1; rep <= nsub; rep++)
    items->SetValue(rep, GetCasted(StepRepr_RepresentationItem, ItemSeq->Value(rep)));
  shapeRep->SetItems(items);
  double                    Tol = UsedTolerance(aStepModel, mytoler, theShape);
  STEPConstruct_UnitContext mk;
  mk.Init(Tol, aStepModel, theLocalFactors);
  shapeRep->SetContextOfItems(mk.Value());
  shapeRep->SetName(new TCollection_HAsciiString(""));

  return binder;
}

occ::handle<Transfer_Binder> STEPControl_ActorWrite::TransferSubShape(
  const occ::handle<Transfer_Finder>&                         start,
  const occ::handle<StepShape_ShapeDefinitionRepresentation>& SDR0,
  occ::handle<StepGeom_GeometricRepresentationItem>&          AX1,
  const occ::handle<Transfer_FinderProcess>&                  FP,
  const StepData_Factors&                                     theLocalFactors,
  const occ::handle<NCollection_HSequence<TopoDS_Shape>>&     shapeGroup,
  const bool                                                  isManifold,
  const Message_ProgressRange&                                theProgress)
{
  occ::handle<TransferBRep_ShapeMapper> mapper = occ::down_cast<TransferBRep_ShapeMapper>(start);
  if (mapper.IsNull())
    return NullResult();
  TopoDS_Shape shape = mapper->Value();

  TopoDS_Shape sh0 = shape;
  gp_Trsf      aLoc;
  bool         isShapeLocated = false;
  if (GroupMode() > 0)
  {
    const TopLoc_Location& shloc = shape.Location();
    isShapeLocated               = !shloc.IsIdentity();
    aLoc                         = shloc.Transformation();
    TopLoc_Location shident;
    sh0.Location(shident);
    mapper = TransferBRep::ShapeMapper(FP, sh0);
    mapper->SameAttributes(start);
  }

  occ::handle<Transfer_Binder>                         resbind = FP->Find(mapper);
  occ::handle<StepShape_ShapeDefinitionRepresentation> sdr;

  STEPConstruct_Part              SDRTool;
  occ::handle<StepData_StepModel> aStepModel = occ::down_cast<StepData_StepModel>(FP->Model());

  bool iasdr =
    FP->GetTypedTransient(resbind, STANDARD_TYPE(StepShape_ShapeDefinitionRepresentation), sdr);
  if (iasdr)
    SDRTool.ReadSDR(sdr);
  else
  {
    SDRTool.MakeSDR(nullptr,
                    myContext.GetProductName(),
                    myContext.GetAPD()->Application(),
                    aStepModel);
    sdr = SDRTool.SDRValue();
  }

  occ::handle<Transfer_Binder> resprod           = TransientResult(sdr);
  bool                         isJustTransferred = false;
  if (!iasdr || resbind.IsNull())
  {
    occ::handle<Transfer_Binder> resbind1 =
      TransferShape(mapper, sdr, FP, theLocalFactors, shapeGroup, isManifold, theProgress);
    if (resbind1.IsNull() || sdr->UsedRepresentation().IsNull())
      return occ::handle<Transfer_Binder>();
    resbind                              = resbind1;
    occ::handle<Transfer_Binder> oldbind = FP->Find(mapper);
    if (!oldbind.IsNull() && !resbind.IsNull())
      resbind->AddResult(oldbind);
    isJustTransferred = true;
  }

  STEPConstruct_Assembly mkitem;

  if (std::abs(aLoc.ScaleFactor() - 1.0) > Precision::Confusion())
  {
    if (aStepModel->InternalParameters.WriteScalingTrsf)
      FP->AddWarning(
        start,
        "The shape has a scaling factor, exported as cartesian_transformation_operator");
    else
      FP->AddWarning(start, "The shape has a scaling factor, skipped");
  }
  if (std::abs(aLoc.ScaleFactor() - 1.0) < Precision::Confusion()
      || !aStepModel->InternalParameters.WriteScalingTrsf)
  {

    GeomToStep_MakeAxis2Placement3d mkax(aLoc, theLocalFactors);
    mkitem.Init(sdr, SDR0, myContext.GetDefaultAxis(), mkax.Value());
    AX1 = mkax.Value();
  }
  else
  {

    GeomToStep_MakeCartesianTransformationOperator aMaker(aLoc, theLocalFactors);
    if (!aMaker.IsDone())
    {
      FP->AddFail(start, "The transformation relation creation failed");
    }
    mkitem.Init(sdr, SDR0, aMaker.Value());
    AX1 = aMaker.Value();
  }

  mkitem.MakeRelationship();
  occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>> roots =
    myContext.GetRootsForAssemblyLink(mkitem);

  if (!iasdr)
  {
    resprod->AddResult(TransientResult(sdr));
    if (resprod != resbind)
      resbind->AddResult(TransientResult(sdr));
    roots->Append(myContext.GetRootsForPart(SDRTool));
  }
  for (int i = 1; i <= roots->Length(); i++)
  {
    resprod->AddResult(TransientResult(roots->Value(i)));
    if (resprod != resbind)
      resbind->AddResult(TransientResult(roots->Value(i)));
  }
  if (isJustTransferred)
  {

    resprod->AddResult(resbind);
    FP->Bind(mapper, resprod);
  }

  myContext.NextIndex();

  if (mapper != start && isShapeLocated)
  {
    occ::handle<Transfer_Binder> bnd = FP->Find(start);
    for (int j = 1; j <= roots->Length(); j++)
      if (bnd.IsNull())
        bnd = TransientResult(roots->Value(j));
      else
        bnd->AddResult(TransientResult(roots->Value(j)));
    FP->Bind(start, bnd);
  }

  return resprod;
}
