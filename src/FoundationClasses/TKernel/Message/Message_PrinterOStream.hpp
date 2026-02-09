#pragma once

enum Message_ConsoleColor
{
  Message_ConsoleColor_Default,
  Message_ConsoleColor_Black,
  Message_ConsoleColor_White,
  Message_ConsoleColor_Red,
  Message_ConsoleColor_Blue,
  Message_ConsoleColor_Green,
  Message_ConsoleColor_Yellow,
  Message_ConsoleColor_Cyan,
  Message_ConsoleColor_Magenta,
};

#include <Message_Printer.hpp>
#include <Standard_OStream.hpp>

class Message_PrinterOStream : public Message_Printer
{
  DEFINE_STANDARD_RTTIEXT(Message_PrinterOStream, Message_Printer)
public:
  Standard_EXPORT static void SetConsoleTextColor(Standard_OStream*    theOStream,
                                                  Message_ConsoleColor theTextColor,
                                                  bool                 theIsIntenseText = false);

public:
  Standard_EXPORT Message_PrinterOStream(const Message_Gravity theTraceLevel = Message_Info);

  Standard_EXPORT Message_PrinterOStream(const char*           theFileName,
                                         const bool            theDoAppend,
                                         const Message_Gravity theTraceLevel = Message_Info);

  Standard_EXPORT void Close();

  ~Message_PrinterOStream() override { Close(); }

  Standard_OStream& GetStream() const { return *(Standard_OStream*)myStream; }

  bool ToColorize() const { return myToColorize; }

  void SetToColorize(bool theToColorize) { myToColorize = theToColorize; }

protected:
  Standard_EXPORT void send(const TCollection_AsciiString& theString,
                            const Message_Gravity          theGravity) const override;

private:
  void* myStream;
  bool  myIsFile;
  bool  myToColorize;
};
