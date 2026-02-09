#include <LDOM_OSStream.hpp>
#include <NCollection_IncAllocator.hpp>
#include <Standard_Assert.hpp>

#include <cstring>

LDOM_SBuffer::LDOM_StringElem::LDOM_StringElem(
  const int                                     theLength,
  const occ::handle<NCollection_BaseAllocator>& theAlloc)
    : buf(reinterpret_cast<char*>(theAlloc->Allocate(theLength))),
      len(0),
      next(nullptr)
{
}

LDOM_SBuffer::LDOM_SBuffer(const int theMaxBuf)
    : myMaxBuf(theMaxBuf),
      myLength(0),
      myAlloc(new NCollection_IncAllocator)
{
  myFirstString = new (myAlloc) LDOM_StringElem(theMaxBuf, myAlloc);
  myCurString   = myFirstString;
}

LDOM_SBuffer::~LDOM_SBuffer() = default;

void LDOM_SBuffer::Clear()
{
  myAlloc       = new NCollection_IncAllocator;
  myFirstString = new (myAlloc) LDOM_StringElem(myMaxBuf, myAlloc);
  myLength      = 0;
  myCurString   = myFirstString;
}

const char* LDOM_SBuffer::str() const
{
  char* aRetStr = new char[myLength + 1];

  LDOM_StringElem* aCurElem = myFirstString;
  int              aCurLen  = 0;
  while (aCurElem)
  {
    strncpy(aRetStr + aCurLen, aCurElem->buf, aCurElem->len);
    aCurLen += aCurElem->len;
    aCurElem = aCurElem->next;
  }
  *(aRetStr + myLength) = '\0';

  return aRetStr;
}

int LDOM_SBuffer::overflow(int c)
{
  char cc = (char)c;
  xsputn(&cc, 1);
  return c;
}

int LDOM_SBuffer::underflow()
{
  return EOF;
}

std::streamsize LDOM_SBuffer::xsputn(const char* aStr, std::streamsize n)
{
  Standard_ASSERT_RAISE(n < IntegerLast(),
                        "LDOM_SBuffer cannot work with strings greater than 2 Gb");

  int aLen    = static_cast<int>(n) + 1;
  int freeLen = myMaxBuf - myCurString->len - 1;
  if (freeLen >= n)
  {
    strncpy(myCurString->buf + myCurString->len, aStr, aLen);
  }
  else if (freeLen <= 0)
  {
    LDOM_StringElem* aNextElem = new (myAlloc) LDOM_StringElem(std::max(aLen, myMaxBuf), myAlloc);
    myCurString->next          = aNextElem;
    myCurString                = aNextElem;
    strncpy(myCurString->buf + myCurString->len, aStr, aLen);
  }
  else
  {

    strncpy(myCurString->buf + myCurString->len, aStr, freeLen);
    myCurString->len += freeLen;
    *(myCurString->buf + myCurString->len) = '\0';
    aLen -= freeLen;
    LDOM_StringElem* aNextElem = new (myAlloc) LDOM_StringElem(std::max(aLen, myMaxBuf), myAlloc);
    myCurString->next          = aNextElem;
    myCurString                = aNextElem;
    strncpy(myCurString->buf + myCurString->len, aStr + freeLen, aLen);
  }
  myCurString->len += aLen - 1;
  *(myCurString->buf + myCurString->len) = '\0';

  myLength += static_cast<int>(n);
  return n;
}

LDOM_OSStream::LDOM_OSStream(const int theMaxBuf)
    : Standard_OStream(&myBuffer),
      myBuffer(theMaxBuf)
{
  init(&myBuffer);
}

LDOM_OSStream::~LDOM_OSStream() = default;
