#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Message_Status.hpp>

/**
 * Tiny class for extended handling of error / execution
 * status of algorithm in universal way.
 *
 * It is in fact a set of integers represented as a collection of bit flags
 * for each of four types of status; each status flag has its own symbolic
 * name and can be set/tested individually.
 *
 * The flags are grouped in semantic groups:
 * - No flags means nothing done
 * - Done flags correspond to some operation successfully completed
 * - Warning flags correspond to warning messages on some
 *   potentially wrong situation, not harming algorithm execution
 * - Alarm flags correspond to more severe warnings about incorrect
 *   user data, while not breaking algorithm execution
 * - Fail flags correspond to cases when algorithm failed to complete
 */
class Message_ExecStatus
{
private:
  //! Mask to separate bits indicating status type and index within the type
  enum StatusMask
  {
    MType  = 0x0000ff00,
    MIndex = 0x000000ff
  };

  static inline int getBitFlag(int theStatus) { return 0x1 << (theStatus & MIndex); }

public:
  //!@name Creation and simple operations with statuses
  //!@{

  //! Create empty execution status
  Message_ExecStatus()
      : myDone(Message_None),
        myWarn(Message_None),
        myAlarm(Message_None),
        myFail(Message_None)
  {
  }

  //! Initialise the execution status
  Message_ExecStatus(Message_Status theStatus)
      : myDone(Message_None),
        myWarn(Message_None),
        myAlarm(Message_None),
        myFail(Message_None)
  {
    Set(theStatus);
  }

  //! Sets a status flag
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

  //! Check status for being set
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

  //! Clear one status
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

  //!@}

  //!@name Advanced: Group operations (useful for analysis)
  //!@{

  //! Check if at least one status of each type is set
  bool IsDone() const { return myDone != Message_None; }

  bool IsFail() const { return myFail != Message_None; }

  bool IsWarn() const { return myWarn != Message_None; }

  bool IsAlarm() const { return myAlarm != Message_None; }

  //! Set all statuses of each type
  void SetAllDone() { myDone = ~0; }

  void SetAllWarn() { myWarn = ~0; }

  void SetAllAlarm() { myAlarm = ~0; }

  void SetAllFail() { myFail = ~0; }

  //! Clear all statuses of each type
  void ClearAllDone() { myDone = Message_None; }

  void ClearAllWarn() { myWarn = Message_None; }

  void ClearAllAlarm() { myAlarm = Message_None; }

  void ClearAllFail() { myFail = Message_None; }

  //! Clear all statuses
  void Clear() { myDone = myWarn = myAlarm = myFail = Message_None; }

  //! Add statuses to me from theOther execution status
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

  //! Leave only the statuses common with theOther
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

  //@}

public:
  //!@name Advanced: Iteration and analysis of status flags
  //!@{

  //! Definitions of range of available statuses
  enum StatusRange
  {
    FirstStatus     = 1,
    StatusesPerType = 32,
    NbStatuses      = 128,
    LastStatus      = 129
  };

  //! Returns index of status in whole range [FirstStatus, LastStatus]
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

  //! Returns index of status inside type of status (Done or Warn or, etc)
  //! in range [1, StatusesPerType]
  static int LocalStatusIndex(Message_Status theStatus)
  {
    return ((unsigned int)theStatus & (unsigned int)MIndex) + 1;
  }

  //! Returns status type (DONE, WARN, ALARM, or FAIL)
  static Message_StatusType TypeOfStatus(Message_Status theStatus)
  {
    return (Message_StatusType)((unsigned int)theStatus & (unsigned int)MType);
  }

  //! Returns status with index theIndex in whole range [FirstStatus, LastStatus]
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

