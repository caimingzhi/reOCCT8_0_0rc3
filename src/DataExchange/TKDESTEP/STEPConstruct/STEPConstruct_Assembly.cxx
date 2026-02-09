

#include <Interface_EntityIterator.hpp>
#include <Interface_Graph.hpp>
#include <Interface_InterfaceModel.hpp>
#include <Standard_Transient.hpp>
#include <StepBasic_ProductDefinition.hpp>
#include <STEPConstruct_Assembly.hpp>
#include <StepGeom_Axis2Placement3d.hpp>
#include <StepGeom_CartesianTransformationOperator3d.hpp>
#include <StepRepr_ItemDefinedTransformation.hpp>
#include <StepRepr_NextAssemblyUsageOccurrence.hpp>
#include <StepRepr_ProductDefinitionShape.hpp>
#include <StepRepr_ShapeRepresentationRelationshipWithTransformation.hpp>
#include <StepRepr_Transformation.hpp>
#include <StepShape_ContextDependentShapeRepresentation.hpp>
#include <StepShape_ShapeDefinitionRepresentation.hpp>
#include <StepShape_ShapeRepresentation.hpp>
#include <TCollection_HAsciiString.hpp>

STEPConstruct_Assembly::STEPConstruct_Assembly() = default;

void STEPConstruct_Assembly::Init(const occ::handle<StepShape_ShapeDefinitionRepresentation>& aSDR,
                                  const occ::handle<StepShape_ShapeDefinitionRepresentation>& SDR0,
                                  const occ::handle<StepGeom_Axis2Placement3d>&               Ax0,
                                  const occ::handle<StepGeom_Axis2Placement3d>&               AxLoc)
{
  thesdr  = aSDR;
  thesdr0 = SDR0;
  thesr   = occ::down_cast<StepShape_ShapeRepresentation>(aSDR->UsedRepresentation());
  thesr0  = occ::down_cast<StepShape_ShapeRepresentation>(SDR0->UsedRepresentation());
  theval.Nullify();
  theax0            = Ax0;
  theloc            = AxLoc;
  myIsCartesianTrsf = false;
}

void STEPConstruct_Assembly::Init(
  const occ::handle<StepShape_ShapeDefinitionRepresentation>&    aSDR,
  const occ::handle<StepShape_ShapeDefinitionRepresentation>&    SDR0,
  const occ::handle<StepGeom_CartesianTransformationOperator3d>& theTrsfOp)
{
  thesdr  = aSDR;
  thesdr0 = SDR0;
  thesr   = occ::down_cast<StepShape_ShapeRepresentation>(aSDR->UsedRepresentation());
  thesr0  = occ::down_cast<StepShape_ShapeRepresentation>(SDR0->UsedRepresentation());
  theval.Nullify();
  myTrsfOp          = theTrsfOp;
  myIsCartesianTrsf = true;
}

void STEPConstruct_Assembly::MakeRelationship()
{

  occ::handle<StepBasic_ProductDefinition> PDED =
    thesdr->Definition().PropertyDefinition()->Definition().ProductDefinition();
  occ::handle<StepBasic_ProductDefinition> PDING =
    thesdr0->Definition().PropertyDefinition()->Definition().ProductDefinition();

  occ::handle<StepRepr_NextAssemblyUsageOccurrence> NAUO = new StepRepr_NextAssemblyUsageOccurrence;
  static int                                        id   = 0;
  occ::handle<TCollection_HAsciiString>             ocid = new TCollection_HAsciiString(++id);
  occ::handle<TCollection_HAsciiString>             ocname = new TCollection_HAsciiString("");
  occ::handle<TCollection_HAsciiString>             ocdesc = new TCollection_HAsciiString("");
  occ::handle<TCollection_HAsciiString>             refdes;
  NAUO->Init(ocid, ocname, true, ocdesc, PDING, PDED, false, refdes);

  occ::handle<StepRepr_ProductDefinitionShape> PDS     = new StepRepr_ProductDefinitionShape;
  occ::handle<TCollection_HAsciiString>        pdsname = new TCollection_HAsciiString("Placement");
  occ::handle<TCollection_HAsciiString>        pdsdesc =
    new TCollection_HAsciiString("Placement of an item");
  StepRepr_CharacterizedDefinition CD;
  CD.SetValue(NAUO);
  PDS->Init(pdsname, true, pdsdesc, CD);

  occ::handle<Standard_Transient> aTrsfItem;
  if (!myIsCartesianTrsf)
  {
    occ::handle<StepRepr_ItemDefinedTransformation> ItemDef =
      new StepRepr_ItemDefinedTransformation;
    occ::handle<TCollection_HAsciiString> idname = new TCollection_HAsciiString("");
    occ::handle<TCollection_HAsciiString> idescr = new TCollection_HAsciiString("");
    ItemDef->Init(idname, idescr, theax0, theloc);
    aTrsfItem = ItemDef;
  }
  else
  {
    aTrsfItem = myTrsfOp;
  }

  occ::handle<StepRepr_ShapeRepresentationRelationshipWithTransformation> SRRWT =
    new StepRepr_ShapeRepresentationRelationshipWithTransformation;
  occ::handle<TCollection_HAsciiString> stname = new TCollection_HAsciiString("");
  occ::handle<TCollection_HAsciiString> stescr = new TCollection_HAsciiString("");
  StepRepr_Transformation               StepTrans;
  StepTrans.SetValue(aTrsfItem);
  SRRWT->Init(stname, stescr, thesr, thesr0, StepTrans);

  occ::handle<StepShape_ContextDependentShapeRepresentation> CDSR =
    new StepShape_ContextDependentShapeRepresentation;
  CDSR->Init(SRRWT, PDS);

  theval = CDSR;
}

