#include <APIHeaderSection_MakeHeader.hpp>
#include <gp_Pnt.hpp>
#include <Interface_EntityIterator.hpp>
#include <MoniTool_Macros.hpp>
#include <Message.hpp>
#include <StepBasic_DerivedUnit.hpp>
#include <StepBasic_DerivedUnitElement.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepBasic_MeasureValueMember.hpp>
#include <StepBasic_ProductDefinition.hpp>
#include <StepBasic_SiUnitAndLengthUnit.hpp>
#include <STEPConstruct_UnitContext.hpp>
#include <STEPConstruct_ValidationProps.hpp>
#include <StepData_Factors.hpp>
#include <StepData_StepModel.hpp>
#include <StepGeom_CartesianPoint.hpp>
#include <StepGeom_GeometricRepresentationContextAndGlobalUnitAssignedContext.hpp>
#include <StepGeom_GeometricRepresentationItem.hpp>
#include <StepGeom_GeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx.hpp>
#include <StepRepr_GlobalUnitAssignedContext.hpp>
#include <StepRepr_MeasureRepresentationItem.hpp>
#include <StepRepr_NextAssemblyUsageOccurrence.hpp>
#include <StepRepr_ProductDefinitionShape.hpp>
#include <StepRepr_PropertyDefinition.hpp>
#include <StepRepr_RepresentationContext.hpp>
#include <StepRepr_RepresentationItem.hpp>
#include <StepRepr_ShapeAspect.hpp>
#include <StepRepr_ShapeRepresentationRelationship.hpp>
#include <StepShape_ShapeDefinitionRepresentation.hpp>
#include <StepShape_ShapeRepresentation.hpp>
#include <TCollection_HAsciiString.hpp>
#include <Transfer_Binder.hpp>
#include <Transfer_SimpleBinderOfTransient.hpp>
#include <TransferBRep.hpp>
#include <TransferBRep_ShapeMapper.hpp>
#include <XSControl_TransferReader.hpp>
#include <XSControl_TransferWriter.hpp>
#include <XSControl_WorkSession.hpp>

STEPConstruct_ValidationProps::STEPConstruct_ValidationProps() = default;

STEPConstruct_ValidationProps::STEPConstruct_ValidationProps(
  const occ::handle<XSControl_WorkSession>& WS)
    : STEPConstruct_Tool(WS)
{
}

bool STEPConstruct_ValidationProps::Init(const occ::handle<XSControl_WorkSession>& WS)
{
  return SetWS(WS);
}

static occ::handle<Transfer_SimpleBinderOfTransient> TransientResult(
  const occ::handle<Standard_Transient>& res)
{
  occ::handle<Transfer_SimpleBinderOfTransient> binder;
  if (res.IsNull())
    return binder;
  binder = new Transfer_SimpleBinderOfTransient;
  binder->SetResult(res);
  return binder;
}

