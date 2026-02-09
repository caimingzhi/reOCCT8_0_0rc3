#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <BRepFill_Evolved.hpp>
#include <BRepFill_AdvancedEvolved.hpp>
#include <BRepBuilderAPI_MakeShape.hpp>
#include <GeomAbs_JoinType.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
class TopoDS_Wire;
class TopoDS_Shape;

class BRepOffsetAPI_MakeEvolved : public BRepBuilderAPI_MakeShape
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepOffsetAPI_MakeEvolved();

  Standard_EXPORT BRepOffsetAPI_MakeEvolved(const TopoDS_Shape&    theSpine,
                                            const TopoDS_Wire&     theProfile,
                                            const GeomAbs_JoinType theJoinType      = GeomAbs_Arc,
                                            const bool             theIsAxeProf     = true,
                                            const bool             theIsSolid       = false,
                                            const bool             theIsProfOnSpine = false,
                                            const double           theTol           = 0.0000001,
                                            const bool             theIsVolume      = false,
                                            const bool             theRunInParallel = false);

  Standard_EXPORT const BRepFill_Evolved& Evolved() const;

  Standard_EXPORT void Build(
    const Message_ProgressRange& theRange = Message_ProgressRange()) override;

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& GeneratedShapes(
    const TopoDS_Shape& SpineShape,
    const TopoDS_Shape& ProfShape) const;

  Standard_EXPORT const TopoDS_Shape& Top() const;

  Standard_EXPORT const TopoDS_Shape& Bottom() const;

private:
  BRepFill_Evolved         myEvolved;
  BRepFill_AdvancedEvolved myVolume;
  bool                     myIsVolume;
};
