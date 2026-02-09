#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepData_Factors.hpp>
#include <StepToTopoDS_NMTool.hpp>
#include <Transfer_ActorOfTransientProcess.hpp>
#include <Standard_Integer.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <Message_ProgressRange.hpp>
#include <Interface_InterfaceModel.hpp>

class StepRepr_Representation;
class Standard_Transient;
class Transfer_Binder;
class Transfer_TransientProcess;
class StepGeom_Axis2Placement3d;
class gp_Trsf;
class StepRepr_RepresentationRelationship;
class TransferBRep_ShapeBinder;
class StepBasic_ProductDefinition;
class StepRepr_NextAssemblyUsageOccurrence;
class StepShape_ShapeRepresentation;
class StepShape_ContextDependentShapeRepresentation;
class StepRepr_ShapeRepresentationRelationship;
class StepGeom_GeometricRepresentationItem;
class StepRepr_MappedItem;
class StepShape_FaceSurface;
class TopoDS_Shell;
class TopoDS_Compound;
class StepRepr_ConstructiveGeometryRepresentationRelationship;
class StepRepr_MechanicalDesignAndDraughtingRelationship;
class StepData_StepModel;

class STEPControl_ActorRead : public Transfer_ActorOfTransientProcess
{

public:
  Standard_EXPORT STEPControl_ActorRead(const occ::handle<Interface_InterfaceModel>& theModel);

  Standard_EXPORT bool Recognize(const occ::handle<Standard_Transient>& start) override;

  Standard_EXPORT occ::handle<Transfer_Binder> Transfer(
    const occ::handle<Standard_Transient>&        start,
    const occ::handle<Transfer_TransientProcess>& TP,
    const Message_ProgressRange&                  theProgress = Message_ProgressRange()) override;

  Standard_EXPORT occ::handle<Transfer_Binder> TransferShape(
    const occ::handle<Standard_Transient>&        start,
    const occ::handle<Transfer_TransientProcess>& TP,
    const StepData_Factors&                       theLocalFactors = StepData_Factors(),
    const bool                                    isManifold      = true,
    const bool                                    theUseTrsf      = false,
    const Message_ProgressRange&                  theProgress     = Message_ProgressRange());

  Standard_EXPORT void PrepareUnits(const occ::handle<StepRepr_Representation>&   rep,
                                    const occ::handle<Transfer_TransientProcess>& TP,
                                    StepData_Factors&                             theLocalFactors);

  Standard_EXPORT void ResetUnits(occ::handle<StepData_StepModel>& theModel,
                                  StepData_Factors&                theLocalFactors);

  Standard_EXPORT void SetModel(const occ::handle<Interface_InterfaceModel>& theModel);

  Standard_EXPORT bool ComputeTransformation(
    const occ::handle<StepGeom_Axis2Placement3d>& Origin,
    const occ::handle<StepGeom_Axis2Placement3d>& Target,
    const occ::handle<StepRepr_Representation>&   OrigContext,
    const occ::handle<StepRepr_Representation>&   TargContext,
    const occ::handle<Transfer_TransientProcess>& TP,
    gp_Trsf&                                      Trsf,
    const StepData_Factors&                       theLocalFactors = StepData_Factors());

  Standard_EXPORT bool ComputeSRRWT(const occ::handle<StepRepr_RepresentationRelationship>& SRR,
                                    const occ::handle<Transfer_TransientProcess>&           TP,
                                    gp_Trsf&                                                Trsf,
                                    const StepData_Factors& theLocalFactors = StepData_Factors());

  DEFINE_STANDARD_RTTIEXT(STEPControl_ActorRead, Transfer_ActorOfTransientProcess)

protected:
  Standard_EXPORT occ::handle<TransferBRep_ShapeBinder> TransferEntity(
    const occ::handle<StepBasic_ProductDefinition>& PD,
    const occ::handle<Transfer_TransientProcess>&   TP,
    const StepData_Factors&                         theLocalFactors = StepData_Factors(),
    const bool                                      theUseTrsf      = false,
    const Message_ProgressRange&                    theProgress     = Message_ProgressRange());

  Standard_EXPORT occ::handle<TransferBRep_ShapeBinder> TransferEntity(
    const occ::handle<StepRepr_NextAssemblyUsageOccurrence>& NAUO,
    const occ::handle<Transfer_TransientProcess>&            TP,
    const StepData_Factors&                                  theLocalFactors = StepData_Factors(),
    const Message_ProgressRange&                             theProgress = Message_ProgressRange());

