#include <IGESData_DirChecker.hpp>
#include <IGESData_Dump.hpp>
#include <IGESData_IGESDumper.hpp>
#include <IGESData_IGESReaderData.hpp>
#include <IGESData_IGESWriter.hpp>
#include <IGESData_ParamReader.hpp>
#include <IGESDefs_AttributeDef.hpp>
#include <IGESDefs_HArray1OfHArray1OfTextDisplayTemplate.hpp>
#include <IGESDefs_ToolAttributeDef.hpp>
#include <IGESGraph_TextDisplayTemplate.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Interface_Check.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_EntityIterator.hpp>
#include <TCollection_HAsciiString.hpp>
#include <MoniTool_Macros.hpp>
#include <Interface_ShareTool.hpp>
#include <Message_Messenger.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Transient.hpp>

#include <cstdio>

IGESDefs_ToolAttributeDef::IGESDefs_ToolAttributeDef() = default;

void IGESDefs_ToolAttributeDef::ReadOwnParams(const occ::handle<IGESDefs_AttributeDef>&   ent,
                                              const occ::handle<IGESData_IGESReaderData>& IR,
                                              IGESData_ParamReader&                       PR) const
{

  occ::handle<TCollection_HAsciiString>                             aName;
  int                                                               aListType;
  occ::handle<NCollection_HArray1<int>>                             attrTypes;
  occ::handle<NCollection_HArray1<int>>                             attrValueDataTypes;
  occ::handle<NCollection_HArray1<int>>                             attrValueCounts;
  occ::handle<NCollection_HArray1<occ::handle<Standard_Transient>>> attrValues;
  occ::handle<IGESDefs_HArray1OfHArray1OfTextDisplayTemplate>       attrValuePointers;
  int                                                               nbval;
  int                                                               fn = ent->FormNumber();

  if (PR.DefinedElseSkip())

    PR.ReadText(PR.Current(), "Attribute Table Name", aName);

  PR.ReadInteger(PR.Current(), "Attribute List Type", aListType);

  bool st = PR.ReadInteger(PR.Current(), "Number of Attributes", nbval);
  if (st && nbval > 0)
  {
    attrTypes          = new NCollection_HArray1<int>(1, nbval);
    attrValueDataTypes = new NCollection_HArray1<int>(1, nbval);
    attrValueCounts    = new NCollection_HArray1<int>(1, nbval);
    if (fn > 0)
      attrValues = new NCollection_HArray1<occ::handle<Standard_Transient>>(1, nbval);
    if (fn > 1)
      attrValuePointers = new IGESDefs_HArray1OfHArray1OfTextDisplayTemplate(1, nbval);
  }
  else
    PR.AddFail("Number of Attributes: Not Positive");

  if (!attrTypes.IsNull())
    for (int i = 1; i <= nbval; i++)
    {
      int attrType;
      int attrValueDataType;
      int avc;

      occ::handle<NCollection_HArray1<occ::handle<IGESGraph_TextDisplayTemplate>>> attrValuePointer;

      if (PR.ReadInteger(PR.Current(), "Attribute Type", attrType))
        attrTypes->SetValue(i, attrType);

      st = PR.ReadInteger(PR.Current(), "Attribute Data Type", attrValueDataType);
      if (st)
        attrValueDataTypes->SetValue(i, attrValueDataType);

      if (PR.DefinedElseSkip())
        st = PR.ReadInteger(PR.Current(), "Attribute Value Count", avc);
      else
        avc = 1;

      if (st)
      {
        attrValueCounts->SetValue(i, avc);
        if (fn > 1)
          attrValuePointer =
            new NCollection_HArray1<occ::handle<IGESGraph_TextDisplayTemplate>>(1, avc);
      }

      if (!attrValues.IsNull())
        if (fn > 0)
        {
          occ::handle<NCollection_HArray1<int>>                                   attrInt;
          occ::handle<NCollection_HArray1<double>>                                attrReal;
          occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>> attrStr;
          occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>      attrEnt;
          switch (attrValueDataType)
          {
            case 1:
              attrInt = new NCollection_HArray1<int>(1, avc);
              attrValues->SetValue(i, attrInt);
              break;
            case 2:
              attrReal = new NCollection_HArray1<double>(1, avc);
              attrValues->SetValue(i, attrReal);
              break;
            case 3:
              attrStr = new NCollection_HArray1<occ::handle<TCollection_HAsciiString>>(1, avc);
              attrValues->SetValue(i, attrStr);
              break;
            case 4:
              attrEnt = new NCollection_HArray1<occ::handle<IGESData_IGESEntity>>(1, avc);
              attrValues->SetValue(i, attrEnt);
              break;
            case 6:
              attrInt = new NCollection_HArray1<int>(1, avc);
              attrValues->SetValue(i, attrInt);
              break;
            default:
              break;
          }
          for (int j = 1; j <= avc; j++)
          {
            switch (attrValueDataType)
            {
              case 0:
              {
                PR.SetCurrentNumber(PR.CurrentNumber() + 1);

                break;
              }
              case 1:
              {
                int temp;

                if (PR.ReadInteger(PR.Current(), "Attribute Value", temp))
                  attrInt->SetValue(j, temp);
              }
              break;
              case 2:
              {
                double temp;

                if (PR.ReadReal(PR.Current(), "Attribute Value", temp))
                  attrReal->SetValue(j, temp);
              }
              break;
              case 3:
              {
                occ::handle<TCollection_HAsciiString> temp;

                if (PR.ReadText(PR.Current(), "Attribute Value", temp))
                  attrStr->SetValue(j, temp);
              }
              break;
              case 4:
              {
                occ::handle<IGESData_IGESEntity> temp;

                if (PR.ReadEntity(IR, PR.Current(), "Attribute Value", temp))
                  attrEnt->SetValue(j, temp);
              }
              break;
              case 5:
                PR.SetCurrentNumber(PR.CurrentNumber() + 1);
                break;
              case 6:
              {
                bool temp;

                if (PR.ReadBoolean(PR.Current(), "Attribute Value", temp))
                  attrInt->SetValue(j, (temp ? 1 : 0));
              }
              break;
            }
            if (fn == 2)
            {
              occ::handle<IGESGraph_TextDisplayTemplate> tempText;

              if (PR.ReadEntity(IR,
                                PR.Current(),
                                "Attribute Val. Pointer",
                                STANDARD_TYPE(IGESGraph_TextDisplayTemplate),
                                tempText))
                attrValuePointer->SetValue(j, tempText);
            }
          }
          if (fn == 2)
            attrValuePointers->SetValue(i, attrValuePointer);
        }
    }

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(), ent);
  ent->Init(aName,
            aListType,
            attrTypes,
            attrValueDataTypes,
            attrValueCounts,
            attrValues,
            attrValuePointers);
}

