

#include <IGESData_ColorEntity.hpp>
#include <IGESData_IGESReaderData.hpp>
#include <IGESData_IGESWriter.hpp>
#include <IGESData_LabelDisplayEntity.hpp>
#include <IGESData_LevelListEntity.hpp>
#include <IGESData_LineFontEntity.hpp>
#include <IGESData_ParamReader.hpp>
#include <IGESData_TransfEntity.hpp>
#include <IGESData_UndefinedEntity.hpp>
#include <IGESData_ViewKindEntity.hpp>
#include <Interface_Check.hpp>
#include <MoniTool_Macros.hpp>
#include <Interface_UndefinedContent.hpp>
#include <Message_Msg.hpp>
#include <Standard_Type.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESData_UndefinedEntity, IGESData_IGESEntity)

IGESData_UndefinedEntity::IGESData_UndefinedEntity()
{
  thecont = new Interface_UndefinedContent;
}

occ::handle<Interface_UndefinedContent> IGESData_UndefinedEntity::UndefinedContent() const
{
  return thecont;
}

occ::handle<Interface_UndefinedContent> IGESData_UndefinedEntity::ChangeableContent()
{
  return thecont;
}

void IGESData_UndefinedEntity::SetNewContent(const occ::handle<Interface_UndefinedContent>& cont)
{
  thecont = cont;
}

bool IGESData_UndefinedEntity::IsOKDirPart() const
{
  return (thedstat == 0);
}

int IGESData_UndefinedEntity::DirStatus() const
{
  return thedstat;
}

void IGESData_UndefinedEntity::SetOKDirPart()
{
  thedstat = 0;
}

IGESData_DefType IGESData_UndefinedEntity::DefLineFont() const
{
  int st = ((thedstat / 4) & 3);
  if (st == 0)
    return IGESData_IGESEntity::DefLineFont();
  else if (st == 1)
    return IGESData_ErrorVal;
  else
    return IGESData_ErrorRef;
}

IGESData_DefList IGESData_UndefinedEntity::DefLevel() const
{
  int st = ((thedstat / 16) & 3);
  if (st == 0)
    return IGESData_IGESEntity::DefLevel();
  else if (st == 1)
    return IGESData_ErrorOne;
  else
    return IGESData_ErrorSeveral;
}

IGESData_DefList IGESData_UndefinedEntity::DefView() const
{
  int st = ((thedstat / 64) & 3);
  if (st == 0)
    return IGESData_IGESEntity::DefView();
  else if (st == 1)
    return IGESData_ErrorOne;
  else
    return IGESData_ErrorSeveral;
}

IGESData_DefType IGESData_UndefinedEntity::DefColor() const
{
  int st = ((thedstat / 256) & 3);
  if (st == 0)
    return IGESData_IGESEntity::DefColor();
  else if (st == 1)
    return IGESData_ErrorVal;
  else
    return IGESData_ErrorRef;
}

bool IGESData_UndefinedEntity::HasSubScriptNumber() const
{
  int st = ((thedstat / 1024) & 1);
  if (st == 0)
    return IGESData_IGESEntity::HasSubScriptNumber();
  else
    return false;
}

