#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Message_Status.hpp>

class Message_ExecStatus
{
private:
  enum StatusMask
  {
    MType  = 0x0000ff00,
    MIndex = 0x000000ff
  };

  static inline int getBitFlag(int theStatus) { return 0x1 << (theStatus & MIndex); }

public:
  Message_ExecStatus()
      : myDone(Message_None),
        myWarn(Message_None),
        myAlarm(Message_None),
        myFail(Message_None)
  {
  }

  Message_ExecStatus(Message_Status theStatus)
      : myDone(Message_None),
        myWarn(Message_None),
        myAlarm(Message_None),
        myFail(Message_None)
  {
    Set(theStatus);
  }

  void Set(Message_Status theStatus)
  {
    switch (TypeOfStatus(theStatus))
    {
      case Message_DONE:
        myDone |= (getBitFlag(theStatus));
        break;
      case Message_WARN:
        myWarn |= (getBitFlag(theStatus));
        break;
      case Message_ALARM:
        myAlarm |= (getBitFlag(theStatus));
        break;
      case Message_FAIL:
        myFail |= (getBitFlag(theStatus));
        break;
    }
  }

  bool IsSet(Message_Status theStatus) const
  {
    switch (TypeOfStatus(theStatus))
    {
      case Message_DONE:
        return (myDone & getBitFlag(theStatus)) != 0;
      case Message_WARN:
        return (myWarn & getBitFlag(theStatus)) != 0;
      case Message_ALARM:
        return (myAlarm & getBitFlag(theStatus)) != 0;
      case Message_FAIL:
        return (myFail & getBitFlag(theStatus)) != 0;
    }
    return false;
  }

  void Clear(Message_Status theStatus)
  {
    switch (TypeOfStatus(theStatus))
    {
      case Message_DONE:
        myDone &= ~(getBitFlag(theStatus));
        return;
      case Message_WARN:
        myWarn &= ~(getBitFlag(theStatus));
        return;
      case Message_ALARM:
        myAlarm &= ~(getBitFlag(theStatus));
        return;
      case Message_FAIL:
        myFail &= ~(getBitFlag(theStatus));
        return;
    }
  }

  bool IsDone() const { return myDone != Message_None; }

  bool IsFail() const { return myFail != Message_None; }

  bool IsWarn() const { return myWarn != Message_None; }

  bool IsAlarm() const { return myAlarm != Message_None; }

  void SetAllDone() { myDone = ~0; }

  void SetAllWarn() { myWarn = ~0; }

  void SetAllAlarm() { myAlarm = ~0; }

  void SetAllFail() { myFail = ~0; }

  void ClearAllDone() { myDone = Message_None; }

  void ClearAllWarn() { myWarn = Message_None; }

  void ClearAllAlarm() { myAlarm = Message_None; }

  void ClearAllFail() { myFail = Message_None; }

  void Clear() { myDone = myWarn = myAlarm = myFail = Message_None; }

  void Add(const Message_ExecStatus& theOther)
  {
    myDone |= theOther.myDone;
    myWarn |= theOther.myWarn;
    myAlarm |= theOther.myAlarm;
    myFail |= theOther.myFail;
  }

  const Message_ExecStatus& operator|=(const Message_ExecStatus& theOther)
  {
    Add(theOther);
    return *this;
  }

  void And(const Message_ExecStatus& theOther)
  {
    myDone &= theOther.myDone;
    myWarn &= theOther.myWarn;
    myAlarm &= theOther.myAlarm;
    myFail &= theOther.myFail;
  }

  const Message_ExecStatus& operator&=(const Message_ExecStatus& theOther)
  {
    And(theOther);
    return *this;
  }

public:
  enum StatusRange
  {
    FirstStatus     = 1,
    StatusesPerType = 32,
    NbStatuses      = 128,
    LastStatus      = 129
  };

  static int StatusIndex(Message_Status theStatus)
  {
    switch (TypeOfStatus(theStatus))
    {
      case Message_DONE:
        return 0 * StatusesPerType + LocalStatusIndex(theStatus);
      case Message_WARN:
        return 1 * StatusesPerType + LocalStatusIndex(theStatus);
      case Message_ALARM:
        return 2 * StatusesPerType + LocalStatusIndex(theStatus);
      case Message_FAIL:
        return 3 * StatusesPerType + LocalStatusIndex(theStatus);
    }
    return 0;
  }

  static int LocalStatusIndex(Message_Status theStatus)
  {
    return ((unsigned int)theStatus & (unsigned int)MIndex) + 1;
  }

  static Message_StatusType TypeOfStatus(Message_Status theStatus)
  {
    return (Message_StatusType)((unsigned int)theStatus & (unsigned int)MType);
  }

  static Message_Status StatusByIndex(const int theIndex)
  {
    int indx = theIndex - 1;
    if (indx < 32)
      return (Message_Status)(Message_DONE + indx);
    else if (indx < 64)
      return (Message_Status)(Message_WARN + (indx - 32));
    else if (indx < 96)
      return (Message_Status)(Message_ALARM + (indx - 64));
    else if (indx < 128)
      return (Message_Status)(Message_FAIL + (indx - 96));
    return Message_None;
  }

private:
  int myDone;
  int myWarn;
  int myAlarm;
  int myFail;
};