bool STEPConstruct_ValidationProps::FindTarget(const TopoDS_Shape&                          Shape,
                                               StepRepr_CharacterizedDefinition&            target,
                                               occ::handle<StepRepr_RepresentationContext>& Context,
                                               const bool instance)
{

  occ::handle<TransferBRep_ShapeMapper> mapper = TransferBRep::ShapeMapper(FinderProcess(), Shape);
  occ::handle<Transfer_Binder>          binder = FinderProcess()->Find(mapper);

  if (instance)
  {
  }

  else if (Shape.ShapeType() == TopAbs_COMPOUND)
  {
    occ::handle<StepBasic_ProductDefinition> ProdDef;
    if (FinderProcess()->FindTypedTransient(mapper,
                                            STANDARD_TYPE(StepBasic_ProductDefinition),
                                            ProdDef))
    {
      occ::handle<StepRepr_ProductDefinitionShape> PDS;
      Interface_EntityIterator                     subs1 = Graph().Sharings(ProdDef);
      for (subs1.Start(); PDS.IsNull() && subs1.More(); subs1.Next())
      {
        PDS = occ::down_cast<StepRepr_ProductDefinitionShape>(subs1.Value());
      }
      target.SetValue(PDS);
#ifdef OCCT_DEBUG

#endif
    }
    else
    {
#ifdef OCCT_DEBUG
      std::cout << "COMPOUND: ProdDef NOT found" << std::endl;
#endif
      occ::handle<StepShape_ShapeRepresentation> SR;
      if (FinderProcess()->FindTypedTransient(mapper,
                                              STANDARD_TYPE(StepShape_ShapeRepresentation),
                                              SR))
      {
        occ::handle<StepRepr_ProductDefinitionShape> PDS;
        Interface_EntityIterator                     subs1 = Graph().Sharings(SR);
        for (subs1.Start(); PDS.IsNull() && subs1.More(); subs1.Next())
        {
          occ::handle<StepShape_ShapeDefinitionRepresentation> SDR =
            occ::down_cast<StepShape_ShapeDefinitionRepresentation>(subs1.Value());
          if (SDR.IsNull())
            continue;
          PDS =
            occ::down_cast<StepRepr_ProductDefinitionShape>(SDR->Definition().PropertyDefinition());
        }
        if (PDS.IsNull())
        {
          subs1 = Graph().Sharings(SR);
          for (subs1.Start(); PDS.IsNull() && subs1.More(); subs1.Next())
          {
            occ::handle<StepRepr_RepresentationRelationship> RR =
              occ::down_cast<StepRepr_RepresentationRelationship>(subs1.Value());
            if (RR.IsNull())
              continue;
            occ::handle<StepShape_ShapeRepresentation> SR1;
            if (RR->Rep1() == SR)
              SR1 = occ::down_cast<StepShape_ShapeRepresentation>(RR->Rep2());
            else
              SR1 = occ::down_cast<StepShape_ShapeRepresentation>(RR->Rep1());
            if (!SR1.IsNull())
            {
              Interface_EntityIterator subs2 = Graph().Sharings(SR1);
              for (subs2.Start(); PDS.IsNull() && subs2.More(); subs2.Next())
              {
                occ::handle<StepShape_ShapeDefinitionRepresentation> SDR =
                  occ::down_cast<StepShape_ShapeDefinitionRepresentation>(subs2.Value());
                if (SDR.IsNull())
                  continue;
                PDS = occ::down_cast<StepRepr_ProductDefinitionShape>(
                  SDR->Definition().PropertyDefinition());
              }
            }
          }
        }
        if (!PDS.IsNull())
        {
          target.SetValue(PDS);
          Context = SR->ContextOfItems();
        }
      }
    }
  }

  else
  {
    occ::handle<StepGeom_GeometricRepresentationItem> item;
    if (FinderProcess()->FindTypedTransient(mapper,
                                            STANDARD_TYPE(StepGeom_GeometricRepresentationItem),
                                            item))
    {
#ifdef OCCT_DEBUG

#endif

      occ::handle<StepRepr_ProductDefinitionShape> PDS;
      Interface_EntityIterator                     subs = Graph().Sharings(item);
      for (subs.Start(); PDS.IsNull() && subs.More(); subs.Next())
      {
#ifdef OCCT_DEBUG

#endif
        if (!subs.Value()->IsKind(STANDARD_TYPE(StepShape_ShapeRepresentation)))
          continue;
        occ::handle<StepShape_ShapeRepresentation> sr =
          occ::down_cast<StepShape_ShapeRepresentation>(subs.Value());
        Context                       = sr->ContextOfItems();
        Interface_EntityIterator sub2 = Graph().Sharings(subs.Value());
        for (sub2.Start(); sub2.More(); sub2.Next())
        {
          if (!sub2.Value()->IsKind(STANDARD_TYPE(StepShape_ShapeDefinitionRepresentation)))
            continue;
          occ::handle<StepShape_ShapeDefinitionRepresentation> sdr =
            occ::down_cast<StepShape_ShapeDefinitionRepresentation>(sub2.Value());
          PDS =
            occ::down_cast<StepRepr_ProductDefinitionShape>(sdr->Definition().PropertyDefinition());
        }
      }
      if (!PDS.IsNull())
      {

        occ::handle<StepRepr_ShapeAspect> aspect;
        occ::handle<Transfer_Binder>      bbb = binder;
        while (!bbb.IsNull())
        {
          occ::handle<Transfer_SimpleBinderOfTransient> bx =
            occ::down_cast<Transfer_SimpleBinderOfTransient>(bbb);
          if (!bx.IsNull())
          {
            occ::handle<StepRepr_ShapeAspect> asp =
              occ::down_cast<StepRepr_ShapeAspect>(bx->Result());
            if (!asp.IsNull() && asp->OfShape() == PDS)
            {
              aspect = asp;
              break;
            }
          }
          bbb = bbb->NextResult();
        }
        if (aspect.IsNull())
        {

#ifdef OCCT_DEBUG
          std::cout << Shape.TShape()->DynamicType()->Name() << ": SHAPE_ASPECT NOT found, creating"
                    << std::endl;
#endif

          occ::handle<TCollection_HAsciiString> AspectName  = new TCollection_HAsciiString("");
          occ::handle<TCollection_HAsciiString> AspectDescr = new TCollection_HAsciiString("");
          aspect                                            = new StepRepr_ShapeAspect;
          aspect->Init(AspectName, AspectDescr, PDS, StepData_LFalse);

          StepRepr_CharacterizedDefinition SA;
          SA.SetValue(aspect);

          occ::handle<TCollection_HAsciiString> PropDefName =
            new TCollection_HAsciiString("shape with specific properties");
          occ::handle<TCollection_HAsciiString> PropDefDescr =
            new TCollection_HAsciiString("properties for subshape");
          occ::handle<StepRepr_PropertyDefinition> propdef = new StepRepr_PropertyDefinition;
          propdef->Init(PropDefName, true, PropDefDescr, SA);

          occ::handle<TCollection_HAsciiString>      SRName = new TCollection_HAsciiString("");
          occ::handle<StepShape_ShapeRepresentation> SR     = new StepShape_ShapeRepresentation;
          occ::handle<NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>> SRItems =
            new NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>(1, 1);
          SRItems->SetValue(1, item);
          SR->Init(SRName, SRItems, Context);

          occ::handle<StepShape_ShapeDefinitionRepresentation> SDR =
            new StepShape_ShapeDefinitionRepresentation;
          StepRepr_RepresentedDefinition RD;
          RD.SetValue(propdef);
          SDR->Init(RD, SR);

          binder->AddResult(TransientResult(aspect));

          Model()->AddWithRefs(SDR);
        }

        else
        {
#ifdef OCCT_DEBUG
          std::cout << Shape.TShape()->DynamicType()->Name() << ": SHAPE_ASPECT found" << std::endl;
#endif
          occ::handle<StepRepr_ProductDefinitionShape> aPDS  = aspect->OfShape();
          Interface_EntityIterator                     asubs = Graph().Sharings(aPDS);
          for (asubs.Start(); Context.IsNull() && asubs.More(); asubs.Next())
          {
            if (!asubs.Value()->IsKind(STANDARD_TYPE(StepShape_ShapeDefinitionRepresentation)))
              continue;
            occ::handle<StepShape_ShapeDefinitionRepresentation> sdr =
              occ::down_cast<StepShape_ShapeDefinitionRepresentation>(asubs.Value());
            Context = sdr->UsedRepresentation()->ContextOfItems();
          }
        }

        if (!aspect.IsNull())
          target.SetValue(aspect);
      }
#ifdef OCCT_DEBUG
      else
        std::cout << Shape.TShape()->DynamicType()->Name()
                  << ": PDS NOT found, fail to create SHAPE_ASPECT" << std::endl;
#endif
    }
#ifdef OCCT_DEBUG
    else
      std::cout << Shape.TShape()->DynamicType()->Name() << ": GeomRepItem NOT found" << std::endl;
#endif
  }

  return !target.IsNull();
}

