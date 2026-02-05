#include <Standard_Type.hpp>
#include <TCollection_HAsciiString.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <Units_Token.hpp>
#include <Units_Unit.hpp>
#include <Units_UnitsDictionary.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Units_Unit, Standard_Transient)

//=================================================================================================

Units_Unit::Units_Unit(const char*                        aname,
                       const char*                        asymbol,
                       const double                       avalue,
                       const occ::handle<Units_Quantity>& aquantity)
{
  thename                                      = new TCollection_HAsciiString(aname);
  thevalue                                     = avalue;
  thequantity                                  = aquantity;
  occ::handle<TCollection_HAsciiString> symbol = new TCollection_HAsciiString(asymbol);
  thesymbolssequence = new NCollection_HSequence<occ::handle<TCollection_HAsciiString>>();
  thesymbolssequence->Prepend(symbol);
}

//=================================================================================================

Units_Unit::Units_Unit(const char* aname, const char* asymbol)
{
  thename                                      = new TCollection_HAsciiString(aname);
  thevalue                                     = 0.;
  occ::handle<TCollection_HAsciiString> symbol = new TCollection_HAsciiString(asymbol);
  thesymbolssequence = new NCollection_HSequence<occ::handle<TCollection_HAsciiString>>();
  thesymbolssequence->Prepend(symbol);
}

//=================================================================================================

Units_Unit::Units_Unit(const char* aname)
{
  thename            = new TCollection_HAsciiString(aname);
  thevalue           = 0.;
  thesymbolssequence = new NCollection_HSequence<occ::handle<TCollection_HAsciiString>>();
}

//=================================================================================================

void Units_Unit::Symbol(const char* asymbol)
{
  occ::handle<TCollection_HAsciiString> symbol = new TCollection_HAsciiString(asymbol);
  thesymbolssequence->Append(symbol);
}

//=================================================================================================

occ::handle<Units_Token> Units_Unit::Token() const
{
  TCollection_AsciiString string = thesymbolssequence->Value(1)->String();
  return new Units_Token(string.ToCString(), " ", thevalue, thequantity->Dimensions());
}

//=================================================================================================

bool Units_Unit::IsEqual(const char* astring) const
{
  int                     index;
  TCollection_AsciiString symbol;

  for (index = 1; index <= thesymbolssequence->Length(); index++)
  {
    symbol = thesymbolssequence->Value(index)->String();
    if (symbol == astring)
      return true;
  }

  return false;
}

//=================================================================================================

void Units_Unit::Dump(const int /*ashift*/, const int) const
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
  std::cout << "		Name:  " << Name().ToCString() << "		(= " << thevalue << " SI)" << std::endl;
}

//=======================================================================
// function : operator ==
// purpose  :
//=======================================================================

bool operator==(const occ::handle<Units_Unit>& aunit, const char* astring)
{
  return aunit->IsEqual(astring);
}
