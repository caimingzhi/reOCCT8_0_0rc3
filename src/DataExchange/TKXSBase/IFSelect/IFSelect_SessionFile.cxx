

#include <IFSelect_BasicDumper.hpp>
#include <IFSelect_IntParam.hpp>
#include <IFSelect_SelectAnyList.hpp>
#include <IFSelect_SelectCombine.hpp>
#include <IFSelect_SelectControl.hpp>
#include <IFSelect_SelectDeduct.hpp>
#include <IFSelect_SelectExtract.hpp>
#include <IFSelect_Selection.hpp>
#include <IFSelect_SessionDumper.hpp>
#include <IFSelect_SessionFile.hpp>
#include <IFSelect_ShareOut.hpp>
#include <IFSelect_Transformer.hpp>
#include <IFSelect_WorkSession.hpp>
#include <MoniTool_Macros.hpp>
#include <Message.hpp>
#include <Message_Messenger.hpp>
#include <OSD_OpenFile.hpp>
#include <Standard_Transient.hpp>
#include <TCollection_AsciiString.hpp>
#include <TCollection_HAsciiString.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>

#include <cstdio>
static int deja = 0;

IFSelect_SessionFile::IFSelect_SessionFile(const occ::handle<IFSelect_WorkSession>& WS)
{
  ClearLines();
  themode = false;
  if (!deja)
  {
    occ::handle<IFSelect_BasicDumper> basedumper = new IFSelect_BasicDumper;
    deja                                         = 1;
  }
  thedone    = false;
  thelastgen = 0;
  thesess    = WS;
}

IFSelect_SessionFile::IFSelect_SessionFile(const occ::handle<IFSelect_WorkSession>& WS,
                                           const char*                              filename)
{
  ClearLines();
  themode = true;
  if (!deja)
  {
    occ::handle<IFSelect_BasicDumper> basedumper = new IFSelect_BasicDumper;
    deja                                         = 1;
  }
  thedone    = false;
  theownflag = false;
  thelastgen = 0;
  thesess    = WS;
  thedone    = (Write(filename) == 0);
}

void IFSelect_SessionFile::ClearLines()
{
  thelist.Clear();
  thenl = 0;
}

int IFSelect_SessionFile::NbLines() const
{
  return thelist.Length();
}

const TCollection_AsciiString& IFSelect_SessionFile::Line(const int num) const
{
  return thelist.Value(num);
}

void IFSelect_SessionFile::AddLine(const char* line)
{
  thelist.Append(TCollection_AsciiString(line));
}

void IFSelect_SessionFile::RemoveLastLine()
{
  if (thelist.Length() > 1)
    thelist.Remove(thelist.Length());
}

bool IFSelect_SessionFile::WriteFile(const char* filename)
{
  FILE* lefic = OSD_OpenFile(filename, "w");
  int   nbl   = thelist.Length();
  for (int i = 1; i <= nbl; i++)
    fprintf(lefic, "%s\n", thelist.Value(i).ToCString());
  fclose(lefic);
  ClearLines();
  return true;
}

bool IFSelect_SessionFile::ReadFile(const char* filename)
{
  char  ligne[201];
  FILE* lefic = OSD_OpenFile(filename, "r");
  if (!lefic)
    return false;
  ClearLines();

  bool header = false;
  for (;;)
  {
    ligne[0] = '\0';
    if (fgets(ligne, 200, lefic) == nullptr || feof(lefic) != 0)
    {
      break;
    }
    if (ligne[0] == '\0')
      continue;

    if (!header)
    {
      if (!RecognizeFile(ligne))
        break;
      header = true;
    }
    ligne[200] = '\0';
    TCollection_AsciiString onemore(ligne);
    thelist.Append(onemore);
  }
  fclose(lefic);
  return header;
}

