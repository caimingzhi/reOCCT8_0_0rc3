#include <Interface_EntityIterator.hpp>
#include <StepAP203_CcDesignApproval.hpp>
#include <StepAP203_CcDesignDateAndTimeAssignment.hpp>
#include <StepAP203_CcDesignPersonAndOrganizationAssignment.hpp>
#include <StepAP203_DateTimeItem.hpp>
#include <StepAP203_ApprovedItem.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepAP203_PersonOrganizationItem.hpp>
#include <StepAP214_AppliedDocumentReference.hpp>
#include <StepAP214_AppliedExternalIdentificationAssignment.hpp>
#include <StepAP214_ExternalIdentificationItem.hpp>
#include <StepAP214_DocumentReferenceItem.hpp>
#include <StepBasic_ApplicationContext.hpp>
#include <StepBasic_ApplicationProtocolDefinition.hpp>
#include <StepBasic_DocumentFile.hpp>
#include <StepBasic_DocumentProductEquivalence.hpp>
#include <StepBasic_DocumentRepresentationType.hpp>
#include <StepBasic_DocumentType.hpp>
#include <StepBasic_ExternalSource.hpp>
#include <StepBasic_IdentificationRole.hpp>
#include <StepBasic_ObjectRole.hpp>
#include <StepBasic_ProductDefinitionContext.hpp>
#include <StepBasic_ProductDefinitionFormation.hpp>
#include <StepBasic_ProductDefinitionWithAssociatedDocuments.hpp>
#include <StepBasic_ProductOrFormationOrDefinition.hpp>
#include <StepBasic_ProductRelatedProductCategory.hpp>
#include <StepBasic_RoleAssociation.hpp>
#include <StepBasic_SourceItem.hpp>
#include <STEPConstruct_ExternRefs.hpp>
#include <StepData_SelectNamed.hpp>
#include <StepRepr_DescriptiveRepresentationItem.hpp>
#include <StepRepr_NextAssemblyUsageOccurrence.hpp>
#include <StepRepr_ProductDefinitionShape.hpp>
#include <StepRepr_PropertyDefinition.hpp>
#include <StepRepr_PropertyDefinitionRepresentation.hpp>
#include <StepRepr_RepresentationContext.hpp>
#include <StepRepr_RepresentedDefinition.hpp>
#include <StepShape_ShapeRepresentation.hpp>
#include <TCollection_HAsciiString.hpp>
#include <XSControl_WorkSession.hpp>
#include <XSControl_TransferReader.hpp>
#include <OSD_File.hpp>
#include <OSD_Path.hpp>

STEPConstruct_ExternRefs::STEPConstruct_ExternRefs() = default;

STEPConstruct_ExternRefs::STEPConstruct_ExternRefs(const occ::handle<XSControl_WorkSession>& WS)
    : STEPConstruct_Tool(WS)
{
}

bool STEPConstruct_ExternRefs::Init(const occ::handle<XSControl_WorkSession>& WS)
{
  Clear();
  return SetWS(WS);
}

void STEPConstruct_ExternRefs::Clear()
{
  myAEIAs.Clear();
  myRoles.Clear();
  myFormats.Clear();
  myShapes.Clear();
  myTypes.Clear();
  myIsAP214.Clear();

  myDocFiles.Clear();
  mySharedPRPC.Nullify();
  mySharedDocType.Nullify();
  mySharedPDC.Nullify();
  mySharedPC.Nullify();
  myAPD.Nullify();
}

static bool findPDWADandExcludeExcess(
  occ::handle<StepAP214_AppliedDocumentReference>&                 ADR,
  NCollection_Sequence<occ::handle<Standard_Transient>>&           aSeqOfPDWAD,
  const Interface_Graph&                                           Graph,
  occ::handle<StepBasic_ProductDefinitionWithAssociatedDocuments>& aPDWAD)
{

  Interface_EntityIterator subsADR = Graph.Shareds(ADR);
  for (subsADR.Start(); subsADR.More(); subsADR.Next())
  {
    if (!subsADR.Value()->IsKind(STANDARD_TYPE(StepBasic_Document)))
      continue;
    occ::handle<StepBasic_Document> aDoc = occ::down_cast<StepBasic_Document>(subsADR.Value());

    Interface_EntityIterator subsD = Graph.Sharings(aDoc);
    for (subsD.Start(); subsD.More(); subsD.Next())
    {
      if (!subsD.Value()->IsKind(STANDARD_TYPE(StepBasic_DocumentProductEquivalence)))
        continue;
      occ::handle<StepBasic_DocumentProductEquivalence> aDPE =
        occ::down_cast<StepBasic_DocumentProductEquivalence>(subsD.Value());

      Interface_EntityIterator subsDPE = Graph.Shareds(aDPE);
      for (subsDPE.Start(); subsDPE.More(); subsDPE.Next())
      {
        if (!subsDPE.Value()->IsKind(STANDARD_TYPE(StepBasic_ProductDefinitionFormation)))
          continue;
        occ::handle<StepBasic_ProductDefinitionFormation> aPDF =
          occ::down_cast<StepBasic_ProductDefinitionFormation>(subsDPE.Value());
        Interface_EntityIterator subs = Graph.Sharings(aPDF);
        for (subs.Start(); subs.More(); subs.Next())
        {
          if (!subs.Value()->IsKind(
                STANDARD_TYPE(StepBasic_ProductDefinitionWithAssociatedDocuments)))
            continue;
          aPDWAD = occ::down_cast<StepBasic_ProductDefinitionWithAssociatedDocuments>(subs.Value());
        }

        for (int pdwadi = 1; pdwadi <= aSeqOfPDWAD.Length(); pdwadi++)
        {
          occ::handle<StepBasic_ProductDefinitionWithAssociatedDocuments> aCurPDWAD =
            occ::down_cast<StepBasic_ProductDefinitionWithAssociatedDocuments>(aSeqOfPDWAD(pdwadi));
          if (!aCurPDWAD.IsNull() && aPDWAD == aCurPDWAD)
          {

            aSeqOfPDWAD.Remove(pdwadi);
            return true;
          }
        }
      }
    }
  }
  return false;
}

