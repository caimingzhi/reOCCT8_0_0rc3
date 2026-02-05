#include <GeomInt.hpp>

//=================================================================================================

bool GeomInt::AdjustPeriodic(const double thePar,
                             const double theParMin,
                             const double theParMax,
                             const double thePeriod,
                             double&      theNewPar,
                             double&      theOffset,
                             const double theEps)
{
  bool bMin, bMax;
  //
  theOffset = 0.;
  theNewPar = thePar;
  bMin      = theParMin - thePar > theEps;
  bMax      = thePar - theParMax > theEps;
  //
  if (bMin || bMax)
  {
    double dp, aNbPer;
    //
    dp = (bMin) ? (theParMax - thePar) : (theParMin - thePar);
    modf(dp / thePeriod, &aNbPer);
    //
    theOffset = aNbPer * thePeriod;
    theNewPar += theOffset;
  }
  //
  return (theOffset > 0.);
}
