#pragma once

#include <NCollection_Array1.hpp>
#include <TCollection_HAsciiString.hpp>

class Interface_LineBuffer
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Interface_LineBuffer(const int size = 10);

  Standard_EXPORT void SetMax(const int max);

  Standard_EXPORT void SetInitial(const int initial);

  Standard_EXPORT void SetKeep();

  Standard_EXPORT bool CanGet(const int more);

  const char* Content() const { return &myLine.First(); }

  int Length() const { return myLen + myInit; }

  Standard_EXPORT void Clear();

  Standard_EXPORT void FreezeInitial();

  Standard_EXPORT void Move(TCollection_AsciiString& str);

  Standard_EXPORT void Move(const occ::handle<TCollection_HAsciiString>& str);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Moved();

  Standard_EXPORT void Add(const char* text);

  Standard_EXPORT void Add(const char* text, const int lntext);

  Standard_EXPORT void Add(const TCollection_AsciiString& text);

  Standard_EXPORT void Add(const char text);

private:
  Standard_EXPORT void Prepare();

  Standard_EXPORT void Keep();

private:
  NCollection_Array1<char> myLine;
  int                      myMax;
  int                      myInit;
  int                      myKeep;
  int                      myGet;
  int                      myLen;
  int                      myFriz;
  char                     myKept;
};
