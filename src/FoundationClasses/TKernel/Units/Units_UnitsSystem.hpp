#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Units_Quantity.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Transient.hpp>
class TCollection_AsciiString;

class Units_UnitsSystem : public Standard_Transient
{

public:
  Standard_EXPORT Units_UnitsSystem();

  Standard_EXPORT Units_UnitsSystem(const char* aName, const bool Verbose = false);

  Standard_EXPORT occ::handle<NCollection_HSequence<occ::handle<Units_Quantity>>>
                  QuantitiesSequence() const;

  Standard_EXPORT occ::handle<NCollection_HSequence<int>> ActiveUnitsSequence() const;

  Standard_EXPORT void Specify(const char* aquantity, const char* aunit);

  Standard_EXPORT void Remove(const char* aquantity, const char* aunit);

  Standard_EXPORT void Activate(const char* aquantity, const char* aunit);

  Standard_EXPORT void Activates();

  Standard_EXPORT TCollection_AsciiString ActiveUnit(const char* aquantity) const;

  Standard_EXPORT double ConvertValueToUserSystem(const char*  aquantity,
                                                  const double avalue,
                                                  const char*  aunit) const;

  Standard_EXPORT double ConvertSIValueToUserSystem(const char*  aquantity,
                                                    const double avalue) const;

  Standard_EXPORT double ConvertUserSystemValueToSI(const char*  aquantity,
                                                    const double avalue) const;

  Standard_EXPORT void Dump() const;

  Standard_EXPORT bool IsEmpty() const;

  DEFINE_STANDARD_RTTIEXT(Units_UnitsSystem, Standard_Transient)

private:
  occ::handle<NCollection_HSequence<occ::handle<Units_Quantity>>> thequantitiessequence;
  occ::handle<NCollection_HSequence<int>>                         theactiveunitssequence;
};
