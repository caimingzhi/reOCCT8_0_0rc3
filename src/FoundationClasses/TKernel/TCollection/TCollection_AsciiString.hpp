#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_PCharacter.hpp>
#include <Standard_CString.hpp>
#include <Standard_Real.hpp>
#include <Standard_OStream.hpp>
#include <Standard_IStream.hpp>
#include <Standard_Macro.hpp>

#if Standard_CPP17_OR_HIGHER
  #include <string_view>
#endif

class TCollection_ExtendedString;

class TCollection_AsciiString
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TCollection_AsciiString() noexcept;

#if Standard_CPP17_OR_HIGHER

  explicit inline TCollection_AsciiString(const std::string_view& theStringView);
#endif

  inline TCollection_AsciiString(const char* theMessage);

  Standard_EXPORT TCollection_AsciiString(const char* theMessage, const int theLength);

  Standard_EXPORT TCollection_AsciiString(const char theChar);

  Standard_EXPORT TCollection_AsciiString(const int theLength, const char theFiller);

  Standard_EXPORT TCollection_AsciiString(const int theValue);

  Standard_EXPORT TCollection_AsciiString(const double theValue);

  Standard_EXPORT TCollection_AsciiString(const TCollection_AsciiString& theString);

  Standard_EXPORT TCollection_AsciiString(TCollection_AsciiString&& theOther) noexcept;

  Standard_EXPORT TCollection_AsciiString(const TCollection_AsciiString& theString,
                                          const char                     theChar);

  Standard_EXPORT TCollection_AsciiString(const TCollection_AsciiString& theString,
                                          const char*                    theMessage);

  Standard_EXPORT TCollection_AsciiString(const TCollection_AsciiString& theString,
                                          const TCollection_AsciiString& theOtherString);

  Standard_EXPORT TCollection_AsciiString(const TCollection_ExtendedString& theExtendedString,
                                          const char                        theReplaceNonAscii = 0);

#if !defined(_MSC_VER) || defined(_NATIVE_WCHAR_T_DEFINED)

  Standard_EXPORT TCollection_AsciiString(const wchar_t* theStringUtf);
#endif

  template <std::size_t N>
  inline TCollection_AsciiString(const char (&theLiteral)[N]);

  Standard_EXPORT void AssignCat(const char theOther);

  void operator+=(const char theOther) { AssignCat(theOther); }

  Standard_EXPORT void AssignCat(const int theOther);

  void operator+=(const int theOther) { AssignCat(theOther); }

  Standard_EXPORT void AssignCat(const double theOther);

  void operator+=(const double theOther) { AssignCat(theOther); }

  Standard_EXPORT void AssignCat(const char* theString, const int theLength);

  inline void AssignCat(const TCollection_AsciiString& theOther);

  void operator+=(const TCollection_AsciiString& theOther) { AssignCat(theOther); }

  inline void AssignCat(const char* theCString);

  void operator+=(const char* theCString) { AssignCat(theCString); }

#if Standard_CPP17_OR_HIGHER

  inline void AssignCat(const std::string_view& theStringView);

  void operator+=(const std::string_view& theStringView) { AssignCat(theStringView); }
#endif

  template <std::size_t N>
  inline void AssignCat(const char (&theLiteral)[N]);

  template <std::size_t N>
  inline void operator+=(const char (&theLiteral)[N]);

  Standard_EXPORT void Capitalize();

  Standard_EXPORT TCollection_AsciiString Cat(const char* theString, const int theLength) const;

  TCollection_AsciiString Cat(const char theOther) const { return Cat(&theOther, 1); }

  inline TCollection_AsciiString operator+(const char theOther) const;

  Standard_EXPORT TCollection_AsciiString Cat(const int theOther) const;

  TCollection_AsciiString operator+(const int theOther) const { return Cat(theOther); }

  Standard_EXPORT TCollection_AsciiString Cat(const double theOther) const;

  TCollection_AsciiString operator+(const double theOther) const { return Cat(theOther); }

  inline TCollection_AsciiString Cat(const TCollection_AsciiString& theOther) const;

  inline TCollection_AsciiString operator+(const TCollection_AsciiString& theOther) const;

  inline TCollection_AsciiString Cat(const char* theCString) const;

  inline TCollection_AsciiString operator+(const char* theCString) const;

#if Standard_CPP17_OR_HIGHER

  inline TCollection_AsciiString Cat(const std::string_view& theStringView) const;

  inline TCollection_AsciiString operator+(const std::string_view& theStringView) const;
#endif

  template <std::size_t N>
  inline TCollection_AsciiString Cat(const char (&theLiteral)[N]) const;

  template <std::size_t N>
  inline TCollection_AsciiString operator+(const char (&theLiteral)[N]) const;

  Standard_EXPORT void Center(const int theWidth, const char theFiller);

  Standard_EXPORT void ChangeAll(const char theChar,
                                 const char theNewChar,
                                 const bool theCaseSensitive = true);

  Standard_EXPORT void Clear();

  Standard_EXPORT void Copy(const char* theString, const int theLength);

  inline void Copy(const char* theCString);

  void operator=(const char* theCString) { Copy(theCString); }

