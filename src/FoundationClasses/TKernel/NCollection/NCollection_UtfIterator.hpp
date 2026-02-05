#pragma once

#include <Standard_Handle.hpp>

//! Template class for Unicode strings support.
//!
//! It defines an iterator and provide correct way to read multi-byte text (UTF-8 and UTF-16)
//! and convert it from one to another.
//! The current value of iterator is returned as UTF-32 Unicode symbol.
//!
//! Here and below term "Unicode symbol" is used as
//! synonym of "Unicode code point".
template <typename Type>
class NCollection_UtfIterator
{

public:
  //! Constructor.
  //! @param theString buffer to iterate
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

  //! Initialize iterator within specified NULL-terminated string.
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

  //! Pre-increment operator. Reads the next unicode symbol.
  //! Notice - no protection against overrun!
  NCollection_UtfIterator& operator++()
  {
    myPosition = myPosNext;
    ++myCharIndex;
    readNext(static_cast<const typename CharTypeChooser<Type>::type*>(nullptr));
    return *this;
  }

  //! Post-increment operator.
  //! Notice - no protection against overrun!
  NCollection_UtfIterator operator++(int)
  {
    NCollection_UtfIterator aCopy = *this;
    ++*this;
    return aCopy;
  }

  //! Equality operator.
  constexpr bool operator==(const NCollection_UtfIterator& theRight) const noexcept
  {
    return myPosition == theRight.myPosition;
  }

  //! Return true if Unicode symbol is within valid range.
  constexpr bool IsValid() const noexcept { return myCharUtf32 <= UTF32_MAX_LEGAL; }

  //! Dereference operator.
  //! @return the UTF-32 codepoint of the symbol currently pointed by iterator.
  constexpr char32_t operator*() const noexcept { return myCharUtf32; }

  //! Buffer-fetching getter.
  constexpr const Type* BufferHere() const noexcept { return myPosition; }

  //! Buffer-fetching getter. Dangerous! Iterator should be reinitialized on buffer change.
  Type* ChangeBufferHere() noexcept { return (Type*)myPosition; }

  //! Buffer-fetching getter.
  constexpr const Type* BufferNext() const noexcept { return myPosNext; }

  //! @return the index displacement from iterator initialization
  //!         (first symbol has index 0)
  constexpr int Index() const noexcept { return myCharIndex; }

  //! @return the advance in bytes to store current symbol in UTF-8.
  //! 0 means an invalid symbol;
  //! 1-4 bytes are valid range.
  int AdvanceBytesUtf8() const;

  //! @return the advance in bytes to store current symbol in UTF-16.
  //! 0 means an invalid symbol;
  //! 2 bytes is a general case;
  //! 4 bytes for surrogate pair.
  int AdvanceBytesUtf16() const;

  //! @return the advance in bytes to store current symbol in UTF-16.
  //! 0 means an invalid symbol;
  //! 1 16-bit code unit is a general case;
  //! 2 16-bit code units for surrogate pair.
  int AdvanceCodeUnitsUtf16() const;

  //! @return the advance in bytes to store current symbol in UTF-32.
  //! Always 4 bytes (method for consistency).
  constexpr int AdvanceBytesUtf32() const noexcept { return int(sizeof(char32_t)); }

  //! Fill the UTF-8 buffer within current Unicode symbol.
  //! Use method AdvanceUtf8() to allocate buffer with enough size.
  //! @param theBuffer buffer to fill
  //! @return new buffer position (for next char)
  char*          GetUtf8(char* theBuffer) const;
  unsigned char* GetUtf8(unsigned char* theBuffer) const;

  //! Fill the UTF-16 buffer within current Unicode symbol.
  //! Use method AdvanceUtf16() to allocate buffer with enough size.
  //! @param theBuffer buffer to fill
  //! @return new buffer position (for next char)
  char16_t* GetUtf16(char16_t* theBuffer) const;

  //! Fill the UTF-32 buffer within current Unicode symbol.
  //! Use method AdvanceUtf32() to allocate buffer with enough size.
  //! @param theBuffer buffer to fill
  //! @return new buffer position (for next char)
  char32_t* GetUtf32(char32_t* theBuffer) const;

