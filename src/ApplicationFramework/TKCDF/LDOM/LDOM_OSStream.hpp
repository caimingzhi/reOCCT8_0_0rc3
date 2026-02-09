#pragma once

#include <NCollection_DefineAlloc.hpp>
#include <NCollection_BaseAllocator.hpp>
#include <Standard_OStream.hpp>

#include <stdio.h>

class LDOM_SBuffer : public std::streambuf
{

  struct LDOM_StringElem
  {
    char*            buf;
    int              len;
    LDOM_StringElem* next;

    DEFINE_NCOLLECTION_ALLOC

    LDOM_StringElem(const int, const occ::handle<NCollection_BaseAllocator>&);
    ~LDOM_StringElem();

  private:
    LDOM_StringElem(const LDOM_StringElem&);
    LDOM_StringElem& operator=(const LDOM_StringElem&);
  };

public:
  Standard_EXPORT LDOM_SBuffer(const int theMaxBuf);

  Standard_EXPORT const char* str() const;

  int Length() const { return myLength; }

  Standard_EXPORT void Clear();

  Standard_EXPORT int overflow(int c = EOF) override;
  Standard_EXPORT int underflow() override;

  Standard_EXPORT std::streamsize xsputn(const char* s, std::streamsize n) override;

  Standard_EXPORT ~LDOM_SBuffer() override;

private:
  int                                    myMaxBuf;
  int                                    myLength;
  LDOM_StringElem*                       myFirstString;
  LDOM_StringElem*                       myCurString;
  occ::handle<NCollection_BaseAllocator> myAlloc;
};

class LDOM_OSStream : public Standard_OStream
{
public:
  Standard_EXPORT LDOM_OSStream(const int theMaxBuf);

  Standard_EXPORT ~LDOM_OSStream() override;

  const char* str() const { return myBuffer.str(); }

  int Length() const { return myBuffer.Length(); }

  void Clear() { myBuffer.Clear(); }

private:
  LDOM_SBuffer myBuffer;

public:
  enum BOMType
  {
    BOM_UNDEFINED,
    BOM_UTF8,
    BOM_UTF16BE,
    BOM_UTF16LE,
    BOM_UTF32BE,
    BOM_UTF32LE,
    BOM_UTF7,
    BOM_UTF1,
    BOM_UTFEBCDIC,
    BOM_SCSU,
    BOM_BOCU1,
    BOM_GB18030
  };
};