bool IFSelect_SessionFile::RecognizeFile(const char* headerline)
{
  Message_Messenger::StreamBuffer sout = Message::SendInfo();

  SplitLine(headerline);
  if (theline.Length() != 4)
  {
    sout << "File Form Incorrect" << std::endl;
    return false;
  }
  occ::handle<Standard_Type> sesstype = thesess->DynamicType();
  if (!theline.Value(1).IsEqual("!XSTEP") || !theline.Value(2).IsEqual("SESSION")
      || !theline.Value(4).IsEqual(sesstype->Name()))
  {
    sout << "Lineno." << thenl << " : File Header Description Incorrect" << std::endl;
    return false;
  }

  return true;
}

int IFSelect_SessionFile::Write(const char* filename)
{
  thenewnum = 0;
  int stat  = WriteSession();
  if (stat != 0)
    return stat;
  stat = WriteEnd();
  if (stat != 0)
    return stat;
  return (WriteFile(filename) ? 0 : -1);
}

int IFSelect_SessionFile::Read(const char* filename)
{
  if (!ReadFile(filename))
    return -1;
  thenewnum = 0;
  int stat  = ReadSession();
  if (stat != 0)
    return stat;
  stat = ReadEnd();
  return stat;
}

int IFSelect_SessionFile::WriteSession()
{
  char laligne[200];
  thedone = true;

  thenames.Clear();
  int nbidents = thesess->MaxIdent();
  thenums      = new NCollection_HArray1<int>(0, nbidents);
  thenums->Init(0);
  int i;
  for (i = 1; i <= nbidents; i++)
  {
    occ::handle<Standard_Transient> item = thesess->Item(i);
    if (!item.IsNull())
      thenums->SetValue(i, -1);
  }

  Sprintf(laligne, "!XSTEP SESSION V1 %s", thesess->DynamicType()->Name());
  WriteLine(laligne, '\n');
  Sprintf(laligne, "!GENERALS");
  WriteLine(laligne, '\n');
  Sprintf(laligne, "ErrorHandle %d", (thesess->ErrorHandle() ? 1 : 0));
  WriteLine(laligne, '\n');
  occ::handle<NCollection_HSequence<int>> idents;
  int                                     nb;
  occ::handle<TCollection_HAsciiString>   name;

  idents = thesess->ItemIdents(STANDARD_TYPE(IFSelect_IntParam));
  nb     = idents->Length();
  if (nb > 0)
    WriteLine("!INTEGERS", '\n');
  int j;
  for (j = 1; j <= nb; j++)
  {
    i                                = idents->Value(j);
    occ::handle<IFSelect_IntParam> P = thesess->IntParam(i);
    name                             = thesess->Name(P);
    if (name.IsNull())
    {
      thenewnum++;
      idents->SetValue(i, thenewnum);
      Sprintf(laligne, " #%d %d", thenewnum, P->Value());
    }
    else
      Sprintf(laligne, " %s %d", name->ToCString(), P->Value());
    WriteLine(laligne, '\n');
  }

  idents = thesess->ItemIdents(STANDARD_TYPE(TCollection_HAsciiString));
  nb     = idents->Length();
  if (nb > 0)
    WriteLine("!TEXTS", '\n');
  for (j = 1; j <= nb; j++)
  {
    i                                       = idents->Value(j);
    occ::handle<TCollection_HAsciiString> P = thesess->TextParam(i);
    name                                    = thesess->Name(P);
    if (name.IsNull())
    {
      thenewnum++;
      thenums->SetValue(i, thenewnum);
      Sprintf(laligne, " #%d %s", thenewnum, P->ToCString());
    }
    else
      Sprintf(laligne, " %s %s", name->ToCString(), P->ToCString());
    WriteLine(laligne, '\n');
  }

  idents = thesess->ItemIdents(STANDARD_TYPE(IFSelect_Selection));
  nb     = idents->Length();
  if (nb > 0)
    WriteLine("!SELECTIONS", '\n');
  for (j = 1; j <= nb; j++)
  {
    i                                 = idents->Value(j);
    occ::handle<IFSelect_Selection> P = thesess->Selection(i);
    NewItem(i, P);

    DeclareAndCast(IFSelect_SelectExtract, sxt, P);
    if (!sxt.IsNull())
    {
      Sprintf(laligne, " %c", (sxt->IsDirect() ? 'D' : 'R'));
      WriteLine(laligne);
    }
    DeclareAndCast(IFSelect_SelectAnyList, sli, P);
    if (!sli.IsNull())
    {
      SetOwn(false);
      WriteLine(" LIST");
      SendItem(sli->Lower());
      SendItem(sli->Upper());
      SetOwn(true);
    }

    WriteOwn(P);
    WriteLine("", '\n');
  }

  SetOwn(false);
  if (nb > 0)
    WriteLine("!SOURCES", '\n');
  for (j = 1; j <= nb; j++)
  {
    i                                   = idents->Value(j);
    occ::handle<IFSelect_Selection> P   = thesess->Selection(i);
    int                             nbs = thesess->NbSources(P);
    if (nbs == 0)
      continue;
    name = thesess->Name(P);
    if (name.IsNull())
      Sprintf(laligne, " #%d %d", thenums->Value(i), nbs);
    else
      Sprintf(laligne, " %s %d", name->ToCString(), nbs);
    WriteLine(laligne);
    for (int k = 1; k <= nbs; k++)
      SendItem(thesess->Source(P, k));
    WriteLine("", '\n');
  }

  idents = thesess->ItemIdents(STANDARD_TYPE(IFSelect_GeneralModifier));
  nb     = idents->Length();
  if (nb > 0)
    WriteLine("!MODIFIERS", '\n');
  for (j = 1; j <= nb; j++)
  {

    i                                       = idents->Value(j);
    occ::handle<IFSelect_GeneralModifier> P = thesess->GeneralModifier(i);
    NewItem(i, P);
    SetOwn(true);

    WriteOwn(P);
    WriteLine("", '\n');
  }

  idents = thesess->ItemIdents(STANDARD_TYPE(IFSelect_Transformer));
  nb     = idents->Length();
  if (nb > 0)
    WriteLine("!TRANSFORMERS", '\n');
  for (j = 1; j <= nb; j++)
  {

    i                                   = idents->Value(j);
    occ::handle<IFSelect_Transformer> P = thesess->Transformer(i);
    NewItem(i, P);
    SetOwn(true);

    WriteOwn(P);
    WriteLine("", '\n');
  }

  SetOwn(false);
  idents = thesess->ItemIdents(STANDARD_TYPE(IFSelect_Dispatch));
  nb     = idents->Length();
  if (nb > 0)
    WriteLine("!DISPATCHES", '\n');
  for (j = 1; j <= nb; j++)
  {
    i                                = idents->Value(j);
    occ::handle<IFSelect_Dispatch> P = thesess->Dispatch(i);
    NewItem(i, P);

    SetOwn(false);
    SendItem(P->FinalSelection());
    SetOwn(true);

    WriteOwn(P);
    WriteLine("", '\n');
  }

  WriteLine("!FILENAMING");
  SetOwn(false);
  occ::handle<TCollection_HAsciiString> namingpart = thesess->FilePrefix();
  if (namingpart->IsEmpty())
    namingpart.Nullify();
  if (namingpart.IsNull())
    SendVoid();
  else
    SendText(namingpart->ToCString());
  namingpart = thesess->DefaultFileRoot();
  if (namingpart->IsEmpty())
    namingpart.Nullify();
  if (namingpart.IsNull())
    SendVoid();
  else
    SendText(namingpart->ToCString());
  namingpart = thesess->FileExtension();
  if (namingpart->IsEmpty())
    namingpart.Nullify();
  if (namingpart.IsNull())
    SendVoid();
  else
    SendText(namingpart->ToCString());
  WriteLine("", '\n');

  for (j = 1; j <= nb; j++)
  {
    i                                = idents->Value(j);
    occ::handle<IFSelect_Dispatch> P = thesess->Dispatch(i);
    if (!P->HasRootName())
      continue;
    namingpart = P->RootName();
    SetOwn(false);
    SendItem(P);
    Sprintf(laligne, " %s", namingpart->ToCString());
    WriteLine(laligne, ' ');
    WriteLine("", '\n');
  }

  for (int formod = 1; formod >= 0; formod--)
  {
    idents = thesess->FinalModifierIdents((formod > 0));
    nb     = idents->Length();
    if (nb == 0)
      continue;
    if (formod > 0)
      WriteLine("!MODELMODIFIERS", '\n');
    else
      WriteLine("!FILEMODIFIERS", '\n');
    for (j = 1; j <= nb; j++)
    {
      i                                       = idents->Value(j);
      occ::handle<IFSelect_GeneralModifier> P = thesess->GeneralModifier(i);
      SetOwn(false);
      SendItem(P);

      SendItem(P->Selection());
      SendItem(P->Dispatch());
      WriteLine("", '\n');
    }
  }

  theline.Clear();
  return 0;
}

