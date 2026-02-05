#include <gp_XYZ.hpp>
#include <IGESData_DirChecker.hpp>
#include <IGESData_Dump.hpp>
#include <IGESData_IGESDumper.hpp>
#include <IGESData_IGESReaderData.hpp>
#include <IGESData_IGESWriter.hpp>
#include <IGESData_ParamReader.hpp>
#include <IGESDraw_CircArraySubfigure.hpp>
#include <IGESDraw_ToolCircArraySubfigure.hpp>
#include <Interface_Check.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_EntityIterator.hpp>
#include <MoniTool_Macros.hpp>
#include <Interface_ShareTool.hpp>
#include <Standard_DomainError.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

IGESDraw_ToolCircArraySubfigure::IGESDraw_ToolCircArraySubfigure() = default;

void IGESDraw_ToolCircArraySubfigure::ReadOwnParams(
  const occ::handle<IGESDraw_CircArraySubfigure>& ent,
  const occ::handle<IGESData_IGESReaderData>&     IR,
  IGESData_ParamReader&                           PR) const
{
  // bool st; //szv#4:S4163:12Mar99 not needed

  gp_XYZ                                tempCenter;
  occ::handle<IGESData_IGESEntity>      tempBase;
  double                                tempRadius, tempStAngle, tempDelAngle;
  int                                   tempNumLocs, tempFlag, tempListCount;
  occ::handle<NCollection_HArray1<int>> tempNumPos;

  // szv#4:S4163:12Mar99 `st=` not needed
  PR.ReadEntity(IR, PR.Current(), "Base Entity", tempBase);
  PR.ReadInteger(PR.Current(), "Number Of Instance Locations", tempNumLocs);
  PR.ReadXYZ(PR.CurrentList(1, 3), "Imaginary Circle Center Coordinate", tempCenter);
  PR.ReadReal(PR.Current(), "Radius Of Imaginary Circle", tempRadius);
  PR.ReadReal(PR.Current(), "Start Angle in Radians", tempStAngle);
  PR.ReadReal(PR.Current(), "Delta Angle in Radians", tempDelAngle);

  // st = PR.ReadInteger(PR.Current(), "DO-DONT List Count", tempListCount); //szv#4:S4163:12Mar99
  // moved in if
  if (PR.ReadInteger(PR.Current(), "DO-DONT List Count", tempListCount))
  {
    // Initialise HArray1 only if there is no error reading its Length
    if (tempListCount > 0)
      tempNumPos = new NCollection_HArray1<int>(1, tempListCount);
    else if (tempListCount < 0)
      PR.AddFail("DO-DONT List Count : Less than Zero");
  }

  PR.ReadInteger(PR.Current(), "DO-DONT Flag", tempFlag); // szv#4:S4163:12Mar99 `st=` not needed

  // Read the HArray1 only if its Length was read without any Error
  if (!tempNumPos.IsNull())
  {
    int I;
    for (I = 1; I <= tempListCount; I++)
    {
      int tempPosition;
      // st = PR.ReadInteger(PR.Current(), "Number Of Position To Process",
      // tempPosition); //szv#4:S4163:12Mar99 moved in if
      if (PR.ReadInteger(PR.Current(), "Number Of Position To Process", tempPosition))
        tempNumPos->SetValue(I, tempPosition);
    }
  }

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(), ent);
  ent->Init(tempBase,
            tempNumLocs,
            tempCenter,
            tempRadius,
            tempStAngle,
            tempDelAngle,
            tempFlag,
            tempNumPos);
}

void IGESDraw_ToolCircArraySubfigure::WriteOwnParams(
  const occ::handle<IGESDraw_CircArraySubfigure>& ent,
  IGESData_IGESWriter&                            IW) const
{
  IW.Send(ent->BaseEntity());
  IW.Send(ent->NbLocations());
  IW.Send(ent->CenterPoint().X());
  IW.Send(ent->CenterPoint().Y());
  IW.Send(ent->CenterPoint().Z());
  IW.Send(ent->CircleRadius());
  IW.Send(ent->StartAngle());
  IW.Send(ent->DeltaAngle());
  IW.Send(ent->ListCount());
  IW.SendBoolean(ent->DoDontFlag());
  // Send the HArray1 only if it is not empty (i.e. Null)
  int I;
  int up = ent->ListCount();
  for (I = 1; I <= up; I++)
    IW.Send(ent->ListPosition(I));
}

