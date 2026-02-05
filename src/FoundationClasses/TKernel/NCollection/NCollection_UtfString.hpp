#pragma once

#include <NCollection_UtfIterator.hpp>

#include <cstring>
#include <cstdlib>

//! This template class represent constant UTF-* string.
//! String stored in memory continuously, always NULL-terminated
//! and can be used as standard C-string using ToCString() method.
//!
//! Notice that changing the string is not allowed
//! and any modifications should produce new string.
//!
//! In comments to this class, terms "Unicode symbol" is used as
//! synonym of "Unicode code point".
template <typename Type>
class NCollection_UtfString
{

public:
  NCollection_UtfIterator<Type> Iterator() const { return NCollection_UtfIterator<Type>(myString); }

  //! @return the size of the buffer in bytes, excluding NULL-termination symbol
  int Size() const noexcept { return mySize; }

  //! @return the length of the string in Unicode symbols
  int Length() const noexcept { return myLength; }

  //! Retrieve Unicode symbol at specified position.
  //! Warning! This is a slow access. Iterator should be used for consecutive parsing.
  //! @param theCharIndex the index of the symbol, should be lesser than Length()
  //! @return the Unicode symbol value
  char32_t GetChar(const int theCharIndex) const;

  //! Retrieve string buffer at specified position.
  //! Warning! This is a slow access. Iterator should be used for consecutive parsing.
  //! @param theCharIndex the index of the symbol, should be less than Length()
  //!        (first symbol of the string has index 0)
  //! @return the pointer to the symbol
  const Type* GetCharBuffer(const int theCharIndex) const;

  //! Retrieve Unicode symbol at specified position.
  //! Warning! This is a slow access. Iterator should be used for consecutive parsing.
  char32_t operator[](const int theCharIndex) const { return GetChar(theCharIndex); }

  //! Initialize empty string.
  NCollection_UtfString();

  //! Copy constructor.
  //! @param theCopy string to copy.
  NCollection_UtfString(const NCollection_UtfString& theCopy);

  //! Move constructor
  NCollection_UtfString(NCollection_UtfString&& theOther) noexcept;

  //! Copy constructor from UTF-8 string.
  //! @param theCopyUtf8 UTF-8 string to copy
  //! @param theLength   optional length limit in Unicode symbols (NOT bytes!)
  //! The string is copied till NULL symbol or, if theLength >0,
  //! till either NULL or theLength-th symbol (which comes first).
  NCollection_UtfString(const char* theCopyUtf8, const int theLength = -1);

  //! Copy constructor from UTF-16 string.
  //! @param theCopyUtf16 UTF-16 string to copy
  //! @param theLength    the length limit in Unicode symbols (NOT bytes!)
  //! The string is copied till NULL symbol or, if theLength >0,
  //! till either NULL or theLength-th symbol (which comes first).
  NCollection_UtfString(const char16_t* theCopyUtf16, const int theLength = -1);

  //! Copy constructor from UTF-32 string.
  //! @param theCopyUtf32 UTF-32 string to copy
  //! @param theLength    the length limit in Unicode symbols (NOT bytes!)
  //! The string is copied till NULL symbol or, if theLength >0,
  //! till either NULL or theLength-th symbol (which comes first).
  NCollection_UtfString(const char32_t* theCopyUtf32, const int theLength = -1);

#if !defined(_MSC_VER) || defined(_NATIVE_WCHAR_T_DEFINED)                                         \
  || (defined(_MSC_VER) && _MSC_VER >= 1900)
  //! Copy constructor from wide UTF string.
  //! @param theCopyUtfWide wide UTF string to copy
  //! @param theLength      the length limit in Unicode symbols (NOT bytes!)
  //! The string is copied till NULL symbol or, if theLength >0,
  //! till either NULL or theLength-th symbol (which comes first).
  //!
  //! This constructor is undefined if wchar_t is the same type as char16_t.
  NCollection_UtfString(const wchar_t* theCopyUtfWide, const int theLength = -1);
#endif

  //! Copy from Unicode string in UTF-8, UTF-16, or UTF-32 encoding,
  //! determined by size of TypeFrom character type.
  //! @param theStringUtf Unicode string
  //! @param theLength    the length limit in Unicode symbols
  //! The string is copied till NULL symbol or, if theLength >0,
  //! till either NULL or theLength-th symbol (which comes first).
  template <typename TypeFrom>
  inline void FromUnicode(const TypeFrom* theStringUtf, const int theLength = -1)
  {
    NCollection_UtfIterator<TypeFrom> anIterRead(theStringUtf);
    if (*anIterRead == 0)
    {
      // special case
      Clear();
      return;
    }
    fromUnicodeImpl(theStringUtf, theLength, anIterRead);
  }