bool STEPConstruct_ValidationProps::AddProp(
  const StepRepr_CharacterizedDefinition&            target,
  const occ::handle<StepRepr_RepresentationContext>& Context,
  const occ::handle<StepRepr_RepresentationItem>&    Prop,
  const char*                                        Descr)
{

  occ::handle<TCollection_HAsciiString> PropDefName =
    new TCollection_HAsciiString("geometric validation property");
  occ::handle<TCollection_HAsciiString>    PropDefDescr = new TCollection_HAsciiString(Descr);
  occ::handle<StepRepr_PropertyDefinition> propdef      = new StepRepr_PropertyDefinition;
  propdef->Init(PropDefName, true, PropDefDescr, target);

  occ::handle<TCollection_HAsciiString> SRName = new TCollection_HAsciiString(Descr);
  occ::handle<StepRepr_Representation>  rep    = new StepRepr_Representation;
  occ::handle<NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>> SRItems =
    new NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>(1, 1);
  SRItems->SetValue(1, Prop);
  rep->Init(SRName, SRItems, Context);

  occ::handle<StepRepr_PropertyDefinitionRepresentation> PrDR =
    new StepRepr_PropertyDefinitionRepresentation;
  StepRepr_RepresentedDefinition RD;
  RD.SetValue(propdef);
  PrDR->Init(RD, rep);

  Model()->AddWithRefs(PrDR);

  occ::handle<StepData_StepModel> aStepModel = occ::down_cast<StepData_StepModel>(Model());

  if (aStepModel->InternalParameters.WriteSchema == 3)
  {
    APIHeaderSection_MakeHeader           mkHdr(aStepModel);
    occ::handle<TCollection_HAsciiString> subSchema =
      new TCollection_HAsciiString("GEOMETRIC_VALIDATION_PROPERTIES_MIM");
    mkHdr.AddSchemaIdentifier(subSchema);
  }

  return true;
}

