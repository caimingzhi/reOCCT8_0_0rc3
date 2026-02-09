

#include <HeaderSection_FileDescription.hpp>
#include <HeaderSection_FileName.hpp>
#include <HeaderSection_FileSchema.hpp>
#include <Interface_EntityIterator.hpp>
#include <TCollection_HAsciiString.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <OSD_Process.hpp>
#include <Quantity_Date.hpp>
#include <StepAP203_CcDesignApproval.hpp>
#include <StepAP203_CcDesignDateAndTimeAssignment.hpp>
#include <StepAP203_CcDesignPersonAndOrganizationAssignment.hpp>
#include <StepAP203_CcDesignSecurityClassification.hpp>
#include <StepAP203_ApprovedItem.hpp>
#include <StepAP203_ClassifiedItem.hpp>
#include <StepAP203_DateTimeItem.hpp>
#include <StepAP203_PersonOrganizationItem.hpp>
#include <StepAP209_Construct.hpp>
#include <StepAP214_AppliedApprovalAssignment.hpp>
#include <StepAP214_AppliedDateAndTimeAssignment.hpp>
#include <StepAP214_AppliedPersonAndOrganizationAssignment.hpp>
#include <StepAP214_AppliedSecurityClassificationAssignment.hpp>
#include <StepAP214_ApprovalItem.hpp>
#include <StepAP214_DateAndTimeItem.hpp>
#include <StepAP214_PersonAndOrganizationItem.hpp>
#include <StepAP214_SecurityClassificationItem.hpp>
#include <StepBasic_ApplicationContext.hpp>
#include <StepBasic_ApplicationProtocolDefinition.hpp>
#include <StepBasic_Approval.hpp>
#include <StepBasic_ApprovalDateTime.hpp>
#include <StepBasic_ApprovalPersonOrganization.hpp>
#include <StepBasic_ApprovalRole.hpp>
#include <StepBasic_ApprovalStatus.hpp>
#include <StepBasic_CalendarDate.hpp>
#include <StepBasic_CoordinatedUniversalTimeOffset.hpp>
#include <StepBasic_DateAndTime.hpp>
#include <StepBasic_DateTimeRole.hpp>
#include <StepBasic_DateTimeSelect.hpp>
#include <StepBasic_DesignContext.hpp>
#include <StepBasic_DimensionalExponents.hpp>
#include <StepBasic_LocalTime.hpp>
#include <StepBasic_MechanicalContext.hpp>
#include <StepBasic_Organization.hpp>
#include <StepBasic_Person.hpp>
#include <StepBasic_PersonAndOrganization.hpp>
#include <StepBasic_PersonAndOrganizationRole.hpp>
#include <StepBasic_PersonOrganizationSelect.hpp>
#include <StepBasic_ProductCategoryRelationship.hpp>
#include <StepBasic_ProductContext.hpp>
#include <StepBasic_ProductDefinition.hpp>
#include <StepBasic_ProductDefinitionContext.hpp>
#include <StepBasic_ProductDefinitionFormation.hpp>
#include <StepBasic_ProductDefinitionFormationRelationship.hpp>
#include <StepBasic_ProductRelatedProductCategory.hpp>
#include <StepBasic_SecurityClassification.hpp>
#include <StepBasic_SecurityClassificationLevel.hpp>
#include <StepBasic_SiUnitAndMassUnit.hpp>
#include <StepBasic_SiUnitAndThermodynamicTemperatureUnit.hpp>
#include <StepBasic_SiUnitAndTimeUnit.hpp>
#include <StepData_StepModel.hpp>
#include <StepElement_AnalysisItemWithinRepresentation.hpp>
#include <StepElement_ElementMaterial.hpp>
#include <StepFEA_Curve3dElementProperty.hpp>
#include <StepFEA_Curve3dElementRepresentation.hpp>
#include <StepFEA_CurveElementIntervalConstant.hpp>
#include <StepFEA_ElementGeometricRelationship.hpp>
#include <StepFEA_ElementRepresentation.hpp>
#include <StepFEA_FeaAxis2Placement3d.hpp>
#include <StepFEA_FeaModel3d.hpp>
#include <StepFEA_FeaModelDefinition.hpp>
#include <StepFEA_CurveElementInterval.hpp>
#include <StepFEA_Surface3dElementRepresentation.hpp>
#include <StepFEA_Volume3dElementRepresentation.hpp>
#include <StepGeom_CartesianPoint.hpp>
#include <StepGeom_Direction.hpp>
#include <StepGeom_GeometricRepresentationContextAndGlobalUnitAssignedContext.hpp>
#include <StepGeom_GeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx.hpp>
#include <StepRepr_GlobalUnitAssignedContext.hpp>
#include <StepRepr_RepresentationItem.hpp>
#include <StepRepr_ProductDefinitionShape.hpp>
#include <StepRepr_PropertyDefinitionRepresentation.hpp>
#include <StepRepr_ShapeRepresentationRelationship.hpp>
#include <StepRepr_StructuralResponseProperty.hpp>
#include <StepRepr_StructuralResponsePropertyDefinitionRepresentation.hpp>
#include <StepShape_ShapeDefinitionRepresentation.hpp>
#include <StepShape_ShapeRepresentation.hpp>
#include <TCollection_AsciiString.hpp>
#include <XSControl_WorkSession.hpp>

StepAP209_Construct::StepAP209_Construct() = default;

StepAP209_Construct::StepAP209_Construct(const occ::handle<XSControl_WorkSession>& WS)
    : STEPConstruct_Tool(WS)
{
}

bool StepAP209_Construct::Init(const occ::handle<XSControl_WorkSession>& WS)
{
  return SetWS(WS);
}

bool StepAP209_Construct::IsDesing(
  const occ::handle<StepBasic_ProductDefinitionFormation>& PDF) const
{
  Interface_EntityIterator subs = Graph().Sharings(PDF);
  for (subs.Start(); subs.More(); subs.Next())
  {
    occ::handle<StepBasic_ProductDefinitionFormationRelationship> PDFR =
      occ::down_cast<StepBasic_ProductDefinitionFormationRelationship>(subs.Value());
    if (PDFR.IsNull())
      continue;
    if (PDF == PDFR->RelatingProductDefinitionFormation())
      return true;
  }
  return false;
}

bool StepAP209_Construct::IsAnalys(
  const occ::handle<StepBasic_ProductDefinitionFormation>& PDF) const
{
  Interface_EntityIterator subs = Graph().Sharings(PDF);
  for (subs.Start(); subs.More(); subs.Next())
  {
    occ::handle<StepBasic_ProductDefinitionFormationRelationship> PDFR =
      occ::down_cast<StepBasic_ProductDefinitionFormationRelationship>(subs.Value());
    if (PDFR.IsNull())
      continue;
    if (PDF == PDFR->RelatedProductDefinitionFormation())
      return true;
  }
  return false;
}

occ::handle<NCollection_HSequence<occ::handle<StepElement_ElementMaterial>>> StepAP209_Construct::
  GetElementMaterial() const
{
  occ::handle<NCollection_HSequence<occ::handle<StepElement_ElementMaterial>>> aSequence =
    new NCollection_HSequence<occ::handle<StepElement_ElementMaterial>>;
  occ::handle<Interface_InterfaceModel> model = Model();
  int                                   nb    = model->NbEntities();
  for (int i = 1; i <= nb; i++)
  {
    occ::handle<Standard_Transient> anEntity = model->Value(i);
    if (anEntity->IsKind(STANDARD_TYPE(StepElement_ElementMaterial)))
    {
      occ::handle<StepElement_ElementMaterial> anElement =
        occ::down_cast<StepElement_ElementMaterial>(anEntity);
      aSequence->Append(anElement);
    }
  }
  return aSequence;
}

occ::handle<NCollection_HSequence<occ::handle<StepFEA_ElementGeometricRelationship>>>
  StepAP209_Construct::GetElemGeomRelat() const
{
  occ::handle<NCollection_HSequence<occ::handle<StepFEA_ElementGeometricRelationship>>> aSequence =
    new NCollection_HSequence<occ::handle<StepFEA_ElementGeometricRelationship>>;
  occ::handle<Interface_InterfaceModel> model = Model();
  int                                   nb    = model->NbEntities();
  for (int i = 1; i <= nb; i++)
  {
    occ::handle<Standard_Transient> anEntity = model->Value(i);
    if (anEntity->IsKind(STANDARD_TYPE(StepFEA_ElementGeometricRelationship)))
    {
      occ::handle<StepFEA_ElementGeometricRelationship> EGR =
        occ::down_cast<StepFEA_ElementGeometricRelationship>(anEntity);
      aSequence->Append(EGR);
    }
  }
  return aSequence;
}

occ::handle<StepShape_ShapeRepresentation> StepAP209_Construct::GetShReprForElem(
  const occ::handle<StepFEA_ElementRepresentation>& ElemRepr) const
{
  occ::handle<StepShape_ShapeRepresentation> SR;
  if (ElemRepr.IsNull())
    return SR;
  Interface_EntityIterator subs = Graph().Sharings(ElemRepr);
  for (subs.Start(); subs.More() && SR.IsNull(); subs.Next())
  {
    occ::handle<StepFEA_ElementGeometricRelationship> EGR =
      occ::down_cast<StepFEA_ElementGeometricRelationship>(subs.Value());
    if (EGR.IsNull())
      continue;
    occ::handle<StepElement_AnalysisItemWithinRepresentation> AIWR = EGR->Item();
    if (AIWR.IsNull())
      continue;
    occ::handle<StepRepr_Representation> Repr = AIWR->Rep();
    if (Repr.IsNull())
      continue;
    SR = occ::down_cast<StepShape_ShapeRepresentation>(Repr);
  }
  return SR;
}

