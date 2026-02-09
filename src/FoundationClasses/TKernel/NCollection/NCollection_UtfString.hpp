#pragma once

#include <NCollection_UtfIterator.hpp>

#include <cstring>
#include <cstdlib>

template <typename Type>
class NCollection_UtfString
{

public:
  NCollection_UtfIterator<Type> Iterator() const { return NCollection_UtfIterator<Type>(myString); }

  int Size() const noexcept { return mySize; }

  int Length() const noexcept { return myLength; }

  char32_t GetChar(const int theCharIndex) const;

  const Type* GetCharBuffer(const int theCharIndex) const;

  char32_t operator[](const int theCharIndex) const { return GetChar(theCharIndex); }

  NCollection_UtfString();

  NCollection_UtfString(const NCollection_UtfString& theCopy);

  NCollection_UtfString(NCollection_UtfString&& theOther) noexcept;

  NCollection_UtfString(const char* theCopyUtf8, const int theLength = -1);

  NCollection_UtfString(const char16_t* theCopyUtf16, const int theLength = -1);

  NCollection_UtfString(const char32_t* theCopyUtf32, const int theLength = -1);

#if !defined(_MSC_VER) || defined(_NATIVE_WCHAR_T_DEFINED)                                         \
  || (defined(_MSC_VER) && _MSC_VER >= 1900)

  NCollection_UtfString(const wchar_t* theCopyUtfWide, const int theLength = -1);
#endif

  template <typename TypeFrom>
  inline void FromUnicode(const TypeFrom* theStringUtf, const int theLength = -1)
  {
    NCollection_UtfIterator<TypeFrom> anIterRead(theStringUtf);
    if (*anIterRead == 0)
    {

      Clear();
      return;
    }
    fromUnicodeImpl(theStringUtf, theLength, anIterRead);
  }

  void FromLocale(const char* theString, const int theLength = -1);

  ~NCollection_UtfString();

  bool IsEqual(const NCollection_UtfString& theCompare) const noexcept;

  NCollection_UtfString SubString(const int theStart, const int theEnd) const;

  const Type* ToCString() const noexcept { return myString; }

  const NCollection_UtfString<char> ToUtf8() const;

  const NCollection_UtfString<char16_t> ToUtf16() const;

  const NCollection_UtfString<char32_t> ToUtf32() const;

  const NCollection_UtfString<wchar_t> ToUtfWide() const;

  bool ToLocale(char* theBuffer, const int theSizeBytes) const;

  bool IsEmpty() const noexcept { return myString[0] == Type(0); }

  void Clear();

public:
  const NCollection_UtfString& Assign(const NCollection_UtfString& theOther);

  void Swap(NCollection_UtfString& theOther) noexcept;

  const NCollection_UtfString& operator=(const NCollection_UtfString& theOther)
  {
    return Assign(theOther);
  }

  NCollection_UtfString& operator=(NCollection_UtfString&& theOther)
  {
    Swap(theOther);
    return *this;
  }

  const NCollection_UtfString& operator=(const char* theStringUtf8);

  const NCollection_UtfString& operator=(const wchar_t* theStringUtfWide);

  NCollection_UtfString& operator+=(const NCollection_UtfString& theAppend);

  friend NCollection_UtfString operator+(const NCollection_UtfString& theLeft,
                                         const NCollection_UtfString& theRight)
  {
    NCollection_UtfString aSumm;
    strFree(aSumm.myString);
    aSumm.mySize   = theLeft.mySize + theRight.mySize;
    aSumm.myLength = theLeft.myLength + theRight.myLength;
    aSumm.myString = strAlloc(aSumm.mySize);

    strCopy((uint8_t*)aSumm.myString, (const uint8_t*)theLeft.myString, theLeft.mySize);
    strCopy((uint8_t*)aSumm.myString + theLeft.mySize,
            (const uint8_t*)theRight.myString,
            theRight.mySize);
    return aSumm;
  }

public:
  bool operator==(const NCollection_UtfString& theCompare) const noexcept
  {
    return IsEqual(theCompare);
  }