int IFSelect_SessionFile::WriteEnd()
{
  WriteLine("!XSTEP END", '\n');
  return 0;
}

void IFSelect_SessionFile::WriteLine(const char* line, const char follow)
{
  if (line[0] != '\0')
    thebuff.AssignCat(line);
  if (follow == '\0')
    return;
  if (follow != '\n')
    thebuff.AssignCat(follow);
  else
  {
    thelist.Append(thebuff);
    thebuff.Clear();
    thenl++;
  }
}

bool IFSelect_SessionFile::WriteOwn(const occ::handle<Standard_Transient>& item)
{
  if (item.IsNull())
    return false;
  SetOwn(true);
  occ::handle<IFSelect_SessionDumper> dumper = IFSelect_SessionDumper::First();
  while (!dumper.IsNull())
  {
    if (dumper->WriteOwn(*this, item))
      break;
    dumper = dumper->Next();
  }
  SetOwn(false);
  return (!dumper.IsNull());
}

int IFSelect_SessionFile::ReadSession()
{
  Message_Messenger::StreamBuffer sout = Message::SendInfo();

  thedone = true;

  thenums.Nullify();
  thenames.Clear();

  if (!ReadLine())
    return 1;
  if (theline.Length() != 4)
  {
    sout << "File Form Incorrect" << std::endl;
    return 1;
  }
  occ::handle<Standard_Type> sesstype = thesess->DynamicType();
  if (!theline.Value(1).IsEqual("!XSTEP") || !theline.Value(2).IsEqual("SESSION")
      || !theline.Value(4).IsEqual(sesstype->Name()))
  {
    sout << "Lineno." << thenl << " : File Header Description Incorrect" << std::endl;
    return 1;
  }

  if (!ReadLine())
    return 1;

  int rubr = (theline.Length() == 1 && theline.Value(1).IsEqual("!GENERALS"));
  while (rubr)
  {
    if (!ReadLine())
      return 1;
    if (theline.Length() == 0)
      continue;
    const TCollection_AsciiString& ungen = theline.Value(1);
    if (ungen.Value(1) == '!')
      break;
    if (ungen.IsEqual("ErrorHandle"))
    {
      if (theline.Length() != 2)
      {
        sout << "Lineno." << thenl << " : ErrorHandle Description Incorrect" << std::endl;
        continue;
      }
      if (theline.Value(2).IsEqual("0"))
        thesess->SetErrorHandle(false);
      else if (theline.Value(2).IsEqual("1"))
        thesess->SetErrorHandle(true);
      else
      {
        sout << "Lineno." << thenl << " : ErrorHandle Incorrect : " << theline.Value(2)
             << std::endl;
        continue;
      }
      continue;
    }
    else
      sout << "Lineno." << thenl << " : Unknown General Parameter : " << ungen << " , ignored"
           << std::endl;
  }

  rubr = (theline.Length() == 1 && theline.Value(1).IsEqual("!INTEGERS"));
  while (rubr)
  {
    if (!ReadLine())
      return 1;
    if (theline.Value(1).Value(1) == '!')
      break;
    if (theline.Length() != 2)
    {
      sout << "Lineno." << thenl << " : An Integer Parameter is badly defined" << std::endl;
      continue;
    }
    occ::handle<IFSelect_IntParam> par = new IFSelect_IntParam;
    par->SetValue(atoi(theline.Value(2).ToCString()));
    AddItem(par);
  }

  rubr = (theline.Length() == 1 && theline.Value(1).IsEqual("!TEXTS"));
  while (rubr)
  {
    if (!ReadLine())
      return 1;
    if (theline.Value(1).Value(1) == '!')
      break;
    if (theline.Length() != 2)
    {
      sout << "Lineno." << thenl << " : A Text Parameter is badly defined" << std::endl;
      continue;
    }

    TCollection_AsciiString oneline = thelist.Value(thenl);
    int                     iw = 0, inc = 0;
    for (int ic = 1; ic <= oneline.Length(); ic++)
    {
      char unc = oneline.Value(1);
      inc      = ic;
      if (unc == ' ')
        iw = 1;
      else if (iw > 0)
        break;
    }
    oneline.Remove(1, inc);
    AddItem(new TCollection_HAsciiString(oneline.ToCString()));
  }

  rubr = (theline.Length() == 1 && theline.Value(1).IsEqual("!SELECTIONS"));
  while (rubr)
  {
    if (!ReadLine())
      return 1;
    if (theline.Value(1).Value(1) == '!')
      break;
    if (theline.Length() < 2)
    {
      sout << "Lineno." << thenl << " : A Selection is badly defined" << std::endl;
      continue;
    }

    occ::handle<IFSelect_IntParam> low, up;
    int                            firstown = 3;
    int                            direct   = 0;
    int                            numlist  = 0;
    if (theline.Length() > 2)
    {
      if (theline.Value(3).IsEqual("D"))
        direct = 1;
      else if (theline.Value(3).IsEqual("R"))
        direct = -1;
      if (direct != 0)
        firstown++;
      if (firstown + 2 <= theline.Length())
      {
        if (theline.Value(firstown).IsEqual("LIST"))
        {
          numlist = firstown;
          firstown += 3;
          low = GetCasted(IFSelect_IntParam, ItemValue(numlist + 1));
          up  = GetCasted(IFSelect_IntParam, ItemValue(numlist + 2));
        }
      }
      SetLastGeneral(firstown - 1);
    }
    occ::handle<Standard_Transient> item;
    ReadOwn(item);
    if (item.IsNull())
      continue;
    DeclareAndCast(IFSelect_SelectExtract, sxt, item);
    if (!sxt.IsNull())
    {
      if (direct == 0)
        sout << "Lineno." << thenl << " : A SelectExtract is badly defined" << std::endl;
      else
        sxt->SetDirect((direct > 0));
    }
    DeclareAndCast(IFSelect_SelectAnyList, sli, item);
    if (!sli.IsNull())
    {
      if (numlist == 0)
        sout << "Lineno." << thenl << " : A SelectAnyList is badly defined" << std::endl;
      else
        sli->SetRange(low, up);
    }
    AddItem(item);
  }

  rubr = (theline.Length() == 1 && theline.Value(1).IsEqual("!SOURCES"));
  while (rubr)
  {
    if (!ReadLine())
      return 1;
    if (theline.Value(1).Value(1) == '!')
      break;
    if (theline.Length() < 3)
    {
      sout << "Lineno." << thenl << " : A Selection Source List is badly defined" << std::endl;
      continue;
    }
    DeclareAndCast(IFSelect_Selection, sel, ItemValue(1));
    if (sel.IsNull())
    {
      sout << "Lineno." << thenl << " : A Source List is not for a Selection" << std::endl;
      continue;
    }
    int nbs = atoi(theline.Value(2).ToCString());

    DeclareAndCast(IFSelect_SelectExtract, sxt, sel);
    if (!sxt.IsNull())
    {
      if (nbs > 1)
        sout << "Lineno." << thenl << " : SelectExtract, more than one source, following ignored"
             << std::endl;
      DeclareAndCast(IFSelect_Selection, source, ItemValue(3));
      sxt->SetInput(source);
    }
    DeclareAndCast(IFSelect_SelectDeduct, sdt, sel);
    if (!sdt.IsNull())
    {
      if (nbs > 1)
        sout << "Lineno." << thenl << " : SelectDeduct, more than one source, following ignored"
             << std::endl;
      sdt->SetInput(GetCasted(IFSelect_Selection, ItemValue(3)));
    }
    DeclareAndCast(IFSelect_SelectControl, sct, sel);
    if (!sct.IsNull())
    {
      if (nbs != 2)
        sout << "Lineno." << thenl << " : SelectControl, not two sources, following ignored"
             << std::endl;
      sct->SetMainInput(GetCasted(IFSelect_Selection, ItemValue(3)));
      sct->SetSecondInput(GetCasted(IFSelect_Selection, ItemValue(4)));
    }
    DeclareAndCast(IFSelect_SelectCombine, sco, sel);
    if (!sco.IsNull())
    {
      for (int j = 1; j <= nbs; j++)
        sco->Add(GetCasted(IFSelect_Selection, ItemValue(j + 2)));
    }
  }

  rubr = (theline.Length() == 1 && theline.Value(1).IsEqual("!MODIFIERS"));
  while (rubr)
  {
    if (!ReadLine())
      return 1;
    if (theline.Value(1).Value(1) == '!')
      break;
    if (theline.Length() < 2)
    {
      sout << "Lineno." << thenl << " : A Modifier is badly defined" << std::endl;
      continue;
    }
    occ::handle<Standard_Transient> item;
    ReadOwn(item);
    if (item.IsNull())
      continue;
    DeclareAndCast(IFSelect_GeneralModifier, modif, item);
    if (modif.IsNull())
    {
      sout << "Lineno." << thenl << " : A Modifier has not been Recognized" << std::endl;
      continue;
    }
    AddItem(modif, false);
  }

  rubr = (theline.Length() == 1 && theline.Value(1).IsEqual("!TRANSFORMERS"));
  while (rubr)
  {
    if (!ReadLine())
      return 1;
    if (theline.Value(1).Value(1) == '!')
      break;
    if (theline.Length() < 2)
    {
      sout << "Lineno." << thenl << " : A Transformer is badly defined" << std::endl;
      continue;
    }
    occ::handle<Standard_Transient> item;
    ReadOwn(item);
    if (item.IsNull())
      continue;
    DeclareAndCast(IFSelect_Transformer, trf, item);
    if (trf.IsNull())
    {
      sout << "Lineno." << thenl << " : A Transformer has not been Recognized" << std::endl;
      continue;
    }
    AddItem(trf, false);
  }

  rubr = (theline.Length() == 1 && theline.Value(1).IsEqual("!DISPATCHES"));
  while (rubr)
  {
    if (!ReadLine())
      return 1;
    if (theline.Value(1).Value(1) == '!')
      break;
    if (theline.Length() < 3)
    {
      sout << "Lineno." << thenl << " : A Dispatch is badly defined" << std::endl;
      continue;
    }
    DeclareAndCast(IFSelect_Selection, input, ItemValue(3));
    SetLastGeneral(3);
    occ::handle<Standard_Transient> item;
    ReadOwn(item);
    if (item.IsNull())
      continue;
    DeclareAndCast(IFSelect_Dispatch, disp, item);
    if (disp.IsNull())
    {
      sout << "Lineno." << thenl << " : A Dispatch has not been Recognized" << std::endl;
      continue;
    }
    AddItem(disp);
    thesess->SetItemSelection(disp, input);
  }

  rubr = (theline.Length() == 4 && theline.Value(1).IsEqual("!FILENAMING"));
  if (rubr)
  {
    if (!IsVoid(2))
      thesess->SetFilePrefix(TextValue(2).ToCString());
    if (!IsVoid(3))
      thesess->SetDefaultFileRoot(TextValue(3).ToCString());
    if (!IsVoid(4))
      thesess->SetFileExtension(TextValue(4).ToCString());
  }
  while (rubr)
  {
    if (!ReadLine())
      return 1;
    if (theline.Value(1).Value(1) == '!')
      break;
    if (theline.Length() != 2)
    {
      sout << "Lineno." << thenl << " : A File Root is badly defined" << std::endl;
      continue;
    }
    DeclareAndCast(IFSelect_Dispatch, disp, ItemValue(1));
    thesess->SetFileRoot(disp, theline.Value(2).ToCString());
  }

  for (int formod = 1; formod >= 0; formod--)
  {
    rubr = (theline.Length() == 1
            && ((formod == 1 && theline.Value(1).IsEqual("!MODELMODIFIERS"))
                || (formod == 0 && theline.Value(1).IsEqual("!FILEMODIFIERS"))));

    while (rubr)
    {
      if (!ReadLine())
        return 1;
      if (theline.Value(1).Value(1) == '!')
        break;
      if (theline.Length() < 3)
      {
        sout << "Lineno." << thenl << " : A General Modifier is badly defined" << std::endl;
        continue;
      }
      DeclareAndCast(IFSelect_GeneralModifier, modif, ItemValue(1));
      DeclareAndCast(IFSelect_Selection, input, ItemValue(2));
      DeclareAndCast(IFSelect_Dispatch, disp, ItemValue(3));
      if (modif.IsNull())
      {
        sout << "Lineno." << thenl << " : A General Modifier has not been Recognized" << std::endl;
        continue;
      }
      thesess->SetItemSelection(modif, input);
      if (!disp.IsNull())
        thesess->SetAppliedModifier(modif, disp);
      else
        thesess->SetAppliedModifier(modif, thesess->ShareOut());
    }
  }

  return 0;
}