bool STEPConstruct_ExternRefs::LoadExternRefs()
{

  occ::handle<Interface_InterfaceModel> model = Model();
  occ::handle<Standard_Type>            tADR  = STANDARD_TYPE(StepAP214_AppliedDocumentReference);
  occ::handle<Standard_Type>            tPDWAD =
    STANDARD_TYPE(StepBasic_ProductDefinitionWithAssociatedDocuments);
  int nb = model->NbEntities();

  NCollection_Sequence<occ::handle<Standard_Transient>> aSeqOfADR, aSeqOfPDWAD;
  for (int ient = 1; ient <= nb; ient++)
  {
    occ::handle<Standard_Transient> enti = model->Value(ient);
    if (enti->DynamicType() == tPDWAD)
      aSeqOfPDWAD.Append(enti);
    else if (enti->DynamicType() == tADR)
      aSeqOfADR.Append(enti);
  }
  int IsAP214 = 0;

  for (int adri = 1; adri <= aSeqOfADR.Length(); adri++)
  {
    occ::handle<StepAP214_AppliedDocumentReference> ADR =
      occ::down_cast<StepAP214_AppliedDocumentReference>(aSeqOfADR.Value(adri));

    occ::handle<StepBasic_ProductDefinitionWithAssociatedDocuments> aPDWAD;
    findPDWADandExcludeExcess(ADR, aSeqOfPDWAD, Graph(), aPDWAD);

    IsAP214 = 1;
    occ::handle<StepBasic_RoleAssociation>                 Role;
    occ::handle<StepBasic_ProductDefinition>               Shape;
    occ::handle<StepRepr_PropertyDefinitionRepresentation> Format;
    occ::handle<StepBasic_DocumentRepresentationType>      Type;

    Interface_EntityIterator subs4 = Graph().Sharings(ADR);
    for (subs4.Start(); subs4.More(); subs4.Next())
    {
      if (subs4.Value()->IsKind(STANDARD_TYPE(StepBasic_RoleAssociation)))
        Role = occ::down_cast<StepBasic_RoleAssociation>(subs4.Value());
    }

    subs4 = Graph().Shareds(ADR);
    for (subs4.Start(); subs4.More(); subs4.Next())
    {
      if (subs4.Value()->IsKind(STANDARD_TYPE(StepBasic_ProductDefinition)))
        Shape = occ::down_cast<StepBasic_ProductDefinition>(subs4.Value());
    }

    occ::handle<StepBasic_DocumentFile> DocFile;
    if (aPDWAD.IsNull())
    {

      subs4 = Graph().Shareds(ADR);
    }
    else

      subs4 = Graph().Shareds(aPDWAD);

    for (subs4.Start(); subs4.More(); subs4.Next())
    {
      if (!subs4.Value()->IsKind(STANDARD_TYPE(StepBasic_DocumentFile)))
        continue;
      DocFile = occ::down_cast<StepBasic_DocumentFile>(subs4.Value());
      if (DocFile.IsNull())
        continue;

      Interface_EntityIterator subs = Graph().Sharings(DocFile);
      for (subs.Start(); subs.More(); subs.Next())
      {
        const occ::handle<Standard_Transient>& sub = subs.Value();

        if (sub->IsKind(STANDARD_TYPE(StepRepr_PropertyDefinition)))
        {
          occ::handle<StepRepr_PropertyDefinition> PD =
            occ::down_cast<StepRepr_PropertyDefinition>(sub);
          Interface_EntityIterator subs2 = Graph().Sharings(PD);
          for (subs2.Start(); subs2.More(); subs2.Next())
          {
            occ::handle<StepRepr_PropertyDefinitionRepresentation> PDR =
              occ::down_cast<StepRepr_PropertyDefinitionRepresentation>(subs2.Value());
            if (PDR.IsNull())
              continue;
            if (PDR->UsedRepresentation()->IsKind(STANDARD_TYPE(StepShape_ShapeRepresentation)))
              Format = PDR;
          }
        }

        if (sub->IsKind(STANDARD_TYPE(StepBasic_DocumentRepresentationType)))
        {
          Type = occ::down_cast<StepBasic_DocumentRepresentationType>(sub);
        }
        if (!Type.IsNull() && !Format.IsNull())
          break;
      }
      if (!Type.IsNull() && !Format.IsNull())
        break;
    }
    if (DocFile.IsNull())
      continue;
    myAEIAs.Append(ADR);
    myRoles.Append(Role);
    myFormats.Append(Format);
    myShapes.Append(Shape);
    myTypes.Append(Type);
    myIsAP214.Append(IsAP214);
    myDocFiles.Append(DocFile);
  }

  for (int pdwadi = 1; pdwadi <= aSeqOfPDWAD.Length(); pdwadi++)
  {
    IsAP214 = 0;
    occ::handle<StepBasic_ProductDefinitionWithAssociatedDocuments> aPDWAD =
      occ::down_cast<StepBasic_ProductDefinitionWithAssociatedDocuments>(aSeqOfPDWAD(pdwadi));
    myShapes.Append(aPDWAD);
    myIsAP214.Append(IsAP214);
    occ::handle<StepAP214_AppliedExternalIdentificationAssignment> AEIA;
    occ::handle<StepBasic_RoleAssociation>                         Role;
    occ::handle<StepRepr_PropertyDefinitionRepresentation>         Format;
    occ::handle<StepBasic_DocumentRepresentationType>              Type;
    occ::handle<StepBasic_DocumentFile>                            DocFile;
    myAEIAs.Append(AEIA);
    myRoles.Append(Role);
    myFormats.Append(Format);
    myTypes.Append(Type);
    myDocFiles.Append(DocFile);
  }

  return myShapes.Length() > 0;
}

