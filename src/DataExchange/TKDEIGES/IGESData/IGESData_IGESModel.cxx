

#include <IGESData_BasicEditor.hpp>
#include <IGESData_IGESEntity.hpp>
#include <IGESData_IGESModel.hpp>
#include <Interface_Check.hpp>
#include <Interface_InterfaceModel.hpp>
#include <MoniTool_Macros.hpp>
#include <Interface_Static.hpp>
#include <Message_Msg.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <TCollection_HAsciiString.hpp>

#include <cstdio>
IMPLEMENT_STANDARD_RTTIEXT(IGESData_IGESModel, Interface_InterfaceModel)

static const char* voidline = "";

void IGESData_VerifyDate(const occ::handle<TCollection_HAsciiString>& str,
                         occ::handle<Interface_Check>&                ach,
                         const char*                                  mess);

IGESData_IGESModel::IGESData_IGESModel()
{
  thestart = new NCollection_HSequence<occ::handle<TCollection_HAsciiString>>();
}

void IGESData_IGESModel::ClearHeader()
{
  IGESData_GlobalSection newheader;
  theheader = newheader;
  thestart  = new NCollection_HSequence<occ::handle<TCollection_HAsciiString>>();
}

void IGESData_IGESModel::DumpHeader(Standard_OStream& S, const int) const
{
  int ns = thestart->Length();
  S << "****    Dump of IGES Model , Start and Global Sections   ****" << std::endl;
  if (ns > 0)
  {
    S << "****    Start Section : " << ns << " Line(s)   ****\n";
    for (int i = 1; i <= ns; i++)
      S << "[" << (i < 10 ? " " : "") << i << "]:" << thestart->Value(i)->ToCString() << std::endl;
  }
  S << "\n****    Global Section    ****\n";
  char sep = theheader.Separator();
  if (sep == ',')
    S << "[ 1]      Default Separator : " << sep;
  else
    S << "[ 1]  Non Default Separator : " << sep;
  char emk = theheader.EndMark();
  if (emk == ';')
    S << "        [ 2]      Default End Mark  : " << emk;
  else
    S << "        [ 2]  Non Default End Mark  : " << emk;
  S << "\n";
  occ::handle<TCollection_HAsciiString> str;
  str = theheader.SendName();
  if (!str.IsNull())
    S << "[ 3]  Sender                : " << str->ToCString() << std::endl;
  str = theheader.FileName();
  if (!str.IsNull())
    S << "[ 4]  (recorded) File Name  : " << str->ToCString() << std::endl;
  str = theheader.SystemId();
  if (!str.IsNull())
    S << "[ 5]  System Identification : " << str->ToCString() << std::endl;
  str = theheader.InterfaceVersion();
  if (!str.IsNull())
    S << "[ 6]  Interface Version     : " << str->ToCString() << std::endl;
  S << std::endl;
  S << "[ 7]  Integer Bits          : " << theheader.IntegerBits()
    << "          Features for Reals : " << std::endl;
  S << "[ 8]  Single Max.Power(10)  : " << theheader.MaxPower10Single();
  S << "         [ 9]  Digits   : " << theheader.MaxDigitsSingle() << "\n";
  S << "[10]  Double Max.Power(10)  : " << theheader.MaxPower10Double();
  S << "         [11]  Digits   : " << theheader.MaxDigitsDouble() << "\n\n";
  str = theheader.ReceiveName();
  if (!str.IsNull())
    S << "[12]  Receiver              : " << str->ToCString() << "\n";
  S << "[13]  Scale                 : " << theheader.Scale() << "\n";
  S << "[14]  Unit  Flag            : " << theheader.UnitFlag();

  S << "    -> Value (in CASCADE units) = " << theheader.UnitValue() << "\n";

  str = theheader.UnitName();
  if (!str.IsNull())
    S << "[15]  Unit  Name            : " << str->ToCString() << "\n\n";
  S << "[16]  Line Weight  Gradient : " << theheader.LineWeightGrad() << "\n";
  S << "[17]  Line Weight  Max Value: " << theheader.MaxLineWeight() << "\n";

  str = theheader.Date();
  if (!str.IsNull())
    S << "[18]  (Creation) Date       : " << str->ToCString() << "  i.e. "
      << IGESData_GlobalSection::NewDateString(str, 1)->ToCString() << "\n";
  S << "[19]  Resolution            : " << theheader.Resolution() << "\n";
  if (theheader.HasMaxCoord())
    S << "[20]  Maximum Coord         : " << theheader.MaxCoord() << "\n\n";
  else
    S << "[20]  Maximum Coord           not defined\n\n";

  str = theheader.AuthorName();
  if (!str.IsNull())
    S << "[21]  Author                : " << str->ToCString() << "\n";
  str = theheader.CompanyName();
  if (!str.IsNull())
    S << "[22]  Company               : " << str->ToCString() << "\n";
  int num = theheader.IGESVersion();
  S << "[23]  IGES Version Number   : " << num
    << "   -> Name : " << IGESData_BasicEditor::IGESVersionName(num);

  num = theheader.DraftingStandard();
  S << "\n[24]  Drafting Standard     : " << num;
  if (num > 0)
    S << "   -> Name : " << IGESData_BasicEditor::DraftingName(num);
  S << std::endl;

  if (theheader.HasLastChangeDate())
  {
    str = theheader.LastChangeDate();
    S << "[25]  Last Change Date      : " << str->ToCString() << "  i.e. "
      << IGESData_GlobalSection::NewDateString(str, 1)->ToCString() << std::endl;
  }
  else
    S << "[25]  Last Change Date        not defined (version IGES < 5.1)" << std::endl;

  if (theheader.HasApplicationProtocol())
  {
    str = theheader.ApplicationProtocol();
    S << "[26]  Application Protocol  : " << str->ToCString() << std::endl;
  }

  S << " ****     End of Dump      ****" << std::endl;
}

