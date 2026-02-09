#include <APIHeaderSection_MakeHeader.hpp>
#include <Interface_EntityIterator.hpp>
#include <Quantity_Color.hpp>
#include <StepBasic_MeasureValueMember.hpp>
#include <STEPConstruct.hpp>
#include <STEPConstruct_Styles.hpp>
#include <StepData_StepModel.hpp>
#include <StepGeom_GeometricRepresentationItem.hpp>
#include <StepRepr_ItemDefinedTransformation.hpp>
#include <StepRepr_ProductDefinitionShape.hpp>
#include <StepRepr_RepresentationContext.hpp>
#include <StepRepr_RepresentationItem.hpp>
#include <StepRepr_RepresentationRelationshipWithTransformation.hpp>
#include <StepRepr_ShapeRepresentationRelationship.hpp>
#include <StepRepr_Transformation.hpp>
#include <StepShape_ContextDependentShapeRepresentation.hpp>
#include <StepShape_ShapeDefinitionRepresentation.hpp>
#include <StepShape_ShapeRepresentation.hpp>
#include <StepVisual_ColourRgb.hpp>
#include <StepVisual_CurveStyle.hpp>
#include <StepVisual_DraughtingModel.hpp>
#include <StepVisual_DraughtingPreDefinedColour.hpp>
#include <StepVisual_DraughtingPreDefinedCurveFont.hpp>
#include <StepVisual_FillAreaStyle.hpp>
#include <StepVisual_FillAreaStyleColour.hpp>
#include <StepVisual_FillStyleSelect.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepVisual_Invisibility.hpp>
#include <StepVisual_InvisibleItem.hpp>
#include <StepVisual_MechanicalDesignGeometricPresentationRepresentation.hpp>
#include <StepVisual_OverRidingStyledItem.hpp>
#include <StepVisual_PreDefinedColour.hpp>
#include <StepVisual_PreDefinedItem.hpp>
#include <StepVisual_PresentationStyleAssignment.hpp>
#include <StepVisual_PresentationStyleByContext.hpp>
#include <StepVisual_PresentationStyleSelect.hpp>
#include <StepVisual_StyledItem.hpp>
#include <StepVisual_SurfaceSideStyle.hpp>
#include <StepVisual_SurfaceStyleBoundary.hpp>
#include <StepVisual_SurfaceStyleElementSelect.hpp>
#include <StepVisual_SurfaceStyleFillArea.hpp>
#include <StepVisual_SurfaceStyleRenderingWithProperties.hpp>
#include <StepVisual_RenderingPropertiesSelect.hpp>
#include <StepVisual_SurfaceStyleTransparent.hpp>
#include <StepVisual_SurfaceStyleUsage.hpp>
#include <TCollection_HAsciiString.hpp>
#include <Standard_Transient.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <TransferBRep.hpp>
#include <TransferBRep_ShapeMapper.hpp>
#include <XSControl_TransferReader.hpp>
#include <XSControl_TransferWriter.hpp>
#include <XSControl_WorkSession.hpp>
#include <StepVisual_ContextDependentOverRidingStyledItem.hpp>

namespace
{

  bool ProcessAsSurfaceStyleRendering(const StepVisual_SurfaceStyleElementSelect& theSSES,
                                      STEPConstruct_RenderingProperties&          theRenderingProps)
  {
    const occ::handle<StepVisual_SurfaceStyleRendering> aSSR = theSSES.SurfaceStyleRendering();
    if (aSSR.IsNull())
    {
      return false;
    }
    const occ::handle<StepVisual_SurfaceStyleRenderingWithProperties> aSSRWP =
      occ::down_cast<StepVisual_SurfaceStyleRenderingWithProperties>(aSSR);
    if (aSSRWP.IsNull())
    {
      return true;
    }
    theRenderingProps.Init(aSSRWP);
    return theRenderingProps.IsDefined();
  }

  bool ProcessAsSurfaceStyleBoundary(const StepVisual_SurfaceStyleElementSelect& theSSES,
                                     occ::handle<StepVisual_Colour>&             theBoundaryColour)
  {
    const occ::handle<StepVisual_SurfaceStyleBoundary> aSSB = theSSES.SurfaceStyleBoundary();
    if (aSSB.IsNull())
    {
      return false;
    }
    const occ::handle<StepVisual_CurveStyle> aCS = aSSB->StyleOfBoundary();
    if (aCS.IsNull())
    {
      return true;
    }
    theBoundaryColour = aCS->CurveColour();
    return true;
  }

