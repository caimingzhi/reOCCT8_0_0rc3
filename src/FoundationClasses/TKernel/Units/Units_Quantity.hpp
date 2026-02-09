#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Units_Unit.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <Standard_Transient.hpp>
#include <TCollection_AsciiString.hpp>
#include <Standard_Integer.hpp>
class TCollection_HAsciiString;
class Units_Dimensions;

class Units_Quantity : public Standard_Transient
{

public:
  Units_Quantity(const char*                                                        aname,
                 const occ::handle<Units_Dimensions>&                               adimensions,
                 const occ::handle<NCollection_HSequence<occ::handle<Units_Unit>>>& aunitssequence);

  TCollection_AsciiString Name() const;

  occ::handle<Units_Dimensions> Dimensions() const;

  occ::handle<NCollection_HSequence<occ::handle<Units_Unit>>> Sequence() const;

  Standard_EXPORT bool IsEqual(const char* astring) const;

  Standard_EXPORT void Dump(const int ashift, const int alevel) const;

  DEFINE_STANDARD_RTTIEXT(Units_Quantity, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString>                       thename;
  occ::handle<Units_Dimensions>                               thedimensions;
  occ::handle<NCollection_HSequence<occ::handle<Units_Unit>>> theunitssequence;
};

#include <Units_Unit.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <Units_Dimensions.hpp>
#include <TCollection_HAsciiString.hpp>

inline Units_Quantity::Units_Quantity(
  const char*                                                        aname,
  const occ::handle<Units_Dimensions>&                               adimensions,
  const occ::handle<NCollection_HSequence<occ::handle<Units_Unit>>>& aunitssequence)
{
  thename          = new TCollection_HAsciiString(aname);
  thedimensions    = adimensions;
  theunitssequence = aunitssequence;
}

inline TCollection_AsciiString Units_Quantity::Name() const
{
  return thename->String();
}

inline occ::handle<Units_Dimensions> Units_Quantity::Dimensions() const
{
  return thedimensions;
}

inline occ::handle<NCollection_HSequence<occ::handle<Units_Unit>>> Units_Quantity::Sequence() const
{
  return theunitssequence;
}