#if Standard_CPP17_OR_HIGHER

  inline void Copy(const std::string_view& theStringView);

  void operator=(const std::string_view& theStringView) { Copy(theStringView); }
#endif

  template <std::size_t N>
  inline void Copy(const char (&theLiteral)[N]);

  template <std::size_t N>
  inline void operator=(const char (&theLiteral)[N]);

  inline void Copy(const TCollection_AsciiString& theFromWhere);

  inline TCollection_AsciiString& operator=(const TCollection_AsciiString& theOther);

  Standard_EXPORT void Move(TCollection_AsciiString&& theOther);

  inline TCollection_AsciiString& operator=(TCollection_AsciiString&& theOther) noexcept;

  Standard_EXPORT void Swap(TCollection_AsciiString& theOther);

  Standard_EXPORT ~TCollection_AsciiString();

  Standard_EXPORT int FirstLocationInSet(const char* theSet,
                                         const int   theSetLength,
                                         const int   theFromIndex,
                                         const int   theToIndex) const;

  inline int FirstLocationInSet(const TCollection_AsciiString& theSet,
                                const int                      theFromIndex,
                                const int                      theToIndex) const;

#if Standard_CPP17_OR_HIGHER

  inline int FirstLocationInSet(const std::string_view& theSet,
                                const int               theFromIndex,
                                const int               theToIndex) const;
#endif

  template <std::size_t N>
  inline int FirstLocationInSet(const char (&theLiteral)[N],
                                const int theFromIndex,
                                const int theToIndex) const;

  Standard_EXPORT int FirstLocationNotInSet(const char* theSet,
                                            const int   theSetLength,
                                            const int   theFromIndex,
                                            const int   theToIndex) const;

  inline int FirstLocationNotInSet(const TCollection_AsciiString& theSet,
                                   const int                      theFromIndex,
                                   const int                      theToIndex) const;

#if Standard_CPP17_OR_HIGHER

  inline int FirstLocationNotInSet(const std::string_view& theSet,
                                   const int               theFromIndex,
                                   const int               theToIndex) const;
#endif

  template <std::size_t N>
  inline int FirstLocationNotInSet(const char (&theLiteral)[N],
                                   const int theFromIndex,
                                   const int theToIndex) const;

  Standard_EXPORT void Insert(const int theWhere, const char theWhat);

  Standard_EXPORT void Insert(const int theWhere, const char* theString, const int theLength);

  inline void Insert(const int theWhere, const TCollection_AsciiString& theWhat);

  inline void Insert(const int theWhere, const char* theCString);

#if Standard_CPP17_OR_HIGHER

  inline void Insert(const int theWhere, const std::string_view& theStringView);
#endif

  template <std::size_t N>
  inline void Insert(const int theWhere, const char (&theLiteral)[N]);

  Standard_EXPORT void InsertAfter(const int theIndex, const char* theString, const int theLength);

  inline void InsertAfter(const int theIndex, const TCollection_AsciiString& theOther);

  inline void InsertAfter(const int theIndex, const char* theCString);

#if Standard_CPP17_OR_HIGHER

  inline void InsertAfter(const int theIndex, const std::string_view& theStringView);
#endif

  template <std::size_t N>
  inline void InsertAfter(const int theIndex, const char (&theLiteral)[N]);

  Standard_EXPORT void InsertBefore(const int theIndex, const char* theString, const int theLength);

  inline void InsertBefore(const int theIndex, const TCollection_AsciiString& theOther);

  inline void InsertBefore(const int theIndex, const char* theCString);

#if Standard_CPP17_OR_HIGHER

  inline void InsertBefore(const int theIndex, const std::string_view& theStringView);
#endif

  template <std::size_t N>
  inline void InsertBefore(const int theIndex, const char (&theLiteral)[N]);

  bool IsEmpty() const { return myLength == 0; }

  inline bool IsEqual(const TCollection_AsciiString& theOther) const;

  inline bool operator==(const TCollection_AsciiString& theOther) const;

  Standard_EXPORT bool IsEqual(const char* theString, const int theLength) const;

  inline bool IsEqual(const char* theCString) const;

  inline bool operator==(const char* theCString) const;

#if Standard_CPP17_OR_HIGHER

  inline bool IsEqual(const std::string_view& theStringView) const;

  inline bool operator==(const std::string_view& theStringView) const;
#endif

  template <std::size_t N>
  inline bool IsEqual(const char (&theLiteral)[N]) const;

  template <std::size_t N>
  inline bool operator==(const char (&theLiteral)[N]) const;

  inline bool IsDifferent(const TCollection_AsciiString& theOther) const;

  inline bool operator!=(const TCollection_AsciiString& theOther) const;

  inline bool IsDifferent(const char* theString, const int theLength) const;

  inline bool IsDifferent(const char* theCString) const;

  inline bool operator!=(const char* theCString) const;

#if Standard_CPP17_OR_HIGHER

  inline bool IsDifferent(const std::string_view& theStringView) const;

  inline bool operator!=(const std::string_view& theStringView) const;
