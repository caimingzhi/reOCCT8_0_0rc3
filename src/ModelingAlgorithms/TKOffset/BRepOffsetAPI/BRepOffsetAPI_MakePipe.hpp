#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BRepFill_Pipe.hpp>
#include <BRepPrimAPI_MakeSweep.hpp>
#include <GeomFill_Trihedron.hpp>
class TopoDS_Wire;
class TopoDS_Shape;

class BRepOffsetAPI_MakePipe : public BRepPrimAPI_MakeSweep
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepOffsetAPI_MakePipe(const TopoDS_Wire& Spine, const TopoDS_Shape& Profile);

  Standard_EXPORT BRepOffsetAPI_MakePipe(const TopoDS_Wire&       Spine,
                                         const TopoDS_Shape&      Profile,
                                         const GeomFill_Trihedron aMode,
                                         const bool               ForceApproxC1 = false);

  Standard_EXPORT const BRepFill_Pipe& Pipe() const;

  Standard_EXPORT void Build(
    const Message_ProgressRange& theRange = Message_ProgressRange()) override;

  Standard_EXPORT TopoDS_Shape FirstShape() override;

  Standard_EXPORT TopoDS_Shape LastShape() override;

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& Generated(const TopoDS_Shape& S) override;

  Standard_EXPORT TopoDS_Shape Generated(const TopoDS_Shape& SSpine, const TopoDS_Shape& SProfile);

  Standard_EXPORT double ErrorOnSurface() const;

private:
  BRepFill_Pipe myPipe;
};
