#include <TopExp.hpp>
#include <TopoDS_Shape.hpp>
#include <TopOpeBRepTool_AncestorsTool.hpp>

void TopOpeBRepTool_AncestorsTool::MakeAncestors(
  const TopoDS_Shape&    S,
  const TopAbs_ShapeEnum TS,
  const TopAbs_ShapeEnum TA,
  NCollection_IndexedDataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>&
    M)
{
  TopExp::MapShapesAndAncestors(S, TS, TA, M);
}
