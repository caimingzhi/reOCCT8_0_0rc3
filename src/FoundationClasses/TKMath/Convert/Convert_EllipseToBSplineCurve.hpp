#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Convert_ConicToBSplineCurve.hpp>
#include <Convert_ParameterisationType.hpp>
class gp_Elips2d;

class Convert_EllipseToBSplineCurve : public Convert_ConicToBSplineCurve
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Convert_EllipseToBSplineCurve(
    const gp_Elips2d&                  E,
    const Convert_ParameterisationType Parameterisation = Convert_TgtThetaOver2);

  Standard_EXPORT Convert_EllipseToBSplineCurve(
    const gp_Elips2d&                  E,
    const double                       U1,
    const double                       U2,
    const Convert_ParameterisationType Parameterisation = Convert_TgtThetaOver2);
};
