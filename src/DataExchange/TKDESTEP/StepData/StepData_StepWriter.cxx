

#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_InterfaceMismatch.hpp>
#include <MoniTool_Macros.hpp>
#include <Interface_ReportEntity.hpp>
#include <Standard_Transient.hpp>
#include <StepData_ESDescr.hpp>
#include <StepData_FieldList.hpp>
#include <StepData_PDescr.hpp>
#include <StepData_Protocol.hpp>
#include <StepData_ReadWriteModule.hpp>
#include <StepData_SelectArrReal.hpp>
#include <StepData_SelectMember.hpp>
#include <StepData_StepModel.hpp>
#include <StepData_StepWriter.hpp>
#include <StepData_UndefinedEntity.hpp>
#include <StepData_WriterLib.hpp>
#include <TCollection_AsciiString.hpp>
#include <TCollection_HAsciiString.hpp>

#include <cstdio>
#define StepLong 72

static TCollection_AsciiString textscope(" &SCOPE");
static TCollection_AsciiString textendscope("        ENDSCOPE");
static TCollection_AsciiString textcomm("  /*  ");
static TCollection_AsciiString textendcomm("  */");
static TCollection_AsciiString textlist("(");
static TCollection_AsciiString textendlist(")");
static TCollection_AsciiString textendent(");");
static TCollection_AsciiString textparam(",");
static TCollection_AsciiString textundef("$");
static TCollection_AsciiString textderived("*");
static TCollection_AsciiString texttrue(".T.");
static TCollection_AsciiString textfalse(".F.");
static TCollection_AsciiString textunknown(".U.");

StepData_StepWriter::StepData_StepWriter(const occ::handle<StepData_StepModel>& amodel)
    : thecurr(StepLong),
      thefloatw(12)
{
  themodel   = amodel;
  thelabmode = thetypmode = 0;
  thefile                 = new NCollection_HSequence<occ::handle<TCollection_HAsciiString>>();
  thesect                 = false;
  thefirst                = true;
  themult                 = false;
  thecomm                 = false;
  thelevel = theindval = 0;
  theindent            = false;
}

Interface_FloatWriter& StepData_StepWriter::FloatWriter()
{
  return thefloatw;
}

int& StepData_StepWriter::LabelMode()
{
  return thelabmode;
}

int& StepData_StepWriter::TypeMode()
{
  return thetypmode;
}

void StepData_StepWriter::SetScope(const int numscope, const int numin)
{
  int nb = themodel->NbEntities();
  if (numscope <= 0 || numscope > nb || numin <= 0 || numin > nb)
    throw Interface_InterfaceMismatch("StepWriter : SetScope, out of range");
  if (thescopenext.IsNull())
  {
    thescopebeg = new NCollection_HArray1<int>(1, nb);
    thescopebeg->Init(0);
    thescopeend = new NCollection_HArray1<int>(1, nb);
    thescopeend->Init(0);
    thescopenext = new NCollection_HArray1<int>(1, nb);
    thescopenext->Init(0);
  }
  else if (thescopenext->Value(numin) != 0)
  {
#ifdef OCCT_DEBUG
    std::cout << "StepWriter : SetScope (scope : " << numscope << " entity : " << numin
              << "), Entity already in a Scope" << std::endl;
#endif
    throw Interface_InterfaceMismatch("StepWriter : SetScope, already set");
  }
  thescopenext->SetValue(numin, -1);
  if (thescopebeg->Value(numscope) == 0)
    thescopebeg->SetValue(numscope, numin);
  int lastin = thescopeend->Value(numscope);
  if (lastin > 0)
    thescopenext->SetValue(lastin, numin);
  thescopeend->SetValue(numscope, numin);
}

bool StepData_StepWriter::IsInScope(const int num) const
{
  if (thescopenext.IsNull())
    return false;
  return (thescopenext->Value(num) != 0);
}