  bool ProcessAsSurfaceStyleFillArea(const StepVisual_SurfaceStyleElementSelect& theSSES,
                                     const StepVisual_SurfaceSide                theSide,
                                     occ::handle<StepVisual_Colour>&             theSurfaceColour)
  {
    const occ::handle<StepVisual_SurfaceStyleFillArea> aSSFA = theSSES.SurfaceStyleFillArea();
    if (aSSFA.IsNull())
    {
      return false;
    }
    const occ::handle<StepVisual_FillAreaStyle> aFAS = aSSFA->FillArea();
    if (aFAS.IsNull())
    {
      return true;
    }

    for (int aFSSIndex = 1; aFSSIndex <= aFAS->NbFillStyles(); aFSSIndex++)
    {
      const StepVisual_FillStyleSelect                  aFSS  = aFAS->FillStylesValue(aFSSIndex);
      const occ::handle<StepVisual_FillAreaStyleColour> aFASC = aFSS.FillAreaStyleColour();
      if (!aFASC.IsNull()

          && (theSurfaceColour.IsNull() || theSide != StepVisual_ssNegative))
      {
        theSurfaceColour = aFASC->FillColour();
      }
    }
    return true;
  }

  bool ProcessAsSurfaceStyleUsage(const StepVisual_PresentationStyleSelect& thePSS,
                                  occ::handle<StepVisual_Colour>&           theSurfaceColour,
                                  occ::handle<StepVisual_Colour>&           theBoundaryColour,
                                  STEPConstruct_RenderingProperties&        theRenderingProps)
  {
    const occ::handle<StepVisual_SurfaceStyleUsage> aSSU = thePSS.SurfaceStyleUsage();
    if (aSSU.IsNull())
    {
      return false;
    }

    const occ::handle<StepVisual_SurfaceSideStyle> aSSS = aSSU->Style();
    for (int aSSESIndex = 1; aSSESIndex <= aSSS->NbStyles(); ++aSSESIndex)
    {
      const StepVisual_SurfaceStyleElementSelect aSSES = aSSS->StylesValue(aSSESIndex);

      ProcessAsSurfaceStyleFillArea(aSSES, aSSU->Side(), theSurfaceColour)
        || ProcessAsSurfaceStyleBoundary(aSSES, theBoundaryColour)
        || ProcessAsSurfaceStyleRendering(aSSES, theRenderingProps);
    }
    return true;
  }

  bool ProcessAsCurveStyle(const StepVisual_PresentationStyleSelect& thePSS,
                           occ::handle<StepVisual_Colour>&           theCurveColour)
  {
    const occ::handle<StepVisual_CurveStyle> aCS = thePSS.CurveStyle();
    if (aCS.IsNull())
    {
      return false;
    }

    theCurveColour = aCS->CurveColour();
    return true;
  }
} // namespace

STEPConstruct_Styles::STEPConstruct_Styles() = default;

STEPConstruct_Styles::STEPConstruct_Styles(const occ::handle<XSControl_WorkSession>& WS)
    : STEPConstruct_Tool(WS)
{
}

bool STEPConstruct_Styles::Init(const occ::handle<XSControl_WorkSession>& WS)
{
  myMapOfStyles.Clear();
  myStyles.Clear();
  myPSA.Clear();
  return SetWS(WS);
}

int STEPConstruct_Styles::NbStyles() const
{
  return myStyles.Extent();
}

occ::handle<StepVisual_StyledItem> STEPConstruct_Styles::Style(const int i) const
{
  return occ::down_cast<StepVisual_StyledItem>(myStyles.FindKey(i));
}

int STEPConstruct_Styles::NbRootStyles() const
{
  return myRootStyles.Extent();
}

occ::handle<StepVisual_StyledItem> STEPConstruct_Styles::RootStyle(const int i) const
{
  return occ::down_cast<StepVisual_StyledItem>(myRootStyles.FindKey(i));
}

