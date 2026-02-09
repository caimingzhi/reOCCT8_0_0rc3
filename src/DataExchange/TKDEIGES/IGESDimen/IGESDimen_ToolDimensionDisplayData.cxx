#include <IGESData_DirChecker.hpp>
#include <IGESData_Dump.hpp>
#include <IGESData_IGESDumper.hpp>
#include <IGESData_IGESReaderData.hpp>
#include <IGESData_IGESWriter.hpp>
#include <IGESData_ParamReader.hpp>
#include <IGESDimen_DimensionDisplayData.hpp>
#include <IGESDimen_ToolDimensionDisplayData.hpp>
#include <Interface_Check.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_ShareTool.hpp>
#include <Message_Messenger.hpp>
#include <TCollection_HAsciiString.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

IGESDimen_ToolDimensionDisplayData::IGESDimen_ToolDimensionDisplayData() = default;

void IGESDimen_ToolDimensionDisplayData::ReadOwnParams(
  const occ::handle<IGESDimen_DimensionDisplayData>& ent,
  const occ::handle<IGESData_IGESReaderData>&,
  IGESData_ParamReader& PR) const
{

  int                                   tempDimType;
  int                                   tempLabelPos;
  int                                   tempCharSet;
  occ::handle<TCollection_HAsciiString> tempLString;
  double                                tempWitLineAng;
  int                                   tempDeciSymb;
  int                                   tempTextAlign;
  int                                   tempTextLevel;
  int                                   tempTextPlace;
  int                                   tempArrHeadOrient;
  double                                tempInitVal;
  int                                   tempNbProps;
  occ::handle<NCollection_HArray1<int>> tempSuppleNotes;
  occ::handle<NCollection_HArray1<int>> tempStartInd;
  occ::handle<NCollection_HArray1<int>> tempEndInd;

  PR.ReadInteger(PR.Current(), "Number of Properties", tempNbProps);
  PR.ReadInteger(PR.Current(), "Dimension Type", tempDimType);
  PR.ReadInteger(PR.Current(), "Label Position", tempLabelPos);
  if (PR.DefinedElseSkip())

    PR.ReadInteger(PR.Current(), "Character Set", tempCharSet);
  else
    tempCharSet = 1;

  PR.ReadText(PR.Current(), "L String", tempLString);
  PR.ReadInteger(PR.Current(), "Decimal Symbol", tempDeciSymb);
  if (PR.DefinedElseSkip())
    PR.ReadReal(PR.Current(), "Witness Line Angle", tempWitLineAng);
  else
    tempWitLineAng = M_PI / 2;

  PR.ReadInteger(PR.Current(), "Text Alignment", tempTextAlign);
  if (PR.DefinedElseSkip())
    PR.ReadInteger(PR.Current(), "Text Level", tempTextLevel);
  else
    tempTextLevel = 0;

  if (PR.DefinedElseSkip())
    PR.ReadInteger(PR.Current(), "Text Place", tempTextPlace);

  else
    tempTextPlace = 0;

  PR.ReadInteger(PR.Current(), "ArrowHeadOrientation", tempArrHeadOrient);
  PR.ReadReal(PR.Current(), "Initial Value", tempInitVal);
  int  tempnbval;
  bool st = PR.ReadInteger(PR.Current(), "No. of supplementary notes", tempnbval);
  if (st && tempnbval > 0)
  {
    tempSuppleNotes = new NCollection_HArray1<int>(1, tempnbval);
    tempStartInd    = new NCollection_HArray1<int>(1, tempnbval);
    tempEndInd      = new NCollection_HArray1<int>(1, tempnbval);
    for (int i = 1; i <= tempnbval; i++)
    {
      int anote, astart, anend;

      if (PR.ReadInteger(PR.Current(), "Supplementary Notes", anote))
        tempSuppleNotes->SetValue(i, anote);

      if (PR.ReadInteger(PR.Current(), "Start Index", astart))
        tempStartInd->SetValue(i, astart);

      if (PR.ReadInteger(PR.Current(), "End Index", anend))
        tempEndInd->SetValue(i, anend);
    }
  }

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(), ent);
  ent->Init(tempNbProps,
            tempDimType,
            tempLabelPos,
            tempCharSet,
            tempLString,
            tempDeciSymb,
            tempWitLineAng,
            tempTextAlign,
            tempTextLevel,
            tempTextPlace,
            tempArrHeadOrient,
            tempInitVal,
            tempSuppleNotes,
            tempStartInd,
            tempEndInd);
}

