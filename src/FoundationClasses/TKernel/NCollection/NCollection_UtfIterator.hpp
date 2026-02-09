#pragma once

#include <Standard_Handle.hpp>

template <typename Type>
class NCollection_UtfIterator
{

public:
  NCollection_UtfIterator(const Type* theString)
      : myPosition(theString),
        myPosNext(theString),
        myCharIndex(0),
        myCharUtf32(0)
  {
    if (theString != nullptr)
    {
      ++(*this);
      myCharIndex = 0;
    }
  }

  void Init(const Type* theString)
  {
    myPosition  = theString;
    myPosNext   = theString;
    myCharUtf32 = 0;
    if (theString != nullptr)
    {
      ++(*this);
    }
    myCharIndex = 0;
  }

  NCollection_UtfIterator& operator++()
  {
    myPosition = myPosNext;
    ++myCharIndex;
    readNext(static_cast<const typename CharTypeChooser<Type>::type*>(nullptr));
    return *this;
  }

  NCollection_UtfIterator operator++(int)
  {
    NCollection_UtfIterator aCopy = *this;
    ++*this;
    return aCopy;
  }

  constexpr bool operator==(const NCollection_UtfIterator& theRight) const noexcept
  {
    return myPosition == theRight.myPosition;
  }

  constexpr bool IsValid() const noexcept { return myCharUtf32 <= UTF32_MAX_LEGAL; }

  constexpr char32_t operator*() const noexcept { return myCharUtf32; }

  constexpr const Type* BufferHere() const noexcept { return myPosition; }

  Type* ChangeBufferHere() noexcept { return (Type*)myPosition; }

  constexpr const Type* BufferNext() const noexcept { return myPosNext; }

  constexpr int Index() const noexcept { return myCharIndex; }

  int AdvanceBytesUtf8() const;

  int AdvanceBytesUtf16() const;

  int AdvanceCodeUnitsUtf16() const;

  constexpr int AdvanceBytesUtf32() const noexcept { return int(sizeof(char32_t)); }

  char*          GetUtf8(char* theBuffer) const;
  unsigned char* GetUtf8(unsigned char* theBuffer) const;

  char16_t* GetUtf16(char16_t* theBuffer) const;

  char32_t* GetUtf32(char32_t* theBuffer) const;

  template <typename TypeWrite>
  inline int AdvanceBytesUtf() const
  {
    return advanceBytes(static_cast<const typename CharTypeChooser<TypeWrite>::type*>(nullptr));
  }

  template <typename TypeWrite>
  inline TypeWrite* GetUtf(TypeWrite* theBuffer) const
  {
    return (
      TypeWrite*)(getUtf(reinterpret_cast<typename CharTypeChooser<TypeWrite>::type*>(theBuffer)));
  }

private:
  template <typename TypeChar>
  class CharTypeChooser
      : public std::conditional<
          sizeof(TypeChar) == 1,
          char,
          typename std::conditional<
            sizeof(TypeChar) == 2,
            char16_t,
            typename std::conditional<sizeof(TypeChar) == 4, char32_t, void>::type>::type>
  {
  };

  void readUTF8();

  void readUTF16();

  void readNext(const char*) { readUTF8(); }

  void readNext(const char16_t*) { readUTF16(); }

  void readNext(const char32_t*) noexcept { myCharUtf32 = *myPosNext++; }

  int advanceBytes(const char*) const { return AdvanceBytesUtf8(); }

  int advanceBytes(const char16_t*) const { return AdvanceBytesUtf16(); }

  constexpr int advanceBytes(const char32_t*) const noexcept { return AdvanceBytesUtf32(); }

  char* getUtf(char* theBuffer) const { return GetUtf8(theBuffer); }

  char16_t* getUtf(char16_t* theBuffer) const { return GetUtf16(theBuffer); }

