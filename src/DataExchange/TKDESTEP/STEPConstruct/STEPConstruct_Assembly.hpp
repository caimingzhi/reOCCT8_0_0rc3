#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class StepShape_ShapeDefinitionRepresentation;
class StepShape_ShapeRepresentation;
class StepGeom_Axis2Placement3d;
class StepGeom_CartesianTransformationOperator3d;
class StepRepr_NextAssemblyUsageOccurrence;
class StepShape_ContextDependentShapeRepresentation;
class Interface_Graph;

class STEPConstruct_Assembly
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT STEPConstruct_Assembly();

  Standard_EXPORT void Init(const occ::handle<StepShape_ShapeDefinitionRepresentation>& aSR,
                            const occ::handle<StepShape_ShapeDefinitionRepresentation>& SDR0,
                            const occ::handle<StepGeom_Axis2Placement3d>&               Ax0,
                            const occ::handle<StepGeom_Axis2Placement3d>&               Loc);

  Standard_EXPORT void Init(
    const occ::handle<StepShape_ShapeDefinitionRepresentation>&    theSR,
    const occ::handle<StepShape_ShapeDefinitionRepresentation>&    theSDR0,
    const occ::handle<StepGeom_CartesianTransformationOperator3d>& theTrsfOp);

  Standard_EXPORT void MakeRelationship();

  Standard_EXPORT occ::handle<Standard_Transient> ItemValue() const;

  Standard_EXPORT occ::handle<StepGeom_Axis2Placement3d> ItemLocation() const;

  Standard_EXPORT occ::handle<StepRepr_NextAssemblyUsageOccurrence> GetNAUO() const;

  Standard_EXPORT static bool CheckSRRReversesNAUO(
    const Interface_Graph&                                            theGraph,
    const occ::handle<StepShape_ContextDependentShapeRepresentation>& CDSR);

private:
  occ::handle<StepShape_ShapeDefinitionRepresentation>    thesdr;
  occ::handle<StepShape_ShapeDefinitionRepresentation>    thesdr0;
  occ::handle<StepShape_ShapeRepresentation>              thesr;
  occ::handle<StepShape_ShapeRepresentation>              thesr0;
  occ::handle<Standard_Transient>                         theval;
  occ::handle<StepGeom_Axis2Placement3d>                  theloc;
  occ::handle<StepGeom_Axis2Placement3d>                  theax0;
  occ::handle<StepGeom_CartesianTransformationOperator3d> myTrsfOp;
  bool                                                    myIsCartesianTrsf;
};
