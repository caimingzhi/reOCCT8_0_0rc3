

#include <IGESData_ColorEntity.hpp>
#include <IGESData_FileRecognizer.hpp>
#include <IGESData_IGESEntity.hpp>
#include <IGESData_IGESModel.hpp>
#include <IGESData_IGESReaderData.hpp>
#include <IGESData_IGESReaderTool.hpp>
#include <IGESData_LabelDisplayEntity.hpp>
#include <IGESData_LevelListEntity.hpp>
#include <IGESData_LineFontEntity.hpp>
#include <IGESData_ParamCursor.hpp>
#include <IGESData_ParamReader.hpp>
#include <IGESData_Protocol.hpp>
#include <IGESData_ReadWriteModule.hpp>
#include <IGESData_TransfEntity.hpp>
#include <IGESData_UndefinedEntity.hpp>
#include <IGESData_ViewKindEntity.hpp>
#include <Interface_Check.hpp>
#include <Interface_InterfaceModel.hpp>
#include <MoniTool_Macros.hpp>
#include <Interface_ParamList.hpp>
#include <Interface_ReaderModule.hpp>
#include <Message_Msg.hpp>
#include <Standard_Transient.hpp>
#include <TCollection_HAsciiString.hpp>

#include <cstdio>

IGESData_IGESReaderTool::IGESData_IGESReaderTool(const occ::handle<IGESData_IGESReaderData>& reader,
                                                 const occ::handle<IGESData_Protocol>& protocol)
    : theglib(protocol),
      therlib(protocol)
{
  SetData(reader, protocol);
}

void IGESData_IGESReaderTool::Prepare(const occ::handle<IGESData_FileRecognizer>& reco)
{
  DeclareAndCast(IGESData_IGESReaderData, igesdat, Data());
  igesdat->SetEntityNumbers();
  thereco = reco;
  SetEntities();
  thelist = igesdat->Params(0);
}

bool IGESData_IGESReaderTool::Recognize(const int                        num,
                                        occ::handle<Interface_Check>&    ach,
                                        occ::handle<Standard_Transient>& ent)
{
  DeclareAndCast(IGESData_IGESReaderData, igesdat, Data());
  thecnum = num;
  thectyp = igesdat->DirType(num);
  occ::handle<IGESData_IGESEntity> anent;
  bool                             res = false;

  if (!thereco.IsNull())
    res = thereco->Evaluate(thectyp, anent);
  if (res)
    ent = anent;

  else
    res = RecognizeByLib(num, theglib, therlib, ach, ent);
  return res;
}

void IGESData_IGESReaderTool::BeginRead(const occ::handle<Interface_InterfaceModel>& amodel)
{
  DeclareAndCast(IGESData_IGESModel, amod, amodel);
  DeclareAndCast(IGESData_IGESReaderData, igesdat, Data());
  const IGESData_GlobalSection& gs = igesdat->GlobalSection();
  amod->SetStartSection(igesdat->StartSection(), false);
  amod->SetGlobalSection(gs);
  occ::handle<Interface_Check> glob = amod->GlobalCheck();
  glob->GetMessages(igesdat->GlobalCheck());
  amod->SetGlobalCheck(glob);
  themaxweight  = gs.MaxLineWeight();
  thegradweight = gs.LineWeightGrad();
  if (thegradweight > 0)
  {
    themaxweight  = themaxweight / thegradweight;
    thegradweight = 1;
  }
  thedefweight = igesdat->DefaultLineWeight();
}

