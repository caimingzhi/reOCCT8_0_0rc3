#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Vec.hpp>
#include <Standard_Boolean.hpp>
#include <BRepSweep_Trsf.hpp>
#include <TopAbs_Orientation.hpp>
class TopoDS_Shape;
class Sweep_NumShape;
class TopLoc_Location;

class BRepSweep_Translation : public BRepSweep_Trsf
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepSweep_Translation(const TopoDS_Shape&    S,
                                        const Sweep_NumShape&  N,
                                        const TopLoc_Location& L,
                                        const gp_Vec&          V,
                                        const bool             C,
                                        const bool             Canonize = true);

  Standard_EXPORT TopoDS_Shape MakeEmptyVertex(const TopoDS_Shape&   aGenV,
                                               const Sweep_NumShape& aDirV) override;

  Standard_EXPORT TopoDS_Shape MakeEmptyDirectingEdge(const TopoDS_Shape&   aGenV,
                                                      const Sweep_NumShape& aDirE) override;

  Standard_EXPORT TopoDS_Shape MakeEmptyGeneratingEdge(const TopoDS_Shape&   aGenE,
                                                       const Sweep_NumShape& aDirV) override;

  Standard_EXPORT void SetParameters(const TopoDS_Shape&   aNewFace,
                                     TopoDS_Shape&         aNewVertex,
                                     const TopoDS_Shape&   aGenF,
                                     const TopoDS_Shape&   aGenV,
                                     const Sweep_NumShape& aDirV) override;

  Standard_EXPORT void SetDirectingParameter(const TopoDS_Shape&   aNewEdge,
                                             TopoDS_Shape&         aNewVertex,
                                             const TopoDS_Shape&   aGenV,
                                             const Sweep_NumShape& aDirE,
                                             const Sweep_NumShape& aDirV) override;

  Standard_EXPORT void SetGeneratingParameter(const TopoDS_Shape&   aNewEdge,
                                              TopoDS_Shape&         aNewVertex,
                                              const TopoDS_Shape&   aGenE,
                                              const TopoDS_Shape&   aGenV,
                                              const Sweep_NumShape& aDirV) override;

  Standard_EXPORT TopoDS_Shape MakeEmptyFace(const TopoDS_Shape&   aGenS,
                                             const Sweep_NumShape& aDirS) override;

  Standard_EXPORT void SetPCurve(const TopoDS_Shape&      aNewFace,
                                 TopoDS_Shape&            aNewEdge,
                                 const TopoDS_Shape&      aGenF,
                                 const TopoDS_Shape&      aGenE,
                                 const Sweep_NumShape&    aDirV,
                                 const TopAbs_Orientation orien) override;

  Standard_EXPORT void SetGeneratingPCurve(const TopoDS_Shape&      aNewFace,
                                           TopoDS_Shape&            aNewEdge,
                                           const TopoDS_Shape&      aGenE,
                                           const Sweep_NumShape&    aDirE,
                                           const Sweep_NumShape&    aDirV,
                                           const TopAbs_Orientation orien) override;

  Standard_EXPORT void SetDirectingPCurve(const TopoDS_Shape&      aNewFace,
                                          TopoDS_Shape&            aNewEdge,
                                          const TopoDS_Shape&      aGenE,
                                          const TopoDS_Shape&      aGenV,
                                          const Sweep_NumShape&    aDirE,
                                          const TopAbs_Orientation orien) override;

  Standard_EXPORT TopAbs_Orientation DirectSolid(const TopoDS_Shape&   aGenS,
                                                 const Sweep_NumShape& aDirS) override;

  Standard_EXPORT bool GGDShapeIsToAdd(const TopoDS_Shape&   aNewShape,
                                       const TopoDS_Shape&   aNewSubShape,
                                       const TopoDS_Shape&   aGenS,
                                       const TopoDS_Shape&   aSubGenS,
                                       const Sweep_NumShape& aDirS) const override;

  Standard_EXPORT bool GDDShapeIsToAdd(const TopoDS_Shape&   aNewShape,
                                       const TopoDS_Shape&   aNewSubShape,
                                       const TopoDS_Shape&   aGenS,
                                       const Sweep_NumShape& aDirS,
                                       const Sweep_NumShape& aSubDirS) const override;

  Standard_EXPORT bool SeparatedWires(const TopoDS_Shape&   aNewShape,
                                      const TopoDS_Shape&   aNewSubShape,
                                      const TopoDS_Shape&   aGenS,
                                      const TopoDS_Shape&   aSubGenS,
                                      const Sweep_NumShape& aDirS) const override;

  Standard_EXPORT bool HasShape(const TopoDS_Shape&   aGenS,
                                const Sweep_NumShape& aDirS) const override;

  Standard_EXPORT bool IsInvariant(const TopoDS_Shape& aGenS) const override;

  Standard_EXPORT gp_Vec Vec() const;

private:
  gp_Vec myVec;
  bool   myCanonize;
};