void STEPConstruct_Styles::ClearStyles()
{
  myStyles.Clear();
  myPSA.Clear();
  myRootStyles.Clear();
}

void STEPConstruct_Styles::AddStyle(const occ::handle<StepVisual_StyledItem>& style)
{
  myStyles.Add(style);
}

occ::handle<StepVisual_StyledItem> STEPConstruct_Styles::AddStyle(
  const occ::handle<StepRepr_RepresentationItem>&            item,
  const occ::handle<StepVisual_PresentationStyleAssignment>& PSA,
  const occ::handle<StepVisual_StyledItem>&                  Override)
{
  occ::handle<StepVisual_StyledItem> Style;

  occ::handle<NCollection_HArray1<occ::handle<StepVisual_PresentationStyleAssignment>>> Styles =
    new NCollection_HArray1<occ::handle<StepVisual_PresentationStyleAssignment>>(1, 1);
  Styles->SetValue(1, PSA);

  if (Override.IsNull())
  {
    occ::handle<TCollection_HAsciiString> StyName = new TCollection_HAsciiString("color");
    Style                                         = new StepVisual_StyledItem;
    Style->Init(StyName, Styles, item);
  }
  else
  {
    occ::handle<TCollection_HAsciiString> StyName =
      new TCollection_HAsciiString("overriding color");
    occ::handle<StepVisual_OverRidingStyledItem> OStyle = new StepVisual_OverRidingStyledItem;
    OStyle->Init(StyName, Styles, item, Override);
    Style = OStyle;
  }

  myStyles.Add(Style);

  myPSA.Append(PSA);

  return Style;
}

occ::handle<StepVisual_StyledItem> STEPConstruct_Styles::AddStyle(
  const TopoDS_Shape&                                        Shape,
  const occ::handle<StepVisual_PresentationStyleAssignment>& PSA,
  const occ::handle<StepVisual_StyledItem>&                  Override)
{
  occ::handle<StepRepr_RepresentationItem> item = STEPConstruct::FindEntity(FinderProcess(), Shape);
  occ::handle<StepVisual_StyledItem>       Style;
  if (!item.IsNull())
    Style = AddStyle(item, PSA, Override);
  return Style;
}

bool STEPConstruct_Styles::CreateMDGPR(
  const occ::handle<StepRepr_RepresentationContext>&                           Context,
  occ::handle<StepVisual_MechanicalDesignGeometricPresentationRepresentation>& Repr,
  occ::handle<StepData_StepModel>&                                             theStepModel)
{
  if (myStyles.Extent() < 1)
    return false;

  occ::handle<NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>> elems =
    new NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>(1, myStyles.Extent());
  for (int i = 1; i <= myStyles.Extent(); i++)
    elems->SetValue(i, occ::down_cast<StepRepr_RepresentationItem>(myStyles.FindKey(i)));

  Repr = new StepVisual_MechanicalDesignGeometricPresentationRepresentation;
  occ::handle<TCollection_HAsciiString> ReprName = new TCollection_HAsciiString("");
  Repr->Init(ReprName, elems, Context);

  if (theStepModel->InternalParameters.WriteSchema == 3)
  {
    APIHeaderSection_MakeHeader           mkHdr(occ::down_cast<StepData_StepModel>(Model()));
    occ::handle<TCollection_HAsciiString> subSchema =
      new TCollection_HAsciiString("SHAPE_APPEARANCE_LAYER_MIM");
    mkHdr.AddSchemaIdentifier(subSchema);
  }

  return true;
}