bool STEPConstruct_ValidationProps::AddProp(const TopoDS_Shape&                             Shape,
                                            const occ::handle<StepRepr_RepresentationItem>& Prop,
                                            const char*                                     Descr,
                                            const bool instance)
{
  StepRepr_CharacterizedDefinition            target;
  occ::handle<StepRepr_RepresentationContext> Context;
  if (!FindTarget(Shape, target, Context, instance))
    return false;
  return AddProp(target, Context, Prop, Descr);
}

bool STEPConstruct_ValidationProps::AddVolume(const TopoDS_Shape& Shape, const double Vol)
{
  occ::handle<StepBasic_MeasureValueMember> Val = new StepBasic_MeasureValueMember;
  Val->SetReal(Vol);

  Val->SetName("VOLUME_MEASURE");

  if (volUnit.DerivedUnit().IsNull())
  {
    occ::handle<StepBasic_SiUnitAndLengthUnit> MM = new StepBasic_SiUnitAndLengthUnit;
    MM->Init(true, StepBasic_spMilli, StepBasic_sunMetre);

    occ::handle<StepBasic_DerivedUnitElement> DUE = new StepBasic_DerivedUnitElement;
    DUE->Init(MM, 3.);

    occ::handle<NCollection_HArray1<occ::handle<StepBasic_DerivedUnitElement>>> DUElems =
      new NCollection_HArray1<occ::handle<StepBasic_DerivedUnitElement>>(1, 1);
    DUElems->SetValue(1, DUE);

    occ::handle<StepBasic_DerivedUnit> DU = new StepBasic_DerivedUnit;
    DU->Init(DUElems);

    volUnit.SetValue(DU);
  }

  occ::handle<TCollection_HAsciiString> MRIName = new TCollection_HAsciiString("volume measure");
  occ::handle<StepRepr_MeasureRepresentationItem> MRI = new StepRepr_MeasureRepresentationItem;
  MRI->Init(MRIName, Val, volUnit);

  return AddProp(Shape, MRI, "volume");
}

