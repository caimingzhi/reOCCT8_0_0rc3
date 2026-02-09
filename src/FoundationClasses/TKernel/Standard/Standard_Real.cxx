

#include <cfloat>
#include <Standard_Real.hpp>

inline double apx_for_ACosApprox(const double theValue)
{
  return (-0.000007239283986332
          + theValue
              * (2.000291665285952400
                 + theValue
                     * (0.163910606547823220
                        + theValue
                            * (0.047654245891495528
                               - theValue
                                   * (0.005516443930088506 + 0.015098965761299077 * theValue)))))
         / sqrt(2 * theValue);
}

double ACosApprox(const double theValue)
{
  if (theValue < 0.)
  {
    const double theX = 1. + theValue;
    return theX < RealSmall() ? 0. : M_PI - apx_for_ACosApprox(theX);
  }
  else
  {
    const double theX = 1. - theValue;
    return theX < RealSmall() ? 0. : apx_for_ACosApprox(theX);
  }
}