int IFSelect_SessionFile::ReadEnd()
{
  Message_Messenger::StreamBuffer sout = Message::SendInfo();
  if (theline.Length() != 2 || !theline.Value(1).IsEqual("!XSTEP")
      || !theline.Value(2).IsEqual("END"))
  {
    sout << "End of File Incorrect, lineno" << thenl << std::endl;
    return 1;
  }
  return 0;
}

bool IFSelect_SessionFile::ReadLine()
{
  if (thenl >= thelist.Length())
    return false;
  thenl++;
  const char* ligne = thelist.Value(thenl).ToCString();

  if (ligne[0] == '\0')
    return ReadLine();
  SplitLine(ligne);
  return true;
}

void IFSelect_SessionFile::SplitLine(const char* line)
{
  char mot[80];
  theline.Clear();
  int  nbc  = 0;
  bool word = (line[0] > ' ');
  for (int i = 0; line[i] != '\0'; i++)
  {
    if (line[i] > ' ')
    {
      if (!word)
      {
        nbc  = 0;
        word = true;
      }
      mot[nbc] = line[i];
      nbc++;
    }
    else
    {
      if (word)
      {
        word     = false;
        mot[nbc] = '\0';
        theline.Append(TCollection_AsciiString(mot));
      }
      if (line[i] == '\0' || line[i] == '\n')
        break;
    }
  }
  thelastgen = 0;
}