bool STEPConstruct_ValidationProps::AddArea(const TopoDS_Shape& Shape, const double Area)
{
  occ::handle<StepBasic_MeasureValueMember> Val = new StepBasic_MeasureValueMember;
  Val->SetReal(Area);

  Val->SetName("AREA_MEASURE");

  if (areaUnit.DerivedUnit().IsNull())
  {
    occ::handle<StepBasic_SiUnitAndLengthUnit> MM = new StepBasic_SiUnitAndLengthUnit;
    MM->Init(true, StepBasic_spMilli, StepBasic_sunMetre);

    occ::handle<StepBasic_DerivedUnitElement> DUE = new StepBasic_DerivedUnitElement;
    DUE->Init(MM, 2.);

    occ::handle<NCollection_HArray1<occ::handle<StepBasic_DerivedUnitElement>>> DUElems =
      new NCollection_HArray1<occ::handle<StepBasic_DerivedUnitElement>>(1, 1);
    DUElems->SetValue(1, DUE);

    occ::handle<StepBasic_DerivedUnit> DU = new StepBasic_DerivedUnit;
    DU->Init(DUElems);

    areaUnit.SetValue(DU);
  }

  occ::handle<TCollection_HAsciiString> MRIName =
    new TCollection_HAsciiString("surface area measure");
  occ::handle<StepRepr_MeasureRepresentationItem> MRI = new StepRepr_MeasureRepresentationItem;
  MRI->Init(MRIName, Val, areaUnit);

  return AddProp(Shape, MRI, "surface area");
}

bool STEPConstruct_ValidationProps::AddCentroid(const TopoDS_Shape& Shape,
                                                const gp_Pnt&       Pnt,
                                                const bool          instance)
{
  occ::handle<TCollection_HAsciiString> CPName = new TCollection_HAsciiString("centre point");
  occ::handle<StepGeom_CartesianPoint>  CP     = new StepGeom_CartesianPoint;
  CP->Init3D(CPName, Pnt.X(), Pnt.Y(), Pnt.Z());

  return AddProp(Shape, CP, "centroid", instance);
}

bool STEPConstruct_ValidationProps::LoadProps(
  NCollection_Sequence<occ::handle<Standard_Transient>>& seq) const
{

  int                        nb   = Model()->NbEntities();
  occ::handle<Standard_Type> tPDR = STANDARD_TYPE(StepRepr_PropertyDefinitionRepresentation);
  for (int i = 1; i <= nb; i++)
  {
    occ::handle<Standard_Transient> enti = Model()->Value(i);
    if (!enti->IsKind(tPDR))
      continue;

    occ::handle<StepRepr_PropertyDefinitionRepresentation> PDR =
      occ::down_cast<StepRepr_PropertyDefinitionRepresentation>(enti);

    occ::handle<StepRepr_PropertyDefinition> PD = PDR->Definition().PropertyDefinition();
    if (!PD.IsNull() && !PD->Name().IsNull())
    {

      TCollection_AsciiString aName = PD->Name()->String();
      aName.ChangeAll('_', ' ', false);
      aName.LowerCase();
      if (aName != "geometric validation property")
        continue;
    }

    seq.Append(PDR);
  }
  return seq.Length() > 0;
}