  //! Copy from multibyte string in current system locale.
  //! @param theString multibyte string
  //! @param theLength the length limit in Unicode symbols
  //! The string is copied till NULL symbol or, if theLength >0,
  //! till either NULL or theLength-th symbol (which comes first).
  void FromLocale(const char* theString, const int theLength = -1);

  //! Destructor.
  ~NCollection_UtfString();

  //! Compares this string with another one.
  bool IsEqual(const NCollection_UtfString& theCompare) const noexcept;

  //! Returns the substring.
  //! @param theStart start index (inclusive) of subString
  //! @param theEnd   end index   (exclusive) of subString
  //! @return the substring
  NCollection_UtfString SubString(const int theStart, const int theEnd) const;

  //! Returns NULL-terminated Unicode string.
  //! Should not be modified or deleted!
  //! @return (const Type* ) pointer to string
  const Type* ToCString() const noexcept { return myString; }

  //! @return copy in UTF-8 format
  const NCollection_UtfString<char> ToUtf8() const;

  //! @return copy in UTF-16 format
  const NCollection_UtfString<char16_t> ToUtf16() const;

  //! @return copy in UTF-32 format
  const NCollection_UtfString<char32_t> ToUtf32() const;

  //! @return copy in wide format (UTF-16 on Windows and UTF-32 on Linux)
  const NCollection_UtfString<wchar_t> ToUtfWide() const;

  //! Converts the string into string in the current system locale.
  //! @param theBuffer    output buffer
  //! @param theSizeBytes buffer size in bytes
  //! @return true on success
  bool ToLocale(char* theBuffer, const int theSizeBytes) const;

  //! @return true if string is empty
  bool IsEmpty() const noexcept { return myString[0] == Type(0); }

  //! Zero string.
  void Clear();

public: //! @name assign operators
  //! Copy from another string.
  const NCollection_UtfString& Assign(const NCollection_UtfString& theOther);

  //! Exchange the data of two strings (without reallocating memory).
  void Swap(NCollection_UtfString& theOther) noexcept;

  //! Copy from another string.
  const NCollection_UtfString& operator=(const NCollection_UtfString& theOther)
  {
    return Assign(theOther);
  }

  //! Move assignment operator.
  NCollection_UtfString& operator=(NCollection_UtfString&& theOther)
  {
    Swap(theOther);
    return *this;
  }

  //! Copy from UTF-8 NULL-terminated string.
  const NCollection_UtfString& operator=(const char* theStringUtf8);

  //! Copy from wchar_t UTF NULL-terminated string.
  const NCollection_UtfString& operator=(const wchar_t* theStringUtfWide);

  //! Join strings.
  NCollection_UtfString& operator+=(const NCollection_UtfString& theAppend);

  //! Join two strings.
  friend NCollection_UtfString operator+(const NCollection_UtfString& theLeft,
                                         const NCollection_UtfString& theRight)
  {
    NCollection_UtfString aSumm;
    strFree(aSumm.myString);
    aSumm.mySize   = theLeft.mySize + theRight.mySize;
    aSumm.myLength = theLeft.myLength + theRight.myLength;
    aSumm.myString = strAlloc(aSumm.mySize);

    // copy bytes
    strCopy((uint8_t*)aSumm.myString, (const uint8_t*)theLeft.myString, theLeft.mySize);
    strCopy((uint8_t*)aSumm.myString + theLeft.mySize,
            (const uint8_t*)theRight.myString,
            theRight.mySize);
    return aSumm;
  }

public: //! @name compare operators
  bool operator==(const NCollection_UtfString& theCompare) const noexcept
  {
    return IsEqual(theCompare);
  }