bool STEPConstruct_Styles::CreateNAUOSRD(
  const occ::handle<StepRepr_RepresentationContext>&                Context,
  const occ::handle<StepShape_ContextDependentShapeRepresentation>& CDSR,
  const occ::handle<StepRepr_ProductDefinitionShape>&               initPDS)
{
  occ::handle<StepShape_ShapeDefinitionRepresentation> aSDR =
    new StepShape_ShapeDefinitionRepresentation;
  occ::handle<StepShape_ShapeRepresentation> aSR      = new StepShape_ShapeRepresentation;
  occ::handle<TCollection_HAsciiString>      ReprName = new TCollection_HAsciiString("");

  occ::handle<NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>> elems =
    new NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>(1, 1);

  occ::handle<StepRepr_ProductDefinitionShape> aPDS;
  if (initPDS.IsNull())
    aPDS = CDSR->RepresentedProductRelation();
  else
    aPDS = initPDS;
  occ::handle<StepRepr_ShapeRepresentationRelationship> aRepRelationShip =
    CDSR->RepresentationRelation();
  occ::handle<StepRepr_RepresentationRelationshipWithTransformation> aRRwTRSF =
    occ::down_cast<StepRepr_RepresentationRelationshipWithTransformation>(aRepRelationShip);
  StepRepr_Transformation SetReprTRSF;
  if (!aRRwTRSF.IsNull())
    SetReprTRSF = aRRwTRSF->TransformationOperator();
  else
    return false;

  occ::handle<StepRepr_ItemDefinedTransformation> anItDT = SetReprTRSF.ItemDefinedTransformation();
  elems->SetValue(1, anItDT->TransformItem2());

  aSR->Init(ReprName, elems, Context);

  for (int psbci = 1; psbci <= myPSA.Length(); psbci++)
  {
    occ::handle<StepVisual_PresentationStyleByContext> PSA =
      occ::down_cast<StepVisual_PresentationStyleByContext>(myPSA.Value(psbci));
    if (PSA.IsNull())
      continue;

    StepVisual_StyleContextSelect aStyleCntxSlct;
    aStyleCntxSlct.SetValue(aSR);
    PSA->SetStyleContext(aStyleCntxSlct);
  }

  StepRepr_RepresentedDefinition aPDSselect;
  aPDSselect.SetValue(aPDS);
  aSDR->Init(aPDSselect, aSR);
  Model()->AddWithRefs(aSDR);

  return true;
}

occ::handle<StepRepr_RepresentationContext> STEPConstruct_Styles::FindContext(
  const TopoDS_Shape& Shape) const
{

  occ::handle<StepRepr_RepresentationContext> Context;
  occ::handle<TransferBRep_ShapeMapper> mapper = TransferBRep::ShapeMapper(FinderProcess(), Shape);
  occ::handle<StepShape_ShapeRepresentation> sr;
  if (FinderProcess()->FindTypedTransient(mapper, STANDARD_TYPE(StepShape_ShapeRepresentation), sr))
  {
#ifdef OCCT_DEBUG

#endif
    Context = sr->ContextOfItems();
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
      Interface_EntityIterator subs = Graph().Sharings(item);
      for (subs.Start(); Context.IsNull() && subs.More(); subs.Next())
      {
#ifdef OCCT_DEBUG

#endif
        if (!subs.Value()->IsKind(STANDARD_TYPE(StepShape_ShapeRepresentation)))
          continue;
        sr      = occ::down_cast<StepShape_ShapeRepresentation>(subs.Value());
        Context = sr->ContextOfItems();
      }
    }
  }
#ifdef OCCT_DEBUG
  if (Context.IsNull())
  {
    std::cout << Shape.TShape()->DynamicType()->Name() << ": Cannot find context" << std::endl;
  }
#endif

  return Context;
}

bool STEPConstruct_Styles::LoadStyles()
{
  myStyles.Clear();
  myPSA.Clear();
  myRootStyles.Clear();

  occ::handle<Interface_InterfaceModel> model = Model();
  int                                   nb    = model->NbEntities();
  occ::handle<Standard_Type>            tMDGPR =
    STANDARD_TYPE(StepVisual_MechanicalDesignGeometricPresentationRepresentation);
  occ::handle<Standard_Type> tDM = STANDARD_TYPE(StepVisual_DraughtingModel);
  occ::handle<Standard_Type> tSI = STANDARD_TYPE(StepVisual_StyledItem);
  occ::handle<Standard_Type> tSR = STANDARD_TYPE(StepShape_ShapeRepresentation);
  for (int i = 1; i <= nb; i++)
  {
    occ::handle<Standard_Transient> enti = model->Value(i);
    if (enti->DynamicType() == tMDGPR || enti->DynamicType() == tDM)
    {
      occ::handle<StepRepr_Representation> container =
        occ::down_cast<StepRepr_Representation>(enti);

      int nbi = container->NbItems();
      for (int j = 1; j <= nbi; j++)
      {
        occ::handle<StepVisual_StyledItem> style =
          occ::down_cast<StepVisual_StyledItem>(container->ItemsValue(j));
        if (style.IsNull())
          continue;
        auto anItem = style->ItemAP242().Value();
        if (!anItem.IsNull() && anItem->IsKind(tSR))
        {
          myRootStyles.Add(style);
        }
        else
        {
          myStyles.Add(style);
        }
      }
    }
    else if (enti->IsKind(STANDARD_TYPE(StepVisual_StyledItem)))
    {
      occ::handle<StepVisual_StyledItem> aStyledItem = occ::down_cast<StepVisual_StyledItem>(enti);
      auto                               anItem      = aStyledItem->ItemAP242().Value();
      if (!anItem.IsNull() && anItem->IsKind(tSR) && !myRootStyles.Contains(aStyledItem))
      {
        myRootStyles.Add(aStyledItem);
      }
      else if (!myStyles.Contains(aStyledItem))
      {
        myStyles.Add(aStyledItem);
      }
    }
  }
  return !myStyles.IsEmpty();
}