void IGESDefs_ToolAttributeDef::WriteOwnParams(const occ::handle<IGESDefs_AttributeDef>& ent,
                                               IGESData_IGESWriter&                      IW) const
{
  if (ent->HasTableName())
    IW.Send(ent->TableName());
  else
    IW.SendVoid();
  IW.Send(ent->ListType());
  int upper = ent->NbAttributes();
  IW.Send(upper);

  for (int i = 1; i <= upper; i++)
  {
    int check = ent->AttributeValueDataType(i);
    int count = ent->AttributeValueCount(i);
    IW.Send(ent->AttributeType(i));
    IW.Send(check);
    IW.Send(count);
    if (ent->FormNumber() > 0)
    {
      for (int j = 1; j <= count; j++)
      {
        switch (check)
        {
          case 0:
            IW.SendVoid();
            break;
          case 1:
            IW.Send(ent->AttributeAsInteger(i, j));
            break;
          case 2:
            IW.Send(ent->AttributeAsReal(i, j));
            break;
          case 3:
            IW.Send(ent->AttributeAsString(i, j));
            break;
          case 4:
            IW.Send(ent->AttributeAsEntity(i, j));
            break;
          case 5:
            IW.SendVoid();
            break;
          case 6:
            IW.SendBoolean(ent->AttributeAsLogical(i, j));
            break;
          default:
            break;
        }
        if (ent->FormNumber() == 2)
          IW.Send(ent->AttributeTextDisplay(i, j));
      }
    }
  }
}

