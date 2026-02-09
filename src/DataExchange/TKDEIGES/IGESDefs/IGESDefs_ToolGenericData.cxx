#include <IGESData_DirChecker.hpp>
#include <IGESData_Dump.hpp>
#include <IGESData_IGESDumper.hpp>
#include <IGESData_IGESReaderData.hpp>
#include <IGESData_IGESWriter.hpp>
#include <IGESData_ParamReader.hpp>
#include <IGESDefs_GenericData.hpp>
#include <IGESDefs_ToolGenericData.hpp>
#include <Interface_Check.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_EntityIterator.hpp>
#include <MoniTool_Macros.hpp>
#include <Interface_ShareTool.hpp>
#include <Message_Messenger.hpp>
#include <TCollection_HAsciiString.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Transient.hpp>

IGESDefs_ToolGenericData::IGESDefs_ToolGenericData() = default;

void IGESDefs_ToolGenericData::ReadOwnParams(const occ::handle<IGESDefs_GenericData>&    ent,
                                             const occ::handle<IGESData_IGESReaderData>& IR,
                                             IGESData_ParamReader&                       PR) const
{

  int                                                               i, num;
  int                                                               tempNbPropVal;
  occ::handle<TCollection_HAsciiString>                             tempName;
  occ::handle<NCollection_HArray1<int>>                             tempTypes;
  occ::handle<NCollection_HArray1<occ::handle<Standard_Transient>>> tempValues;

  PR.ReadInteger(PR.Current(), "Number of property values", tempNbPropVal);

  PR.ReadText(PR.Current(), "Property Name", tempName);

  bool st = PR.ReadInteger(PR.Current(), "Number of TYPE/VALUEs", num);
  if (st && num > 0)
  {
    tempTypes  = new NCollection_HArray1<int>(1, num);
    tempValues = new NCollection_HArray1<occ::handle<Standard_Transient>>(1, num);
  }
  else
    PR.AddFail("Number of TYPE/VALUEs: Not Positive");

  if (!tempTypes.IsNull() && !tempValues.IsNull())
    for (i = 1; i <= num; i++)
    {
      int tempTyp;
      PR.ReadInteger(PR.Current(), "Type code", tempTyp);
      tempTypes->SetValue(i, tempTyp);
      switch (tempTyp)
      {
        case 0:
          PR.SetCurrentNumber(PR.CurrentNumber() + 1);
          break;
        case 1:
        {
          occ::handle<NCollection_HArray1<int>> tempObj;

          if (PR.ReadInts(PR.CurrentList(1), "Integer value", tempObj))
            tempValues->SetValue(i, tempObj);
        }
        break;
        case 2:
        {
          occ::handle<NCollection_HArray1<double>> tempObj;

          if (PR.ReadReals(PR.CurrentList(1), "Real value", tempObj))
            tempValues->SetValue(i, tempObj);
        }
        break;
        case 3:
        {
          occ::handle<TCollection_HAsciiString> tempObj;

          if (PR.ReadText(PR.Current(), "String value", tempObj))
            tempValues->SetValue(i, tempObj);
        }
        break;
        case 4:
        {
          occ::handle<IGESData_IGESEntity> tempEntity;

          if (PR.ReadEntity(IR, PR.Current(), "Entity value", tempEntity))
            tempValues->SetValue(i, tempEntity);
        }
        break;
        case 5:
          PR.SetCurrentNumber(PR.CurrentNumber() + 1);
          break;
        case 6:
        {
          occ::handle<NCollection_HArray1<int>> tempObj = new NCollection_HArray1<int>(1, 1);
          bool                                  tempBool;

          if (PR.ReadBoolean(PR.Current(), "Boolean value", tempBool))
          {
            tempObj->SetValue(1, (tempBool ? 1 : 0));
            tempValues->SetValue(i, tempObj);
          }
        }
        break;
      }
    }

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(), ent);
  ent->Init(tempNbPropVal, tempName, tempTypes, tempValues);
}

void IGESDefs_ToolGenericData::WriteOwnParams(const occ::handle<IGESDefs_GenericData>& ent,
                                              IGESData_IGESWriter&                     IW) const
{
  int i, num;
  IW.Send(ent->NbPropertyValues());
  IW.Send(ent->Name());
  IW.Send(ent->NbTypeValuePairs());
  for (num = ent->NbTypeValuePairs(), i = 1; i <= num; i++)
  {
    IW.Send(ent->Type(i));
    switch (ent->Type(i))
    {
      case 0:
        IW.SendVoid();
        break;
      case 1:
        IW.Send(ent->ValueAsInteger(i));
        break;
      case 2:
        IW.Send(ent->ValueAsReal(i));
        break;
      case 3:
        IW.Send(ent->ValueAsString(i));
        break;
      case 4:
        IW.Send(ent->ValueAsEntity(i));
        break;
      case 5:
        IW.SendVoid();
        break;
      case 6:
        IW.SendBoolean(ent->ValueAsLogical(i));
        break;
      default:
        break;
    }
  }
}

void IGESDefs_ToolGenericData::OwnShared(const occ::handle<IGESDefs_GenericData>& ent,
                                         Interface_EntityIterator&                iter) const
{
  int i, num;
  for (num = ent->NbTypeValuePairs(), i = 1; i <= num; i++)
  {
    if (ent->Type(i) == 4)
      iter.GetOneItem(ent->ValueAsEntity(i));
  }
}