void StepData_StepWriter::SendModel(const occ::handle<StepData_Protocol>& protocol,
                                    const bool                            headeronly)
{
  StepData_WriterLib lib(protocol);

  if (!headeronly)
    thefile->Append(new TCollection_HAsciiString("ISO-10303-21;"));
  SendHeader();

  Interface_EntityIterator header = themodel->Header();
  thenum                          = 0;
  for (header.Start(); header.More(); header.Next())
  {
    const occ::handle<Standard_Transient>& anent = header.Value();

    occ::handle<StepData_ReadWriteModule> module;
    int                                   CN;
    if (lib.Select(anent, module, CN))
    {
      if (module->IsComplex(CN))
        StartComplex();
      else
      {
        TCollection_AsciiString styp;
        if (thetypmode > 0)
          styp = module->ShortType(CN);
        if (styp.Length() == 0)
          styp = module->StepType(CN);
        StartEntity(styp);
      }
      module->WriteStep(CN, *this, anent);
      if (module->IsComplex(CN))
        EndComplex();
    }
    else
    {

      DeclareAndCast(StepData_UndefinedEntity, und, anent);
      if (und.IsNull())
        continue;
      if (und->IsComplex())
        StartComplex();
      und->WriteParams(*this);
      if (und->IsComplex())
        EndComplex();
    }
    EndEntity();
  }
  EndSec();
  if (headeronly)
    return;

  SendData();

  occ::handle<Interface_Check> achglob = themodel->GlobalCheck();
  int                          nbfails = achglob->NbFails();
  if (nbfails > 0)
  {
    Comment(true);
    SendComment("GLOBAL FAIL MESSAGES,  recorded at Read time :");
    for (int ifail = 1; ifail <= nbfails; ifail++)
    {
      SendComment(achglob->Fail(ifail));
    }
    Comment(false);
    NewLine(false);
  }

  int nb = themodel->NbEntities();
  for (int i = 1; i <= nb; i++)
  {

    if (!thescopebeg.IsNull())
    {
      if (thescopenext->Value(i) != 0)
        continue;
    }
    SendEntity(i, lib);
  }

  EndSec();
  EndFile();
}

void StepData_StepWriter::SendHeader()
{
  NewLine(false);
  thefile->Append(new TCollection_HAsciiString("HEADER;"));
  thesect = true;
}

void StepData_StepWriter::SendData()
{
  if (thesect)
    throw Interface_InterfaceMismatch("StepWriter : Data section");
  NewLine(false);
  thefile->Append(new TCollection_HAsciiString("DATA;"));
  thesect = true;
}

void StepData_StepWriter::EndSec()
{
  thefile->Append(new TCollection_HAsciiString("ENDSEC;"));
  thesect = false;
}

void StepData_StepWriter::EndFile()
{
  if (thesect)
    throw Interface_InterfaceMismatch("StepWriter : EndFile");
  NewLine(false);
  thefile->Append(new TCollection_HAsciiString("END-ISO-10303-21;"));
  thesect = false;
}