void IGESDimen_ToolDimensionDisplayData::WriteOwnParams(
  const occ::handle<IGESDimen_DimensionDisplayData>& ent,
  IGESData_IGESWriter&                               IW) const
{
  IW.Send(ent->NbPropertyValues());
  IW.Send(ent->DimensionType());
  IW.Send(ent->LabelPosition());
  IW.Send(ent->CharacterSet());
  IW.Send(ent->LString());
  IW.Send(ent->DecimalSymbol());
  IW.Send(ent->WitnessLineAngle());
  IW.Send(ent->TextAlignment());
  IW.Send(ent->TextLevel());
  IW.Send(ent->TextPlacement());
  IW.Send(ent->ArrowHeadOrientation());
  IW.Send(ent->InitialValue());

  int nbval = ent->NbSupplementaryNotes();
  IW.Send(nbval);
  for (int i = 1; i <= nbval; i++)
  {
    IW.Send(ent->SupplementaryNote(i));
    IW.Send(ent->StartIndex(i));
    IW.Send(ent->EndIndex(i));
  }
}

void IGESDimen_ToolDimensionDisplayData::OwnShared(
  const occ::handle<IGESDimen_DimensionDisplayData>&,
  Interface_EntityIterator&) const
{
}

void IGESDimen_ToolDimensionDisplayData::OwnCopy(
  const occ::handle<IGESDimen_DimensionDisplayData>& another,
  const occ::handle<IGESDimen_DimensionDisplayData>& ent,
  Interface_CopyTool&) const
{
  occ::handle<NCollection_HArray1<int>> EndList;
  occ::handle<NCollection_HArray1<int>> StartList;
  occ::handle<NCollection_HArray1<int>> NotesList;

  int upper = another->NbSupplementaryNotes();
  if (upper > 0)
  {
    EndList   = new NCollection_HArray1<int>(1, upper);
    StartList = new NCollection_HArray1<int>(1, upper);
    NotesList = new NCollection_HArray1<int>(1, upper);
    for (int i = 1; i <= upper; i++)
    {
      EndList->SetValue(i, another->EndIndex(i));
      StartList->SetValue(i, another->StartIndex(i));
      NotesList->SetValue(i, another->SupplementaryNote(i));
    }
  }
  int                                   tempNbPropertyValues = another->NbPropertyValues();
  int                                   tempDimensionType    = another->DimensionType();
  int                                   tempLabelPos         = another->LabelPosition();
  int                                   tempCharSet          = another->CharacterSet();
  occ::handle<TCollection_HAsciiString> tempLS = new TCollection_HAsciiString(another->LString());
  int                                   tempSymbol    = another->DecimalSymbol();
  double                                tempAngle     = another->WitnessLineAngle();
  int                                   tempAlign     = another->TextAlignment();
  int                                   tempLevel     = another->TextLevel();
  int                                   tempPlacement = another->TextPlacement();
  int                                   tempArrowHead = another->ArrowHeadOrientation();
  double                                tempInitial   = another->InitialValue();

  ent->Init(tempNbPropertyValues,
            tempDimensionType,
            tempLabelPos,
            tempCharSet,
            tempLS,
            tempSymbol,
            tempAngle,
            tempAlign,
            tempLevel,
            tempPlacement,
            tempArrowHead,
            tempInitial,
            NotesList,
            StartList,
            EndList);
}

