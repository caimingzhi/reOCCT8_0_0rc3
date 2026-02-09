#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <STEPConstruct_Tool.hpp>
#include <StepElement_ElementMaterial.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <StepFEA_ElementGeometricRelationship.hpp>
#include <StepFEA_ElementRepresentation.hpp>
#include <Standard_Type.hpp>
#include <StepElement_CurveElementSectionDefinition.hpp>
class XSControl_WorkSession;
class StepBasic_ProductDefinitionFormation;
class StepFEA_FeaModel;
class StepBasic_Product;
class StepFEA_FeaAxis2Placement3d;
class StepShape_ShapeRepresentation;
class StepFEA_Curve3dElementRepresentation;
class StepFEA_ElementRepresentation;
class StepBasic_ProductDefinition;
class StepData_StepModel;
class StepRepr_ProductDefinitionShape;

class StepAP209_Construct : public STEPConstruct_Tool
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepAP209_Construct();

  Standard_EXPORT StepAP209_Construct(const occ::handle<XSControl_WorkSession>& WS);

  Standard_EXPORT bool Init(const occ::handle<XSControl_WorkSession>& WS);

  Standard_EXPORT bool IsDesing(const occ::handle<StepBasic_ProductDefinitionFormation>& PD) const;

  Standard_EXPORT bool IsAnalys(const occ::handle<StepBasic_ProductDefinitionFormation>& PD) const;

  Standard_EXPORT occ::handle<StepFEA_FeaModel> FeaModel(
    const occ::handle<StepBasic_Product>& Prod) const;

  Standard_EXPORT occ::handle<StepFEA_FeaModel> FeaModel(
    const occ::handle<StepBasic_ProductDefinitionFormation>& PDF) const;

  Standard_EXPORT occ::handle<StepFEA_FeaAxis2Placement3d> GetFeaAxis2Placement3d(
    const occ::handle<StepFEA_FeaModel>& theFeaModel) const;

  Standard_EXPORT occ::handle<StepShape_ShapeRepresentation> IdealShape(
    const occ::handle<StepBasic_Product>& Prod) const;

  Standard_EXPORT occ::handle<StepShape_ShapeRepresentation> IdealShape(
    const occ::handle<StepBasic_ProductDefinitionFormation>& PDF) const;

  Standard_EXPORT occ::handle<StepShape_ShapeRepresentation> NominShape(
    const occ::handle<StepBasic_Product>& Prod) const;

  Standard_EXPORT occ::handle<StepShape_ShapeRepresentation> NominShape(
    const occ::handle<StepBasic_ProductDefinitionFormation>& PDF) const;

  Standard_EXPORT occ::handle<NCollection_HSequence<occ::handle<StepElement_ElementMaterial>>>
                  GetElementMaterial() const;

  Standard_EXPORT occ::handle<
    NCollection_HSequence<occ::handle<StepFEA_ElementGeometricRelationship>>>
    GetElemGeomRelat() const;

  Standard_EXPORT occ::handle<NCollection_HSequence<occ::handle<StepFEA_ElementRepresentation>>>
                  GetElements1D(const occ::handle<StepFEA_FeaModel>& theFeaModel) const;

  Standard_EXPORT occ::handle<NCollection_HSequence<occ::handle<StepFEA_ElementRepresentation>>>
                  GetElements2D(const occ::handle<StepFEA_FeaModel>& theFEAModel) const;

  Standard_EXPORT occ::handle<NCollection_HSequence<occ::handle<StepFEA_ElementRepresentation>>>
                  GetElements3D(const occ::handle<StepFEA_FeaModel>& theFEAModel) const;

  Standard_EXPORT occ::handle<
    NCollection_HSequence<occ::handle<StepElement_CurveElementSectionDefinition>>>
    GetCurElemSection(const occ::handle<StepFEA_Curve3dElementRepresentation>& ElemRepr) const;

  Standard_EXPORT occ::handle<StepShape_ShapeRepresentation> GetShReprForElem(
    const occ::handle<StepFEA_ElementRepresentation>& ElemRepr) const;

  Standard_EXPORT bool CreateAnalysStructure(const occ::handle<StepBasic_Product>& Prod) const;

  Standard_EXPORT bool CreateFeaStructure(const occ::handle<StepBasic_Product>& Prod) const;

  Standard_EXPORT bool ReplaceCcDesingToApplied() const;

  Standard_EXPORT bool CreateAddingEntities(
    const occ::handle<StepBasic_ProductDefinition>& AnaPD) const;

  Standard_EXPORT occ::handle<StepData_StepModel> CreateAP203Structure() const;

  Standard_EXPORT bool CreateAdding203Entities(const occ::handle<StepBasic_ProductDefinition>& PD,
                                               occ::handle<StepData_StepModel>& aModel) const;

  Standard_EXPORT occ::handle<StepFEA_FeaModel> FeaModel(
    const occ::handle<StepRepr_ProductDefinitionShape>& PDS) const;

  Standard_EXPORT occ::handle<StepFEA_FeaModel> FeaModel(
    const occ::handle<StepBasic_ProductDefinition>& PD) const;

  Standard_EXPORT occ::handle<StepShape_ShapeRepresentation> IdealShape(
    const occ::handle<StepBasic_ProductDefinition>& PD) const;

  Standard_EXPORT occ::handle<StepShape_ShapeRepresentation> IdealShape(
    const occ::handle<StepRepr_ProductDefinitionShape>& PDS) const;

protected:
  Standard_EXPORT occ::handle<NCollection_HSequence<occ::handle<StepFEA_ElementRepresentation>>>
                  GetFeaElements(const occ::handle<StepFEA_FeaModel>& theFeaModel,
                                 const occ::handle<Standard_Type>&    theType) const;
};