  bool operator!=(const NCollection_UtfString& theCompare) const noexcept;

private:
  void fromUnicodeImpl(const Type*                    theStringUtf,
                       const int                      theLength,
                       NCollection_UtfIterator<Type>& theIterator)
  {
    Type* anOldBuffer = myString;

    const int aLengthMax = (theLength > 0) ? theLength : IntegerLast();
    for (; *theIterator != 0 && theIterator.Index() < aLengthMax; ++theIterator)
    {
    }

    mySize   = int((uint8_t*)theIterator.BufferHere() - (uint8_t*)theStringUtf);
    myLength = theIterator.Index();
    myString = strAlloc(mySize);
    strCopy((uint8_t*)myString, (const uint8_t*)theStringUtf, mySize);

    strFree(anOldBuffer);
  }

  template <typename TypeFrom>
  void fromUnicodeImpl(
    typename opencascade::std::enable_if<!opencascade::std::is_same<Type, TypeFrom>::value,
                                         const TypeFrom*>::type theStringUtf,
    const int                                                   theLength,
    NCollection_UtfIterator<TypeFrom>&                          theIterator)
  {
    Type* anOldBuffer = myString;

    mySize               = 0;
    const int aLengthMax = (theLength > 0) ? theLength : IntegerLast();
    for (; *theIterator != 0 && theIterator.Index() < aLengthMax; ++theIterator)
    {
      mySize += theIterator.template AdvanceBytesUtf<Type>();
    }
    myLength = theIterator.Index();

    myString = strAlloc(mySize);

    theIterator.Init(theStringUtf);
    Type* anIterWrite = myString;
    for (; *theIterator != 0 && theIterator.Index() < myLength; ++theIterator)
    {
      anIterWrite = theIterator.GetUtf(anIterWrite);
    }

    strFree(anOldBuffer);
  }

  static Type* strAlloc(const size_t theSizeBytes)
  {
    Type* aPtr = (Type*)Standard::Allocate(theSizeBytes + sizeof(Type));
    if (aPtr != nullptr)
    {

      aPtr[theSizeBytes / sizeof(Type)] = Type(0);
    }
    return aPtr;
  }

  static void strFree(Type*& thePtr) { Standard::Free(thePtr); }

  static void strCopy(uint8_t* theStrDst, const uint8_t* theStrSrc, const int theSizeBytes) noexcept
  {
    std::memcpy(theStrDst, theStrSrc, (size_t)theSizeBytes);
  }

  static bool strAreEqual(const Type* theString1,
                          const int   theSizeBytes1,
                          const Type* theString2,
                          const int   theSizeBytes2) noexcept
  {
    return (theSizeBytes1 == theSizeBytes2)
           && (std::memcmp(theString1, theString2, (size_t)theSizeBytes1) == 0);
  }

private:
  Type* myString;
  int   mySize;

  int myLength;
};

template <typename Type>
char32_t NCollection_UtfString<Type>::GetChar(const int theCharIndex) const
{

  NCollection_UtfIterator<Type> anIter(myString);
  for (; *anIter != 0; ++anIter)
  {
    if (anIter.Index() == theCharIndex)
    {
      return *anIter;
    }
  }
  return 0;
}

template <typename Type>
const Type* NCollection_UtfString<Type>::GetCharBuffer(const int theCharIndex) const
{

  NCollection_UtfIterator<Type> anIter(myString);
  for (; *anIter != 0; ++anIter)
  {
    if (anIter.Index() == theCharIndex)
    {
      return anIter.BufferHere();
    }
  }
  return NULL;
}

template <typename Type>
inline void NCollection_UtfString<Type>::Clear()
{
  strFree(myString);
  mySize   = 0;
  myLength = 0;
  myString = strAlloc(mySize);
}

template <typename Type>
inline NCollection_UtfString<Type>::NCollection_UtfString()
    : myString(strAlloc(0)),
      mySize(0),
      myLength(0)
{
}

