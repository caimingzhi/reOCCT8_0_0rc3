#include <Message.hpp>
#include <Message_Algorithm.hpp>
#include <Message_Messenger.hpp>
#include <Message_Msg.hpp>
#include <Message_MsgFile.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>
#include <TCollection_ExtendedString.hpp>
#include <TCollection_HAsciiString.hpp>
#include <TCollection_HExtendedString.hpp>
#include <TColStd_HPackedMapOfInteger.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <TColStd_MapIteratorOfPackedMapOfInteger.hpp>

IMPLEMENT_STANDARD_RTTIEXT(System::log::Message_Algorithm, Standard_Transient)

System::log::Message_Algorithm::Message_Algorithm()
{
  myMessenger = System::log::Message::DefaultMessenger();
}

void System::log::Message_Algorithm::SetMessenger(const occ::handle<System::log::Message_Messenger>& theMsgr)
{
  if (theMsgr.IsNull())
    myMessenger = System::log::Message::DefaultMessenger();
  else
    myMessenger = theMsgr;
}

void System::log::Message_Algorithm::SetStatus(const Message_Status& theStat)
{
  myStatus.Set(theStat);
}

void System::log::Message_Algorithm::SetStatus(const Message_Status& theStat, const int theInt)
{

  SetStatus(theStat);

  int aFlagIndex = Message_ExecStatus::StatusIndex(theStat);
  if (!aFlagIndex)
    return;

  if (myReportIntegers.IsNull())
    myReportIntegers =
      new NCollection_HArray1<occ::handle<Standard_Transient>>(Message_ExecStatus::FirstStatus,
                                                               Message_ExecStatus::LastStatus);
  occ::handle<Standard_Transient>& aData = myReportIntegers->ChangeValue(aFlagIndex);
  if (aData.IsNull())
    aData = new TColStd_HPackedMapOfInteger;

  occ::down_cast<TColStd_HPackedMapOfInteger>(aData)->ChangeMap().Add(theInt);
}

void System::log::Message_Algorithm::SetStatus(const Message_Status&                           theStat,
                                  const occ::handle<TCollection_HExtendedString>& theStr,
                                  const bool                                      noRepetitions)
{

  SetStatus(theStat);
  if (theStr.IsNull())
    return;

  int aFlagIndex = Message_ExecStatus::StatusIndex(theStat);
  if (!aFlagIndex)
    return;

  if (myReportStrings.IsNull())
    myReportStrings =
      new NCollection_HArray1<occ::handle<Standard_Transient>>(Message_ExecStatus::FirstStatus,
                                                               Message_ExecStatus::LastStatus);
  occ::handle<Standard_Transient>& aData = myReportStrings->ChangeValue(aFlagIndex);
  if (aData.IsNull())
    aData = new NCollection_HSequence<occ::handle<TCollection_HExtendedString>>;

  occ::handle<NCollection_HSequence<occ::handle<TCollection_HExtendedString>>> aReportSeq =
    occ::down_cast<NCollection_HSequence<occ::handle<TCollection_HExtendedString>>>(aData);
  if (aReportSeq.IsNull())
    return;
  if (noRepetitions)
  {

    for (int i = 1; i <= aReportSeq->Length(); i++)
      if (aReportSeq->Value(i)->String().IsEqual(theStr->String()))
        return;
  }

  aReportSeq->Append(theStr);
}

void System::log::Message_Algorithm::SetStatus(const Message_Status& theStat, const System::log::Message_Msg& theMsg)
{

  SetStatus(theStat);

  int aFlagIndex = Message_ExecStatus::StatusIndex(theStat);
  if (aFlagIndex == 0)
  {
    return;
  }

  if (myReportMessages.IsNull())
  {
    myReportMessages =
      new NCollection_Array1<NCollection_Handle<System::log::Message_Msg>>(Message_ExecStatus::FirstStatus,
                                                              Message_ExecStatus::LastStatus);
  }

  myReportMessages->ChangeValue(aFlagIndex) = new System::log::Message_Msg(theMsg);
}

