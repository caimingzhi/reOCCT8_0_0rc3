#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Units_Unit.hpp>
#include <Standard_Integer.hpp>
class Units_Quantity;
class Units_Token;

//! This class is useful to describe units with a
//! shifted origin in relation to another unit. A well
//! known example is the Celsius degrees in relation
//! to Kelvin degrees. The shift of the Celsius origin
//! is 273.15 Kelvin degrees.
class Units_ShiftedUnit : public Units_Unit
{

public:
  //! Creates and returns a shifted unit. <aname> is the
  //! name of the unit, <asymbol> is the usual abbreviation
  //! of the unit, <avalue> is the value in relation to the
  //! International System of Units, and <amove> is the gap
  //! in relation to another unit.
  //!
  //! For example Celsius degree of temperature is an
  //! instance of ShiftedUnit with <avalue> equal to 1.
  //! and <amove> equal to 273.15.
  Standard_EXPORT Units_ShiftedUnit(const char*                        aname,
                                    const char*                        asymbol,
                                    const double                       avalue,
                                    const double                       amove,
                                    const occ::handle<Units_Quantity>& aquantity);

  //! Creates and returns a unit. <aname> is the name of
  //! the unit, <asymbol> is the usual abbreviation of the
  //! unit.
  Standard_EXPORT Units_ShiftedUnit(const char* aname, const char* asymbol);

  //! Creates and returns a unit. <aname> is the name of
  //! the unit.
  Standard_EXPORT Units_ShiftedUnit(const char* aname);

  //! Sets the field <themove> to <amove>
  Standard_EXPORT void Move(const double amove);

  //! Returns the shifted value <themove>.
  Standard_EXPORT double Move() const;

  //! This redefined method returns a ShiftedToken object.
  Standard_EXPORT occ::handle<Units_Token> Token() const override;

  Standard_EXPORT void Dump(const int ashift, const int alevel) const override;

  DEFINE_STANDARD_RTTIEXT(Units_ShiftedUnit, Units_Unit)

private:
  double themove;
};

