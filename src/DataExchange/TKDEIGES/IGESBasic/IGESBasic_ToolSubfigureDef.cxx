#include <IGESBasic_SubfigureDef.hpp>
#include <IGESBasic_ToolSubfigureDef.hpp>
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
#include <TCollection_HAsciiString.hpp>

IGESBasic_ToolSubfigureDef::IGESBasic_ToolSubfigureDef() = default;

void IGESBasic_ToolSubfigureDef::ReadOwnParams(const occ::handle<IGESBasic_SubfigureDef>&  ent,
                                               const occ::handle<IGESData_IGESReaderData>& IR,
                                               IGESData_ParamReader&                       PR) const
{

  Message_Msg Msg209("XSTEP_209");

  int                                   tempDepth;
  occ::handle<TCollection_HAsciiString> tempName;

  int                                                                nbval = 0;
  occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>> EntArray;

  if (!PR.ReadInteger(PR.Current(), tempDepth))
  {
    Message_Msg Msg208("XSTEP_208");
    PR.SendFail(Msg208);
  }
  PR.ReadText(PR.Current(), Msg209, tempName);
  if (PR.ReadInteger(PR.Current(), nbval))
  {
    Message_Msg Msg211("XSTEP_211");
    PR.ReadEnts(IR, PR.CurrentList(nbval), Msg211, EntArray);
  }
  else
  {
    Message_Msg Msg210("XSTEP_210");
    PR.SendFail(Msg210);
  }
  DirChecker(ent).CheckTypeAndForm(PR.CCheck(), ent);
  ent->Init(tempDepth, tempName, EntArray);
}

void IGESBasic_ToolSubfigureDef::WriteOwnParams(const occ::handle<IGESBasic_SubfigureDef>& ent,
                                                IGESData_IGESWriter&                       IW) const
{
  int nb = ent->NbEntities();

  IW.Send(ent->Depth());
  IW.Send(ent->Name());
  IW.Send(nb);
  for (int i = 1; i <= nb; i++)
    IW.Send(ent->AssociatedEntity(i));
}

void IGESBasic_ToolSubfigureDef::OwnShared(const occ::handle<IGESBasic_SubfigureDef>& ent,
                                           Interface_EntityIterator&                  iter) const
{
  int nb = ent->NbEntities();
  for (int i = 1; i <= nb; i++)
    iter.GetOneItem(ent->AssociatedEntity(i));
}

void IGESBasic_ToolSubfigureDef::OwnCopy(const occ::handle<IGESBasic_SubfigureDef>& another,
                                         const occ::handle<IGESBasic_SubfigureDef>& ent,
                                         Interface_CopyTool&                        TC) const
{
  int                                   lower, upper;
  int                                   aDepth = another->Depth();
  occ::handle<TCollection_HAsciiString> aName  = new TCollection_HAsciiString(another->Name());

  lower = 1;
  upper = another->NbEntities();
  occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>> EntArray =
    new NCollection_HArray1<occ::handle<IGESData_IGESEntity>>(lower, upper);
  for (int i = lower; i <= upper; i++)
  {
    DeclareAndCast(IGESData_IGESEntity, myentity, TC.Transferred(another->AssociatedEntity(i)));
    EntArray->SetValue(i, myentity);
  }
  ent->Init(aDepth, aName, EntArray);
}

IGESData_DirChecker IGESBasic_ToolSubfigureDef::DirChecker(
  const occ::handle<IGESBasic_SubfigureDef>& ent) const
{
  IGESData_DirChecker DC(308, 0);
  DC.Structure(IGESData_DefVoid);
  if (ent->HierarchyStatus() == 1)
    DC.GraphicsIgnored(01);

  else
  {
    DC.BlankStatusIgnored();
  }
  DC.UseFlagRequired(02);
  return DC;
}

void IGESBasic_ToolSubfigureDef::OwnCheck(const occ::handle<IGESBasic_SubfigureDef>&,
                                          const Interface_ShareTool&,
                                          occ::handle<Interface_Check>&) const
{
}

void IGESBasic_ToolSubfigureDef::OwnDump(const occ::handle<IGESBasic_SubfigureDef>& ent,
                                         const IGESData_IGESDumper&                 dumper,
                                         Standard_OStream&                          S,
                                         const int                                  level) const
{
  S << "IGESBasic_SubfigureDef\n"
    << "Depth of the subfigure : " << ent->Depth() << "\n"
    << "Name of subfigure : ";
  IGESData_DumpString(S, ent->Name());
  S << "\n"
    << "The Associated Entities : ";
  IGESData_DumpEntities(S, dumper, level, 1, ent->NbEntities(), ent->AssociatedEntity);
  S << std::endl;
}