void StepData_StepWriter::SendEntity(const int num, const StepData_WriterLib& lib)
{
  char                            lident[20];
  occ::handle<Standard_Transient> anent = themodel->Entity(num);
  int                             idnum = num, idtrue = 0;

  if (thelabmode > 0)
    idtrue = themodel->IdentLabel(anent);
  if (thelabmode == 1)
    idnum = idtrue;
  if (idnum == 0)
    idnum = num;
  if (thelabmode < 2 || idnum == idtrue)
    Sprintf(lident, "#%d = ", idnum);
  else
    Sprintf(lident, "%d:#%d = ", idnum, idtrue);

  thecurr.Clear();
  thecurr.Add(lident);
  themult = false;

  if (!thescopebeg.IsNull())
  {
    int numin = thescopebeg->Value(num);
    if (numin != 0)
    {
      SendScope();
      for (int nument = numin; numin > 0; nument = numin)
      {
        SendEntity(nument, lib);
        numin = thescopenext->Value(nument);
      }
      SendEndscope();
    }
  }

  thenum = num;
  occ::handle<StepData_ReadWriteModule> module;
  int                                   CN;
  if (themodel->IsRedefinedContent(num))
  {

    occ::handle<Interface_ReportEntity> rep = themodel->ReportEntity(num);
    DeclareAndCast(StepData_UndefinedEntity, und, rep->Content());
    if (und.IsNull())
    {
      thechecks.CCheck(num)->AddFail("Erroneous Entity, Content lost");
      StartEntity(TCollection_AsciiString("!?LOST_DATA"));
    }
    else
    {
      thechecks.CCheck(num)->AddWarning("Erroneous Entity, equivalent content");
      if (und->IsComplex())
        AddString(" (", 2);
      und->WriteParams(*this);
      if (und->IsComplex())
      {
        AddString(") ", 2);
      }
    }
    EndEntity();
    NewLine(false);
    Comment(true);
    if (und.IsNull())
      SendComment("   ERRONEOUS ENTITY, DATA LOST");
    SendComment("On Entity above, Fail Messages recorded at Read time :");
    occ::handle<Interface_Check> ach     = rep->Check();
    int                          nbfails = ach->NbFails();
    for (int ifail = 1; ifail <= nbfails; ifail++)
    {
      SendComment(ach->Fail(ifail));
    }
    Comment(false);
    NewLine(false);
  }
  else if (lib.Select(anent, module, CN))
  {
    if (module->IsComplex(CN))
      StartComplex();
    else
    {
      TCollection_AsciiString styp;
      if (thetypmode > 0)
        styp = module->ShortType(CN);
      if (styp.Length() == 0)
        styp = module->StepType(CN);
      StartEntity(styp);
    }
    module->WriteStep(CN, *this, anent);
    if (module->IsComplex(CN))
      EndComplex();
    EndEntity();
  }
  else
  {

    DeclareAndCast(StepData_UndefinedEntity, und, anent);
    if (und.IsNull())
      return;
    if (und->IsComplex())
      StartComplex();
    und->WriteParams(*this);
    if (und->IsComplex())
      EndComplex();
    EndEntity();
  }
}

void StepData_StepWriter::NewLine(const bool evenempty)
{
  if (evenempty || thecurr.Length() > 0)
  {
    thefile->Append(thecurr.Moved());
  }
  int indst = thelevel * 2;
  if (theindent)
    indst += theindval;
  thecurr.SetInitial(indst);
  thecurr.Clear();
}

void StepData_StepWriter::JoinLast(const bool)
{
  thecurr.SetKeep();
}

void StepData_StepWriter::Indent(const bool onent)
{
  theindent = onent;
}

void StepData_StepWriter::SendIdent(const int ident)
{
  char lident[12];
  Sprintf(lident, "#%d =", ident);
  thecurr.Clear();
  thecurr.Add(lident);
  themult = false;
}

void StepData_StepWriter::SendScope()
{
  AddString(textscope);
}

void StepData_StepWriter::SendEndscope()
{
  NewLine(false);
  thefile->Append(new TCollection_HAsciiString(textendscope));
}

void StepData_StepWriter::Comment(const bool mode)
{
  if (mode && !thecomm)
    AddString(textcomm, 20);
  if (!mode && thecomm)
    AddString(textendcomm);
  thecomm = mode;
}

void StepData_StepWriter::SendComment(const occ::handle<TCollection_HAsciiString>& text)
{
  if (!thecomm)
    throw Interface_InterfaceMismatch("StepWriter : Comment");
  AddString(text->ToCString(), text->Length());
}

void StepData_StepWriter::SendComment(const char* text)
{
  if (!thecomm)
    throw Interface_InterfaceMismatch("StepWriter : Comment");
  AddString(text, (int)strlen(text));
}

void StepData_StepWriter::StartEntity(const TCollection_AsciiString& atype)
{
  if (atype.Length() == 0)
    return;
  if (themult)
  {

    if (thelevel != 1)
      throw Interface_InterfaceMismatch("StepWriter : StartEntity");

    AddString(textendlist);
    AddString(" ", 1);
  }
  themult = true;

  AddString(atype);
  thelevel  = 0;
  theindval = thecurr.Length();
  thecurr.SetInitial(0);
  thefirst = true;
  OpenSub();
}

