#include <gp_GTrsf.hpp>
#include <gp_Pnt.hpp>
#include <gp_XYZ.hpp>
#include <IGESData_DirChecker.hpp>
#include <IGESData_Dump.hpp>
#include <IGESData_IGESDumper.hpp>
#include <IGESData_IGESReaderData.hpp>
#include <IGESData_IGESWriter.hpp>
#include <IGESData_ParamReader.hpp>
#include <IGESGraph_TextDisplayTemplate.hpp>
#include <IGESGraph_TextFontDef.hpp>
#include <IGESGraph_ToolTextDisplayTemplate.hpp>
#include <Interface_Check.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_EntityIterator.hpp>
#include <MoniTool_Macros.hpp>
#include <Interface_ShareTool.hpp>
#include <Message_Messenger.hpp>

IGESGraph_ToolTextDisplayTemplate::IGESGraph_ToolTextDisplayTemplate() = default;

void IGESGraph_ToolTextDisplayTemplate::ReadOwnParams(
  const occ::handle<IGESGraph_TextDisplayTemplate>& ent,
  const occ::handle<IGESData_IGESReaderData>&       IR,
  IGESData_ParamReader&                             PR) const
{

  double                             boxWidth;
  double                             boxHeight;
  int                                fontCode;
  occ::handle<IGESGraph_TextFontDef> fontEnt;
  double                             slantAngle;
  double                             rotationAngle;
  int                                mirrorFlag;
  int                                rotateFlag;
  gp_XYZ                             corner;

  PR.ReadReal(PR.Current(), "Character box width", boxWidth);

  PR.ReadReal(PR.Current(), "Character box height", boxHeight);

  int curnum = PR.CurrentNumber();
  if (PR.DefinedElseSkip())
  {

    PR.ReadInteger(PR.Current(), "Font Code", fontCode);

    if (fontCode < 0)
    {
      fontEnt = GetCasted(IGESGraph_TextFontDef, PR.ParamEntity(IR, curnum));
      if (fontEnt.IsNull())
        PR.AddFail("Font Entity : incorrect reference");
    }
  }
  else
    fontCode = 1;

  if (PR.DefinedElseSkip())

    PR.ReadReal(PR.Current(), "Slant Angle", slantAngle);
  else
    slantAngle = M_PI / 2.0;

  PR.ReadReal(PR.Current(), "Rotation Angle", rotationAngle);

  PR.ReadInteger(PR.Current(), "Mirror Flag", mirrorFlag);

  PR.ReadInteger(PR.Current(), "Rotate Flag", rotateFlag);

  PR.ReadXYZ(PR.CurrentList(1, 3), "Lower left coordinates/Increments", corner);

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(), ent);
  ent->Init(boxWidth,
            boxHeight,
            fontCode,
            fontEnt,
            slantAngle,
            rotationAngle,
            mirrorFlag,
            rotateFlag,
            corner);
}

void IGESGraph_ToolTextDisplayTemplate::WriteOwnParams(
  const occ::handle<IGESGraph_TextDisplayTemplate>& ent,
  IGESData_IGESWriter&                              IW) const
{
  IW.Send(ent->BoxWidth());
  IW.Send(ent->BoxHeight());

  if (ent->IsFontEntity())
    IW.Send(ent->FontEntity(), true);
  else
    IW.Send(ent->FontCode());

  IW.Send(ent->SlantAngle());
  IW.Send(ent->RotationAngle());
  IW.Send(ent->MirrorFlag());
  IW.Send(ent->RotateFlag());
  IW.Send(ent->StartingCorner().X());
  IW.Send(ent->StartingCorner().Y());
  IW.Send(ent->StartingCorner().Z());
}

void IGESGraph_ToolTextDisplayTemplate::OwnShared(
  const occ::handle<IGESGraph_TextDisplayTemplate>& ent,
  Interface_EntityIterator&                         iter) const
{
  if (ent->IsFontEntity())
    iter.GetOneItem(ent->FontEntity());
}

void IGESGraph_ToolTextDisplayTemplate::OwnCopy(
  const occ::handle<IGESGraph_TextDisplayTemplate>& another,
  const occ::handle<IGESGraph_TextDisplayTemplate>& ent,
  Interface_CopyTool&                               TC) const
{
  double                             boxWidth;
  double                             boxHeight;
  int                                fontCode = 0;
  occ::handle<IGESGraph_TextFontDef> fontEntity;
  double                             slantAngle;
  double                             rotationAngle;
  int                                mirrorFlag;
  int                                rotateFlag;
  gp_XYZ                             corner;

  boxWidth  = another->BoxWidth();
  boxHeight = another->BoxHeight();

  if (another->IsFontEntity())
    fontEntity = occ::down_cast<IGESGraph_TextFontDef>(TC.Transferred(another->FontEntity()));
  else
    fontCode = another->FontCode();

  slantAngle    = another->SlantAngle();
  rotationAngle = another->RotationAngle();
  mirrorFlag    = another->MirrorFlag();
  rotateFlag    = another->RotateFlag();
  corner        = another->StartingCorner().XYZ();

  ent->Init(boxWidth,
            boxHeight,
            fontCode,
            fontEntity,
            slantAngle,
            rotationAngle,
            mirrorFlag,
            rotateFlag,
            corner);
}

IGESData_DirChecker IGESGraph_ToolTextDisplayTemplate::DirChecker(
  const occ::handle<IGESGraph_TextDisplayTemplate>&) const
{
  IGESData_DirChecker DC(312, 0, 1);
  DC.Structure(IGESData_DefVoid);
  DC.LineFont(IGESData_DefVoid);
  DC.LineWeight(IGESData_DefVoid);
  DC.Color(IGESData_DefAny);
  DC.SubordinateStatusRequired(0);
  DC.UseFlagRequired(2);
  DC.HierarchyStatusRequired(0);
  return DC;
}

void IGESGraph_ToolTextDisplayTemplate::OwnCheck(const occ::handle<IGESGraph_TextDisplayTemplate>&,
                                                 const Interface_ShareTool&,
                                                 occ::handle<Interface_Check>&) const
{
}

void IGESGraph_ToolTextDisplayTemplate::OwnDump(
  const occ::handle<IGESGraph_TextDisplayTemplate>& ent,
  const IGESData_IGESDumper&                        dumper,
  Standard_OStream&                                 S,
  const int                                         level) const
{
  int sublevel = (level <= 4) ? 0 : 1;

  S << "IGESGraph_TextDisplayTemplate\n"
    << "Character box width  : " << ent->BoxWidth() << "  "
    << "Character box height : " << ent->BoxHeight() << "\n";
  if (ent->IsFontEntity())
  {
    S << "Font Entity : ";
    dumper.Dump(ent->FontEntity(), S, sublevel);
  }
  else
    S << "Font code : " << ent->FontCode();

  S << "\n"
    << "Slant angle    : " << ent->SlantAngle() << "  "
    << "Rotation angle : " << ent->RotationAngle() << "\n"
    << "Mirror flag    : " << ent->MirrorFlag() << "  "
    << "Rotate flag    : " << ent->RotateFlag() << "\n";
  if (ent->FormNumber() == 0)
    S << "Lower Left Corner coordinates : ";
  else
    S << "Increments from coordinates : ";
  IGESData_DumpXYZL(S, level, ent->StartingCorner(), ent->Location());
  S << std::endl;
}