occ::handle<StepFEA_FeaModel> StepAP209_Construct::FeaModel(
  const occ::handle<StepBasic_Product>& Prod) const
{
  occ::handle<StepFEA_FeaModel> FM;
  if (Prod.IsNull())
    return FM;
  Interface_EntityIterator subs = Graph().Sharings(Prod);
  for (subs.Start(); subs.More() && FM.IsNull(); subs.Next())
  {
    occ::handle<StepBasic_ProductDefinitionFormation> PDF =
      occ::down_cast<StepBasic_ProductDefinitionFormation>(subs.Value());
    if (PDF.IsNull())
      continue;
    FM = FeaModel(PDF);
  }
  return FM;
}

occ::handle<StepFEA_FeaModel> StepAP209_Construct::FeaModel(
  const occ::handle<StepBasic_ProductDefinition>& PD) const
{

  occ::handle<StepFEA_FeaModel> FM;
  if (PD.IsNull())
    return FM;
  Interface_EntityIterator subs = Graph().Shareds(PD);
  for (subs.Start(); subs.More() && FM.IsNull(); subs.Next())
  {
    occ::handle<StepBasic_ProductDefinitionFormation> PDF =
      occ::down_cast<StepBasic_ProductDefinitionFormation>(subs.Value());
    if (PDF.IsNull())
      continue;
    FM = FeaModel(PDF);
  }
  return FM;
}

occ::handle<StepFEA_FeaModel> StepAP209_Construct::FeaModel(
  const occ::handle<StepBasic_ProductDefinitionFormation>& PDF) const
{
  occ::handle<StepFEA_FeaModel> FM;
  if (PDF.IsNull())
    return FM;
  occ::handle<StepBasic_ProductDefinitionFormation> PDF2;
  Interface_EntityIterator                          subs = Graph().Sharings(PDF);
  for (subs.Start(); subs.More(); subs.Next())
  {
    occ::handle<StepBasic_ProductDefinitionFormationRelationship> PDFR =
      occ::down_cast<StepBasic_ProductDefinitionFormationRelationship>(subs.Value());
    if (PDFR.IsNull())
      continue;
    PDF2 = PDFR->RelatedProductDefinitionFormation();
  }
  if (PDF2.IsNull())
    return FM;
  subs = Graph().Sharings(PDF2);
  for (subs.Start(); subs.More() && FM.IsNull(); subs.Next())
  {
    occ::handle<StepBasic_ProductDefinition> PD =
      occ::down_cast<StepBasic_ProductDefinition>(subs.Value());
    if (PD.IsNull())
      continue;
    Interface_EntityIterator subs2 = Graph().Sharings(PD);
    for (subs2.Start(); subs2.More() && FM.IsNull(); subs2.Next())
    {
      occ::handle<StepRepr_ProductDefinitionShape> PDS =
        occ::down_cast<StepRepr_ProductDefinitionShape>(subs2.Value());
      if (PDS.IsNull())
        continue;
      FM = FeaModel(PDS);
    }
  }
  return FM;
}

occ::handle<StepFEA_FeaModel> StepAP209_Construct::FeaModel(
  const occ::handle<StepRepr_ProductDefinitionShape>& PDS) const
{
  occ::handle<StepFEA_FeaModel> FM;
  Interface_EntityIterator      subs = Graph().Sharings(PDS);
  for (subs.Start(); subs.More() && FM.IsNull(); subs.Next())
  {
    occ::handle<StepFEA_FeaModelDefinition> FMD =
      occ::down_cast<StepFEA_FeaModelDefinition>(subs.Value());
    if (FMD.IsNull())
      continue;
    Interface_EntityIterator subs2 = Graph().Sharings(FMD);
    for (subs2.Start(); subs2.More() && FM.IsNull(); subs2.Next())
    {

      occ::handle<StepRepr_StructuralResponseProperty> SRP =
        occ::down_cast<StepRepr_StructuralResponseProperty>(subs2.Value());
      if (SRP.IsNull())
        continue;
      Interface_EntityIterator subs3 = Graph().Sharings(SRP);
      for (subs3.Start(); subs3.More() && FM.IsNull(); subs3.Next())
      {

        occ::handle<StepRepr_StructuralResponsePropertyDefinitionRepresentation> SRPDR =
          occ::down_cast<StepRepr_StructuralResponsePropertyDefinitionRepresentation>(
            subs3.Value());
        if (SRPDR.IsNull())
          continue;
        occ::handle<StepRepr_Representation> Repr = SRPDR->UsedRepresentation();
        if (Repr.IsNull())
          continue;
        if (Repr->IsKind(STANDARD_TYPE(StepFEA_FeaModel)))
          FM = occ::down_cast<StepFEA_FeaModel>(Repr);
      }
    }
  }
  return FM;
}

occ::handle<StepFEA_FeaAxis2Placement3d> StepAP209_Construct::GetFeaAxis2Placement3d(
  const occ::handle<StepFEA_FeaModel>& theFeaModel) const
{
  occ::handle<StepFEA_FeaAxis2Placement3d> FA2P3D = new StepFEA_FeaAxis2Placement3d;
  if (theFeaModel.IsNull())
    return FA2P3D;
  Interface_EntityIterator subs = Graph().Shareds(theFeaModel);
  for (subs.Start(); subs.More(); subs.Next())
  {
    FA2P3D = occ::down_cast<StepFEA_FeaAxis2Placement3d>(subs.Value());
    if (FA2P3D.IsNull())
      continue;
    return FA2P3D;
  }
  return FA2P3D;
}

occ::handle<StepShape_ShapeRepresentation> StepAP209_Construct::IdealShape(
  const occ::handle<StepBasic_Product>& Prod) const
{
  occ::handle<StepShape_ShapeRepresentation> SR;
  if (Prod.IsNull())
    return SR;
  Interface_EntityIterator subs = Graph().Sharings(Prod);
  for (subs.Start(); subs.More() && SR.IsNull(); subs.Next())
  {
    occ::handle<StepBasic_ProductDefinitionFormation> PDF =
      occ::down_cast<StepBasic_ProductDefinitionFormation>(subs.Value());
    if (PDF.IsNull())
      continue;
    SR = IdealShape(PDF);
  }
  return SR;
}

occ::handle<StepShape_ShapeRepresentation> StepAP209_Construct::IdealShape(
  const occ::handle<StepBasic_ProductDefinition>& PD) const
{
  occ::handle<StepShape_ShapeRepresentation> SR;
  if (PD.IsNull())
    return SR;
  Interface_EntityIterator subs = Graph().Shareds(PD);
  for (subs.Start(); subs.More() && SR.IsNull(); subs.Next())
  {
    occ::handle<StepBasic_ProductDefinitionFormation> PDF =
      occ::down_cast<StepBasic_ProductDefinitionFormation>(subs.Value());
    if (PDF.IsNull())
      continue;
    SR = IdealShape(PDF);
  }
  return SR;
}

occ::handle<StepShape_ShapeRepresentation> StepAP209_Construct::IdealShape(
  const occ::handle<StepBasic_ProductDefinitionFormation>& PDF) const
{
  occ::handle<StepShape_ShapeRepresentation> SR;
  if (PDF.IsNull())
    return SR;
  occ::handle<StepBasic_ProductDefinitionFormation> PDF2;
  Interface_EntityIterator                          subs = Graph().Sharings(PDF);
  for (subs.Start(); subs.More(); subs.Next())
  {
    occ::handle<StepBasic_ProductDefinitionFormationRelationship> PDFR =
      occ::down_cast<StepBasic_ProductDefinitionFormationRelationship>(subs.Value());
    if (PDFR.IsNull())
      continue;
    PDF2 = PDFR->RelatedProductDefinitionFormation();
  }
  if (PDF2.IsNull())
    return SR;
  subs = Graph().Sharings(PDF2);
  for (subs.Start(); subs.More() && SR.IsNull(); subs.Next())
  {
    occ::handle<StepBasic_ProductDefinition> PD =
      occ::down_cast<StepBasic_ProductDefinition>(subs.Value());
    if (PD.IsNull())
      continue;
    Interface_EntityIterator subs2 = Graph().Sharings(PD);
    for (subs2.Start(); subs2.More() && SR.IsNull(); subs2.Next())
    {
      occ::handle<StepRepr_ProductDefinitionShape> PDS =
        occ::down_cast<StepRepr_ProductDefinitionShape>(subs2.Value());
      if (PDS.IsNull())
        continue;
      SR = IdealShape(PDS);
    }
  }
  return SR;
}

occ::handle<StepShape_ShapeRepresentation> StepAP209_Construct::IdealShape(
  const occ::handle<StepRepr_ProductDefinitionShape>& PDS) const
{
  occ::handle<StepShape_ShapeRepresentation> SR;
  Interface_EntityIterator                   subs = Graph().Sharings(PDS);
  for (subs.Start(); subs.More() && SR.IsNull(); subs.Next())
  {
    occ::handle<StepShape_ShapeDefinitionRepresentation> SDR =
      occ::down_cast<StepShape_ShapeDefinitionRepresentation>(subs.Value());
    if (SDR.IsNull())
      continue;
    SR = occ::down_cast<StepShape_ShapeRepresentation>(SDR->UsedRepresentation());
  }
  return SR;
}

occ::handle<StepShape_ShapeRepresentation> StepAP209_Construct::NominShape(
  const occ::handle<StepBasic_Product>& Prod) const
{
  occ::handle<StepShape_ShapeRepresentation> SR;
  if (Prod.IsNull())
    return SR;
  Interface_EntityIterator subs = Graph().Sharings(Prod);
  for (subs.Start(); subs.More() && SR.IsNull(); subs.Next())
  {
    occ::handle<StepBasic_ProductDefinitionFormation> PDF =
      occ::down_cast<StepBasic_ProductDefinitionFormation>(subs.Value());
    if (PDF.IsNull())
      continue;
    SR = NominShape(PDF);
  }
  return SR;
}

