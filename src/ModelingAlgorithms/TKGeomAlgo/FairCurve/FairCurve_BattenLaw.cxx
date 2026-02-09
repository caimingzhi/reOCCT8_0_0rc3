

#include <FairCurve_BattenLaw.hpp>

FairCurve_BattenLaw::FairCurve_BattenLaw(const double Heigth,
                                         const double Slope,
                                         const double Sliding)
    : MiddleHeigth(Heigth),
      GeometricSlope(Slope),
      LengthSliding(Sliding)
{
}
