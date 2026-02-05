#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Units_Token.hpp>
#include <Standard_Integer.hpp>
class Units_Dimensions;

//! The ShiftedToken class inherits from Token and
//! describes tokens which have a gap in addition of
//! the multiplicative factor. This kind of token
//! allows the description of linear functions which
//! do not pass through the origin, of the form:
//!
//! y = ax +b
//!
//! where <x> and <y> are the unknown variables, <a>
//! the mutiplicative factor, and <b> the gap relative
//! to the ordinate axis.
//!
//! An example is the translation between the Celsius
//! and Fahrenheit degree of temperature.
class Units_ShiftedToken : public Units_Token
{

public:
  //! Creates and returns a shifted token. <aword> is a
  //! string containing the available word, <amean> gives
  //! the signification of the token, <avalue> is the
  //! numeric value of the dimension, <amove> is the gap,
  //! and <adimensions> is the dimension of the given word
  //! <aword>.
  Standard_EXPORT Units_ShiftedToken(const char*                          aword,
                                     const char*                          amean,
                                     const double                         avalue,
                                     const double                         amove,
                                     const occ::handle<Units_Dimensions>& adimensions);

  //! Creates and returns a token, which is a ShiftedToken.
  Standard_EXPORT occ::handle<Units_Token> Creates() const override;

  //! Returns the gap <themove>
  Standard_EXPORT double Move() const;

  //! This virtual method is called by the Measurement
  //! methods, to compute the measurement during a
  //! conversion.
  Standard_EXPORT double Multiplied(const double avalue) const override;

  //! This virtual method is called by the Measurement
  //! methods, to compute the measurement during a
  //! conversion.
  Standard_EXPORT double Divided(const double avalue) const override;

  Standard_EXPORT void Dump(const int ashift, const int alevel) const override;

  DEFINE_STANDARD_RTTIEXT(Units_ShiftedToken, Units_Token)

private:
  double themove;
};
