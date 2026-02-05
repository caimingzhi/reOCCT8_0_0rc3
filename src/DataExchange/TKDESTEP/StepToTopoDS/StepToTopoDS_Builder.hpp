#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepToTopoDS_BuilderError.hpp>
#include <TopoDS_Shape.hpp>
#include <StepToTopoDS_Root.hpp>
#include <Message_ProgressRange.hpp>

class StepShape_ManifoldSolidBrep;
class Transfer_TransientProcess;
class StepShape_BrepWithVoids;
class StepShape_FacetedBrep;
class StepShape_FacetedBrepAndBrepWithVoids;
class StepShape_ShellBasedSurfaceModel;
class StepToTopoDS_NMTool;
class StepShape_GeometricSet;
class StepShape_EdgeBasedWireframeModel;
class StepShape_FaceBasedSurfaceModel;
class StepVisual_TessellatedFace;
class StepVisual_TessellatedShell;
class StepVisual_TessellatedSolid;
class StepVisual_TessellatedSurfaceSet;
class Transfer_ActorOfTransientProcess;

class StepToTopoDS_Builder : public StepToTopoDS_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepToTopoDS_Builder();

  Standard_EXPORT void Init(const occ::handle<StepShape_ManifoldSolidBrep>& theManifoldSolid,
                            const occ::handle<Transfer_TransientProcess>&   theTP,
                            const StepData_Factors&      theLocalFactors = StepData_Factors(),
                            const Message_ProgressRange& theProgress     = Message_ProgressRange());

  Standard_EXPORT void Init(const occ::handle<StepShape_BrepWithVoids>&   theBRepWithVoids,
                            const occ::handle<Transfer_TransientProcess>& theTP,
                            const StepData_Factors&      theLocalFactors = StepData_Factors(),
                            const Message_ProgressRange& theProgress     = Message_ProgressRange());

  Standard_EXPORT void Init(const occ::handle<StepShape_FacetedBrep>&     theFB,
                            const occ::handle<Transfer_TransientProcess>& theTP,
                            const StepData_Factors&      theLocalFactors = StepData_Factors(),
                            const Message_ProgressRange& theProgress     = Message_ProgressRange());

  Standard_EXPORT void Init(const occ::handle<StepShape_FacetedBrepAndBrepWithVoids>& theFBABWV,
                            const occ::handle<Transfer_TransientProcess>&             theTP,
                            const StepData_Factors&      theLocalFactors = StepData_Factors(),
                            const Message_ProgressRange& theProgress     = Message_ProgressRange());

  Standard_EXPORT void Init(const occ::handle<StepShape_ShellBasedSurfaceModel>& S,
                            const occ::handle<Transfer_TransientProcess>&        TP,
                            StepToTopoDS_NMTool&                                 NMTool,
                            const StepData_Factors&      theLocalFactors = StepData_Factors(),
                            const Message_ProgressRange& theProgress     = Message_ProgressRange());

  Standard_EXPORT void Init(const occ::handle<StepShape_EdgeBasedWireframeModel>& S,
                            const occ::handle<Transfer_TransientProcess>&         TP,
                            const StepData_Factors& theLocalFactors = StepData_Factors());

  Standard_EXPORT void Init(const occ::handle<StepShape_FaceBasedSurfaceModel>& S,
                            const occ::handle<Transfer_TransientProcess>&       TP,
                            const StepData_Factors& theLocalFactors = StepData_Factors());

  Standard_EXPORT void Init(const occ::handle<StepShape_GeometricSet>&    S,
                            const occ::handle<Transfer_TransientProcess>& TP,
                            const StepData_Factors& theLocalFactors = StepData_Factors(),
                            const occ::handle<Transfer_ActorOfTransientProcess>& RA = nullptr,
                            const bool                                           isManifold = false,
                            const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT void Init(const occ::handle<StepVisual_TessellatedSolid>& theTSo,
                            const occ::handle<Transfer_TransientProcess>&   theTP,
                            const bool                   theReadTessellatedWhenNoBRepOnly,
                            bool&                        theHasGeom,
                            const StepData_Factors&      theLocalFactors = StepData_Factors(),
                            const Message_ProgressRange& theProgress     = Message_ProgressRange());

  Standard_EXPORT void Init(const occ::handle<StepVisual_TessellatedShell>& theTSh,
                            const occ::handle<Transfer_TransientProcess>&   theTP,
                            const bool                   theReadTessellatedWhenNoBRepOnly,
                            bool&                        theHasGeom,
                            const StepData_Factors&      theLocalFactors = StepData_Factors(),
                            const Message_ProgressRange& theProgress     = Message_ProgressRange());

  Standard_EXPORT void Init(const occ::handle<StepVisual_TessellatedFace>& theTF,
                            const occ::handle<Transfer_TransientProcess>&  theTP,
                            const bool              theReadTessellatedWhenNoBRepOnly,
                            bool&                   theHasGeom,
                            const StepData_Factors& theLocalFactors = StepData_Factors());

  Standard_EXPORT void Init(const occ::handle<StepVisual_TessellatedSurfaceSet>& theTSS,
                            const occ::handle<Transfer_TransientProcess>&        theTP,
                            bool&                                                theHasGeom,
                            const StepData_Factors& theLocalFactors = StepData_Factors());

  Standard_EXPORT const TopoDS_Shape& Value() const;

  Standard_EXPORT StepToTopoDS_BuilderError Error() const;

private:
  StepToTopoDS_BuilderError myError;
  TopoDS_Shape              myResult;
};