occ::handle<StepShape_ShapeRepresentation> StepAP209_Construct::NominShape(
  const occ::handle<StepBasic_ProductDefinitionFormation>& PDF) const
{
  occ::handle<StepShape_ShapeRepresentation> SR;
  if (PDF.IsNull())
    return SR;
  occ::handle<StepBasic_ProductDefinitionFormation> PDF2;
  Interface_EntityIterator                          subs = Graph().Sharings(PDF);
  for (subs.Start(); subs.More(); subs.Next())
  {
    occ::handle<StepBasic_ProductDefinitionFormationRelationship> PDFR =
      occ::down_cast<StepBasic_ProductDefinitionFormationRelationship>(subs.Value());
    if (PDFR.IsNull())
      continue;
    PDF2 = PDFR->RelatingProductDefinitionFormation();
  }
  if (PDF2.IsNull())
    return SR;
  subs = Graph().Sharings(PDF2);
  for (subs.Start(); subs.More() && SR.IsNull(); subs.Next())
  {
    occ::handle<StepBasic_ProductDefinition> PD =
      occ::down_cast<StepBasic_ProductDefinition>(subs.Value());
    if (PD.IsNull())
      continue;
    Interface_EntityIterator subs2 = Graph().Sharings(PD);
    for (subs2.Start(); subs2.More() && SR.IsNull(); subs2.Next())
    {
      occ::handle<StepRepr_ProductDefinitionShape> PDS =
        occ::down_cast<StepRepr_ProductDefinitionShape>(subs2.Value());
      if (PDS.IsNull())
        continue;
      Interface_EntityIterator subs3 = Graph().Sharings(PDS);
      for (subs3.Start(); subs3.More() && SR.IsNull(); subs3.Next())
      {
        occ::handle<StepShape_ShapeDefinitionRepresentation> SDR =
          occ::down_cast<StepShape_ShapeDefinitionRepresentation>(subs3.Value());
        if (SDR.IsNull())
          continue;
        SR = occ::down_cast<StepShape_ShapeRepresentation>(SDR->UsedRepresentation());
      }
    }
  }
  return SR;
}

occ::handle<NCollection_HSequence<occ::handle<StepFEA_ElementRepresentation>>> StepAP209_Construct::
  GetElements1D(const occ::handle<StepFEA_FeaModel>& theFeaModel) const
{
  return GetFeaElements(theFeaModel, STANDARD_TYPE(StepFEA_Curve3dElementRepresentation));
}

occ::handle<NCollection_HSequence<occ::handle<StepFEA_ElementRepresentation>>> StepAP209_Construct::
  GetElements2D(const occ::handle<StepFEA_FeaModel>& theFeaModel) const
{
  return GetFeaElements(theFeaModel, STANDARD_TYPE(StepFEA_Surface3dElementRepresentation));
}

occ::handle<NCollection_HSequence<occ::handle<StepFEA_ElementRepresentation>>> StepAP209_Construct::
  GetElements3D(const occ::handle<StepFEA_FeaModel>& theFeaModel) const
{
  return GetFeaElements(theFeaModel, STANDARD_TYPE(StepFEA_Volume3dElementRepresentation));
}

occ::handle<NCollection_HSequence<occ::handle<StepFEA_ElementRepresentation>>> StepAP209_Construct::
  GetFeaElements(const occ::handle<StepFEA_FeaModel>& theFeaModel,
                 const occ::handle<Standard_Type>&    theType) const
{
  occ::handle<NCollection_HSequence<occ::handle<StepFEA_ElementRepresentation>>> aSequence;
  if (!theType->SubType(STANDARD_TYPE(StepFEA_ElementRepresentation)))
    return aSequence;

  Interface_EntityIterator anIter = Graph().Sharings(theFeaModel);
  anIter.Start();
  if (anIter.More())
    aSequence = new NCollection_HSequence<occ::handle<StepFEA_ElementRepresentation>>;

  for (; anIter.More(); anIter.Next())
  {
    const occ::handle<Standard_Transient>& anEntity = anIter.Value();
    if (anEntity->IsKind(theType))
    {
      occ::handle<StepFEA_ElementRepresentation> anElement =
        occ::down_cast<StepFEA_ElementRepresentation>(anEntity);
      aSequence->Append(anElement);
    }
  }
  return aSequence;
}

occ::handle<NCollection_HSequence<occ::handle<StepElement_CurveElementSectionDefinition>>>
  StepAP209_Construct::GetCurElemSection(
    const occ::handle<StepFEA_Curve3dElementRepresentation>& ElemRepr) const
{
  occ::handle<NCollection_HSequence<occ::handle<StepElement_CurveElementSectionDefinition>>>
    aSequence = new NCollection_HSequence<occ::handle<StepElement_CurveElementSectionDefinition>>;
  if (ElemRepr.IsNull())
    return aSequence;

  occ::handle<StepFEA_Curve3dElementProperty> C3dEP = ElemRepr->Property();
  if (C3dEP.IsNull())
    return aSequence;

  occ::handle<NCollection_HArray1<occ::handle<StepFEA_CurveElementInterval>>> ACEI =
    C3dEP->IntervalDefinitions();
  if (ACEI.IsNull())
    return aSequence;

  for (int i = 1; i <= ACEI->Length(); i++)
  {
    occ::handle<StepFEA_CurveElementIntervalConstant> CEIC =
      occ::down_cast<StepFEA_CurveElementIntervalConstant>(ACEI->Value(i));
    if (CEIC.IsNull())
      continue;
    aSequence->Append(CEIC->Section());
  }
  return aSequence;
}

bool StepAP209_Construct::CreateAnalysStructure(const occ::handle<StepBasic_Product>& Prod) const
{
  if (Prod.IsNull())
    return false;
  Interface_EntityIterator                          subs = Graph().Sharings(Prod);
  occ::handle<StepBasic_ProductDefinitionFormation> PDF;
  for (subs.Start(); subs.More() && PDF.IsNull(); subs.Next())
  {
    PDF = occ::down_cast<StepBasic_ProductDefinitionFormation>(subs.Value());
    if (PDF.IsNull())
      continue;
  }
  if (PDF.IsNull())
    return false;

  occ::handle<StepShape_ShapeRepresentation> SR;
  occ::handle<StepBasic_ProductDefinition>   PD;
  subs = Graph().Sharings(PDF);
  for (subs.Start(); subs.More() && SR.IsNull(); subs.Next())
  {
    PD = occ::down_cast<StepBasic_ProductDefinition>(subs.Value());
    if (PD.IsNull())
      continue;
    Interface_EntityIterator subs2 = Graph().Sharings(PD);
    for (subs2.Start(); subs2.More() && SR.IsNull(); subs2.Next())
    {
      occ::handle<StepRepr_ProductDefinitionShape> PDS =
        occ::down_cast<StepRepr_ProductDefinitionShape>(subs2.Value());
      if (PDS.IsNull())
        continue;
      Interface_EntityIterator subs3 = Graph().Sharings(PDS);
      for (subs3.Start(); subs3.More() && SR.IsNull(); subs3.Next())
      {
        occ::handle<StepShape_ShapeDefinitionRepresentation> SDR =
          occ::down_cast<StepShape_ShapeDefinitionRepresentation>(subs3.Value());
        if (SDR.IsNull())
          continue;
        SR = occ::down_cast<StepShape_ShapeRepresentation>(SDR->UsedRepresentation());
      }
    }
  }
  if (SR.IsNull())
    return false;

  ReplaceCcDesingToApplied();
  occ::handle<StepData_StepModel> smodel = occ::down_cast<StepData_StepModel>(Model());

  occ::handle<StepBasic_ProductContext> OldProdCtx = Prod->FrameOfReferenceValue(1);
  if (!OldProdCtx.IsNull())
  {
    occ::handle<StepBasic_ProductContext> ProdCtx = new StepBasic_ProductContext;
    ProdCtx->Init(OldProdCtx->Name(), OldProdCtx->FrameOfReference(), OldProdCtx->DisciplineType());
    smodel->ReplaceEntity(smodel->Number(OldProdCtx), ProdCtx);
    smodel->SetIdentLabel(ProdCtx, smodel->Number(ProdCtx));
    occ::handle<NCollection_HArray1<occ::handle<StepBasic_ProductContext>>> HAPC =
      Prod->FrameOfReference();
    HAPC->SetValue(1, ProdCtx);
    Prod->SetFrameOfReference(HAPC);
  }
  occ::handle<StepBasic_ProductDefinitionContext> OldPDCtx = PD->FrameOfReference();
  if (!OldPDCtx.IsNull())
  {
    occ::handle<StepBasic_ProductDefinitionContext> PDCtx = new StepBasic_ProductDefinitionContext;
    PDCtx->Init(OldPDCtx->Name(), OldPDCtx->FrameOfReference(), OldPDCtx->LifeCycleStage());
    smodel->ReplaceEntity(smodel->Number(OldPDCtx), PDCtx);
    smodel->SetIdentLabel(PDCtx, smodel->Number(PDCtx));
    PD->SetFrameOfReference(PDCtx);
  }

  occ::handle<StepShape_ShapeRepresentation> AnaSR = new StepShape_ShapeRepresentation;
  occ::handle<StepRepr_RepresentationItem>   RI    = new StepRepr_RepresentationItem;
  RI                                               = SR->ItemsValue(1);
  smodel->AddWithRefs(RI);
  smodel->SetIdentLabel(RI, smodel->Number(RI));
  occ::handle<NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>> ARI =
    new NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>(1, 1);
  ARI->SetValue(1, RI);
  AnaSR->Init(new TCollection_HAsciiString("idealized_analysis_shape"), ARI, SR->ContextOfItems());
  smodel->AddWithRefs(AnaSR);
  smodel->SetIdentLabel(AnaSR, smodel->Number(AnaSR));

  occ::handle<StepBasic_Product> AnaProd = new StepBasic_Product;
  AnaProd->Init(new TCollection_HAsciiString(""),
                new TCollection_HAsciiString("analysis"),
                new TCollection_HAsciiString("analysis product"),
                Prod->FrameOfReference());
  smodel->AddWithRefs(AnaProd);
  smodel->SetIdentLabel(AnaProd, smodel->Number(AnaProd));

  occ::handle<StepBasic_ProductDefinitionFormation> AnaPDF =
    new StepBasic_ProductDefinitionFormation;
  AnaPDF->Init(new TCollection_HAsciiString(""),
               new TCollection_HAsciiString("analysis version"),
               AnaProd);
  smodel->AddWithRefs(AnaPDF);
  smodel->SetIdentLabel(AnaPDF, smodel->Number(AnaPDF));

  occ::handle<StepBasic_ProductDefinitionFormationRelationship> PDFR =
    new StepBasic_ProductDefinitionFormationRelationship;
  PDFR->Init(new TCollection_HAsciiString(""),
             new TCollection_HAsciiString("analysis design version relationship"),
             new TCollection_HAsciiString(""),
             PDF,
             AnaPDF);
  smodel->AddWithRefs(PDFR);
  smodel->SetIdentLabel(PDFR, smodel->Number(PDFR));

  occ::handle<StepBasic_ProductDefinition>        AnaPD  = new StepBasic_ProductDefinition;
  occ::handle<StepBasic_ProductDefinitionContext> AnaPDC = new StepBasic_ProductDefinitionContext;
  occ::handle<StepBasic_ApplicationContext> AC = Prod->FrameOfReferenceValue(1)->FrameOfReference();
  AnaPDC->Init(new TCollection_HAsciiString("analysis"),
               AC,
               new TCollection_HAsciiString("analysis"));
  smodel->AddWithRefs(AnaPDC);
  smodel->SetIdentLabel(AnaPDC, smodel->Number(AnaPDC));
  AnaPD->Init(new TCollection_HAsciiString("analysis"),
              new TCollection_HAsciiString("analysis discipline product definition"),
              AnaPDF,
              AnaPDC);
  smodel->AddWithRefs(AnaPD);
  smodel->SetIdentLabel(AnaPD, smodel->Number(AnaPD));

  occ::handle<StepRepr_ProductDefinitionShape> AnaPDS = new StepRepr_ProductDefinitionShape;
  StepRepr_CharacterizedDefinition             ChDef;
  ChDef.SetValue(AnaPD);
  AnaPDS->Init(new TCollection_HAsciiString(""),
               true,
               new TCollection_HAsciiString("analysis shape"),
               ChDef);
  smodel->AddWithRefs(AnaPDS);
  smodel->SetIdentLabel(AnaPDS, smodel->Number(AnaPDS));

  occ::handle<StepShape_ShapeDefinitionRepresentation> AnaSDR =
    new StepShape_ShapeDefinitionRepresentation;
  StepRepr_RepresentedDefinition RepDef;
  RepDef.SetValue(AnaPDS);
  AnaSDR->Init(RepDef, AnaSR);
  smodel->AddWithRefs(AnaSDR);
  smodel->SetIdentLabel(AnaSDR, smodel->Number(AnaSDR));

  occ::handle<StepRepr_ShapeRepresentationRelationship> SRR =
    new StepRepr_ShapeRepresentationRelationship;
  SRR->Init(new TCollection_HAsciiString("basis"), new TCollection_HAsciiString(""), AnaSR, SR);
  smodel->AddWithRefs(SRR);
  smodel->SetIdentLabel(SRR, smodel->Number(SRR));

  CreateAddingEntities(AnaPD);

  WS()->ComputeGraph(true);
  WS()->ComputeCheck(true);

  return true;
}

