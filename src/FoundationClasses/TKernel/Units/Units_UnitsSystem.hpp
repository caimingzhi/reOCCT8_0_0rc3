#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Units_Quantity.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Transient.hpp>
class TCollection_AsciiString;

//! This class allows the user to define his own
//! system of units.
class Units_UnitsSystem : public Standard_Transient
{

public:
  //! Returns an instance of UnitsSystem initialized to the
  //! S.I. units system.
  Standard_EXPORT Units_UnitsSystem();

  //! Returns an instance of UnitsSystem initialized to the
  //! S.I. units system upgraded by the base system units description
  //! file.
  //! Attempts to find the four following files:
  //! $CSF_`aName`Defaults/.aName
  //! $CSF_`aName`SiteDefaults/.aName
  //! $CSF_`aName`GroupDefaults/.aName
  //! $CSF_`aName`UserDefaults/.aName
  //! See : Resource_Manager for the description of this file.
  Standard_EXPORT Units_UnitsSystem(const char* aName, const bool Verbose = false);

  //! Returns the sequence of refined quantities.
  Standard_EXPORT occ::handle<NCollection_HSequence<occ::handle<Units_Quantity>>>
                  QuantitiesSequence() const;

  //! Returns a sequence of integer in correspondence with
  //! the sequence of quantities, which indicates, for each
  //! redefined quantity, the index into the sequence of
  //! units, of the active unit.
  Standard_EXPORT occ::handle<NCollection_HSequence<int>> ActiveUnitsSequence() const;

  //! Specifies for <aquantity> the unit <aunit> used.
  Standard_EXPORT void Specify(const char* aquantity, const char* aunit);

  //! Removes for <aquantity> the unit <aunit> used.
  Standard_EXPORT void Remove(const char* aquantity, const char* aunit);

  //! Specifies for <aquantity> the unit <aunit> used.
  Standard_EXPORT void Activate(const char* aquantity, const char* aunit);

  //! Activates the first unit of all defined system quantities
  Standard_EXPORT void Activates();

  //! Returns for <aquantity> the active unit.
  Standard_EXPORT TCollection_AsciiString ActiveUnit(const char* aquantity) const;

  //! Converts a real value <avalue> from the unit <aunit>
  //! belonging to the physical dimensions <aquantity> to
  //! the corresponding unit of the user system.
  Standard_EXPORT double ConvertValueToUserSystem(const char*  aquantity,
                                                  const double avalue,
                                                  const char*  aunit) const;

  //! Converts the real value <avalue> from the S.I. system
  //! of units to the user system of units. <aquantity> is
  //! the physical dimensions of the measurement.
  Standard_EXPORT double ConvertSIValueToUserSystem(const char*  aquantity,
                                                    const double avalue) const;

  //! Converts the real value <avalue> from the user system
  //! of units to the S.I. system of units. <aquantity> is
  //! the physical dimensions of the measurement.
  Standard_EXPORT double ConvertUserSystemValueToSI(const char*  aquantity,
                                                    const double avalue) const;

  Standard_EXPORT void Dump() const;

  //! Returns TRUE if no units has been defined in the system.
  Standard_EXPORT bool IsEmpty() const;

  DEFINE_STANDARD_RTTIEXT(Units_UnitsSystem, Standard_Transient)

private:
  occ::handle<NCollection_HSequence<occ::handle<Units_Quantity>>> thequantitiessequence;
  occ::handle<NCollection_HSequence<int>>                         theactiveunitssequence;
};