void IGESDefs_ToolAttributeDef::OwnShared(const occ::handle<IGESDefs_AttributeDef>& ent,
                                          Interface_EntityIterator&                 iter) const
{
  int upper = ent->NbAttributes();
  for (int i = 1; i <= upper; i++)
  {
    int check = ent->AttributeValueDataType(i);
    int count = ent->AttributeValueCount(i);
    if (ent->FormNumber() > 0)
    {
      for (int j = 1; j <= count; j++)
      {
        if (check == 4)
          iter.GetOneItem(ent->AttributeAsEntity(i, j));
        if (ent->FormNumber() == 2)
          iter.GetOneItem(ent->AttributeTextDisplay(i, j));
      }
    }
  }
}

void IGESDefs_ToolAttributeDef::OwnCopy(const occ::handle<IGESDefs_AttributeDef>& another,
                                        const occ::handle<IGESDefs_AttributeDef>& ent,
                                        Interface_CopyTool&                       TC) const
{
  occ::handle<TCollection_HAsciiString> aName;
  if (!another->TableName().IsNull())
    aName = new TCollection_HAsciiString(another->TableName());
  int aListType = another->ListType();

  occ::handle<NCollection_HArray1<int>>                             attrTypes;
  occ::handle<NCollection_HArray1<int>>                             attrValueDataTypes;
  occ::handle<NCollection_HArray1<int>>                             attrValueCounts;
  occ::handle<NCollection_HArray1<occ::handle<Standard_Transient>>> attrValues;
  occ::handle<IGESDefs_HArray1OfHArray1OfTextDisplayTemplate>       attrValuePointers;
  int                                                               nbval = another->NbAttributes();

  attrTypes          = new NCollection_HArray1<int>(1, nbval);
  attrValueDataTypes = new NCollection_HArray1<int>(1, nbval);
  attrValueCounts    = new NCollection_HArray1<int>(1, nbval);
  if (another->HasValues())
    attrValues = new NCollection_HArray1<occ::handle<Standard_Transient>>(1, nbval);
  if (another->HasTextDisplay())
    attrValuePointers = new IGESDefs_HArray1OfHArray1OfTextDisplayTemplate(1, nbval);

  for (int i = 1; i <= nbval; i++)
  {
    int attrType = another->AttributeType(i);
    attrTypes->SetValue(i, attrType);
    int attrValueDataType = another->AttributeValueDataType(i);
    attrValueDataTypes->SetValue(i, attrValueDataType);
    int avc = another->AttributeValueCount(i);
    attrValueCounts->SetValue(i, avc);
    occ::handle<NCollection_HArray1<occ::handle<IGESGraph_TextDisplayTemplate>>> attrValuePointer;

    if (another->HasTextDisplay())
      attrValuePointer =
        new NCollection_HArray1<occ::handle<IGESGraph_TextDisplayTemplate>>(1, avc);

    if (another->HasValues())
    {
      occ::handle<NCollection_HArray1<int>>                                   attrInt;
      occ::handle<NCollection_HArray1<double>>                                attrReal;
      occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>> attrStr;
      occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>      attrEnt;
      switch (attrValueDataType)
      {
        case 1:
          attrInt = new NCollection_HArray1<int>(1, avc);
          attrValues->SetValue(i, attrInt);
          break;
        case 2:
          attrReal = new NCollection_HArray1<double>(1, avc);
          attrValues->SetValue(i, attrReal);
          break;
        case 3:
          attrStr = new NCollection_HArray1<occ::handle<TCollection_HAsciiString>>(1, avc);
          attrValues->SetValue(i, attrStr);
          break;
        case 4:
          attrEnt = new NCollection_HArray1<occ::handle<IGESData_IGESEntity>>(1, avc);
          attrValues->SetValue(i, attrEnt);
          break;
        case 6:
          attrInt = new NCollection_HArray1<int>(1, avc);
          attrValues->SetValue(i, attrInt);
          break;
        default:
          break;
      }
      for (int j = 1; j <= avc; j++)
      {
        switch (attrValueDataType)
        {
          case 0:
            break;
          case 1:
            attrInt->SetValue(j, another->AttributeAsInteger(i, j));
            break;
          case 2:
            attrReal->SetValue(j, another->AttributeAsReal(i, j));
            break;
          case 3:
            attrStr->SetValue(j, new TCollection_HAsciiString(another->AttributeAsString(i, j)));
            break;
          case 4:
          {
            DeclareAndCast(IGESData_IGESEntity,
                           Ent,
                           TC.Transferred(another->AttributeAsEntity(i, j)));
            attrEnt->SetValue(j, Ent);
          }
          break;
          case 5:
            break;
          case 6:
            attrInt->SetValue(j, (another->AttributeAsLogical(i, j) ? 1 : 0));
            break;
          default:
            break;
        }
        if (another->HasTextDisplay())
        {
          DeclareAndCast(IGESGraph_TextDisplayTemplate,
                         temptext,
                         TC.Transferred(another->AttributeTextDisplay(i, j)));
          attrValuePointer->SetValue(j, temptext);
        }
      }
      if (another->HasTextDisplay())
        attrValuePointers->SetValue(i, attrValuePointer);
    }
  }
  ent->Init(aName,
            aListType,
            attrTypes,
            attrValueDataTypes,
            attrValueCounts,
            attrValues,
            attrValuePointers);
}