bool StepAP209_Construct::CreateFeaStructure(const occ::handle<StepBasic_Product>& Prod) const
{
  if (Prod.IsNull())
  {
#ifdef OCCT_DEBUG
    std::cout << "Prod.IsNull()" << std::endl;
#endif
    return false;
  }
  occ::handle<StepShape_ShapeRepresentation> AnaSR = IdealShape(Prod);
  if (AnaSR.IsNull())
  {
#ifdef OCCT_DEBUG
    std::cout << "AnaSR.IsNull()" << std::endl;
#endif
    return false;
  }
  occ::handle<StepRepr_ProductDefinitionShape> AnaPDS;
  Interface_EntityIterator                     subs = Graph().Sharings(AnaSR);
  for (subs.Start(); subs.More() && AnaPDS.IsNull(); subs.Next())
  {
    occ::handle<StepShape_ShapeDefinitionRepresentation> SDR =
      occ::down_cast<StepShape_ShapeDefinitionRepresentation>(subs.Value());
    if (SDR.IsNull())
      continue;
    AnaPDS = occ::down_cast<StepRepr_ProductDefinitionShape>(SDR->Definition().Value());
  }

  occ::handle<StepData_StepModel> smodel = occ::down_cast<StepData_StepModel>(Model());

  occ::handle<StepFEA_FeaModelDefinition> FMD = new StepFEA_FeaModelDefinition;
  FMD->Init(new TCollection_HAsciiString("FEA_MODEL"),
            new TCollection_HAsciiString("FEA_MODEL"),
            AnaPDS,
            StepData_LFalse);
  smodel->AddWithRefs(FMD);
  smodel->SetIdentLabel(FMD, smodel->Number(FMD));

  occ::handle<StepFEA_FeaAxis2Placement3d> FA2P3D = new StepFEA_FeaAxis2Placement3d;
  occ::handle<StepGeom_CartesianPoint>     SGCP   = new StepGeom_CartesianPoint;
  SGCP->Init3D(new TCollection_HAsciiString(""), 0., 0., 0.);
  occ::handle<NCollection_HArray1<double>> ArrTmp = new NCollection_HArray1<double>(1, 3);
  ArrTmp->SetValue(1, 0.);
  ArrTmp->SetValue(2, 0.);
  ArrTmp->SetValue(3, 1.);
  occ::handle<StepGeom_Direction> SGD1 = new StepGeom_Direction;
  SGD1->Init(new TCollection_HAsciiString(""), ArrTmp);
  ArrTmp->SetValue(1, 1.);
  ArrTmp->SetValue(2, 0.);
  ArrTmp->SetValue(3, 0.);
  occ::handle<StepGeom_Direction> SGD2 = new StepGeom_Direction;
  SGD2->Init(new TCollection_HAsciiString(""), ArrTmp);
  FA2P3D->Init(new TCollection_HAsciiString("FEA_BASIC_COORD_SYSTEM"),
               SGCP,
               true,
               SGD1,
               true,
               SGD2,
               StepFEA_Cartesian,
               new TCollection_HAsciiString("FEA_BASIC_COORD_SYSTEM"));
  smodel->AddWithRefs(FA2P3D);
  smodel->SetIdentLabel(FA2P3D, smodel->Number(FA2P3D));

  occ::handle<StepShape_ShapeRepresentation>                         NS = NominShape(Prod);
  occ::handle<StepRepr_RepresentationContext>                        RC = NS->ContextOfItems();
  occ::handle<StepGeom_GeometricRepresentationContext>               GeoCtx;
  occ::handle<NCollection_HArray1<occ::handle<StepBasic_NamedUnit>>> OldHANU;
  if (RC->IsKind(STANDARD_TYPE(StepGeom_GeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx)))
  {
    occ::handle<StepGeom_GeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx> GeoUnitCtxNS =
      occ::down_cast<StepGeom_GeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx>(RC);
    GeoCtx  = GeoUnitCtxNS->GeometricRepresentationContext();
    OldHANU = GeoUnitCtxNS->GlobalUnitAssignedContext()->Units();
  }
  if (RC->IsKind(
        STANDARD_TYPE(StepGeom_GeometricRepresentationContextAndGlobalUnitAssignedContext)))
  {
    occ::handle<StepGeom_GeometricRepresentationContextAndGlobalUnitAssignedContext> GeoUnitCtxNS =
      occ::down_cast<StepGeom_GeometricRepresentationContextAndGlobalUnitAssignedContext>(RC);
    GeoCtx  = GeoUnitCtxNS->GeometricRepresentationContext();
    OldHANU = GeoUnitCtxNS->GlobalUnitAssignedContext()->Units();
  }
  occ::handle<NCollection_HArray1<occ::handle<StepBasic_NamedUnit>>> NewHANU =
    new NCollection_HArray1<occ::handle<StepBasic_NamedUnit>>(1, OldHANU->Length() + 3);
  for (int i = 1; i <= OldHANU->Length(); i++)
    NewHANU->SetValue(i, OldHANU->Value(i));

  occ::handle<StepBasic_SiUnitAndTimeUnit> SUTU = new StepBasic_SiUnitAndTimeUnit;
  SUTU->Init(false, StepBasic_spExa, StepBasic_sunSecond);
  smodel->AddWithRefs(SUTU);
  smodel->SetIdentLabel(SUTU, smodel->Number(SUTU));
  NewHANU->SetValue(OldHANU->Length() + 1, SUTU);

  occ::handle<StepBasic_SiUnitAndMassUnit> SUMU = new StepBasic_SiUnitAndMassUnit;
  SUMU->Init(true, StepBasic_spKilo, StepBasic_sunGram);
  smodel->AddWithRefs(SUMU);
  smodel->SetIdentLabel(SUMU, smodel->Number(SUMU));
  NewHANU->SetValue(OldHANU->Length() + 2, SUMU);

  occ::handle<StepBasic_SiUnitAndThermodynamicTemperatureUnit> SUTTU =
    new StepBasic_SiUnitAndThermodynamicTemperatureUnit;
  SUTTU->Init(false, StepBasic_spExa, StepBasic_sunDegreeCelsius);
  smodel->AddWithRefs(SUTTU);
  smodel->SetIdentLabel(SUTTU, smodel->Number(SUTTU));
  NewHANU->SetValue(OldHANU->Length() + 3, SUTTU);

  occ::handle<StepRepr_GlobalUnitAssignedContext> NewUnitCtx =
    new StepRepr_GlobalUnitAssignedContext;
  NewUnitCtx->Init(new TCollection_HAsciiString(""), new TCollection_HAsciiString(""), NewHANU);
  occ::handle<StepGeom_GeometricRepresentationContextAndGlobalUnitAssignedContext> NewGeoCtx =
    new StepGeom_GeometricRepresentationContextAndGlobalUnitAssignedContext;
  NewGeoCtx->Init(new TCollection_HAsciiString("REP_CONTEXT_FEA"),
                  new TCollection_HAsciiString("3D"),
                  GeoCtx,
                  NewUnitCtx);
  smodel->AddWithRefs(NewGeoCtx);
  smodel->SetIdentLabel(NewGeoCtx, smodel->Number(NewGeoCtx));

  occ::handle<StepFEA_FeaModel3d> FM = new StepFEA_FeaModel3d;
  FM->SetName(new TCollection_HAsciiString("FEA_MODEL"));
  occ::handle<NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>> HARI =
    new NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>(1, 1);
  HARI->SetValue(1, FA2P3D);
  occ::handle<NCollection_HArray1<TCollection_AsciiString>> HAAS =
    new NCollection_HArray1<TCollection_AsciiString>(1, 1);
  HAAS->SetValue(1, "FEA_SOLVER");
  FM->Init(new TCollection_HAsciiString("FEA_MODEL"),
           HARI,
           NewGeoCtx,
           new TCollection_HAsciiString(""),
           HAAS,
           new TCollection_HAsciiString("ANALYSIS_MODEL"),
           new TCollection_HAsciiString("LINEAR_STATIC"));
  smodel->AddWithRefs(FM);
  smodel->SetIdentLabel(FM, smodel->Number(FM));

  occ::handle<StepRepr_StructuralResponseProperty> SRP = new StepRepr_StructuralResponseProperty;
  StepRepr_CharacterizedDefinition                 ChDef2;
  ChDef2.SetValue(FMD);
  SRP->Init(new TCollection_HAsciiString("STRUCT_RESP_PROP"),
            true,
            new TCollection_HAsciiString("STRUCTURAL_RESPONSE_PROPERTY"),
            ChDef2);
  smodel->AddWithRefs(SRP);
  smodel->SetIdentLabel(SRP, smodel->Number(SRP));

  occ::handle<StepRepr_StructuralResponsePropertyDefinitionRepresentation> SRPDR =
    new StepRepr_StructuralResponsePropertyDefinitionRepresentation;
  StepRepr_RepresentedDefinition RepDef2;
  RepDef2.SetValue(SRP);
  SRPDR->Init(RepDef2, FM);
  smodel->AddWithRefs(SRPDR);
  smodel->SetIdentLabel(SRPDR, smodel->Number(SRPDR));

  WS()->ComputeGraph(true);
  WS()->ComputeCheck(true);

  return true;
}