#endif

  template <std::size_t N>
  inline bool IsDifferent(const char (&theLiteral)[N]) const;

  template <std::size_t N>
  inline bool operator!=(const char (&theLiteral)[N]) const;

  Standard_EXPORT bool IsLess(const char* theString, const int theLength) const;

  inline bool IsLess(const TCollection_AsciiString& theOther) const;

  inline bool operator<(const TCollection_AsciiString& theOther) const;

  inline bool IsLess(const char* theCString) const;

  bool operator<(const char* theCString) const { return IsLess(theCString); }

#if Standard_CPP17_OR_HIGHER

  inline bool IsLess(const std::string_view& theStringView) const;

  inline bool operator<(const std::string_view& theStringView) const;
#endif

  template <std::size_t N>
  inline bool IsLess(const char (&theLiteral)[N]) const;

  template <std::size_t N>
  inline bool operator<(const char (&theLiteral)[N]) const;

  Standard_EXPORT bool IsGreater(const char* theString, const int theLength) const;

  inline bool IsGreater(const TCollection_AsciiString& theOther) const;

  inline bool operator>(const TCollection_AsciiString& theOther) const;

  inline bool IsGreater(const char* theCString) const;

  inline bool operator>(const char* theCString) const;

#if Standard_CPP17_OR_HIGHER

  inline bool IsGreater(const std::string_view& theStringView) const;

  inline bool operator>(const std::string_view& theStringView) const;
#endif

  template <std::size_t N>
  inline bool IsGreater(const char (&theLiteral)[N]) const;

  template <std::size_t N>
  inline bool operator>(const char (&theLiteral)[N]) const;

  Standard_EXPORT bool StartsWith(const char* theStartString, const int theStartLength) const;

  inline bool StartsWith(const TCollection_AsciiString& theStartString) const;

  inline bool StartsWith(const char* theCString) const;

#if Standard_CPP17_OR_HIGHER

  inline bool StartsWith(const std::string_view& theStartString) const;
#endif

  Standard_EXPORT bool EndsWith(const char* theEndString, const int theEndLength) const;

  inline bool EndsWith(const TCollection_AsciiString& theEndString) const;

#if Standard_CPP17_OR_HIGHER

  inline bool EndsWith(const std::string_view& theEndString) const;
#endif

  template <std::size_t N>
  inline bool StartsWith(const char (&theLiteral)[N]) const;

  template <std::size_t N>
  inline bool EndsWith(const char (&theLiteral)[N]) const;

  Standard_EXPORT int IntegerValue() const;

  Standard_EXPORT bool IsIntegerValue() const;

  Standard_EXPORT bool IsRealValue(bool theToCheckFull = false) const;

  Standard_EXPORT bool IsAscii() const;

  Standard_EXPORT void LeftAdjust();

  Standard_EXPORT void LeftJustify(const int theWidth, const char theFiller);

  int Length() const { return myLength; }

  Standard_EXPORT int Location(const TCollection_AsciiString& theOther,
                               const int                      theFromIndex,
                               const int                      theToIndex) const;

  Standard_EXPORT int Location(const int  theN,
                               const char theC,
                               const int  theFromIndex,
                               const int  theToIndex) const;

  Standard_EXPORT void LowerCase();

  Standard_EXPORT void Prepend(const TCollection_AsciiString& theOther);

  Standard_EXPORT void                     Print(Standard_OStream& theStream) const;
  friend Standard_EXPORT Standard_OStream& operator<<(Standard_OStream&              theStream,
                                                      const TCollection_AsciiString& theString);

  Standard_EXPORT void                     Read(Standard_IStream& theStream);
  friend Standard_EXPORT Standard_IStream& operator>>(Standard_IStream&        theStream,
                                                      TCollection_AsciiString& theString);

  Standard_EXPORT double RealValue() const;

  Standard_EXPORT void RemoveAll(const char theC, const bool theCaseSensitive);

  Standard_EXPORT void RemoveAll(const char theWhat);

  Standard_EXPORT void Remove(const int theWhere, const int theHowMany = 1);

  Standard_EXPORT void RightAdjust();

  Standard_EXPORT void RightJustify(const int theWidth, const char theFiller);

  Standard_EXPORT int Search(const char* theWhat, const int theWhatLength) const;

  inline int Search(const TCollection_AsciiString& theWhat) const;

  inline int Search(const char* theCString) const;

#if Standard_CPP17_OR_HIGHER

  inline int Search(const std::string_view& theWhat) const;
#endif

  template <std::size_t N>
  inline int Search(const char (&theLiteral)[N]) const;

  Standard_EXPORT int SearchFromEnd(const char* theWhat, const int theWhatLength) const;

  inline int SearchFromEnd(const TCollection_AsciiString& theWhat) const;

  inline int SearchFromEnd(const char* theCString) const;

#if Standard_CPP17_OR_HIGHER

  inline int SearchFromEnd(const std::string_view& theWhat) const;
#endif

  template <std::size_t N>
  inline int SearchFromEnd(const char (&theLiteral)[N]) const;

  Standard_EXPORT void SetValue(const int theWhere, const char theWhat);

  Standard_EXPORT void SetValue(const int theWhere, const char* theString, const int theLength);

  inline void SetValue(const int theWhere, const TCollection_AsciiString& theWhat);

  inline void SetValue(const int theWhere, const char* theCString);

#if Standard_CPP17_OR_HIGHER

  inline void SetValue(const int theWhere, const std::string_view& theStringView);
