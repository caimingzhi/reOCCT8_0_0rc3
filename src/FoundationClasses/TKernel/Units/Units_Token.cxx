#include <Standard_Type.hpp>
#include <Units_Operators.hpp>
#include <Units_Token.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Units_Token, Standard_Transient)

Units_Token::Units_Token()
{
  theword       = " ";
  themean       = " ";
  thevalue      = 0.;
  thedimensions = new Units_Dimensions(0., 0., 0., 0., 0., 0., 0., 0., 0.);
}

Units_Token::Units_Token(const char* aword)
{
  theword       = aword;
  themean       = " ";
  thevalue      = 0.;
  thedimensions = new Units_Dimensions(0., 0., 0., 0., 0., 0., 0., 0., 0.);
}

Units_Token::Units_Token(const char* aword, const char* amean)
{
  theword       = aword;
  themean       = amean;
  thevalue      = 0.;
  thedimensions = new Units_Dimensions(0., 0., 0., 0., 0., 0., 0., 0., 0.);
}

Units_Token::Units_Token(const char* aword, const char* amean, const double avalue)
{
  theword       = aword;
  themean       = amean;
  thevalue      = avalue;
  thedimensions = new Units_Dimensions(0., 0., 0., 0., 0., 0., 0., 0., 0.);
}

Units_Token::Units_Token(const char*                          aword,
                         const char*                          amean,
                         const double                         avalue,
                         const occ::handle<Units_Dimensions>& adimensions)
{
  theword  = aword;
  themean  = amean;
  thevalue = avalue;
  if (adimensions.IsNull())
    thedimensions = new Units_Dimensions(0., 0., 0., 0., 0., 0., 0., 0., 0.);
  else
    thedimensions = new Units_Dimensions(adimensions->Mass(),
                                         adimensions->Length(),
                                         adimensions->Time(),
                                         adimensions->ElectricCurrent(),
                                         adimensions->ThermodynamicTemperature(),
                                         adimensions->AmountOfSubstance(),
                                         adimensions->LuminousIntensity(),
                                         adimensions->PlaneAngle(),
                                         adimensions->SolidAngle());
}

occ::handle<Units_Token> Units_Token::Creates() const
{
  TCollection_AsciiString word = Word();
  TCollection_AsciiString mean = Mean();
  return new Units_Token(word.ToCString(), mean.ToCString(), Value(), Dimensions());
}

int Units_Token::Length() const
{
  return theword.Length();
}

void Units_Token::Dimensions(const occ::handle<Units_Dimensions>& adimensions)
{
  if (adimensions.IsNull())
    thedimensions = new Units_Dimensions(0., 0., 0., 0., 0., 0., 0., 0., 0.);
  else
    thedimensions = new Units_Dimensions(adimensions->Mass(),
                                         adimensions->Length(),
                                         adimensions->Time(),
                                         adimensions->ElectricCurrent(),
                                         adimensions->ThermodynamicTemperature(),
                                         adimensions->AmountOfSubstance(),
                                         adimensions->LuminousIntensity(),
                                         adimensions->PlaneAngle(),
                                         adimensions->SolidAngle());
}

Units_Token::Units_Token(const occ::handle<Units_Token>& atoken)
{
  theword       = atoken->Word();
  themean       = atoken->Mean();
  thevalue      = atoken->Value();
  thedimensions = atoken->Dimensions();
}

void Units_Token::Update(const char* amean)
{
  TCollection_AsciiString string = Mean();
  if (string.Search(amean) != -1)
    std::cout << Word() << " encountered twice with the same signification : " << amean
              << std::endl;
  string  = string + amean;
  themean = string;
}

occ::handle<Units_Token> Units_Token::Add(const int) const
{

  return new Units_Token();
}

occ::handle<Units_Token> Units_Token::Add(const occ::handle<Units_Token>& atoken) const
{
  TCollection_AsciiString word = Word();
  if (thedimensions->IsEqual(atoken->Dimensions()))
    return new Units_Token(word.ToCString(), " ", thevalue + atoken->Value(), thedimensions);
  else
    return new Units_Token(" ");
}

occ::handle<Units_Token> Units_Token::Subtract(const occ::handle<Units_Token>& atoken) const
{
  TCollection_AsciiString word = Word();
  if (thedimensions->IsEqual(atoken->Dimensions()))
    return new Units_Token(word.ToCString(), " ", thevalue - atoken->Value(), thedimensions);
  else
    return new Units_Token(" ");
}

occ::handle<Units_Token> Units_Token::Multiply(const occ::handle<Units_Token>& atoken) const
{
  TCollection_AsciiString string = Word();
  string.Insert(1, '(');
  string = string + ")*(";
  string = string + atoken->Word();
  string = string + ")";
  return new Units_Token(string.ToCString(),
                         " ",
                         thevalue * atoken->Value(),
                         thedimensions * (atoken->Dimensions()));
}

double Units_Token::Multiplied(const double avalue) const
{
  return avalue * thevalue;
}

