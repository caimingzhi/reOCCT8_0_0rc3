#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_PExtCharacter.hpp>
#include <Standard_Integer.hpp>
#include <Standard_CString.hpp>
#include <Standard_Boolean.hpp>
#include <Standard_Character.hpp>
#include <Standard_ExtCharacter.hpp>
#include <Standard_Real.hpp>
#include <Standard_OStream.hpp>
#include <Standard_PCharacter.hpp>
#include <Standard_Macro.hpp>
class TCollection_AsciiString;

class TCollection_ExtendedString
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TCollection_ExtendedString() noexcept;

  Standard_EXPORT TCollection_ExtendedString(const char* astring, const bool isMultiByte = false);

  Standard_EXPORT TCollection_ExtendedString(const char16_t* astring);

#if !defined(_MSC_VER) || defined(_NATIVE_WCHAR_T_DEFINED)

  Standard_EXPORT TCollection_ExtendedString(const wchar_t* theStringUtf);
#endif

  Standard_EXPORT TCollection_ExtendedString(const char aChar);

  Standard_EXPORT TCollection_ExtendedString(const char16_t aChar);

  Standard_EXPORT TCollection_ExtendedString(const int length, const char16_t filler);

  Standard_EXPORT TCollection_ExtendedString(const int value);

  Standard_EXPORT TCollection_ExtendedString(const double value);

  Standard_EXPORT TCollection_ExtendedString(const TCollection_ExtendedString& astring);

  Standard_EXPORT TCollection_ExtendedString(TCollection_ExtendedString&& theOther) noexcept;

  Standard_EXPORT TCollection_ExtendedString(const TCollection_AsciiString& astring,
                                             const bool                     isMultiByte = true);

  Standard_EXPORT void AssignCat(const TCollection_ExtendedString& other);

  void operator+=(const TCollection_ExtendedString& other) { AssignCat(other); }

  Standard_EXPORT void AssignCat(const char16_t theChar);

  Standard_EXPORT TCollection_ExtendedString Cat(const TCollection_ExtendedString& other) const;

  TCollection_ExtendedString operator+(const TCollection_ExtendedString& other) const
  {
    return Cat(other);
  }

  Standard_EXPORT void ChangeAll(const char16_t aChar, const char16_t NewChar);

  Standard_EXPORT void Clear();

  Standard_EXPORT void Copy(const TCollection_ExtendedString& fromwhere);

  TCollection_ExtendedString& operator=(const TCollection_ExtendedString& theOther)
  {
    Copy(theOther);
    return *this;
  }

  Standard_EXPORT void Move(TCollection_ExtendedString&& theOther);

  TCollection_ExtendedString& operator=(TCollection_ExtendedString&& theOther) noexcept
  {
    Move(std::forward<TCollection_ExtendedString>(theOther));
    return *this;
  }

  Standard_EXPORT void Swap(TCollection_ExtendedString& theOther);

  Standard_EXPORT ~TCollection_ExtendedString();

  Standard_EXPORT void Insert(const int where, const char16_t what);

  Standard_EXPORT void Insert(const int where, const TCollection_ExtendedString& what);

  bool IsEmpty() const { return mylength == 0; }

  Standard_EXPORT bool IsEqual(const char16_t* other) const;

  bool operator==(const char16_t* other) const { return IsEqual(other); }

  Standard_EXPORT bool IsEqual(const TCollection_ExtendedString& other) const;

  bool operator==(const TCollection_ExtendedString& other) const { return IsEqual(other); }

  Standard_EXPORT bool IsDifferent(const char16_t* other) const;

  bool operator!=(const char16_t* other) const { return IsDifferent(other); }

  Standard_EXPORT bool IsDifferent(const TCollection_ExtendedString& other) const;

  bool operator!=(const TCollection_ExtendedString& other) const { return IsDifferent(other); }

  Standard_EXPORT bool IsLess(const char16_t* other) const;

  bool operator<(const char16_t* other) const { return IsLess(other); }

  Standard_EXPORT bool IsLess(const TCollection_ExtendedString& other) const;

  bool operator<(const TCollection_ExtendedString& other) const { return IsLess(other); }

  Standard_EXPORT bool IsGreater(const char16_t* other) const;

  bool operator>(const char16_t* other) const { return IsGreater(other); }

  Standard_EXPORT bool IsGreater(const TCollection_ExtendedString& other) const;

  bool operator>(const TCollection_ExtendedString& other) const { return IsGreater(other); }

  Standard_EXPORT bool StartsWith(const TCollection_ExtendedString& theStartString) const;

  Standard_EXPORT bool EndsWith(const TCollection_ExtendedString& theEndString) const;

  Standard_EXPORT bool IsAscii() const;

  Standard_EXPORT int Length() const;

  Standard_EXPORT void                     Print(Standard_OStream& astream) const;
  friend Standard_EXPORT Standard_OStream& operator<<(Standard_OStream&                 astream,
                                                      const TCollection_ExtendedString& astring);

  Standard_EXPORT void RemoveAll(const char16_t what);

  Standard_EXPORT void Remove(const int where, const int ahowmany = 1);

  Standard_EXPORT int Search(const TCollection_ExtendedString& what) const;

  Standard_EXPORT int SearchFromEnd(const TCollection_ExtendedString& what) const;

  Standard_EXPORT void SetValue(const int where, const char16_t what);

  Standard_EXPORT void SetValue(const int where, const TCollection_ExtendedString& what);

  Standard_EXPORT TCollection_ExtendedString Split(const int where);

  Standard_EXPORT TCollection_ExtendedString Token(const char16_t* separators,
                                                   const int       whichone = 1) const;

  Standard_EXPORT const char16_t* ToExtString() const;

#ifdef _WIN32

  const wchar_t* ToWideString() const { return (const wchar_t*)ToExtString(); }
#endif

  Standard_EXPORT void Trunc(const int ahowmany);

  Standard_EXPORT char16_t Value(const int where) const;

  size_t HashCode() const
  {
    const int aSize = mylength * sizeof(char16_t);
    if (mylength < 2)
    {
      return opencascade::FNVHash::hash_combine(*mystring, aSize);
    }
    return opencascade::hashBytes(mystring, aSize);
  }

  Standard_EXPORT static const TCollection_ExtendedString& EmptyString() noexcept;

  static bool IsEqual(const TCollection_ExtendedString& theString1,
                      const TCollection_ExtendedString& theString2)
  {
    return theString1.IsEqual(theString2);
  }

  Standard_EXPORT int ToUTF8CString(Standard_PCharacter& theCString) const;

  Standard_EXPORT int LengthOfCString() const;

private:
  bool ConvertToUnicode(const char* astring);

  void allocate(const int theLength);

  void reallocate(const int theLength);

  void deallocate();

private:
  Standard_PExtCharacter mystring{};

  int mylength{};
};

namespace std
{
  template <>
  struct hash<TCollection_ExtendedString>
  {
    size_t operator()(const TCollection_ExtendedString& theString) const
    {
      return theString.HashCode();
    }
  };
} // namespace std
