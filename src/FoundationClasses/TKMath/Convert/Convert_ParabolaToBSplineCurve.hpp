#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Convert_ConicToBSplineCurve.hpp>
class gp_Parab2d;

class Convert_ParabolaToBSplineCurve : public Convert_ConicToBSplineCurve
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Convert_ParabolaToBSplineCurve(const gp_Parab2d& Prb,
                                                 const double      U1,
                                                 const double      U2);
};
