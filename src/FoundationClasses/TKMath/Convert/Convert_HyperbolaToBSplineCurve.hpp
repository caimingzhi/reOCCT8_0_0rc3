#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Convert_ConicToBSplineCurve.hpp>
class gp_Hypr2d;

class Convert_HyperbolaToBSplineCurve : public Convert_ConicToBSplineCurve
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Convert_HyperbolaToBSplineCurve(const gp_Hypr2d& H,
                                                  const double     U1,
                                                  const double     U2);
};
