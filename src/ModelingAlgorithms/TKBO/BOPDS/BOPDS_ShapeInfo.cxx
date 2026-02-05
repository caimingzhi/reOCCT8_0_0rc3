#include <BOPDS_ShapeInfo.hpp>
#include <TopoDS_Shape.hpp>

#include <cstdio>

//=================================================================================================

void BOPDS_ShapeInfo::Dump() const
{
  const TopAbs_ShapeEnum aTS = ShapeType();
  printf(" %s", TopAbs::ShapeTypeToString(aTS));
  printf(" {");
  for (NCollection_List<int>::Iterator aIt(mySubShapes); aIt.More(); aIt.Next())
  {
    int n = aIt.Value();
    printf(" %d", n);
  }
  printf(" }");
}