  bool operator!=(const NCollection_UtfString& theCompare) const noexcept;

private: //! @name low-level methods
  //! Implementation of copy routine for string of the same type
  void fromUnicodeImpl(const Type*                    theStringUtf,
                       const int                      theLength,
                       NCollection_UtfIterator<Type>& theIterator)
  {
    Type* anOldBuffer = myString; // necessary in case of self-copying

    // advance to the end
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

  //! Implementation of copy routine for string of other types
  template <typename TypeFrom>
  void fromUnicodeImpl(
    typename opencascade::std::enable_if<!opencascade::std::is_same<Type, TypeFrom>::value,
                                         const TypeFrom*>::type theStringUtf,
    const int                                                   theLength,
    NCollection_UtfIterator<TypeFrom>&                          theIterator)
  {
    Type* anOldBuffer = myString; // necessary in case of self-copying

    mySize               = 0;
    const int aLengthMax = (theLength > 0) ? theLength : IntegerLast();
    for (; *theIterator != 0 && theIterator.Index() < aLengthMax; ++theIterator)
    {
      mySize += theIterator.template AdvanceBytesUtf<Type>();
    }
    myLength = theIterator.Index();

    myString = strAlloc(mySize);

    // copy string
    theIterator.Init(theStringUtf);
    Type* anIterWrite = myString;
    for (; *theIterator != 0 && theIterator.Index() < myLength; ++theIterator)
    {
      anIterWrite = theIterator.GetUtf(anIterWrite);
    }

    strFree(anOldBuffer);
  }

  //! Allocate NULL-terminated string buffer.
  static Type* strAlloc(const size_t theSizeBytes)
  {
    Type* aPtr = (Type*)Standard::Allocate(theSizeBytes + sizeof(Type));
    if (aPtr != nullptr)
    {
      // always NULL-terminate the string
      aPtr[theSizeBytes / sizeof(Type)] = Type(0);
    }
    return aPtr;
  }

  //! Release string buffer and nullify the pointer.
  static void strFree(Type*& thePtr) { Standard::Free(thePtr); }

  //! Provides bytes interface to avoid incorrect pointer arithmetics.
  static void strCopy(uint8_t* theStrDst, const uint8_t* theStrSrc, const int theSizeBytes) noexcept
  {
    std::memcpy(theStrDst, theStrSrc, (size_t)theSizeBytes);
  }

  //! Compare two Unicode strings per-byte.
  static bool strAreEqual(const Type* theString1,
                          const int   theSizeBytes1,
                          const Type* theString2,
                          const int   theSizeBytes2) noexcept
  {
    return (theSizeBytes1 == theSizeBytes2)
           && (std::memcmp(theString1, theString2, (size_t)theSizeBytes1) == 0);
  }

private:          //! @name private fields
  Type* myString; //!< string buffer
  int   mySize;   //!< buffer size in bytes, excluding NULL-termination symbol
  // clang-format off
  int myLength; //!< length of the string in Unicode symbols (cached value, excluding NULL-termination symbol)
  // clang-format on
};

// template implementation (inline methods)

template <typename Type>
char32_t NCollection_UtfString<Type>::GetChar(const int theCharIndex) const
{
  // Standard_ASSERT_SKIP (theCharIndex < myLength, "Out of range");
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

//=================================================================================================

template <typename Type>
const Type* NCollection_UtfString<Type>::GetCharBuffer(const int theCharIndex) const
{
  // Standard_ASSERT_SKIP(theCharIndex < myLength);
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

//=================================================================================================

template <typename Type>
inline void NCollection_UtfString<Type>::Clear()
{
  strFree(myString);
  mySize   = 0;
  myLength = 0;
  myString = strAlloc(mySize);
}

//=================================================================================================

template <typename Type>
inline NCollection_UtfString<Type>::NCollection_UtfString()
    : myString(strAlloc(0)),
      mySize(0),
      myLength(0)
{
}

//=================================================================================================

template <typename Type>
inline NCollection_UtfString<Type>::NCollection_UtfString(const NCollection_UtfString& theCopy)
    : myString(strAlloc(theCopy.mySize)),
      mySize(theCopy.mySize),
      myLength(theCopy.myLength)
{
  strCopy((uint8_t*)myString, (const uint8_t*)theCopy.myString, mySize);
}

//=================================================================================================

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

//=================================================================================================

template <typename Type>
inline NCollection_UtfString<Type>::NCollection_UtfString(const char* theCopyUtf8,
                                                          const int   theLength)
    : myString(nullptr),
      mySize(0),
      myLength(0)
{
  FromUnicode(theCopyUtf8, theLength);
}

//=================================================================================================

template <typename Type>
inline NCollection_UtfString<Type>::NCollection_UtfString(const char16_t* theCopyUtf16,
                                                          const int       theLength)
    : myString(nullptr),
      mySize(0),
      myLength(0)
{
  FromUnicode(theCopyUtf16, theLength);
}

//=================================================================================================

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
//=================================================================================================

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

// =======================================================================
// function : ~NCollection_UtfString
// purpose  :
// =======================================================================
template <typename Type>
inline NCollection_UtfString<Type>::~NCollection_UtfString()
{
  strFree(myString);
}

//=================================================================================================

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

//=================================================================================================

template <typename Type>
inline void NCollection_UtfString<Type>::Swap(NCollection_UtfString<Type>& theOther) noexcept
{
  // Note: we could use std::swap() here, but prefer to not
  // have dependency on <algorithm> header at that level
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
//! Auxiliary conversion tool.
class NCollection_UtfStringTool
{
public:
  //! Empty constructor.
  NCollection_UtfStringTool()
      : myWideBuffer(nullptr)
  {
  }

  //! Destructor for temporary resources.
  Standard_EXPORT ~NCollection_UtfStringTool();

  //! Convert the string from current locale into UNICODE (wide characters) using system APIs.
  //! Returned pointer will be released by this tool.
  Standard_EXPORT wchar_t* FromLocale(const char* theString);

  //! Convert the UNICODE (wide characters) string into locale using system APIs.
  Standard_EXPORT static bool ToLocale(const wchar_t* theWideString,
                                       char*          theBuffer,
                                       const int      theSizeBytes);

private:
  wchar_t* myWideBuffer; //!< temporary variable
};
#endif

//=================================================================================================

template <typename Type>
inline void NCollection_UtfString<Type>::FromLocale(const char* theString, const int theLength)
{
#if defined(__ANDROID__)
  // no locales on Android
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

//=================================================================================================

template <typename Type>
inline bool NCollection_UtfString<Type>::ToLocale(char* theBuffer, const int theSizeBytes) const
{
#if defined(__ANDROID__)
  // no locales on Android
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

// =======================================================================
// function : operator=
// purpose  :
// =======================================================================
template <typename Type>
inline const NCollection_UtfString<Type>& NCollection_UtfString<Type>::operator=(
  const char* theStringUtf8)
{
  FromUnicode(theStringUtf8);
  return (*this);
}

// =======================================================================
// function : operator=
// purpose  :
// =======================================================================
template <typename Type>
inline const NCollection_UtfString<Type>& NCollection_UtfString<Type>::operator=(
  const wchar_t* theStringUtfWide)
{
  FromUnicode(theStringUtfWide);
  return (*this);
}

//=================================================================================================

template <typename Type>
inline bool NCollection_UtfString<Type>::IsEqual(
  const NCollection_UtfString& theCompare) const noexcept
{
  return this == &theCompare
         || strAreEqual(myString, mySize, theCompare.myString, theCompare.mySize);
}

// =======================================================================
// function : operator!=
// purpose  :
// =======================================================================
template <typename Type>
inline bool NCollection_UtfString<Type>::operator!=(
  const NCollection_UtfString& theCompare) const noexcept
{
  return (!NCollection_UtfString::operator==(theCompare));
}

// =======================================================================
// function : operator+=
// purpose  :
// =======================================================================
template <typename Type>
inline NCollection_UtfString<Type>& NCollection_UtfString<Type>::operator+=(
  const NCollection_UtfString<Type>& theAppend)
{
  if (theAppend.IsEmpty())
  {
    return (*this);
  }

  // create new string
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

//=================================================================================================

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

//=================================================================================================

template <typename Type>
inline const NCollection_UtfString<char> NCollection_UtfString<Type>::ToUtf8() const
{
  NCollection_UtfString<char> aCopy;
  aCopy.FromUnicode(myString);
  return aCopy;
}

//=================================================================================================

template <typename Type>
inline const NCollection_UtfString<char16_t> NCollection_UtfString<Type>::ToUtf16() const
{
  NCollection_UtfString<char16_t> aCopy;
  aCopy.FromUnicode(myString);
  return aCopy;
}

//=================================================================================================

template <typename Type>
inline const NCollection_UtfString<char32_t> NCollection_UtfString<Type>::ToUtf32() const
{
  NCollection_UtfString<char32_t> aCopy;
  aCopy.FromUnicode(myString);
  return aCopy;
}

//=================================================================================================

template <typename Type>
inline const NCollection_UtfString<wchar_t> NCollection_UtfString<Type>::ToUtfWide() const
{
  NCollection_UtfString<wchar_t> aCopy;
  aCopy.FromUnicode(myString);
  return aCopy;
}
