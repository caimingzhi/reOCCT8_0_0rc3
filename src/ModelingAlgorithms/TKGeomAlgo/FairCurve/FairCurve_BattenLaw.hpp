#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Real.hpp>
#include <math_Function.hpp>
#include <Standard_Boolean.hpp>

//! This class compute the Heigth of an batten
class FairCurve_BattenLaw : public math_Function
{
public:
  DEFINE_STANDARD_ALLOC

  //! Constructor of linear batten with
  //! Heigth  : the Heigth at the middle point
  //! Slope   : the geometric slope of the batten
  //! Sliding : Active Length of the batten without extension
  Standard_EXPORT FairCurve_BattenLaw(const double Heigth,
                                      const double Slope,
                                      const double Sliding);

  //! Change the value of sliding
  void SetSliding(const double Sliding);

  //! Change the value of Heigth at the middle point.
  void SetHeigth(const double Heigth);

  //! Change the value of the geometric slope.
  void SetSlope(const double Slope);

  //! computes the value of the heigth for the parameter T
  //! on the neutral fibber
  bool Value(const double T, double& THeigth) override;

private:
  double MiddleHeigth;
  double GeometricSlope;
  double LengthSliding;
};

inline void FairCurve_BattenLaw::SetSliding(const double Sliding)
{
  LengthSliding = Sliding;
}

inline void FairCurve_BattenLaw::SetHeigth(const double Heigth)
{
  MiddleHeigth = Heigth;
}

inline void FairCurve_BattenLaw::SetSlope(const double Slope)
{
  GeometricSlope = Slope;
}

inline bool FairCurve_BattenLaw::Value(const double T, double& THeigth)
{
  THeigth = MiddleHeigth + (T - 0.5) * GeometricSlope * LengthSliding;
  return (THeigth > 0);
}
