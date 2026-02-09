

#include <Message_Messenger.hpp>
#include <Message_Printer.hpp>
#include <Message.hpp>
#include <TCollection_AsciiString.hpp>

#include <gtest/gtest.h>

#include <sstream>

namespace
{

  class TestMessagePrinter : public Message_Printer
  {
  public:
    TestMessagePrinter(std::ostringstream& theStream)
        : myStream(theStream)
    {
    }

    void send(const TCollection_AsciiString& theString,
              const Message_Gravity          theGravity) const override
    {
      if (theGravity >= Message_Info)
      {
        myStream << theString << "\n";
      }
    }

  private:
    std::ostringstream& myStream;
  };
} // namespace

TEST(Message_Messenger_Test, OCC31189_StreamBufferMessageOrdering)
{

  std::ostringstream                    anOutput;
  occ::handle<TestMessagePrinter>       aPrinter = new TestMessagePrinter(anOutput);
  const occ::handle<Message_Messenger>& aMsgMgr  = ::Message::DefaultMessenger();

  NCollection_Sequence<occ::handle<Message_Printer>> anOriginalPrinters;
  anOriginalPrinters.Append(aMsgMgr->ChangePrinters());

  aMsgMgr->ChangePrinters().Clear();
  aMsgMgr->AddPrinter(aPrinter);

  {
    Message_Messenger::StreamBuffer aSender = ::Message::SendInfo();

    aSender << "Sender message 1: start ...";
    aMsgMgr->Send("Direct message 1");
    aSender << "... end" << std::endl;

    ::Message::SendInfo();

    aMsgMgr->Send("Direct message 2");

    ::Message::SendInfo() << std::endl;

    aSender << "Sender message 2";
  }

  aMsgMgr->ChangePrinters().Clear();
  aMsgMgr->ChangePrinters().Append(anOriginalPrinters);

  std::string anOutputStr = anOutput.str();

  EXPECT_NE(anOutputStr.find("Direct message 1"), std::string::npos)
    << "Direct message 1 should be present";
  EXPECT_NE(anOutputStr.find("Sender message 1: start ...... end"), std::string::npos)
    << "Sender message 1 should be complete and present";
  EXPECT_NE(anOutputStr.find("Direct message 2"), std::string::npos)
    << "Direct message 2 should be present";
  EXPECT_NE(anOutputStr.find("Sender message 2"), std::string::npos)
    << "Sender message 2 should be present";

  size_t aDirect1Pos = anOutputStr.find("Direct message 1");
  size_t aSender1Pos = anOutputStr.find("Sender message 1");
  size_t aDirect2Pos = anOutputStr.find("Direct message 2");
  size_t aSender2Pos = anOutputStr.find("Sender message 2");

  EXPECT_LT(aDirect1Pos, aSender1Pos) << "Direct message 1 should appear before Sender message 1";
  EXPECT_LT(aSender1Pos, aDirect2Pos) << "Sender message 1 should appear before Direct message 2";
  EXPECT_LT(aDirect2Pos, aSender2Pos) << "Direct message 2 should appear before Sender message 2";
}

TEST(Message_Messenger_Test, StreamBufferBasicUsage)
{

  std::ostringstream                    anOutput;
  occ::handle<TestMessagePrinter>       aPrinter = new TestMessagePrinter(anOutput);
  const occ::handle<Message_Messenger>& aMsgMgr  = Message::DefaultMessenger();

  NCollection_Sequence<occ::handle<Message_Printer>> anOriginalPrinters;
  anOriginalPrinters.Append(aMsgMgr->ChangePrinters());

  aMsgMgr->ChangePrinters().Clear();
  aMsgMgr->AddPrinter(aPrinter);
  {
    Message_Messenger::StreamBuffer aBuffer = Message::SendInfo();
    aBuffer << "Test message" << std::endl;
  }

  aMsgMgr->ChangePrinters().Clear();
  aMsgMgr->ChangePrinters().Append(anOriginalPrinters);

  std::string anOutputStr = anOutput.str();
  EXPECT_NE(anOutputStr.find("Test message"), std::string::npos)
    << "Stream buffer should output message";
}