  Standard_EXPORT occ::handle<TransferBRep_ShapeBinder> TransferEntity(
    const occ::handle<StepShape_ShapeRepresentation>& sr,
    const occ::handle<Transfer_TransientProcess>&     TP,
    const StepData_Factors&                           theLocalFactors,
    bool&                                             isBound,
    const bool                                        theUseTrsf  = false,
    const Message_ProgressRange&                      theProgress = Message_ProgressRange());

  Standard_EXPORT occ::handle<TransferBRep_ShapeBinder> TransferEntity(
    const occ::handle<StepShape_ContextDependentShapeRepresentation>& CDSR,
    const occ::handle<Transfer_TransientProcess>&                     TP,
    const StepData_Factors&      theLocalFactors = StepData_Factors(),
    const Message_ProgressRange& theProgress     = Message_ProgressRange());

  Standard_EXPORT occ::handle<TransferBRep_ShapeBinder> TransferEntity(
    const occ::handle<StepRepr_ShapeRepresentationRelationship>& und,
    const occ::handle<Transfer_TransientProcess>&                TP,
    const StepData_Factors&                                      theLocalFactors,
    const int                                                    nbrep      = 0,
    const bool                                                   theUseTrsf = false,
    const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT occ::handle<TransferBRep_ShapeBinder> TransferEntity(
    const occ::handle<StepGeom_GeometricRepresentationItem>& git,
    const occ::handle<Transfer_TransientProcess>&            TP,
    const StepData_Factors&                                  theLocalFactors,
    const bool                                               isManifold,
    const Message_ProgressRange&                             theProgress);

  Standard_EXPORT occ::handle<TransferBRep_ShapeBinder> TransferEntity(
    const occ::handle<StepRepr_MappedItem>&       mapit,
    const occ::handle<Transfer_TransientProcess>& TP,
    const StepData_Factors&                       theLocalFactors,
    const Message_ProgressRange&                  theProgress);

  Standard_EXPORT occ::handle<TransferBRep_ShapeBinder> TransferEntity(
    const occ::handle<StepShape_FaceSurface>&     fs,
    const occ::handle<Transfer_TransientProcess>& TP,
    const StepData_Factors&                       theLocalFactors,
    const Message_ProgressRange&                  theProgress);

  occ::handle<TransferBRep_ShapeBinder> TransferEntity(
    const occ::handle<StepRepr_ConstructiveGeometryRepresentationRelationship>& theCGRR,
    const occ::handle<Transfer_TransientProcess>&                               theTP,
    const StepData_Factors& theLocalFactors = StepData_Factors());

  occ::handle<TransferBRep_ShapeBinder> TransferEntity(
    const occ::handle<StepRepr_MechanicalDesignAndDraughtingRelationship>& theMDADR,
    const occ::handle<Transfer_TransientProcess>&                          theTP,
    const StepData_Factors&                                                theLocalFactors,
    const Message_ProgressRange&                                           theProgress);

  Standard_EXPORT occ::handle<TransferBRep_ShapeBinder> OldWay(
    const occ::handle<Standard_Transient>&        start,
    const occ::handle<Transfer_TransientProcess>& TP,
    const Message_ProgressRange&                  theProgress);

private:
  Standard_EXPORT TopoDS_Shell closeIDEASShell(const TopoDS_Shell&                   shell,
                                               const NCollection_List<TopoDS_Shape>& closingShells);

  Standard_EXPORT void computeIDEASClosings(
    const TopoDS_Compound&                               comp,
    NCollection_IndexedDataMap<TopoDS_Shape,
                               NCollection_List<TopoDS_Shape>,
                               TopTools_ShapeMapHasher>& shellClosingMap);

  Standard_EXPORT TopoDS_Shape
    TransferRelatedSRR(const occ::handle<Transfer_TransientProcess>&     theTP,
                       const occ::handle<StepShape_ShapeRepresentation>& theRep,
                       const bool                                        theUseTrsf,
                       const bool                                        theReadConstructiveGeomRR,
                       const StepData_Factors&                           theLocalFactors,
                       TopoDS_Compound&                                  theCund,
                       Message_ProgressScope&                            thePS);

private:
  StepToTopoDS_NMTool                   myNMTool;
  double                                myPrecision;
  double                                myMaxTol;
  occ::handle<StepRepr_Representation>  mySRContext;
  occ::handle<Interface_InterfaceModel> myModel;
};
