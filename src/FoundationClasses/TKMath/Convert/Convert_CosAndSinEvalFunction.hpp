#pragma once


#include <gp_Pnt2d.hpp>
#include <NCollection_Array1.hpp>
#include <Standard_Integer.hpp>

typedef void Convert_CosAndSinEvalFunction(double,
                                           const int,
                                           const NCollection_Array1<gp_Pnt2d>&,
                                           const NCollection_Array1<double>&,
                                           const NCollection_Array1<int>*,
                                           double Result[2]);