bool StepAP209_Construct::ReplaceCcDesingToApplied() const
{
  occ::handle<StepData_StepModel> smodel = occ::down_cast<StepData_StepModel>(Model());
  int                             nb     = smodel->NbEntities();
  for (int i = 1; i <= nb; i++)
  {
    occ::handle<Standard_Transient> anEntity = smodel->Value(i);
    if (anEntity->IsKind(STANDARD_TYPE(StepAP203_CcDesignApproval)))
    {
      occ::handle<StepAP203_CcDesignApproval> ent =
        occ::down_cast<StepAP203_CcDesignApproval>(anEntity);
      occ::handle<StepAP214_AppliedApprovalAssignment> nent =
        new StepAP214_AppliedApprovalAssignment;
      occ::handle<NCollection_HArray1<StepAP203_ApprovedItem>> HAAI203 = ent->Items();
      occ::handle<NCollection_HArray1<StepAP214_ApprovalItem>> HAAI214 =
        new NCollection_HArray1<StepAP214_ApprovalItem>(1, HAAI203->Length());
      for (int j = 1; j <= HAAI203->Length(); j++)
      {
        StepAP214_ApprovalItem AI214;
        AI214.SetValue(HAAI203->Value(j).Value());
        HAAI214->SetValue(j, AI214);
      }
      nent->Init(ent->AssignedApproval(), HAAI214);
      smodel->ReplaceEntity(i, nent);
      smodel->SetIdentLabel(nent, smodel->Number(nent));
    }
    else if (anEntity->IsKind(STANDARD_TYPE(StepAP203_CcDesignPersonAndOrganizationAssignment)))
    {
      occ::handle<StepAP203_CcDesignPersonAndOrganizationAssignment> ent =
        occ::down_cast<StepAP203_CcDesignPersonAndOrganizationAssignment>(anEntity);
      occ::handle<StepAP214_AppliedPersonAndOrganizationAssignment> nent =
        new StepAP214_AppliedPersonAndOrganizationAssignment;
      occ::handle<NCollection_HArray1<StepAP203_PersonOrganizationItem>>    HAPOI203 = ent->Items();
      occ::handle<NCollection_HArray1<StepAP214_PersonAndOrganizationItem>> HAPOI214 =
        new NCollection_HArray1<StepAP214_PersonAndOrganizationItem>(1, HAPOI203->Length());
      for (int j = 1; j <= HAPOI203->Length(); j++)
      {
        StepAP214_PersonAndOrganizationItem POI214;
        POI214.SetValue(HAPOI203->Value(j).Value());
        HAPOI214->SetValue(j, POI214);
      }
      nent->Init(ent->AssignedPersonAndOrganization(), ent->Role(), HAPOI214);
      smodel->ReplaceEntity(i, nent);
      smodel->SetIdentLabel(nent, smodel->Number(nent));
    }
    else if (anEntity->IsKind(STANDARD_TYPE(StepAP203_CcDesignDateAndTimeAssignment)))
    {
      occ::handle<StepAP203_CcDesignDateAndTimeAssignment> ent =
        occ::down_cast<StepAP203_CcDesignDateAndTimeAssignment>(anEntity);
      occ::handle<StepAP214_AppliedDateAndTimeAssignment> nent =
        new StepAP214_AppliedDateAndTimeAssignment;
      occ::handle<NCollection_HArray1<StepAP203_DateTimeItem>>    HADTI203 = ent->Items();
      occ::handle<NCollection_HArray1<StepAP214_DateAndTimeItem>> HADTI214 =
        new NCollection_HArray1<StepAP214_DateAndTimeItem>(1, HADTI203->Length());
      for (int j = 1; j <= HADTI203->Length(); j++)
      {
        StepAP214_DateAndTimeItem DTI214;
        DTI214.SetValue(HADTI203->Value(j).Value());
        HADTI214->SetValue(j, DTI214);
      }
      nent->Init(ent->AssignedDateAndTime(), ent->Role(), HADTI214);
      smodel->ReplaceEntity(i, nent);
      smodel->SetIdentLabel(nent, smodel->Number(nent));
    }
    else if (anEntity->IsKind(STANDARD_TYPE(StepAP203_CcDesignSecurityClassification)))
    {
      occ::handle<StepAP203_CcDesignSecurityClassification> ent =
        occ::down_cast<StepAP203_CcDesignSecurityClassification>(anEntity);
      occ::handle<StepAP214_AppliedSecurityClassificationAssignment> nent =
        new StepAP214_AppliedSecurityClassificationAssignment;
      occ::handle<NCollection_HArray1<StepAP203_ClassifiedItem>>             HACI203 = ent->Items();
      occ::handle<NCollection_HArray1<StepAP214_SecurityClassificationItem>> HASCI214 =
        new NCollection_HArray1<StepAP214_SecurityClassificationItem>(1, HACI203->Length());
      for (int j = 1; j <= HACI203->Length(); j++)
      {
        StepAP214_SecurityClassificationItem SCI214;
        SCI214.SetValue(HACI203->Value(j).Value());
        HASCI214->SetValue(j, SCI214);
      }
      nent->Init(ent->AssignedSecurityClassification(), HASCI214);
      smodel->ReplaceEntity(i, nent);
      smodel->SetIdentLabel(nent, smodel->Number(nent));
    }
  }

  return true;
}

