#include <IVtkOCC_ShapeMesher.hpp>

#include <Bnd_Box.hpp>
#include <BRep_Tool.hpp>
#include <BRepTools.hpp>
#include <Message.hpp>
#include <NCollection_Array1.hpp>
#include <Poly_Polygon3D.hpp>
#include <Poly_PolygonOnTriangulation.hpp>
#include <Poly_Triangulation.hpp>
#include <Prs3d.hpp>
#include <Prs3d_Drawer.hpp>
#include <Standard_ErrorHandler.hpp>
#include <StdPrs_Isolines.hpp>
#include <StdPrs_ToolTriangulatedShape.hpp>
#include <TopExp.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedDataMap.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IVtkOCC_ShapeMesher, IVtk_IShapeMesher)

IVtkOCC_ShapeMesher::IVtkOCC_ShapeMesher() = default;

IVtkOCC_ShapeMesher::~IVtkOCC_ShapeMesher() = default;

void IVtkOCC_ShapeMesher::internalBuild()
{
  const TopoDS_Shape& anOcctShape = GetShapeObj()->GetShape();
  if (anOcctShape.IsNull())
  {
    return;
  }

  const occ::handle<Prs3d_Drawer>& anOcctDrawer = GetShapeObj()->Attributes();
  const double                     aShapeDeflection =
    StdPrs_ToolTriangulatedShape::GetDeflection(anOcctShape, anOcctDrawer);
  if (anOcctDrawer->IsAutoTriangulation())
  {
    StdPrs_ToolTriangulatedShape::ClearOnOwnDeflectionChange(anOcctShape, anOcctDrawer, true);
    StdPrs_ToolTriangulatedShape::Tessellate(anOcctShape, anOcctDrawer);
  }
  for (TopExp_Explorer aFaceIter(anOcctShape, TopAbs_FACE); aFaceIter.More(); aFaceIter.Next())
  {
    const TopoDS_Face& anOcctFace = TopoDS::Face(aFaceIter.Current());
    TopLoc_Location    aLoc;
    if (const occ::handle<Poly_Triangulation>& anOcctTriangulation =
          BRep_Tool::Triangulation(anOcctFace, aLoc))
    {
      StdPrs_ToolTriangulatedShape::ComputeNormals(anOcctFace, anOcctTriangulation);
    }
  }

  addFreeVertices();
  addEdges();

  for (TopExp_Explorer aFaceIter(anOcctShape, TopAbs_FACE); aFaceIter.More(); aFaceIter.Next())
  {
    const TopoDS_Face& anOcctFace = TopoDS::Face(aFaceIter.Current());
    try
    {
      OCC_CATCH_SIGNALS
      addWFFace(anOcctFace, GetShapeObj()->GetSubShapeId(anOcctFace), aShapeDeflection);
    }
    catch (const Standard_Failure& anException)
    {
      Message::SendFail(TCollection_AsciiString(
                          "Error: addWireFrameFaces() wireframe presentation builder has failed (")
                        + anException.what() + ")");
    }
  }

  for (TopExp_Explorer aFaceIter(anOcctShape, TopAbs_FACE); aFaceIter.More(); aFaceIter.Next())
  {
    const TopoDS_Face& anOcctFace = TopoDS::Face(aFaceIter.Current());
    addShadedFace(anOcctFace, GetShapeObj()->GetSubShapeId(anOcctFace));
  }
}

const IVtkOCC_Shape::Handle IVtkOCC_ShapeMesher::GetShapeObj() const
{
  return IVtkOCC_Shape::Handle::DownCast(myShapeObj);
}

double IVtkOCC_ShapeMesher::GetDeflection() const
{
  const TopoDS_Shape& anOcctShape = GetShapeObj()->GetShape();
  return !anOcctShape.IsNull()
           ? StdPrs_ToolTriangulatedShape::GetDeflection(anOcctShape, GetShapeObj()->Attributes())
           : 0.0;
}

double IVtkOCC_ShapeMesher::GetDeviationCoeff() const
{
  if (IVtkOCC_Shape::Handle aShape = GetShapeObj())
  {
    return aShape->Attributes()->DeviationCoefficient();
  }
  return 0.0;
}

double IVtkOCC_ShapeMesher::GetDeviationAngle() const
{
  if (IVtkOCC_Shape::Handle aShape = GetShapeObj())
  {
    return aShape->Attributes()->DeviationAngle();
  }
  return 0.0;
}

void IVtkOCC_ShapeMesher::addFreeVertices()
{
  NCollection_IndexedDataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
    aVertexMap;
  TopExp::MapShapesAndAncestors(GetShapeObj()->GetShape(), TopAbs_VERTEX, TopAbs_EDGE, aVertexMap);

  int           aVertNum = aVertexMap.Extent();
  IVtk_MeshType aType;
  for (int anIt = 1; anIt <= aVertNum; anIt++)
  {
    if (aVertexMap.FindFromIndex(anIt).IsEmpty())
    {
      aType = MT_FreeVertex;
    }
    else
    {
      aType = MT_SharedVertex;
    }
    const TopoDS_Vertex& aVertex = TopoDS::Vertex(aVertexMap.FindKey(anIt));
    addVertex(aVertex, GetShapeObj()->GetSubShapeId(aVertex), aType);
  }
}

