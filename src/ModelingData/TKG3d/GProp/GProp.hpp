#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Real.hpp>
class gp_Pnt;
class gp_Mat;

class GProp
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void HOperator(const gp_Pnt& G,
                                        const gp_Pnt& Q,
                                        const double  Mass,
                                        gp_Mat&       Operator);
};
