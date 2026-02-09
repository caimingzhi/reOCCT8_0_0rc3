

#include <gp_XY.hpp>
#include <gp_XYZ.hpp>
#include <IGESData_ColorEntity.hpp>
#include <IGESData_DefType.hpp>
#include <IGESData_IGESEntity.hpp>
#include <IGESData_IGESModel.hpp>
#include <IGESData_IGESWriter.hpp>
#include <IGESData_Protocol.hpp>
#include <IGESData_ReadWriteModule.hpp>
#include <IGESData_UndefinedEntity.hpp>
#include <IGESData_WriterLib.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_FloatWriter.hpp>
#include <Interface_InterfaceMismatch.hpp>
#include <MoniTool_Macros.hpp>
#include <Interface_ParamList.hpp>
#include <Interface_ParamSet.hpp>
#include <Interface_ReportEntity.hpp>
#include <Message.hpp>
#include <Message_Messenger.hpp>
#include <Standard_PCharacter.hpp>
#include <TCollection_HAsciiString.hpp>

#include <cstdio>
#define MaxcarsG 72
#define MaxcarsP 64

IGESData_IGESWriter::IGESData_IGESWriter(const occ::handle<IGESData_IGESModel>& amodel)
    : thedirs(0, amodel->NbEntities()),
      thepnum(1, amodel->NbEntities() + 1),
      thecurr(MaxcarsG + 1),
      themodew(0),
      thefloatw(9)
{
  themodel = amodel;
  thehead  = new NCollection_HSequence<occ::handle<TCollection_HAsciiString>>();
  thesep   = ',';
  theendm  = ';';
  thepars  = new NCollection_HSequence<occ::handle<TCollection_HAsciiString>>();
  thepnum.SetValue(1, 1);
  thesect = 0;
  thepnum.Init(0);
}

IGESData_IGESWriter::IGESData_IGESWriter()
    : thedirs(0, 0),
      thepnum(1, 1),
      thecurr(MaxcarsG + 1),
      thefloatw(9)
{
}

IGESData_IGESWriter::IGESData_IGESWriter(const IGESData_IGESWriter&)
    : thedirs(0, 0),
      thepnum(1, 1),
      thecurr(MaxcarsG + 1),
      thefloatw(9)
{
}

Interface_FloatWriter& IGESData_IGESWriter::FloatWriter()
{
  return thefloatw;
}

int& IGESData_IGESWriter::WriteMode()
{
  return themodew;
}

void IGESData_IGESWriter::SendStartLine(const char* startline)
{
  Standard_PCharacter pstartline;

  pstartline = (Standard_PCharacter)startline;

  size_t lst = strlen(startline);
  if (lst == 0)
    return;
  if (thestar.IsNull())
    thestar = new NCollection_HSequence<occ::handle<TCollection_HAsciiString>>();
  if (lst <= (size_t)MaxcarsG)
  {
    thestar->Append(new TCollection_HAsciiString(startline));
    return;
  }

  char startchar       = startline[MaxcarsG];
  pstartline[MaxcarsG] = '\0';
  SendStartLine(startline);
  pstartline[MaxcarsG] = startchar;
  SendStartLine(&startline[MaxcarsG]);
}

void IGESData_IGESWriter::SendModel(const occ::handle<IGESData_Protocol>& protocol)
{
  Message_Messenger::StreamBuffer sout = Message::SendInfo();
  IGESData_WriterLib              lib(protocol);

  int nb = themodel->NbEntities();
#ifdef PATIENCELOG
  sout << " IGESWriter : " << nb << " Entities (* = 1000 Ent.s)" << std::endl;
#endif
  SectionS();
  int ns = themodel->NbStartLines();
  int i;
  for (i = 1; i <= ns; i++)
    SendStartLine(themodel->StartLine(i));
  SectionG(themodel->GlobalSection());
  SectionsDP();
  for (i = 1; i <= nb; i++)
  {
    occ::handle<IGESData_IGESEntity> ent = themodel->Entity(i);
    occ::handle<IGESData_IGESEntity> cnt = ent;
#ifdef PATIENCELOG
    if (i % 1000 == 1)
      std::cout << "*" << std::flush;
#endif

    if (themodel->IsRedefinedContent(i))
    {
      sout << " --  IGESWriter : Erroneous Entity N0." << i << "  --" << std::endl;
      occ::handle<Interface_ReportEntity> rep = themodel->ReportEntity(i);
      if (!rep.IsNull())
        cnt = GetCasted(IGESData_IGESEntity, rep->Content());
      if (cnt.IsNull())
        cnt = ent;
    }

    DirPart(cnt);
    OwnParams(ent);

    occ::handle<IGESData_ReadWriteModule> module;
    int                                   CN;

    if (lib.Select(cnt, module, CN))
      module->WriteOwnParams(CN, cnt, *this);
    else if (cnt->IsKind(STANDARD_TYPE(IGESData_UndefinedEntity)))
    {
      DeclareAndCast(IGESData_UndefinedEntity, undent, cnt);
      undent->WriteOwnParams(*this);
    }
    else
      sout << " -- IGESWriter : Not Processed for n0." << i << " in file,  Type "
           << cnt->TypeNumber() << "  Form " << cnt->FormNumber() << std::endl;

    Associativities(cnt);
    Properties(cnt);
    EndEntity();
  }
#ifdef PATIENCELOG
  std::cout << " Entity Sending Finished" << std::endl;
#endif
  SectionT();
}

