#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <TopoDS_Face.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <BRepFill_OffsetWire.hpp>
#include <BRepBuilderAPI_MakeShape.hpp>
class TopoDS_Wire;
class TopoDS_Shape;

class BRepOffsetAPI_MakeOffset : public BRepBuilderAPI_MakeShape
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepOffsetAPI_MakeOffset();

  Standard_EXPORT BRepOffsetAPI_MakeOffset(const TopoDS_Face&     Spine,
                                           const GeomAbs_JoinType Join         = GeomAbs_Arc,
                                           const bool             IsOpenResult = false);

  Standard_EXPORT void Init(const TopoDS_Face&     Spine,
                            const GeomAbs_JoinType Join         = GeomAbs_Arc,
                            const bool             IsOpenResult = false);

  Standard_EXPORT BRepOffsetAPI_MakeOffset(const TopoDS_Wire&     Spine,
                                           const GeomAbs_JoinType Join         = GeomAbs_Arc,
                                           const bool             IsOpenResult = false);

  Standard_EXPORT void Init(const GeomAbs_JoinType Join         = GeomAbs_Arc,
                            const bool             IsOpenResult = false);

  Standard_EXPORT void SetApprox(const bool ToApprox);

  Standard_EXPORT void AddWire(const TopoDS_Wire& Spine);

  Standard_EXPORT void Perform(const double Offset, const double Alt = 0.0);

  Standard_EXPORT void Build(
    const Message_ProgressRange& theRange = Message_ProgressRange()) override;

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& Generated(const TopoDS_Shape& S) override;

  Standard_EXPORT static TopoDS_Face ConvertFace(const TopoDS_Face& theFace,
                                                 const double       theAngleTolerance);

private:
  bool                                  myIsInitialized;
  bool                                  myLastIsLeft;
  GeomAbs_JoinType                      myJoin;
  bool                                  myIsOpenResult;
  bool                                  myIsToApprox;
  TopoDS_Face                           myFace;
  NCollection_List<TopoDS_Shape>        myWires;
  NCollection_List<BRepFill_OffsetWire> myLeft;
  NCollection_List<BRepFill_OffsetWire> myRight;
};