int STEPConstruct_ExternRefs::NbExternRefs() const
{
  return myShapes.Length();
}

const char* STEPConstruct_ExternRefs::FileName(const int num) const
{
  occ::handle<StepBasic_DocumentFile>                            DocFile;
  occ::handle<StepAP214_AppliedExternalIdentificationAssignment> AEIA;
  const char*                                                    aCStringFileName = nullptr;
  if (myDocFiles.Length() >= num && !myDocFiles.Value(num).IsNull())
    DocFile = occ::down_cast<StepBasic_DocumentFile>(myDocFiles.Value(num));
  else if (myIsAP214(num) == 1)
  {
    occ::handle<StepAP214_AppliedDocumentReference> ADR =
      occ::down_cast<StepAP214_AppliedDocumentReference>(myAEIAs(num));

    occ::handle<StepBasic_ProductDefinitionWithAssociatedDocuments> aPDWAD;

    NCollection_Sequence<occ::handle<Standard_Transient>> aSeqOfPDWAD;

    findPDWADandExcludeExcess(ADR, aSeqOfPDWAD, Graph(), aPDWAD);

    Interface_EntityIterator subs4;
    if (aPDWAD.IsNull())
    {

      subs4 = Graph().Shareds(ADR);
    }
    else

      subs4 = Graph().Shareds(aPDWAD);
    for (subs4.Start(); subs4.More(); subs4.Next())
    {
      if (!subs4.Value()->IsKind(STANDARD_TYPE(StepBasic_DocumentFile)))
        continue;
      DocFile = occ::down_cast<StepBasic_DocumentFile>(subs4.Value());
      if (DocFile.IsNull())
        continue;
    }
  }
  else
  {
    occ::handle<StepBasic_ProductDefinitionWithAssociatedDocuments> aPDWAD =
      occ::down_cast<StepBasic_ProductDefinitionWithAssociatedDocuments>(myShapes(num));
    if (aPDWAD.IsNull() || aPDWAD->DocIds().IsNull())
      return "";
    int i;
    for (i = 1; i <= aPDWAD->NbDocIds(); i++)
    {
      occ::handle<StepBasic_Document>       Doc       = aPDWAD->DocIdsValue(i);
      occ::handle<TCollection_HAsciiString> aFilename = Doc->Name();
      if (!aFilename.IsNull() && !aFilename->IsEmpty())
        return aFilename->ToCString();
    }
    return "";
  }

  if (!DocFile.IsNull())
  {
    Interface_EntityIterator subs3 = Graph().Sharings(DocFile);
    for (subs3.Start(); subs3.More(); subs3.Next())
    {
      if (subs3.Value()->IsKind(STANDARD_TYPE(StepAP214_AppliedExternalIdentificationAssignment)))
      {
        AEIA = occ::down_cast<StepAP214_AppliedExternalIdentificationAssignment>(subs3.Value());
        if (!AEIA.IsNull())
          break;
      }
    }
  }
  if (!AEIA.IsNull())
  {
    occ::handle<TCollection_HAsciiString> aFilename;
    aFilename = AEIA->AssignedId();
    if (!aFilename.IsNull() && !aFilename->IsEmpty())
    {
      aCStringFileName = aFilename->ToCString();

      if (aCStringFileName && aCStringFileName[0] == '#')
        aCStringFileName = nullptr;
    }
    if (!aCStringFileName || !aCStringFileName[0])
    {

      occ::handle<StepBasic_ExternalSource> theSource = AEIA->Source();
      if (!theSource.IsNull())
      {
        StepBasic_SourceItem theSourceId = theSource->SourceId();
        if (!theSourceId.IsNull())
        {
          occ::handle<StepData_SelectNamed> theFileName;
          theFileName = occ::down_cast<StepData_SelectNamed>(theSourceId.Value());
          if (theFileName.IsNull() || theFileName->Kind() != 6)
          {
          }
          else
            aCStringFileName = theFileName->String();
        }
      }
    }
  }
  const char* oldFileName = nullptr;

  OSD_Path mainfile(WS()->LoadedFile());
  mainfile.SetName("");
  mainfile.SetExtension("");
  TCollection_AsciiString dpath;
  mainfile.SystemName(dpath);
  if (aCStringFileName && aCStringFileName[0])
  {
    TCollection_AsciiString fullname = OSD_Path::AbsolutePath(dpath, aCStringFileName);
    if (fullname.Length() <= 0)
      fullname = aCStringFileName;
    if (!OSD_File(fullname).Exists())
    {
      oldFileName      = aCStringFileName;
      aCStringFileName = nullptr;
    }
  }
  if (!aCStringFileName || !aCStringFileName[0])
  {

    if (!DocFile.IsNull())
    {
      occ::handle<TCollection_HAsciiString> aFilename = DocFile->Id();
      if (!aFilename.IsNull() && !aFilename->IsEmpty())
        aCStringFileName = aFilename->ToCString();
      if (!aCStringFileName || !aCStringFileName[0])
      {
        aFilename = DocFile->Name();
        if (!aFilename.IsNull() && !aFilename->IsEmpty())
          aCStringFileName = aFilename->ToCString();
      }
      if (!aCStringFileName || !aCStringFileName[0])
      {
        if (oldFileName)
        {
          aCStringFileName = oldFileName;
        }
        else
        {
          return "";
        }
      }
    }
  }
  TCollection_AsciiString fullname = OSD_Path::AbsolutePath(dpath, aCStringFileName);
  if (fullname.Length() <= 0)
    fullname = aCStringFileName;
  if (!OSD_File(fullname).Exists())
  {
    if (oldFileName)
    {
      aCStringFileName = oldFileName;
    }
    occ::handle<Transfer_TransientProcess> aTP = WS()->TransferReader()->TransientProcess();
    TCollection_AsciiString                aMess("Can not read external file ");
    aMess.AssignCat(aCStringFileName);
    aTP->AddFail(DocFile, aMess.ToCString());
  }
  else
  {
    if (oldFileName && strcmp(oldFileName, aCStringFileName) != 0)
    {
      occ::handle<Transfer_TransientProcess> aTP = WS()->TransferReader()->TransientProcess();
      TCollection_AsciiString                aMess("External file with name from entity AEIA (");
      aMess.AssignCat(oldFileName);
      aMess.AssignCat(") not existed => use file name from DocumentFile entity - ");
      aMess.AssignCat(aCStringFileName);
      aTP->AddWarning(DocFile, aMess.ToCString());
    }
  }
  return aCStringFileName;
}

