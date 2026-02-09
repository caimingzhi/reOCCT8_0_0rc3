#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TCollection_AsciiString.hpp>
#include <Standard_Transient.hpp>
#include <Standard_CString.hpp>
#include <Standard_Integer.hpp>
#include <Standard_OStream.hpp>
class TCollection_HExtendedString;

class TCollection_HAsciiString : public Standard_Transient
{

public:
  Standard_EXPORT TCollection_HAsciiString();

  Standard_EXPORT TCollection_HAsciiString(const char* message);

  Standard_EXPORT TCollection_HAsciiString(const char aChar);

  Standard_EXPORT TCollection_HAsciiString(const int length, const char filler);

  Standard_EXPORT TCollection_HAsciiString(const int value);

  Standard_EXPORT TCollection_HAsciiString(const double value);

  Standard_EXPORT TCollection_HAsciiString(const TCollection_AsciiString& aString);

  TCollection_HAsciiString(TCollection_AsciiString&& theString) noexcept
      : myString(std::move(theString))
  {
  }

  Standard_EXPORT TCollection_HAsciiString(const occ::handle<TCollection_HAsciiString>& aString);

  Standard_EXPORT TCollection_HAsciiString(const occ::handle<TCollection_HExtendedString>& aString,
                                           const char replaceNonAscii);

  void AssignCat(const char* other);

  void AssignCat(const occ::handle<TCollection_HAsciiString>& other);

  Standard_EXPORT void Capitalize();

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Cat(const char* other) const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Cat(
    const occ::handle<TCollection_HAsciiString>& other) const;

  Standard_EXPORT void Center(const int Width, const char Filler);

  Standard_EXPORT void ChangeAll(const char aChar,
                                 const char NewChar,
                                 const bool CaseSensitive = true);

  Standard_EXPORT void Clear();

  Standard_EXPORT int FirstLocationInSet(const occ::handle<TCollection_HAsciiString>& Set,
                                         const int                                    FromIndex,
                                         const int ToIndex) const;

  Standard_EXPORT int FirstLocationNotInSet(const occ::handle<TCollection_HAsciiString>& Set,
                                            const int                                    FromIndex,
                                            const int ToIndex) const;

  Standard_EXPORT void Insert(const int where, const char what);

  Standard_EXPORT void Insert(const int where, const char* what);

  Standard_EXPORT void Insert(const int where, const occ::handle<TCollection_HAsciiString>& what);

  Standard_EXPORT void InsertAfter(const int                                    Index,
                                   const occ::handle<TCollection_HAsciiString>& other);

  Standard_EXPORT void InsertBefore(const int                                    Index,
                                    const occ::handle<TCollection_HAsciiString>& other);

  Standard_EXPORT bool IsEmpty() const;

  Standard_EXPORT bool IsLess(const occ::handle<TCollection_HAsciiString>& other) const;

  Standard_EXPORT bool IsGreater(const occ::handle<TCollection_HAsciiString>& other) const;

  Standard_EXPORT int IntegerValue() const;

  Standard_EXPORT bool IsIntegerValue() const;

  Standard_EXPORT bool IsRealValue() const;

  Standard_EXPORT bool IsAscii() const;

  Standard_EXPORT bool IsDifferent(const occ::handle<TCollection_HAsciiString>& S) const;

  Standard_EXPORT bool IsSameString(const occ::handle<TCollection_HAsciiString>& S) const;

  Standard_EXPORT bool IsSameString(const occ::handle<TCollection_HAsciiString>& S,
                                    const bool CaseSensitive) const;

  Standard_EXPORT void LeftAdjust();

  Standard_EXPORT void LeftJustify(const int Width, const char Filler);

  int Length() const;

  Standard_EXPORT int Location(const occ::handle<TCollection_HAsciiString>& other,
                               const int                                    FromIndex,
                               const int                                    ToIndex) const;

  Standard_EXPORT int Location(const int  N,
                               const char C,
                               const int  FromIndex,
                               const int  ToIndex) const;

  Standard_EXPORT void LowerCase();

  Standard_EXPORT void Prepend(const occ::handle<TCollection_HAsciiString>& other);

  Standard_EXPORT void Print(Standard_OStream& astream) const;

  Standard_EXPORT double RealValue() const;

  Standard_EXPORT void RemoveAll(const char C, const bool CaseSensitive);

  Standard_EXPORT void RemoveAll(const char what);

  Standard_EXPORT void Remove(const int where, const int ahowmany = 1);

  Standard_EXPORT void RightAdjust();

  Standard_EXPORT void RightJustify(const int Width, const char Filler);

  Standard_EXPORT int Search(const char* what) const;

  Standard_EXPORT int Search(const occ::handle<TCollection_HAsciiString>& what) const;

  Standard_EXPORT int SearchFromEnd(const char* what) const;

  Standard_EXPORT int SearchFromEnd(const occ::handle<TCollection_HAsciiString>& what) const;

  Standard_EXPORT void SetValue(const int where, const char what);

  Standard_EXPORT void SetValue(const int where, const char* what);

  Standard_EXPORT void SetValue(const int where, const occ::handle<TCollection_HAsciiString>& what);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Split(const int where);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> SubString(const int FromIndex,
                                                                  const int ToIndex) const;

  const char* ToCString() const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Token(const char* separators = " \t",
                                                              const int   whichone   = 1) const;

  Standard_EXPORT void Trunc(const int ahowmany);

  Standard_EXPORT void UpperCase();

  Standard_EXPORT int UsefullLength() const;

  Standard_EXPORT char Value(const int where) const;

  const TCollection_AsciiString& String() const;

  Standard_EXPORT bool IsSameState(const occ::handle<TCollection_HAsciiString>& other) const;

  DEFINE_STANDARD_RTTIEXT(TCollection_HAsciiString, Standard_Transient)

private:
  TCollection_AsciiString myString;
};

inline void TCollection_HAsciiString::AssignCat(const char* other)
{
  myString.AssignCat(other);
}

inline void TCollection_HAsciiString::AssignCat(const occ::handle<TCollection_HAsciiString>& other)
{
  myString.AssignCat(other->String());
}

inline int TCollection_HAsciiString::Length() const
{
  return myString.Length();
}

inline const TCollection_AsciiString& TCollection_HAsciiString::String() const
{
  return myString;
}

inline const char* TCollection_HAsciiString::ToCString() const
{
  return myString.ToCString();
}

namespace std
{
  template <>
  struct hash<occ::handle<TCollection_HAsciiString>>
  {
    size_t operator()(const occ::handle<TCollection_HAsciiString>& theString) const
    {
      if (theString.IsNull())
        return 0;
      return std::hash<TCollection_AsciiString>{}(theString->String());
    }
  };

  template <>
  struct equal_to<occ::handle<TCollection_HAsciiString>>
  {
    bool operator()(const occ::handle<TCollection_HAsciiString>& theString1,
                    const occ::handle<TCollection_HAsciiString>& theString2) const
    {
      return theString1 == theString2
             || (!theString1.IsNull() && !theString2.IsNull()
                 && theString1->String() == theString2->String());
    }
  };
} // namespace std