bool StepAP209_Construct::CreateAddingEntities(
  const occ::handle<StepBasic_ProductDefinition>& AnaPD) const
{
  occ::handle<StepData_StepModel> smodel = occ::down_cast<StepData_StepModel>(Model());
  occ::handle<StepBasic_ProductDefinitionFormation> AnaPDF  = AnaPD->Formation();
  occ::handle<StepBasic_Product>                    AnaProd = AnaPDF->OfProduct();

  occ::handle<StepBasic_ApprovalStatus> AS = new StepBasic_ApprovalStatus;
  AS->Init(new TCollection_HAsciiString("approved"));
  smodel->AddEntity(AS);
  smodel->SetIdentLabel(AS, smodel->Number(AS));
  occ::handle<StepBasic_Approval> Appr = new StepBasic_Approval;
  Appr->Init(AS, new TCollection_HAsciiString("approved"));
  smodel->AddWithRefs(Appr);
  smodel->SetIdentLabel(Appr, smodel->Number(Appr));

  occ::handle<StepBasic_SecurityClassificationLevel> SCL =
    new StepBasic_SecurityClassificationLevel;
  SCL->Init(new TCollection_HAsciiString("unclassified"));
  smodel->AddEntity(SCL);
  smodel->SetIdentLabel(SCL, smodel->Number(SCL));
  occ::handle<StepBasic_SecurityClassification> SC = new StepBasic_SecurityClassification;
  SC->Init(new TCollection_HAsciiString(""), new TCollection_HAsciiString(""), SCL);
  smodel->AddWithRefs(SC);
  smodel->SetIdentLabel(SC, smodel->Number(SC));

  occ::handle<StepAP214_AppliedApprovalAssignment> AAA = new StepAP214_AppliedApprovalAssignment;
  occ::handle<NCollection_HArray1<StepAP214_ApprovalItem>> HAAI =
    new NCollection_HArray1<StepAP214_ApprovalItem>(1, 3);
  StepAP214_ApprovalItem AI1;
  AI1.SetValue(AnaPD);
  HAAI->SetValue(1, AI1);
  StepAP214_ApprovalItem AI2;
  AI2.SetValue(AnaPDF);
  HAAI->SetValue(2, AI2);
  StepAP214_ApprovalItem AI3;
  AI3.SetValue(SC);
  HAAI->SetValue(3, AI3);
  AAA->Init(Appr, HAAI);
  smodel->AddWithRefs(AAA);
  smodel->SetIdentLabel(AAA, smodel->Number(AAA));

  occ::handle<StepAP214_AppliedSecurityClassificationAssignment> ASCA =
    new StepAP214_AppliedSecurityClassificationAssignment;
  occ::handle<NCollection_HArray1<StepAP214_SecurityClassificationItem>> HASCI =
    new NCollection_HArray1<StepAP214_SecurityClassificationItem>(1, 1);
  StepAP214_SecurityClassificationItem SCI;
  SCI.SetValue(AnaPDF);
  HASCI->SetValue(1, SCI);
  ASCA->Init(SC, HASCI);
  smodel->AddWithRefs(ASCA);
  smodel->SetIdentLabel(ASCA, smodel->Number(ASCA));

  OSD_Process   sys;
  Quantity_Date date = sys.SystemDate();

  occ::handle<StepBasic_CalendarDate> CDate = new StepBasic_CalendarDate;
  CDate->Init(date.Year(), date.Day(), date.Month());
  smodel->AddEntity(CDate);
  smodel->SetIdentLabel(CDate, smodel->Number(CDate));
  occ::handle<StepBasic_CoordinatedUniversalTimeOffset> CUTO =
    new StepBasic_CoordinatedUniversalTimeOffset;
  CUTO->Init(0, true, 0, StepBasic_aobAhead);
  smodel->AddEntity(CUTO);
  smodel->SetIdentLabel(CUTO, smodel->Number(CUTO));
  occ::handle<StepBasic_LocalTime> LT = new StepBasic_LocalTime;
  LT->Init(date.Hour(), true, date.Minute(), true, (double)date.Second(), CUTO);
  smodel->AddWithRefs(LT);
  smodel->SetIdentLabel(LT, smodel->Number(LT));
  occ::handle<StepBasic_DateAndTime> DAT = new StepBasic_DateAndTime;
  DAT->Init(CDate, LT);
  smodel->AddWithRefs(DAT);
  smodel->SetIdentLabel(DAT, smodel->Number(DAT));

  occ::handle<StepBasic_DateTimeRole> DTR = new StepBasic_DateTimeRole;
  DTR->Init(new TCollection_HAsciiString("classification_date"));
  smodel->AddEntity(DTR);
  smodel->SetIdentLabel(DTR, smodel->Number(DTR));
  occ::handle<StepAP214_AppliedDateAndTimeAssignment> ADTA =
    new StepAP214_AppliedDateAndTimeAssignment;
  occ::handle<NCollection_HArray1<StepAP214_DateAndTimeItem>> HADTI =
    new NCollection_HArray1<StepAP214_DateAndTimeItem>(1, 1);
  StepAP214_DateAndTimeItem DTI1;
  DTI1.SetValue(SC);
  HADTI->SetValue(1, DTI1);
  ADTA->Init(DAT, DTR, HADTI);
  smodel->AddWithRefs(ADTA);
  smodel->SetIdentLabel(ADTA, smodel->Number(ADTA));

  DTR = new StepBasic_DateTimeRole;
  DTR->Init(new TCollection_HAsciiString("creation_date"));
  smodel->AddEntity(DTR);
  smodel->SetIdentLabel(DTR, smodel->Number(DTR));
  ADTA  = new StepAP214_AppliedDateAndTimeAssignment;
  HADTI = new NCollection_HArray1<StepAP214_DateAndTimeItem>(1, 1);
  StepAP214_DateAndTimeItem DTI2;
  DTI2.SetValue(AnaPD);
  HADTI->SetValue(1, DTI2);
  ADTA->Init(DAT, DTR, HADTI);
  smodel->AddWithRefs(ADTA);
  smodel->SetIdentLabel(ADTA, smodel->Number(ADTA));

  occ::handle<StepBasic_ApprovalDateTime> ADT = new StepBasic_ApprovalDateTime;
  StepBasic_DateTimeSelect                DTS;
  DTS.SetValue(DAT);
  ADT->Init(DTS, Appr);
  smodel->AddWithRefs(ADT);
  smodel->SetIdentLabel(ADT, smodel->Number(ADT));

  occ::handle<StepBasic_Person> Pers = new StepBasic_Person;
  occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>> HAHAS =
    new NCollection_HArray1<occ::handle<TCollection_HAsciiString>>(1, 1);
  HAHAS->SetValue(1, new TCollection_HAsciiString(""));
  Pers->Init(new TCollection_HAsciiString("1"),
             true,
             new TCollection_HAsciiString("last_name"),
             true,
             new TCollection_HAsciiString("first_name"),
             true,
             HAHAS,
             true,
             HAHAS,
             true,
             HAHAS);
  smodel->AddEntity(Pers);
  smodel->SetIdentLabel(Pers, smodel->Number(Pers));
  occ::handle<StepBasic_Organization> Org = new StepBasic_Organization;
  Org->Init(true,
            new TCollection_HAsciiString("1"),
            new TCollection_HAsciiString("organisation"),
            new TCollection_HAsciiString("organisation_description"));
  smodel->AddEntity(Org);
  smodel->SetIdentLabel(Org, smodel->Number(Org));
  occ::handle<StepBasic_PersonAndOrganization> PO = new StepBasic_PersonAndOrganization;
  PO->Init(Pers, Org);
  smodel->AddWithRefs(PO);
  smodel->SetIdentLabel(PO, smodel->Number(PO));

  occ::handle<StepBasic_PersonAndOrganizationRole> POR = new StepBasic_PersonAndOrganizationRole;
  POR->Init(new TCollection_HAsciiString("analysis_owner"));
  smodel->AddEntity(POR);
  smodel->SetIdentLabel(POR, smodel->Number(POR));
  occ::handle<StepAP214_AppliedPersonAndOrganizationAssignment> APOA =
    new StepAP214_AppliedPersonAndOrganizationAssignment;
  occ::handle<NCollection_HArray1<StepAP214_PersonAndOrganizationItem>> HAPOI =
    new NCollection_HArray1<StepAP214_PersonAndOrganizationItem>(1, 1);
  StepAP214_PersonAndOrganizationItem POI1;
  POI1.SetValue(AnaProd);
  HAPOI->SetValue(1, POI1);
  APOA->Init(PO, POR, HAPOI);
  smodel->AddWithRefs(APOA);
  smodel->SetIdentLabel(APOA, smodel->Number(APOA));

  POR = new StepBasic_PersonAndOrganizationRole;
  POR->Init(new TCollection_HAsciiString("creator"));
  smodel->AddEntity(POR);
  smodel->SetIdentLabel(POR, smodel->Number(POR));
  APOA  = new StepAP214_AppliedPersonAndOrganizationAssignment;
  HAPOI = new NCollection_HArray1<StepAP214_PersonAndOrganizationItem>(1, 1);
  StepAP214_PersonAndOrganizationItem POI2;
  POI2.SetValue(AnaPD);
  HAPOI->SetValue(1, POI2);
  APOA->Init(PO, POR, HAPOI);
  smodel->AddWithRefs(APOA);
  smodel->SetIdentLabel(APOA, smodel->Number(APOA));

  POR = new StepBasic_PersonAndOrganizationRole;
  POR->Init(new TCollection_HAsciiString("analysis_owner"));
  smodel->AddEntity(POR);
  smodel->SetIdentLabel(POR, smodel->Number(POR));
  APOA  = new StepAP214_AppliedPersonAndOrganizationAssignment;
  HAPOI = new NCollection_HArray1<StepAP214_PersonAndOrganizationItem>(1, 1);
  StepAP214_PersonAndOrganizationItem POI3;
  POI3.SetValue(AnaPD);
  HAPOI->SetValue(1, POI3);
  APOA->Init(PO, POR, HAPOI);
  smodel->AddWithRefs(APOA);
  smodel->SetIdentLabel(APOA, smodel->Number(APOA));

  POR = new StepBasic_PersonAndOrganizationRole;
  POR->Init(new TCollection_HAsciiString("classification_officer"));
  smodel->AddEntity(POR);
  smodel->SetIdentLabel(POR, smodel->Number(POR));
  APOA  = new StepAP214_AppliedPersonAndOrganizationAssignment;
  HAPOI = new NCollection_HArray1<StepAP214_PersonAndOrganizationItem>(1, 1);
  StepAP214_PersonAndOrganizationItem POI4;
  POI4.SetValue(SC);
  HAPOI->SetValue(1, POI4);
  APOA->Init(PO, POR, HAPOI);
  smodel->AddWithRefs(APOA);
  smodel->SetIdentLabel(APOA, smodel->Number(APOA));

  POR = new StepBasic_PersonAndOrganizationRole;
  POR->Init(new TCollection_HAsciiString("creator"));
  smodel->AddEntity(POR);
  smodel->SetIdentLabel(POR, smodel->Number(POR));
  APOA  = new StepAP214_AppliedPersonAndOrganizationAssignment;
  HAPOI = new NCollection_HArray1<StepAP214_PersonAndOrganizationItem>(1, 1);
  StepAP214_PersonAndOrganizationItem POI5;
  POI5.SetValue(AnaPDF);
  HAPOI->SetValue(1, POI5);
  APOA->Init(PO, POR, HAPOI);
  smodel->AddWithRefs(APOA);
  smodel->SetIdentLabel(APOA, smodel->Number(APOA));

  occ::handle<StepBasic_ApprovalRole> AR = new StepBasic_ApprovalRole;
  AR->Init(new TCollection_HAsciiString("approver"));
  smodel->AddEntity(AR);
  smodel->SetIdentLabel(AR, smodel->Number(AR));
  occ::handle<StepBasic_ApprovalPersonOrganization> APO = new StepBasic_ApprovalPersonOrganization;
  StepBasic_PersonOrganizationSelect                POS;
  POS.SetValue(PO);
  APO->Init(POS, Appr, AR);
  smodel->AddWithRefs(APO);
  smodel->SetIdentLabel(APO, smodel->Number(APO));

  return true;
}

