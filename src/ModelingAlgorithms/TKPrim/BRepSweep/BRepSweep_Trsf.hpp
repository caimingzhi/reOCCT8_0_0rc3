#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <TopLoc_Location.hpp>
#include <BRepSweep_NumLinearRegularSweep.hpp>
#include <TopAbs_Orientation.hpp>
class BRep_Builder;
class TopoDS_Shape;
class Sweep_NumShape;

class BRepSweep_Trsf : public BRepSweep_NumLinearRegularSweep
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT void Init();

  Standard_EXPORT bool Process(const TopoDS_Shape& aGenS, const Sweep_NumShape& aDirV);

  Standard_EXPORT TopoDS_Shape MakeEmptyVertex(const TopoDS_Shape&   aGenV,
                                               const Sweep_NumShape& aDirV) override = 0;

  Standard_EXPORT TopoDS_Shape MakeEmptyDirectingEdge(const TopoDS_Shape&   aGenV,
                                                      const Sweep_NumShape& aDirE) override = 0;

  Standard_EXPORT TopoDS_Shape MakeEmptyGeneratingEdge(const TopoDS_Shape&   aGenE,
                                                       const Sweep_NumShape& aDirV) override = 0;

  Standard_EXPORT void SetParameters(const TopoDS_Shape&   aNewFace,
                                     TopoDS_Shape&         aNewVertex,
                                     const TopoDS_Shape&   aGenF,
                                     const TopoDS_Shape&   aGenV,
                                     const Sweep_NumShape& aDirV) override = 0;

  Standard_EXPORT void SetDirectingParameter(const TopoDS_Shape&   aNewEdge,
                                             TopoDS_Shape&         aNewVertex,
                                             const TopoDS_Shape&   aGenV,
                                             const Sweep_NumShape& aDirE,
                                             const Sweep_NumShape& aDirV) override = 0;

  Standard_EXPORT void SetGeneratingParameter(const TopoDS_Shape&   aNewEdge,
                                              TopoDS_Shape&         aNewVertex,
                                              const TopoDS_Shape&   aGenE,
                                              const TopoDS_Shape&   aGenV,
                                              const Sweep_NumShape& aDirV) override = 0;

  Standard_EXPORT TopoDS_Shape MakeEmptyFace(const TopoDS_Shape&   aGenS,
                                             const Sweep_NumShape& aDirS) override = 0;

  Standard_EXPORT void SetPCurve(const TopoDS_Shape&      aNewFace,
                                 TopoDS_Shape&            aNewEdge,
                                 const TopoDS_Shape&      aGenF,
                                 const TopoDS_Shape&      aGenE,
                                 const Sweep_NumShape&    aDirV,
                                 const TopAbs_Orientation orien) override = 0;

  Standard_EXPORT void SetGeneratingPCurve(const TopoDS_Shape&      aNewFace,
                                           TopoDS_Shape&            aNewEdge,
                                           const TopoDS_Shape&      aGenE,
                                           const Sweep_NumShape&    aDirE,
                                           const Sweep_NumShape&    aDirV,
                                           const TopAbs_Orientation orien) override = 0;

  Standard_EXPORT void SetDirectingPCurve(const TopoDS_Shape&      aNewFace,
                                          TopoDS_Shape&            aNewEdge,
                                          const TopoDS_Shape&      aGenE,
                                          const TopoDS_Shape&      aGenV,
                                          const Sweep_NumShape&    aDirE,
                                          const TopAbs_Orientation orien) override = 0;

  Standard_EXPORT bool GGDShapeIsToAdd(const TopoDS_Shape&   aNewShape,
                                       const TopoDS_Shape&   aNewSubShape,
                                       const TopoDS_Shape&   aGenS,
                                       const TopoDS_Shape&   aSubGenS,
                                       const Sweep_NumShape& aDirS) const override = 0;

  Standard_EXPORT bool GDDShapeIsToAdd(const TopoDS_Shape&   aNewShape,
                                       const TopoDS_Shape&   aNewSubShape,
                                       const TopoDS_Shape&   aGenS,
                                       const Sweep_NumShape& aDirS,
                                       const Sweep_NumShape& aSubDirS) const override = 0;

  Standard_EXPORT bool SeparatedWires(const TopoDS_Shape&   aNewShape,
                                      const TopoDS_Shape&   aNewSubShape,
                                      const TopoDS_Shape&   aGenS,
                                      const TopoDS_Shape&   aSubGenS,
                                      const Sweep_NumShape& aDirS) const override = 0;

  Standard_EXPORT bool HasShape(const TopoDS_Shape&   aGenS,
                                const Sweep_NumShape& aDirS) const override = 0;

  Standard_EXPORT bool IsInvariant(const TopoDS_Shape& aGenS) const override = 0;

  Standard_EXPORT void SetContinuity(const TopoDS_Shape&   aGenS,
                                     const Sweep_NumShape& aDirS) override;

protected:
  Standard_EXPORT BRepSweep_Trsf(const BRep_Builder&    aBuilder,
                                 const TopoDS_Shape&    aGenShape,
                                 const Sweep_NumShape&  aDirWire,
                                 const TopLoc_Location& aLocation,
                                 const bool             aCopy);

  TopLoc_Location myLocation;
  bool            myCopy;
};
