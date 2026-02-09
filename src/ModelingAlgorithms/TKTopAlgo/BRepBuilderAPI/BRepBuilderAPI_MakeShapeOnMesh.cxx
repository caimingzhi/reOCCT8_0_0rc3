#include <BRepBuilderAPI_MakeShapeOnMesh.hpp>

#include <BRep_Builder.hpp>
#include <BRepAdaptor_Curve.hpp>
#include <BRepBuilderAPI_MakeEdge.hpp>
#include <BRepBuilderAPI_MakeFace.hpp>
#include <BRepBuilderAPI_MakeVertex.hpp>
#include <BRepBuilderAPI_MakeWire.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <Standard_HashUtils.hpp>

namespace
{

  struct Edge
  {

    Edge(const int TheIdx1, const int TheIdx2)
        : Idx1(std::min(TheIdx1, TheIdx2)),
          Idx2(std::max(TheIdx1, TheIdx2))
    {
    }

    bool operator<(const Edge& other) const
    {
      return Idx1 < other.Idx1 || (Idx1 == other.Idx1 && Idx2 < other.Idx2);
    }

    bool operator==(const Edge& theOther) const
    {
      return theOther.Idx1 == Idx1 && theOther.Idx2 == Idx2;
    }

    int Idx1;

    int Idx2;
  };
} // namespace

namespace std
{
  template <>
  struct hash<Edge>
  {
    size_t operator()(const Edge& theEdge) const noexcept
    {

      int aCombination[2]{theEdge.Idx1, theEdge.Idx2};
      return opencascade::hashBytes(aCombination, sizeof(aCombination));
    }
  };
} // namespace std