bool IGESData_IGESReaderTool::AnalyseRecord(const int                              num,
                                            const occ::handle<Standard_Transient>& anent,
                                            occ::handle<Interface_Check>&          ach)
{

  occ::handle<TCollection_HAsciiString> lab;

  DeclareAndCast(IGESData_IGESEntity, ent, anent);
  DeclareAndCast(IGESData_IGESReaderData, igesdat, Data());

  ent->Clear();

  DeclareAndCast(IGESData_UndefinedEntity, undent, ent);
  if (!undent.IsNull())
  {
    IGESData_DirPart DP = igesdat->DirPart(num);
    undent->ReadDir(igesdat, DP, ach);
    ReadDir(ent, igesdat, DP, ach);
  }
  else
    ReadDir(ent, igesdat, igesdat->DirPart(num), ach);

  thestep = IGESData_ReadDir;

  int nbpar = Data()->NbParams(num);
  int n0par = (num == 1 ? 1 : (Data()->ParamFirstRank(num - 1) + 1));
  if (nbpar < 1)
  {

    if (!undent.IsNull())
      return true;

    Message_Msg Msg27("XSTEP_27");
    Msg27.Arg(thecnum);
    ach->SendFail(Msg27);
    return false;
  }
  const Interface_FileParameter& FP = thelist->Value(n0par);
  if ((FP.ParamType() != Interface_ParamInteger) || (atoi(FP.CValue()) != ent->TypeNumber()))
  {

    Message_Msg Msg28("XSTEP_28");
    Msg28.Arg(thecnum);
    ach->SendFail(Msg28);
    return false;
  }

  IGESData_ParamReader PR(thelist, ach, n0par, nbpar, num);
  thestep = IGESData_ReadOwn;
  ReadOwnParams(ent, igesdat, PR);
  if ((thestep = PR.Stage()) == IGESData_ReadOwn)
    PR.NextStage();
  if (thestep == IGESData_ReadEnd)
  {
    if (!PR.IsCheckEmpty())
      ach = PR.Check();
    return (!ach->HasFailed());
  }

  ReadAssocs(ent, igesdat, PR);
  if ((thestep = PR.Stage()) == IGESData_ReadAssocs)
    PR.NextStage();
  if (thestep == IGESData_ReadEnd)
  {
    if (!PR.IsCheckEmpty())
      ach = PR.Check();
    return (!ach->HasFailed());
  }
  ReadProps(ent, igesdat, PR);

  if (!PR.IsCheckEmpty())
    ach = PR.Check();
  return (!ach->HasFailed());
}

void IGESData_IGESReaderTool::EndRead(const occ::handle<Interface_InterfaceModel>&) {}

