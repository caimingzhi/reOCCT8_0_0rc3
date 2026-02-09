#include <IMeshTools_ShapeExplorer.hpp>
#include <TopExp.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <BRepLib.hpp>
#include <BRep_Tool.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_Map.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IMeshTools_ShapeExplorer, IMeshData_Shape)

namespace
{

  void visitEdges(const occ::handle<IMeshTools_ShapeVisitor>& theVisitor,
                  const TopoDS_Shape&                         theShape,
                  const bool                                  isResetLocation,
                  const TopAbs_ShapeEnum                      theToFind,
                  const TopAbs_ShapeEnum                      theToAvoid = TopAbs_SHAPE)
  {
    TopExp_Explorer aEdgesIt(theShape, theToFind, theToAvoid);
    for (; aEdgesIt.More(); aEdgesIt.Next())
    {
      const TopoDS_Edge& aEdge = TopoDS::Edge(aEdgesIt.Current());
      if (!BRep_Tool::IsGeometric(aEdge))
      {
        continue;
      }

      theVisitor->Visit(isResetLocation ? TopoDS::Edge(aEdge.Located(TopLoc_Location())) : aEdge);
    }
  }
} // namespace

IMeshTools_ShapeExplorer::IMeshTools_ShapeExplorer(const TopoDS_Shape& theShape)
    : IMeshData_Shape(theShape)
{
}

IMeshTools_ShapeExplorer::~IMeshTools_ShapeExplorer() = default;

void IMeshTools_ShapeExplorer::Accept(const occ::handle<IMeshTools_ShapeVisitor>& theVisitor)
{

  visitEdges(theVisitor, GetShape(), true, TopAbs_EDGE, TopAbs_FACE);

  NCollection_List<TopoDS_Shape> aFaceList;
  BRepLib::ReverseSortFaces(GetShape(), aFaceList);
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> aFaceMap;

  const TopLoc_Location                    aEmptyLoc;
  NCollection_List<TopoDS_Shape>::Iterator aFaceIter(aFaceList);
  for (; aFaceIter.More(); aFaceIter.Next())
  {
    TopoDS_Shape aFaceNoLoc = aFaceIter.Value();
    aFaceNoLoc.Location(aEmptyLoc);
    if (!aFaceMap.Add(aFaceNoLoc))
    {
      continue;
    }

    const TopoDS_Face& aFace = TopoDS::Face(aFaceIter.Value());
    if (!BRep_Tool::IsGeometric(aFace))
    {
      continue;
    }

    visitEdges(theVisitor, aFace, false, TopAbs_EDGE);

    theVisitor->Visit(TopoDS::Face(aFace.Oriented(TopAbs_FORWARD)));
  }
}
