#include <gp_Pnt.hpp>
#include <gp_XYZ.hpp>
#include <IGESData_DirChecker.hpp>
#include <IGESData_Dump.hpp>
#include <IGESData_IGESDumper.hpp>
#include <IGESData_IGESReaderData.hpp>
#include <IGESData_IGESWriter.hpp>
#include <IGESData_ParamReader.hpp>
#include <IGESDimen_GeneralNote.hpp>
#include <IGESDimen_ToolGeneralNote.hpp>
#include <IGESGraph_TextFontDef.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Interface_Check.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_EntityIterator.hpp>
#include <TCollection_HAsciiString.hpp>
#include <MoniTool_Macros.hpp>
#include <Interface_ShareTool.hpp>
#include <Message_Messenger.hpp>
#include <Standard_DomainError.hpp>
#include <Standard_Integer.hpp>

#include <cstdio>

IGESDimen_ToolGeneralNote::IGESDimen_ToolGeneralNote() = default;

void IGESDimen_ToolGeneralNote::ReadOwnParams(const occ::handle<IGESDimen_GeneralNote>&   ent,
                                              const occ::handle<IGESData_IGESReaderData>& IR,
                                              IGESData_ParamReader&                       PR) const
{

  int                                                                     nbval;
  occ::handle<NCollection_HArray1<int>>                                   nbChars;
  occ::handle<NCollection_HArray1<double>>                                boxWidths;
  occ::handle<NCollection_HArray1<double>>                                boxHeights;
  occ::handle<NCollection_HArray1<int>>                                   fontCodes;
  occ::handle<NCollection_HArray1<occ::handle<IGESGraph_TextFontDef>>>    fontEntities;
  occ::handle<NCollection_HArray1<double>>                                slantAngles;
  occ::handle<NCollection_HArray1<double>>                                rotationAngles;
  occ::handle<NCollection_HArray1<int>>                                   mirrorFlags;
  occ::handle<NCollection_HArray1<int>>                                   rotateFlags;
  occ::handle<NCollection_HArray1<gp_XYZ>>                                startPoints;
  occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>> texts;

  bool st = PR.ReadInteger(PR.Current(), "Number of Text Strings", nbval);
  if (st && nbval > 0)
  {
    nbChars        = new NCollection_HArray1<int>(1, nbval);
    boxWidths      = new NCollection_HArray1<double>(1, nbval);
    boxHeights     = new NCollection_HArray1<double>(1, nbval);
    fontCodes      = new NCollection_HArray1<int>(1, nbval);
    fontEntities   = new NCollection_HArray1<occ::handle<IGESGraph_TextFontDef>>(1, nbval);
    slantAngles    = new NCollection_HArray1<double>(1, nbval);
    rotationAngles = new NCollection_HArray1<double>(1, nbval);
    mirrorFlags    = new NCollection_HArray1<int>(1, nbval);
    rotateFlags    = new NCollection_HArray1<int>(1, nbval);
    startPoints    = new NCollection_HArray1<gp_XYZ>(1, nbval);
    texts          = new NCollection_HArray1<occ::handle<TCollection_HAsciiString>>(1, nbval);
  }
  else
    PR.AddFail("Number of Text Strings: Not Positive");

  if (!nbChars.IsNull())
  {
    for (int i = 1; i <= nbval; i++)
    {
      int                                   nbChar;
      double                                boxWidth;
      double                                boxHeight;
      int                                   fontCode;
      occ::handle<IGESGraph_TextFontDef>    fontEntity;
      double                                slantAngle;
      double                                rotationAngle;
      int                                   mirrorFlag;
      int                                   rotateFlag;
      gp_XYZ                                startPoint;
      occ::handle<TCollection_HAsciiString> text;

      if (PR.ReadInteger(PR.Current(), "Number of Characters", nbChar))
        nbChars->SetValue(i, nbChar);

      if (PR.ReadReal(PR.Current(), "Box Width", boxWidth))
        boxWidths->SetValue(i, boxWidth);

      if (PR.ReadReal(PR.Current(), "Box Height", boxHeight))
        boxHeights->SetValue(i, boxHeight);

      int curnum = PR.CurrentNumber();
      if (PR.DefinedElseSkip())
      {

        PR.ReadInteger(PR.Current(), "Font Code", fontCode);

        if (fontCode < 0)
        {
          fontEntity = GetCasted(IGESGraph_TextFontDef, PR.ParamEntity(IR, curnum));
          if (fontEntity.IsNull())
            PR.AddFail("Font Entity : incorrect reference");
          fontEntities->SetValue(i, fontEntity);
          fontCodes->SetValue(i, -1);
        }
        else
          fontCodes->SetValue(i, fontCode);
      }
      else
      {
        fontCodes->SetValue(i, 1);
      }

      if (PR.DefinedElseSkip())
      {

        if (PR.ReadReal(PR.Current(), "Slant Angle", slantAngle))
          slantAngles->SetValue(i, slantAngle);
      }
      else
        slantAngles->SetValue(i, M_PI / 2);

      if (PR.ReadReal(PR.Current(), "Rotation Angle", rotationAngle))
        rotationAngles->SetValue(i, rotationAngle);

      if (PR.ReadInteger(PR.Current(), "Mirror Flag", mirrorFlag))
        mirrorFlags->SetValue(i, mirrorFlag);

      if (PR.ReadInteger(PR.Current(), "Rotate Flag", rotateFlag))
        rotateFlags->SetValue(i, rotateFlag);

      if (PR.ReadXYZ(PR.CurrentList(1, 3), "Start Point", startPoint))
        startPoints->SetValue(i, startPoint);

      if (PR.ReadText(PR.Current(), "Text String", text))
        texts->SetValue(i, text);
    }
  }

  if (!(nbChars.IsNull() || boxWidths.IsNull() || boxHeights.IsNull() || fontCodes.IsNull()
        || fontEntities.IsNull() || slantAngles.IsNull() || rotationAngles.IsNull()
        || mirrorFlags.IsNull() || rotateFlags.IsNull() || startPoints.IsNull() || texts.IsNull()))
  {
    DirChecker(ent).CheckTypeAndForm(PR.CCheck(), ent);
    ent->Init(nbChars,
              boxWidths,
              boxHeights,
              fontCodes,
              fontEntities,
              slantAngles,
              rotationAngles,
              mirrorFlags,
              rotateFlags,
              startPoints,
              texts);
  }
}