#endif

  Standard_EXPORT TCollection_AsciiString Split(const int theWhere);

  Standard_EXPORT TCollection_AsciiString SubString(const int theFromIndex,
                                                    const int theToIndex) const;

  const char* ToCString() const { return myString; }

#if Standard_CPP17_OR_HIGHER

  explicit operator std::string_view() const { return std::string_view(myString, myLength); }
#endif

  Standard_EXPORT TCollection_AsciiString Token(const char* theSeparators = " \t",
                                                const int   theWhichOne   = 1) const;

  Standard_EXPORT void Trunc(const int theHowMany);

  Standard_EXPORT void UpperCase();

  Standard_EXPORT int UsefullLength() const;

  Standard_EXPORT char Value(const int theWhere) const;

  inline size_t HashCode() const;

  Standard_EXPORT static const TCollection_AsciiString& EmptyString() noexcept;

  inline static bool IsEqual(const TCollection_AsciiString& string1,
                             const TCollection_AsciiString& string2);

  static bool IsEqual(const TCollection_AsciiString& string1, const char* string2);

#if Standard_CPP17_OR_HIGHER

  inline static bool IsEqual(const TCollection_AsciiString& theString1,
                             const std::string_view&        theStringView);

  inline static bool IsEqual(const std::string_view&        theStringView,
                             const TCollection_AsciiString& theString2);
#endif

  Standard_EXPORT static bool IsSameString(const char* theString1,
                                           const int   theLength1,
                                           const char* theString2,
                                           const int   theLength2,
                                           const bool  theIsCaseSensitive);

  inline static bool IsSameString(const TCollection_AsciiString& theString1,
                                  const TCollection_AsciiString& theString2,
                                  const bool                     theIsCaseSensitive);

  inline static bool IsSameString(const TCollection_AsciiString& theString1,
                                  const char*                    theCString,
                                  const bool                     theIsCaseSensitive);

  inline static bool IsSameString(const char*                    theCString,
                                  const TCollection_AsciiString& theString2,
                                  const bool                     theIsCaseSensitive);

#if Standard_CPP17_OR_HIGHER

  inline static bool IsSameString(const TCollection_AsciiString& theString1,
                                  const std::string_view&        theStringView,
                                  const bool                     theIsCaseSensitive);

  inline static bool IsSameString(const std::string_view&        theStringView,
                                  const TCollection_AsciiString& theString2,
                                  const bool                     theIsCaseSensitive);
#endif

  inline static bool IsSameString(const char* theCString1,
                                  const char* theCString2,
                                  const bool  theIsCaseSensitive);

#if Standard_CPP17_OR_HIGHER

  inline static bool IsSameString(const std::string_view& theStringView1,
                                  const std::string_view& theStringView2,
                                  const bool              theIsCaseSensitive);
#endif

private:
  void allocate(const int theLength);

  void reallocate(const int theLength);

  void deallocate();

private:
  Standard_PCharacter myString{};
  int                 myLength{};
};

#include <TCollection_AsciiString.hpp>

inline bool IsEqual(const TCollection_AsciiString& theString1,
                    const TCollection_AsciiString& theString2)
{
  return TCollection_AsciiString::IsEqual(theString1, theString2);
}

namespace std
{
  template <>
  struct hash<TCollection_AsciiString>
  {
    size_t operator()(const TCollection_AsciiString& theString) const
    {
      return theString.HashCode();
    }
  };
} // namespace std

inline void TCollection_AsciiString::AssignCat(const TCollection_AsciiString& theOther)
{
  AssignCat(theOther.ToCString(), theOther.Length());
}

inline void TCollection_AsciiString::AssignCat(const char* theCString)
{
  if (theCString)
  {
    AssignCat(theCString, static_cast<int>(strlen(theCString)));
  }
}

#if Standard_CPP17_OR_HIGHER
inline void TCollection_AsciiString::AssignCat(const std::string_view& theStringView)
{
  if (!theStringView.empty())
  {
    AssignCat(theStringView.data(), static_cast<int>(theStringView.size()));
  }
}
#endif

template <std::size_t N>
inline void TCollection_AsciiString::AssignCat(const char (&theLiteral)[N])
{
  AssignCat(theLiteral, static_cast<int>(strlen(theLiteral)));
}

inline TCollection_AsciiString TCollection_AsciiString::Cat(
  const TCollection_AsciiString& theOther) const
{
  return Cat(theOther.ToCString(), theOther.Length());
}

inline TCollection_AsciiString TCollection_AsciiString::Cat(const char* theCString) const
{
  return theCString ? Cat(theCString, static_cast<int>(strlen(theCString)))
                    : TCollection_AsciiString(*this);
}

#if Standard_CPP17_OR_HIGHER
inline TCollection_AsciiString TCollection_AsciiString::Cat(
  const std::string_view& theStringView) const
{
  return Cat(theStringView.data(), static_cast<int>(theStringView.size()));
}
#endif

template <std::size_t N>
inline TCollection_AsciiString TCollection_AsciiString::Cat(const char (&theLiteral)[N]) const
{
  return Cat(theLiteral, static_cast<int>(strlen(theLiteral)));
}