bool STEPConstruct_Styles::LoadInvisStyles(
  occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>>& theInvStyles) const
{
  occ::handle<Interface_InterfaceModel> model         = Model();
  int                                   nb            = model->NbEntities();
  occ::handle<Standard_Type>            tInvisibility = STANDARD_TYPE(StepVisual_Invisibility);

  for (int i = 1; i <= nb; i++)
  {
    occ::handle<Standard_Transient> enti = model->Value(i);
    if (enti->DynamicType() != tInvisibility)
      continue;

    occ::handle<StepVisual_Invisibility> container = occ::down_cast<StepVisual_Invisibility>(enti);
    int                                  nbi       = container->NbInvisibleItems();
    for (int j = 1; j <= nbi; j++)
    {
      StepVisual_InvisibleItem           anInvItem = container->InvisibleItemsValue(j);
      occ::handle<StepVisual_StyledItem> style     = anInvItem.StyledItem();
      if (style.IsNull())
        continue;

      if (theInvStyles.IsNull())
        theInvStyles = new NCollection_HSequence<occ::handle<Standard_Transient>>;
      theInvStyles->Append(style);
    }
  }
  return (!theInvStyles.IsNull() && (theInvStyles->Length() > 0));
}

occ::handle<StepVisual_PresentationStyleAssignment> STEPConstruct_Styles::MakeColorPSA(
  const occ::handle<StepRepr_RepresentationItem>&,
  const occ::handle<StepVisual_Colour>&    SurfCol,
  const occ::handle<StepVisual_Colour>&    CurveCol,
  const STEPConstruct_RenderingProperties& theRenderingProps,
  const bool                               isForNAUO) const
{
  occ::handle<StepVisual_PresentationStyleAssignment>   PSA;
  NCollection_Sequence<occ::handle<Standard_Transient>> items;

  if (!SurfCol.IsNull())
  {
    occ::handle<TCollection_HAsciiString>       FASCName = new TCollection_HAsciiString("");
    occ::handle<StepVisual_FillAreaStyleColour> FASC     = new StepVisual_FillAreaStyleColour;
    FASC->Init(FASCName, SurfCol);

    StepVisual_FillStyleSelect FSS;
    FSS.SetValue(FASC);

    occ::handle<NCollection_HArray1<StepVisual_FillStyleSelect>> FASSs =
      new NCollection_HArray1<StepVisual_FillStyleSelect>(1, 1);
    FASSs->SetValue(1, FSS);

    occ::handle<TCollection_HAsciiString> FASName = new TCollection_HAsciiString("");
    occ::handle<StepVisual_FillAreaStyle> FAS     = new StepVisual_FillAreaStyle;
    FAS->Init(FASName, FASSs);

    occ::handle<StepVisual_SurfaceStyleFillArea> SSFA = new StepVisual_SurfaceStyleFillArea;
    SSFA->Init(FAS);

    StepVisual_SurfaceStyleElementSelect SES;
    SES.SetValue(SSFA);

    occ::handle<StepVisual_SurfaceStyleRenderingWithProperties> aSSRWP =
      theRenderingProps.CreateRenderingProperties(SurfCol);

    occ::handle<NCollection_HArray1<StepVisual_SurfaceStyleElementSelect>> SSESs;
    if (aSSRWP.IsNull())
    {
      SSESs = new NCollection_HArray1<StepVisual_SurfaceStyleElementSelect>(1, 1);
    }
    else
    {
      StepVisual_SurfaceStyleElementSelect aSESR;
      aSESR.SetValue(aSSRWP);
      SSESs = new NCollection_HArray1<StepVisual_SurfaceStyleElementSelect>(1, 2);
      SSESs->SetValue(2, aSESR);
    }
    SSESs->SetValue(1, SES);

    occ::handle<TCollection_HAsciiString>    SSSName = new TCollection_HAsciiString("");
    occ::handle<StepVisual_SurfaceSideStyle> SSS     = new StepVisual_SurfaceSideStyle;
    SSS->Init(SSSName, SSESs);

    occ::handle<StepVisual_SurfaceStyleUsage> SSU = new StepVisual_SurfaceStyleUsage;
    SSU->Init(StepVisual_ssBoth, SSS);

    items.Append(SSU);
  }

  if (!CurveCol.IsNull())
  {
    occ::handle<TCollection_HAsciiString> fontName = new TCollection_HAsciiString("continuous");
    occ::handle<StepVisual_DraughtingPreDefinedCurveFont> SDPDCF =
      new StepVisual_DraughtingPreDefinedCurveFont;
    SDPDCF->Init(fontName);

    occ::handle<StepBasic_MeasureValueMember> Val = new StepBasic_MeasureValueMember;
    Val->SetReal(0.1);
    Val->SetName("POSITIVE_LENGTH_MEASURE");

    StepVisual_CurveStyleFontSelect SCSFS;
    SCSFS.SetValue(SDPDCF);

    StepBasic_SizeSelect SSSelect;
    SSSelect.SetValue(Val);

    occ::handle<TCollection_HAsciiString> SCSName = new TCollection_HAsciiString("");
    occ::handle<StepVisual_CurveStyle>    SCS     = new StepVisual_CurveStyle;
    SCS->Init(SCSName, SCSFS, SSSelect, CurveCol);

    items.Append(SCS);
  }

  if (items.Length() < 1)
  {
#ifdef OCCT_DEBUG
    std::cout << "Error: no color is supplied" << std::endl;
#endif
    return PSA;
  }

  occ::handle<NCollection_HArray1<StepVisual_PresentationStyleSelect>> PSSs =
    new NCollection_HArray1<StepVisual_PresentationStyleSelect>(1, items.Length());
  for (int i = 1; i <= items.Length(); i++)
  {
    StepVisual_PresentationStyleSelect PSS;
    PSS.SetValue(items.Value(i));
    PSSs->SetValue(i, PSS);
  }
  if (!isForNAUO)
    PSA = new StepVisual_PresentationStyleAssignment;
  else
    PSA = new StepVisual_PresentationStyleByContext;
  PSA->Init(PSSs);

  return PSA;
}

