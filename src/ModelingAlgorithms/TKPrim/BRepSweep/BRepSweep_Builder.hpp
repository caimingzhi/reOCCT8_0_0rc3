#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BRep_Builder.hpp>
#include <TopAbs_Orientation.hpp>
class TopoDS_Shape;

//! implements the abstract Builder with the BRep Builder
class BRepSweep_Builder
{
public:
  DEFINE_STANDARD_ALLOC

  //! Creates a Builder.
  Standard_EXPORT BRepSweep_Builder(const BRep_Builder& aBuilder);

  const BRep_Builder& Builder() const;

  //! Returns an empty Compound.
  Standard_EXPORT void MakeCompound(TopoDS_Shape& aCompound) const;

  //! Returns an empty CompSolid.
  Standard_EXPORT void MakeCompSolid(TopoDS_Shape& aCompSolid) const;

  //! Returns an empty Solid.
  Standard_EXPORT void MakeSolid(TopoDS_Shape& aSolid) const;

  //! Returns an empty Shell.
  Standard_EXPORT void MakeShell(TopoDS_Shape& aShell) const;

  //! Returns an empty Wire.
  Standard_EXPORT void MakeWire(TopoDS_Shape& aWire) const;

  //! Adds the Shape 1 in the Shape 2, set to
  //! <Orient> orientation.
  Standard_EXPORT void Add(TopoDS_Shape&            aShape1,
                           const TopoDS_Shape&      aShape2,
                           const TopAbs_Orientation Orient) const;

  //! Adds the Shape 1 in the Shape 2.
  Standard_EXPORT void Add(TopoDS_Shape& aShape1, const TopoDS_Shape& aShape2) const;

private:
  BRep_Builder myBuilder;
};

inline const BRep_Builder& BRepSweep_Builder::Builder() const
{
  return myBuilder;
}
