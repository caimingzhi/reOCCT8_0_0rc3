#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BRep_Builder.hpp>
#include <TopAbs_Orientation.hpp>
class TopoDS_Shape;

class BRepSweep_Builder
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepSweep_Builder(const BRep_Builder& aBuilder);

  const BRep_Builder& Builder() const;

  Standard_EXPORT void MakeCompound(TopoDS_Shape& aCompound) const;

  Standard_EXPORT void MakeCompSolid(TopoDS_Shape& aCompSolid) const;

  Standard_EXPORT void MakeSolid(TopoDS_Shape& aSolid) const;

  Standard_EXPORT void MakeShell(TopoDS_Shape& aShell) const;

  Standard_EXPORT void MakeWire(TopoDS_Shape& aWire) const;

  Standard_EXPORT void Add(TopoDS_Shape&            aShape1,
                           const TopoDS_Shape&      aShape2,
                           const TopAbs_Orientation Orient) const;

  Standard_EXPORT void Add(TopoDS_Shape& aShape1, const TopoDS_Shape& aShape2) const;

private:
  BRep_Builder myBuilder;
};

inline const BRep_Builder& BRepSweep_Builder::Builder() const
{
  return myBuilder;
}