occ::handle<StepBasic_ProductDefinition> STEPConstruct_ValidationProps::GetPropPD(
  const occ::handle<StepRepr_PropertyDefinition>& PD) const
{
  StepRepr_CharacterizedDefinition CD = PD->Definition();

  occ::handle<StepBasic_ProductDefinition> ProdDef;
  occ::handle<StepRepr_PropertyDefinition> PDS = CD.ProductDefinitionShape();
  if (PDS.IsNull())
  {
    occ::handle<StepRepr_ShapeAspect> SA = CD.ShapeAspect();
    if (SA.IsNull())
    {
#ifdef OCCT_DEBUG
      Message_Messenger::StreamBuffer sout = Message::SendInfo();
      sout << "Error: Cannot find target entity (SA) for geometric_validation_property ";
      Model()->PrintLabel(PD, sout);
      sout << std::endl;
#endif
      return ProdDef;
    }
    Interface_EntityIterator subs = Graph().Sharings(SA);
    for (subs.Start(); subs.More(); subs.Next())
    {
      PDS = occ::down_cast<StepRepr_PropertyDefinition>(subs.Value());
      if (PDS.IsNull())
        return ProdDef;
      Interface_EntityIterator subs1 = Graph().Shareds(PDS);
      for (subs1.Start(); ProdDef.IsNull() && subs1.More(); subs1.Next())
      {
        ProdDef = occ::down_cast<StepBasic_ProductDefinition>(subs1.Value());
      }
    }
  }
  else
  {
    Interface_EntityIterator subs = Graph().Shareds(PDS);
    for (subs.Start(); ProdDef.IsNull() && subs.More(); subs.Next())
    {
      ProdDef = occ::down_cast<StepBasic_ProductDefinition>(subs.Value());
    }
  }
#ifdef OCCT_DEBUG
  if (ProdDef.IsNull())
  {
    Message_Messenger::StreamBuffer sout = Message::SendInfo();
    sout << "Error: Cannot find target entity (SDR) for geometric_validation_property ";
    Model()->PrintLabel(PD, sout);
    sout << std::endl;
  }
#endif
  return ProdDef;
}

occ::handle<StepRepr_NextAssemblyUsageOccurrence> STEPConstruct_ValidationProps::GetPropNAUO(
  const occ::handle<StepRepr_PropertyDefinition>& PD) const
{
  StepRepr_CharacterizedDefinition CD = PD->Definition();

  occ::handle<StepRepr_NextAssemblyUsageOccurrence> NAUO;
  occ::handle<StepRepr_PropertyDefinition>          PDS = CD.ProductDefinitionShape();
  if (PDS.IsNull())
    return NAUO;
  Interface_EntityIterator subs = Graph().Shareds(PDS);
  for (subs.Start(); NAUO.IsNull() && subs.More(); subs.Next())
  {
    NAUO = occ::down_cast<StepRepr_NextAssemblyUsageOccurrence>(subs.Value());
  }
  return NAUO;
}

TopoDS_Shape STEPConstruct_ValidationProps::GetPropShape(
  const occ::handle<StepBasic_ProductDefinition>& ProdDef) const
{

  TopoDS_Shape                 S;
  occ::handle<Transfer_Binder> binder = TransientProcess()->Find(ProdDef);
  if (!binder.IsNull() && binder->HasResult())
  {
    S = TransferBRep::ShapeResult(TransientProcess(), binder);
  }

#ifdef OCCT_DEBUG
  if (S.IsNull())
  {
    Message_Messenger::StreamBuffer sout = Message::SendInfo();
    sout << "Warning: Entity ";
    Model()->PrintLabel(ProdDef, sout);
    sout << " is not mapped to shape" << std::endl;
  }
#endif
  return S;
}

TopoDS_Shape STEPConstruct_ValidationProps::GetPropShape(
  const occ::handle<StepRepr_PropertyDefinition>& PD) const
{
  occ::handle<StepBasic_ProductDefinition> ProdDef = GetPropPD(PD);
  TopoDS_Shape                             S;
  if (!ProdDef.IsNull())
    S = GetPropShape(ProdDef);
  return S;
}

