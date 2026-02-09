#include <IGESData_DirChecker.hpp>
#include <IGESData_IGESDumper.hpp>
#include <IGESData_IGESReaderData.hpp>
#include <IGESData_IGESWriter.hpp>
#include <IGESData_ParamReader.hpp>
#include <IGESSolid_SolidInstance.hpp>
#include <IGESSolid_ToolSolidInstance.hpp>
#include <Interface_Check.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_EntityIterator.hpp>
#include <MoniTool_Macros.hpp>
#include <Interface_ShareTool.hpp>

IGESSolid_ToolSolidInstance::IGESSolid_ToolSolidInstance() = default;

void IGESSolid_ToolSolidInstance::ReadOwnParams(const occ::handle<IGESSolid_SolidInstance>& ent,
                                                const occ::handle<IGESData_IGESReaderData>& IR,
                                                IGESData_ParamReader& PR) const
{
  occ::handle<IGESData_IGESEntity> tempEntity;

  PR.ReadEntity(IR, PR.Current(), "Solid Entity", tempEntity);

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(), ent);
  ent->Init(tempEntity);
}

void IGESSolid_ToolSolidInstance::WriteOwnParams(const occ::handle<IGESSolid_SolidInstance>& ent,
                                                 IGESData_IGESWriter& IW) const
{
  IW.Send(ent->Entity());
}

void IGESSolid_ToolSolidInstance::OwnShared(const occ::handle<IGESSolid_SolidInstance>& ent,
                                            Interface_EntityIterator&                   iter) const
{
  iter.GetOneItem(ent->Entity());
}

void IGESSolid_ToolSolidInstance::OwnCopy(const occ::handle<IGESSolid_SolidInstance>& another,
                                          const occ::handle<IGESSolid_SolidInstance>& ent,
                                          Interface_CopyTool&                         TC) const
{
  DeclareAndCast(IGESData_IGESEntity, tempEntity, TC.Transferred(another->Entity()));
  ent->Init(tempEntity);
}

IGESData_DirChecker IGESSolid_ToolSolidInstance::DirChecker(
  const occ::handle<IGESSolid_SolidInstance>&) const
{
  IGESData_DirChecker DC(430, 0, 1);

  DC.Structure(IGESData_DefVoid);
  DC.LineFont(IGESData_DefAny);
  DC.Color(IGESData_DefAny);

  DC.GraphicsIgnored(1);
  return DC;
}

void IGESSolid_ToolSolidInstance::OwnCheck(const occ::handle<IGESSolid_SolidInstance>&,
                                           const Interface_ShareTool&,
                                           occ::handle<Interface_Check>&) const
{
}

void IGESSolid_ToolSolidInstance::OwnDump(const occ::handle<IGESSolid_SolidInstance>& ent,
                                          const IGESData_IGESDumper&                  dumper,
                                          Standard_OStream&                           S,
                                          const int                                   level) const
{
  S << "IGESSolid_SolidInstance\n"
    << "Solid entity : ";
  dumper.Dump(ent->Entity(), S, (level <= 4) ? 0 : 1);
  S << std::endl;
}