void IGESData_IGESReaderTool::ReadDir(const occ::handle<IGESData_IGESEntity>&     ent,
                                      const occ::handle<IGESData_IGESReaderData>& IR,
                                      const IGESData_DirPart&                     DP,
                                      occ::handle<Interface_Check>&               ach) const
{

  int  v[17]   = {};
  char nom[9]  = {};
  char snum[9] = {}, theRes1[9] = {}, theRes2[9] = {};
  DP.Values(v[0],
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
            theRes1,
            theRes2,
            nom,
            snum);

  ent->InitTypeAndForm(v[0], v[16]);
  occ::handle<IGESData_IGESEntity> fieldent, Structure, fieldlab;
  if (v[2] < 0)
    Structure = GetCasted(IGESData_IGESEntity, IR->BoundEntity((1 - v[2]) / 2));

  occ::handle<IGESData_LineFontEntity> Lnf;
  if (v[3] < 0)
  {
    fieldent = GetCasted(IGESData_IGESEntity, IR->BoundEntity((1 - v[3]) / 2));
    Lnf      = GetCasted(IGESData_LineFontEntity, fieldent);
    if (Lnf.IsNull())
    {

      Message_Msg Msg29("XSTEP_29");
      Msg29.Arg(thecnum);
      Msg29.Arg(thectyp.Type());
      ach->SendWarning(Msg29);
      ent->InitDirFieldEntity(4, fieldent);
    }
    else
      ent->InitLineFont(Lnf);
  }
  else
    ent->InitLineFont(Lnf, v[3]);

  occ::handle<IGESData_LevelListEntity> Lvs;
  if (v[4] < 0)
  {
    fieldent = GetCasted(IGESData_IGESEntity, IR->BoundEntity((1 - v[4]) / 2));
    Lvs      = GetCasted(IGESData_LevelListEntity, fieldent);
    if (Lvs.IsNull())
    {

      Message_Msg Msg30("XSTEP_30");
      Msg30.Arg(thecnum);
      Msg30.Arg(thectyp.Type());
      ach->SendWarning(Msg30);
      ent->InitDirFieldEntity(5, fieldent);
    }
    else
      ent->InitLevel(Lvs, -1);
  }
  else
    ent->InitLevel(Lvs, v[4]);

  if (v[5] != 0)
  {
    fieldent = GetCasted(IGESData_IGESEntity, IR->BoundEntity((1 + v[5]) / 2));
    DeclareAndCast(IGESData_ViewKindEntity, View, fieldent);
    if (View.IsNull())
    {

      Message_Msg Msg31("XSTEP_31");
      Msg31.Arg(thecnum);
      Msg31.Arg(thectyp.Type());
      ach->SendWarning(Msg31);
      ent->InitDirFieldEntity(6, fieldent);
    }
    else
      ent->InitView(View);
  }

  if (v[6] != 0)
  {
    fieldent = GetCasted(IGESData_IGESEntity, IR->BoundEntity((1 + v[6]) / 2));
    DeclareAndCast(IGESData_TransfEntity, Transf, fieldent);
    if (Transf.IsNull())
    {

      Message_Msg Msg32("XSTEP_32");
      Msg32.Arg(thecnum);
      Msg32.Arg(thectyp.Type());
      ach->SendWarning(Msg32);
      ent->InitDirFieldEntity(7, fieldent);
    }
    else
      ent->InitTransf(Transf);
  }

  occ::handle<IGESData_LabelDisplayEntity> Lbd;
  if (v[7] != 0)
  {
    fieldlab = GetCasted(IGESData_IGESEntity, IR->BoundEntity((1 + v[7]) / 2));
    Lbd      = GetCasted(IGESData_LabelDisplayEntity, fieldent);
    if (Lbd.IsNull())
    {

      Message_Msg Msg33("XSTEP_33");
      Msg33.Arg(thecnum);
      Msg33.Arg(thectyp.Type());
      ach->SendWarning(Msg33);
    }
  }

  ent->InitStatus(v[8], v[9], v[10], v[11]);

  int LWeightNum = v[13];

  occ::handle<IGESData_ColorEntity> Color;
  if (v[14] < 0)
  {
    fieldent = GetCasted(IGESData_IGESEntity, IR->BoundEntity((1 - v[14]) / 2));
    Color    = GetCasted(IGESData_ColorEntity, fieldent);

    if (Color.IsNull())
    {

      Message_Msg Msg34("XSTEP_34");
      Msg34.Arg(thecnum);
      Msg34.Arg(thectyp.Type());
      ach->SendWarning(Msg34);
      ent->InitDirFieldEntity(13, Color);
    }
    else
      ent->InitColor(Color);
  }
  else
    ent->InitColor(Color, v[14]);

  ent->InitMisc(Structure, Lbd, LWeightNum);
  ent->InitDirFieldEntity(8, fieldlab);

  occ::handle<TCollection_HAsciiString> ShortLabel;
  int                                   SubScriptN = -1;
  int                                   iacar      = 0;
  int                                   i;
  for (i = 0; i < 8; i++)
  {
    if (nom[i] > ' ')
      iacar = 1;
  }
  if (iacar > 0)
    ShortLabel = new TCollection_HAsciiString(nom);
  iacar = 0;
  for (i = 0; i < 8; i++)
  {
    if (snum[i] > ' ')
      iacar = 1;
    if (snum[i] == 0)
      break;
  }
  if (iacar > 0)
    SubScriptN = atoi(snum);
  ent->SetLabel(ShortLabel, SubScriptN);

  ent->SetLineWeight(IR->DefaultLineWeight(), themaxweight, thegradweight);
}