occ::handle<StepBasic_ProductDefinition> STEPConstruct_ExternRefs::ProdDef(const int num) const
{
  return occ::down_cast<StepBasic_ProductDefinition>(myShapes(num));
}

occ::handle<StepBasic_DocumentFile> STEPConstruct_ExternRefs::DocFile(const int num) const
{
  return occ::down_cast<StepBasic_DocumentFile>(myDocFiles.Value(num));
}

occ::handle<TCollection_HAsciiString> STEPConstruct_ExternRefs::Format(const int num) const
{
  occ::handle<TCollection_HAsciiString> Format;

  if (myIsAP214(num) == 0)
    return Format;

  occ::handle<StepRepr_PropertyDefinitionRepresentation> PDR =
    occ::down_cast<StepRepr_PropertyDefinitionRepresentation>(myFormats(num));
  if (PDR.IsNull())
    return Format;

  occ::handle<StepRepr_Representation> rep = PDR->UsedRepresentation();
  for (int i = 1; i <= rep->NbItems(); i++)
  {
    if (rep->ItemsValue(i)->IsKind(STANDARD_TYPE(StepRepr_DescriptiveRepresentationItem)))
    {
      occ::handle<StepRepr_DescriptiveRepresentationItem> DRI =
        occ::down_cast<StepRepr_DescriptiveRepresentationItem>(rep->ItemsValue(i));
      Format = DRI->Description();
      break;
    }
  }

  return Format;
}