IGESData_DirChecker IGESDefs_ToolAttributeDef::DirChecker(
  const occ::handle<IGESDefs_AttributeDef>&) const
{
  IGESData_DirChecker DC(322, 0, 2);
  DC.Structure(IGESData_DefVoid);
  DC.LineFont(IGESData_DefAny);
  DC.LineWeight(IGESData_DefValue);
  DC.Color(IGESData_DefAny);
  DC.BlankStatusIgnored();
  DC.SubordinateStatusRequired(0);
  DC.UseFlagRequired(2);
  DC.GraphicsIgnored(1);
  return DC;
}

void IGESDefs_ToolAttributeDef::OwnCheck(const occ::handle<IGESDefs_AttributeDef>& ent,
                                         const Interface_ShareTool&,
                                         occ::handle<Interface_Check>& ach) const
{
  int nb = ent->NbAttributes();
  int fn = ent->FormNumber();
  for (int i = 1; i <= nb; i++)
  {
    char mess[80];
    if (ent->AttributeType(i) < 0 || ent->AttributeType(i) > 9999)
    {
      Sprintf(mess, "Attribute Type n0.%d not in <0 - 9999>", ent->AttributeType(i));
      ach->AddFail(mess);
    }
    int aty = ent->AttributeValueDataType(i);
    if (aty < 0 || aty > 6)
    {
      Sprintf(mess, "Attribute Value Data Type n0.%d not in <0 - 6>", aty);
      ach->AddFail(mess);
    }
    if (ent->AttributeValueCount(i) <= 0)
      continue;
    occ::handle<Standard_Transient> list = ent->AttributeList(i);
    if (fn > 0 && ent.IsNull())
    {
      if (aty == 0 || aty == 5)
        continue;
      Sprintf(mess, "Form Number > 0 and Attribute Value List n0.%d undefined", aty);
      ach->AddFail(mess);
      continue;
    }
    else if (fn == 0)
      continue;
    mess[0] = '\0';
    switch (aty)
    {
      case 1:
        if (!list->IsKind(STANDARD_TYPE(NCollection_HArray1<int>)))
        {
          Sprintf(mess, "Attribute List n0.%d (Integers) badly defined", aty);
        }
        break;
      case 2:
        if (!list->IsKind(STANDARD_TYPE(NCollection_HArray1<double>)))
        {
          Sprintf(mess, "Attribute List n0.%d (Reals) badly defined", aty);
        }
        break;
      case 3:
        if (!list->IsKind(
              STANDARD_TYPE(NCollection_HArray1<occ::handle<TCollection_HAsciiString>>)))
        {
          Sprintf(mess, "Attribute List n0.%d (Strings) badly defined", aty);
        }
        break;
      case 4:
        if (!list->IsKind(STANDARD_TYPE(NCollection_HArray1<occ::handle<IGESData_IGESEntity>>)))
        {
          Sprintf(mess, "Attribute List n0.%d (IGES Pointers) badly defined", aty);
        }
        break;
      case 6:
        if (!list->IsKind(STANDARD_TYPE(NCollection_HArray1<int>)))
        {
          Sprintf(mess, "Attribute List n0.%d (Logicals i.e. Integers) badly defined", aty);
        }
        break;
      default:
        break;
    }
    if (mess[0] != '\0')
      ach->AddFail(mess);
  }
}