void IGESData_IGESReaderTool::ReadOwnParams(const occ::handle<IGESData_IGESEntity>&     ent,
                                            const occ::handle<IGESData_IGESReaderData>& IR,
                                            IGESData_ParamReader&                       PR) const
{
  occ::handle<Interface_Check>        ach = new Interface_Check();
  occ::handle<Interface_ReaderModule> imodule;
  int                                 CN;

  if (therlib.Select(ent, imodule, CN))
  {
    occ::handle<IGESData_ReadWriteModule> module =
      occ::down_cast<IGESData_ReadWriteModule>(imodule);
    module->ReadOwnParams(CN, ent, IR, PR);
  }
  else if (ent.IsNull())
  {

    Message_Msg Msg35("XSTEP_35");
    Msg35.Arg(thecnum);
    ach->SendFail(Msg35);
  }
  else if (ent->IsKind(STANDARD_TYPE(IGESData_UndefinedEntity)))
  {
    DeclareAndCast(IGESData_UndefinedEntity, undent, ent);
    undent->ReadOwnParams(IR, PR);
  }
  else
  {

    Message_Msg Msg36("XSTEP_36");
    Msg36.Arg(thecnum);
    ach->SendFail(Msg36);
  }
}

void IGESData_IGESReaderTool::ReadProps(const occ::handle<IGESData_IGESEntity>&     ent,
                                        const occ::handle<IGESData_IGESReaderData>& IR,
                                        IGESData_ParamReader&                       PR) const
{

  Message_Msg Msg38("XSTEP_38");

  occ::handle<Interface_Check> ach = new Interface_Check;
  Msg38.Arg(thecnum);
  Msg38.Arg(thectyp.Type());
  if (PR.Stage() != IGESData_ReadProps)
    ach->SendFail(Msg38);
  int ncur = PR.CurrentNumber();
  int nbp  = PR.NbParams();
  if (ncur == nbp + 1)
  {
    PR.EndAll();
    return;
  }
  else if (ncur > nbp || ncur == 0)
    ach->SendWarning(Msg38);

  int nbprops = 0;
  if (!PR.DefinedElseSkip())
    return;
  if (!PR.ReadInteger(ncur, nbprops))
  {
    Message_Msg Msg221("XSTEP_221");
    PR.SendFail(Msg221);
    return;
  }
  if (nbprops == 0)
  {
    return;
  }

  ++ncur;
  Interface_EntityList props;
  if (PR.ReadEntList(IR, PR.CurrentList(nbprops), Msg38, props, false))
    ent->LoadProperties(props);
}

void IGESData_IGESReaderTool::ReadAssocs(const occ::handle<IGESData_IGESEntity>&     ent,
                                         const occ::handle<IGESData_IGESReaderData>& IR,
                                         IGESData_ParamReader&                       PR) const
{

  Message_Msg Msg37("XSTEP_37");

  Msg37.Arg(thecnum);
  Msg37.Arg(thectyp.Type());
  occ::handle<Interface_Check> ach = new Interface_Check;
  if (PR.Stage() != IGESData_ReadAssocs)
    ach->SendFail(Msg37);
  int ncur = PR.CurrentNumber();
  int nbp  = PR.NbParams();
  if (ncur == nbp + 1)
  {
    PR.EndAll();
    return;
  }
  else if (ncur > nbp || ncur == 0)
    ach->SendWarning(Msg37);

  int nbassocs = 0;
  if (!PR.DefinedElseSkip())
    return;
  if (!PR.ReadInteger(PR.Current(), nbassocs))
  {
    Message_Msg Msg220("XSTEP_220");
    PR.SendFail(Msg220);
    return;
  }
  if (nbassocs == 0)
    return;
  Interface_EntityList assocs;
  if (PR.ReadEntList(IR, PR.CurrentList(nbassocs), Msg37, assocs, false))
    ent->LoadAssociativities(assocs);
}
