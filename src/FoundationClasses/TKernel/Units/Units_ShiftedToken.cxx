#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>
#include <Units_ShiftedToken.hpp>
#include <Units_Token.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Units_ShiftedToken, Units_Token)

Units_ShiftedToken::Units_ShiftedToken(const char*                          aword,
                                       const char*                          amean,
                                       const double                         avalue,
                                       const double                         amove,
                                       const occ::handle<Units_Dimensions>& adimensions)
    : Units_Token(aword, amean, avalue, adimensions)
{
  themove = amove;
}

occ::handle<Units_Token> Units_ShiftedToken::Creates() const
{
  TCollection_AsciiString word = Word();
  TCollection_AsciiString mean = Mean();
  return new Units_ShiftedToken(word.ToCString(), mean.ToCString(), Value(), Move(), Dimensions());
}

double Units_ShiftedToken::Move() const
{
  return themove;
}

double Units_ShiftedToken::Multiplied(const double avalue) const
{
  return (avalue + themove) * Value();
}

double Units_ShiftedToken::Divided(const double avalue) const
{
  return (avalue / Value()) - themove;
}

void Units_ShiftedToken::Dump(const int ashift, const int alevel) const
{
  Units_Token::Dump(ashift, alevel);
  for (int i = 0; i < ashift; i++)
    std::cout << "  ";
  std::cout << "  move  : " << themove << std::endl;
}