occ::handle<StepVisual_PresentationStyleAssignment> STEPConstruct_Styles::GetColorPSA(
  const occ::handle<StepRepr_RepresentationItem>& item,
  const occ::handle<StepVisual_Colour>&           Col)
{

  occ::handle<StepVisual_PresentationStyleAssignment> PSA;
  if (myMapOfStyles.Contains(Col))
  {
    PSA = occ::down_cast<StepVisual_PresentationStyleAssignment>(myMapOfStyles.FindFromKey(Col));
  }
  else
  {
    PSA = MakeColorPSA(item, Col, Col, STEPConstruct_RenderingProperties());
    myMapOfStyles.Add(Col, PSA);
  }
  return PSA;
}

bool STEPConstruct_Styles::GetColors(const occ::handle<StepVisual_StyledItem>& theStyle,
                                     occ::handle<StepVisual_Colour>&           theSurfaceColour,
                                     occ::handle<StepVisual_Colour>&           theBoundaryColour,
                                     occ::handle<StepVisual_Colour>&           theCurveColour,
                                     STEPConstruct_RenderingProperties&        theRenderingProps,
                                     bool&                                     theIsComponent) const
{
  theSurfaceColour.Nullify();
  theBoundaryColour.Nullify();
  theCurveColour.Nullify();
  theRenderingProps = STEPConstruct_RenderingProperties();

  for (int aPSAIndex = 1; aPSAIndex <= theStyle->NbStyles(); ++aPSAIndex)
  {
    const occ::handle<StepVisual_PresentationStyleAssignment> aPSA =
      theStyle->StylesValue(aPSAIndex);
    if (aPSA.IsNull() || aPSA->Styles().IsNull())
    {
      continue;
    }
    theIsComponent = true;

    for (int aPSSIndex = 1; aPSSIndex <= aPSA->NbStyles(); ++aPSSIndex)
    {
      const StepVisual_PresentationStyleSelect aPSS = aPSA->StylesValue(aPSSIndex);

      ProcessAsSurfaceStyleUsage(aPSS, theSurfaceColour, theBoundaryColour, theRenderingProps)
        || ProcessAsCurveStyle(aPSS, theCurveColour);
    }
  }
  return !theSurfaceColour.IsNull() || !theBoundaryColour.IsNull() || !theCurveColour.IsNull()
         || theRenderingProps.IsDefined();
}