void StepData_StepWriter::StartComplex()
{
  AddString("( ", 2);
}

void StepData_StepWriter::EndComplex()
{
  AddString(") ", 2);
}

void StepData_StepWriter::SendField(const StepData_Field&               fild,
                                    const occ::handle<StepData_PDescr>& descr)
{
  bool done = true;
  int  kind = fild.Kind(false);

  if (kind == 16)
  {
    DeclareAndCast(StepData_SelectMember, sm, fild.Transient());
    SendSelect(sm, descr);
    return;
  }
  switch (kind)
  {

    case 0:
      SendUndef();
      break;
    case 1:
      Send(fild.Integer());
      break;
    case 2:
      SendBoolean(fild.Boolean());
      break;
    case 3:
      SendLogical(fild.Logical());
      break;
    case 4:
      SendEnum(fild.EnumText());
      break;
    case 5:
      Send(fild.Real());
      break;
    case 6:
      Send(fild.String());
      break;
    case 7:
      Send(fild.Entity());
      break;
    case 8:
      done = false;
      break;
    case 9:
      SendDerived();
      break;
    default:
      done = false;
      break;
  }
  if (done)
    return;

  int arity = fild.Arity();
  if (arity == 0)
  {
    SendUndef();
    return;
  }
  if (arity == 1)
  {
    OpenSub();
    int i, low = fild.Lower(), up = low + fild.Length() - 1;
    for (i = low; i <= up; i++)
    {
      kind = fild.ItemKind(i);
      done = true;
      switch (kind)
      {
        case 0:
          SendUndef();
          break;
        case 1:
          Send(fild.Integer(i));
          break;
        case 2:
          SendBoolean(fild.Boolean(i));
          break;
        case 3:
          SendLogical(fild.Logical(i));
          break;
        case 4:
          SendEnum(fild.EnumText(i));
          break;
        case 5:
          Send(fild.Real(i));
          break;
        case 6:
          Send(fild.String(i));
          break;
        case 7:
          Send(fild.Entity(i));
          break;
        default:
          SendUndef();
          done = false;
          break;
      }
    }
    CloseSub();
    return;
  }
  if (arity == 2)
  {
    OpenSub();
    int j, low1 = fild.Lower(1), up1 = low1 + fild.Length(1) - 1;
    for (j = low1; j <= up1; j++)
    {
      int i = 0, low2 = fild.Lower(2), up2 = low2 + fild.Length(2) - 1;
      OpenSub();
      for (i = low2; i <= up2; i++)
      {
        kind = fild.ItemKind(i, j);
        done = true;
        switch (kind)
        {
          case 0:
            SendUndef();
            break;
          case 1:
            Send(fild.Integer(i, j));
            break;
          case 2:
            SendBoolean(fild.Boolean(i, j));
            break;
          case 3:
            SendLogical(fild.Logical(i, j));
            break;
          case 4:
            SendEnum(fild.EnumText(i, j));
            break;
          case 5:
            Send(fild.Real(i, j));
            break;
          case 6:
            Send(fild.String(i, j));
            break;
          case 7:
            Send(fild.Entity(i, j));
            break;
          default:
            SendUndef();
            done = false;
            break;
        }
      }
      CloseSub();
    }
    CloseSub();
    return;
  }
}