void BRepBuilderAPI_MakeShapeOnMesh::Build(const Message_ProgressRange& theRange)
{

  if (myMesh.IsNull() || myMesh->NbNodes() == 0 || myMesh->NbTriangles() == 0)
    return;

  const int aNbNodes     = myMesh->NbNodes();
  const int aNbTriangles = myMesh->NbTriangles();

  Message_ProgressScope aPS(theRange,
                            "Per-facet shape construction",
                            double(aNbNodes + 2 * aNbTriangles));

  NCollection_IndexedDataMap<int, TopoDS_Vertex> aPnt2VertexMap;

  for (int i = 1; i <= aNbNodes; ++i)
  {
    aPS.Next();
    if (aPS.UserBreak())
      return;

    const gp_Pnt        aP = myMesh->Node(i);
    const TopoDS_Vertex aV = BRepBuilderAPI_MakeVertex(aP);
    aPnt2VertexMap.Add(i, aV);
  }

  NCollection_IndexedDataMap<Edge, TopoDS_Edge> anEdgeToTEgeMap;
  for (int i = 1; i <= aNbTriangles; ++i)
  {
    aPS.Next();
    if (aPS.UserBreak())
      return;

    int                  anIdx[3];
    const Poly_Triangle& aTriangle = myMesh->Triangle(i);
    aTriangle.Get(anIdx[0], anIdx[1], anIdx[2]);

    if (anIdx[0] == anIdx[1] || anIdx[0] == anIdx[2] || anIdx[1] == anIdx[2])
      continue;

    const gp_Pnt aP1 = myMesh->Node(anIdx[0]);
    const gp_Pnt aP2 = myMesh->Node(anIdx[1]);
    const gp_Pnt aP3 = myMesh->Node(anIdx[2]);
    const double aD1 = aP1.SquareDistance(aP2);
    const double aD2 = aP1.SquareDistance(aP3);
    const double aD3 = aP2.SquareDistance(aP3);
    if (aD1 < gp::Resolution() || aD2 < gp::Resolution() || aD3 < gp::Resolution())
    {
      continue;
    }

    const TopoDS_Vertex& aV1 = aPnt2VertexMap.FindFromKey(anIdx[0]);
    const TopoDS_Vertex& aV2 = aPnt2VertexMap.FindFromKey(anIdx[1]);
    const TopoDS_Vertex& aV3 = aPnt2VertexMap.FindFromKey(anIdx[2]);

    const Edge aMeshEdge1(anIdx[0], anIdx[1]);
    const Edge aMeshEdge2(anIdx[1], anIdx[2]);
    const Edge aMeshEdge3(anIdx[2], anIdx[0]);

    BRepBuilderAPI_MakeEdge aMaker1(aV1, aV2);
    BRepBuilderAPI_MakeEdge aMaker2(aV2, aV3);
    BRepBuilderAPI_MakeEdge aMaker3(aV3, aV1);

    TopoDS_Edge aTE1 = aMaker1.Edge();
    if (anIdx[1] < anIdx[0])
      aTE1.Reverse();

    TopoDS_Edge aTE2 = aMaker2.Edge();
    if (anIdx[2] < anIdx[1])
      aTE2.Reverse();

    TopoDS_Edge aTE3 = aMaker3.Edge();
    if (anIdx[0] < anIdx[2])
      aTE3.Reverse();

    anEdgeToTEgeMap.Add(aMeshEdge1, aTE1);
    anEdgeToTEgeMap.Add(aMeshEdge2, aTE2);
    anEdgeToTEgeMap.Add(aMeshEdge3, aTE3);
  }

  TopoDS_Compound aResult;
  BRep_Builder    aBB;
  aBB.MakeCompound(aResult);
  for (int i = 1; i <= aNbTriangles; ++i)
  {
    aPS.Next();
    if (aPS.UserBreak())
      return;

    int                  anIdx[3];
    const Poly_Triangle& aTriangle = myMesh->Triangle(i);
    aTriangle.Get(anIdx[0], anIdx[1], anIdx[2]);

    const Edge aMeshEdge1(anIdx[0], anIdx[1]);
    const Edge aMeshEdge2(anIdx[1], anIdx[2]);
    const Edge aMeshEdge3(anIdx[2], anIdx[0]);
    const bool isReversed1 = anIdx[1] < anIdx[0];
    const bool isReversed2 = anIdx[2] < anIdx[1];
    const bool isReversed3 = anIdx[0] < anIdx[2];

    const bool aHasAllEdges = anEdgeToTEgeMap.Contains(aMeshEdge1)
                              && anEdgeToTEgeMap.Contains(aMeshEdge2)
                              && anEdgeToTEgeMap.Contains(aMeshEdge3);
    if (!aHasAllEdges)
      continue;

    TopoDS_Edge aTEdge1 = anEdgeToTEgeMap.FindFromKey(aMeshEdge1);
    if (isReversed1)
      aTEdge1.Reverse();
    TopoDS_Edge aTEdge2 = anEdgeToTEgeMap.FindFromKey(aMeshEdge2);
    if (isReversed2)
      aTEdge2.Reverse();
    TopoDS_Edge aTEdge3 = anEdgeToTEgeMap.FindFromKey(aMeshEdge3);
    if (isReversed3)
      aTEdge3.Reverse();

    BRepBuilderAPI_MakeWire aWireMaker;
    aWireMaker.Add(aTEdge1);
    aWireMaker.Add(aTEdge2);
    aWireMaker.Add(aTEdge3);
    const TopoDS_Wire aWire = aWireMaker.Wire();

    BRepAdaptor_Curve aC1(aTEdge1);
    BRepAdaptor_Curve aC2(aTEdge2);
    const gp_Dir      aD1 = aC1.Line().Direction();
    const gp_Dir      aD2 = aC2.Line().Direction();
    gp_XYZ            aN  = aD1.XYZ().Crossed(aD2.XYZ());
    if (aN.SquareModulus() < Precision::SquareConfusion())
      continue;
    if (aTEdge1.Orientation() == TopAbs_REVERSED)
      aN.Reverse();
    if (aTEdge2.Orientation() == TopAbs_REVERSED)
      aN.Reverse();
    const gp_Dir aNorm(aN);
    gp_Pln       aPln(myMesh->Node(anIdx[0]), aNorm);

    BRepBuilderAPI_MakeFace aFaceMaker(aPln, aWire);
    const TopoDS_Face&      aFace = aFaceMaker.Face();

    aBB.Add(aResult, aFace);
  }

  this->Done();
  myShape = aResult;
}