inline void TCollection_AsciiString::Copy(const char* theCString)
{
  Copy(theCString, theCString ? static_cast<int>(strlen(theCString)) : 0);
}

#if Standard_CPP17_OR_HIGHER
inline void TCollection_AsciiString::Copy(const std::string_view& theStringView)
{
  Copy(theStringView.data(), static_cast<int>(theStringView.size()));
}
#endif

template <std::size_t N>
inline void TCollection_AsciiString::Copy(const char (&theLiteral)[N])
{
  Copy(theLiteral, static_cast<int>(strlen(theLiteral)));
}

inline void TCollection_AsciiString::Copy(const TCollection_AsciiString& theFromWhere)
{
  if (&theFromWhere != this)
  {
    Copy(theFromWhere.ToCString(), theFromWhere.Length());
  }
}

inline void TCollection_AsciiString::Insert(const int                      theWhere,
                                            const TCollection_AsciiString& theWhat)
{
  Insert(theWhere, theWhat.ToCString(), theWhat.Length());
}

inline void TCollection_AsciiString::Insert(const int theWhere, const char* theCString)
{
  if (theCString)
  {
    Insert(theWhere, theCString, static_cast<int>(strlen(theCString)));
  }
}

#if Standard_CPP17_OR_HIGHER
inline void TCollection_AsciiString::Insert(const int               theWhere,
                                            const std::string_view& theStringView)
{
  Insert(theWhere, theStringView.data(), static_cast<int>(theStringView.size()));
}
#endif

template <std::size_t N>
inline void TCollection_AsciiString::Insert(const int theWhere, const char (&theLiteral)[N])
{
  Insert(theWhere, theLiteral, static_cast<int>(strlen(theLiteral)));
}

inline void TCollection_AsciiString::InsertAfter(const int                      theIndex,
                                                 const TCollection_AsciiString& theOther)
{
  InsertAfter(theIndex, theOther.ToCString(), theOther.Length());
}

inline void TCollection_AsciiString::InsertAfter(const int theIndex, const char* theCString)
{
  if (theCString)
    InsertAfter(theIndex, theCString, static_cast<int>(strlen(theCString)));
}

#if Standard_CPP17_OR_HIGHER
inline void TCollection_AsciiString::InsertAfter(const int               theIndex,
                                                 const std::string_view& theStringView)
{
  InsertAfter(theIndex, theStringView.data(), static_cast<int>(theStringView.size()));
}
#endif

template <std::size_t N>
inline void TCollection_AsciiString::InsertAfter(const int theIndex, const char (&theLiteral)[N])
{
  InsertAfter(theIndex, theLiteral, static_cast<int>(strlen(theLiteral)));
}

inline void TCollection_AsciiString::InsertBefore(const int                      theIndex,
                                                  const TCollection_AsciiString& theOther)
{
  InsertBefore(theIndex, theOther.ToCString(), theOther.Length());
}

inline void TCollection_AsciiString::InsertBefore(const int theIndex, const char* theCString)
{
  if (theCString)
    InsertBefore(theIndex, theCString, static_cast<int>(strlen(theCString)));
}

#if Standard_CPP17_OR_HIGHER
inline void TCollection_AsciiString::InsertBefore(const int               theIndex,
                                                  const std::string_view& theStringView)
{
  InsertBefore(theIndex, theStringView.data(), static_cast<int>(theStringView.size()));
}
#endif

template <std::size_t N>
inline void TCollection_AsciiString::InsertBefore(const int theIndex, const char (&theLiteral)[N])
{
  InsertBefore(theIndex, theLiteral, static_cast<int>(strlen(theLiteral)));
}

inline bool TCollection_AsciiString::IsEqual(const TCollection_AsciiString& theOther) const
{
  return IsEqual(theOther.myString, theOther.myLength);
}

inline bool TCollection_AsciiString::IsEqual(const char* theCString) const
{
  return theCString ? IsEqual(theCString, static_cast<int>(strlen(theCString))) : (myLength == 0);
}

#if Standard_CPP17_OR_HIGHER
inline bool TCollection_AsciiString::IsEqual(const std::string_view& theStringView) const
{
  return IsEqual(theStringView.data(), static_cast<int>(theStringView.size()));
}
#endif

template <std::size_t N>
inline bool TCollection_AsciiString::IsEqual(const char (&theLiteral)[N]) const
{
  return IsEqual(theLiteral, static_cast<int>(strlen(theLiteral)));
}

inline bool TCollection_AsciiString::IsDifferent(const TCollection_AsciiString& theOther) const
{
  return IsDifferent(theOther.myString, theOther.myLength);
}

inline bool TCollection_AsciiString::IsDifferent(const char* theCString) const
{
  return !IsEqual(theCString);
}

#if Standard_CPP17_OR_HIGHER
inline bool TCollection_AsciiString::IsDifferent(const std::string_view& theStringView) const
{
  return !IsEqual(theStringView);
}
#endif

template <std::size_t N>
inline bool TCollection_AsciiString::IsDifferent(const char (&theLiteral)[N]) const
{
  return !IsEqual(theLiteral);
}

inline bool TCollection_AsciiString::IsLess(const TCollection_AsciiString& theOther) const
{
  return IsLess(theOther.ToCString(), theOther.Length());
}