void StepData_StepWriter::SendSelect(const occ::handle<StepData_SelectMember>& sm,
                                     const occ::handle<StepData_PDescr>&)
{

  bool selname = false;
  if (sm.IsNull())
    return;
  if (sm->HasName())
  {
    selname = true;

    OpenTypedSub(sm->Name());
  }
  int kind = sm->Kind();
  switch (kind)
  {
    case 0:
      SendUndef();
      break;
    case 1:
      Send(sm->Integer());
      break;
    case 2:
      SendBoolean(sm->Boolean());
      break;
    case 3:
      SendLogical(sm->Logical());
      break;
    case 4:
      SendEnum(sm->EnumText());
      break;
    case 5:
      Send(sm->Real());
      break;
    case 6:
      Send(sm->String());
      break;
    case 8:
      SendArrReal(occ::down_cast<StepData_SelectArrReal>(sm)->ArrReal());
      break;
    default:
      break;
  }
  if (selname)
    CloseSub();
}

void StepData_StepWriter::SendList(const StepData_FieldList&            list,
                                   const occ::handle<StepData_ESDescr>& descr)
{

  int i, nb = list.NbFields();
  for (i = 1; i <= nb; i++)
  {
    occ::handle<StepData_PDescr> pde;
    if (!descr.IsNull())
      pde = descr->Field(i);
    const StepData_Field& fild = list.Field(i);
    SendField(fild, pde);
  }
}

void StepData_StepWriter::OpenSub()
{
  AddParam();
  AddString(textlist);
  thefirst = true;
  thelevel++;
}

void StepData_StepWriter::OpenTypedSub(const char* subtype)
{
  AddParam();
  if (subtype[0] != '\0')
    AddString(subtype, (int)strlen(subtype));
  AddString(textlist);
  thefirst = true;
  thelevel++;
}

void StepData_StepWriter::CloseSub()
{
  AddString(textendlist);
  thefirst = false;
  thelevel--;
}

void StepData_StepWriter::AddParam()
{
  if (!thefirst)
    AddString(textparam);
  thefirst = false;
}

void StepData_StepWriter::Send(const int val)
{
  char lval[12];
  AddParam();
  Sprintf(lval, "%d", val);
  AddString(lval, (int)strlen(lval));
}

void StepData_StepWriter::Send(const double val)
{

  char lval[24] = {};
  int  lng      = thefloatw.Write(val, lval);
  AddParam();
  AddString(lval, lng);
}

void StepData_StepWriter::Send(const TCollection_AsciiString& val)
{
  AddParam();

  TCollection_AsciiString aVal = CleanTextForSend(val);
  int                     aNn  = aVal.Length();

  aVal.Insert(1, '\'');
  aVal.AssignCat('\'');
  aNn += 2;

  if (thecurr.CanGet(aNn))
    AddString(aVal, 0);

  else
  {
    thefile->Append(thecurr.Moved());
    int anIndst = thelevel * 2;
    if (theindent)
      anIndst += theindval;
    if (anIndst + aNn <= StepLong)
      thecurr.SetInitial(anIndst);
    else
      thecurr.SetInitial(0);
    if (thecurr.CanGet(aNn))
      AddString(aVal, 0);
    else
    {
      while (aNn > 0)
      {
        if (aNn <= StepLong)
        {
          thecurr.Add(aVal);
          thecurr.FreezeInitial();
          break;
        }
        int aStop = StepLong;
        for (; aStop > 0 && aVal.Value(aStop) != ' '; aStop--)
          ;
        if (!aStop)
        {
          aStop = StepLong;
          for (; aStop > 0 && aVal.Value(aStop) != '\\'; aStop--)
            ;
          if (!aStop)
          {
            aStop = StepLong;
            for (; aStop > 0 && aVal.Value(aStop) != '_'; aStop--)
              ;
            if (!aStop)
              aStop = StepLong;
          }
        }
        TCollection_AsciiString aBval = aVal.Split(aStop);
        thefile->Append(new TCollection_HAsciiString(aVal));
        aVal = aBval;
        aNn -= aStop;
      }
    }
  }
}

