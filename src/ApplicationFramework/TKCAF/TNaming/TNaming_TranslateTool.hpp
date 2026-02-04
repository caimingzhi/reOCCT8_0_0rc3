#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
#include <NCollection_IndexedDataMap.hpp>
class TopoDS_Shape;

//! tool to copy underlying TShape of a Shape.
//! The TranslateTool class is provided to support the
//! translation of topological data structures Transient
//! to Transient.
class TNaming_TranslateTool : public Standard_Transient
{

public:
  Standard_EXPORT void Add(TopoDS_Shape& S1, const TopoDS_Shape& S2) const;

  Standard_EXPORT void MakeVertex(TopoDS_Shape& S) const;

  Standard_EXPORT void MakeEdge(TopoDS_Shape& S) const;

  Standard_EXPORT void MakeWire(TopoDS_Shape& S) const;

  Standard_EXPORT void MakeFace(TopoDS_Shape& S) const;

  Standard_EXPORT void MakeShell(TopoDS_Shape& S) const;

  Standard_EXPORT void MakeSolid(TopoDS_Shape& S) const;

  Standard_EXPORT void MakeCompSolid(TopoDS_Shape& S) const;

  Standard_EXPORT void MakeCompound(TopoDS_Shape& S) const;

  Standard_EXPORT void UpdateVertex(
    const TopoDS_Shape& S1,
    TopoDS_Shape&       S2,
    NCollection_IndexedDataMap<occ::handle<Standard_Transient>, occ::handle<Standard_Transient>>& M)
    const;

  Standard_EXPORT void UpdateEdge(
    const TopoDS_Shape& S1,
    TopoDS_Shape&       S2,
    NCollection_IndexedDataMap<occ::handle<Standard_Transient>, occ::handle<Standard_Transient>>& M)
    const;

  Standard_EXPORT void UpdateFace(
    const TopoDS_Shape& S1,
    TopoDS_Shape&       S2,
    NCollection_IndexedDataMap<occ::handle<Standard_Transient>, occ::handle<Standard_Transient>>& M)
    const;

  Standard_EXPORT void UpdateShape(const TopoDS_Shape& S1, TopoDS_Shape& S2) const;

  DEFINE_STANDARD_RTTIEXT(TNaming_TranslateTool, Standard_Transient)
};

