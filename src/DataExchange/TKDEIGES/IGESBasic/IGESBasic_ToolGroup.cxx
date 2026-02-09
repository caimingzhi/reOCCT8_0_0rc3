#include <IGESBasic_Group.hpp>
#include <IGESBasic_ToolGroup.hpp>
#include <IGESData_DirChecker.hpp>
#include <IGESData_Dump.hpp>
#include <IGESData_IGESEntity.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <IGESData_IGESDumper.hpp>
#include <IGESData_IGESReaderData.hpp>
#include <IGESData_IGESWriter.hpp>
#include <IGESData_ParamReader.hpp>
#include <Interface_Check.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_EntityIterator.hpp>
#include <MoniTool_Macros.hpp>
#include <Interface_ShareTool.hpp>
#include <Message_Msg.hpp>
#include <Standard_DomainError.hpp>

IGESBasic_ToolGroup::IGESBasic_ToolGroup() = default;

void IGESBasic_ToolGroup::ReadOwnParams(const occ::handle<IGESBasic_Group>&         ent,
                                        const occ::handle<IGESData_IGESReaderData>& IR,
                                        IGESData_ParamReader&                       PR) const
{

  int nbval = 0;

  occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>> EntArray;
  if (PR.ReadInteger(PR.Current(), nbval))
  {
    Message_Msg Msg203("XSTEP_203");
    Msg203.Arg(1);
    PR.ReadEnts(IR, PR.CurrentList(nbval), Msg203, EntArray);
  }
  else
  {
    Message_Msg Msg202("XSTEP_202");
    Msg202.Arg(1);
    PR.SendFail(Msg202);
  }

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(), ent);
  ent->Init(EntArray);
}

void IGESBasic_ToolGroup::WriteOwnParams(const occ::handle<IGESBasic_Group>& ent,
                                         IGESData_IGESWriter&                IW) const
{
  int upper = ent->NbEntities();
  IW.Send(upper);
  for (int i = 1; i <= upper; i++)
    IW.Send(ent->Entity(i));
}

void IGESBasic_ToolGroup::OwnShared(const occ::handle<IGESBasic_Group>& ent,
                                    Interface_EntityIterator&           iter) const
{
  int upper = ent->NbEntities();
  for (int i = 1; i <= upper; i++)
    iter.GetOneItem(ent->Entity(i));
}

void IGESBasic_ToolGroup::OwnCopy(const occ::handle<IGESBasic_Group>& another,
                                  const occ::handle<IGESBasic_Group>& ent,
                                  Interface_CopyTool&                 TC) const
{
  int lower, upper;
  lower = 1;
  upper = another->NbEntities();
  occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>> EntArray =
    new NCollection_HArray1<occ::handle<IGESData_IGESEntity>>(lower, upper);
  for (int i = lower; i <= upper; i++)
  {
    DeclareAndCast(IGESData_IGESEntity, myentity, TC.Transferred(another->Entity(i)));
    EntArray->SetValue(i, myentity);
  }
  ent->Init(EntArray);
}

bool IGESBasic_ToolGroup::OwnCorrect(const occ::handle<IGESBasic_Group>& ent) const
{
  int ianul = 0;
  int i, nbtrue = 0, nb = ent->NbEntities();
  for (i = 1; i <= nb; i++)
  {
    occ::handle<IGESData_IGESEntity> val = ent->Entity(i);
    if (val.IsNull())
      ianul++;
    else if (val->TypeNumber() == 0)
      ianul++;
  }
  if (ianul == 0)
    return false;
  occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>> EntArray;
  if (ianul < nb)
    EntArray = new NCollection_HArray1<occ::handle<IGESData_IGESEntity>>(1, nb - ianul);
  for (i = 1; i <= nb; i++)
  {
    occ::handle<IGESData_IGESEntity> val = ent->Entity(i);
    if (val.IsNull())
      continue;
    else if (val->TypeNumber() == 0)
      continue;
    nbtrue++;
    EntArray->SetValue(nbtrue, ent->Entity(i));
  }
  ent->Init(EntArray);
  return true;
}

IGESData_DirChecker IGESBasic_ToolGroup::DirChecker(const occ::handle<IGESBasic_Group>&) const
{
  IGESData_DirChecker DC(402, 1);
  DC.Structure(IGESData_DefVoid);
  DC.GraphicsIgnored();
  DC.BlankStatusIgnored();
  DC.HierarchyStatusIgnored();
  return DC;
}

void IGESBasic_ToolGroup::OwnCheck(const occ::handle<IGESBasic_Group>& ent,
                                   const Interface_ShareTool&,
                                   occ::handle<Interface_Check>&) const
{
  bool ianul = false;
  int  i, nb = ent->NbEntities();
  for (i = 1; i <= nb; i++)
  {
    occ::handle<IGESData_IGESEntity> val = ent->Entity(i);
    if (val.IsNull())
      ianul = true;
    else if (val->TypeNumber() == 0)
      ianul = true;
    if (ianul)
    {
      break;
    }
  }
}

void IGESBasic_ToolGroup::OwnDump(const occ::handle<IGESBasic_Group>& ent,
                                  const IGESData_IGESDumper&          dumper,
                                  Standard_OStream&                   S,
                                  const int                           level) const
{
  S << "IGESBasic_Group\n"
    << "Entries in the Group : ";
  IGESData_DumpEntities(S, dumper, level, 1, ent->NbEntities(), ent->Entity);
  S << std::endl;
}