void IGESDimen_ToolGeneralNote::WriteOwnParams(const occ::handle<IGESDimen_GeneralNote>& ent,
                                               IGESData_IGESWriter&                      IW) const
{
  int nbval = ent->NbStrings();
  IW.Send(nbval);

  for (int i = 1; i <= nbval; i++)
  {
    IW.Send(ent->NbCharacters(i));
    IW.Send(ent->BoxWidth(i));
    IW.Send(ent->BoxHeight(i));
    if (ent->IsFontEntity(i))
      IW.Send(ent->FontEntity(i), true);
    else
      IW.Send(ent->FontCode(i));
    IW.Send(ent->SlantAngle(i));
    IW.Send(ent->RotationAngle(i));
    IW.Send(ent->MirrorFlag(i));
    IW.Send(ent->RotateFlag(i));
    IW.Send((ent->StartPoint(i)).X());
    IW.Send((ent->StartPoint(i)).Y());
    IW.Send((ent->StartPoint(i)).Z());
    IW.Send(ent->Text(i));
  }
}

void IGESDimen_ToolGeneralNote::OwnShared(const occ::handle<IGESDimen_GeneralNote>& ent,
                                          Interface_EntityIterator&                 iter) const
{
  int nbval = ent->NbStrings();
  for (int i = 1; i <= nbval; i++)
  {
    if (ent->IsFontEntity(i))
      iter.GetOneItem(ent->FontEntity(i));
  }
}