bool IGESDimen_ToolDimensionDisplayData::OwnCorrect(
  const occ::handle<IGESDimen_DimensionDisplayData>& ent) const
{
  bool res = (ent->NbPropertyValues() != 14);
  if (!res)
    return res;
  occ::handle<NCollection_HArray1<int>> EndList;
  occ::handle<NCollection_HArray1<int>> StartList;
  occ::handle<NCollection_HArray1<int>> NotesList;

  int upper = ent->NbSupplementaryNotes();
  if (upper > 0)
  {
    EndList   = new NCollection_HArray1<int>(1, upper);
    StartList = new NCollection_HArray1<int>(1, upper);
    NotesList = new NCollection_HArray1<int>(1, upper);
    for (int i = 1; i <= upper; i++)
    {
      EndList->SetValue(i, ent->EndIndex(i));
      StartList->SetValue(i, ent->StartIndex(i));
      NotesList->SetValue(i, ent->SupplementaryNote(i));
    }
  }
  ent->Init(14,
            ent->DimensionType(),
            ent->LabelPosition(),
            ent->CharacterSet(),
            ent->LString(),
            ent->DecimalSymbol(),
            ent->WitnessLineAngle(),
            ent->TextAlignment(),
            ent->TextLevel(),
            ent->TextPlacement(),
            ent->ArrowHeadOrientation(),
            ent->InitialValue(),
            NotesList,
            StartList,
            EndList);
  return res;
}

IGESData_DirChecker IGESDimen_ToolDimensionDisplayData::DirChecker(
  const occ::handle<IGESDimen_DimensionDisplayData>&) const
{
  IGESData_DirChecker DC(406, 30);
  DC.Structure(IGESData_DefVoid);
  DC.GraphicsIgnored();
  DC.BlankStatusIgnored();
  DC.SubordinateStatusRequired(02);
  DC.UseFlagRequired(02);
  DC.HierarchyStatusIgnored();
  return DC;
}

void IGESDimen_ToolDimensionDisplayData::OwnCheck(
  const occ::handle<IGESDimen_DimensionDisplayData>& ent,
  const Interface_ShareTool&,
  occ::handle<Interface_Check>& ach) const
{
  if (ent->NbPropertyValues() != 14)
    ach->AddFail("The No. of property values != 14 ");
  if (ent->DimensionType() < 0 || ent->DimensionType() > 2)
    ach->AddFail("Incorrect Dimension Type");
  if (ent->LabelPosition() < 0 || ent->LabelPosition() > 4)
    ach->AddFail("Incorrect Preferred Label Position");
  if (ent->CharacterSet() != 1 && ent->CharacterSet() != 1001 && ent->CharacterSet() != 1002
      && ent->CharacterSet() != 1003)
    ach->AddFail("Incorrect Character Set");
  if (ent->DecimalSymbol() != 0 && ent->DecimalSymbol() != 1)
    ach->AddFail("Incorrect Decimal Symbol");
  if (ent->TextAlignment() != 0 && ent->TextAlignment() != 1)
    ach->AddFail("Incorrect Text Alignment");
  if (ent->TextLevel() < 0 || ent->TextLevel() > 2)
    ach->AddFail("Incorrect Text Level");
  if (ent->TextPlacement() < 0 || ent->TextPlacement() > 2)
    ach->AddFail("Incorrect Text Placement");
  if (ent->ArrowHeadOrientation() != 0 && ent->ArrowHeadOrientation() != 1)
    ach->AddFail("Incorrect ArrowHead Orientation");
  for (int upper = ent->NbSupplementaryNotes(), i = 1; i <= upper; i++)
  {
    if (ent->SupplementaryNote(i) < 1 || ent->SupplementaryNote(i) > 4)
      ach->AddFail("Incorrect First supplement note");
  }
}

