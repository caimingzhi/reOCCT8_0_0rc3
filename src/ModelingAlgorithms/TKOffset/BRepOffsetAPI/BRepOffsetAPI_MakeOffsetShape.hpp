#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BRepOffset_MakeOffset.hpp>
#include <BRepOffset_MakeSimpleOffset.hpp>
#include <BRepBuilderAPI_MakeShape.hpp>
#include <BRepOffset_Mode.hpp>
#include <GeomAbs_JoinType.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
class TopoDS_Shape;

class BRepOffsetAPI_MakeOffsetShape : public BRepBuilderAPI_MakeShape
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepOffsetAPI_MakeOffsetShape();

  Standard_EXPORT void PerformBySimple(const TopoDS_Shape& theS, const double theOffsetValue);

  Standard_EXPORT void PerformByJoin(
    const TopoDS_Shape&          S,
    const double                 Offset,
    const double                 Tol,
    const BRepOffset_Mode        Mode           = BRepOffset_Skin,
    const bool                   Intersection   = false,
    const bool                   SelfInter      = false,
    const GeomAbs_JoinType       Join           = GeomAbs_Arc,
    const bool                   RemoveIntEdges = false,
    const Message_ProgressRange& theRange       = Message_ProgressRange());

  Standard_EXPORT virtual const BRepOffset_MakeOffset& MakeOffset() const;

  Standard_EXPORT void Build(
    const Message_ProgressRange& theRange = Message_ProgressRange()) override;

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& Generated(const TopoDS_Shape& S) override;

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& Modified(const TopoDS_Shape& S) override;

  Standard_EXPORT bool IsDeleted(const TopoDS_Shape& S) override;

  Standard_EXPORT GeomAbs_JoinType GetJoinType() const;

protected:
  enum OffsetAlgo_Type
  {
    OffsetAlgo_NONE,
    OffsetAlgo_JOIN,
    OffsetAlgo_SIMPLE
  };

  OffsetAlgo_Type myLastUsedAlgo;

  BRepOffset_MakeOffset       myOffsetShape;
  BRepOffset_MakeSimpleOffset mySimpleOffsetShape;
};