int STEPConstruct_ExternRefs::AddExternRef(const char*                                     filename,
                                           const occ::handle<StepBasic_ProductDefinition>& PD,
                                           const char*                                     format)
{
  occ::handle<TCollection_HAsciiString> EmptyString = new TCollection_HAsciiString("");
  occ::handle<TCollection_HAsciiString> fmt         = new TCollection_HAsciiString(format);
  occ::handle<TCollection_HAsciiString> tmp         = new TCollection_HAsciiString("203");
  int                                   np          = fmt->Location(tmp, 1, fmt->Length());

  if (!(np > 0))
  {

    occ::handle<StepBasic_DocumentType> DT = new StepBasic_DocumentType;
    DT->Init(EmptyString);
    occ::handle<TCollection_HAsciiString> DFid = new TCollection_HAsciiString(filename);

    occ::handle<StepBasic_DocumentFile> DF = new StepBasic_DocumentFile;
    DF->Init(DFid, EmptyString, false, EmptyString, DT, EmptyString, false, EmptyString);

    occ::handle<StepBasic_IdentificationRole> IR = new StepBasic_IdentificationRole;

    occ::handle<TCollection_HAsciiString> aName =
      new TCollection_HAsciiString("external document id and location");
    IR->SetName(aName);

    occ::handle<StepData_SelectNamed> SDS = new StepData_SelectNamed;
    SDS->SetString(filename);
    SDS->SetName("IDENTIFIER");
    StepBasic_SourceItem SID;
    SID.SetValue(SDS);
    occ::handle<StepBasic_ExternalSource> ES = new StepBasic_ExternalSource;
    ES->Init(SID);

    StepAP214_ExternalIdentificationItem Item;
    Item.SetValue(DF);
    occ::handle<NCollection_HArray1<StepAP214_ExternalIdentificationItem>> Items =
      new NCollection_HArray1<StepAP214_ExternalIdentificationItem>(1, 1);
    Items->SetValue(1, Item);

    occ::handle<StepAP214_AppliedExternalIdentificationAssignment> ExtIdent =
      new StepAP214_AppliedExternalIdentificationAssignment;

    occ::handle<TCollection_HAsciiString> aFName = new TCollection_HAsciiString(filename);
    ExtIdent->Init(aFName, IR, ES, Items);

    occ::handle<TCollection_HAsciiString>             Dig = new TCollection_HAsciiString("digital");
    occ::handle<StepBasic_DocumentRepresentationType> Type =
      new StepBasic_DocumentRepresentationType;
    Type->Init(Dig, DF);

    occ::handle<StepAP214_AppliedDocumentReference> ADR = new StepAP214_AppliedDocumentReference;

    addAP214ExterRef(ADR, PD, DF, filename);

    occ::handle<StepBasic_ObjectRole>     OR        = new StepBasic_ObjectRole;
    occ::handle<TCollection_HAsciiString> mandatory = new TCollection_HAsciiString("mandatory");
    OR->Init(mandatory, false, EmptyString);
    StepBasic_RoleSelect RS;
    RS.SetValue(ADR);
    occ::handle<StepBasic_RoleAssociation> Role = new StepBasic_RoleAssociation;
    Role->Init(OR, RS);

    StepRepr_CharacterizedDefinition CD;
    CD.SetValue(DF);
    occ::handle<TCollection_HAsciiString> PDname =
      new TCollection_HAsciiString("external definition");
    occ::handle<StepRepr_PropertyDefinition> PropD = new StepRepr_PropertyDefinition;
    PropD->Init(PDname, true, EmptyString, CD);
    StepRepr_RepresentedDefinition RD;
    RD.SetValue(PropD);

    occ::handle<StepRepr_PropertyDefinitionRepresentation> PDRformat;
    if (format && format[0])
    {

      occ::handle<TCollection_HAsciiString> RCftype =
        new TCollection_HAsciiString("document parameters");
      occ::handle<StepRepr_RepresentationContext> RCf = new StepRepr_RepresentationContext;
      RCf->Init(EmptyString, RCftype);

      occ::handle<TCollection_HAsciiString> DRIname = new TCollection_HAsciiString("data format");
      occ::handle<TCollection_HAsciiString> DRIdscr = new TCollection_HAsciiString(format);
      occ::handle<StepRepr_DescriptiveRepresentationItem> DRI =
        new StepRepr_DescriptiveRepresentationItem;
      DRI->Init(DRIname, DRIdscr);
      occ::handle<NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>> fItems =
        new NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>(1, 1);
      fItems->SetValue(1, DRI);

      occ::handle<TCollection_HAsciiString> SRfname =
        new TCollection_HAsciiString("document format");
      occ::handle<StepRepr_Representation> SRformat = new StepRepr_Representation;
      SRformat->Init(SRfname, fItems, RCf);

      StepRepr_CharacterizedDefinition CDf;
      CDf.SetValue(DF);
      occ::handle<TCollection_HAsciiString> PDfname =
        new TCollection_HAsciiString("document property");
      occ::handle<StepRepr_PropertyDefinition> PDf = new StepRepr_PropertyDefinition;
      PDf->Init(PDfname, true, EmptyString, CDf);
      StepRepr_RepresentedDefinition RDf;
      RDf.SetValue(PDf);

      PDRformat = new StepRepr_PropertyDefinitionRepresentation;
      PDRformat->Init(RDf, SRformat);
    }

    myAEIAs.Append(ExtIdent);
    myRoles.Append(Role);
    myFormats.Append(PDRformat);

    myShapes.Append(PD);
    myTypes.Append(Type);
  }

  else
  {

    occ::handle<StepBasic_ProductDefinitionFormation> ProdDefForm = PD->Formation();
    occ::handle<StepBasic_ProductDefinitionContext>   ProdDefCont = PD->FrameOfReference();

    occ::handle<TCollection_HAsciiString> fname    = new TCollection_HAsciiString(filename);
    occ::handle<StepBasic_DocumentType>   aDocType = new StepBasic_DocumentType;
    occ::handle<TCollection_HAsciiString> aDT      = new TCollection_HAsciiString("cad_filename");
    aDocType->Init(aDT);
    occ::handle<StepBasic_Document>       aDoc = new StepBasic_Document;
    occ::handle<TCollection_HAsciiString> aDescription =
      new TCollection_HAsciiString("CAD Model associated to the part");
    aDoc->Init(EmptyString, fname, true, aDescription, aDocType);
    occ::handle<NCollection_HArray1<occ::handle<StepBasic_Document>>> aDocIds =
      new NCollection_HArray1<occ::handle<StepBasic_Document>>(1, 1);
    aDocIds->SetValue(1, aDoc);

    aDescription = PD->Description();
    occ::handle<StepBasic_ProductDefinitionWithAssociatedDocuments> PDWAD =
      new StepBasic_ProductDefinitionWithAssociatedDocuments;
    PDWAD->Init(EmptyString, aDescription, ProdDefForm, ProdDefCont, aDocIds);

    Interface_EntityIterator subs = Graph().Sharings(PD);
    for (subs.Start(); subs.More(); subs.Next())
    {
      const occ::handle<Standard_Transient>& sub = subs.Value();
      if (!sub->IsKind(STANDARD_TYPE(StepRepr_ProductDefinitionShape)))
        continue;
      occ::handle<StepRepr_ProductDefinitionShape> ProdDefSh =
        occ::down_cast<StepRepr_ProductDefinitionShape>(sub);
      if (ProdDefSh.IsNull())
        continue;
      StepRepr_CharacterizedDefinition CDf;
      CDf.SetValue(PDWAD);
      ProdDefSh->SetDefinition(CDf);
    }

    int numProdDef = Model()->Number(PD);

    Interface_EntityIterator subs2 = Graph().Sharings(PD);
    for (subs2.Start(); subs2.More(); subs2.Next())
    {
      const occ::handle<Standard_Transient>& sub2 = subs2.Value();

      if (sub2->IsKind(STANDARD_TYPE(StepRepr_NextAssemblyUsageOccurrence)))
      {
        occ::handle<StepRepr_NextAssemblyUsageOccurrence> NAUO =
          occ::down_cast<StepRepr_NextAssemblyUsageOccurrence>(sub2);
        NAUO->SetRelatedProductDefinition(PDWAD);
      }

      if (sub2->IsKind(STANDARD_TYPE(StepAP203_CcDesignPersonAndOrganizationAssignment)))
      {
        occ::handle<StepAP203_CcDesignPersonAndOrganizationAssignment> CDPAOA =
          occ::down_cast<StepAP203_CcDesignPersonAndOrganizationAssignment>(sub2);
        occ::handle<NCollection_HArray1<StepAP203_PersonOrganizationItem>> HAPOI = CDPAOA->Items();
        for (int i = 1; i <= HAPOI->Length(); i++)
        {
          StepAP203_PersonOrganizationItem         POI      = HAPOI->Value(i);
          occ::handle<StepBasic_ProductDefinition> PDtmp    = POI.ProductDefinition();
          int                                      numPDtmp = Model()->Number(PDtmp);
          if (numProdDef == numPDtmp)
          {
            POI.SetValue(PDWAD);
            HAPOI->SetValue(i, POI);
          }
        }
      }

      if (sub2->IsKind(STANDARD_TYPE(StepAP203_CcDesignDateAndTimeAssignment)))
      {
        occ::handle<StepAP203_CcDesignDateAndTimeAssignment> CDDATA =
          occ::down_cast<StepAP203_CcDesignDateAndTimeAssignment>(sub2);
        occ::handle<NCollection_HArray1<StepAP203_DateTimeItem>> HADTI = CDDATA->Items();
        for (int i = 1; i <= HADTI->Length(); i++)
        {
          StepAP203_DateTimeItem                   DTI      = HADTI->Value(i);
          occ::handle<StepBasic_ProductDefinition> PDtmp    = DTI.ProductDefinition();
          int                                      numPDtmp = Model()->Number(PDtmp);
          if (numProdDef == numPDtmp)
          {
            DTI.SetValue(PDWAD);
            HADTI->SetValue(i, DTI);
          }
        }
      }

      if (sub2->IsKind(STANDARD_TYPE(StepAP203_CcDesignApproval)))
      {
        occ::handle<StepAP203_CcDesignApproval> CDA =
          occ::down_cast<StepAP203_CcDesignApproval>(sub2);
        occ::handle<NCollection_HArray1<StepAP203_ApprovedItem>> HAAI = CDA->Items();
        for (int i = 1; i <= HAAI->Length(); i++)
        {
          StepAP203_ApprovedItem                   AI       = HAAI->Value(i);
          occ::handle<StepBasic_ProductDefinition> PDtmp    = AI.ProductDefinition();
          int                                      numPDtmp = Model()->Number(PDtmp);
          if (numProdDef == numPDtmp)
          {
            AI.SetValue(PDWAD);
            HAAI->SetValue(i, AI);
          }
        }
      }
    }

    myAEIAs.Append(PDWAD);
    myReplaceNum.Append(numProdDef);
    myRoles.Append(aDoc);
    myTypes.Append(aDocType);
  }

  return myAEIAs.Length();
}