void IGESDraw_ToolCircArraySubfigure::OwnShared(
  const occ::handle<IGESDraw_CircArraySubfigure>& /*ent*/,
  Interface_EntityIterator& /*iter*/) const
{
}

void IGESDraw_ToolCircArraySubfigure::OwnCopy(
  const occ::handle<IGESDraw_CircArraySubfigure>& another,
  const occ::handle<IGESDraw_CircArraySubfigure>& ent,
  Interface_CopyTool&                             TC) const
{
  DeclareAndCast(IGESData_IGESEntity, tempBase, TC.Transferred(another->BaseEntity()));
  int                                   tempNumLocs   = another->NbLocations();
  gp_XYZ                                tempCenter    = (another->CenterPoint()).XYZ();
  double                                tempRadius    = another->CircleRadius();
  double                                tempStAngle   = another->StartAngle();
  double                                tempDelAngle  = another->DeltaAngle();
  int                                   tempListCount = another->ListCount();
  int                                   tempFlag      = another->DoDontFlag();
  occ::handle<NCollection_HArray1<int>> tempNumPos;
  if (!another->DisplayFlag())
  {
    tempNumPos = new NCollection_HArray1<int>(1, tempListCount);
    int I;
    for (I = 1; I <= tempListCount; I++)
    {
      int tempPosition = another->ListPosition(I);
      tempNumPos->SetValue(I, tempPosition);
    }
  }

  ent->Init(tempBase,
            tempNumLocs,
            tempCenter,
            tempRadius,
            tempStAngle,
            tempDelAngle,
            tempFlag,
            tempNumPos);
}

IGESData_DirChecker IGESDraw_ToolCircArraySubfigure::DirChecker(
  const occ::handle<IGESDraw_CircArraySubfigure>& /*ent*/) const
{
  IGESData_DirChecker DC(414, 0);
  DC.Structure(IGESData_DefVoid);
  DC.LineFont(IGESData_DefAny);
  DC.LineWeight(IGESData_DefValue);
  DC.Color(IGESData_DefAny);
  DC.GraphicsIgnored(1);

  return DC;
}

void IGESDraw_ToolCircArraySubfigure::OwnCheck(
  const occ::handle<IGESDraw_CircArraySubfigure>& /*ent*/,
  const Interface_ShareTool&,
  occ::handle<Interface_Check>& /*ach*/) const
{
}

void IGESDraw_ToolCircArraySubfigure::OwnDump(const occ::handle<IGESDraw_CircArraySubfigure>& ent,
                                              const IGESData_IGESDumper& dumper,
                                              Standard_OStream&          S,
                                              const int                  level) const
{
  int tempSubLevel = (level <= 4) ? 0 : 1;

  S << "IGESDraw_CircArraySubfigure\n"
    << "Base Entity : ";
  dumper.Dump(ent->BaseEntity(), S, tempSubLevel);
  S << "\n"
    << "Total Number Of Possible Instance Locations : " << ent->NbLocations() << "\n"
    << "Imaginary Circle. Radius : " << ent->CircleRadius() << "  Center : ";
  IGESData_DumpXYZL(S, level, ent->CenterPoint(), ent->Location());
  S << "\n";
  S << "Start Angle (in radians) : " << ent->StartAngle() << "  "
    << "Delta Angle (in radians) : " << ent->DeltaAngle() << "\n"
    << "Do-Dont Flag : ";
  if (ent->DoDontFlag())
    S << "Dont\n";
  else
    S << "Do\n";
  S << "The Do-Dont List : ";
  IGESData_DumpVals(S, level, 1, ent->ListCount(), ent->ListPosition);
  S << std::endl;
}
