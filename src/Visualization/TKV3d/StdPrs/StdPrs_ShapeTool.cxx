#include <StdPrs_ShapeTool.hpp>

#include <BRep_Tool.hpp>
#include <BRepAdaptor_Curve.hpp>
#include <BRepAdaptor_Surface.hpp>
#include <BRepBndLib.hpp>
#include <BRepTools.hpp>
#include <Geom_Plane.hpp>
#include <Geom_RectangularTrimmedSurface.hpp>
#include <Geom_Surface.hpp>
#include <Poly_Polygon3D.hpp>
#include <Poly_PolygonOnTriangulation.hpp>
#include <Poly_Triangulation.hpp>
#include <TopExp.hpp>
#include <TopLoc_Location.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>

StdPrs_ShapeTool::StdPrs_ShapeTool(const TopoDS_Shape& theShape, const bool theAllVertices)
    : myShape(theShape)
{
  myEdgeMap.Clear();
  myVertexMap.Clear();
  TopExp::MapShapesAndAncestors(theShape, TopAbs_EDGE, TopAbs_FACE, myEdgeMap);

  TopExp_Explorer anExpl;
  if (theAllVertices)
  {
    for (anExpl.Init(theShape, TopAbs_VERTEX); anExpl.More(); anExpl.Next())
    {
      myVertexMap.Add(anExpl.Current());
    }
  }
  else
  {

    for (anExpl.Init(theShape, TopAbs_VERTEX, TopAbs_EDGE); anExpl.More(); anExpl.Next())
    {
      myVertexMap.Add(anExpl.Current());
    }

    for (anExpl.Init(theShape, TopAbs_EDGE); anExpl.More(); anExpl.Next())
    {
      TopoDS_Iterator aIt(anExpl.Current(), false, true);
      for (; aIt.More(); aIt.Next())
      {
        const TopoDS_Shape& aV = aIt.Value();
        if (aV.Orientation() == TopAbs_INTERNAL)
        {
          myVertexMap.Add(aV);
        }
      }
    }
  }
}

Bnd_Box StdPrs_ShapeTool::FaceBound() const
{
  const TopoDS_Face& F = TopoDS::Face(myFaceExplorer.Current());
  Bnd_Box            B;
  BRepBndLib::Add(F, B);
  return B;
}

bool StdPrs_ShapeTool::IsPlanarFace(const TopoDS_Face& theFace)
{
  TopLoc_Location                  l;
  const occ::handle<Geom_Surface>& S = BRep_Tool::Surface(theFace, l);
  if (S.IsNull())
  {
    return false;
  }

  occ::handle<Standard_Type> TheType = S->DynamicType();

  if (TheType == STANDARD_TYPE(Geom_RectangularTrimmedSurface))
  {
    occ::handle<Geom_RectangularTrimmedSurface> RTS =
      occ::down_cast<Geom_RectangularTrimmedSurface>(S);
    TheType = RTS->BasisSurface()->DynamicType();
  }
  return (TheType == STANDARD_TYPE(Geom_Plane));
}

Bnd_Box StdPrs_ShapeTool::CurveBound() const
{
  const TopoDS_Edge& E = TopoDS::Edge(myEdgeMap.FindKey(myEdge));
  Bnd_Box            B;
  BRepBndLib::Add(E, B);
  return B;
}

int StdPrs_ShapeTool::Neighbours() const
{
  const NCollection_List<TopoDS_Shape>& L = myEdgeMap.FindFromIndex(myEdge);
  return L.Extent();
}

occ::handle<NCollection_HSequence<TopoDS_Shape>> StdPrs_ShapeTool::FacesOfEdge() const
{
  occ::handle<NCollection_HSequence<TopoDS_Shape>> H = new NCollection_HSequence<TopoDS_Shape>();
  const NCollection_List<TopoDS_Shape>&            L = myEdgeMap.FindFromIndex(myEdge);
  for (NCollection_List<TopoDS_Shape>::Iterator LI(L); LI.More(); LI.Next())
  {
    H->Append(LI.Value());
  }
  return H;
}

bool StdPrs_ShapeTool::HasSurface() const
{
  TopLoc_Location                  l;
  const occ::handle<Geom_Surface>& S = BRep_Tool::Surface(GetFace(), l);
  return !S.IsNull();
}

occ::handle<Poly_Triangulation> StdPrs_ShapeTool::CurrentTriangulation(TopLoc_Location& l) const
{
  return BRep_Tool::Triangulation(GetFace(), l);
}

bool StdPrs_ShapeTool::HasCurve() const
{
  return BRep_Tool::IsGeometric(GetCurve());
}

void StdPrs_ShapeTool::PolygonOnTriangulation(occ::handle<Poly_PolygonOnTriangulation>& Indices,
                                              occ::handle<Poly_Triangulation>&          T,
                                              TopLoc_Location&                          l) const
{
  BRep_Tool::PolygonOnTriangulation(GetCurve(), Indices, T, l);
}

occ::handle<Poly_Polygon3D> StdPrs_ShapeTool::Polygon3D(TopLoc_Location& l) const
{
  return BRep_Tool::Polygon3D(GetCurve(), l);
}
