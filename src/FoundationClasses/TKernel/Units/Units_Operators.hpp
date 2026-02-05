#pragma once

#include <Units_Token.hpp>
#include <Units_Quantity.hpp>

Standard_EXPORT bool operator==(const occ::handle<Units_Quantity>&, const char*);
Standard_EXPORT bool operator==(const occ::handle<Units_Token>&, const char*);
Standard_EXPORT bool operator==(const occ::handle<Units_Unit>&, const char*);

Standard_EXPORT occ::handle<Units_Dimensions> operator*(const occ::handle<Units_Dimensions>&,
                                                        const occ::handle<Units_Dimensions>&);
Standard_EXPORT occ::handle<Units_Dimensions> operator/(const occ::handle<Units_Dimensions>&,
                                                        const occ::handle<Units_Dimensions>&);

Standard_EXPORT occ::handle<Units_Dimensions> pow(const occ::handle<Units_Dimensions>&,
                                                  const double);
Standard_EXPORT occ::handle<Units_Token> pow(const occ::handle<Units_Token>&,
                                             const occ::handle<Units_Token>&);
Standard_EXPORT occ::handle<Units_Token> pow(const occ::handle<Units_Token>&, const double);

Standard_EXPORT occ::handle<Units_Token> operator+(const occ::handle<Units_Token>&, const int);
Standard_EXPORT occ::handle<Units_Token> operator+(const occ::handle<Units_Token>&,
                                                   const occ::handle<Units_Token>&);
Standard_EXPORT occ::handle<Units_Token> operator-(const occ::handle<Units_Token>&,
                                                   const occ::handle<Units_Token>&);
Standard_EXPORT occ::handle<Units_Token> operator*(const occ::handle<Units_Token>&,
                                                   const occ::handle<Units_Token>&);
Standard_EXPORT occ::handle<Units_Token> operator/(const occ::handle<Units_Token>&,
                                                   const occ::handle<Units_Token>&);

Standard_EXPORT bool operator!=(const occ::handle<Units_Token>&, const char*);
Standard_EXPORT bool operator<=(const occ::handle<Units_Token>&, const char*);
Standard_EXPORT bool operator>(const occ::handle<Units_Token>&, const char*);
Standard_EXPORT bool operator>(const occ::handle<Units_Token>&, const occ::handle<Units_Token>&);
Standard_EXPORT bool operator>=(const occ::handle<Units_Token>&, const occ::handle<Units_Token>&);