void IGESData_IGESWriter::SectionS()
{
  if (thesect != 0)
    throw Interface_InterfaceError("IGESWriter : SectionS");
  thesect = 1;
}

void IGESData_IGESWriter::SectionG(const IGESData_GlobalSection& header)
{
  if (thesect != 1)
    throw Interface_InterfaceError("IGESWriter : SectionG");
  thesect = 2;
  thesep  = header.Separator();
  theendm = header.EndMark();
  thecurr.SetMax(MaxcarsG);

  occ::handle<Interface_ParamSet> gl = header.Params();
  int                             nb = gl->NbParams();
  for (int i = 1; i <= nb; i++)
  {
    const Interface_FileParameter& FP = gl->Param(i);
    AddString(FP.CValue());
    if (i < nb)
      AddChar(thesep);
    else
      AddChar(theendm);
  }
  if (thecurr.Length() > 0)
    thehead->Append(thecurr.Moved());
}

void IGESData_IGESWriter::SectionsDP()
{
  if (thesect != 2)
    throw Interface_InterfaceError("IGESWriter : SectionsDP");
  thesect = 3;
  thecurr.SetMax(MaxcarsP);
  thestep = IGESData_ReadEnd;
}

void IGESData_IGESWriter::SectionT()
{
  if (thesect != 3)
    throw Interface_InterfaceError("IGESWriter : SectionT");
  thesect = 4;
  thepnum.SetValue(thepnum.Length(), thepars->Length() + 1);
}

void IGESData_IGESWriter::DirPart(const occ::handle<IGESData_IGESEntity>& anent)
{
  if (thesect != 3 && thestep != IGESData_ReadEnd)
    throw Interface_InterfaceError("IGESWriter : DirPart");
  int  v[17];
  char res1[9], res2[9], label[9], snum[9];
  int  nument = themodel->Number(anent);
  if (nument == 0)
    return;
  IGESData_DirPart& DP = thedirs.ChangeValue(nument);

  v[0] = anent->TypeNumber();
  v[1] = 0;
  if (anent->HasStructure())
    v[2] = -themodel->DNum(anent->DirFieldEntity(3));
  else
    v[2] = 0;

  IGESData_DefType linet = anent->DefLineFont();
  if (linet == IGESData_DefReference)
    v[3] = -themodel->DNum(anent->DirFieldEntity(4));
  else if (linet == IGESData_DefValue)
    v[3] = anent->RankLineFont();
  else
    v[3] = 0;

  IGESData_DefList levt = anent->DefLevel();
  if (levt == IGESData_DefSeveral)
    v[4] = -themodel->DNum(anent->DirFieldEntity(5));
  else if (levt == IGESData_DefOne)
    v[4] = anent->Level();
  else
    v[4] = 0;

  IGESData_DefList viewt = anent->DefView();
  if (viewt == IGESData_DefSeveral || viewt == IGESData_DefOne)
    v[5] = themodel->DNum(anent->DirFieldEntity(6));
  else
    v[5] = 0;

  if (anent->HasTransf())
    v[6] = themodel->DNum(anent->DirFieldEntity(7));
  else
    v[6] = 0;

  if (anent->HasLabelDisplay())
    v[7] = themodel->DNum(anent->DirFieldEntity(8));
  else
    v[7] = 0;

  v[8]  = anent->BlankStatus();
  v[9]  = anent->SubordinateStatus();
  v[10] = anent->UseFlag();
  v[11] = anent->HierarchyStatus();
  v[12] = v[0];
  v[13] = anent->LineWeightNumber();

  IGESData_DefType colt = anent->DefColor();
  if (colt == IGESData_DefReference)
    v[14] = -themodel->DNum(anent->DirFieldEntity(13));
  else if (colt == IGESData_DefValue)
    v[14] = anent->RankColor();
  else
    v[14] = 0;

  v[15] = 0;
  v[16] = anent->FormNumber();

  anent->CResValues(res1, res2);
  int i;
  for (i = 0; i < 8; i++)
    label[i] = snum[i] = ' ';
  if (anent->HasShortLabel())
  {
    occ::handle<TCollection_HAsciiString> slab = anent->ShortLabel();
    for (i = 0; i < slab->Length(); i++)
      label[i] = slab->Value(i + 1);
  }
  if (anent->HasSubScriptNumber())
  {
    int sn  = anent->SubScriptNumber();
    snum[7] = '0';
    i       = 7;
    while (sn != 0)
    {
      snum[i] = (char)((sn % 10) + 48);
      sn      = sn / 10;
      i--;
    }
  }

  DP.Init(v[0],
          v[1],
          v[2],
          v[3],
          v[4],
          v[5],
          v[6],
          v[7],
          v[8],
          v[9],
          v[10],
          v[11],
          v[12],
          v[13],
          v[14],
          v[15],
          v[16],
          res1,
          res2,
          label,
          snum);

  thestep = IGESData_ReadDir;
}

