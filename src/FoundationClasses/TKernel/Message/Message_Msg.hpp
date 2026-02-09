#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TCollection_HAsciiString.hpp>
#include <TCollection_HExtendedString.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Sequence.hpp>

class TCollection_AsciiString;
class TCollection_HAsciiString;
class TCollection_HExtendedString;

class Message_Msg
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Message_Msg();

  Standard_EXPORT Message_Msg(const Message_Msg& theMsg);

  Standard_EXPORT Message_Msg(const char* theKey);

  Standard_EXPORT Message_Msg(const TCollection_ExtendedString& theKey);

  Standard_EXPORT void Set(const char* theMsg);

  Standard_EXPORT void Set(const TCollection_ExtendedString& theMsg);

  Standard_EXPORT Message_Msg& Arg(const char* theString);

  Message_Msg& operator<<(const char* theString) { return Arg(theString); }

  Message_Msg& Arg(const TCollection_AsciiString& theString);

  Message_Msg& operator<<(const TCollection_AsciiString& theString) { return Arg(theString); }

  Message_Msg& Arg(const occ::handle<TCollection_HAsciiString>& theString);

  Message_Msg& operator<<(const occ::handle<TCollection_HAsciiString>& theString)
  {
    return Arg(theString);
  }

  Standard_EXPORT Message_Msg& Arg(const TCollection_ExtendedString& theString);

  Message_Msg& operator<<(const TCollection_ExtendedString& theString) { return Arg(theString); }

  Message_Msg& Arg(const occ::handle<TCollection_HExtendedString>& theString);

  Message_Msg& operator<<(const occ::handle<TCollection_HExtendedString>& theString)
  {
    return Arg(theString);
  }

  Standard_EXPORT Message_Msg& Arg(const int theInt);

  Message_Msg& operator<<(const int theInt) { return Arg(theInt); }

  Standard_EXPORT Message_Msg& Arg(const double theReal);

  Message_Msg& operator<<(const double theReal) { return Arg(theReal); }

  const TCollection_ExtendedString& Original() const;

  const TCollection_ExtendedString& Value() const;

  bool IsEdited() const;

  Standard_EXPORT const TCollection_ExtendedString& Get();

  operator const TCollection_ExtendedString&() { return Get(); }

private:
  Standard_EXPORT int getFormat(const int theType, TCollection_AsciiString& theFormat);

  Standard_EXPORT void replaceText(const int                         theFirst,
                                   const int                         theNb,
                                   const TCollection_ExtendedString& theStr);

  TCollection_ExtendedString myOriginal;
  TCollection_ExtendedString myMessageBody;
  NCollection_Sequence<int>  mySeqOfFormats;
};

#include <Message_Msg.hpp>

#include <TCollection_HAsciiString.hpp>
#include <TCollection_HExtendedString.hpp>

inline Message_Msg& Message_Msg::Arg(const TCollection_AsciiString& theString)
{
  return Arg(theString.ToCString());
}

inline Message_Msg& Message_Msg::Arg(const occ::handle<TCollection_HAsciiString>& theString)
{
  return Arg(theString->String().ToCString());
}

inline Message_Msg& Message_Msg::Arg(const occ::handle<TCollection_HExtendedString>& theString)
{
  return Arg(theString->String());
}

inline const TCollection_ExtendedString& Message_Msg::Original() const
{
  return myOriginal;
}

inline const TCollection_ExtendedString& Message_Msg::Value() const
{
  return myMessageBody;
}

inline bool Message_Msg::IsEdited() const
{
  return !myOriginal.IsEqual(myMessageBody);
}