int STEPConstruct_ExternRefs::WriteExternRefs(const int num) const
{
  if (num == 3)
  {
    for (int i = 1; i <= myAEIAs.Length(); i++)
    {
      Model()->ReplaceEntity(myReplaceNum(i), myAEIAs(i));
      if (!myRoles(i).IsNull())
        Model()->AddWithRefs(myRoles(i));
      if (!myTypes(i).IsNull())
        Model()->AddWithRefs(myTypes(i));
    }
  }
  else
  {
    for (int i = 1; i <= myAEIAs.Length(); i++)
    {
      Model()->AddWithRefs(myAEIAs(i));
      if (!myRoles(i).IsNull())
        Model()->AddWithRefs(myRoles(i));
      if (!myFormats(i).IsNull())
        Model()->AddWithRefs(myFormats(i));
      if (!myShapes(i).IsNull())
        Model()->AddWithRefs(myShapes(i));
      if (!myTypes(i).IsNull())
        Model()->AddWithRefs(myTypes(i));
    }
  }

  if (!myAPD.IsNull())
    Model()->AddWithRefs(myAPD);
  if (!mySharedPRPC.IsNull())
    Model()->AddWithRefs(mySharedPRPC);

  return myAEIAs.Length();
}

bool STEPConstruct_ExternRefs::addAP214ExterRef(
  const occ::handle<StepAP214_AppliedDocumentReference>& ADR,
  const occ::handle<StepBasic_ProductDefinition>&        PD,
  const occ::handle<StepBasic_DocumentFile>&             DF,
  const char*                                            filename)
{
  occ::handle<NCollection_HArray1<StepAP214_DocumentReferenceItem>> DRIs =
    new NCollection_HArray1<StepAP214_DocumentReferenceItem>(1, 1);
  StepAP214_DocumentReferenceItem aDRI;
  aDRI.SetValue(PD);
  DRIs->SetValue(1, aDRI);
  occ::handle<TCollection_HAsciiString> EmptyString = new TCollection_HAsciiString("");

  checkAP214Shared();

  occ::handle<StepBasic_Document> aDocument = new StepBasic_Document;
  aDocument->Init(EmptyString, EmptyString, false, EmptyString, mySharedDocType);
  ADR->Init(aDocument, EmptyString, DRIs);

  occ::handle<StepBasic_Product>                                   Product = new StepBasic_Product;
  occ::handle<NCollection_HArray1<occ::handle<StepBasic_Product>>> HProducts =
    mySharedPRPC->Products();
  int nbProducts = 0;
  if (!HProducts.IsNull())
    nbProducts = HProducts->Length();
  int                                   intProdId   = 20001 + nbProducts;
  occ::handle<TCollection_HAsciiString> ProductID   = new TCollection_HAsciiString(intProdId);
  occ::handle<TCollection_HAsciiString> ProductName = new TCollection_HAsciiString(filename);
  ProductName->AssignCat("-Doc");
  occ::handle<NCollection_HArray1<occ::handle<StepBasic_ProductContext>>> aHProdContext =
    new NCollection_HArray1<occ::handle<StepBasic_ProductContext>>(1, 1);
  aHProdContext->SetValue(1, mySharedPC);
  Product->Init(ProductID, ProductName, EmptyString, aHProdContext);

  occ::handle<StepBasic_ProductDefinitionFormation> PDF = new StepBasic_ProductDefinitionFormation;

  occ::handle<TCollection_HAsciiString> PDF_ID = new TCollection_HAsciiString("1");
  PDF->Init(PDF_ID, EmptyString, Product);

  occ::handle<StepBasic_DocumentProductEquivalence> DPE = new StepBasic_DocumentProductEquivalence;
  occ::handle<TCollection_HAsciiString>    DPEname = new TCollection_HAsciiString("equivalence");
  StepBasic_ProductOrFormationOrDefinition aPOFOD;
  aPOFOD.SetValue(PDF);
  DPE->Init(DPEname, false, EmptyString, aDocument, aPOFOD);

  Model()->AddWithRefs(DPE);

  occ::handle<NCollection_HArray1<occ::handle<StepBasic_Product>>> newHProducts =
    new NCollection_HArray1<occ::handle<StepBasic_Product>>(1, nbProducts + 1);
  for (int pi = 1; pi <= nbProducts; pi++)
    newHProducts->SetValue(pi, HProducts->Value(pi));
  newHProducts->SetValue(nbProducts + 1, Product);

  mySharedPRPC->SetProducts(newHProducts);

  occ::handle<StepBasic_ProductDefinitionWithAssociatedDocuments> PDWAD =
    new StepBasic_ProductDefinitionWithAssociatedDocuments;
  occ::handle<NCollection_HArray1<occ::handle<StepBasic_Document>>> aDocIds =
    new NCollection_HArray1<occ::handle<StepBasic_Document>>(1, 1);
  aDocIds->SetValue(1, DF);
  occ::handle<TCollection_HAsciiString> PDWAD_ID = new TCollection_HAsciiString("1");
  PDWAD->Init(PDWAD_ID, EmptyString, PDF, mySharedPDC, aDocIds);

  Model()->AddWithRefs(PDWAD);

  return true;
}