template <typename Type>
inline NCollection_UtfString<Type>::NCollection_UtfString(const NCollection_UtfString& theCopy)
    : myString(strAlloc(theCopy.mySize)),
      mySize(theCopy.mySize),
      myLength(theCopy.myLength)
{
  strCopy((uint8_t*)myString, (const uint8_t*)theCopy.myString, mySize);
}

template <typename Type>
inline NCollection_UtfString<Type>::NCollection_UtfString(NCollection_UtfString&& theOther) noexcept
    : myString(theOther.myString),
      mySize(theOther.mySize),
      myLength(theOther.myLength)
{
  theOther.myString = nullptr;
  theOther.mySize   = 0;
  theOther.myLength = 0;
}

template <typename Type>
inline NCollection_UtfString<Type>::NCollection_UtfString(const char* theCopyUtf8,
                                                          const int   theLength)
    : myString(nullptr),
      mySize(0),
      myLength(0)
{
  FromUnicode(theCopyUtf8, theLength);
}

template <typename Type>
inline NCollection_UtfString<Type>::NCollection_UtfString(const char16_t* theCopyUtf16,
                                                          const int       theLength)
    : myString(nullptr),
      mySize(0),
      myLength(0)
{
  FromUnicode(theCopyUtf16, theLength);
}

template <typename Type>
inline NCollection_UtfString<Type>::NCollection_UtfString(const char32_t* theCopyUtf32,
                                                          const int       theLength)
    : myString(nullptr),
      mySize(0),
      myLength(0)
{
  FromUnicode(theCopyUtf32, theLength);
}

#if !defined(_MSC_VER) || defined(_NATIVE_WCHAR_T_DEFINED)                                         \
  || (defined(_MSC_VER) && _MSC_VER >= 1900)

template <typename Type>
inline NCollection_UtfString<Type>::NCollection_UtfString(const wchar_t* theCopyUtfWide,
                                                          const int      theLength)
    : myString(NULL),
      mySize(0),
      myLength(0)
{
  FromUnicode(theCopyUtfWide, theLength);
}
#endif

template <typename Type>
inline NCollection_UtfString<Type>::~NCollection_UtfString()
{
  strFree(myString);
}

template <typename Type>
inline const NCollection_UtfString<Type>& NCollection_UtfString<Type>::Assign(
  const NCollection_UtfString<Type>& theOther)
{
  if (this == &theOther)
  {
    return (*this);
  }

  strFree(myString);
  mySize   = theOther.mySize;
  myLength = theOther.myLength;
  myString = strAlloc(mySize);
  strCopy((uint8_t*)myString, (const uint8_t*)theOther.myString, mySize);
  return (*this);
}

template <typename Type>
inline void NCollection_UtfString<Type>::Swap(NCollection_UtfString<Type>& theOther) noexcept
{

  Type*     aString = myString;
  const int aSize   = mySize;
  const int aLength = myLength;
  myString          = theOther.myString;
  mySize            = theOther.mySize;
  myLength          = theOther.myLength;
  theOther.myString = aString;
  theOther.mySize   = aSize;
  theOther.myLength = aLength;
}

#if !defined(__ANDROID__)

class NCollection_UtfStringTool
{
public:
  NCollection_UtfStringTool()
      : myWideBuffer(nullptr)
  {
  }

  Standard_EXPORT ~NCollection_UtfStringTool();

  Standard_EXPORT wchar_t* FromLocale(const char* theString);

  Standard_EXPORT static bool ToLocale(const wchar_t* theWideString,
                                       char*          theBuffer,
                                       const int      theSizeBytes);

private:
  wchar_t* myWideBuffer;
};
#endif

template <typename Type>
inline void NCollection_UtfString<Type>::FromLocale(const char* theString, const int theLength)
{
#if defined(__ANDROID__)

  FromUnicode(theString, theLength);
#else
  NCollection_UtfStringTool aConvertor;
  wchar_t*                  aWideBuffer = aConvertor.FromLocale(theString);
  if (aWideBuffer == nullptr)
  {
    Clear();
    return;
  }
  FromUnicode(aWideBuffer, theLength);
#endif
}

