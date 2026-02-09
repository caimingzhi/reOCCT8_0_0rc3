#include <AIS_C0RegularityFilter.hpp>
#include <BRep_Tool.hpp>
#include <GeomAbs_Shape.hpp>
#include <Standard_Type.hpp>
#include <StdSelect_BRepOwner.hpp>
#include <TopExp.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedDataMap.hpp>

IMPLEMENT_STANDARD_RTTIEXT(AIS_C0RegularityFilter, SelectMgr_Filter)

AIS_C0RegularityFilter::AIS_C0RegularityFilter(const TopoDS_Shape& aShape)
{
  NCollection_IndexedDataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
    SubShapes;
  TopExp::MapShapesAndAncestors(aShape, TopAbs_EDGE, TopAbs_FACE, SubShapes);
  bool Ok;
  for (int i = 1; i <= SubShapes.Extent(); i++)
  {
    Ok = false;
    NCollection_List<TopoDS_Shape>::Iterator it(SubShapes(i));
    TopoDS_Face                              Face1, Face2;
    if (it.More())
    {
      Face1 = TopoDS::Face(it.Value());
      it.Next();
      if (it.More())
      {
        Face2 = TopoDS::Face(it.Value());
        it.Next();
        if (!it.More())
        {
          GeomAbs_Shape ShapeContinuity =
            BRep_Tool::Continuity(TopoDS::Edge(SubShapes.FindKey(i)), Face1, Face2);
          Ok = (ShapeContinuity == GeomAbs_C0);
        }
      }
    }
    if (Ok)
    {
      const TopoDS_Shape& curEdge = SubShapes.FindKey(i);
      myMapOfEdges.Add(curEdge);
    }
  }
}

bool AIS_C0RegularityFilter::ActsOn(const TopAbs_ShapeEnum aType) const
{
  return (aType == TopAbs_EDGE);
}

bool AIS_C0RegularityFilter::IsOk(const occ::handle<SelectMgr_EntityOwner>& EO) const
{
  occ::handle<StdSelect_BRepOwner> aBO(occ::down_cast<StdSelect_BRepOwner>(EO));
  if (aBO.IsNull())
    return false;

  const TopoDS_Shape& aShape = aBO->Shape();

  if (aShape.ShapeType() != TopAbs_EDGE)
    return false;

  return (myMapOfEdges.Contains(aShape));
}