bool STEPConstruct_ValidationProps::GetPropReal(
  const occ::handle<StepRepr_RepresentationItem>& item,
  double&                                         Val,
  bool&                                           isArea,
  const StepData_Factors&                         theLocalFactors) const
{

  if (!item->IsKind(STANDARD_TYPE(StepRepr_MeasureRepresentationItem)))
    return false;

  occ::handle<StepRepr_MeasureRepresentationItem> mri =
    occ::down_cast<StepRepr_MeasureRepresentationItem>(item);

  occ::handle<StepBasic_MeasureWithUnit> M    = mri->Measure();
  TCollection_AsciiString                Name = M->ValueComponentMember()->Name();
  StepBasic_Unit                         Unit = M->UnitComponent();

  double                             scale = 1.;
  occ::handle<StepBasic_DerivedUnit> DU    = Unit.DerivedUnit();
  if (!DU.IsNull())
  {
    for (int ind = 1; ind <= DU->NbElements(); ind++)
    {
      occ::handle<StepBasic_DerivedUnitElement> DUE = DU->ElementsValue(ind);
      double                                    exp = DUE->Exponent();
      occ::handle<StepBasic_NamedUnit>          NU  = DUE->Unit();
      STEPConstruct_UnitContext                 unit;
      unit.ComputeFactors(NU, theLocalFactors);
      if (unit.LengthDone())
      {
        double lengthFactor = unit.LengthFactor();
        scale *= pow(lengthFactor, exp);
      }
    }
  }
  else
  {
    occ::handle<StepBasic_NamedUnit> NU = Unit.NamedUnit();
    if (!NU.IsNull())
    {
      STEPConstruct_UnitContext unit;
      unit.ComputeFactors(NU, theLocalFactors);
      if (unit.AreaDone())
        scale = unit.AreaFactor();
      if (unit.VolumeDone())
        scale = unit.VolumeFactor();
    }
  }

  Val = M->ValueComponent() * scale;

  if (Name == "AREA_MEASURE")
    isArea = true;
  else if (Name == "VOLUME_MEASURE")
    isArea = false;
  else
  {
#ifdef OCCT_DEBUG
    std::cout << "Warning: Measure " << Model()->StringLabel(M)->String()
              << " is neither area not volume" << std::endl;
#endif
    return false;
  }
  return true;
}

bool STEPConstruct_ValidationProps::GetPropPnt(
  const occ::handle<StepRepr_RepresentationItem>&    item,
  const occ::handle<StepRepr_RepresentationContext>& Context,
  gp_Pnt&                                            Pnt,
  const StepData_Factors&                            theLocalFactors) const
{

  if (!item->IsKind(STANDARD_TYPE(StepGeom_CartesianPoint)))
    return false;

  occ::handle<StepGeom_CartesianPoint> P = occ::down_cast<StepGeom_CartesianPoint>(item);
  if (P.IsNull() || P->NbCoordinates() != 3)
  {
#ifdef OCCT_DEBUG
    std::cout << "Warning: Point " << Model()->StringLabel(P)->String()
              << " is not valid for centroid" << std::endl;
#endif
    return false;
  }

  gp_Pnt pos(P->CoordinatesValue(1), P->CoordinatesValue(2), P->CoordinatesValue(3));

  if (!Context.IsNull())
  {
    occ::handle<StepRepr_GlobalUnitAssignedContext> theGUAC;
    if (Context->IsKind(
          STANDARD_TYPE(StepGeom_GeometricRepresentationContextAndGlobalUnitAssignedContext)))
    {
      DeclareAndCast(StepGeom_GeometricRepresentationContextAndGlobalUnitAssignedContext,
                     theGRCAGAUC,
                     Context);
      theGUAC = theGRCAGAUC->GlobalUnitAssignedContext();
    }
    else if (Context->IsKind(
               STANDARD_TYPE(StepGeom_GeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx)))
    {
      DeclareAndCast(StepGeom_GeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx,
                     theGRCAGAUC,
                     Context);
      theGUAC = theGRCAGAUC->GlobalUnitAssignedContext();
    }
    if (!theGUAC.IsNull())
    {
      STEPConstruct_UnitContext UnitTool;
      UnitTool.ComputeFactors(theGUAC, theLocalFactors);
      gp_Pnt zero(0, 0, 0);
      pos.Scale(zero, UnitTool.LengthFactor());
    }
  }
  Pnt = pos;

  return true;
}

void STEPConstruct_ValidationProps::SetAssemblyShape(const TopoDS_Shape& shape)
{
  occ::handle<TransferBRep_ShapeMapper> mapper = TransferBRep::ShapeMapper(FinderProcess(), shape);
  FinderProcess()->FindTypedTransient(mapper,
                                      STANDARD_TYPE(StepBasic_ProductDefinition),
                                      myAssemblyPD);
}
