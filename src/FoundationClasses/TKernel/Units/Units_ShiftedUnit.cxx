#include <Standard_Type.hpp>
#include <TCollection_HAsciiString.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <Units_Quantity.hpp>
#include <Units_ShiftedToken.hpp>
#include <Units_ShiftedUnit.hpp>
#include <Units_Token.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Units_ShiftedUnit, Units_Unit)

//=================================================================================================

Units_ShiftedUnit::Units_ShiftedUnit(const char*                        aname,
                                     const char*                        asymbol,
                                     const double                       avalue,
                                     const double                       amove,
                                     const occ::handle<Units_Quantity>& aquantity)
    : Units_Unit(aname, asymbol, avalue, aquantity)
{
  themove = amove;
}

//=================================================================================================

Units_ShiftedUnit::Units_ShiftedUnit(const char* aname, const char* asymbol)
    : Units_Unit(aname, asymbol),
      themove(0.0)
{
}

//=================================================================================================

Units_ShiftedUnit::Units_ShiftedUnit(const char* aname)
    : Units_Unit(aname),
      themove(0.0)
{
}

//=================================================================================================

void Units_ShiftedUnit::Move(const double amove)
{
  themove = amove;
}

//=================================================================================================

double Units_ShiftedUnit::Move() const
{
  return themove;
}

//=================================================================================================

occ::handle<Units_Token> Units_ShiftedUnit::Token() const
{
  TCollection_AsciiString string = SymbolsSequence()->Value(1)->String();
  return new Units_ShiftedToken(string.ToCString(),
                                " ",
                                Value(),
                                themove,
                                Quantity()->Dimensions());
}

//=================================================================================================

// void Units_ShiftedUnit::Dump(const int ashift,
//			     const int alevel) const
void Units_ShiftedUnit::Dump(const int, const int) const
{
  int                     index;
  TCollection_AsciiString string;

  //  int i;
  //  for(i=0; i<ashift; i++)std::cout<<"  ";
  for (index = 1; index <= thesymbolssequence->Length(); index++)
  {
    string = thesymbolssequence->Value(index)->String();
    if (index != 1)
      std::cout << " or ";
    std::cout << "\"" << string.ToCString() << "\"";
  }
  std::cout << "		Name:  " << Name().ToCString() << "		(= *" << thevalue << " SI + " << themove
            << ")" << std::endl;
}