void IGESDefs_ToolGenericData::OwnCopy(const occ::handle<IGESDefs_GenericData>& another,
                                       const occ::handle<IGESDefs_GenericData>& ent,
                                       Interface_CopyTool&                      TC) const
{
  int                                   num           = another->NbTypeValuePairs();
  int                                   tempNbPropVal = another->NbPropertyValues();
  occ::handle<TCollection_HAsciiString> tempName  = new TCollection_HAsciiString(another->Name());
  occ::handle<NCollection_HArray1<int>> tempTypes = new NCollection_HArray1<int>(1, num);
  occ::handle<NCollection_HArray1<occ::handle<Standard_Transient>>> tempValues =
    new NCollection_HArray1<occ::handle<Standard_Transient>>(1, num);

  for (int i = 1; i <= num; i++)
  {
    tempTypes->SetValue(i, another->Type(i));
    switch (another->Type(i))
    {
      case 0:
        break;
      case 1:
      {
        occ::handle<NCollection_HArray1<int>> tempObj = new NCollection_HArray1<int>(1, 1);
        tempObj->SetValue(1, another->ValueAsInteger(i));
        tempValues->SetValue(i, tempObj);
      }
      break;
      case 2:
      {
        occ::handle<NCollection_HArray1<double>> tempObj = new NCollection_HArray1<double>(1, 1);
        tempObj->SetValue(1, another->ValueAsReal(i));
        tempValues->SetValue(i, tempObj);
      }
      break;
      case 3:
      {
        tempValues->SetValue(i, new TCollection_HAsciiString(another->ValueAsString(i)));
      }
      break;
      case 4:
      {
        DeclareAndCast(IGESData_IGESEntity, tempObj, TC.Transferred(another->ValueAsEntity(i)));
        tempValues->SetValue(i, tempObj);
      }
      break;
      case 5:
        break;
      case 6:
      {
        occ::handle<NCollection_HArray1<int>> tempObj = new NCollection_HArray1<int>(1, 1);
        tempObj->SetValue(1, (another->ValueAsLogical(i) ? 1 : 0));
        tempValues->SetValue(i, tempObj);
      }
      break;
    }
  }
  ent->Init(tempNbPropVal, tempName, tempTypes, tempValues);
}

IGESData_DirChecker IGESDefs_ToolGenericData::DirChecker(
  const occ::handle<IGESDefs_GenericData>&) const
{
  IGESData_DirChecker DC(406, 27);
  DC.Structure(IGESData_DefVoid);
  DC.GraphicsIgnored();
  DC.LineFont(IGESData_DefVoid);
  DC.LineWeight(IGESData_DefVoid);
  DC.Color(IGESData_DefVoid);
  DC.BlankStatusIgnored();
  DC.SubordinateStatusRequired(1);
  DC.UseFlagRequired(2);
  DC.HierarchyStatusIgnored();
  return DC;
}

void IGESDefs_ToolGenericData::OwnCheck(const occ::handle<IGESDefs_GenericData>& ent,
                                        const Interface_ShareTool&,
                                        occ::handle<Interface_Check>& ach) const
{
  if (ent->NbPropertyValues() != ent->NbTypeValuePairs() * 2 + 2)
    ach->AddFail("Nb. of Property Values not consistent with Nb. of Type/value Pairs");
}

void IGESDefs_ToolGenericData::OwnDump(const occ::handle<IGESDefs_GenericData>& ent,
                                       const IGESData_IGESDumper&               dumper,
                                       Standard_OStream&                        S,
                                       const int                                level) const
{
  S << "IGESDefs_GenericData\n"
    << "Number of property values : " << ent->NbPropertyValues() << "\n"
    << "Property Name : ";
  IGESData_DumpString(S, ent->Name());
  S << std::endl;
  switch (level)
  {
    case 4:
      S << "Types  :\n";
      S << "Values : Count = " << ent->NbTypeValuePairs() << "\n";
      S << "      [ as level > 4 for content ]\n";
      break;
    case 5:
    case 6:
    {
      int i, num;
      S << "Types & Values : " << "\n";
      for (num = ent->NbTypeValuePairs(), i = 1; i <= num; i++)
      {
        S << "[" << i << "]: ";
        S << "Type : " << ent->Type(i);
        switch (ent->Type(i))
        {
          case 0:
            S << "  (Void)";
            break;
          case 1:
            S << "  Integer, Value : " << ent->ValueAsInteger(i);
            break;
          case 2:
            S << "  Real   , Value : " << ent->ValueAsReal(i);
            break;
          case 3:
            S << "  String , Value : ";
            IGESData_DumpString(S, ent->ValueAsString(i));
            break;
          case 4:
            S << "  Entity , Value : ";
            dumper.Dump(ent->ValueAsEntity(i), S, level - 1);
            break;
          case 5:
            S << " (Not used)";
            break;
          case 6:
            S << "  Logical, Value : " << (ent->ValueAsLogical(i) ? "True" : "False");
            break;
          default:
            break;
        }
        S << "\n";
      }
    }
  }
  S << std::endl;
}