  char32_t* getUtf(char32_t* theBuffer) const { return GetUtf32(theBuffer); }

private:
  static constexpr unsigned char UTF8_BYTES_MINUS_ONE[256] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5};

  static constexpr char32_t offsetsFromUTF8[6] =
    {0x00000000UL, 0x00003080UL, 0x000E2080UL, 0x03C82080UL, 0xFA082080UL, 0x82082080UL};

  static constexpr unsigned char UTF8_FIRST_BYTE_MARK[7] =
    {0x00, 0x00, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC};

  static constexpr char32_t UTF8_BYTE_MASK             = 0xBF;
  static constexpr char32_t UTF8_BYTE_MARK             = 0x80;
  static constexpr char32_t UTF16_SURROGATE_HIGH_START = 0xD800;
  static constexpr char32_t UTF16_SURROGATE_HIGH_END   = 0xDBFF;
  static constexpr char32_t UTF16_SURROGATE_LOW_START  = 0xDC00;
  static constexpr char32_t UTF16_SURROGATE_LOW_END    = 0xDFFF;
  static constexpr char32_t UTF16_SURROGATE_HIGH_SHIFT = 10;
  static constexpr char32_t UTF16_SURROGATE_LOW_BASE   = 0x0010000UL;
  static constexpr char32_t UTF16_SURROGATE_LOW_MASK   = 0x3FFUL;
  static constexpr char32_t UTF32_MAX_BMP              = 0x0000FFFFUL;
  static constexpr char32_t UTF32_MAX_LEGAL            = 0x0010FFFFUL;

private:
  const Type* myPosition;
  const Type* myPosNext;
  int         myCharIndex;
  char32_t    myCharUtf32;
};

template <typename Type>
inline void NCollection_UtfIterator<Type>::readUTF8()
{

  unsigned char*      aPos         = (unsigned char*)myPosNext;
  const unsigned char aBytesToRead = UTF8_BYTES_MINUS_ONE[*aPos];
  myCharUtf32                      = 0;
  switch (aBytesToRead)
  {
    case 5:
      myCharUtf32 += *aPos++;
      myCharUtf32 <<= 6;
      [[fallthrough]];
    case 4:
      myCharUtf32 += *aPos++;
      myCharUtf32 <<= 6;
      [[fallthrough]];
    case 3:
      myCharUtf32 += *aPos++;
      myCharUtf32 <<= 6;
      [[fallthrough]];
    case 2:
      myCharUtf32 += *aPos++;
      myCharUtf32 <<= 6;
      [[fallthrough]];
    case 1:
      myCharUtf32 += *aPos++;
      myCharUtf32 <<= 6;
      [[fallthrough]];
    case 0:
      myCharUtf32 += *aPos++;
  }
  myCharUtf32 -= offsetsFromUTF8[aBytesToRead];
  myPosNext = (Type*)aPos;
}

template <typename Type>
inline void NCollection_UtfIterator<Type>::readUTF16()
{
  char32_t aChar = *myPosNext++;

  if (aChar >= UTF16_SURROGATE_HIGH_START && aChar <= UTF16_SURROGATE_HIGH_END)
  {
    const char32_t aChar2 = *myPosNext;

    if (aChar2 >= UTF16_SURROGATE_LOW_START && aChar2 <= UTF16_SURROGATE_LOW_END)
    {
      aChar = ((aChar - UTF16_SURROGATE_HIGH_START) << UTF16_SURROGATE_HIGH_SHIFT)
              + (aChar2 - UTF16_SURROGATE_LOW_START) + UTF16_SURROGATE_LOW_BASE;
      ++myPosNext;
    }
  }
  myCharUtf32 = aChar;
}

template <typename Type>
inline int NCollection_UtfIterator<Type>::AdvanceBytesUtf8() const
{
  if (myCharUtf32 >= UTF16_SURROGATE_HIGH_START && myCharUtf32 <= UTF16_SURROGATE_LOW_END)
  {

    return 0;
  }
  else if (myCharUtf32 < char32_t(0x80))
  {
    return 1;
  }
  else if (myCharUtf32 < char32_t(0x800))
  {
    return 2;
  }
  else if (myCharUtf32 < char32_t(0x10000))
  {
    return 3;
  }
  else if (myCharUtf32 <= UTF32_MAX_LEGAL)
  {
    return 4;
  }
  else
  {

    return 0;
  }
}

template <typename Type>
inline char* NCollection_UtfIterator<Type>::GetUtf8(char* theBuffer) const
{

  return (char*)GetUtf8((unsigned char*)theBuffer);
}

