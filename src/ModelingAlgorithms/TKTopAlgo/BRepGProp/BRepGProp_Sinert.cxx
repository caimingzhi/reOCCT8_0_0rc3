

#include <BRepGProp_Domain.hpp>
#include <BRepGProp_Face.hpp>
#include <BRepGProp_Gauss.hpp>
#include <BRepGProp_Sinert.hpp>
#include <gp_Pnt.hpp>

BRepGProp_Sinert::BRepGProp_Sinert()
    : myEpsilon(0.0)
{
}

BRepGProp_Sinert::BRepGProp_Sinert(const BRepGProp_Face& theSurface, const gp_Pnt& theLocation)
{
  SetLocation(theLocation);
  Perform(theSurface);
}

BRepGProp_Sinert::BRepGProp_Sinert(BRepGProp_Face&   theSurface,
                                   BRepGProp_Domain& theDomain,
                                   const gp_Pnt&     theLocation)
{
  SetLocation(theLocation);
  Perform(theSurface, theDomain);
}

BRepGProp_Sinert::BRepGProp_Sinert(BRepGProp_Face& theSurface,
                                   const gp_Pnt&   theLocation,
                                   const double    theEps)
{
  SetLocation(theLocation);
  Perform(theSurface, theEps);
}

BRepGProp_Sinert::BRepGProp_Sinert(BRepGProp_Face&   theSurface,
                                   BRepGProp_Domain& theDomain,
                                   const gp_Pnt&     theLocation,
                                   const double      theEps)
{
  SetLocation(theLocation);
  Perform(theSurface, theDomain, theEps);
}

void BRepGProp_Sinert::SetLocation(const gp_Pnt& theLocation)
{
  loc = theLocation;
}

void BRepGProp_Sinert::Perform(const BRepGProp_Face& theSurface)
{
  myEpsilon = 1.0;

  BRepGProp_Gauss aGauss(BRepGProp_Gauss::Sinert);
  aGauss.Compute(theSurface, loc, dim, g, inertia);
}

void BRepGProp_Sinert::Perform(BRepGProp_Face& theSurface, BRepGProp_Domain& theDomain)
{
  myEpsilon = 1.0;

  BRepGProp_Gauss aGauss(BRepGProp_Gauss::Sinert);
  aGauss.Compute(theSurface, theDomain, loc, dim, g, inertia);
}

double BRepGProp_Sinert::Perform(BRepGProp_Face& theSurface, const double theEps)
{
  BRepGProp_Domain anEmptyDomian;
  return Perform(theSurface, anEmptyDomian, theEps);
}

double BRepGProp_Sinert::Perform(BRepGProp_Face&   theSurface,
                                 BRepGProp_Domain& theDomain,
                                 const double      theEps)
{
  BRepGProp_Gauss aGauss(BRepGProp_Gauss::Sinert);
  return myEpsilon = aGauss.Compute(theSurface, theDomain, loc, theEps, dim, g, inertia);
}

double BRepGProp_Sinert::GetEpsilon()
{
  return myEpsilon;
}
