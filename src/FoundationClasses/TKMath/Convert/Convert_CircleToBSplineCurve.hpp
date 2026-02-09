#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Convert_ConicToBSplineCurve.hpp>
#include <Convert_ParameterisationType.hpp>
class gp_Circ2d;

class Convert_CircleToBSplineCurve : public Convert_ConicToBSplineCurve
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Convert_CircleToBSplineCurve(
    const gp_Circ2d&                   C,
    const Convert_ParameterisationType Parameterisation = Convert_TgtThetaOver2);

  Standard_EXPORT Convert_CircleToBSplineCurve(
    const gp_Circ2d&                   C,
    const double                       U1,
    const double                       U2,
    const Convert_ParameterisationType Parameterisation = Convert_TgtThetaOver2);
};