occ::handle<Standard_Transient> STEPConstruct_Assembly::ItemValue() const
{
  if (theval.IsNull())
    return occ::handle<Standard_Transient>(thesr);
  return theval;
}

occ::handle<StepGeom_Axis2Placement3d> STEPConstruct_Assembly::ItemLocation() const
{
  return theloc;
}

occ::handle<StepRepr_NextAssemblyUsageOccurrence> STEPConstruct_Assembly::GetNAUO() const
{
  occ::handle<StepShape_ContextDependentShapeRepresentation> CDSR =
    occ::down_cast<StepShape_ContextDependentShapeRepresentation>(ItemValue());
  if (!CDSR.IsNull())
  {
    occ::handle<StepBasic_ProductDefinitionRelationship> PDR =
      CDSR->RepresentedProductRelation()->Definition().ProductDefinitionRelationship();
    return occ::down_cast<StepRepr_NextAssemblyUsageOccurrence>(PDR);
  }
  return nullptr;
}

bool STEPConstruct_Assembly::CheckSRRReversesNAUO(
  const Interface_Graph&                                            theGraph,
  const occ::handle<StepShape_ContextDependentShapeRepresentation>& CDSR)
{
  occ::handle<StepRepr_NextAssemblyUsageOccurrence> nauo =
    occ::down_cast<StepRepr_NextAssemblyUsageOccurrence>(
      CDSR->RepresentedProductRelation()->Definition().ProductDefinitionRelationship());
  if (nauo.IsNull())
  {
#ifdef OCCT_DEBUG
    std::cout << "Warning: No NAUO found in CDSR !" << std::endl;
#endif
    return false;
  }

  occ::handle<StepBasic_ProductDefinition> pd1, pd2;
  occ::handle<StepRepr_Representation>     rep1 = CDSR->RepresentationRelation()->Rep1();
  occ::handle<StepRepr_Representation>     rep2 = CDSR->RepresentationRelation()->Rep2();
  if (rep1.IsNull() || rep2.IsNull())
    return false;

  occ::handle<Standard_Type> tSDR   = STANDARD_TYPE(StepShape_ShapeDefinitionRepresentation);
  Interface_EntityIterator   anIter = theGraph.Sharings(rep1);
  for (; anIter.More() && pd1.IsNull(); anIter.Next())
  {
    const occ::handle<Standard_Transient>& enti = anIter.Value();
    if (enti->DynamicType() == tSDR)
    {
      occ::handle<StepShape_ShapeDefinitionRepresentation> SDR =
        occ::down_cast<StepShape_ShapeDefinitionRepresentation>(enti);
      if (SDR->UsedRepresentation() == rep1)
        pd1 = SDR->Definition().PropertyDefinition()->Definition().ProductDefinition();
    }
  }

  anIter = theGraph.Sharings(rep2);
  for (; anIter.More() && pd2.IsNull(); anIter.Next())
  {
    const occ::handle<Standard_Transient>& enti = anIter.Value();
    if (enti->DynamicType() == tSDR)
    {
      occ::handle<StepShape_ShapeDefinitionRepresentation> SDR =
        occ::down_cast<StepShape_ShapeDefinitionRepresentation>(enti);
      if (SDR->UsedRepresentation() == rep2)
        pd2 = SDR->Definition().PropertyDefinition()->Definition().ProductDefinition();
    }
  }

  if (pd1 == nauo->RelatedProductDefinition() && pd2 == nauo->RelatingProductDefinition())
    return false;

  if (pd2 == nauo->RelatedProductDefinition() && pd1 == nauo->RelatingProductDefinition())
  {
    return true;
  }

#ifdef OCCT_DEBUG
  std::cout << "Warning: SRR and NAUO are incompatible" << std::endl;

#endif

  if (pd2 == nauo->RelatedProductDefinition() || pd1 == nauo->RelatingProductDefinition())
  {
    return true;
  }

  return false;
}
