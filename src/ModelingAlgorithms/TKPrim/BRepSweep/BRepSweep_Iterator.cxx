#include <BRepSweep_Iterator.hpp>
#include <TopoDS_Shape.hpp>

//=================================================================================================

BRepSweep_Iterator::BRepSweep_Iterator() = default;

//=================================================================================================

void BRepSweep_Iterator::Init(const TopoDS_Shape& aShape)
{
  myIterator.Initialize(aShape);
}

//=================================================================================================

void BRepSweep_Iterator::Next()
{
  myIterator.Next();
}