bool IFSelect_SessionFile::ReadOwn(occ::handle<Standard_Transient>& item)
{
  Message_Messenger::StreamBuffer sout = Message::SendInfo();

  if (theline.Length() < 2)
    return false;
  const TCollection_AsciiString& type = theline.Value(2);
  if (thelastgen < 2)
    thelastgen = 2;

  occ::handle<IFSelect_SessionDumper> dumper = IFSelect_SessionDumper::First();
  while (!dumper.IsNull())
  {
    if (dumper->ReadOwn(*this, type, item))
      break;
    dumper = dumper->Next();
  }
  if (dumper.IsNull())
    sout << " -- Lineno." << thenl << " : an Item could not be read" << std::endl;
  return (!dumper.IsNull());
}

void IFSelect_SessionFile::AddItem(const occ::handle<Standard_Transient>& item, const bool active)
{
  Message_Messenger::StreamBuffer sout = Message::SendInfo();

  const TCollection_AsciiString& name = theline.Value(1);
  int                            id   = 0;
  if (!item.IsNull())
  {
    if (name.Value(1) == '#')
      id = thesess->AddItem(item, active);
    else if (!thesess->NamedItem(name.ToCString()).IsNull())
      id = thesess->AddItem(item, active);
    else
      id = thesess->AddNamedItem(name.ToCString(), item, active);
  }
  else
    sout << "Lineno." << thenl << " -- Name : " << name << " : Item could not be defined"
         << std::endl;
  thenames.Bind(name, id);
}

