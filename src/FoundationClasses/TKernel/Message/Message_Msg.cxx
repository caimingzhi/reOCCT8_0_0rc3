#include <Message_Msg.hpp>
#include <Message_MsgFile.hpp>
#include <TCollection_AsciiString.hpp>

typedef enum
{
  Msg_IntegerType,
  Msg_RealType,
  Msg_StringType,
  Msg_IndefiniteType
} FormatType;

Message_Msg::Message_Msg() = default;

Message_Msg::Message_Msg(const Message_Msg& theMsg)
{
  myMessageBody = theMsg.myMessageBody;
  myOriginal    = theMsg.myOriginal;
  for (int i = 1, n = theMsg.mySeqOfFormats.Length(); i <= n; i++)
    mySeqOfFormats.Append(theMsg.mySeqOfFormats.Value(i));
}

Message_Msg::Message_Msg(const char* theMsgCode)
{
  TCollection_AsciiString aKey((char*)theMsgCode);
  Set(Message_MsgFile::Msg(aKey));
}

Message_Msg::Message_Msg(const TCollection_ExtendedString& theMsgCode)
{
  Set(Message_MsgFile::Msg(theMsgCode));
}

void Message_Msg::Set(const char* theMsg)
{
  TCollection_AsciiString aMsg((char*)theMsg);
  Set(aMsg);
}

void Message_Msg::Set(const TCollection_ExtendedString& theMsg)
{
  myMessageBody = theMsg;

  const char16_t* anExtString = myMessageBody.ToExtString();
  int             anMsgLength = myMessageBody.Length();
  for (int i = 0; i < anMsgLength; i++)
  {

    if (ToCharacter(anExtString[i]) == '%')
    {
      int  aStart = i++;
      char aChar  = ToCharacter(anExtString[i]);

      if (aChar == '%')
      {
        myMessageBody.Remove(i + 1);
        if (i >= --anMsgLength)
          break;
        aChar = ToCharacter(anExtString[i]);
      }

      while (i < anMsgLength)
      {
        if (aChar == '-' || aChar == '+' || aChar == ' ' || aChar == '#'
            || (aChar >= '0' && aChar <= '9') || aChar == '.')
          i++;
        else
          break;
        aChar = ToCharacter(anExtString[i]);
      }
      if (i >= anMsgLength)
        break;

      FormatType aFormatType;
      if (aChar == 'h' || aChar == 'l')
        aChar = ToCharacter(anExtString[++i]);
      switch (aChar)
      {
        case 'd':
        case 'i':
        case 'o':
        case 'u':
        case 'x':
        case 'X':
          aFormatType = Msg_IntegerType;
          break;
        case 'f':
        case 'e':
        case 'E':
        case 'g':
        case 'G':
          aFormatType = Msg_RealType;
          break;
        case 's':
          aFormatType = Msg_StringType;
          break;
        default:
          continue;
      }
      mySeqOfFormats.Append(int(aFormatType));
      mySeqOfFormats.Append(aStart);
      mySeqOfFormats.Append(i + 1 - aStart);
    }
  }
  myOriginal = myMessageBody;
}

Message_Msg& Message_Msg::Arg(const char* theString)
{

  TCollection_AsciiString aFormat;
  int                     aFirst = getFormat(Msg_StringType, aFormat);
  if (!aFirst)
    return *this;

  char* sStringBuffer = new char[std::max(static_cast<int>(strlen(theString) + 1), 1024)];
  Sprintf(sStringBuffer, aFormat.ToCString(), theString);
  TCollection_ExtendedString aStr(sStringBuffer, true);
  delete[] sStringBuffer;
  sStringBuffer = nullptr;

  replaceText(aFirst, aFormat.Length(), aStr);

  return *this;
}

Message_Msg& Message_Msg::Arg(const TCollection_ExtendedString& theString)
{

  TCollection_AsciiString aFormat;
  int                     aFirst = getFormat(Msg_StringType, aFormat);
  if (!aFirst)
    return *this;

  replaceText(aFirst, aFormat.Length(), theString);

  return *this;
}

Message_Msg& Message_Msg::Arg(const int theValue)
{

  TCollection_AsciiString aFormat;
  int                     aFirst = getFormat(Msg_IntegerType, aFormat);
  if (!aFirst)
    return *this;

  char sStringBuffer[64];
  Sprintf(sStringBuffer, aFormat.ToCString(), theValue);
  TCollection_ExtendedString aStr(sStringBuffer);

  replaceText(aFirst, aFormat.Length(), aStr);

  return *this;
}

Message_Msg& Message_Msg::Arg(const double theValue)
{

  TCollection_AsciiString aFormat;
  int                     aFirst = getFormat(Msg_RealType, aFormat);
  if (!aFirst)
    return *this;

  char sStringBuffer[64];
  Sprintf(sStringBuffer, aFormat.ToCString(), theValue);
  TCollection_ExtendedString aStr(sStringBuffer);

  replaceText(aFirst, aFormat.Length(), aStr);

  return *this;
}

const TCollection_ExtendedString& Message_Msg::Get()
{

  int                                     i, anIncrement = 0;
  static const TCollection_ExtendedString anUnknown("UNKNOWN");
  for (i = 1; i < mySeqOfFormats.Length(); i += 3)
  {
    TCollection_ExtendedString aRightPart =
      myMessageBody.Split(mySeqOfFormats(i + 1) + anIncrement);
    aRightPart.Remove(1, mySeqOfFormats(i + 2));
    myMessageBody += anUnknown;
    myMessageBody += aRightPart;
    anIncrement += (anUnknown.Length() - mySeqOfFormats(i + 2));
  }
  return myMessageBody;
}

int Message_Msg::getFormat(const int theType, TCollection_AsciiString& theFormat)
{
  for (int i = 1; i <= mySeqOfFormats.Length(); i += 3)
    if (mySeqOfFormats(i) == theType)
    {

      int aFirst = mySeqOfFormats(i + 1);
      int aLen   = mySeqOfFormats(i + 2);
      theFormat  = TCollection_AsciiString(aLen, ' ');
      for (int j = 1; j <= aLen; j++)
        if (IsAnAscii(myMessageBody.Value(aFirst + j)))
          theFormat.SetValue(j, (char)myMessageBody.Value(aFirst + j));

      mySeqOfFormats.Remove(i, i + 2);

      return aFirst + 1;
    }
  return 0;
}

void Message_Msg::replaceText(const int                         theFirst,
                              const int                         theNb,
                              const TCollection_ExtendedString& theStr)
{
  myMessageBody.Remove(theFirst, theNb);
  myMessageBody.Insert(theFirst, theStr);

  int anIncrement = theStr.Length() - theNb;
  if (!anIncrement)
    return;
  for (int i = 1; i <= mySeqOfFormats.Length(); i += 3)
    if (mySeqOfFormats(i + 1) > theFirst)
      mySeqOfFormats(i + 1) += anIncrement;
}
