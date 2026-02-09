#include <ChFiDS_Map.hpp>
#include <TopExp.hpp>
#include <TopoDS_Shape.hpp>

ChFiDS_Map::ChFiDS_Map() = default;

void ChFiDS_Map::Fill(const TopoDS_Shape& S, const TopAbs_ShapeEnum T1, const TopAbs_ShapeEnum T2)
{
  TopExp::MapShapesAndAncestors(S, T1, T2, myMap);
}

bool ChFiDS_Map::Contains(const TopoDS_Shape& S) const
{
  return myMap.Contains(S);
}

const NCollection_List<TopoDS_Shape>& ChFiDS_Map::FindFromKey(const TopoDS_Shape& S) const
{
  return myMap.FindFromKey(S);
}

const NCollection_List<TopoDS_Shape>& ChFiDS_Map::FindFromIndex(const int I) const
{
  return myMap.FindFromIndex(I);
}