  //!@}

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

//! Class Message_Algorithm is intended to be the base class for
//! classes implementing algorithms or any operations that need
//! to provide extended information on its execution to the
//! caller / user.
//!
//! It provides generic mechanism for management of the execution
//! status, collection and output of messages.
//!
//! The algorithm uses methods SetStatus() to set an execution status.
//! It is possible to associate a status with a number or a string
//! (second argument of SetStatus() methods) to indicate precisely
//! the item (object, element etc.) in the input data which caused
//! the problem.
//!
//! Each execution status generated by the algorithm has associated
//! text message that should be defined in the resource file loaded
//! with call to Message_MsgFile::LoadFile().
//!
//! The messages corresponding to the statuses generated during the
//! algorithm execution are output to Message_Messenger using
//! methods SendMessages(). If status have associated numbers
//! or strings, they are included in the message body in place of
//! "%s" placeholder which should be present in the message text.
//!
//! The name of the message text in the resource file is constructed
//! from name of the class and name of the status, separated by dot,
//! for instance:
//!
//! .TObj_CheckModel.Alarm2
//! Error: Some objects (%s) have references to dead object(s)
//!
//! If message for the status is not found with prefix of
//! the current class type, the same message is searched for the base
//! class(es) recursively.
//!
//! Message can be set explicitly for the status; in this case the
//! above procedure is not used and supplied message is used as is.
//!
//! The messages are output to the messenger, stored in the field;
//! though messenger can be changed, it is guaranteed to be non-null.
//! By default, Message::DefaultMessenger() is used.
class Message_Algorithm : public Standard_Transient
{

public:
  //! Empty constructor
  Standard_EXPORT Message_Algorithm();

  //! Sets status with no parameter
  Standard_EXPORT void SetStatus(const Message_Status& theStat);

  //! Sets status with integer parameter
  Standard_EXPORT void SetStatus(const Message_Status& theStat, const int theInt);

  //! Sets status with string parameter.
  //! If noRepetitions is True, the parameter will be added only
  //! if it has not been yet recorded for the same status flag
  void SetStatus(const Message_Status& theStat,
                 const char*           theStr,
                 const bool            noRepetitions = true);

  //! Sets status with string parameter
  //! If noRepetitions is True, the parameter will be added only
  //! if it has not been yet recorded for the same status flag
  void SetStatus(const Message_Status&          theStat,
                 const TCollection_AsciiString& theStr,
                 const bool                     noRepetitions = true);

  //! Sets status with string parameter
  //! If noRepetitions is True, the parameter will be added only
  //! if it has not been yet recorded for the same status flag
  void SetStatus(const Message_Status&                        theStat,
                 const occ::handle<TCollection_HAsciiString>& theStr,
                 const bool                                   noRepetitions = true);

  //! Sets status with string parameter
  //! If noRepetitions is True, the parameter will be added only
  //! if it has not been yet recorded for the same status flag
  void SetStatus(const Message_Status&             theStat,
                 const TCollection_ExtendedString& theStr,
                 const bool                        noRepetitions = true);

  //! Sets status with string parameter
  //! If noRepetitions is True, the parameter will be added only
  //! if it has not been yet recorded for the same status flag
  Standard_EXPORT void SetStatus(const Message_Status&                           theStat,
                                 const occ::handle<TCollection_HExtendedString>& theStr,
                                 const bool noRepetitions = true);

  //! Sets status with preformatted message. This message will be
  //! used directly to report the status; automatic generation of
  //! status messages will be disabled for it.
  Standard_EXPORT void SetStatus(const Message_Status& theStat, const Message_Msg& theMsg);

  //! Returns copy of exec status of algorithm
  const Message_ExecStatus& GetStatus() const;

  //! Returns exec status of algorithm
  Message_ExecStatus& ChangeStatus();

  //! Clear exec status of algorithm
  Standard_EXPORT void ClearStatus();

  //! Sets messenger to algorithm
  Standard_EXPORT void SetMessenger(const occ::handle<Message_Messenger>& theMsgr);

  //! Returns messenger of algorithm.
  //! The returned handle is always non-null and can
  //! be used for sending messages.
  occ::handle<Message_Messenger> GetMessenger() const;

