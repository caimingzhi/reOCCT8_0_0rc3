#pragma once


#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Integer.hpp>

void BuildPolynomialCosAndSin(const double,
                              const double,
                              const int,
                              occ::handle<NCollection_HArray1<double>>&,
                              occ::handle<NCollection_HArray1<double>>&,
                              occ::handle<NCollection_HArray1<double>>&);