void System::log::Message_Algorithm::ClearStatus()
{
  myStatus.Clear();
  myReportIntegers.Nullify();
  myReportStrings.Nullify();
  myReportMessages.Nullify();
}

void System::log::Message_Algorithm::SendStatusMessages(const Message_ExecStatus& theStatus,
                                           const Message_Gravity     theTraceLevel,
                                           const int                 theMaxCount) const
{
  occ::handle<System::log::Message_Messenger> aMsgr = GetMessenger();
  if (aMsgr.IsNull())
  {
    return;
  }

  for (int i = Message_ExecStatus::FirstStatus; i <= Message_ExecStatus::LastStatus; i++)
  {
    Message_Status stat = Message_ExecStatus::StatusByIndex(i);
    if (!theStatus.IsSet(stat) || !myStatus.IsSet(stat))
    {
      continue;
    }

    NCollection_Handle<System::log::Message_Msg> aMsgCustom;
    if (!myReportMessages.IsNull())
      aMsgCustom = myReportMessages->Value(i);
    if (!aMsgCustom.IsNull())
    {

      aMsgr->Send(*aMsgCustom, theTraceLevel);
      continue;
    }

    TCollection_AsciiString aSuffix;
    switch (Message_ExecStatus::TypeOfStatus(stat))
    {
      case Message_DONE:
        aSuffix.AssignCat(".Done");
        break;
      case Message_WARN:
        aSuffix.AssignCat(".Warn");
        break;
      case Message_ALARM:
        aSuffix.AssignCat(".Alarm");
        break;
      case Message_FAIL:
        aSuffix.AssignCat(".Fail");
        break;
      default:
        continue;
    }
    aSuffix.AssignCat(Message_ExecStatus::LocalStatusIndex(stat));

    TCollection_AsciiString aMsgName;
    for (occ::handle<Standard_Type> aType = DynamicType(); !aType.IsNull(); aType = aType->Parent())
    {
      aMsgName = aType->Name();
      aMsgName += aSuffix;
      if (System::log::Message_MsgFile::HasMsg(aMsgName))
        break;
    }

    System::log::Message_Msg aMsg(aMsgName);

    if (!myReportIntegers.IsNull())
    {
      occ::handle<TColStd_HPackedMapOfInteger> aMapErrors =
        occ::down_cast<TColStd_HPackedMapOfInteger>(myReportIntegers->Value(i));
      if (!aMapErrors.IsNull())
      {
        aMsg << PrepareReport(aMapErrors, theMaxCount);
      }
    }
    if (!myReportStrings.IsNull() && !myReportStrings->Value(i).IsNull())
    {
      occ::handle<NCollection_HSequence<occ::handle<TCollection_HExtendedString>>> aReportSeq =
        occ::down_cast<NCollection_HSequence<occ::handle<TCollection_HExtendedString>>>(
          myReportStrings->Value(i));
      if (!aReportSeq.IsNull())
      {
        aMsg << PrepareReport(aReportSeq->Sequence(), theMaxCount);
      }
    }

    aMsgr->Send(aMsg, theTraceLevel);
  }
}

void System::log::Message_Algorithm::SendMessages(const Message_Gravity theTraceLevel,
                                     const int             theMaxCount) const
{
  Message_ExecStatus aStat;
  aStat.SetAllWarn();
  aStat.SetAllAlarm();
  aStat.SetAllFail();
  SendStatusMessages(aStat, theTraceLevel, theMaxCount);
}

void System::log::Message_Algorithm::AddStatus(const occ::handle<System::log::Message_Algorithm>& theOtherAlgo)
{
  AddStatus(theOtherAlgo->GetStatus(), theOtherAlgo);
}

