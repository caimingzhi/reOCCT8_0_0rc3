#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <BRepSweep_Builder.hpp>
#include <TopoDS_Shape.hpp>
#include <BRepSweep_Tool.hpp>
#include <Sweep_NumShapeTool.hpp>
#include <NCollection_Array2.hpp>
#include <TopAbs_Orientation.hpp>

class BRepSweep_NumLinearRegularSweep
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT virtual TopoDS_Shape MakeEmptyVertex(const TopoDS_Shape&   aGenV,
                                                       const Sweep_NumShape& aDirV) = 0;
  Standard_EXPORT virtual ~BRepSweep_NumLinearRegularSweep();

  Standard_EXPORT virtual TopoDS_Shape MakeEmptyDirectingEdge(const TopoDS_Shape&   aGenV,
                                                              const Sweep_NumShape& aDirE) = 0;

  Standard_EXPORT virtual TopoDS_Shape MakeEmptyGeneratingEdge(const TopoDS_Shape&   aGenE,
                                                               const Sweep_NumShape& aDirV) = 0;

  Standard_EXPORT virtual void SetParameters(const TopoDS_Shape&   aNewFace,
                                             TopoDS_Shape&         aNewVertex,
                                             const TopoDS_Shape&   aGenF,
                                             const TopoDS_Shape&   aGenV,
                                             const Sweep_NumShape& aDirV) = 0;

  Standard_EXPORT virtual void SetDirectingParameter(const TopoDS_Shape&   aNewEdge,
                                                     TopoDS_Shape&         aNewVertex,
                                                     const TopoDS_Shape&   aGenV,
                                                     const Sweep_NumShape& aDirE,
                                                     const Sweep_NumShape& aDirV) = 0;

  Standard_EXPORT virtual void SetGeneratingParameter(const TopoDS_Shape&   aNewEdge,
                                                      TopoDS_Shape&         aNewVertex,
                                                      const TopoDS_Shape&   aGenE,
                                                      const TopoDS_Shape&   aGenV,
                                                      const Sweep_NumShape& aDirV) = 0;

  Standard_EXPORT virtual TopoDS_Shape MakeEmptyFace(const TopoDS_Shape&   aGenS,
                                                     const Sweep_NumShape& aDirS) = 0;

  Standard_EXPORT virtual void SetPCurve(const TopoDS_Shape&      aNewFace,
                                         TopoDS_Shape&            aNewEdge,
                                         const TopoDS_Shape&      aGenF,
                                         const TopoDS_Shape&      aGenE,
                                         const Sweep_NumShape&    aDirV,
                                         const TopAbs_Orientation orien) = 0;

  Standard_EXPORT virtual void SetGeneratingPCurve(const TopoDS_Shape&      aNewFace,
                                                   TopoDS_Shape&            aNewEdge,
                                                   const TopoDS_Shape&      aGenE,
                                                   const Sweep_NumShape&    aDirE,
                                                   const Sweep_NumShape&    aDirV,
                                                   const TopAbs_Orientation orien) = 0;

  Standard_EXPORT virtual void SetDirectingPCurve(const TopoDS_Shape&      aNewFace,
                                                  TopoDS_Shape&            aNewEdge,
                                                  const TopoDS_Shape&      aGenE,
                                                  const TopoDS_Shape&      aGenV,
                                                  const Sweep_NumShape&    aDirE,
                                                  const TopAbs_Orientation orien) = 0;

  Standard_EXPORT virtual TopAbs_Orientation DirectSolid(const TopoDS_Shape&   aGenS,
                                                         const Sweep_NumShape& aDirS) = 0;

  Standard_EXPORT virtual bool GGDShapeIsToAdd(const TopoDS_Shape&   aNewShape,
                                               const TopoDS_Shape&   aNewSubShape,
                                               const TopoDS_Shape&   aGenS,
                                               const TopoDS_Shape&   aSubGenS,
                                               const Sweep_NumShape& aDirS) const = 0;

  Standard_EXPORT virtual bool GDDShapeIsToAdd(const TopoDS_Shape&   aNewShape,
                                               const TopoDS_Shape&   aNewSubShape,
                                               const TopoDS_Shape&   aGenS,
                                               const Sweep_NumShape& aDirS,
                                               const Sweep_NumShape& aSubDirS) const = 0;

  Standard_EXPORT virtual bool SeparatedWires(const TopoDS_Shape&   aNewShape,
                                              const TopoDS_Shape&   aNewSubShape,
                                              const TopoDS_Shape&   aGenS,
                                              const TopoDS_Shape&   aSubGenS,
                                              const Sweep_NumShape& aDirS) const = 0;

  Standard_EXPORT virtual TopoDS_Shape SplitShell(const TopoDS_Shape& aNewShape) const;

  Standard_EXPORT virtual void SetContinuity(const TopoDS_Shape&   aGenS,
                                             const Sweep_NumShape& aDirS) = 0;

  Standard_EXPORT virtual bool HasShape(const TopoDS_Shape&   aGenS,
                                        const Sweep_NumShape& aDirS) const = 0;

  Standard_EXPORT virtual bool IsInvariant(const TopoDS_Shape& aGenS) const = 0;

  Standard_EXPORT TopoDS_Shape Shape(const TopoDS_Shape& aGenS, const Sweep_NumShape& aDirS);

  Standard_EXPORT TopoDS_Shape Shape(const TopoDS_Shape& aGenS);

  Standard_EXPORT bool IsUsed(const TopoDS_Shape& aGenS) const;

  Standard_EXPORT bool GenIsUsed(const TopoDS_Shape& theS) const;

  Standard_EXPORT TopoDS_Shape Shape();

  Standard_EXPORT TopoDS_Shape FirstShape();

  Standard_EXPORT TopoDS_Shape LastShape();

  Standard_EXPORT TopoDS_Shape FirstShape(const TopoDS_Shape& aGenS);

  Standard_EXPORT TopoDS_Shape LastShape(const TopoDS_Shape& aGenS);

  Standard_EXPORT bool Closed() const;

protected:
  Standard_EXPORT BRepSweep_NumLinearRegularSweep(const BRepSweep_Builder& aBuilder,
                                                  const TopoDS_Shape&      aGenShape,
                                                  const Sweep_NumShape&    aDirWire);

  BRepSweep_Builder                myBuilder;
  TopoDS_Shape                     myGenShape;
  Sweep_NumShape                   myDirWire;
  BRepSweep_Tool                   myGenShapeTool;
  Sweep_NumShapeTool               myDirShapeTool;
  NCollection_Array2<TopoDS_Shape> myShapes;
  NCollection_Array2<bool>         myBuiltShapes;
  NCollection_Array2<bool>         myUsedShapes;
};