#include <Standard_Transient.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Message_Status.hpp>
#include <Standard_Integer.hpp>
#include <Standard_CString.hpp>
#include <Message_Gravity.hpp>
#include <TCollection_HAsciiString.hpp>
#include <TCollection_HExtendedString.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <Message_Msg.hpp>
#include <NCollection_Handle.hpp>

class Message_Messenger;
class TCollection_AsciiString;
class TCollection_HAsciiString;
class TCollection_ExtendedString;
class TCollection_HExtendedString;
class Message_Msg;
class TColStd_HPackedMapOfInteger;

class Message_Algorithm : public Standard_Transient
{

public:
  Standard_EXPORT Message_Algorithm();

  Standard_EXPORT void SetStatus(const Message_Status& theStat);

  Standard_EXPORT void SetStatus(const Message_Status& theStat, const int theInt);

  void SetStatus(const Message_Status& theStat,
                 const char*           theStr,
                 const bool            noRepetitions = true);

  void SetStatus(const Message_Status&          theStat,
                 const TCollection_AsciiString& theStr,
                 const bool                     noRepetitions = true);

  void SetStatus(const Message_Status&                        theStat,
                 const occ::handle<TCollection_HAsciiString>& theStr,
                 const bool                                   noRepetitions = true);

  void SetStatus(const Message_Status&             theStat,
                 const TCollection_ExtendedString& theStr,
                 const bool                        noRepetitions = true);

  Standard_EXPORT void SetStatus(const Message_Status&                           theStat,
                                 const occ::handle<TCollection_HExtendedString>& theStr,
                                 const bool noRepetitions = true);

  Standard_EXPORT void SetStatus(const Message_Status& theStat, const Message_Msg& theMsg);

  const Message_ExecStatus& GetStatus() const;

  Message_ExecStatus& ChangeStatus();

  Standard_EXPORT void ClearStatus();

  Standard_EXPORT void SetMessenger(const occ::handle<Message_Messenger>& theMsgr);

  occ::handle<Message_Messenger> GetMessenger() const;

  Standard_EXPORT virtual void SendStatusMessages(
    const Message_ExecStatus& theFilter,
    const Message_Gravity     theTraceLevel = Message_Warning,
    const int                 theMaxCount   = 20) const;

  Standard_EXPORT void SendMessages(const Message_Gravity theTraceLevel = Message_Warning,
                                    const int             theMaxCount   = 20) const;

  Standard_EXPORT void AddStatus(const occ::handle<Message_Algorithm>& theOther);

  Standard_EXPORT void AddStatus(const Message_ExecStatus&             theStatus,
                                 const occ::handle<Message_Algorithm>& theOther);

  Standard_EXPORT occ::handle<TColStd_HPackedMapOfInteger> GetMessageNumbers(
    const Message_Status& theStatus) const;

  Standard_EXPORT occ::handle<NCollection_HSequence<occ::handle<TCollection_HExtendedString>>>
                  GetMessageStrings(const Message_Status& theStatus) const;

  Standard_EXPORT static TCollection_ExtendedString PrepareReport(
    const occ::handle<TColStd_HPackedMapOfInteger>& theError,
    const int                                       theMaxCount);

  Standard_EXPORT static TCollection_ExtendedString PrepareReport(
    const NCollection_Sequence<occ::handle<TCollection_HExtendedString>>& theReportSeq,
    const int                                                             theMaxCount);

  DEFINE_STANDARD_RTTIEXT(Message_Algorithm, Standard_Transient)

protected:
  Message_ExecStatus             myStatus;
  occ::handle<Message_Messenger> myMessenger;

private:
  occ::handle<NCollection_HArray1<occ::handle<Standard_Transient>>>       myReportIntegers;
  occ::handle<NCollection_HArray1<occ::handle<Standard_Transient>>>       myReportStrings;
  NCollection_Handle<NCollection_Array1<NCollection_Handle<Message_Msg>>> myReportMessages;
};

#include <Message_Algorithm.hpp>
#include <TCollection_HExtendedString.hpp>

inline void Message_Algorithm::SetStatus(const Message_Status& theStat,
                                         const char*           theStr,
                                         const bool            noRepetitions)
{
  SetStatus(theStat, new TCollection_HExtendedString(theStr), noRepetitions);
}

inline void Message_Algorithm::SetStatus(const Message_Status&          theStat,
                                         const TCollection_AsciiString& theStr,
                                         const bool                     noRepetitions)
{
  SetStatus(theStat, new TCollection_HExtendedString(theStr), noRepetitions);
}

inline void Message_Algorithm::SetStatus(const Message_Status&                        theStat,
                                         const occ::handle<TCollection_HAsciiString>& theStr,
                                         const bool                                   noRepetitions)
{
  SetStatus(theStat, new TCollection_HExtendedString(theStr), noRepetitions);
}

inline void Message_Algorithm::SetStatus(const Message_Status&             theStat,
                                         const TCollection_ExtendedString& theStr,
                                         const bool                        noRepetitions)
{
  SetStatus(theStat, new TCollection_HExtendedString(theStr), noRepetitions);
}

inline const Message_ExecStatus& Message_Algorithm::GetStatus() const
{
  return myStatus;
}

inline Message_ExecStatus& Message_Algorithm::ChangeStatus()
{
  return myStatus;
}

inline occ::handle<Message_Messenger> Message_Algorithm::GetMessenger() const
{
  return myMessenger;
}