inline bool TCollection_AsciiString::IsLess(const char* theCString) const
{
  return theCString ? IsLess(theCString, static_cast<int>(strlen(theCString))) : false;
}

#if Standard_CPP17_OR_HIGHER
inline bool TCollection_AsciiString::IsLess(const std::string_view& theStringView) const
{
  return IsLess(theStringView.data(), static_cast<int>(theStringView.size()));
}
#endif

template <std::size_t N>
inline bool TCollection_AsciiString::IsLess(const char (&theLiteral)[N]) const
{
  return IsLess(theLiteral, static_cast<int>(strlen(theLiteral)));
}

inline bool TCollection_AsciiString::IsGreater(const TCollection_AsciiString& theOther) const
{
  return IsGreater(theOther.ToCString(), theOther.Length());
}

inline bool TCollection_AsciiString::IsGreater(const char* theCString) const
{
  return theCString ? IsGreater(theCString, static_cast<int>(strlen(theCString))) : (myLength > 0);
}

#if Standard_CPP17_OR_HIGHER
inline bool TCollection_AsciiString::IsGreater(const std::string_view& theStringView) const
{
  return IsGreater(theStringView.data(), static_cast<int>(theStringView.size()));
}
#endif

template <std::size_t N>
inline bool TCollection_AsciiString::IsGreater(const char (&theLiteral)[N]) const
{
  return IsGreater(theLiteral, static_cast<int>(strlen(theLiteral)));
}

inline bool TCollection_AsciiString::StartsWith(const TCollection_AsciiString& theStartString) const
{
  return StartsWith(theStartString.ToCString(), theStartString.Length());
}

inline bool TCollection_AsciiString::StartsWith(const char* theCString) const
{
  return theCString ? StartsWith(theCString, static_cast<int>(strlen(theCString)))
                    : (myLength == 0);
}

#if Standard_CPP17_OR_HIGHER
inline bool TCollection_AsciiString::StartsWith(const std::string_view& theStartString) const
{
  return StartsWith(theStartString.data(), static_cast<int>(theStartString.size()));
}
#endif

inline bool TCollection_AsciiString::EndsWith(const TCollection_AsciiString& theEndString) const
{
  return EndsWith(theEndString.ToCString(), theEndString.Length());
}

#if Standard_CPP17_OR_HIGHER
inline bool TCollection_AsciiString::EndsWith(const std::string_view& theEndString) const
{
  return EndsWith(theEndString.data(), static_cast<int>(theEndString.size()));
}
#endif

template <std::size_t N>
inline bool TCollection_AsciiString::StartsWith(const char (&theLiteral)[N]) const
{
  return StartsWith(theLiteral, static_cast<int>(strlen(theLiteral)));
}

template <std::size_t N>
inline bool TCollection_AsciiString::EndsWith(const char (&theLiteral)[N]) const
{
  return EndsWith(theLiteral, static_cast<int>(strlen(theLiteral)));
}

inline int TCollection_AsciiString::Search(const TCollection_AsciiString& theWhat) const
{
  return Search(theWhat.ToCString(), theWhat.Length());
}

inline int TCollection_AsciiString::Search(const char* theCString) const
{
  return theCString ? Search(theCString, static_cast<int>(strlen(theCString))) : -1;
}

#if Standard_CPP17_OR_HIGHER
inline int TCollection_AsciiString::Search(const std::string_view& theWhat) const
{
  return Search(theWhat.data(), static_cast<int>(theWhat.size()));
}
#endif

template <std::size_t N>
inline int TCollection_AsciiString::Search(const char (&theLiteral)[N]) const
{
  return Search(theLiteral, static_cast<int>(strlen(theLiteral)));
}

inline int TCollection_AsciiString::SearchFromEnd(const TCollection_AsciiString& theWhat) const
{
  return SearchFromEnd(theWhat.ToCString(), theWhat.Length());
}

inline int TCollection_AsciiString::SearchFromEnd(const char* theCString) const
{
  return theCString ? SearchFromEnd(theCString, static_cast<int>(strlen(theCString))) : -1;
}

#if Standard_CPP17_OR_HIGHER
inline int TCollection_AsciiString::SearchFromEnd(const std::string_view& theWhat) const
{
  return SearchFromEnd(theWhat.data(), static_cast<int>(theWhat.size()));
}
#endif

template <std::size_t N>
inline int TCollection_AsciiString::SearchFromEnd(const char (&theLiteral)[N]) const
{
  return SearchFromEnd(theLiteral, static_cast<int>(strlen(theLiteral)));
}

inline void TCollection_AsciiString::SetValue(const int                      theWhere,
                                              const TCollection_AsciiString& theWhat)
{
  SetValue(theWhere, theWhat.ToCString(), theWhat.Length());
}

inline void TCollection_AsciiString::SetValue(const int theWhere, const char* theCString)
{
  if (theCString)
  {
    SetValue(theWhere, theCString, static_cast<int>(strlen(theCString)));
  }
  else
  {
    SetValue(theWhere, "", 0);
  }
}

#if Standard_CPP17_OR_HIGHER
inline void TCollection_AsciiString::SetValue(const int               theWhere,
                                              const std::string_view& theStringView)
{
  SetValue(theWhere, theStringView.data(), static_cast<int>(theStringView.size()));
}
#endif

