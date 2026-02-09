#include <BRepSweep_Builder.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Shape.hpp>

BRepSweep_Builder::BRepSweep_Builder(const BRep_Builder& aBuilder)
    : myBuilder(aBuilder)
{
}

void BRepSweep_Builder::MakeCompound(TopoDS_Shape& aCompound) const
{
  myBuilder.MakeCompound(TopoDS::Compound(aCompound));
}

void BRepSweep_Builder::MakeCompSolid(TopoDS_Shape& aCompSolid) const
{
  myBuilder.MakeCompSolid(TopoDS::CompSolid(aCompSolid));
}

void BRepSweep_Builder::MakeSolid(TopoDS_Shape& aSolid) const
{
  myBuilder.MakeSolid(TopoDS::Solid(aSolid));
}

void BRepSweep_Builder::MakeShell(TopoDS_Shape& aShell) const
{
  myBuilder.MakeShell(TopoDS::Shell(aShell));
}

void BRepSweep_Builder::MakeWire(TopoDS_Shape& aWire) const
{
  myBuilder.MakeWire(TopoDS::Wire(aWire));
}

void BRepSweep_Builder::Add(TopoDS_Shape&            aShape1,
                            const TopoDS_Shape&      aShape2,
                            const TopAbs_Orientation Orient) const
{
  TopoDS_Shape aComp = aShape2;
  aComp.Orientation(Orient);
  myBuilder.Add(aShape1, aComp);
}

void BRepSweep_Builder::Add(TopoDS_Shape& aShape1, const TopoDS_Shape& aShape2) const
{
  myBuilder.Add(aShape1, aShape2);
}