template <typename Type>
inline bool NCollection_UtfString<Type>::ToLocale(char* theBuffer, const int theSizeBytes) const
{
#if defined(__ANDROID__)

  NCollection_UtfString<char> anUtf8Copy(myString, myLength);
  const int                   aSize = anUtf8Copy.Size() + 1;
  if (theSizeBytes < aSize)
  {
    return false;
  }
  std::memcpy(theBuffer, anUtf8Copy.ToCString(), (size_t)aSize);
  return true;
#else
  NCollection_UtfString<wchar_t> aWideCopy(myString, myLength);
  return NCollection_UtfStringTool::ToLocale(aWideCopy.ToCString(), theBuffer, theSizeBytes);
#endif
}

template <typename Type>
inline const NCollection_UtfString<Type>& NCollection_UtfString<Type>::operator=(
  const char* theStringUtf8)
{
  FromUnicode(theStringUtf8);
  return (*this);
}

template <typename Type>
inline const NCollection_UtfString<Type>& NCollection_UtfString<Type>::operator=(
  const wchar_t* theStringUtfWide)
{
  FromUnicode(theStringUtfWide);
  return (*this);
}

template <typename Type>
inline bool NCollection_UtfString<Type>::IsEqual(
  const NCollection_UtfString& theCompare) const noexcept
{
  return this == &theCompare
         || strAreEqual(myString, mySize, theCompare.myString, theCompare.mySize);
}

template <typename Type>
inline bool NCollection_UtfString<Type>::operator!=(
  const NCollection_UtfString& theCompare) const noexcept
{
  return (!NCollection_UtfString::operator==(theCompare));
}

template <typename Type>
inline NCollection_UtfString<Type>& NCollection_UtfString<Type>::operator+=(
  const NCollection_UtfString<Type>& theAppend)
{
  if (theAppend.IsEmpty())
  {
    return (*this);
  }

  int   aSize   = mySize + theAppend.mySize;
  Type* aString = strAlloc(aSize);
  strCopy((uint8_t*)aString, (const uint8_t*)myString, mySize);
  strCopy((uint8_t*)aString + mySize, (const uint8_t*)theAppend.myString, theAppend.mySize);

  strFree(myString);
  mySize   = aSize;
  myString = aString;
  myLength += theAppend.myLength;
  return (*this);
}

template <typename Type>
inline NCollection_UtfString<Type> NCollection_UtfString<Type>::SubString(const int theStart,
                                                                          const int theEnd) const
{
  if (theStart >= theEnd)
  {
    return NCollection_UtfString<Type>();
  }
  for (NCollection_UtfIterator<Type> anIter(myString); *anIter != 0; ++anIter)
  {
    if (anIter.Index() >= theStart)
    {
      return NCollection_UtfString<Type>(anIter.BufferHere(), theEnd - theStart);
    }
  }
  return NCollection_UtfString<Type>();
}

template <typename Type>
inline const NCollection_UtfString<char> NCollection_UtfString<Type>::ToUtf8() const
{
  NCollection_UtfString<char> aCopy;
  aCopy.FromUnicode(myString);
  return aCopy;
}

template <typename Type>
inline const NCollection_UtfString<char16_t> NCollection_UtfString<Type>::ToUtf16() const
{
  NCollection_UtfString<char16_t> aCopy;
  aCopy.FromUnicode(myString);
  return aCopy;
}

template <typename Type>
inline const NCollection_UtfString<char32_t> NCollection_UtfString<Type>::ToUtf32() const
{
  NCollection_UtfString<char32_t> aCopy;
  aCopy.FromUnicode(myString);
  return aCopy;
}

template <typename Type>
inline const NCollection_UtfString<wchar_t> NCollection_UtfString<Type>::ToUtfWide() const
{
  NCollection_UtfString<wchar_t> aCopy;
  aCopy.FromUnicode(myString);
  return aCopy;
}
