#include <CSLib_NormalPolyDef.hpp>
#include <PLib.hpp>

#include <cmath>

CSLib_NormalPolyDef::CSLib_NormalPolyDef(const int theK0, const NCollection_Array1<double>& theLi)
    : myK0(theK0),
      myTABli(0, theK0)
{
  for (int i = 0; i <= theK0; ++i)
  {
    myTABli(i) = theLi(i);
  }
}

bool CSLib_NormalPolyDef::Value(const double theX, double& theF)
{
  theF = 0.0;

  const double aCos = std::cos(theX);
  const double aSin = std::sin(theX);

  if (std::abs(aCos) <= RealSmall() || std::abs(aSin) <= RealSmall())
  {
    return true;
  }

  for (int i = 0; i <= myK0; ++i)
  {
    theF += PLib::Bin(myK0, i) * std::pow(aCos, i) * std::pow(aSin, myK0 - i) * myTABli(i);
  }

  return true;
}

bool CSLib_NormalPolyDef::Derivative(const double theX, double& theD)
{
  theD = 0.0;

  const double aCos = std::cos(theX);
  const double aSin = std::sin(theX);

  if (std::abs(aCos) <= RealSmall() || std::abs(aSin) <= RealSmall())
  {
    return true;
  }

  for (int i = 0; i <= myK0; ++i)
  {
    theD += PLib::Bin(myK0, i) * std::pow(aCos, i - 1) * std::pow(aSin, myK0 - i - 1)
            * (myK0 * aCos * aCos - i) * myTABli(i);
  }

  return true;
}

bool CSLib_NormalPolyDef::Values(const double theX, double& theF, double& theD)
{
  theF = 0.0;
  theD = 0.0;

  const double aCos = std::cos(theX);
  const double aSin = std::sin(theX);

  if (std::abs(aCos) <= RealSmall() || std::abs(aSin) <= RealSmall())
  {
    return true;
  }

  for (int i = 0; i <= myK0; ++i)
  {
    const double aBinCoeff = PLib::Bin(myK0, i);
    const double aLiCoeff  = myTABli(i);

    theF += aBinCoeff * std::pow(aCos, i) * std::pow(aSin, myK0 - i) * aLiCoeff;
    theD += aBinCoeff * std::pow(aCos, i - 1) * std::pow(aSin, myK0 - i - 1)
            * (myK0 * aCos * aCos - i) * aLiCoeff;
  }

  return true;
}