template <typename Type>
inline unsigned char* NCollection_UtfIterator<Type>::GetUtf8(unsigned char* theBuffer) const
{
  char32_t aChar = myCharUtf32;
  if (myCharUtf32 >= UTF16_SURROGATE_HIGH_START && myCharUtf32 <= UTF16_SURROGATE_LOW_END)
  {

    return theBuffer;
  }
  else if (myCharUtf32 < char32_t(0x80))
  {
    *theBuffer++ = static_cast<unsigned char>(aChar | UTF8_FIRST_BYTE_MARK[1]);
    return theBuffer;
  }
  else if (myCharUtf32 < char32_t(0x800))
  {
    *++theBuffer = static_cast<unsigned char>((aChar | UTF8_BYTE_MARK) & UTF8_BYTE_MASK);
    aChar >>= 6;
    *--theBuffer = static_cast<unsigned char>(aChar | UTF8_FIRST_BYTE_MARK[2]);
    return theBuffer + 2;
  }
  else if (myCharUtf32 < char32_t(0x10000))
  {
    theBuffer += 3;
    *--theBuffer = static_cast<unsigned char>((aChar | UTF8_BYTE_MARK) & UTF8_BYTE_MASK);
    aChar >>= 6;
    *--theBuffer = static_cast<unsigned char>((aChar | UTF8_BYTE_MARK) & UTF8_BYTE_MASK);
    aChar >>= 6;
    *--theBuffer = static_cast<unsigned char>(aChar | UTF8_FIRST_BYTE_MARK[3]);
    return theBuffer + 3;
  }
  else if (myCharUtf32 <= UTF32_MAX_LEGAL)
  {
    theBuffer += 4;
    *--theBuffer = static_cast<unsigned char>((aChar | UTF8_BYTE_MARK) & UTF8_BYTE_MASK);
    aChar >>= 6;
    *--theBuffer = static_cast<unsigned char>((aChar | UTF8_BYTE_MARK) & UTF8_BYTE_MASK);
    aChar >>= 6;
    *--theBuffer = static_cast<unsigned char>((aChar | UTF8_BYTE_MARK) & UTF8_BYTE_MASK);
    aChar >>= 6;
    *--theBuffer = static_cast<unsigned char>(aChar | UTF8_FIRST_BYTE_MARK[4]);
    return theBuffer + 4;
  }
  else
  {

    return theBuffer;
  }
}

template <typename Type>
inline int NCollection_UtfIterator<Type>::AdvanceBytesUtf16() const
{
  return AdvanceCodeUnitsUtf16() * sizeof(char16_t);
}

template <typename Type>
inline int NCollection_UtfIterator<Type>::AdvanceCodeUnitsUtf16() const
{
  if (myCharUtf32 <= UTF32_MAX_BMP)
  {

    if (myCharUtf32 >= UTF16_SURROGATE_HIGH_START && myCharUtf32 <= UTF16_SURROGATE_LOW_END)
    {
      return 0;
    }
    else
    {
      return 1;
    }
  }
  else if (myCharUtf32 > UTF32_MAX_LEGAL)
  {

    return 0;
  }
  else
  {

    return 2;
  }
}

template <typename Type>
inline char16_t* NCollection_UtfIterator<Type>::GetUtf16(char16_t* theBuffer) const
{
  if (myCharUtf32 <= UTF32_MAX_BMP)
  {

    if (myCharUtf32 >= UTF16_SURROGATE_HIGH_START && myCharUtf32 <= UTF16_SURROGATE_LOW_END)
    {
      return theBuffer;
    }
    else
    {
      *theBuffer++ = char16_t(myCharUtf32);
      return theBuffer;
    }
  }
  else if (myCharUtf32 > UTF32_MAX_LEGAL)
  {

    return theBuffer;
  }
  else
  {

    char32_t aChar = myCharUtf32 - UTF16_SURROGATE_LOW_BASE;
    *theBuffer++   = char16_t((aChar >> UTF16_SURROGATE_HIGH_SHIFT) + UTF16_SURROGATE_HIGH_START);
    *theBuffer++   = char16_t((aChar & UTF16_SURROGATE_LOW_MASK) + UTF16_SURROGATE_LOW_START);
    return theBuffer;
  }
}

template <typename Type>
inline char32_t* NCollection_UtfIterator<Type>::GetUtf32(char32_t* theBuffer) const
{
  *theBuffer++ = myCharUtf32;
  return theBuffer;
}
