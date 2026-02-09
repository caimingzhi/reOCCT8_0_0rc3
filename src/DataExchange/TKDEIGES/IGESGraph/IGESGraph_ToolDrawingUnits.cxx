#include <IGESData_DirChecker.hpp>
#include <IGESData_Dump.hpp>
#include <IGESData_IGESDumper.hpp>
#include <IGESData_IGESReaderData.hpp>
#include <IGESData_IGESWriter.hpp>
#include <IGESData_ParamReader.hpp>
#include <IGESGraph_DrawingUnits.hpp>
#include <IGESGraph_ToolDrawingUnits.hpp>
#include <Interface_Check.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_ShareTool.hpp>
#include <Message_Messenger.hpp>
#include <TCollection_HAsciiString.hpp>

IGESGraph_ToolDrawingUnits::IGESGraph_ToolDrawingUnits() = default;

void IGESGraph_ToolDrawingUnits::ReadOwnParams(const occ::handle<IGESGraph_DrawingUnits>& ent,
                                               const occ::handle<IGESData_IGESReaderData>&,
                                               IGESData_ParamReader& PR) const
{

  int                                   nbPropertyValues;
  int                                   flag;
  occ::handle<TCollection_HAsciiString> unit;

  PR.ReadInteger(PR.Current(), "No. of property values", nbPropertyValues);

  if (nbPropertyValues != 2)
    PR.AddFail("No. of Property values : Value is not 2");

  PR.ReadInteger(PR.Current(), "Units Flag", flag);

  PR.ReadText(PR.Current(), "Units Name", unit);

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(), ent);
  ent->Init(nbPropertyValues, flag, unit);
}

void IGESGraph_ToolDrawingUnits::WriteOwnParams(const occ::handle<IGESGraph_DrawingUnits>& ent,
                                                IGESData_IGESWriter&                       IW) const
{
  IW.Send(ent->NbPropertyValues());
  IW.Send(ent->Flag());
  IW.Send(ent->Unit());
}

void IGESGraph_ToolDrawingUnits::OwnShared(const occ::handle<IGESGraph_DrawingUnits>&,
                                           Interface_EntityIterator&) const
{
}

void IGESGraph_ToolDrawingUnits::OwnCopy(const occ::handle<IGESGraph_DrawingUnits>& another,
                                         const occ::handle<IGESGraph_DrawingUnits>& ent,
                                         Interface_CopyTool&) const
{
  int                                   NbPropertyValues;
  int                                   Flag;
  occ::handle<TCollection_HAsciiString> Unit;

  NbPropertyValues = another->NbPropertyValues();
  Flag             = another->Flag();
  Unit             = new TCollection_HAsciiString(another->Unit());

  ent->Init(NbPropertyValues, Flag, Unit);
}

bool IGESGraph_ToolDrawingUnits::OwnCorrect(const occ::handle<IGESGraph_DrawingUnits>& ent) const
{
  bool res = (ent->NbPropertyValues() != 2);

  int                                   unf = ent->Flag();
  occ::handle<TCollection_HAsciiString> name;
  const char*                           unm = "";
  if (!ent->Unit().IsNull())
    unm = ent->Unit()->ToCString();
  switch (unf)
  {
    case 1:
      if ((strcmp(unm, "IN") == 0) || (strcmp(unm, "INCH") == 0))
      {
        name = new TCollection_HAsciiString("IN");
      }
      break;
    case 2:
      if (strcmp(unm, "MM") == 0)
      {
        name = new TCollection_HAsciiString("MM");
      }
      break;
    case 3:
      break;
    case 4:
      if (strcmp(unm, "FT") == 0)
      {
        name = new TCollection_HAsciiString("FT");
      }
      break;
    case 5:
      if (strcmp(unm, "MI") == 0)
      {
        name = new TCollection_HAsciiString("MI");
      }
      break;
    case 6:
      if (strcmp(unm, "M") == 0)
      {
        name = new TCollection_HAsciiString("M");
      }
      break;
    case 7:
      if (strcmp(unm, "KM") == 0)
      {
        name = new TCollection_HAsciiString("KM");
      }
      break;
    case 8:
      if (strcmp(unm, "MIL") == 0)
      {
        name = new TCollection_HAsciiString("MIL");
      }
      break;
    case 9:
      if (strcmp(unm, "UM") == 0)
      {
        name = new TCollection_HAsciiString("UM");
      }
      break;
    case 10:
      if (strcmp(unm, "CM") == 0)
      {
        name = new TCollection_HAsciiString("CM");
      }
      break;
    case 11:
      if (strcmp(unm, "UIN") == 0)
      {
        name = new TCollection_HAsciiString("UIN");
      }
      break;
    default:
      break;
  }

  res |= (!name.IsNull());
  if (name.IsNull())
    name = ent->Unit();
  if (res)
    ent->Init(2, unf, name);
  return res;
}

IGESData_DirChecker IGESGraph_ToolDrawingUnits::DirChecker(
  const occ::handle<IGESGraph_DrawingUnits>&) const
{
  IGESData_DirChecker DC(406, 17);
  DC.Structure(IGESData_DefVoid);
  DC.LineFont(IGESData_DefVoid);
  DC.LineWeight(IGESData_DefVoid);
  DC.Color(IGESData_DefVoid);
  DC.BlankStatusIgnored();
  DC.UseFlagIgnored();
  DC.HierarchyStatusIgnored();
  return DC;
}

void IGESGraph_ToolDrawingUnits::OwnCheck(const occ::handle<IGESGraph_DrawingUnits>& ent,
                                          const Interface_ShareTool&,
                                          occ::handle<Interface_Check>& ach) const
{
  if (ent->NbPropertyValues() != 2)
    ach->AddFail("No. of Property values : Value != 2");

  int unf = ent->Flag();
  if (ent->Unit().IsNull())
  {
    if (unf == 3)
      ach->AddFail("Unit Flag = 3 (user def.) and Unit Name undefined");
  }
  else
  {
    const char* unm  = ent->Unit()->ToCString();
    bool        unok = true;
    switch (unf)
    {
      case 1:
        unok = (!strcmp(unm, "IN") || !strcmp(unm, "INCH"));
        break;
      case 2:
        unok = !strcmp(unm, "MM");
        break;
      case 3:
        unok = true;
        break;
      case 4:
        unok = !strcmp(unm, "FT");
        break;
      case 5:
        unok = !strcmp(unm, "MI");
        break;
      case 6:
        unok = !strcmp(unm, "M");
        break;
      case 7:
        unok = !strcmp(unm, "KM");
        break;
      case 8:
        unok = !strcmp(unm, "MIL");
        break;
      case 9:
        unok = !strcmp(unm, "UM");
        break;
      case 10:
        unok = !strcmp(unm, "CM");
        break;
      case 11:
        unok = !strcmp(unm, "UIN");
        break;
      default:
        ach->AddFail("Unit Flag not in range 1 - 11");
        break;
    }
    if (!unok)
      ach->AddFail("Unit Flag & Name not accorded");
  }
}

void IGESGraph_ToolDrawingUnits::OwnDump(const occ::handle<IGESGraph_DrawingUnits>& ent,
                                         const IGESData_IGESDumper&,
                                         Standard_OStream& S,
                                         const int) const
{
  S << "IGESGraph_DrawingUnits\n"
    << "No. of property values : " << ent->NbPropertyValues() << "\n"
    << "  Units Flag : " << ent->Flag() << "  Units Name : ";
  IGESData_DumpString(S, ent->Unit());
  S << "  computed Value (in meters) : " << ent->UnitValue() << std::endl;
}