void IGESData_IGESWriter::OwnParams(const occ::handle<IGESData_IGESEntity>& anent)
{
  char text[20];
  if (thesect != 3 && thestep != IGESData_ReadDir)
    throw Interface_InterfaceError("IGESWriter : OwnParams");
  thepnum.SetValue(themodel->Number(anent), thepars->Length() + 1);
  thecurr.Clear();
  Sprintf(text, "%d", anent->TypeNumber());
  AddString(text);
  thestep = IGESData_ReadOwn;
}

void IGESData_IGESWriter::Properties(const occ::handle<IGESData_IGESEntity>& anent)
{
  if (thesect != 3 && thestep != IGESData_ReadOwn)
    throw Interface_InterfaceError("IGESWriter : Properties");
  thestep = IGESData_ReadProps;
  if (!anent->ArePresentProperties())
    return;
  Send(anent->NbProperties());
  for (Interface_EntityIterator iter = anent->Properties(); iter.More(); iter.Next())
  {
    DeclareAndCast(IGESData_IGESEntity, localent, iter.Value());
    Send(localent);
  }
}

void IGESData_IGESWriter::Associativities(const occ::handle<IGESData_IGESEntity>& anent)
{
  if (thesect != 3 && thestep != IGESData_ReadOwn)
    throw Interface_InterfaceError("IGESWriter : Associativities");
  thestep = IGESData_ReadAssocs;
  if (!anent->ArePresentAssociativities() && !anent->ArePresentProperties())
    return;
  Send(anent->NbAssociativities());
  for (Interface_EntityIterator iter = anent->Associativities(); iter.More(); iter.Next())
  {
    DeclareAndCast(IGESData_IGESEntity, localent, iter.Value());
    Send(localent);
  }
  thestep = IGESData_ReadAssocs;
}

void IGESData_IGESWriter::EndEntity()
{
  if (thesect != 3 && thestep != IGESData_ReadOwn)
    throw Interface_InterfaceError("IGESWriter : EndEntity");
  AddChar(theendm);
  if (thecurr.Length() > 0)
    thepars->Append(thecurr.Moved());
  thestep = IGESData_ReadEnd;
}

void IGESData_IGESWriter::AddString(const occ::handle<TCollection_HAsciiString>& val,
                                    const int                                    more)
{
  if (val.IsNull())
    return;
  AddString(val->ToCString(), val->Length(), more);
}

void IGESData_IGESWriter::AddString(const char* val, const int lnval, const int more)
{
  int lnstr = lnval;
  if (lnstr <= 0)
    lnstr = (int)strlen(val);
  if (!thecurr.CanGet(lnstr + more + 1))
  {

    if (thesect < 3)
      thehead->Append(thecurr.Moved());
    else
      thepars->Append(thecurr.Moved());
  }
  int maxcars = (thesect == 3 ? MaxcarsP : MaxcarsG);
  int n2      = 0;

  while (lnstr > maxcars)
  {
    thecurr.Add(&val[n2], lnstr);
    if (thesect < 3)
      thehead->Append(thecurr.Moved());
    else
      thepars->Append(thecurr.Moved());
    n2 += maxcars;
    lnstr -= maxcars;
  }
  thecurr.Add(&val[n2], lnstr);
}