void StepData_StepWriter::Send(const occ::handle<Standard_Transient>& val)
{
  char lident[20];

  if (val.IsNull())
  {

    thechecks.CCheck(thenum)->AddFail("Null Reference");
    SendUndef();
    Comment(true);
    SendComment(" NUL REF ");
    Comment(false);
    return;
  }
  int num = themodel->Number(val);

  if (num == 0)
  {
    if (val->IsKind(STANDARD_TYPE(TCollection_HAsciiString)))
    {
      DeclareAndCast(TCollection_HAsciiString, strval, val);
      Send(TCollection_AsciiString(strval->ToCString()));
      return;
    }

    else if (val->IsKind(STANDARD_TYPE(StepData_SelectMember)))
    {
      DeclareAndCast(StepData_SelectMember, sm, val);
      occ::handle<StepData_PDescr> descr;
      SendSelect(sm, descr);
    }

    else
    {
      thechecks.CCheck(thenum)->AddFail("UnknownReference");
      SendUndef();
      Comment(true);
      SendComment(" UNKNOWN REF ");
      Comment(false);
    }
  }

  else
  {
    int idnum = num, idtrue = 0;
    if (thelabmode > 0)
      idtrue = themodel->IdentLabel(val);
    if (thelabmode == 1)
      idnum = idtrue;
    if (idnum == 0)
      idnum = num;
    if (thelabmode < 2 || idnum == idtrue)
      Sprintf(lident, "#%d", idnum);
    else
      Sprintf(lident, "%d:#%d", idnum, idtrue);
    AddParam();
    AddString(lident, (int)strlen(lident));
  }
}

void StepData_StepWriter::SendBoolean(const bool val)
{
  if (val)
    SendString(texttrue);
  else
    SendString(textfalse);
}

void StepData_StepWriter::SendLogical(const StepData_Logical val)
{
  if (val == StepData_LTrue)
    SendString(texttrue);
  else if (val == StepData_LFalse)
    SendString(textfalse);
  else
    SendString(textunknown);
}

void StepData_StepWriter::SendString(const TCollection_AsciiString& val)
{
  AddParam();
  AddString(val);
}

void StepData_StepWriter::SendString(const char* val)
{
  AddParam();
  AddString(val, (int)strlen(val));
}

void StepData_StepWriter::SendEnum(const TCollection_AsciiString& val)
{
  if (val.Length() == 1 && val.Value(1) == '$')
  {
    SendUndef();
    return;
  }
  AddParam();
  TCollection_AsciiString aValue = val;
  if (aValue.Value(1) != '.')
    aValue.Prepend('.');
  if (aValue.Value(aValue.Length()) != '.')
    aValue += '.';
  AddString(aValue, 2);
}

void StepData_StepWriter::SendEnum(const char* val)
{

  if (val[0] == '$' && val[1] == '\0')
  {
    SendUndef();
    return;
  }
  TCollection_AsciiString aValue(val);
  SendEnum(aValue);
}

void StepData_StepWriter::SendArrReal(const occ::handle<NCollection_HArray1<double>>& anArr)
{
  AddString(textlist);
  if (anArr->Length() > 0)
  {

    Send(anArr->Value(1));
    for (int i = 2; i <= anArr->Length(); i++)
    {

      Send(anArr->Value(i));
    }
  }
  AddString(textendlist);
}

void StepData_StepWriter::SendUndef()
{
  AddParam();
  AddString(textundef);
}

void StepData_StepWriter::SendDerived()
{
  AddParam();
  AddString(textderived);
}

void StepData_StepWriter::EndEntity()
{

  if (thelevel != 1)
    throw Interface_InterfaceMismatch("StepWriter : EndEntity");

  AddString(textendent);
  thelevel    = 0;
  bool indent = theindent;
  theindent   = false;
  NewLine(false);
  theindent = indent;
  themult   = false;
}

void StepData_StepWriter::AddString(const TCollection_AsciiString& astr, const int more)
{
  while (!thecurr.CanGet(astr.Length() + more))
  {
    thefile->Append(thecurr.Moved());
    int indst = thelevel * 2;
    if (theindent)
      indst += theindval;
    thecurr.SetInitial(indst);
  }
  thecurr.Add(astr);
}

