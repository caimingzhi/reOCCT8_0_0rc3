#include <TopTools.hpp>

#include <TopTools_ShapeSet.hpp>

void TopTools::Dump(const TopoDS_Shape& Sh, Standard_OStream& S)
{
  TopTools_ShapeSet SSet;
  SSet.Add(Sh);
  SSet.Dump(Sh, S);
  SSet.Dump(S);
}

void TopTools::Dummy(const int) {}
