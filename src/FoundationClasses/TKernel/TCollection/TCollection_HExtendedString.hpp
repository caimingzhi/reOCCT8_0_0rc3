#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TCollection_ExtendedString.hpp>
#include <Standard_Transient.hpp>
#include <Standard_CString.hpp>
#include <Standard_Integer.hpp>
#include <Standard_OStream.hpp>
class TCollection_HAsciiString;

class TCollection_HExtendedString : public Standard_Transient
{

public:
  Standard_EXPORT TCollection_HExtendedString();

  Standard_EXPORT TCollection_HExtendedString(const char* message);

  Standard_EXPORT TCollection_HExtendedString(const char16_t* message);

  Standard_EXPORT TCollection_HExtendedString(const char16_t aChar);

  Standard_EXPORT TCollection_HExtendedString(const int length, const char16_t filler);

  Standard_EXPORT TCollection_HExtendedString(const TCollection_ExtendedString& aString);

  TCollection_HExtendedString(TCollection_ExtendedString&& theString) noexcept
      : myString(std::move(theString))
  {
  }

  Standard_EXPORT TCollection_HExtendedString(const occ::handle<TCollection_HAsciiString>& aString);

  Standard_EXPORT TCollection_HExtendedString(
    const occ::handle<TCollection_HExtendedString>& aString);

  Standard_EXPORT void AssignCat(const occ::handle<TCollection_HExtendedString>& other);

  Standard_EXPORT occ::handle<TCollection_HExtendedString> Cat(
    const occ::handle<TCollection_HExtendedString>& other) const;

  Standard_EXPORT void ChangeAll(const char16_t aChar, const char16_t NewChar);

  Standard_EXPORT void Clear();

  Standard_EXPORT bool IsEmpty() const;

  Standard_EXPORT void Insert(const int where, const char16_t what);

  Standard_EXPORT void Insert(const int                                       where,
                              const occ::handle<TCollection_HExtendedString>& what);

  Standard_EXPORT bool IsLess(const occ::handle<TCollection_HExtendedString>& other) const;

  Standard_EXPORT bool IsGreater(const occ::handle<TCollection_HExtendedString>& other) const;

  Standard_EXPORT bool IsAscii() const;

  Standard_EXPORT int Length() const;

  Standard_EXPORT void Remove(const int where, const int ahowmany = 1);

  Standard_EXPORT void RemoveAll(const char16_t what);

  Standard_EXPORT void SetValue(const int where, const char16_t what);

  Standard_EXPORT void SetValue(const int                                       where,
                                const occ::handle<TCollection_HExtendedString>& what);

  Standard_EXPORT occ::handle<TCollection_HExtendedString> Split(const int where);

  Standard_EXPORT int Search(const occ::handle<TCollection_HExtendedString>& what) const;

  Standard_EXPORT int SearchFromEnd(const occ::handle<TCollection_HExtendedString>& what) const;

  const char16_t* ToExtString() const { return myString.ToExtString(); }

  Standard_EXPORT occ::handle<TCollection_HExtendedString> Token(const char16_t* separators,
                                                                 const int whichone = 1) const;

  Standard_EXPORT void Trunc(const int ahowmany);

  Standard_EXPORT char16_t Value(const int where) const;

  Standard_EXPORT const TCollection_ExtendedString& String() const;

  Standard_EXPORT void Print(Standard_OStream& astream) const;

  Standard_EXPORT bool IsSameState(const occ::handle<TCollection_HExtendedString>& other) const;

  DEFINE_STANDARD_RTTIEXT(TCollection_HExtendedString, Standard_Transient)

private:
  Standard_EXPORT TCollection_ExtendedString& ChangeString() const;

  TCollection_ExtendedString myString;
};

namespace std
{
  template <>
  struct hash<occ::handle<TCollection_HExtendedString>>
  {
    size_t operator()(const occ::handle<TCollection_HExtendedString>& theString) const
    {
      if (theString.IsNull())
        return 0;
      return std::hash<TCollection_ExtendedString>{}(theString->String());
    }
  };

  template <>
  struct equal_to<occ::handle<TCollection_HExtendedString>>
  {
    bool operator()(const occ::handle<TCollection_HExtendedString>& theString1,
                    const occ::handle<TCollection_HExtendedString>& theString2) const
    {
      return theString1 == theString2
             || (!theString1.IsNull() && !theString2.IsNull()
                 && theString1->String() == theString2->String());
    }
  };
} // namespace std