occ::handle<NCollection_HSequence<occ::handle<TCollection_HAsciiString>>> IGESData_IGESModel::
  StartSection() const
{
  return thestart;
}

int IGESData_IGESModel::NbStartLines() const
{
  return thestart->Length();
}

const char* IGESData_IGESModel::StartLine(const int num) const
{
  if (num > 0 && num <= thestart->Length())
    return thestart->Value(num)->ToCString();
  return voidline;
}

void IGESData_IGESModel::ClearStartSection()
{
  thestart->Clear();
}

void IGESData_IGESModel::SetStartSection(
  const occ::handle<NCollection_HSequence<occ::handle<TCollection_HAsciiString>>>& list,
  const bool                                                                       copy)
{
  if (copy)
  {
    thestart = new NCollection_HSequence<occ::handle<TCollection_HAsciiString>>();
    if (list.IsNull())
      return;
    int i, nb = list->Length();
    for (i = 1; i <= nb; i++)
      thestart->Append(new TCollection_HAsciiString(list->Value(i)->ToCString()));
  }
  else if (list.IsNull())
    thestart = new NCollection_HSequence<occ::handle<TCollection_HAsciiString>>();
  else
    thestart = list;
}

void IGESData_IGESModel::AddStartLine(const char* line, const int atnum)
{
  if (atnum <= 0 || atnum > thestart->Length())
    thestart->Append(new TCollection_HAsciiString(line));
  else
    thestart->InsertBefore(atnum, new TCollection_HAsciiString(line));
}

void IGESData_IGESModel::SetGlobalSection(const IGESData_GlobalSection& header)
{
  theheader = header;
}

bool IGESData_IGESModel::ApplyStatic(const char* param)
{
  if (param[0] == '\0')
  {

    ApplyStatic("receiver");
    ApplyStatic("author");
    ApplyStatic("company");
    return true;
  }

  const char* val;
  if (param[0] == 'r')
  {
    val = Interface_Static::CVal("write.iges.header.receiver");
    if (!val || val[0] == '\0')
      return false;
    theheader.SetReceiveName(new TCollection_HAsciiString(val));
  }
  if (param[0] == 'a')
  {
    val = Interface_Static::CVal("write.iges.header.author");
    if (!val || val[0] == '\0')
      return false;
    theheader.SetAuthorName(new TCollection_HAsciiString(val));
  }
  if (param[0] == 'c')
  {
    val = Interface_Static::CVal("write.iges.header.company");
    if (!val || val[0] == '\0')
      return false;
    theheader.SetCompanyName(new TCollection_HAsciiString(val));
  }
  return true;
}

occ::handle<IGESData_IGESEntity> IGESData_IGESModel::Entity(const int num) const
{
  return GetCasted(IGESData_IGESEntity, Value(num));
}

int IGESData_IGESModel::DNum(const occ::handle<IGESData_IGESEntity>& ent) const
{
  int num = Number(ent);
  if (num == 0)
    return 0;
  else
    return 2 * num - 1;
}