void IGESDefs_ToolAttributeDef::OwnDump(const occ::handle<IGESDefs_AttributeDef>& ent,
                                        const IGESData_IGESDumper&                dumper,
                                        Standard_OStream&                         S,
                                        const int                                 level) const
{
  int sublevel = (level > 4) ? 1 : 0;

  S << "IGESDefs_AttributeDef\n"
    << "Attribute Table Name: ";
  IGESData_DumpString(S, ent->TableName());
  S << "\n"
    << "Attribute List Type  : " << ent->ListType() << "\n"
    << "Number of Attributes : " << ent->NbAttributes() << "\n"
    << "Attribute Types :\n"
    << "Attribute Value Data Types :\n"
    << "Attribute Value Counts :\n";
  if (ent->HasValues())
    S << "Attribute Values :\n";
  if (ent->HasTextDisplay())
    S << "Attribute Value Entities :\n";
  IGESData_DumpVals(S, -level, 1, ent->NbAttributes(), ent->AttributeType);
  S << "\n";
  if (level > 4)
  {
    int upper = ent->NbAttributes();
    for (int i = 1; i <= upper; i++)
    {
      int avc = ent->AttributeValueCount(i);
      int typ = ent->AttributeValueDataType(i);
      S << "[" << i << "]:  "
        << "Attribute Type : " << ent->AttributeType(i) << "  "
        << "Value Data Type : " << typ;
      switch (typ)
      {
        case 0:
          S << "  (Void)";
          break;
        case 1:
          S << " : Integer ";
          break;
        case 2:
          S << " : Real    ";
          break;
        case 3:
          S << " : String  ";
          break;
        case 4:
          S << " : Entity  ";
          break;
        case 5:
          S << " (Not Used)";
          break;
        case 6:
          S << " : Logical ";
          break;
        default:
          break;
      }
      S << "   Count : " << avc << "\n";
      if (ent->HasValues())
      {
        if (level <= 5)
        {
          S << " [ content (Values) : ask level > 5 ]\n";
          continue;
        }
        for (int j = 1; j <= avc; j++)
        {
          S << "[" << j << "]: ";
          switch (ent->AttributeValueDataType(i))
          {
            case 0:
              S << "(Void) ";
              break;
            case 1:
              S << ent->AttributeAsInteger(i, j);
              break;
            case 2:
              S << ent->AttributeAsReal(i, j);
              break;
            case 3:
              IGESData_DumpString(S, ent->AttributeAsString(i, j));
              break;
            case 4:
              dumper.Dump(ent->AttributeAsEntity(i, j), S, level - 5);
              break;
            case 5:
              S << "(Not Used)";
              break;
            case 6:
              S << (ent->AttributeAsLogical(i, j) ? "True" : "False");
              break;
            default:
              break;
          }
          if (ent->HasTextDisplay())
          {
            S << "  Attribute Value Pointer : ";
            dumper.Dump(ent->AttributeTextDisplay(i, j), S, sublevel);
          }
          S << std::endl;
        }
      }
    }
  }
  S << std::endl;
}
