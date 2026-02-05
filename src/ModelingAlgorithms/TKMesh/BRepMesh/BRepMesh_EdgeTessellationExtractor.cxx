#include <BRepMesh_EdgeTessellationExtractor.hpp>

#include <BRepMesh_ShapeTool.hpp>
#include <BRep_Tool.hpp>
#include <gp_Pnt.hpp>
#include <IMeshData_Edge.hpp>
#include <IMeshData_Face.hpp>
#include <Poly_Triangulation.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BRepMesh_EdgeTessellationExtractor, IMeshTools_CurveTessellator)

//=================================================================================================

BRepMesh_EdgeTessellationExtractor::BRepMesh_EdgeTessellationExtractor(
  const IMeshData::IEdgeHandle& theEdge,
  const IMeshData::IFaceHandle& theFace)
{
  occ::handle<Poly_Triangulation> aTriangulation =
    BRep_Tool::Triangulation(theFace->GetFace(), myLoc);

  occ::handle<Poly_PolygonOnTriangulation> aPolygon =
    BRep_Tool::PolygonOnTriangulation(theEdge->GetEdge(), aTriangulation, myLoc);

  myTriangulation = aTriangulation.get();
  myIndices       = &aPolygon->Nodes();
  myProvider.Init(theEdge, TopAbs_FORWARD, theFace, aPolygon->Parameters());
}

//=================================================================================================

BRepMesh_EdgeTessellationExtractor::~BRepMesh_EdgeTessellationExtractor() = default;

//=================================================================================================

int BRepMesh_EdgeTessellationExtractor::PointsNb() const
{
  return myIndices->Size();
}

//=================================================================================================

bool BRepMesh_EdgeTessellationExtractor::Value(const int theIndex,
                                               gp_Pnt&   thePoint,
                                               double&   theParameter) const
{
  const gp_Pnt aRefPnt = myTriangulation->Node(myIndices->Value(theIndex));
  thePoint             = BRepMesh_ShapeTool::UseLocation(aRefPnt, myLoc);

  theParameter = myProvider.Parameter(theIndex, thePoint);
  return true;
}