bool IGESData_UndefinedEntity::ReadDir(const occ::handle<IGESData_IGESReaderData>& IR,
                                       IGESData_DirPart&                           DP,
                                       occ::handle<Interface_Check>&               ach)
{

  int  v[17];
  char res1[9], res2[9], lab[9], subs[9];
  int  max = 2 * IR->NbRecords();
  thedstat = 0;

  occ::handle<IGESData_IGESEntity> anent;
  bool                             iapb;
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
            res1,
            res2,
            lab,
            subs);

  iapb = false;
  if (v[3] < -max)
    iapb = true;
  else if (v[3] < 0)
  {
    anent = GetCasted(IGESData_IGESEntity, IR->BoundEntity((1 - v[3]) / 2));
    if (!anent->IsKind(STANDARD_TYPE(IGESData_LineFontEntity)))
      iapb = true;
  }

  if (iapb)
  {
    Message_Msg Msg60("XSTEP_60");
    ach->SendFail(Msg60);
    thedstat += 8;
    v[3] = 0;
  }

  iapb = false;
  if (v[4] < -max)
    iapb = true;
  else if (v[4] < 0)
  {
    anent = GetCasted(IGESData_IGESEntity, IR->BoundEntity((1 - v[4]) / 2));
    if (!anent->IsKind(STANDARD_TYPE(IGESData_LevelListEntity)))
      iapb = true;
  }

  if (iapb)
  {
    Message_Msg Msg61("XSTEP_61");
    ach->SendFail(Msg61);
    thedstat += 32;
    v[3] = 0;
  }

  iapb = false;
  if (v[5] < 0 || v[5] > max)
    iapb = true;
  else if (v[5] > 0)
  {
    anent = GetCasted(IGESData_IGESEntity, IR->BoundEntity((1 + v[5]) / 2));
    if (!anent->IsKind(STANDARD_TYPE(IGESData_ViewKindEntity)))
      iapb = true;
  }

  if (iapb)
  {
    Message_Msg Msg62("XSTEP_62");
    ach->SendFail(Msg62);
    thedstat += 128;
    v[5] = 0;
  }

  iapb = false;
  if (v[6] < 0 || v[6] > max)
    iapb = true;
  else if (v[6] > 0)
  {
    anent = GetCasted(IGESData_IGESEntity, IR->BoundEntity((1 + v[6]) / 2));
    if (!anent->IsKind(STANDARD_TYPE(IGESData_TransfEntity)))
      iapb = true;
  }

  if (iapb)
  {
    Message_Msg Msg63("XSTEP_63");
    ach->SendFail(Msg63);
    thedstat |= 1;
    v[6] = 0;
  }

  iapb = false;
  if (v[7] < 0 || v[7] > max)
    iapb = true;
  else if (v[7] > 0)
  {
    anent = GetCasted(IGESData_IGESEntity, IR->BoundEntity((1 + v[7]) / 2));
    if (!anent->IsKind(STANDARD_TYPE(IGESData_LabelDisplayEntity)))
      iapb = true;
  }

  if (iapb)
  {
    Message_Msg Msg64("XSTEP_64");
    ach->SendFail(Msg64);
    thedstat |= 1;
    v[7] = 0;
  }

  iapb = false;
  if (v[14] < -max || v[14] > max)
    iapb = true;
  else if (v[14] < 0)
  {
    anent = GetCasted(IGESData_IGESEntity, IR->BoundEntity((1 - v[14]) / 2));
    if (!anent->IsKind(STANDARD_TYPE(IGESData_ColorEntity)))
    {
      thedstat += 512;
      v[14] = 0;
    }
  }

  if (iapb)
  {
    Message_Msg Msg70("XSTEP_70");
    ach->SendFail(Msg70);
    thedstat += 512;
    v[14] = 0;
  }

  iapb = false;
  int i;
  for (i = 0; i < 8; i++)
  {
    if (subs[i] == '\0')
      break;
    if (subs[i] != ' ' && (subs[i] < 48 || subs[i] > 57))
      iapb = true;
  }

  if (iapb)
  {
    Message_Msg Msg72("XSTEP_72");
    ach->SendFail(Msg72);
    thedstat += 1024;
    for (i = 0; i < 8; i++)
      subs[i] = ' ';
  }

  if (thedstat == 0)
    return true;
  else
  {
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
            lab,
            subs);
    return false;
  }
}

void IGESData_UndefinedEntity::ReadOwnParams(const occ::handle<IGESData_IGESReaderData>&,
                                             IGESData_ParamReader& PR)
{
  int nb = PR.NbParams();

  thecont->Reservate(nb, nb);
  for (int i = 1; i <= nb; i++)
  {
    Interface_ParamType ptyp = PR.ParamType(i);

    thecont->AddLiteral(ptyp, new TCollection_HAsciiString(PR.ParamValue(i)));
  }
  PR.SetCurrentNumber(nb + 1);
}

void IGESData_UndefinedEntity::WriteOwnParams(IGESData_IGESWriter& IW) const
{
  int nb = thecont->NbParams();
  for (int i = 1; i <= nb; i++)
  {
    Interface_ParamType ptyp = thecont->ParamType(i);
    if (ptyp == Interface_ParamVoid)
      IW.SendVoid();
    else if (thecont->IsParamEntity(i))
    {
      DeclareAndCast(IGESData_IGESEntity, anent, thecont->ParamEntity(i));
      IW.Send(anent);
    }
    else
      IW.SendString(thecont->ParamValue(i));
  }
}
