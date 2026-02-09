#pragma once

#include <Units_Quantity.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
class TCollection_AsciiString;
class Units_Dimensions;

class Units_UnitsDictionary : public Standard_Transient
{

public:
  Standard_EXPORT Units_UnitsDictionary();

  Standard_EXPORT void Creates();

  occ::handle<NCollection_HSequence<occ::handle<Units_Quantity>>> Sequence() const;

  Standard_EXPORT TCollection_AsciiString ActiveUnit(const char* aquantity) const;

  void Dump(const int alevel) const;

  void Dump(const occ::handle<Units_Dimensions>& adimensions) const;

  DEFINE_STANDARD_RTTIEXT(Units_UnitsDictionary, Standard_Transient)

private:
  occ::handle<NCollection_HSequence<occ::handle<Units_Quantity>>> thequantitiessequence;
};

#include <Units_Quantity.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <Units_Explorer.hpp>

inline occ::handle<NCollection_HSequence<occ::handle<Units_Quantity>>> Units_UnitsDictionary::
  Sequence() const
{
  return thequantitiessequence;
}

inline void Units_UnitsDictionary::Dump(const int alevel) const
{
  int index;
  switch (alevel)
  {
    case 2:
      if (!thequantitiessequence.IsNull())
      {
        for (index = 1; index <= thequantitiessequence->Length(); index++)
          thequantitiessequence->Value(index)->Dump(0, 1);
      }
      break;

    case 1:
    default:
      Units_Explorer explorer(this);
      std::cout << " UNITS DICTIONARY : " << std::endl;
      for (; explorer.MoreQuantity(); explorer.NextQuantity())
      {
        std::cout << explorer.Quantity() << std::endl;
        for (; explorer.MoreUnit(); explorer.NextUnit())
          std::cout << "  " << explorer.Unit() << std::endl;
      }
  }
}

inline void Units_UnitsDictionary::Dump(const occ::handle<Units_Dimensions>& adimensions) const
{
  int index;
  for (index = 1; index <= thequantitiessequence->Length(); index++)
  {
    if (thequantitiessequence->Value(index)->Dimensions()->IsEqual(adimensions))
      thequantitiessequence->Value(index)->Dump(0, 1);
  }
}