void IGESData_IGESModel::GetFromAnother(const occ::handle<Interface_InterfaceModel>& other)
{
  DeclareAndCast(IGESData_IGESModel, another, other);
  theheader = another->GlobalSection();
  theheader.CopyRefs();
  SetStartSection(another->StartSection(), true);
}

occ::handle<Interface_InterfaceModel> IGESData_IGESModel::NewEmptyModel() const
{
  return new IGESData_IGESModel;
}

void IGESData_IGESModel::VerifyCheck(occ::handle<Interface_Check>& ach) const
{

  char del[2];
  del[0] = theheader.Separator();
  del[1] = theheader.EndMark();

  if (del[0] == del[1])
  {
    Message_Msg Msg40("XSTEP_40");
    ach->SendFail(Msg40);
  }
  for (int i = 0; i <= 1; i++)
  {
    if (del[i] <= 32 || del[i] == 43 || del[i] == 45 || del[i] == 46
        || (del[i] >= 48 && del[i] <= 57) || del[i] == 68 || del[i] == 69 || del[i] == 72
        || del[i] >= 127)
    {

      if (i == 0)
      {
        Message_Msg Msg41("XSTEP_41");
        ach->SendFail(Msg41);
      }

      else
      {
        Message_Msg Msg42("XSTEP_42");
        ach->SendFail(Msg42);
      }
    }
  }

  if (theheader.MaxPower10Single() <= 0)
  {
    Message_Msg Msg43("XSTEP_43");
    ach->SendFail(Msg43);
  }

  if (theheader.MaxDigitsSingle() <= 0)
  {
    Message_Msg Msg44("XSTEP_44");
    ach->SendFail(Msg44);
  }

  if (theheader.MaxPower10Double() <= 0)
  {
    Message_Msg Msg45("XSTEP_45");
    ach->SendFail(Msg45);
  }

  if (theheader.MaxDigitsDouble() <= 0)
  {
    Message_Msg Msg46("XSTEP_46");
    ach->SendFail(Msg46);
  }

  if (theheader.Scale() <= 0.)
  {
    Message_Msg Msg47("XSTEP_47");
    ach->SendFail(Msg47);
  }

  int unf = theheader.UnitFlag();

  if (unf < 1 || unf > 11)
  {
    Message_Msg Msg48("XSTEP_48");
    ach->SendFail(Msg48);
  }

  if (theheader.UnitName().IsNull())
  {

    if (unf == 3)
    {
      Message_Msg Msg50("XSTEP_50");
      ach->SendFail(Msg50);
    }
  }
  else
  {
    const char* unm  = theheader.UnitName()->ToCString();
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
        Message_Msg Msg48("XSTEP_48");
        ach->SendFail(Msg48);
        break;
    }

    if (!unok)
    {
      Message_Msg Msg51("XSTEP_51");
      ach->SendFail(Msg51);
    }
  }

  IGESData_VerifyDate(theheader.Date(), ach, "Creation Date");

  if (theheader.Resolution() <= 0.)
  {
    Message_Msg Msg52("XSTEP_52");
    ach->SendFail(Msg52);
  }

  if (theheader.IGESVersion() < 1
      || theheader.IGESVersion() > IGESData_BasicEditor::IGESVersionMax())
  {
    Message_Msg Msg53("XSTEP_53");
    ach->SendWarning(Msg53);
  }

  if (theheader.DraftingStandard() < 0
      || theheader.DraftingStandard() > IGESData_BasicEditor::DraftingMax())
  {
    Message_Msg Msg54("XSTEP_54");
    ach->SendWarning(Msg54);
  }

  if (theheader.IGESVersion() >= 9)
  {

    if (!theheader.HasLastChangeDate())
    {
      Message_Msg Msg55("XSTEP_55");
      ach->SendWarning(Msg55);
    }
    else
      IGESData_VerifyDate(theheader.LastChangeDate(), ach, "Last Change Date");
  }
}