bool IFSelect_SessionFile::IsDone() const
{
  return thedone;
}

occ::handle<IFSelect_WorkSession> IFSelect_SessionFile::WorkSession() const
{
  return thesess;
}

void IFSelect_SessionFile::NewItem(const int ident, const occ::handle<Standard_Transient>& par)
{
  char laligne[100];
  if (!thesess->HasName(par))
  {
    thenewnum++;
    thenums->SetValue(ident, thenewnum);
    Sprintf(laligne, " #%d %s", thenewnum, par->DynamicType()->Name());
  }
  else
    Sprintf(laligne, " %s %s", thesess->Name(par)->ToCString(), par->DynamicType()->Name());
  WriteLine(laligne);
}

void IFSelect_SessionFile::SetOwn(const bool mode)
{
  theownflag = mode;
}

void IFSelect_SessionFile::SendVoid()
{

  WriteLine(" $");
}

void IFSelect_SessionFile::SendItem(const occ::handle<Standard_Transient>& par)
{
  Message_Messenger::StreamBuffer sout = Message::SendInfo();

  char laligne[100];
  int  filenum = 0;
  int  id      = thesess->ItemIdent(par);
  if (id != 0)
    filenum = thenums->Value(id);
  if (filenum == 0)
  {
    if (!par.IsNull())
      sout << "Lineno " << thenl << " --  Unknown Item : "
           << " Type:" << par->DynamicType()->Name() << std::endl;
    SendVoid();
    thedone = false;
    return;
  }

  if (filenum < 0)
    Sprintf(laligne, " :%s", thesess->Name(par)->ToCString());
  else
    Sprintf(laligne, " #%d", filenum);
  WriteLine(laligne);
}