void System::log::Message_Algorithm::AddStatus(const Message_ExecStatus&             theAllowedStatus,
                                  const occ::handle<System::log::Message_Algorithm>& theOtherAlgo)
{

  const Message_ExecStatus& aStatusOfAlgo = theOtherAlgo->GetStatus();
  for (int i = Message_ExecStatus::FirstStatus; i <= Message_ExecStatus::LastStatus; i++)
  {
    Message_Status stat = Message_ExecStatus::StatusByIndex(i);
    if (!theAllowedStatus.IsSet(stat) || !aStatusOfAlgo.IsSet(stat))
      continue;

    SetStatus(stat);

    occ::handle<TColStd_HPackedMapOfInteger> aNumsOther = theOtherAlgo->GetMessageNumbers(stat);
    if (!aNumsOther.IsNull())
    {

      if (myReportIntegers.IsNull())
        myReportIntegers =
          new NCollection_HArray1<occ::handle<Standard_Transient>>(Message_ExecStatus::FirstStatus,
                                                                   Message_ExecStatus::LastStatus);
      occ::handle<Standard_Transient>& aData = myReportIntegers->ChangeValue(i);
      if (aData.IsNull())
        aData = new TColStd_HPackedMapOfInteger;

      occ::down_cast<TColStd_HPackedMapOfInteger>(aData)->ChangeMap().Unite(aNumsOther->Map());
    }

    occ::handle<NCollection_HSequence<occ::handle<TCollection_HExtendedString>>> aStrsOther =
      theOtherAlgo->GetMessageStrings(stat);
    if (!aStrsOther.IsNull())
    {
      for (int n = 1; n < aStrsOther->Length(); n++)
        SetStatus(stat, aStrsOther->Value(n));
    }
  }
}

occ::handle<TColStd_HPackedMapOfInteger> System::log::Message_Algorithm::GetMessageNumbers(
  const Message_Status& theStatus) const
{
  if (myReportIntegers.IsNull())
    return nullptr;

  int aFlagIndex = Message_ExecStatus::StatusIndex(theStatus);
  if (!aFlagIndex)
    return nullptr;

  return occ::down_cast<TColStd_HPackedMapOfInteger>(myReportIntegers->Value(aFlagIndex));
}

occ::handle<NCollection_HSequence<occ::handle<TCollection_HExtendedString>>> System::log::Message_Algorithm::
  GetMessageStrings(const Message_Status& theStatus) const
{
  if (myReportStrings.IsNull())
    return nullptr;

  int aFlagIndex = Message_ExecStatus::StatusIndex(theStatus);
  if (!aFlagIndex)
    return nullptr;

  return occ::down_cast<NCollection_HSequence<occ::handle<TCollection_HExtendedString>>>(
    myReportStrings->Value(aFlagIndex));
}

TCollection_ExtendedString System::log::Message_Algorithm::PrepareReport(
  const occ::handle<TColStd_HPackedMapOfInteger>& theMapError,
  const int                                       theMaxCount)
{
  TCollection_ExtendedString              aNewReport;
  TColStd_MapIteratorOfPackedMapOfInteger anIt(theMapError->Map());
  int                                     nb = 1;
  for (; anIt.More() && nb <= theMaxCount; anIt.Next(), nb++)
  {
    if (nb > 1)
      aNewReport += " ";
    aNewReport += anIt.Key();
  }

  if (anIt.More())
  {
    aNewReport += " ... (total ";
    aNewReport += theMapError->Map().Extent();
    aNewReport += ")";
  }
  return aNewReport;
}

TCollection_ExtendedString System::log::Message_Algorithm::PrepareReport(
  const NCollection_Sequence<occ::handle<TCollection_HExtendedString>>& theReportSeq,
  const int                                                             theMaxCount)
{
  TCollection_ExtendedString aNewReport;
  int                        nb = 1;
  for (; nb <= theReportSeq.Length() && nb <= theMaxCount; nb++)
  {
    aNewReport += (const char*)(nb > 1 ? ", \'" : "\'");
    aNewReport += theReportSeq.Value(nb)->String();
    aNewReport += "\'";
  }

  if (theReportSeq.Length() > theMaxCount)
  {
    aNewReport += " ... (total ";
    aNewReport += theReportSeq.Length();
    aNewReport += ") ";
  }
  return aNewReport;
}