inline size_t TCollection_AsciiString::HashCode() const
{
  if (myLength < 4)
  {
    return opencascade::FNVHash::hash_combine(*myString, myLength);
  }
  return opencascade::hashBytes(myString, myLength);
}

inline bool TCollection_AsciiString::IsEqual(const TCollection_AsciiString& string1,
                                             const TCollection_AsciiString& string2)
{
  return string1.IsEqual(string2);
}

#if Standard_CPP17_OR_HIGHER
inline bool TCollection_AsciiString::IsEqual(const TCollection_AsciiString& theString1,
                                             const std::string_view&        theStringView)
{
  return theString1.IsEqual(theStringView);
}
#endif

#if Standard_CPP17_OR_HIGHER
inline bool TCollection_AsciiString::IsEqual(const std::string_view&        theStringView,
                                             const TCollection_AsciiString& theString2)
{
  return theString2.IsEqual(theStringView);
}
#endif

inline bool TCollection_AsciiString::IsSameString(const TCollection_AsciiString& theString1,
                                                  const TCollection_AsciiString& theString2,
                                                  const bool                     theIsCaseSensitive)
{
  return IsSameString(theString1.ToCString(),
                      theString1.Length(),
                      theString2.ToCString(),
                      theString2.Length(),
                      theIsCaseSensitive);
}

inline bool TCollection_AsciiString::IsSameString(const TCollection_AsciiString& theString1,
                                                  const char*                    theCString,
                                                  const bool                     theIsCaseSensitive)
{
  if (!theCString)
    return theString1.Length() == 0;

  return IsSameString(theString1.ToCString(),
                      theString1.Length(),
                      theCString,
                      static_cast<int>(strlen(theCString)),
                      theIsCaseSensitive);
}

inline bool TCollection_AsciiString::IsSameString(const char*                    theCString,
                                                  const TCollection_AsciiString& theString2,
                                                  const bool                     theIsCaseSensitive)
{
  return IsSameString(theString2, theCString, theIsCaseSensitive);
}

#if Standard_CPP17_OR_HIGHER
inline bool TCollection_AsciiString::IsSameString(const TCollection_AsciiString& theString1,
                                                  const std::string_view&        theStringView,
                                                  const bool                     theIsCaseSensitive)
{
  return IsSameString(theString1.ToCString(),
                      theString1.Length(),
                      theStringView.data(),
                      static_cast<int>(theStringView.size()),
                      theIsCaseSensitive);
}
#endif

#if Standard_CPP17_OR_HIGHER
inline bool TCollection_AsciiString::IsSameString(const std::string_view&        theStringView,
                                                  const TCollection_AsciiString& theString2,
                                                  const bool                     theIsCaseSensitive)
{

  return IsSameString(theString2, theStringView, theIsCaseSensitive);
}
#endif

inline bool TCollection_AsciiString::IsSameString(const char* theCString1,
                                                  const char* theCString2,
                                                  const bool  theIsCaseSensitive)
{
  if (!theCString1 && !theCString2)
    return true;
  if (!theCString1 || !theCString2)
    return false;

  return IsSameString(theCString1,
                      static_cast<int>(strlen(theCString1)),
                      theCString2,
                      static_cast<int>(strlen(theCString2)),
                      theIsCaseSensitive);
}

#if Standard_CPP17_OR_HIGHER
inline bool TCollection_AsciiString::IsSameString(const std::string_view& theStringView1,
                                                  const std::string_view& theStringView2,
                                                  const bool              theIsCaseSensitive)
{
  return IsSameString(theStringView1.data(),
                      static_cast<int>(theStringView1.size()),
                      theStringView2.data(),
                      static_cast<int>(theStringView2.size()),
                      theIsCaseSensitive);
}
#endif

template <std::size_t N>
inline void TCollection_AsciiString::operator+=(const char (&theLiteral)[N])
{
  AssignCat(theLiteral);
}

template <std::size_t N>
inline TCollection_AsciiString TCollection_AsciiString::operator+(const char (&theLiteral)[N]) const
{
  return Cat(theLiteral);
}

template <std::size_t N>
inline void TCollection_AsciiString::operator=(const char (&theLiteral)[N])
{
  Copy(theLiteral);
}

template <std::size_t N>
inline bool TCollection_AsciiString::operator==(const char (&theLiteral)[N]) const
{
  return IsEqual(theLiteral);
}

template <std::size_t N>
inline bool TCollection_AsciiString::operator!=(const char (&theLiteral)[N]) const
{
  return IsDifferent(theLiteral);
}

template <std::size_t N>
inline bool TCollection_AsciiString::operator<(const char (&theLiteral)[N]) const
{
  return IsLess(theLiteral);
}

template <std::size_t N>
inline bool TCollection_AsciiString::operator>(const char (&theLiteral)[N]) const
{
  return IsGreater(theLiteral);
}

inline TCollection_AsciiString TCollection_AsciiString::operator+(const char theOther) const
{
  return Cat(theOther);
}

inline int TCollection_AsciiString::FirstLocationInSet(const TCollection_AsciiString& theSet,
                                                       const int                      theFromIndex,
                                                       const int theToIndex) const
{
  return FirstLocationInSet(theSet.ToCString(), theSet.Length(), theFromIndex, theToIndex);
}