occ::handle<StepData_StepModel> StepAP209_Construct::CreateAP203Structure() const
{
  occ::handle<StepData_StepModel> smodel = occ::down_cast<StepData_StepModel>(Model());
  occ::handle<StepData_StepModel> nmodel;
  if (smodel.IsNull())
    return nmodel;

  occ::handle<StepBasic_ProductDefinitionFormation>    PDF;
  occ::handle<StepBasic_ProductDefinition>             PD;
  occ::handle<StepRepr_ProductDefinitionShape>         PDS;
  occ::handle<StepShape_ShapeDefinitionRepresentation> SDR;
  int                                                  nb = smodel->NbEntities();
  for (int i = 1; i <= nb; i++)
  {
    if (smodel->Value(i)->IsKind(STANDARD_TYPE(StepShape_ShapeDefinitionRepresentation)))
    {
      SDR = occ::down_cast<StepShape_ShapeDefinitionRepresentation>(smodel->Value(i));
      PDS = occ::down_cast<StepRepr_ProductDefinitionShape>(SDR->Definition().Value());
      if (PDS.IsNull())
        continue;
      PD = occ::down_cast<StepBasic_ProductDefinition>(PDS->Definition().Value());
      if (PD.IsNull())
        continue;
      occ::handle<StepBasic_ProductDefinitionFormation> PDF1 = PD->Formation();
      if (IsDesing(PDF1))
      {
        PDF = PDF1;
        i   = nb;
      }
    }
  }
  if (PDF.IsNull())
    return nmodel;
  nmodel = new StepData_StepModel;
  nmodel->SetProtocol(smodel->Protocol());

  occ::handle<StepBasic_Product> Prod = PDF->OfProduct();
  nmodel->AddWithRefs(Prod);

  occ::handle<NCollection_HArray1<occ::handle<StepBasic_Product>>> HAProd =
    new NCollection_HArray1<occ::handle<StepBasic_Product>>(1, 1);
  HAProd->SetValue(1, Prod);
  occ::handle<StepBasic_ProductRelatedProductCategory> PRPC =
    new StepBasic_ProductRelatedProductCategory;
  PRPC->Init(new TCollection_HAsciiString("design"), true, Prod->Name(), HAProd);
  nmodel->AddEntity(PRPC);
  occ::handle<StepBasic_ProductCategory> PCat = new StepBasic_ProductCategory;
  PCat->Init(new TCollection_HAsciiString("part"), true, Prod->Name());
  nmodel->AddEntity(PCat);

  occ::handle<StepBasic_ProductCategoryRelationship> PCR =
    new StepBasic_ProductCategoryRelationship;
  PCR->Init(new TCollection_HAsciiString(""), true, Prod->Name(), PCat, PRPC);
  nmodel->AddWithRefs(PCR);

  nmodel->AddWithRefs(PDF);
  nmodel->AddWithRefs(PD);

  occ::handle<StepBasic_ApplicationContext> ApplCtx;
  occ::handle<StepBasic_ProductContext>     ProdCtx = Prod->FrameOfReferenceValue(1);
  if (!ProdCtx.IsNull())
  {
    occ::handle<StepBasic_MechanicalContext> MechCtx = new StepBasic_MechanicalContext;
    MechCtx->Init(ProdCtx->Name(), ProdCtx->FrameOfReference(), ProdCtx->DisciplineType());
    nmodel->ReplaceEntity(nmodel->Number(ProdCtx), MechCtx);
    occ::handle<NCollection_HArray1<occ::handle<StepBasic_ProductContext>>> HAPC =
      new NCollection_HArray1<occ::handle<StepBasic_ProductContext>>(1, 1);
    HAPC->SetValue(1, MechCtx);
    Prod->SetFrameOfReference(HAPC);
    ApplCtx = MechCtx->FrameOfReference();
  }
  occ::handle<StepBasic_ProductDefinitionContext> PDCtx = PD->FrameOfReference();
  if (!PDCtx.IsNull())
  {
    occ::handle<StepBasic_DesignContext> DesCtx = new StepBasic_DesignContext;
    DesCtx->Init(PDCtx->Name(), PDCtx->FrameOfReference(), PDCtx->LifeCycleStage());
    nmodel->ReplaceEntity(nmodel->Number(PDCtx), DesCtx);
    PD->SetFrameOfReference(DesCtx);
    ApplCtx = DesCtx->FrameOfReference();
  }
  if (!ApplCtx.IsNull())
  {
    occ::handle<StepBasic_ApplicationProtocolDefinition> APD;
    Interface_EntityIterator                             subs = Graph().Sharings(ApplCtx);
    for (subs.Start(); subs.More() && APD.IsNull(); subs.Next())
    {
      APD = occ::down_cast<StepBasic_ApplicationProtocolDefinition>(subs.Value());
      if (APD.IsNull())
        continue;
      nmodel->AddWithRefs(APD);
    }
  }

  CreateAdding203Entities(PD, nmodel);

  nmodel->AddWithRefs(SDR);

  occ::handle<StepBasic_DimensionalExponents> DimExp = new StepBasic_DimensionalExponents;
  DimExp->Init(1., 0., 0., 0., 0., 0., 0.);
  nmodel->AddWithRefs(DimExp);
  DimExp = new StepBasic_DimensionalExponents;
  DimExp->Init(0., 0., 0., 0., 0., 0., 0.);
  nmodel->AddWithRefs(DimExp);

  nmodel->ClearHeader();
  occ::handle<HeaderSection_FileName> FN = occ::down_cast<HeaderSection_FileName>(
    smodel->HeaderEntity(STANDARD_TYPE(HeaderSection_FileName)));
  if (!FN.IsNull())
  {
    FN->SetPreprocessorVersion(new TCollection_HAsciiString("AP209 -> SDRB Convertor"));
    nmodel->AddHeaderEntity(FN);
  }
  occ::handle<HeaderSection_FileSchema> FS = occ::down_cast<HeaderSection_FileSchema>(
    smodel->HeaderEntity(STANDARD_TYPE(HeaderSection_FileSchema)));
  if (!FS.IsNull())
    nmodel->AddHeaderEntity(FS);
  occ::handle<HeaderSection_FileDescription> FD = occ::down_cast<HeaderSection_FileDescription>(
    smodel->HeaderEntity(STANDARD_TYPE(HeaderSection_FileDescription)));
  if (!FD.IsNull())
  {
    occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>> HAAS =
      new NCollection_HArray1<occ::handle<TCollection_HAsciiString>>(1, 1);
    HAAS->SetValue(1, new TCollection_HAsciiString("STEP AP203 file generated from STEP AP209"));
    FD->SetDescription(HAAS);
    nmodel->AddHeaderEntity(FD);
  }

  return nmodel;
}