  //! @return the advance in TypeWrite chars needed to store current symbol
  template <typename TypeWrite>
  inline int AdvanceBytesUtf() const
  {
    return advanceBytes(static_cast<const typename CharTypeChooser<TypeWrite>::type*>(nullptr));
  }

  //! Fill the UTF-** buffer within current Unicode symbol.
  //! Use method AdvanceUtf**() to allocate buffer with enough size.
  //! @param theBuffer buffer to fill
  //! @return new buffer position (for next char)
  template <typename TypeWrite>
  inline TypeWrite* GetUtf(TypeWrite* theBuffer) const
  {
    return (
      TypeWrite*)(getUtf(reinterpret_cast<typename CharTypeChooser<TypeWrite>::type*>(theBuffer)));
  }

private:
  //! Helper template class dispatching its argument class
  //! to the equivalent (by size) character (Unicode code unit) type.
  //! The code unit type is defined as nested typedef "type".
  //!
  //! In practice this is relevant for wchar_t type:
  //! typename CharTypeChooser<wchar_t>::type resolves to
  //! char16_t on Windows and to char32_t on Linux.
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

  //! Helper function for reading a single Unicode symbol from the UTF-8 string.
  //! Updates internal state appropriately.
  void readUTF8();

  //! Helper function for reading a single Unicode symbol from the UTF-16 string.
  //! Updates internal state appropriately.
  void readUTF16();

  //! Helper overload methods to dispatch reading function depending on code unit size
  void readNext(const char*) { readUTF8(); }

  void readNext(const char16_t*) { readUTF16(); }

  void readNext(const char32_t*) noexcept { myCharUtf32 = *myPosNext++; }

  //! Helper overload methods to dispatch advance function depending on code unit size
  int advanceBytes(const char*) const { return AdvanceBytesUtf8(); }

  int advanceBytes(const char16_t*) const { return AdvanceBytesUtf16(); }

  constexpr int advanceBytes(const char32_t*) const noexcept { return AdvanceBytesUtf32(); }

  //! Helper overload methods to dispatch getter function depending on code unit size
  char* getUtf(char* theBuffer) const { return GetUtf8(theBuffer); }

  char16_t* getUtf(char16_t* theBuffer) const { return GetUtf16(theBuffer); }

  char32_t* getUtf(char32_t* theBuffer) const { return GetUtf32(theBuffer); }

private: //! @name unicode magic numbers
  //! The first character in a UTF-8 sequence indicates how many bytes to read (among other things).
  static constexpr unsigned char UTF8_BYTES_MINUS_ONE[256] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5};

  //! Magic values subtracted from a buffer value during UTF-8 conversion.
  //! This table contains as many values as there might be trailing bytes in a UTF-8 sequence.
  static constexpr char32_t offsetsFromUTF8[6] =
    {0x00000000UL, 0x00003080UL, 0x000E2080UL, 0x03C82080UL, 0xFA082080UL, 0x82082080UL};

  //! The first character in a UTF-8 sequence indicates how many bytes to read.
  static constexpr unsigned char UTF8_FIRST_BYTE_MARK[7] =
    {0x00, 0x00, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC};

  // Magic numbers for UTF encoding/decoding
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

private:                   //! @name private fields
  const Type* myPosition;  //!< buffer position of the first element in the current symbol
  const Type* myPosNext;   //!< buffer position of the first element in the next symbol
  int         myCharIndex; //!< index displacement from iterator initialization
  char32_t    myCharUtf32; //!< Unicode symbol stored at the current buffer position
};

