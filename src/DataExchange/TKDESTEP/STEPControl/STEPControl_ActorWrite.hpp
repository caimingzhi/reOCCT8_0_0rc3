#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <STEPConstruct_ContextTool.hpp>
#include <Transfer_ActorOfFinderProcess.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <STEPControl_StepModelType.hpp>
class Transfer_Finder;
class Transfer_Binder;
class Transfer_FinderProcess;
class StepShape_ShapeDefinitionRepresentation;
class StepGeom_GeometricRepresentationItem;
class TopoDS_Shape;
class StepShape_NonManifoldSurfaceShapeRepresentation;

class STEPControl_ActorWrite : public Transfer_ActorOfFinderProcess
{

public:
  Standard_EXPORT STEPControl_ActorWrite();

  Standard_EXPORT bool Recognize(const occ::handle<Transfer_Finder>& start) override;

  Standard_EXPORT occ::handle<Transfer_Binder> Transfer(
    const occ::handle<Transfer_Finder>&        start,
    const occ::handle<Transfer_FinderProcess>& FP,
    const Message_ProgressRange&               theProgress = Message_ProgressRange()) override;

  Standard_EXPORT occ::handle<Transfer_Binder> TransferSubShape(
    const occ::handle<Transfer_Finder>&                         start,
    const occ::handle<StepShape_ShapeDefinitionRepresentation>& SDR,
    occ::handle<StepGeom_GeometricRepresentationItem>&          AX1,
    const occ::handle<Transfer_FinderProcess>&                  FP,
    const StepData_Factors&                                 theLocalFactors = StepData_Factors(),
    const occ::handle<NCollection_HSequence<TopoDS_Shape>>& shapeGroup      = nullptr,
    const bool                                              isManifold      = true,
    const Message_ProgressRange&                            theProgress = Message_ProgressRange());

  Standard_EXPORT occ::handle<Transfer_Binder> TransferShape(
    const occ::handle<Transfer_Finder>&                         start,
    const occ::handle<StepShape_ShapeDefinitionRepresentation>& SDR,
    const occ::handle<Transfer_FinderProcess>&                  FP,
    const StepData_Factors&                                 theLocalFactors = StepData_Factors(),
    const occ::handle<NCollection_HSequence<TopoDS_Shape>>& shapeGroup      = nullptr,
    const bool                                              isManifold      = true,
    const Message_ProgressRange&                            theProgress = Message_ProgressRange());

  Standard_EXPORT occ::handle<Transfer_Binder> TransferCompound(
    const occ::handle<Transfer_Finder>&                         start,
    const occ::handle<StepShape_ShapeDefinitionRepresentation>& SDR,
    const occ::handle<Transfer_FinderProcess>&                  FP,
    const StepData_Factors&      theLocalFactors = StepData_Factors(),
    const Message_ProgressRange& theProgress     = Message_ProgressRange());

  Standard_EXPORT void SetMode(const STEPControl_StepModelType M);

  Standard_EXPORT STEPControl_StepModelType Mode() const;

  Standard_EXPORT void SetGroupMode(const int mode);

  Standard_EXPORT int GroupMode() const;

  Standard_EXPORT void SetTolerance(const double Tol);

  Standard_EXPORT virtual bool IsAssembly(const occ::handle<StepData_StepModel>& theModel,
                                          TopoDS_Shape&                          S) const;

  DEFINE_STANDARD_RTTIEXT(STEPControl_ActorWrite, Transfer_ActorOfFinderProcess)

private:
  Standard_EXPORT occ::handle<StepShape_NonManifoldSurfaceShapeRepresentation> getNMSSRForGroup(
    const occ::handle<NCollection_HSequence<TopoDS_Shape>>& shapeGroup,
    const occ::handle<Transfer_FinderProcess>&              FP,
    bool&                                                   isNMSSRCreated) const;

  Standard_EXPORT void mergeInfoForNM(const occ::handle<Transfer_FinderProcess>& theFP,
                                      const occ::handle<Standard_Transient>&     theInfo) const;

  bool separateShapeToSoloVertex(const TopoDS_Shape&                 theShape,
                                 NCollection_Sequence<TopoDS_Shape>& theVertices);

private:
  int                       mygroup;
  double                    mytoler;
  STEPConstruct_ContextTool myContext;
};
