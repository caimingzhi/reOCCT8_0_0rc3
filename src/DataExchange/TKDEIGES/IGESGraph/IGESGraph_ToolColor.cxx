#include <IGESData_DirChecker.hpp>
#include <IGESData_Dump.hpp>
#include <IGESData_IGESDumper.hpp>
#include <IGESData_IGESReaderData.hpp>
#include <IGESData_IGESWriter.hpp>
#include <IGESData_ParamReader.hpp>
#include <IGESGraph_Color.hpp>
#include <IGESGraph_ToolColor.hpp>
#include <Interface_Check.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_ShareTool.hpp>
#include <Message_Messenger.hpp>
#include <TCollection_HAsciiString.hpp>

IGESGraph_ToolColor::IGESGraph_ToolColor() = default;

void IGESGraph_ToolColor::ReadOwnParams(const occ::handle<IGESGraph_Color>& ent,
                                        const occ::handle<IGESData_IGESReaderData>&,
                                        IGESData_ParamReader& PR) const
{
  double                                tempRed, tempGreen, tempBlue;
  occ::handle<TCollection_HAsciiString> tempColorName;

  PR.ReadReal(PR.Current(), "RED as % Of Full Intensity", tempRed);

  PR.ReadReal(PR.Current(), "GREEN as % Of Full Intensity", tempGreen);

  PR.ReadReal(PR.Current(), "BLUE as % Of Full Intensity", tempBlue);

  if ((PR.CurrentNumber() <= PR.NbParams())
      && (PR.ParamType(PR.CurrentNumber()) == Interface_ParamText))
    PR.ReadText(PR.Current(), "Color Name", tempColorName);

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(), ent);
  ent->Init(tempRed, tempGreen, tempBlue, tempColorName);
}

void IGESGraph_ToolColor::WriteOwnParams(const occ::handle<IGESGraph_Color>& ent,
                                         IGESData_IGESWriter&                IW) const
{
  double Red, Green, Blue;
  ent->RGBIntensity(Red, Green, Blue);
  IW.Send(Red);
  IW.Send(Green);
  IW.Send(Blue);

  if (ent->HasColorName())
    IW.Send(ent->ColorName());
  else
    IW.SendVoid();
}

void IGESGraph_ToolColor::OwnShared(const occ::handle<IGESGraph_Color>&,
                                    Interface_EntityIterator&) const
{
}

void IGESGraph_ToolColor::OwnCopy(const occ::handle<IGESGraph_Color>& another,
                                  const occ::handle<IGESGraph_Color>& ent,
                                  Interface_CopyTool&) const
{
  double                                tempRed, tempGreen, tempBlue;
  occ::handle<TCollection_HAsciiString> tempColorName;
  another->RGBIntensity(tempRed, tempGreen, tempBlue);
  if (another->HasColorName())
    tempColorName = new TCollection_HAsciiString(another->ColorName());

  ent->Init(tempRed, tempGreen, tempBlue, tempColorName);
}

IGESData_DirChecker IGESGraph_ToolColor::DirChecker(const occ::handle<IGESGraph_Color>&) const
{
  IGESData_DirChecker DC(314, 0);
  DC.Structure(IGESData_DefVoid);
  DC.LineFont(IGESData_DefVoid);
  DC.LineWeight(IGESData_DefVoid);
  DC.Color(IGESData_DefAny);
  DC.BlankStatusIgnored();
  DC.SubordinateStatusRequired(0);
  DC.UseFlagRequired(2);
  DC.HierarchyStatusIgnored();

  return DC;
}

void IGESGraph_ToolColor::OwnCheck(const occ::handle<IGESGraph_Color>&,
                                   const Interface_ShareTool&,
                                   occ::handle<Interface_Check>&) const
{
}

void IGESGraph_ToolColor::OwnDump(const occ::handle<IGESGraph_Color>& ent,
                                  const IGESData_IGESDumper&,
                                  Standard_OStream& S,
                                  const int) const
{
  S << "IGESGraph_Color\n";

  double Red, Green, Blue;
  ent->RGBIntensity(Red, Green, Blue);
  S << "Red   (in % Of Full Intensity) : " << Red << "\n"
    << "Green (in % Of Full Intensity) : " << Green << "\n"
    << "Blue  (in % Of Full Intensity) : " << Blue << "\n"
    << "Color Name : ";
  IGESData_DumpString(S, ent->ColorName());
  S << std::endl;
}
