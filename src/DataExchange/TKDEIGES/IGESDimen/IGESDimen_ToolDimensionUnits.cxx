#include <IGESData_DirChecker.hpp>
#include <IGESData_Dump.hpp>
#include <IGESData_IGESDumper.hpp>
#include <IGESData_IGESReaderData.hpp>
#include <IGESData_IGESWriter.hpp>
#include <IGESData_ParamReader.hpp>
#include <IGESDimen_DimensionUnits.hpp>
#include <IGESDimen_ToolDimensionUnits.hpp>
#include <Interface_Check.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_ShareTool.hpp>
#include <Message_Messenger.hpp>
#include <TCollection_HAsciiString.hpp>

IGESDimen_ToolDimensionUnits::IGESDimen_ToolDimensionUnits() = default;

void IGESDimen_ToolDimensionUnits::ReadOwnParams(const occ::handle<IGESDimen_DimensionUnits>& ent,
                                                 const occ::handle<IGESData_IGESReaderData>&,
                                                 IGESData_ParamReader& PR) const
{

  int                                   tempNbProps;
  int                                   tempSecondDimenPos;
  int                                   tempUnitsIndic;
  int                                   tempCharSet;
  int                                   tempFracFlag;
  int                                   tempPrecision;
  occ::handle<TCollection_HAsciiString> tempFormatString;

  if (PR.DefinedElseSkip())

    PR.ReadInteger(PR.Current(), "Number of Properties", tempNbProps);
  else
    tempNbProps = 6;

  PR.ReadInteger(PR.Current(), "Secondary Dimension Position", tempSecondDimenPos);
  PR.ReadInteger(PR.Current(), "Units Indicator", tempUnitsIndic);
  if (PR.DefinedElseSkip())
    PR.ReadInteger(PR.Current(), "Character Set", tempCharSet);
  else
    tempCharSet = 1;

  PR.ReadText(PR.Current(), "Format String", tempFormatString);
  PR.ReadInteger(PR.Current(), "Fraction Flag", tempFracFlag);

  PR.ReadInteger(PR.Current(), "Precision", tempPrecision);

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(), ent);
  ent->Init(tempNbProps,
            tempSecondDimenPos,
            tempUnitsIndic,
            tempCharSet,
            tempFormatString,
            tempFracFlag,
            tempPrecision);
}

void IGESDimen_ToolDimensionUnits::WriteOwnParams(const occ::handle<IGESDimen_DimensionUnits>& ent,
                                                  IGESData_IGESWriter& IW) const
{
  IW.Send(ent->NbPropertyValues());
  IW.Send(ent->SecondaryDimenPosition());
  IW.Send(ent->UnitsIndicator());
  IW.Send(ent->CharacterSet());
  IW.Send(ent->FormatString());
  IW.Send(ent->FractionFlag());
  IW.Send(ent->PrecisionOrDenominator());
}

void IGESDimen_ToolDimensionUnits::OwnShared(const occ::handle<IGESDimen_DimensionUnits>&,
                                             Interface_EntityIterator&) const
{
}

void IGESDimen_ToolDimensionUnits::OwnCopy(const occ::handle<IGESDimen_DimensionUnits>& another,
                                           const occ::handle<IGESDimen_DimensionUnits>& ent,
                                           Interface_CopyTool&) const
{
  int                                   tempNbProps        = another->NbPropertyValues();
  int                                   tempSecondDimenPos = another->SecondaryDimenPosition();
  int                                   tempUnitsIndic     = another->UnitsIndicator();
  int                                   tempCharSet        = another->CharacterSet();
  occ::handle<TCollection_HAsciiString> tempFormatString =
    new TCollection_HAsciiString(another->FormatString());
  int tempFracFlag  = another->FractionFlag();
  int tempPrecision = another->PrecisionOrDenominator();
  ent->Init(tempNbProps,
            tempSecondDimenPos,
            tempUnitsIndic,
            tempCharSet,
            tempFormatString,
            tempFracFlag,
            tempPrecision);
}

bool IGESDimen_ToolDimensionUnits::OwnCorrect(
  const occ::handle<IGESDimen_DimensionUnits>& ent) const
{
  bool res = (ent->NbPropertyValues() != 6);
  if (res)
    ent->Init(6,
              ent->SecondaryDimenPosition(),
              ent->UnitsIndicator(),
              ent->CharacterSet(),
              ent->FormatString(),
              ent->FractionFlag(),
              ent->PrecisionOrDenominator());
  return res;
}

IGESData_DirChecker IGESDimen_ToolDimensionUnits::DirChecker(
  const occ::handle<IGESDimen_DimensionUnits>&) const
{
  IGESData_DirChecker DC(406, 28);
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

void IGESDimen_ToolDimensionUnits::OwnCheck(const occ::handle<IGESDimen_DimensionUnits>& ent,
                                            const Interface_ShareTool&,
                                            occ::handle<Interface_Check>& ach) const
{
  if (ent->NbPropertyValues() != 6)
    ach->AddFail("Number of properties != 6");
  if (ent->SecondaryDimenPosition() < 0 || ent->SecondaryDimenPosition() > 4)
    ach->AddFail("Secondary Dimension Position != 0-4");
  if ((ent->CharacterSet() != 1) && ((ent->CharacterSet() < 1001) || (ent->CharacterSet() > 1003)))
    ach->AddFail("Character Set != 1,1001-1003");
  if ((ent->FractionFlag() != 0) && (ent->FractionFlag() != 1))
    ach->AddFail("Fraction Flag != 0,1");
}

void IGESDimen_ToolDimensionUnits::OwnDump(const occ::handle<IGESDimen_DimensionUnits>& ent,
                                           const IGESData_IGESDumper&,
                                           Standard_OStream& S,
                                           const int) const
{
  S << "IGESDimen_DimensionUnits\n"
    << "Number of property values : " << ent->NbPropertyValues() << "\n"
    << "Secondary Dimension Position : " << ent->SecondaryDimenPosition() << "\n"
    << "Units Indicator : " << ent->UnitsIndicator() << "\n"
    << "Character Set   : " << ent->CharacterSet() << "\n"
    << "Format String   : ";
  IGESData_DumpString(S, ent->FormatString());
  S << "\n"
    << "Fraction Flag   : " << ent->FractionFlag();
  if (ent->FractionFlag() == 0)
    S << " Decimal  , Precision   : ";
  else
    S << " Fraction , Denominator : ";
  S << ent->PrecisionOrDenominator() << std::endl;
}