occ::handle<Units_Token> Units_Token::Divide(const occ::handle<Units_Token>& atoken) const
{
  if (fabs(atoken->Value()) < 1.e-40)
  {
#ifdef OCCT_DEBUG
    std::cout << "Warning: division on token with value=0 => return initial token." << std::endl;
#endif
    return this;
  }
  TCollection_AsciiString string = Word();
  string.Insert(1, '(');
  string = string + ")/(";
  string = string + atoken->Word();
  string = string + ")";
  return new Units_Token(string.ToCString(),
                         " ",
                         thevalue / atoken->Value(),
                         thedimensions / (atoken->Dimensions()));
}

double Units_Token::Divided(const double avalue) const
{
  return avalue / thevalue;
}

occ::handle<Units_Token> Units_Token::Power(const occ::handle<Units_Token>& atoken) const
{
  TCollection_AsciiString string = Word();
  string.Insert(1, '(');
  string = string + ")**(";
  string = string + atoken->Word();
  string = string + ")";
  return new Units_Token(string.ToCString(),
                         " ",
                         pow(thevalue, atoken->Value()),
                         pow(thedimensions, atoken->Value()));
}

occ::handle<Units_Token> Units_Token::Power(const double anexponent) const
{
  TCollection_AsciiString exponent(anexponent);
  TCollection_AsciiString string = Word();
  string.Insert(1, '(');
  string = string + ")**(";
  string = string + exponent;
  string = string + ")";
  return new Units_Token(string.ToCString(),
                         " ",
                         pow(thevalue, anexponent),
                         pow(thedimensions, anexponent));
}

bool Units_Token::IsEqual(const char* astring) const
{
  TCollection_AsciiString string = Word();
#ifdef UNX
  int length = string.Length();
#else
  unsigned int length = string.Length();
#endif
  if (strlen(astring) == length)
    return strncmp(string.ToCString(), astring, unsigned(length)) == 0;
  else
    return false;
}

bool Units_Token::IsEqual(const occ::handle<Units_Token>& atoken) const
{
  TCollection_AsciiString string1 = Word();
  TCollection_AsciiString string2 = atoken->Word();
  int                     length  = string1.Length();
  if (length == atoken->Length())
    return strcmp(string1.ToCString(), string2.ToCString()) == 0;
  else
    return false;
}

void Units_Token::Dump(const int ashift, const int alevel) const
{
  int                     i;
  TCollection_AsciiString word = Word();
  TCollection_AsciiString mean = Mean();

  for (i = 0; i < ashift; i++)
    std::cout << "  ";
  std::cout << "Units_Token::Dump of " << this << std::endl;
  for (i = 0; i < ashift; i++)
    std::cout << "  ";
  std::cout << word.ToCString() << std::endl;
  for (i = 0; i < ashift; i++)
    std::cout << "  ";
  std::cout << "  value : " << thevalue << std::endl;
  for (i = 0; i < ashift; i++)
    std::cout << "  ";
  std::cout << "  mean  : " << mean.ToCString() << std::endl;
  if (alevel)
    thedimensions->Dump(ashift);
}

occ::handle<Units_Token> operator+(const occ::handle<Units_Token>& atoken, const int aninteger)
{
  return atoken->Add(aninteger);
}

occ::handle<Units_Token> operator+(const occ::handle<Units_Token>& atoken1,
                                   const occ::handle<Units_Token>& atoken2)
{
  return atoken1->Add(atoken2);
}

occ::handle<Units_Token> operator-(const occ::handle<Units_Token>& atoken1,
                                   const occ::handle<Units_Token>& atoken2)
{
  return atoken1->Subtract(atoken2);
}

occ::handle<Units_Token> operator*(const occ::handle<Units_Token>& atoken1,
                                   const occ::handle<Units_Token>& atoken2)
{
  return atoken1->Multiply(atoken2);
}

occ::handle<Units_Token> operator/(const occ::handle<Units_Token>& atoken1,
                                   const occ::handle<Units_Token>& atoken2)
{
  return atoken1->Divide(atoken2);
}

occ::handle<Units_Token> pow(const occ::handle<Units_Token>& atoken1,
                             const occ::handle<Units_Token>& atoken2)
{
  return atoken1->Power(atoken2);
}

occ::handle<Units_Token> pow(const occ::handle<Units_Token>& atoken, const double areal)
{
  return atoken->Power(areal);
}

bool operator==(const occ::handle<Units_Token>& atoken, const char* astring)
{
  return atoken->IsEqual(astring);
}

bool operator!=(const occ::handle<Units_Token>& atoken, const char* astring)
{
  return atoken->IsNotEqual(astring);
}

bool operator<=(const occ::handle<Units_Token>& atoken, const char* astring)
{
  return atoken->IsLessOrEqual(astring);
}

bool operator>(const occ::handle<Units_Token>& atoken, const char* astring)
{
  return atoken->IsGreater(astring);
}

bool operator>(const occ::handle<Units_Token>& atoken1, const occ::handle<Units_Token>& atoken2)
{
  return atoken1->IsGreater(atoken2);
}

bool operator>=(const occ::handle<Units_Token>& atoken1, const occ::handle<Units_Token>& atoken2)
{
  return atoken1->IsGreaterOrEqual(atoken2);
}
