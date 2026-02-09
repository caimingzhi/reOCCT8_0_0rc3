#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TCollection_HAsciiString.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <Standard_Transient.hpp>
#include <TCollection_AsciiString.hpp>
#include <Standard_Integer.hpp>
class TCollection_HAsciiString;
class Units_Quantity;
class Units_Token;

class Units_Unit : public Standard_Transient
{

public:
  Standard_EXPORT Units_Unit(const char*                        aname,
                             const char*                        asymbol,
                             const double                       avalue,
                             const occ::handle<Units_Quantity>& aquantity);

  Standard_EXPORT Units_Unit(const char* aname, const char* asymbol);

  Standard_EXPORT Units_Unit(const char* aname);

  TCollection_AsciiString Name() const;

  Standard_EXPORT void Symbol(const char* asymbol);

  double Value() const;

  occ::handle<Units_Quantity> Quantity() const;

  occ::handle<NCollection_HSequence<occ::handle<TCollection_HAsciiString>>> SymbolsSequence() const;

  void Value(const double avalue);

  void Quantity(const occ::handle<Units_Quantity>& aquantity);

  Standard_EXPORT virtual occ::handle<Units_Token> Token() const;

  Standard_EXPORT bool IsEqual(const char* astring) const;

  Standard_EXPORT virtual void Dump(const int ashift, const int alevel) const;

  DEFINE_STANDARD_RTTIEXT(Units_Unit, Standard_Transient)

protected:
  occ::handle<NCollection_HSequence<occ::handle<TCollection_HAsciiString>>> thesymbolssequence;
  double                                                                    thevalue;

private:
  occ::handle<TCollection_HAsciiString> thename;
  occ::handle<Units_Quantity>           thequantity;
};

#include <stdio.h>
#include <string.h>
#include <Standard_Macro.hpp>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <TCollection_HAsciiString.hpp>
#include <TCollection_AsciiString.hpp>

inline TCollection_AsciiString Units_Unit::Name() const
{
  return thename->String();
}

inline double Units_Unit::Value() const
{
  return thevalue;
}

inline occ::handle<Units_Quantity> Units_Unit::Quantity() const
{
  return thequantity;
}

inline occ::handle<NCollection_HSequence<occ::handle<TCollection_HAsciiString>>> Units_Unit::
  SymbolsSequence() const
{
  return thesymbolssequence;
}

inline void Units_Unit::Value(const double avalue)
{
  thevalue = avalue;
}

inline void Units_Unit::Quantity(const occ::handle<Units_Quantity>& aquantity)
{
  thequantity = aquantity;
}