void StepData_StepWriter::AddString(const char* astr, const int lnstr, const int more)
{
  while (!thecurr.CanGet(lnstr + more))
  {
    thefile->Append(thecurr.Moved());
    int indst = thelevel * 2;
    if (theindent)
      indst += theindval;
    thecurr.SetInitial(indst);
  }
  thecurr.Add(astr, lnstr);
}

Interface_CheckIterator StepData_StepWriter::CheckList() const
{
  return thechecks;
}

int StepData_StepWriter::NbLines() const
{
  return thefile->Length();
}

occ::handle<TCollection_HAsciiString> StepData_StepWriter::Line(const int num) const
{
  return thefile->Value(num);
}

bool StepData_StepWriter::Print(Standard_OStream& S)
{
  bool isGood = (S.good());
  int  nb     = thefile->Length();
  for (int i = 1; i <= nb && isGood; i++)
    S << thefile->Value(i)->ToCString() << "\n";

  S << std::flush;
  isGood = (S && S.good());

  return isGood;
}

TCollection_AsciiString StepData_StepWriter::CleanTextForSend(
  const TCollection_AsciiString& theText)
{
  TCollection_AsciiString aResult;
  const int               aNb = theText.Length();

  for (int anI = 1; anI <= aNb; anI++)
  {
    const char anUncar = theText.Value(anI);

    bool anIsDirective    = false;
    int  aDirectiveLength = 0;

    if (anUncar == '\\' && anI <= aNb)
    {

      if (anI + 3 <= aNb && theText.Value(anI + 1) == 'X' && theText.Value(anI + 3) == '\\')
      {
        const char aThirdChar = theText.Value(anI + 2);

        if (aThirdChar == '2' || aThirdChar == '4' || aThirdChar == '0')
        {
          anIsDirective    = true;
          aDirectiveLength = 4;

          if (aThirdChar == '2' || aThirdChar == '4')
          {
            int aJ = anI + 4;
            while (aJ <= aNb - 3)
            {
              if (theText.Value(aJ) == '\\' && theText.Value(aJ + 1) == 'X'
                  && theText.Value(aJ + 2) == '0' && theText.Value(aJ + 3) == '\\')
              {
                aDirectiveLength = (aJ + 4) - anI;
                break;
              }
              aJ++;
            }
          }
        }
      }

      else if (anI + 4 <= aNb && theText.Value(anI + 1) == 'X' && theText.Value(anI + 4) == '\\')
      {
        const char aThirdChar  = theText.Value(anI + 2);
        const char aFourthChar = theText.Value(anI + 3);

        if (std::isxdigit(aThirdChar) && std::isxdigit(aFourthChar))
        {
          anIsDirective    = true;
          aDirectiveLength = 5;
        }
      }

      else if (anI + 2 <= aNb && theText.Value(anI + 2) == '\\')
      {
        const char aSecondChar = theText.Value(anI + 1);
        if (aSecondChar == 'S' || aSecondChar == 'N' || aSecondChar == 'T')
        {
          anIsDirective    = true;
          aDirectiveLength = 3;
        }
      }

      else if (anI + 3 <= aNb && theText.Value(anI + 1) == 'P' && theText.Value(anI + 3) == '\\')
      {
        const char aSecondChar = theText.Value(anI + 2);
        if (std::isalpha(aSecondChar))
        {
          anIsDirective    = true;
          aDirectiveLength = 4;
        }
      }
    }

    if (anIsDirective)
    {

      for (int aJ = 0; aJ < aDirectiveLength; aJ++)
      {
        aResult += theText.Value(anI + aJ);
      }
      anI += aDirectiveLength - 1;
    }
    else
    {

      if (anUncar == '\'')
      {
        aResult += "''";
      }
      else if (anUncar == '\\')
      {
        aResult += "\\\\";
      }
      else if (anUncar == '\n')
      {
        aResult += "\\N\\";
      }
      else if (anUncar == '\t')
      {
        aResult += "\\T\\";
      }
      else
      {
        aResult += anUncar;
      }
    }
  }

  return aResult;
}