void IGESData_VerifyDate(const occ::handle<TCollection_HAsciiString>& str,
                         occ::handle<Interface_Check>&                ach,
                         const char*                                  mess)
{

  Message_Msg Msg57("XSTEP_57");

  if (str.IsNull())
  {
    ach->SendFail(Msg57);
    return;
  }

  const occ::handle<TCollection_HAsciiString>& stdvar = str;
  if (strcmp(mess, "Last Change Date") == 0)
    Msg57.Arg(25);
  else
    Msg57.Arg(18);
  if (((stdvar->Length() != 13) && (stdvar->Length() != 15)) || !stdvar->IsRealValue())
    ach->SendFail(Msg57);

  else if ((stdvar->Value(3) > '1' || (stdvar->Value(3) == '1' && stdvar->Value(4) > '2'))
           && (stdvar->Length() == 13))
    ach->SendFail(Msg57);

  else if ((stdvar->Value(5) > '3' || (stdvar->Value(5) == '3' && stdvar->Value(6) > '1'))
           && (stdvar->Length() == 13))
    ach->SendFail(Msg57);
  else if ((stdvar->Value(7) != '.' || stdvar->Value(10) > '5' || stdvar->Value(12) > '5')
           && (stdvar->Length() == 13))
    ach->SendFail(Msg57);
  else if ((stdvar->Value(8) > '2' || (stdvar->Value(8) == '2' && stdvar->Value(9) > '3'))
           && (stdvar->Length() == 13))
    ach->SendFail(Msg57);

  else if ((stdvar->Value(5) > '1' || (stdvar->Value(5) == '1' && stdvar->Value(6) > '2'))
           && (stdvar->Length() == 15))
    ach->SendFail(Msg57);
  else if ((stdvar->Value(7) > '3' || (stdvar->Value(7) == '3' && stdvar->Value(8) > '1'))
           && (stdvar->Length() == 15))
    ach->SendFail(Msg57);
  else if ((stdvar->Value(9) != '.' || stdvar->Value(12) > '5' || stdvar->Value(14) > '5')
           && (stdvar->Length() == 15))
    ach->SendFail(Msg57);
  else if ((stdvar->Value(10) > '2' || (stdvar->Value(10) == '2' && stdvar->Value(11) > '3'))
           && (stdvar->Length() == 15))
    ach->SendFail(Msg57);
}

void IGESData_IGESModel::SetLineWeights(const double defw)
{
  int    nb   = NbEntities();
  int    lwg  = theheader.LineWeightGrad();
  double maxw = theheader.MaxLineWeight();
  if (lwg > 0)
  {
    maxw = maxw / lwg;
    lwg  = 1;
  }
  for (int i = 1; i <= nb; i++)
    Entity(i)->SetLineWeight(defw, maxw, lwg);
}

void IGESData_IGESModel::ClearLabels() {}

void IGESData_IGESModel::PrintLabel(const occ::handle<Standard_Transient>& ent,
                                    Standard_OStream&                      S) const
{
  DeclareAndCast(IGESData_IGESEntity, igesent, ent);
  if (igesent.IsNull())
    S << "Null";
  else
  {
    int num = Number(ent);
    if (num == 0)
      S << "??";
    else
      S << "D" << (2 * num - 1);
  }
}

void IGESData_IGESModel::PrintToLog(const occ::handle<Standard_Transient>& ent,
                                    Standard_OStream&                      S) const
{
  DeclareAndCast(IGESData_IGESEntity, igesent, ent);
  if (!igesent.IsNull())
  {
    int num = Number(ent);
    if (num == 0)
      S << "??";
    else
    {
      S << " DE : " << (2 * num - 1) << " type : " << igesent->TypeNumber();
    }
  }
}

void IGESData_IGESModel::PrintInfo(const occ::handle<Standard_Transient>& ent,
                                   Standard_OStream&                      S) const
{
  DeclareAndCast(IGESData_IGESEntity, igesent, ent);
  if (igesent.IsNull())
    S << "(NOT IGES)";
  else
  {
    int num = Number(ent);
    if (num == 0)
      S << "??";
    else
    {
      S << (2 * num - 1) << "type " << Type(ent)->Name();
    }
  }
}

occ::handle<TCollection_HAsciiString> IGESData_IGESModel::StringLabel(
  const occ::handle<Standard_Transient>& ent) const
{
  occ::handle<TCollection_HAsciiString> label;
  DeclareAndCast(IGESData_IGESEntity, igesent, ent);
  if (igesent.IsNull())
    return new TCollection_HAsciiString("(NOT IGES)");
  else
  {
    char text[20];
    int  num = Number(ent);
    if (num > 0)
      Sprintf(text, "D%d", 2 * num - 1);
    else
      Sprintf(text, "D0...");
    label = new TCollection_HAsciiString(text);
  }
  return label;
}
