#include <IGESData_DirChecker.hpp>
#include <IGESData_IGESDumper.hpp>
#include <IGESData_IGESReaderData.hpp>
#include <IGESData_IGESWriter.hpp>
#include <IGESData_ParamReader.hpp>
#include <IGESGraph_HighLight.hpp>
#include <IGESGraph_ToolHighLight.hpp>
#include <Interface_Check.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_ShareTool.hpp>

IGESGraph_ToolHighLight::IGESGraph_ToolHighLight() = default;

void IGESGraph_ToolHighLight::ReadOwnParams(const occ::handle<IGESGraph_HighLight>& ent,
                                            const occ::handle<IGESData_IGESReaderData>& /*IR*/,
                                            IGESData_ParamReader& PR) const
{
  int nbPropertyValues;
  int highLightStatus;

  // Reading nbPropertyValues(Integer)
  PR.ReadInteger(PR.Current(), "No. of property values", nbPropertyValues);
  if (nbPropertyValues != 1)
    PR.AddFail("No. of Property values : Value is not 1");

  if (PR.DefinedElseSkip())
    // Reading highLightStatus(Integer)
    PR.ReadInteger(PR.Current(), "Highlight flag", highLightStatus);
  else
    highLightStatus = 0; // Default Value

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(), ent);
  ent->Init(nbPropertyValues, highLightStatus);
}

void IGESGraph_ToolHighLight::WriteOwnParams(const occ::handle<IGESGraph_HighLight>& ent,
                                             IGESData_IGESWriter&                    IW) const
{
  IW.Send(ent->NbPropertyValues());
  IW.Send(ent->HighLightStatus());
}

void IGESGraph_ToolHighLight::OwnShared(const occ::handle<IGESGraph_HighLight>& /*ent*/,
                                        Interface_EntityIterator& /*iter*/) const
{
}

void IGESGraph_ToolHighLight::OwnCopy(const occ::handle<IGESGraph_HighLight>& another,
                                      const occ::handle<IGESGraph_HighLight>& ent,
                                      Interface_CopyTool& /*TC*/) const
{
  ent->Init(1, another->HighLightStatus());
}

bool IGESGraph_ToolHighLight::OwnCorrect(const occ::handle<IGESGraph_HighLight>& ent) const
{
  bool res = (ent->NbPropertyValues() != 1);
  if (res)
    ent->Init(1, ent->HighLightStatus()); // nbpropertyvalues=1
  return res;
}

IGESData_DirChecker IGESGraph_ToolHighLight::DirChecker(
  const occ::handle<IGESGraph_HighLight>& /*ent*/) const
{
  IGESData_DirChecker DC(406, 20);
  DC.Structure(IGESData_DefVoid);
  DC.LineFont(IGESData_DefVoid);
  DC.LineWeight(IGESData_DefVoid);
  DC.Color(IGESData_DefVoid);
  DC.BlankStatusIgnored();
  DC.UseFlagIgnored();
  DC.HierarchyStatusIgnored();
  return DC;
}

void IGESGraph_ToolHighLight::OwnCheck(const occ::handle<IGESGraph_HighLight>& ent,
                                       const Interface_ShareTool&,
                                       occ::handle<Interface_Check>& ach) const
{
  if (ent->NbPropertyValues() != 1)
    ach->AddFail("No. of Property values : Value != 1");
}

void IGESGraph_ToolHighLight::OwnDump(const occ::handle<IGESGraph_HighLight>& ent,
                                      const IGESData_IGESDumper& /*dumper*/,
                                      Standard_OStream& S,
                                      const int /*level*/) const
{
  S << "IGESGraph_HighLight\n"
    << "No. of property values : " << ent->NbPropertyValues() << "\n"
    << "Highlight Status : " << ent->HighLightStatus() << "\n"
    << std::endl;
}