void IGESData_IGESWriter::AddChar(const char val, const int more)
{

  char text[2];
  text[0] = val;
  text[1] = '\0';
  if (!thecurr.CanGet(1 + more))
  {
    if (thesect < 3)
      thehead->Append(thecurr.Moved());
    else
      thepars->Append(thecurr.Moved());
  }
  thecurr.Add(text, 1);
}

void IGESData_IGESWriter::SendVoid()
{
  AddChar(thesep);
}

void IGESData_IGESWriter::Send(const int val)
{
  char text[20];
  AddChar(thesep);
  Sprintf(text, "%d", val);
  AddString(text);
}

void IGESData_IGESWriter::SendBoolean(const bool val)
{
  AddChar(thesep);
  if (val)
    AddString("1");
  else
    AddString("0");
}

void IGESData_IGESWriter::Send(const double val)
{

  char lval[24];
  AddChar(thesep);
  int lng = thefloatw.Write(val, lval);
  AddString(lval, lng);
}

void IGESData_IGESWriter::Send(const occ::handle<TCollection_HAsciiString>& val)
{
  AddChar(thesep);
  if (val.IsNull())
    return;
  int lns = val->Length();
  if (lns == 0)
    return;
  occ::handle<TCollection_HAsciiString> hol = new TCollection_HAsciiString(lns);
  hol->AssignCat("H");
  hol->AssignCat(val->ToCString());
  AddString(hol);
}

void IGESData_IGESWriter::Send(const occ::handle<IGESData_IGESEntity>& val, const bool negative)
{
  int num = 0;
  if (!val.IsNull())
    num = themodel->DNum(val);
  if (negative)
    num = -num;
  Send(num);
}

void IGESData_IGESWriter::Send(const gp_XY& val)
{
  Send(val.X());
  Send(val.Y());
}

void IGESData_IGESWriter::Send(const gp_XYZ& val)
{
  Send(val.X());
  Send(val.Y());
  Send(val.Z());
}

void IGESData_IGESWriter::SendString(const occ::handle<TCollection_HAsciiString>& val)
{
  AddChar(thesep);
  AddString(val);
}

occ::handle<NCollection_HSequence<occ::handle<TCollection_HAsciiString>>> IGESData_IGESWriter::
  SectionStrings(const int num) const
{
  occ::handle<NCollection_HSequence<occ::handle<TCollection_HAsciiString>>> res;
  if (num == 1)
    res = thestar;
  if (num == 2)
    res = thehead;
  if (num >= 3)
    res = thepars;
  return res;
}

static void writefnes(Standard_OStream& S, const char* ligne)
{
  char val;
  for (int i = 0; i < 80; i++)
  {
    if (ligne[i] == '\0')
      return;
    val = (char)(ligne[i] ^ (150 + (i & 3)));
    S << val;
  }
}