void STEPConstruct_ExternRefs::SetAP214APD(
  const occ::handle<StepBasic_ApplicationProtocolDefinition>& APD)
{
  myAPD = APD;
}

occ::handle<StepBasic_ApplicationProtocolDefinition> STEPConstruct_ExternRefs::GetAP214APD()
{
  if (myAPD.IsNull())
  {

    myAPD = new StepBasic_ApplicationProtocolDefinition;

    occ::handle<TCollection_HAsciiString> status = new TCollection_HAsciiString("version 1.1");
    occ::handle<TCollection_HAsciiString> appSchemaName =
      new TCollection_HAsciiString("pdm_schema");
    int                                       intProtocolYear = 1999;
    occ::handle<StepBasic_ApplicationContext> aApplication    = new StepBasic_ApplicationContext;
    occ::handle<TCollection_HAsciiString>     EmptyString     = new TCollection_HAsciiString("");
    aApplication->Init(EmptyString);
    myAPD->Init(status, appSchemaName, intProtocolYear, aApplication);
  }
  return myAPD;
}

void STEPConstruct_ExternRefs::checkAP214Shared()
{
  occ::handle<TCollection_HAsciiString> EmptyString = new TCollection_HAsciiString("");
  if (mySharedPRPC.IsNull())
  {

    occ::handle<TCollection_HAsciiString> PRPCname = new TCollection_HAsciiString("document");
    mySharedPRPC                                   = new StepBasic_ProductRelatedProductCategory;
    mySharedPRPC->Init(PRPCname, false, EmptyString, nullptr);
  }
  if (mySharedDocType.IsNull())
  {

    mySharedDocType = new StepBasic_DocumentType;
    occ::handle<TCollection_HAsciiString> prod_dat_type =
      new TCollection_HAsciiString("configuration controlled document version");
    mySharedDocType->Init(prod_dat_type);
  }
  if (mySharedPDC.IsNull())
  {

    mySharedPDC = new StepBasic_ProductDefinitionContext;
    occ::handle<TCollection_HAsciiString> aPDCname =
      new TCollection_HAsciiString("digital document definition");
    occ::handle<StepBasic_ApplicationContext> anAppContext = GetAP214APD()->Application();
    mySharedPDC->Init(aPDCname, anAppContext, EmptyString);
  }
  if (mySharedPC.IsNull())
  {

    mySharedPC                                             = new StepBasic_ProductContext;
    occ::handle<StepBasic_ApplicationContext> anAppContext = GetAP214APD()->Application();
    mySharedPC->Init(EmptyString, anAppContext, EmptyString);
  }
}
