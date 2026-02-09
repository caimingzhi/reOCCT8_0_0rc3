#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <BRepSweep_Prism.hpp>
#include <BRepPrimAPI_MakeSweep.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
class TopoDS_Shape;
class gp_Vec;
class gp_Dir;

class BRepPrimAPI_MakePrism : public BRepPrimAPI_MakeSweep
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepPrimAPI_MakePrism(const TopoDS_Shape& S,
                                        const gp_Vec&       V,
                                        const bool          Copy     = false,
                                        const bool          Canonize = true);

  Standard_EXPORT BRepPrimAPI_MakePrism(const TopoDS_Shape& S,
                                        const gp_Dir&       D,
                                        const bool          Inf      = true,
                                        const bool          Copy     = false,
                                        const bool          Canonize = true);

  Standard_EXPORT const BRepSweep_Prism& Prism() const;

  Standard_EXPORT void Build(
    const Message_ProgressRange& theRange = Message_ProgressRange()) override;

  Standard_EXPORT TopoDS_Shape FirstShape() override;

  Standard_EXPORT TopoDS_Shape LastShape() override;

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& Generated(const TopoDS_Shape& S) override;

  Standard_EXPORT bool IsDeleted(const TopoDS_Shape& S) override;

  Standard_EXPORT TopoDS_Shape FirstShape(const TopoDS_Shape& theShape);

  Standard_EXPORT TopoDS_Shape LastShape(const TopoDS_Shape& theShape);

private:
  BRepSweep_Prism myPrism;
};