// template implementation
template <typename Type>
inline void NCollection_UtfIterator<Type>::readUTF8()
{
  // unsigned arithmetic used
  unsigned char*      aPos         = (unsigned char*)myPosNext;
  const unsigned char aBytesToRead = UTF8_BYTES_MINUS_ONE[*aPos];
  myCharUtf32                      = 0;
  switch (aBytesToRead)
  {
    case 5:
      myCharUtf32 += *aPos++;
      myCharUtf32 <<= 6; // remember, illegal UTF-8
      [[fallthrough]];
    case 4:
      myCharUtf32 += *aPos++;
      myCharUtf32 <<= 6; // remember, illegal UTF-8
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

//=================================================================================================

template <typename Type>
inline void NCollection_UtfIterator<Type>::readUTF16()
{
  char32_t aChar = *myPosNext++;
  // if we have the first half of the surrogate pair
  if (aChar >= UTF16_SURROGATE_HIGH_START && aChar <= UTF16_SURROGATE_HIGH_END)
  {
    const char32_t aChar2 = *myPosNext;
    // complete the surrogate pair
    if (aChar2 >= UTF16_SURROGATE_LOW_START && aChar2 <= UTF16_SURROGATE_LOW_END)
    {
      aChar = ((aChar - UTF16_SURROGATE_HIGH_START) << UTF16_SURROGATE_HIGH_SHIFT)
              + (aChar2 - UTF16_SURROGATE_LOW_START) + UTF16_SURROGATE_LOW_BASE;
      ++myPosNext;
    }
  }
  myCharUtf32 = aChar;
}

//=================================================================================================

template <typename Type>
inline int NCollection_UtfIterator<Type>::AdvanceBytesUtf8() const
{
  if (myCharUtf32 >= UTF16_SURROGATE_HIGH_START && myCharUtf32 <= UTF16_SURROGATE_LOW_END)
  {
    // UTF-16 surrogate values are illegal in UTF-32
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
    // illegal
    return 0;
  }
}

//=================================================================================================

template <typename Type>
inline char* NCollection_UtfIterator<Type>::GetUtf8(char* theBuffer) const
{
  // unsigned arithmetic used
  return (char*)GetUtf8((unsigned char*)theBuffer);
}

//=================================================================================================

template <typename Type>
inline unsigned char* NCollection_UtfIterator<Type>::GetUtf8(unsigned char* theBuffer) const
{
  char32_t aChar = myCharUtf32;
  if (myCharUtf32 >= UTF16_SURROGATE_HIGH_START && myCharUtf32 <= UTF16_SURROGATE_LOW_END)
  {
    // UTF-16 surrogate values are illegal in UTF-32
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
    // illegal
    return theBuffer;
  }
}

//=================================================================================================

template <typename Type>
inline int NCollection_UtfIterator<Type>::AdvanceBytesUtf16() const
{
  return AdvanceCodeUnitsUtf16() * sizeof(char16_t);
}

//=================================================================================================

template <typename Type>
inline int NCollection_UtfIterator<Type>::AdvanceCodeUnitsUtf16() const
{
  if (myCharUtf32 <= UTF32_MAX_BMP) // target is a character <= 0xFFFF
  {
    // UTF-16 surrogate values are illegal in UTF-32; 0xffff or 0xfffe are both reserved values
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
    // illegal
    return 0;
  }
  else
  {
    // target is a character in range 0xFFFF - 0x10FFFF
    // surrogate pair
    return 2;
  }
}

//=================================================================================================

template <typename Type>
inline char16_t* NCollection_UtfIterator<Type>::GetUtf16(char16_t* theBuffer) const
{
  if (myCharUtf32 <= UTF32_MAX_BMP) // target is a character <= 0xFFFF
  {
    // UTF-16 surrogate values are illegal in UTF-32; 0xffff or 0xfffe are both reserved values
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
    // illegal
    return theBuffer;
  }
  else
  {
    // surrogate pair
    char32_t aChar = myCharUtf32 - UTF16_SURROGATE_LOW_BASE;
    *theBuffer++   = char16_t((aChar >> UTF16_SURROGATE_HIGH_SHIFT) + UTF16_SURROGATE_HIGH_START);
    *theBuffer++   = char16_t((aChar & UTF16_SURROGATE_LOW_MASK) + UTF16_SURROGATE_LOW_START);
    return theBuffer;
  }
}

//=================================================================================================

template <typename Type>
inline char32_t* NCollection_UtfIterator<Type>::GetUtf32(char32_t* theBuffer) const
{
  *theBuffer++ = myCharUtf32;
  return theBuffer;
}