void IVtkOCC_ShapeMesher::addEdges()
{
  NCollection_IndexedDataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
    anEdgesMap;
  TopExp::MapShapesAndAncestors(GetShapeObj()->GetShape(), TopAbs_EDGE, TopAbs_FACE, anEdgesMap);
  int           aNbFaces;
  IVtk_MeshType aType;
  myEdgesTypes.Clear();

  NCollection_IndexedDataMap<TopoDS_Shape,
                             NCollection_List<TopoDS_Shape>,
                             TopTools_ShapeMapHasher>::Iterator aEdgeIt(anEdgesMap);
  for (; aEdgeIt.More(); aEdgeIt.Next())
  {
    const TopoDS_Edge&                    anOcctEdge = TopoDS::Edge(aEdgeIt.Key());
    const NCollection_List<TopoDS_Shape>& aFaceList  = aEdgeIt.Value();
    aNbFaces                                         = aFaceList.Extent();
    if (aNbFaces == 0)
    {
      aType = MT_FreeEdge;
    }
    else if (aNbFaces == 1)
    {
      aType = MT_BoundaryEdge;
    }
    else
    {
      aType = (aNbFaces >= 2) && (BRep_Tool::MaxContinuity(anOcctEdge) > GeomAbs_G2)
                ? MT_SeamEdge
                : MT_SharedEdge;
    }
    addEdge(anOcctEdge, GetShapeObj()->GetSubShapeId(anOcctEdge), aType);
    myEdgesTypes.Bind(anOcctEdge, aType);
  }
}

void IVtkOCC_ShapeMesher::addVertex(const TopoDS_Vertex& theVertex,
                                    const IVtk_IdType    theShapeId,
                                    const IVtk_MeshType  theMeshType)
{
  if (theVertex.IsNull())
  {
    return;
  }

  gp_Pnt aPnt3d = BRep_Tool::Pnt(theVertex);

  IVtk_PointId anId = myShapeData->InsertCoordinate(aPnt3d);
  myShapeData->InsertVertex(theShapeId, anId, theMeshType);
}

void IVtkOCC_ShapeMesher::addEdge(const TopoDS_Edge&  theEdge,
                                  const IVtk_IdType   theShapeId,
                                  const IVtk_MeshType theMeshType)
{
  if (theEdge.IsNull() || BRep_Tool::Degenerated(theEdge))
  {
    return;
  }

  occ::handle<Poly_PolygonOnTriangulation> aPolyOnTriangulation;
  occ::handle<Poly_Triangulation>          aTriangulation;
  TopLoc_Location                          aLoc;
  BRep_Tool::PolygonOnTriangulation(theEdge, aPolyOnTriangulation, aTriangulation, aLoc, 1);
  if (!aPolyOnTriangulation.IsNull() && aPolyOnTriangulation->NbNodes() >= 2)
  {

    const gp_Trsf aTrsf        = aLoc.Transformation();
    const bool    hasTransform = !aLoc.IsIdentity();

    NCollection_List<IVtk_PointId> aPolyPointIds;
    const int                      aNbNodes = aPolyOnTriangulation->NbNodes();
    for (int aJ = 0; aJ < aNbNodes; aJ++)
    {
      const int aPntId = aPolyOnTriangulation->Node(aJ + 1);
      gp_Pnt    aPoint = aTriangulation->Node(aPntId);
      gp_Dir    aNorm  = aTriangulation->HasNormals() ? aTriangulation->Normal(aPntId) : gp::DZ();
      if (hasTransform)
      {
        aPoint.Transform(aTrsf);
        aNorm.Transform(aTrsf);
      }

      IVtk_PointId anId = myShapeData->InsertPoint(
        aPoint,
        NCollection_Vec3<float>((float)aNorm.X(), (float)aNorm.Y(), (float)aNorm.Z()));
      aPolyPointIds.Append(anId);
    }
    myShapeData->InsertLine(theShapeId, &aPolyPointIds, theMeshType);
    return;
  }

  occ::handle<Poly_Polygon3D> aPoly3d = BRep_Tool::Polygon3D(theEdge, aLoc);
  if (aPoly3d.IsNull() || aPoly3d->NbNodes() < 2)
  {
    return;
  }

  const gp_Trsf                  anEdgeTransf = aLoc.Transformation();
  const bool                     noTransform  = aLoc.IsIdentity();
  NCollection_List<IVtk_PointId> aPolyPointIds;
  for (int aNodeIter = 1; aNodeIter <= aPoly3d->NbNodes(); ++aNodeIter)
  {
    gp_Pnt aPnt = aPoly3d->Nodes().Value(aNodeIter);
    if (!noTransform)
    {
      aPnt.Transform(anEdgeTransf);
    }

    const IVtk_PointId anId = myShapeData->InsertCoordinate(aPnt);
    aPolyPointIds.Append(anId);
  }
  myShapeData->InsertLine(theShapeId, &aPolyPointIds, theMeshType);
}