#if Standard_CPP17_OR_HIGHER
inline int TCollection_AsciiString::FirstLocationInSet(const std::string_view& theSet,
                                                       const int               theFromIndex,
                                                       const int               theToIndex) const
{
  return FirstLocationInSet(theSet.data(),
                            static_cast<int>(theSet.size()),
                            theFromIndex,
                            theToIndex);
}
#endif

template <std::size_t N>
inline int TCollection_AsciiString::FirstLocationInSet(const char (&theLiteral)[N],
                                                       const int theFromIndex,
                                                       const int theToIndex) const
{
  return FirstLocationInSet(theLiteral, static_cast<int>(N - 1), theFromIndex, theToIndex);
}

inline int TCollection_AsciiString::FirstLocationNotInSet(const TCollection_AsciiString& theSet,
                                                          const int theFromIndex,
                                                          const int theToIndex) const
{
  return FirstLocationNotInSet(theSet.ToCString(), theSet.Length(), theFromIndex, theToIndex);
}

#if Standard_CPP17_OR_HIGHER
inline int TCollection_AsciiString::FirstLocationNotInSet(const std::string_view& theSet,
                                                          const int               theFromIndex,
                                                          const int               theToIndex) const
{
  return FirstLocationNotInSet(theSet.data(),
                               static_cast<int>(theSet.size()),
                               theFromIndex,
                               theToIndex);
}
#endif

template <std::size_t N>
inline int TCollection_AsciiString::FirstLocationNotInSet(const char (&theLiteral)[N],
                                                          const int theFromIndex,
                                                          const int theToIndex) const
{
  return FirstLocationNotInSet(theLiteral, static_cast<int>(N - 1), theFromIndex, theToIndex);
}

inline bool TCollection_AsciiString::IsDifferent(const char* theString, const int theLength) const
{
  return !IsEqual(theString, theLength);
}

inline TCollection_AsciiString TCollection_AsciiString::operator+(
  const TCollection_AsciiString& theOther) const
{
  return Cat(theOther);
}

inline TCollection_AsciiString TCollection_AsciiString::operator+(const char* theCString) const
{
  return Cat(theCString);
}

#if Standard_CPP17_OR_HIGHER
inline TCollection_AsciiString TCollection_AsciiString::operator+(
  const std::string_view& theStringView) const
{
  return Cat(theStringView);
}
#endif

inline TCollection_AsciiString& TCollection_AsciiString::operator=(
  const TCollection_AsciiString& theOther)
{
  Copy(theOther);
  return *this;
}

inline TCollection_AsciiString& TCollection_AsciiString::operator=(
  TCollection_AsciiString&& theOther) noexcept
{
  Move(std::forward<TCollection_AsciiString>(theOther));
  return *this;
}

inline bool TCollection_AsciiString::operator==(const TCollection_AsciiString& theOther) const
{
  return IsEqual(theOther);
}

inline bool TCollection_AsciiString::operator==(const char* theCString) const
{
  return IsEqual(theCString);
}

#if Standard_CPP17_OR_HIGHER
inline bool TCollection_AsciiString::operator==(const std::string_view& theStringView) const
{
  return IsEqual(theStringView);
}
#endif

inline bool TCollection_AsciiString::operator!=(const TCollection_AsciiString& theOther) const
{
  return IsDifferent(theOther);
}

inline bool TCollection_AsciiString::operator!=(const char* theCString) const
{
  return IsDifferent(theCString);
}

#if Standard_CPP17_OR_HIGHER
inline bool TCollection_AsciiString::operator!=(const std::string_view& theStringView) const
{
  return IsDifferent(theStringView);
}
#endif

inline bool TCollection_AsciiString::operator<(const TCollection_AsciiString& theOther) const
{
  return IsLess(theOther);
}

#if Standard_CPP17_OR_HIGHER
inline bool TCollection_AsciiString::operator<(const std::string_view& theStringView) const
{
  return IsLess(theStringView);
}
#endif

inline bool TCollection_AsciiString::operator>(const TCollection_AsciiString& theOther) const
{
  return IsGreater(theOther);
}

inline bool TCollection_AsciiString::operator>(const char* theCString) const
{
  return IsGreater(theCString);
}

#if Standard_CPP17_OR_HIGHER
inline bool TCollection_AsciiString::operator>(const std::string_view& theStringView) const
{
  return IsGreater(theStringView);
}
#endif

#if Standard_CPP17_OR_HIGHER
inline TCollection_AsciiString::TCollection_AsciiString(const std::string_view& theStringView)
    : TCollection_AsciiString(theStringView.data(), static_cast<int>(theStringView.size()))
{
}
#endif

inline TCollection_AsciiString::TCollection_AsciiString(const char* theMessage)
    : TCollection_AsciiString(theMessage, theMessage ? static_cast<int>(strlen(theMessage)) : 0)
{
}

template <std::size_t N>
inline TCollection_AsciiString::TCollection_AsciiString(const char (&theLiteral)[N])
    : TCollection_AsciiString(theLiteral, static_cast<int>(strlen(theLiteral)))
{
}