occ::handle<StepVisual_Colour> STEPConstruct_Styles::EncodeColor(const Quantity_Color& C)
{

  const char* cName = nullptr;
  if (C == Quantity_Color(Quantity_NOC_GREEN))
    cName = "green";
  else if (C == Quantity_Color(Quantity_NOC_RED))
    cName = "red";
  else if (C == Quantity_Color(Quantity_NOC_BLUE1))
    cName = "blue";
  else if (C == Quantity_Color(Quantity_NOC_YELLOW))
    cName = "yellow";
  else if (C == Quantity_Color(Quantity_NOC_MAGENTA1))
    cName = "magenta";
  else if (C == Quantity_Color(Quantity_NOC_CYAN1))
    cName = "cyan";
  else if (C == Quantity_Color(Quantity_NOC_BLACK))
    cName = "black";
  else if (C == Quantity_Color(Quantity_NOC_WHITE))
    cName = "white";

  if (cName)
  {
    occ::handle<StepVisual_DraughtingPreDefinedColour> ColPr =
      new StepVisual_DraughtingPreDefinedColour;
    occ::handle<StepVisual_PreDefinedItem> preDef = new StepVisual_PreDefinedItem;
    preDef->Init(new TCollection_HAsciiString(cName));
    ColPr->SetPreDefinedItem(preDef);
    return ColPr;
  }
  else
  {
    occ::handle<TCollection_HAsciiString> ColName = new TCollection_HAsciiString("");
    occ::handle<StepVisual_ColourRgb>     ColRGB  = new StepVisual_ColourRgb;
    NCollection_Vec3<double>              aColor_sRGB;
    C.Values(aColor_sRGB.r(), aColor_sRGB.g(), aColor_sRGB.b(), Quantity_TOC_sRGB);
    ColRGB->Init(ColName, aColor_sRGB.r(), aColor_sRGB.g(), aColor_sRGB.b());
    return ColRGB;
  }
}