void IVtkOCC_ShapeMesher::addWFFace(const TopoDS_Face& theFace,
                                    const IVtk_IdType  theShapeId,
                                    const double       theDeflection)
{
  if (theFace.IsNull())
  {
    return;
  }

  TopoDS_Face aFaceToMesh = theFace;
  aFaceToMesh.Orientation(TopAbs_FORWARD);

  for (TopExp_Explorer anEdgeIter(aFaceToMesh, TopAbs_EDGE); anEdgeIter.More(); anEdgeIter.Next())
  {
    const TopoDS_Edge& anOcctEdge = TopoDS::Edge(anEdgeIter.Current());
    addEdge(anOcctEdge, theShapeId, myEdgesTypes(anOcctEdge));
  }

  TopLoc_Location                  aLoc;
  const occ::handle<Geom_Surface>& aGeomSurf = BRep_Tool::Surface(aFaceToMesh, aLoc);
  if (aGeomSurf.IsNull())
  {
    return;
  }

  NCollection_List<occ::handle<NCollection_HSequence<gp_Pnt>>> aPolylines;
  StdPrs_Isolines::Add(theFace, GetShapeObj()->Attributes(), theDeflection, aPolylines, aPolylines);
  for (NCollection_List<occ::handle<NCollection_HSequence<gp_Pnt>>>::Iterator aPolyIter(aPolylines);
       aPolyIter.More();
       aPolyIter.Next())
  {
    const occ::handle<NCollection_HSequence<gp_Pnt>>& aPoints    = aPolyIter.Value();
    const int                                         theNbNodes = aPoints->Length();
    if (theNbNodes < 2)
    {
      continue;
    }

    NCollection_List<IVtk_PointId> aPolyPointIds;
    for (NCollection_HSequence<gp_Pnt>::Iterator aNodeIter(*aPoints); aNodeIter.More();
         aNodeIter.Next())
    {
      const gp_Pnt&      aPnt = aNodeIter.Value();
      const IVtk_PointId anId = myShapeData->InsertCoordinate(aPnt);
      aPolyPointIds.Append(anId);
    }

    myShapeData->InsertLine(theShapeId, &aPolyPointIds, MT_IsoLine);
  }
}

void IVtkOCC_ShapeMesher::addShadedFace(const TopoDS_Face& theFace, const IVtk_IdType theShapeId)
{
  if (theFace.IsNull())
  {
    return;
  }

  TopLoc_Location                        aLoc;
  const occ::handle<Poly_Triangulation>& anOcctTriangulation =
    BRep_Tool::Triangulation(theFace, aLoc);
  if (anOcctTriangulation.IsNull())
  {
    return;
  }

  const gp_Trsf aTrsf        = aLoc.Transformation();
  const bool    hasTransform = !aLoc.IsIdentity();
  const bool    isMirrored   = aTrsf.VectorialPart().Determinant() < 0;

  int aNbPoints = anOcctTriangulation->NbNodes();

  NCollection_Array1<IVtk_PointId> aPointIds(1, aNbPoints);
  IVtk_PointId                     anId;
  for (int anI = 1; anI <= aNbPoints; anI++)
  {
    gp_Pnt aPoint = anOcctTriangulation->Node(anI);
    gp_Dir aNorm  = anOcctTriangulation->HasNormals() ? anOcctTriangulation->Normal(anI) : gp::DZ();
    if ((theFace.Orientation() == TopAbs_REVERSED) ^ isMirrored)
    {
      aNorm.Reverse();
    }
    if (hasTransform)
    {
      aPoint.Transform(aTrsf);
      aNorm.Transform(aTrsf);
    }

    anId = myShapeData->InsertPoint(
      aPoint,
      NCollection_Vec3<float>((float)aNorm.X(), (float)aNorm.Y(), (float)aNorm.Z()));
    aPointIds.SetValue(anI, anId);
  }

  const int aNbTriangles = anOcctTriangulation->NbTriangles();
  int       aN1, aN2, aN3;
  for (int anI = 1; anI <= aNbTriangles; anI++)
  {
    if (theFace.Orientation() == TopAbs_REVERSED)
    {
      anOcctTriangulation->Triangle(anI).Get(aN1, aN3, aN2);
    }
    else
    {
      anOcctTriangulation->Triangle(anI).Get(aN1, aN2, aN3);
    }

    myShapeData->InsertTriangle(theShapeId,
                                aPointIds(aN1),
                                aPointIds(aN2),
                                aPointIds(aN3),
                                MT_ShadedFace);
  }
}
