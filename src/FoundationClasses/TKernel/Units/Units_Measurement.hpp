#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class Units_Token;

//! This class defines a measurement which is the
//! association of a real value and a unit.
class Units_Measurement
{
public:
  DEFINE_STANDARD_ALLOC

  //! It is the empty constructor of the class.
  Standard_EXPORT Units_Measurement();

  //! Returns an instance of this class. <avalue> defines
  //! the measurement, and <atoken> the token which defines
  //! the unit used.
  Standard_EXPORT Units_Measurement(const double avalue, const occ::handle<Units_Token>& atoken);

  //! Returns an instance of this class. <avalue> defines
  //! the measurement, and <aunit> the unit used,
  //! described in natural language.
  Standard_EXPORT Units_Measurement(const double avalue, const char* aunit);

  //! Converts (if possible) the measurement object into
  //! another unit. <aunit> must have the same
  //! dimensionality as the unit contained in the token
  //! <thetoken>.
  Standard_EXPORT void Convert(const char* aunit);

  //! Returns a Measurement object with the integer value of
  //! the measurement contained in <me>.
  Standard_EXPORT Units_Measurement Integer() const;

  //! Returns a Measurement object with the fractional value
  //! of the measurement contained in <me>.
  Standard_EXPORT Units_Measurement Fractional() const;

  //! Returns the value of the measurement.
  Standard_EXPORT double Measurement() const;

  //! Returns the token contained in <me>.
  Standard_EXPORT occ::handle<Units_Token> Token() const;

  //! Returns (if it is possible) a measurement which is the
  //! addition of <me> and <ameasurement>. The chosen
  //! returned unit is the unit of <me>.
  Standard_EXPORT Units_Measurement Add(const Units_Measurement& ameasurement) const;

  Units_Measurement operator+(const Units_Measurement& ameasurement) const
  {
    return Add(ameasurement);
  }

  //! Returns (if it is possible) a measurement which is the
  //! subtraction of <me> and <ameasurement>. The chosen
  //! returned unit is the unit of <me>.
  Standard_EXPORT Units_Measurement Subtract(const Units_Measurement& ameasurement) const;

  Units_Measurement operator-(const Units_Measurement& ameasurement) const
  {
    return Subtract(ameasurement);
  }

  //! Returns a measurement which is the multiplication of
  //! <me> and <ameasurement>.
  Standard_EXPORT Units_Measurement Multiply(const Units_Measurement& ameasurement) const;

  Units_Measurement operator*(const Units_Measurement& ameasurement) const
  {
    return Multiply(ameasurement);
  }

  //! Returns a measurement which is the multiplication of
  //! <me> with the value <avalue>.
  Standard_EXPORT Units_Measurement Multiply(const double avalue) const;

  Units_Measurement operator*(const double avalue) const { return Multiply(avalue); }

  //! Returns a measurement which is the division of <me> by
  //! <ameasurement>.
  Standard_EXPORT Units_Measurement Divide(const Units_Measurement& ameasurement) const;

  Units_Measurement operator/(const Units_Measurement& ameasurement) const
  {
    return Divide(ameasurement);
  }

  //! Returns a measurement which is the division of <me> by
  //! the constant <avalue>.
  Standard_EXPORT Units_Measurement Divide(const double avalue) const;

  Units_Measurement operator/(const double avalue) const { return Divide(avalue); }

  //! Returns a measurement which is <me> powered
  //! <anexponent>.
  Standard_EXPORT Units_Measurement Power(const double anexponent) const;

  Standard_EXPORT bool HasToken() const;

  //! Useful for debugging.
  Standard_EXPORT void Dump() const;

private:
  double                   themeasurement;
  occ::handle<Units_Token> thetoken;
  bool                     myHasToken;
};

