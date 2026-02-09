#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BRepOffsetAPI_MakeOffsetShape.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <BRepOffset_Mode.hpp>
#include <Standard_Boolean.hpp>
#include <GeomAbs_JoinType.hpp>
class TopoDS_Shape;

class BRepOffsetAPI_MakeThickSolid : public BRepOffsetAPI_MakeOffsetShape
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepOffsetAPI_MakeThickSolid();

  Standard_EXPORT void MakeThickSolidBySimple(const TopoDS_Shape& theS,
                                              const double        theOffsetValue);

  Standard_EXPORT void MakeThickSolidByJoin(
    const TopoDS_Shape&                   S,
    const NCollection_List<TopoDS_Shape>& ClosingFaces,
    const double                          Offset,
    const double                          Tol,
    const BRepOffset_Mode                 Mode           = BRepOffset_Skin,
    const bool                            Intersection   = false,
    const bool                            SelfInter      = false,
    const GeomAbs_JoinType                Join           = GeomAbs_Arc,
    const bool                            RemoveIntEdges = false,
    const Message_ProgressRange&          theRange       = Message_ProgressRange());

  Standard_EXPORT void Build(
    const Message_ProgressRange& theRange = Message_ProgressRange()) override;

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& Modified(const TopoDS_Shape& S) override;
};