  //! Print messages for all status flags that have been set during
  //! algorithm execution, excluding statuses that are NOT set
  //! in theFilter.
  //!
  //! The messages are taken from resource file, names being
  //! constructed as {dynamic class type}.{status name},
  //! for instance, "Message_Algorithm.Fail5".
  //! If message is not found in resources for this class and all
  //! its base types, surrogate text is printed.
  //!
  //! For the statuses having number or string parameters,
  //! theMaxCount defines maximal number of numbers or strings to be
  //! included in the message
  //!
  //! Note that this method is virtual; this allows descendant
  //! classes to customize message output (e.g. by adding
  //! messages from other sub-algorithms)
  Standard_EXPORT virtual void SendStatusMessages(
    const Message_ExecStatus& theFilter,
    const Message_Gravity     theTraceLevel = Message_Warning,
    const int                 theMaxCount   = 20) const;

  //! Convenient variant of SendStatusMessages() with theFilter
  //! having defined all WARN, ALARM, and FAIL (but not DONE)
  //! status flags
  Standard_EXPORT void SendMessages(const Message_Gravity theTraceLevel = Message_Warning,
                                    const int             theMaxCount   = 20) const;

  //! Add statuses to this algorithm from other algorithm
  //! (including messages)
  Standard_EXPORT void AddStatus(const occ::handle<Message_Algorithm>& theOther);

  //! Add statuses to this algorithm from other algorithm, but
  //! only those items are moved that correspond to statuses
  //! set in theStatus
  Standard_EXPORT void AddStatus(const Message_ExecStatus&             theStatus,
                                 const occ::handle<Message_Algorithm>& theOther);

  //! Return the numbers associated with the indicated status;
  //! Null handle if no such status or no numbers associated with it
  Standard_EXPORT occ::handle<TColStd_HPackedMapOfInteger> GetMessageNumbers(
    const Message_Status& theStatus) const;

  //! Return the strings associated with the indicated status;
  //! Null handle if no such status or no strings associated with it
  Standard_EXPORT occ::handle<NCollection_HSequence<occ::handle<TCollection_HExtendedString>>>
                  GetMessageStrings(const Message_Status& theStatus) const;

  //! Prepares a string containing a list of integers contained
  //! in theError map, but not more than theMaxCount
  Standard_EXPORT static TCollection_ExtendedString PrepareReport(
    const occ::handle<TColStd_HPackedMapOfInteger>& theError,
    const int                                       theMaxCount);

  //! Prepares a string containing a list of names contained
  //! in theReportSeq sequence, but not more than theMaxCount
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

//=================================================================================================

inline void Message_Algorithm::SetStatus(const Message_Status& theStat,
                                         const char*           theStr,
                                         const bool            noRepetitions)
{
  SetStatus(theStat, new TCollection_HExtendedString(theStr), noRepetitions);
}

//=================================================================================================

inline void Message_Algorithm::SetStatus(const Message_Status&          theStat,
                                         const TCollection_AsciiString& theStr,
                                         const bool                     noRepetitions)
{
  SetStatus(theStat, new TCollection_HExtendedString(theStr), noRepetitions);
}

//=================================================================================================

inline void Message_Algorithm::SetStatus(const Message_Status&                        theStat,
                                         const occ::handle<TCollection_HAsciiString>& theStr,
                                         const bool                                   noRepetitions)
{
  SetStatus(theStat, new TCollection_HExtendedString(theStr), noRepetitions);
}

//=================================================================================================

inline void Message_Algorithm::SetStatus(const Message_Status&             theStat,
                                         const TCollection_ExtendedString& theStr,
                                         const bool                        noRepetitions)
{
  SetStatus(theStat, new TCollection_HExtendedString(theStr), noRepetitions);
}

//=================================================================================================

inline const Message_ExecStatus& Message_Algorithm::GetStatus() const
{
  return myStatus;
}

//=================================================================================================

inline Message_ExecStatus& Message_Algorithm::ChangeStatus()
{
  return myStatus;
}

//=================================================================================================

inline occ::handle<Message_Messenger> Message_Algorithm::GetMessenger() const
{
  return myMessenger;
}