bool StepAP209_Construct::CreateAdding203Entities(
  const occ::handle<StepBasic_ProductDefinition>& PD,
  occ::handle<StepData_StepModel>&                aModel) const
{
  occ::handle<StepData_StepModel> smodel = occ::down_cast<StepData_StepModel>(Model());
  occ::handle<StepBasic_ProductDefinitionFormation> PDF  = PD->Formation();
  occ::handle<StepBasic_Product>                    Prod = PDF->OfProduct();

  occ::handle<StepBasic_SecurityClassification> SC;
  Interface_EntityIterator                      subs = Graph().Sharings(PDF);
  for (subs.Start(); subs.More() && SC.IsNull(); subs.Next())
  {
    occ::handle<StepAP214_AppliedSecurityClassificationAssignment> ASCA =
      occ::down_cast<StepAP214_AppliedSecurityClassificationAssignment>(subs.Value());
    if (ASCA.IsNull())
      continue;
    SC = ASCA->AssignedSecurityClassification();
  }
  if (SC.IsNull())
  {

    occ::handle<StepBasic_SecurityClassificationLevel> SCL =
      new StepBasic_SecurityClassificationLevel;
    SCL->Init(new TCollection_HAsciiString("unclassified"));
    SC = new StepBasic_SecurityClassification;
    SC->Init(new TCollection_HAsciiString(""), new TCollection_HAsciiString(""), SCL);
  }
  aModel->AddWithRefs(SC);
  occ::handle<StepAP203_CcDesignSecurityClassification> DSC =
    new StepAP203_CcDesignSecurityClassification;
  occ::handle<NCollection_HArray1<StepAP203_ClassifiedItem>> HACI =
    new NCollection_HArray1<StepAP203_ClassifiedItem>(1, 1);
  StepAP203_ClassifiedItem CI;
  CI.SetValue(PDF);
  HACI->SetValue(1, CI);
  DSC->Init(SC, HACI);
  aModel->AddWithRefs(DSC);

  occ::handle<StepBasic_DateAndTime> DT;
  subs = Graph().Sharings(PD);
  for (subs.Start(); subs.More(); subs.Next())
  {
    occ::handle<StepAP214_AppliedApprovalAssignment> AAA =
      occ::down_cast<StepAP214_AppliedApprovalAssignment>(subs.Value());
    if (!AAA.IsNull())
    {
      occ::handle<NCollection_HArray1<StepAP214_ApprovalItem>> HAAI214 = AAA->Items();
      occ::handle<NCollection_HArray1<StepAP203_ApprovedItem>> HAAI =
        new NCollection_HArray1<StepAP203_ApprovedItem>(1, HAAI214->Length());
      for (int i = 1; i <= HAAI214->Length(); i++)
      {
        StepAP203_ApprovedItem AI;
        AI.SetValue(AAA->ItemsValue(i).Value());
        HAAI->SetValue(i, AI);
      }
      occ::handle<StepAP203_CcDesignApproval> DA = new StepAP203_CcDesignApproval;
      DA->Init(AAA->AssignedApproval(), HAAI);
      aModel->AddWithRefs(DA);

      Interface_EntityIterator subs2 = Graph().Sharings(AAA->AssignedApproval());
      for (subs2.Start(); subs2.More(); subs2.Next())
      {
        occ::handle<StepBasic_ApprovalDateTime> ADT =
          occ::down_cast<StepBasic_ApprovalDateTime>(subs2.Value());
        if (ADT.IsNull())
          continue;
        aModel->AddWithRefs(ADT);
        occ::handle<StepBasic_DateAndTime> DT1 =
          occ::down_cast<StepBasic_DateAndTime>(ADT->DateTime().Value());
        if (DT1.IsNull())
          continue;
        DT = DT1;
      }
    }
  }
  subs = Graph().Sharings(PDF);
  for (subs.Start(); subs.More(); subs.Next())
  {
    occ::handle<StepAP214_AppliedApprovalAssignment> AAA =
      occ::down_cast<StepAP214_AppliedApprovalAssignment>(subs.Value());
    if (!AAA.IsNull())
    {
      occ::handle<NCollection_HArray1<StepAP214_ApprovalItem>> HAAI214 = AAA->Items();
      occ::handle<NCollection_HArray1<StepAP203_ApprovedItem>> HAAI =
        new NCollection_HArray1<StepAP203_ApprovedItem>(1, HAAI214->Length());
      for (int i = 1; i <= HAAI214->Length(); i++)
      {
        StepAP203_ApprovedItem AI;
        AI.SetValue(AAA->ItemsValue(i).Value());
        HAAI->SetValue(i, AI);
      }
      occ::handle<StepAP203_CcDesignApproval> DA = new StepAP203_CcDesignApproval;
      DA->Init(AAA->AssignedApproval(), HAAI);
      aModel->AddWithRefs(DA);

      Interface_EntityIterator subs2 = Graph().Sharings(AAA->AssignedApproval());
      for (subs2.Start(); subs2.More(); subs2.Next())
      {
        occ::handle<StepBasic_ApprovalDateTime> ADT =
          occ::down_cast<StepBasic_ApprovalDateTime>(subs2.Value());
        if (ADT.IsNull())
          continue;
        aModel->AddWithRefs(ADT);
        occ::handle<StepBasic_DateAndTime> DT1 =
          occ::down_cast<StepBasic_DateAndTime>(ADT->DateTime().Value());
        if (DT1.IsNull())
          continue;
        DT = DT1;
      }
    }
  }
  subs = Graph().Sharings(SC);
  for (subs.Start(); subs.More(); subs.Next())
  {
    occ::handle<StepAP214_AppliedApprovalAssignment> AAA =
      occ::down_cast<StepAP214_AppliedApprovalAssignment>(subs.Value());
    if (!AAA.IsNull())
    {
      occ::handle<NCollection_HArray1<StepAP214_ApprovalItem>> HAAI214 = AAA->Items();
      occ::handle<NCollection_HArray1<StepAP203_ApprovedItem>> HAAI =
        new NCollection_HArray1<StepAP203_ApprovedItem>(1, HAAI214->Length());
      for (int i = 1; i <= HAAI214->Length(); i++)
      {
        StepAP203_ApprovedItem AI;
        AI.SetValue(AAA->ItemsValue(i).Value());
        HAAI->SetValue(i, AI);
      }
      occ::handle<StepAP203_CcDesignApproval> DA = new StepAP203_CcDesignApproval;
      DA->Init(AAA->AssignedApproval(), HAAI);
      aModel->AddWithRefs(DA);

      Interface_EntityIterator subs2 = Graph().Sharings(AAA->AssignedApproval());
      for (subs2.Start(); subs2.More(); subs2.Next())
      {
        occ::handle<StepBasic_ApprovalDateTime> ADT =
          occ::down_cast<StepBasic_ApprovalDateTime>(subs2.Value());
        if (ADT.IsNull())
          continue;
        aModel->AddWithRefs(ADT);
        occ::handle<StepBasic_DateAndTime> DT1 =
          occ::down_cast<StepBasic_DateAndTime>(ADT->DateTime().Value());
        if (DT1.IsNull())
          continue;
        DT = DT1;
      }
    }
  }

  if (aModel->Number(DT) > 0)
  {

    subs = Graph().Sharings(DT);
    for (subs.Start(); subs.More(); subs.Next())
    {
      occ::handle<StepAP214_AppliedDateAndTimeAssignment> ADTA =
        occ::down_cast<StepAP214_AppliedDateAndTimeAssignment>(subs.Value());
      if (ADTA.IsNull())
        continue;
      occ::handle<NCollection_HArray1<StepAP214_DateAndTimeItem>> HADTI214 = ADTA->Items();
      occ::handle<NCollection_HArray1<StepAP203_DateTimeItem>>    HADTI =
        new NCollection_HArray1<StepAP203_DateTimeItem>(1, HADTI214->Length());
      for (int i = 1; i <= HADTI214->Length(); i++)
      {
        StepAP203_DateTimeItem DTI;
        DTI.SetValue(ADTA->ItemsValue(i).Value());
        HADTI->SetValue(i, DTI);
      }
      occ::handle<StepAP203_CcDesignDateAndTimeAssignment> DDTA =
        new StepAP203_CcDesignDateAndTimeAssignment;
      DDTA->Init(DT, ADTA->Role(), HADTI);
      aModel->AddWithRefs(DDTA);
    }
  }

  subs = Graph().Sharings(Prod);
  for (subs.Start(); subs.More(); subs.Next())
  {
    occ::handle<StepAP214_AppliedPersonAndOrganizationAssignment> APOA =
      occ::down_cast<StepAP214_AppliedPersonAndOrganizationAssignment>(subs.Value());
    if (APOA.IsNull())
      continue;
    occ::handle<NCollection_HArray1<StepAP214_PersonAndOrganizationItem>> HAPOI214 = APOA->Items();
    occ::handle<NCollection_HArray1<StepAP203_PersonOrganizationItem>>    HAPOI =
      new NCollection_HArray1<StepAP203_PersonOrganizationItem>(1, HAPOI214->Length());
    for (int i = 1; i <= HAPOI214->Length(); i++)
    {
      StepAP203_PersonOrganizationItem POI;
      POI.SetValue(HAPOI214->Value(i).Value());
      HAPOI->SetValue(i, POI);
    }
    occ::handle<StepAP203_CcDesignPersonAndOrganizationAssignment> DPOA =
      new StepAP203_CcDesignPersonAndOrganizationAssignment;
    DPOA->Init(APOA->AssignedPersonAndOrganization(), APOA->Role(), HAPOI);
    aModel->AddWithRefs(DPOA);
  }
  subs = Graph().Sharings(PD);
  for (subs.Start(); subs.More(); subs.Next())
  {
    occ::handle<StepAP214_AppliedPersonAndOrganizationAssignment> APOA =
      occ::down_cast<StepAP214_AppliedPersonAndOrganizationAssignment>(subs.Value());
    if (APOA.IsNull())
      continue;
    occ::handle<NCollection_HArray1<StepAP214_PersonAndOrganizationItem>> HAPOI214 = APOA->Items();
    occ::handle<NCollection_HArray1<StepAP203_PersonOrganizationItem>>    HAPOI =
      new NCollection_HArray1<StepAP203_PersonOrganizationItem>(1, HAPOI214->Length());
    for (int i = 1; i <= HAPOI214->Length(); i++)
    {
      StepAP203_PersonOrganizationItem POI;
      POI.SetValue(HAPOI214->Value(i).Value());
      HAPOI->SetValue(i, POI);
    }
    occ::handle<StepAP203_CcDesignPersonAndOrganizationAssignment> DPOA =
      new StepAP203_CcDesignPersonAndOrganizationAssignment;
    DPOA->Init(APOA->AssignedPersonAndOrganization(), APOA->Role(), HAPOI);
    aModel->AddWithRefs(DPOA);
  }
  subs = Graph().Sharings(PDF);
  for (subs.Start(); subs.More(); subs.Next())
  {
    occ::handle<StepAP214_AppliedPersonAndOrganizationAssignment> APOA =
      occ::down_cast<StepAP214_AppliedPersonAndOrganizationAssignment>(subs.Value());
    if (APOA.IsNull())
      continue;
    occ::handle<NCollection_HArray1<StepAP214_PersonAndOrganizationItem>> HAPOI214 = APOA->Items();
    occ::handle<NCollection_HArray1<StepAP203_PersonOrganizationItem>>    HAPOI =
      new NCollection_HArray1<StepAP203_PersonOrganizationItem>(1, HAPOI214->Length());
    for (int i = 1; i <= HAPOI214->Length(); i++)
    {
      StepAP203_PersonOrganizationItem POI;
      POI.SetValue(HAPOI214->Value(i).Value());
      HAPOI->SetValue(i, POI);
    }
    occ::handle<StepAP203_CcDesignPersonAndOrganizationAssignment> DPOA =
      new StepAP203_CcDesignPersonAndOrganizationAssignment;
    DPOA->Init(APOA->AssignedPersonAndOrganization(), APOA->Role(), HAPOI);
    aModel->AddWithRefs(DPOA);
  }
  subs = Graph().Sharings(SC);
  for (subs.Start(); subs.More(); subs.Next())
  {
    occ::handle<StepAP214_AppliedPersonAndOrganizationAssignment> APOA =
      occ::down_cast<StepAP214_AppliedPersonAndOrganizationAssignment>(subs.Value());
    if (APOA.IsNull())
      continue;
    occ::handle<NCollection_HArray1<StepAP214_PersonAndOrganizationItem>> HAPOI214 = APOA->Items();
    occ::handle<NCollection_HArray1<StepAP203_PersonOrganizationItem>>    HAPOI =
      new NCollection_HArray1<StepAP203_PersonOrganizationItem>(1, HAPOI214->Length());
    for (int i = 1; i <= HAPOI214->Length(); i++)
    {
      StepAP203_PersonOrganizationItem POI;
      POI.SetValue(HAPOI214->Value(i).Value());
      HAPOI->SetValue(i, POI);
    }
    occ::handle<StepAP203_CcDesignPersonAndOrganizationAssignment> DPOA =
      new StepAP203_CcDesignPersonAndOrganizationAssignment;
    DPOA->Init(APOA->AssignedPersonAndOrganization(), APOA->Role(), HAPOI);
    aModel->AddWithRefs(DPOA);
  }

  return true;
}