void IGESDimen_ToolGeneralNote::OwnCopy(const occ::handle<IGESDimen_GeneralNote>& another,
                                        const occ::handle<IGESDimen_GeneralNote>& ent,
                                        Interface_CopyTool&                       TC) const
{
  int nbval = another->NbStrings();

  occ::handle<NCollection_HArray1<int>>                                   nbChars;
  occ::handle<NCollection_HArray1<double>>                                boxWidths;
  occ::handle<NCollection_HArray1<double>>                                boxHeights;
  occ::handle<NCollection_HArray1<int>>                                   fontCodes;
  occ::handle<NCollection_HArray1<occ::handle<IGESGraph_TextFontDef>>>    fontEntities;
  occ::handle<NCollection_HArray1<double>>                                slantAngles;
  occ::handle<NCollection_HArray1<double>>                                rotationAngles;
  occ::handle<NCollection_HArray1<int>>                                   mirrorFlags;
  occ::handle<NCollection_HArray1<int>>                                   rotateFlags;
  occ::handle<NCollection_HArray1<gp_XYZ>>                                startPoints;
  occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>> texts;

  nbChars        = new NCollection_HArray1<int>(1, nbval);
  boxWidths      = new NCollection_HArray1<double>(1, nbval);
  boxHeights     = new NCollection_HArray1<double>(1, nbval);
  fontCodes      = new NCollection_HArray1<int>(1, nbval);
  fontEntities   = new NCollection_HArray1<occ::handle<IGESGraph_TextFontDef>>(1, nbval);
  slantAngles    = new NCollection_HArray1<double>(1, nbval);
  rotationAngles = new NCollection_HArray1<double>(1, nbval);
  mirrorFlags    = new NCollection_HArray1<int>(1, nbval);
  rotateFlags    = new NCollection_HArray1<int>(1, nbval);
  startPoints    = new NCollection_HArray1<gp_XYZ>(1, nbval);
  texts          = new NCollection_HArray1<occ::handle<TCollection_HAsciiString>>(1, nbval);

  for (int i = 1; i <= nbval; i++)
  {
    int nbChar = another->NbCharacters(i);
    nbChars->SetValue(i, nbChar);
    double boxWidth = another->BoxWidth(i);
    boxWidths->SetValue(i, boxWidth);
    double boxHeight = another->BoxHeight(i);
    boxHeights->SetValue(i, boxHeight);

    if (another->IsFontEntity(i))
    {
      DeclareAndCast(IGESGraph_TextFontDef, fontEntity, TC.Transferred(another->FontEntity(i)));
      fontEntities->SetValue(i, fontEntity);
      fontCodes->SetValue(i, -1);
    }
    else
    {
      int fontCode = another->FontCode(i);
      fontCodes->SetValue(i, fontCode);
    }

    double slantAngle = another->SlantAngle(i);
    slantAngles->SetValue(i, slantAngle);
    double rotationAngle = another->RotationAngle(i);
    rotationAngles->SetValue(i, rotationAngle);
    int mirrorFlag = another->MirrorFlag(i);
    mirrorFlags->SetValue(i, mirrorFlag);
    int rotateFlag = another->RotateFlag(i);
    rotateFlags->SetValue(i, rotateFlag);
    gp_XYZ startPoint = (another->StartPoint(i)).XYZ();
    startPoints->SetValue(i, startPoint);
    occ::handle<TCollection_HAsciiString> text = new TCollection_HAsciiString(another->Text(i));
    texts->SetValue(i, text);
  }

  ent->Init(nbChars,
            boxWidths,
            boxHeights,
            fontCodes,
            fontEntities,
            slantAngles,
            rotationAngles,
            mirrorFlags,
            rotateFlags,
            startPoints,
            texts);
  ent->SetFormNumber(another->FormNumber());
}