void IGESDimen_ToolDimensionDisplayData::OwnDump(
  const occ::handle<IGESDimen_DimensionDisplayData>& ent,
  const IGESData_IGESDumper&,
  Standard_OStream& S,
  const int         level) const
{
  S << "IGESDimen_DimensionDisplayData\n"
    << "No. of property values : " << ent->NbPropertyValues() << "\n"
    << "DimensionType : " << ent->DimensionType();
  switch (ent->DimensionType())
  {
    case 0:
      S << " (Ordinary)\n";
      break;
    case 1:
      S << " (Reference)\n";
      break;
    case 2:
      S << " (Basic)\n";
      break;
    default:
      S << " (Incorrect Value)\n";
      break;
  }

  S << "Preferred Label Position : " << ent->LabelPosition();
  switch (ent->LabelPosition())
  {
    case 0:
      S << " (Does not exist)\n";
      break;
    case 1:
      S << " (Before Measurement)\n";
      break;
    case 2:
      S << " (After Measurement)\n";
      break;
    case 3:
      S << " (Above Measurement)\n";
      break;
    case 4:
      S << " (Below Measurement)\n";
      break;
    default:
      S << " (Incorrect Value)\n";
      break;
  }

  S << "Character set interpretation : " << ent->CharacterSet();
  switch (ent->CharacterSet())
  {
    case 1:
      S << " (Standard ASCII)\n";
      break;
    case 1001:
      S << " (Symbol Font 1)\n";
      break;
    case 1002:
      S << " (Symbol Font 2)\n";
      break;
    case 1003:
      S << " (Drafting Font)\n";
      break;
    default:
      S << " (Not meaningful)\n";
      break;
  }

  S << "LString : ";
  IGESData_DumpString(S, ent->LString());
  S << "\n"
    << "Decimal Symbol : ";
  if (ent->DecimalSymbol() == 0)
    S << "0 (.)\n";
  else
    S << "1 (,)\n";

  S << "Witness Line Angle : " << ent->WitnessLineAngle() << "\n"
    << "Text Alignment : ";
  if (ent->TextAlignment() == 0)
    S << "0 (Horizontal)\n";
  else if (ent->TextAlignment() == 1)
    S << "1 (Parallel)\n";
  else
    S << ent->TextAlignment() << " (Incorrect Value)\n";

  S << "Text Level : " << ent->TextLevel();
  switch (ent->TextLevel())
  {
    case 0:
      S << " (Neither above nor below)\n";
      break;
    case 1:
      S << " (Above)\n";
      break;
    case 2:
      S << " (Below)\n";
      break;
    default:
      S << " (Incorrect Value)\n";
      break;
  }

  S << "Preferred Text placement : " << ent->TextPlacement();
  switch (ent->TextPlacement())
  {
    case 0:
      S << " (Between witness lines)\n";
      break;
    case 1:
      S << " (Outside near the first witness line)\n";
      break;
    case 2:
      S << " (Outside near second witness line)\n";
      break;
    default:
      S << " (Incorrect Value)\n";
      break;
  }

  S << "Arrow Head Orientation : " << ent->ArrowHeadOrientation();
  if (ent->ArrowHeadOrientation() == 0)
    S << " (In, pointing out)\n";
  else if (ent->ArrowHeadOrientation() == 1)
    S << " (Out, pointing in)\n";
  else
    S << " (Incorrect Value)\n";

  int nbnotes = ent->NbSupplementaryNotes();
  S << " Primary Dimension Value : " << ent->InitialValue() << "\n"
    << " Number of Supplementary Notes : " << nbnotes << "\n"
    << "Supplementary Notes , "
    << " Start Index , "
    << " End   Index :\n";
  IGESData_DumpVals(S, -level, 1, nbnotes, ent->EndIndex);
  S << "\n";
  if (level > 4)
    for (int i = 1; i <= nbnotes; i++)
    {
      S << "[" << i << "]:\n"
        << "Supplementary Note : " << ent->SupplementaryNote(i)
        << ", Start Index : " << ent->StartIndex(i) << ", End Index : " << ent->EndIndex(i) << "\n";
    }
  S << std::endl;
}