void IFSelect_SessionFile::SendText(const char* text)
{
  char laligne[100];

  Sprintf(laligne, " %s", text);
  WriteLine(laligne);
}

void IFSelect_SessionFile::SetLastGeneral(const int lastgen)
{
  thelastgen = lastgen;
}

int IFSelect_SessionFile::NbParams() const
{
  return theline.Length() - thelastgen;
}

bool IFSelect_SessionFile::IsVoid(const int num) const
{
  int nm = num + thelastgen;
  if (nm <= 0 || nm > theline.Length())
    return true;
  const TCollection_AsciiString& term = theline.Value(nm);
  return (term.IsEqual("$") || term.IsEqual(":$"));
}

bool IFSelect_SessionFile::IsText(const int num) const
{
  int nm = num + thelastgen;
  if (nm <= 0 || nm > theline.Length())
    return false;
  const TCollection_AsciiString& term = theline.Value(nm);
  if (term.Value(1) == ':')
    return false;
  if (term.Value(1) == '#')
    return false;
  if (term.IsEqual("$"))
    return false;
  return true;
}

const TCollection_AsciiString& IFSelect_SessionFile::ParamValue(const int num) const
{
  return theline.Value(num + thelastgen);
}

TCollection_AsciiString IFSelect_SessionFile::TextValue(const int num) const
{
  int                     nm = num + thelastgen;
  TCollection_AsciiString res;
  if (nm <= 0 || nm > theline.Length())
    return res;
  res = theline.Value(nm);
  if (res.Value(res.Length()) == '"')
    res.Remove(res.Length());
  if (res.Value(1) == ':')
    res.Remove(1);
  if (res.Value(1) == '"')
    res.Remove(1);
  return res;
}

occ::handle<Standard_Transient> IFSelect_SessionFile::ItemValue(const int num) const
{
  Message_Messenger::StreamBuffer sout = Message::SendInfo();

  occ::handle<Standard_Transient> res;
  int                             nm = num + thelastgen;
  if (nm <= 0 || nm > theline.Length())
    return res;
  int                     id;
  TCollection_AsciiString name = theline.Value(nm);
  if (name.Value(1) == ':')
    name.Remove(1);
  if (name.IsEqual("$"))
    return res;
  if (!thenames.Find(name, id))
  {
    sout << " -- Item Unknown in File : " << name << " lineno " << thenl << " param." << nm
         << std::endl;
    id = 0;
  }
  return thesess->Item(id);
}

void IFSelect_SessionFile::Destroy() {}