IGESData_DirChecker IGESDimen_ToolGeneralNote::DirChecker(
  const occ::handle<IGESDimen_GeneralNote>&) const
{
  IGESData_DirChecker DC(212, 0, 105);
  DC.Structure(IGESData_DefVoid);
  DC.LineFont(IGESData_DefValue);
  DC.LineWeight(IGESData_DefValue);
  DC.Color(IGESData_DefAny);
  DC.UseFlagRequired(1);
  DC.HierarchyStatusIgnored();
  return DC;
}

void IGESDimen_ToolGeneralNote::OwnCheck(const occ::handle<IGESDimen_GeneralNote>& ent,
                                         const Interface_ShareTool&,
                                         occ::handle<Interface_Check>& ach) const
{
  if (((ent->FormNumber() < 0) || (ent->FormNumber() > 8))
      && ((ent->FormNumber() < 100) || (ent->FormNumber() > 102)) && (ent->FormNumber() != 105))
    ach->AddFail("Form Number: Not Valid");

  int upper = ent->NbStrings();
  for (int i = 1; i <= upper; i++)
  {
    if (ent->NbCharacters(i) != ent->Text(i)->Length())
    {
      char mess[80];
      Sprintf(mess, "%d : Number of Characters != Length of Text String", i);
      ach->AddFail(mess);
    }
    int mflag = ent->MirrorFlag(i);
    if ((mflag < 0) || (mflag > 2))
    {
      char mess[80];
      Sprintf(mess, "%d : Mirror flag != 0, 1, 2", i);
      ach->AddFail(mess);
    }
    int rflag = ent->RotateFlag(i);
    if ((rflag < 0) || (rflag > 1))
    {
      char mess[80];
      Sprintf(mess, "%d : Rotate flag != 0, 1", i);
      ach->AddFail(mess);
    }
  }
}

void IGESDimen_ToolGeneralNote::OwnDump(const occ::handle<IGESDimen_GeneralNote>& ent,
                                        const IGESData_IGESDumper&                dumper,
                                        Standard_OStream&                         S,
                                        const int                                 level) const
{
  int sublevel = (level > 4) ? 1 : 0;
  int upper    = ent->NbStrings();

  S << "IGESDimen_GeneralNote\n"
    << "Number of Text Strings : " << upper << "\n"
    << "Number of Characters :\n"
    << "Box Widths :\n"
    << "Box Heights :\n"
    << "Font Codes :\n"
    << "Font Entities :\n"
    << "Slant Angles :\n"
    << "Rotation Angles :\n"
    << "Mirror Flags :\n"
    << "Rotate Flags :\n"
    << "Start Points :\n"
    << "Texts : ";
  IGESData_DumpVals(S, -level, 1, ent->NbStrings(), ent->NbCharacters);
  S << "\n";
  if (level > 4)
  {
    S << "Details of each String\n";
    for (int i = 1; i <= upper; i++)
    {
      S << "[" << i << "]:\n"
        << "Number of Characters : " << ent->NbCharacters(i) << "  "
        << "Box Width  : " << ent->BoxWidth(i) << "  "
        << "Box Height : " << ent->BoxHeight(i) << "\n";
      if (ent->IsFontEntity(i))
      {
        S << "Font Entity : ";
        dumper.Dump(ent->FontEntity(i), S, sublevel);
        S << "\n";
      }
      else
        S << "Font Code : " << ent->FontCode(i) << "\n"
          << "Slant Angle : " << ent->SlantAngle(i) << "  "
          << "Rotation Angle : " << ent->RotationAngle(i) << "  "
          << "Mirror Flag : " << ent->MirrorFlag(i) << "  "
          << "Rotate Flag : " << ent->RotateFlag(i) << "\n"
          << "Start Point : ";
      IGESData_DumpXYZL(S, level, ent->StartPoint(i), ent->Location());
      S << "\nText : ";
      IGESData_DumpString(S, ent->Text(i));
      S << "\n";
    }
  }
  S << std::endl;
}
