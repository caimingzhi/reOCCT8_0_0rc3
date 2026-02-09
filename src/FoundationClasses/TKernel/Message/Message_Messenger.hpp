#pragma once

#include <Message_Printer.hpp>
#include <NCollection_Sequence.hpp>

#include <TCollection_HAsciiString.hpp>
#include <TCollection_HExtendedString.hpp>

class Message_Printer;

#ifdef AddPrinter
  #undef AddPrinter
#endif

class Message_Messenger : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(Message_Messenger, Standard_Transient)
public:
  class StreamBuffer
  {
  public:
    ~StreamBuffer() { Flush(); }

    void Flush(bool doForce = false)
    {
      myStream.flush();
      if (doForce || myStream.tellp() != std::streampos(0))
      {
        if (myMessenger)
        {
          myMessenger->Send(myStream, myGravity);
        }
        myStream.str(std::string());
      }
    }

    StreamBuffer(const StreamBuffer& theOther)
        : myMessenger(theOther.myMessenger),
          myGravity(theOther.myGravity)
    {
    }

    template <typename T>
    StreamBuffer& operator<<(const T& theArg)
    {
      myStream << theArg;
      return *this;
    }

    StreamBuffer& operator<<(std::ostream& (*)(std::ostream&))
    {
      Flush(true);
      return *this;
    }

    Standard_SStream& Stream() { return myStream; }

    operator Standard_OStream&() { return myStream; }

    Message_Messenger* Messenger() { return myMessenger; }

  private:
    friend class Message_Messenger;

    StreamBuffer(Message_Messenger* theMessenger, Message_Gravity theGravity)
        : myMessenger(theMessenger),
          myGravity(theGravity)
    {
    }

  private:
    Message_Messenger* myMessenger;

    Message_Gravity  myGravity;
    Standard_SStream myStream;
  };

public:
  Standard_EXPORT Message_Messenger();

  Standard_EXPORT Message_Messenger(const occ::handle<Message_Printer>& thePrinter);

  Standard_EXPORT bool AddPrinter(const occ::handle<Message_Printer>& thePrinter);

  Standard_EXPORT bool RemovePrinter(const occ::handle<Message_Printer>& thePrinter);

  Standard_EXPORT int RemovePrinters(const occ::handle<Standard_Type>& theType);

  const NCollection_Sequence<occ::handle<Message_Printer>>& Printers() const { return myPrinters; }

  NCollection_Sequence<occ::handle<Message_Printer>>& ChangePrinters() { return myPrinters; }

  Standard_EXPORT void Send(const char*           theString,
                            const Message_Gravity theGravity = Message_Warning) const;

  Standard_EXPORT void Send(const Standard_SStream& theStream,
                            const Message_Gravity   theGravity = Message_Warning) const;

  Standard_EXPORT void Send(const TCollection_AsciiString& theString,
                            const Message_Gravity          theGravity = Message_Warning) const;

  Standard_EXPORT void Send(const TCollection_ExtendedString& theString,
                            const Message_Gravity             theGravity = Message_Warning) const;

  StreamBuffer Send(Message_Gravity theGravity) { return StreamBuffer(this, theGravity); }

  Standard_EXPORT void Send(const occ::handle<Standard_Transient>& theObject,
                            const Message_Gravity theGravity = Message_Warning) const;

  StreamBuffer SendFail() { return Send(Message_Fail); }

  StreamBuffer SendAlarm() { return Send(Message_Alarm); }

  StreamBuffer SendWarning() { return Send(Message_Warning); }

  StreamBuffer SendInfo() { return Send(Message_Info); }

  StreamBuffer SendTrace() { return Send(Message_Trace); }

  void SendFail(const TCollection_AsciiString& theMessage) { Send(theMessage, Message_Fail); }

  void SendAlarm(const TCollection_AsciiString& theMessage) { Send(theMessage, Message_Alarm); }

  void SendWarning(const TCollection_AsciiString& theMessage) { Send(theMessage, Message_Warning); }

  void SendInfo(const TCollection_AsciiString& theMessage) { Send(theMessage, Message_Info); }

  void SendTrace(const TCollection_AsciiString& theMessage) { Send(theMessage, Message_Trace); }

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

private:
  NCollection_Sequence<occ::handle<Message_Printer>> myPrinters;
};
