#include <IGESData_DirChecker.hpp>
#include <IGESData_IGESDumper.hpp>
#include <IGESData_IGESReaderData.hpp>
#include <IGESData_IGESWriter.hpp>
#include <IGESData_ParamReader.hpp>
#include <IGESDimen_DimensionTolerance.hpp>
#include <IGESDimen_ToolDimensionTolerance.hpp>
#include <Interface_Check.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_ShareTool.hpp>

IGESDimen_ToolDimensionTolerance::IGESDimen_ToolDimensionTolerance() = default;

void IGESDimen_ToolDimensionTolerance::ReadOwnParams(
  const occ::handle<IGESDimen_DimensionTolerance>& ent,
  const occ::handle<IGESData_IGESReaderData>&,
  IGESData_ParamReader& PR) const
{

  int    tempNbProps;
  int    tempSecondTolFlag;
  int    tempTolTyp;
  int    tempTolPlaceFlag;
  double tempUpperTol;
  double tempLowerTol;
  bool   tempSignSupFlag;
  int    tempFracFlag;
  int    tempPrecision;

  if (PR.DefinedElseSkip())

    PR.ReadInteger(PR.Current(), "Number of properties", tempNbProps);
  else
    tempNbProps = 8;

  PR.ReadInteger(PR.Current(), "Secondary Tolerance Flag", tempSecondTolFlag);
  PR.ReadInteger(PR.Current(), "Tolerance Type", tempTolTyp);
  if (PR.DefinedElseSkip())
    PR.ReadInteger(PR.Current(), "Tolerance Placement Flag", tempTolPlaceFlag);
  else
    tempTolPlaceFlag = 2;

  PR.ReadReal(PR.Current(), "Upper Tolerance", tempUpperTol);
  PR.ReadReal(PR.Current(), "Lower Tolerance", tempLowerTol);
  PR.ReadBoolean(PR.Current(), "Sign Suppression Flag", tempSignSupFlag);
  PR.ReadInteger(PR.Current(), "Fraction Flag", tempFracFlag);

  PR.ReadInteger(PR.Current(), "Precision", tempPrecision);

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(), ent);
  ent->Init(tempNbProps,
            tempSecondTolFlag,
            tempTolTyp,
            tempTolPlaceFlag,
            tempUpperTol,
            tempLowerTol,
            tempSignSupFlag,
            tempFracFlag,
            tempPrecision);
}

void IGESDimen_ToolDimensionTolerance::WriteOwnParams(
  const occ::handle<IGESDimen_DimensionTolerance>& ent,
  IGESData_IGESWriter&                             IW) const
{
  IW.Send(ent->NbPropertyValues());
  IW.Send(ent->SecondaryToleranceFlag());
  IW.Send(ent->ToleranceType());
  IW.Send(ent->TolerancePlacementFlag());
  IW.Send(ent->UpperTolerance());
  IW.Send(ent->LowerTolerance());
  IW.SendBoolean(ent->SignSuppressionFlag());
  IW.Send(ent->FractionFlag());
  IW.Send(ent->Precision());
}

void IGESDimen_ToolDimensionTolerance::OwnShared(const occ::handle<IGESDimen_DimensionTolerance>&,
                                                 Interface_EntityIterator&) const
{
}

void IGESDimen_ToolDimensionTolerance::OwnCopy(
  const occ::handle<IGESDimen_DimensionTolerance>& another,
  const occ::handle<IGESDimen_DimensionTolerance>& ent,
  Interface_CopyTool&) const
{
  ent->Init(8,
            another->SecondaryToleranceFlag(),
            another->ToleranceType(),
            another->TolerancePlacementFlag(),
            another->UpperTolerance(),
            another->LowerTolerance(),
            (another->SignSuppressionFlag() ? 1 : 0),
            another->FractionFlag(),
            another->Precision());
}

bool IGESDimen_ToolDimensionTolerance::OwnCorrect(
  const occ::handle<IGESDimen_DimensionTolerance>& ent) const
{
  bool res = (ent->NbPropertyValues() != 8);
  if (res)
    ent->Init(8,
              ent->SecondaryToleranceFlag(),
              ent->ToleranceType(),
              ent->TolerancePlacementFlag(),
              ent->UpperTolerance(),
              ent->LowerTolerance(),
              (ent->SignSuppressionFlag() ? 1 : 0),
              ent->FractionFlag(),
              ent->Precision());
  return res;
}

IGESData_DirChecker IGESDimen_ToolDimensionTolerance::DirChecker(
  const occ::handle<IGESDimen_DimensionTolerance>&) const
{
  IGESData_DirChecker DC(406, 29);
  DC.Structure(IGESData_DefVoid);
  DC.GraphicsIgnored();
  DC.LineFont(IGESData_DefVoid);
  DC.LineWeight(IGESData_DefVoid);
  DC.Color(IGESData_DefVoid);
  DC.BlankStatusIgnored();
  DC.SubordinateStatusRequired(2);
  DC.UseFlagRequired(2);
  DC.HierarchyStatusIgnored();
  return DC;
}

void IGESDimen_ToolDimensionTolerance::OwnCheck(
  const occ::handle<IGESDimen_DimensionTolerance>& ent,
  const Interface_ShareTool&,
  occ::handle<Interface_Check>& ach) const
{
  if (ent->NbPropertyValues() != 8)
    ach->AddFail("Number of properties != 8");
  if ((ent->SecondaryToleranceFlag() < 0) || (ent->SecondaryToleranceFlag() > 2))
    ach->AddFail("Secondary Tolerance Flag != 0-2");
  if ((ent->ToleranceType() < 1) || (ent->ToleranceType() > 10))
    ach->AddFail("Tolerance Type != 1-10");
  if ((ent->TolerancePlacementFlag() < 1) || (ent->TolerancePlacementFlag() > 4))
    ach->AddFail("Tolerance Placement Flag != 1-4");
  if ((ent->FractionFlag() < 0) || (ent->FractionFlag() > 2))
    ach->AddFail("Fraction Flag != 0-2");
}

void IGESDimen_ToolDimensionTolerance::OwnDump(const occ::handle<IGESDimen_DimensionTolerance>& ent,
                                               const IGESData_IGESDumper&,
                                               Standard_OStream& S,
                                               const int) const
{
  S << "IGESDimen_DimensionTolerance\n"
    << "Number of property values : " << ent->NbPropertyValues() << "\n"
    << "Secondary Tolerance Flag : " << ent->SecondaryToleranceFlag() << "\n"
    << "Tolerance Type           : " << ent->ToleranceType() << "\n"
    << "Tolerance Placement Flag : " << ent->TolerancePlacementFlag() << "\n"
    << "Upper Tolerance          : " << ent->UpperTolerance() << "\n"
    << "Lower Tolerance          : " << ent->LowerTolerance() << "\n"
    << "Sign Suppression Flag    : " << (ent->SignSuppressionFlag() ? "True" : "False") << "\n"
    << "Fraction Flag            : " << ent->FractionFlag() << "\n"
    << "Precision                : " << ent->Precision() << std::endl;
}