occ::handle<StepVisual_Colour> STEPConstruct_Styles::EncodeColor(
  const Quantity_Color&                                                          C,
  NCollection_DataMap<TCollection_AsciiString, occ::handle<Standard_Transient>>& DPDCs,
  NCollection_DataMap<gp_Pnt, occ::handle<Standard_Transient>>&                  ColRGBs)
{

  const char* cName = nullptr;
  if (C == Quantity_Color(Quantity_NOC_GREEN))
    cName = "green";
  else if (C == Quantity_Color(Quantity_NOC_RED))
    cName = "red";
  else if (C == Quantity_Color(Quantity_NOC_BLUE1))
    cName = "blue";
  else if (C == Quantity_Color(Quantity_NOC_YELLOW))
    cName = "yellow";
  else if (C == Quantity_Color(Quantity_NOC_MAGENTA1))
    cName = "magenta";
  else if (C == Quantity_Color(Quantity_NOC_CYAN1))
    cName = "cyan";
  else if (C == Quantity_Color(Quantity_NOC_BLACK))
    cName = "black";
  else if (C == Quantity_Color(Quantity_NOC_WHITE))
    cName = "white";

  if (cName)
  {
    occ::handle<StepVisual_DraughtingPreDefinedColour> ColPr;
    TCollection_AsciiString                            aName(cName);
    if (DPDCs.IsBound(aName))
    {
      ColPr = occ::down_cast<StepVisual_DraughtingPreDefinedColour>(DPDCs.Find(aName));
      if (!ColPr.IsNull())
        return ColPr;
    }
    ColPr                                         = new StepVisual_DraughtingPreDefinedColour;
    occ::handle<StepVisual_PreDefinedItem> preDef = new StepVisual_PreDefinedItem;
    preDef->Init(new TCollection_HAsciiString(cName));
    ColPr->SetPreDefinedItem(preDef);
    DPDCs.Bind(aName, ColPr);
    return ColPr;
  }
  else
  {
    occ::handle<StepVisual_ColourRgb> ColRGB;
    gp_Pnt                            P;
    C.Values(P.ChangeCoord().ChangeData()[0],
             P.ChangeCoord().ChangeData()[1],
             P.ChangeCoord().ChangeData()[2],
             Quantity_TOC_sRGB);
    if (ColRGBs.IsBound(P))
    {
      ColRGB = occ::down_cast<StepVisual_ColourRgb>(ColRGBs.Find(P));
      if (!ColRGB.IsNull())
        return ColRGB;
    }
    occ::handle<TCollection_HAsciiString> ColName = new TCollection_HAsciiString("");
    ColRGB                                        = new StepVisual_ColourRgb;
    ColRGB->Init(ColName, P.Coord(1), P.Coord(2), P.Coord(3));
    ColRGBs.Bind(P, ColRGB);
    return ColRGB;
  }
}

bool STEPConstruct_Styles::DecodeColor(const occ::handle<StepVisual_Colour>& Colour,
                                       Quantity_Color&                       Col)
{
  if (Colour->IsKind(STANDARD_TYPE(StepVisual_ColourRgb)))
  {
    occ::handle<StepVisual_ColourRgb> rgb = occ::down_cast<StepVisual_ColourRgb>(Colour);
    if (rgb->Red() > 1. || rgb->Green() > 1. || rgb->Blue() > 1.)
    {
      double norm = rgb->Red();
      if (norm < rgb->Green())
        norm = rgb->Green();
      if (norm < rgb->Blue())
        norm = rgb->Blue();
      Col.SetValues(rgb->Red() / norm, rgb->Green() / norm, rgb->Blue() / norm, Quantity_TOC_sRGB);
    }
    else
      Col.SetValues(rgb->Red(), rgb->Green(), rgb->Blue(), Quantity_TOC_sRGB);
    return true;
  }
  else if (Colour->IsKind(STANDARD_TYPE(StepVisual_PreDefinedColour)))
  {
    occ::handle<StepVisual_PreDefinedColour> pdc =
      occ::down_cast<StepVisual_PreDefinedColour>(Colour);
    occ::handle<StepVisual_PreDefinedItem> pdi  = pdc->GetPreDefinedItem();
    const TCollection_AsciiString          name = pdi->Name()->String();
    if (name.IsEqual("red"))
      Col.SetValues(Quantity_NOC_RED);
    else if (name.IsEqual("green"))
      Col.SetValues(Quantity_NOC_GREEN);
    else if (name.IsEqual("blue"))
      Col.SetValues(Quantity_NOC_BLUE1);
    else if (name.IsEqual("yellow"))
      Col.SetValues(Quantity_NOC_YELLOW);
    else if (name.IsEqual("magenta"))
      Col.SetValues(Quantity_NOC_MAGENTA1);
    else if (name.IsEqual("cyan"))
      Col.SetValues(Quantity_NOC_CYAN1);
    else if (name.IsEqual("black"))
      Col.SetValues(Quantity_NOC_BLACK);
    else if (name.IsEqual("white"))
      Col.SetValues(Quantity_NOC_WHITE);
    else
    {
#ifdef OCCT_DEBUG
      std::cout << "Error: color name \"" << name << "\" is not recognized" << std::endl;
#endif
      return false;
    }
    return true;
  }
  return false;
}
