#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TCollection_AsciiString.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Integer.hpp>
class Units_Dimensions;

class Units_Token : public Standard_Transient
{

public:
  Standard_EXPORT Units_Token();

  Standard_EXPORT Units_Token(const char* aword);

  Standard_EXPORT Units_Token(const occ::handle<Units_Token>& atoken);

  Standard_EXPORT Units_Token(const char* aword, const char* amean);

  Standard_EXPORT Units_Token(const char* aword, const char* amean, const double avalue);

  Standard_EXPORT Units_Token(const char*                          aword,
                              const char*                          amean,
                              const double                         avalue,
                              const occ::handle<Units_Dimensions>& adimension);

  Standard_EXPORT virtual occ::handle<Units_Token> Creates() const;

  Standard_EXPORT int Length() const;

  TCollection_AsciiString Word() const;

  void Word(const char* aword);

  TCollection_AsciiString Mean() const;

  void Mean(const char* amean);

  double Value() const;

  void Value(const double avalue);

  occ::handle<Units_Dimensions> Dimensions() const;

  Standard_EXPORT void Dimensions(const occ::handle<Units_Dimensions>& adimensions);

  Standard_EXPORT void Update(const char* amean);

  Standard_EXPORT occ::handle<Units_Token> Add(const int aninteger) const;

  Standard_EXPORT occ::handle<Units_Token> Add(const occ::handle<Units_Token>& atoken) const;

  Standard_EXPORT occ::handle<Units_Token> Subtract(const occ::handle<Units_Token>& atoken) const;

  Standard_EXPORT occ::handle<Units_Token> Multiply(const occ::handle<Units_Token>& atoken) const;

  [[nodiscard]] Standard_EXPORT virtual double Multiplied(const double avalue) const;

  Standard_EXPORT occ::handle<Units_Token> Divide(const occ::handle<Units_Token>& atoken) const;

  [[nodiscard]] Standard_EXPORT virtual double Divided(const double avalue) const;

  Standard_EXPORT occ::handle<Units_Token> Power(const occ::handle<Units_Token>& atoken) const;

  Standard_EXPORT occ::handle<Units_Token> Power(const double anexponent) const;

  Standard_EXPORT bool IsEqual(const char* astring) const;

  Standard_EXPORT bool IsEqual(const occ::handle<Units_Token>& atoken) const;

  bool IsNotEqual(const char* astring) const;

  bool IsNotEqual(const occ::handle<Units_Token>& atoken) const;

  bool IsLessOrEqual(const char* astring) const;

  bool IsGreater(const char* astring) const;

  bool IsGreater(const occ::handle<Units_Token>& atoken) const;

  bool IsGreaterOrEqual(const occ::handle<Units_Token>& atoken) const;

  Standard_EXPORT virtual void Dump(const int ashift, const int alevel) const;

  DEFINE_STANDARD_RTTIEXT(Units_Token, Standard_Transient)

private:
  TCollection_AsciiString       theword;
  TCollection_AsciiString       themean;
  double                        thevalue;
  occ::handle<Units_Dimensions> thedimensions;
};

#include <stdio.h>
#include <string.h>
#include <Standard_Macro.hpp>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <TCollection_AsciiString.hpp>
#include <Units_Dimensions.hpp>

inline TCollection_AsciiString Units_Token::Word() const
{
  return theword;
}

inline TCollection_AsciiString Units_Token::Mean() const
{
  return themean;
}

inline double Units_Token::Value() const
{
  return thevalue;
}

inline occ::handle<Units_Dimensions> Units_Token::Dimensions() const
{
  return thedimensions;
}

inline void Units_Token::Word(const char* aword)
{
  theword = aword;
}

inline void Units_Token::Mean(const char* amean)
{
  themean = amean;
}

inline void Units_Token::Value(const double avalue)
{
  thevalue = avalue;
}

inline bool Units_Token::IsNotEqual(const char* astring) const
{
  TCollection_AsciiString string = Word();
  int                     length = string.Length();
  if (strlen(astring) == (unsigned int)length)
    return strncmp(string.ToCString(), astring, unsigned(length)) != 0;
  else
    return true;
}

inline bool Units_Token::IsNotEqual(const occ::handle<Units_Token>& atoken) const
{
  TCollection_AsciiString string1 = Word();
  TCollection_AsciiString string2 = atoken->Word();
  int                     length  = string1.Length();
  if (length == atoken->Length())
    return strcmp(string1.ToCString(), string2.ToCString()) != 0;
  else
    return true;
}

inline bool Units_Token::IsLessOrEqual(const char* astring) const
{
  TCollection_AsciiString string = Word();
  int                     length = string.Length();
  if (strlen(astring) >= (unsigned int)length)
    return strncmp(string.ToCString(), astring, unsigned(length)) == 0;
  else
    return false;
}

inline bool Units_Token::IsGreater(const char* astring) const
{
  TCollection_AsciiString string = Word();
  int                     length = string.Length();
  return strncmp(string.ToCString(), astring, unsigned(length)) > 0;
}

inline bool Units_Token::IsGreater(const occ::handle<Units_Token>& atoken) const
{
  TCollection_AsciiString string1 = Word();
  TCollection_AsciiString string2 = atoken->Word();
  int                     length  = string1.Length();
  return strncmp(string1.ToCString(), string2.ToCString(), unsigned(length)) > 0;
}

inline bool Units_Token::IsGreaterOrEqual(const occ::handle<Units_Token>& atoken) const
{
  TCollection_AsciiString string1 = Word();
  TCollection_AsciiString string2 = atoken->Word();
  int                     length  = string1.Length();
  return strncmp(string1.ToCString(), string2.ToCString(), unsigned(length)) >= 0;
}