bool IGESData_IGESWriter::Print(Standard_OStream& S) const
{

  bool isGood = (S.good());
  bool fnes   = (themodew >= 10);
  if (!isGood)
    return isGood;
  char ligne[256];
#ifdef PATIENCELOG
  int lignespatience = 1000;
#endif
  char blancs[73];
  int  i;
  for (i = 0; i < MaxcarsG; i++)
    blancs[i] = ' ';
  blancs[MaxcarsG] = '\0';
  if (fnes)
  {
    for (i = 0; i < MaxcarsG; i++)
      blancs[i] = (char)(blancs[i] ^ (150 + (i & 3)));
  }

  if (thesect != 4)
    throw Interface_InterfaceError("IGESWriter not ready for Print");

  occ::handle<TCollection_HAsciiString> line;
  int                                   nbs = 1;
  if (thestar.IsNull())
  {
    if (fnes)
    {
      S << "                              ***  EUCLID/STRIM  DESKTOP CLIPBOARD  ***" << std::endl;
      writefnes(S,
                "                                                                        S0000001");
    }
    else
      S << "                                                                        S0000001";

    S << std::endl;
  }
  else
  {
    nbs = thestar->Length();
    for (i = 1; i <= nbs; i++)
    {
      char finlin[20];
      Sprintf(finlin, "S%7.7d", i);
      line = thestar->Value(i);

      if (fnes)
        writefnes(S, line->ToCString());
      else
        S << line->ToCString();

      S << &blancs[line->Length()];
      if (fnes)
        writefnes(S, finlin);
      else
        S << finlin;
      S << std::endl;
    }
  }
#ifdef PATIENCELOG
  std::cout << "Global Section : " << std::flush;
#endif
  isGood = S.good();

  int nbg = thehead->Length();
  for (i = 1; i <= nbg && isGood; i++)
  {
    char finlin[20];
    Sprintf(finlin, "G%7.7d", i);
    line = thehead->Value(i);

    if (fnes)
      writefnes(S, line->ToCString());
    else
      S << line->ToCString();

    S << &blancs[line->Length()];
    if (fnes)
      writefnes(S, finlin);
    else
      S << finlin;
    S << std::endl;
    isGood = S.good();
  }
  if (!isGood)
    return isGood;
#ifdef PATIENCELOG
  std::cout << nbg << " lines" << std::endl;
#endif

  int nbd = thedirs.Upper();
#ifdef PATIENCELOG
  std::cout << "\nDirectory section : " << nbd << " Entites" << std::endl;
#endif
  for (i = 1; i <= nbd && isGood; i++)
  {
    int  v[17];
    char res1[9], res2[9], lab[9], num[9];
    thedirs.Value(i).Values(v[0],
                            v[1],
                            v[2],
                            v[3],
                            v[4],
                            v[5],
                            v[6],
                            v[7],
                            v[8],
                            v[9],
                            v[10],
                            v[11],
                            v[12],
                            v[13],
                            v[14],
                            v[15],
                            v[16],
                            res1,
                            res2,
                            lab,
                            num);
    v[1]  = thepnum.Value(i);
    v[15] = thepnum.Value(i + 1) - thepnum.Value(i);
    Sprintf(ligne,
            "%8d%8d%8d%8d%8d%8d%8d%8d%2.2d%2.2d%2.2d%2.2dD%7.7d",
            v[0],
            v[1],
            v[2],
            v[3],
            v[4],
            v[5],
            v[6],
            v[7],
            v[8],
            v[9],
            v[10],
            v[11],
            2 * i - 1);
    if (fnes)
      writefnes(S, ligne);
    else
      S << ligne;
    S << "\n";
    Sprintf(ligne,
            "%8d%8d%8d%8d%8d%8s%8s%8s%8sD%7.7d",
            v[0],
            v[13],
            v[14],
            v[15],
            v[16],
            res1,
            res2,
            lab,
            num,
            2 * i);
    if (fnes)
      writefnes(S, ligne);
    else
      S << ligne;
    S << "\n";

    isGood = S.good();
  }
  if (!isGood)
    return isGood;

#ifdef PATIENCELOG
  std::cout << " Parameter Section : " << thepnum.Value(nbd) - 1 << " lines (* = 1000 lines) "
            << std::flush;
#endif

  blancs[MaxcarsP] = '\0';
  for (i = 1; i <= nbd && isGood; i++)
  {
    for (int j = thepnum.Value(i); j < thepnum.Value(i + 1); j++)
    {
      char finlin[32];
      Sprintf(finlin, " %7.7dP%7.7d", 2 * i - 1, j);
      line = thepars->Value(j);

      if (fnes)
        writefnes(S, line->ToCString());
      else
        S << line->ToCString();

      S << &blancs[line->Length()];
      if (fnes)
        writefnes(S, finlin);
      else
        S << finlin;
      S << std::endl;
      isGood = S.good();
#ifdef PATIENCELOG
      lignespatience--;
      if (lignespatience <= 0)
      {
        std::cout << "*" << std::flush;
        lignespatience = 1000;
      }
#endif
    }
  }
  if (!isGood)
    return isGood;

  Sprintf(ligne,
          "S%7dG%7dD%7dP%7d                                        T0000001",
          nbs,
          nbg,
          nbd * 2,
          thepnum.Value(thepnum.Length()) - 1);

  if (fnes)
    writefnes(S, ligne);
  else
    S << ligne;
  S << "\n";
  S.flush();
  isGood = S.good();
#ifdef PATIENCELOG
  std::cout << "\n Section T (lines counts) : G " << nbg << "   D " << nbd << "   P "
            << thepnum.Value(thepnum.Length()) - 1 << "   T 1" << std::endl;
#endif
  return isGood;
}
