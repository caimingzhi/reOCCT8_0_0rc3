#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Transient.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <TopoDSToStep_BuilderError.hpp>
#include <TopoDSToStep_Root.hpp>
#include <TopoDS_Shape.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
class TopoDS_Shape;
class TopoDSToStep_Tool;
class Transfer_FinderProcess;
class TopoDS_Edge;
class TopoDS_Face;

//! This builder Class provides services to build
//! a ProSTEP Wireframemodel from a Cas.Cad BRep.
class TopoDSToStep_WireframeBuilder : public TopoDSToStep_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopoDSToStep_WireframeBuilder();

  Standard_EXPORT TopoDSToStep_WireframeBuilder(
    const TopoDS_Shape&     S,
    TopoDSToStep_Tool&      T,
    const StepData_Factors& theLocalFactors = StepData_Factors());

  Standard_EXPORT void Init(const TopoDS_Shape&     S,
                            TopoDSToStep_Tool&      T,
                            const StepData_Factors& theLocalFactors = StepData_Factors());

  Standard_EXPORT TopoDSToStep_BuilderError Error() const;

  Standard_EXPORT const occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>>& Value()
    const;

  //! Extraction of Trimmed Curves from TopoDS_Edge for the
  //! Creation of a GeometricallyBoundedWireframeRepresentation
  Standard_EXPORT bool GetTrimmedCurveFromEdge(
    const TopoDS_Edge&                                                                           E,
    const TopoDS_Face&                                                                           F,
    NCollection_DataMap<TopoDS_Shape, occ::handle<Standard_Transient>, TopTools_ShapeMapHasher>& M,
    occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>>&                         L,
    const StepData_Factors& theLocalFactors = StepData_Factors()) const;

  //! Extraction of Trimmed Curves from TopoDS_Face for the
  //! Creation of a GeometricallyBoundedWireframeRepresentation
  Standard_EXPORT bool GetTrimmedCurveFromFace(
    const TopoDS_Face&                                                                           F,
    NCollection_DataMap<TopoDS_Shape, occ::handle<Standard_Transient>, TopTools_ShapeMapHasher>& M,
    occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>>&                         L,
    const StepData_Factors& theLocalFactors = StepData_Factors()) const;

  //! Extraction of Trimmed Curves from any TopoDS_Shape for the
  //! Creation of a GeometricallyBoundedWireframeRepresentation
  Standard_EXPORT bool GetTrimmedCurveFromShape(
    const TopoDS_Shape&                                                                          S,
    NCollection_DataMap<TopoDS_Shape, occ::handle<Standard_Transient>, TopTools_ShapeMapHasher>& M,
    occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>>&                         L,
    const StepData_Factors& theLocalFactors = StepData_Factors()) const;

private:
  occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>> myResult;
  TopoDSToStep_BuilderError                                           myError;
};
