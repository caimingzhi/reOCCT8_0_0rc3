#pragma once

#include <Standard.hpp>
#include <Standard_OStream.hpp>
#include <Standard_SStream.hpp>

#include <exception>

class Standard_Failure : public std::exception
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Standard_Failure();

  Standard_EXPORT Standard_Failure(const Standard_Failure& theOther);

  Standard_EXPORT Standard_Failure(const char* theMessage);

  Standard_EXPORT Standard_Failure(const char* theMessage, const char* theStackTrace);

  Standard_EXPORT Standard_Failure& operator=(const Standard_Failure& theOther);

  Standard_EXPORT ~Standard_Failure() override;

  Standard_EXPORT const char* what() const noexcept override;

  Standard_DEPRECATED("Use what() instead")

  const char* GetMessageString() const noexcept { return what(); }

  virtual const char* ExceptionType() const noexcept { return "Standard_Failure"; }

  Standard_EXPORT const char* GetStackString() const;

  Standard_EXPORT void Print(Standard_OStream& theStream) const;

public:
  Standard_EXPORT static int DefaultStackTraceLength();

  Standard_EXPORT static void SetDefaultStackTraceLength(int theNbStackTraces);

private:
  struct StringRef
  {
    int  Counter;
    char Message[1];

    const char* GetMessage() const { return &Message[0]; }

    static StringRef* Allocate(const char* theString);

    static StringRef* Copy(StringRef* theString);

    static void Free(StringRef* theString);
  };

  void captureStackTrace();

private:
  StringRef* myMessage;
  StringRef* myStackTrace;
};

inline Standard_OStream& operator<<(Standard_OStream& theStream, const Standard_Failure& theFailure)
{
  theFailure.Print(theStream);
  return theStream;
}
