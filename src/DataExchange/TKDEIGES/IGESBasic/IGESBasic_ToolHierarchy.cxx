#include <IGESBasic_Hierarchy.hpp>
#include <IGESBasic_ToolHierarchy.hpp>
#include <IGESData_DirChecker.hpp>
#include <IGESData_IGESDumper.hpp>
#include <IGESData_IGESReaderData.hpp>
#include <IGESData_IGESWriter.hpp>
#include <IGESData_ParamReader.hpp>
#include <Interface_Check.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_ShareTool.hpp>

IGESBasic_ToolHierarchy::IGESBasic_ToolHierarchy() = default;

void IGESBasic_ToolHierarchy::ReadOwnParams(const occ::handle<IGESBasic_Hierarchy>& ent,
                                            const occ::handle<IGESData_IGESReaderData>&,
                                            IGESData_ParamReader& PR) const
{
  int tempNbPropertyValues;
  int tempLineFont;
  int tempView;
  int tempEntityLevel;
  int tempBlankStatus;
  int tempLineWeight;
  int tempColorNum;

  PR.ReadInteger(PR.Current(), "No. of Property values", tempNbPropertyValues);
  PR.ReadInteger(PR.Current(), "LineFont", tempLineFont);
  PR.ReadInteger(PR.Current(), "View", tempView);
  PR.ReadInteger(PR.Current(), "Entity level", tempEntityLevel);
  PR.ReadInteger(PR.Current(), "Blank status", tempBlankStatus);
  PR.ReadInteger(PR.Current(), "Line weight", tempLineWeight);
  PR.ReadInteger(PR.Current(), "Color number", tempColorNum);

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(), ent);
  ent->Init(tempNbPropertyValues,
            tempLineFont,
            tempView,
            tempEntityLevel,
            tempBlankStatus,
            tempLineWeight,
            tempColorNum);
}

void IGESBasic_ToolHierarchy::WriteOwnParams(const occ::handle<IGESBasic_Hierarchy>& ent,
                                             IGESData_IGESWriter&                    IW) const
{
  IW.Send(ent->NbPropertyValues());
  IW.Send(ent->NewLineFont());
  IW.Send(ent->NewView());
  IW.Send(ent->NewEntityLevel());
  IW.Send(ent->NewBlankStatus());
  IW.Send(ent->NewLineWeight());
  IW.Send(ent->NewColorNum());
}

void IGESBasic_ToolHierarchy::OwnShared(const occ::handle<IGESBasic_Hierarchy>&,
                                        Interface_EntityIterator&) const
{
}

void IGESBasic_ToolHierarchy::OwnCopy(const occ::handle<IGESBasic_Hierarchy>& another,
                                      const occ::handle<IGESBasic_Hierarchy>& ent,
                                      Interface_CopyTool&) const
{
  ent->Init(6,
            another->NewLineFont(),
            another->NewView(),
            another->NewEntityLevel(),
            another->NewBlankStatus(),
            another->NewLineWeight(),
            another->NewColorNum());
}

bool IGESBasic_ToolHierarchy::OwnCorrect(const occ::handle<IGESBasic_Hierarchy>& ent) const
{
  bool res = (ent->NbPropertyValues() != 6);
  if (res)
    ent->Init(6,
              ent->NewLineFont(),
              ent->NewView(),
              ent->NewEntityLevel(),
              ent->NewBlankStatus(),
              ent->NewLineWeight(),
              ent->NewColorNum());
  return res;
}

IGESData_DirChecker IGESBasic_ToolHierarchy::DirChecker(
  const occ::handle<IGESBasic_Hierarchy>&) const
{
  IGESData_DirChecker DC(406, 10);
  DC.Structure(IGESData_DefVoid);
  DC.GraphicsIgnored();
  DC.BlankStatusIgnored();
  DC.UseFlagIgnored();
  DC.HierarchyStatusIgnored();
  return DC;
}

void IGESBasic_ToolHierarchy::OwnCheck(const occ::handle<IGESBasic_Hierarchy>& ent,
                                       const Interface_ShareTool&,
                                       occ::handle<Interface_Check>& ach) const
{
  if (ent->NbPropertyValues() != 6)
    ach->AddFail("Number of Property Values != 6");
  if (ent->NewLineFont() != 0 && ent->NewLineFont() != 1)
    ach->AddFail("InCorrect LineFont");
  if (ent->NewView() != 0 && ent->NewView() != 1)
    ach->AddFail("InCorrect View");
  if (ent->NewEntityLevel() != 0 && ent->NewEntityLevel() != 1)
    ach->AddFail("InCorrect EntityLevel");
  if (ent->NewBlankStatus() != 0 && ent->NewBlankStatus() != 1)
    if (ent->NewLineWeight() != 0 && ent->NewLineWeight() != 1)
      ach->AddFail("InCorrect LineWeight");
  if (ent->NewColorNum() != 0 && ent->NewColorNum() != 1)
    ach->AddFail("InCorrect ColorNum");
}

void IGESBasic_ToolHierarchy::OwnDump(const occ::handle<IGESBasic_Hierarchy>& ent,
                                      const IGESData_IGESDumper&,
                                      Standard_OStream& S,
                                      const int) const
{
  S << "IGESBasic_Hierarchy\n"
    << "Number of property values : " << ent->NbPropertyValues() << "\n"
    << "Line Font    : " << ent->NewLineFont() << "\n"
    << "View Number  : " << ent->NewView() << "\n"
    << "Entity level : " << ent->NewEntityLevel() << "\n"
    << "Blank status : " << ent->NewBlankStatus() << "\n"
    << "Line weight  : " << ent->NewLineWeight() << "\n"
    << "Color number : " << ent->NewColorNum() << std::endl;
}
