#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class Units_Token;

class Units_Measurement
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Units_Measurement();

  Standard_EXPORT Units_Measurement(const double avalue, const occ::handle<Units_Token>& atoken);

  Standard_EXPORT Units_Measurement(const double avalue, const char* aunit);

  Standard_EXPORT void Convert(const char* aunit);

  Standard_EXPORT Units_Measurement Integer() const;

  Standard_EXPORT Units_Measurement Fractional() const;

  Standard_EXPORT double Measurement() const;

  Standard_EXPORT occ::handle<Units_Token> Token() const;

  Standard_EXPORT Units_Measurement Add(const Units_Measurement& ameasurement) const;

  Units_Measurement operator+(const Units_Measurement& ameasurement) const
  {
    return Add(ameasurement);
  }

  Standard_EXPORT Units_Measurement Subtract(const Units_Measurement& ameasurement) const;

  Units_Measurement operator-(const Units_Measurement& ameasurement) const
  {
    return Subtract(ameasurement);
  }

  Standard_EXPORT Units_Measurement Multiply(const Units_Measurement& ameasurement) const;

  Units_Measurement operator*(const Units_Measurement& ameasurement) const
  {
    return Multiply(ameasurement);
  }

  Standard_EXPORT Units_Measurement Multiply(const double avalue) const;

  Units_Measurement operator*(const double avalue) const { return Multiply(avalue); }

  Standard_EXPORT Units_Measurement Divide(const Units_Measurement& ameasurement) const;

  Units_Measurement operator/(const Units_Measurement& ameasurement) const
  {
    return Divide(ameasurement);
  }

  Standard_EXPORT Units_Measurement Divide(const double avalue) const;

  Units_Measurement operator/(const double avalue) const { return Divide(avalue); }

  Standard_EXPORT Units_Measurement Power(const double anexponent) const;

  Standard_EXPORT bool HasToken() const;

  Standard_EXPORT void Dump() const;

private:
  double                   themeasurement;
  occ::handle<Units_Token> thetoken;
  bool                     myHasToken;
};
