#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_XYZ.hpp>
#include <Standard_Real.hpp>
#include <Standard_Boolean.hpp>

class Bnd_Sphere
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Bnd_Sphere();

  Standard_EXPORT Bnd_Sphere(const gp_XYZ& theCntr,
                             const double  theRad,
                             const int     theU,
                             const int     theV);

  int U() const;

  int V() const;

  bool IsValid() const;

  void SetValid(const bool isValid);

  const gp_XYZ& Center() const;

  double Radius() const;

  Standard_EXPORT void Distances(const gp_XYZ& theXYZ, double& theMin, double& theMax) const;

  Standard_EXPORT void SquareDistances(const gp_XYZ& theXYZ, double& theMin, double& theMax) const;

  Standard_EXPORT bool Project(const gp_XYZ& theNode,
                               gp_XYZ&       theProjNode,
                               double&       theDist,
                               bool&         theInside) const;

  Standard_EXPORT double Distance(const gp_XYZ& theNode) const;

  Standard_EXPORT double SquareDistance(const gp_XYZ& theNode) const;

  Standard_EXPORT void Add(const Bnd_Sphere& theOther);

  Standard_EXPORT bool IsOut(const Bnd_Sphere& theOther) const;

  Standard_EXPORT bool IsOut(const gp_XYZ& thePnt, double& theMaxDist) const;

  Standard_EXPORT double SquareExtent() const;

private:
  gp_XYZ myCenter;
  double myRadius;
  bool   myIsValid;
  int    myU;
  int    myV;
};

inline int Bnd_Sphere::U() const
{
  return myU;
}

inline int Bnd_Sphere::V() const
{
  return myV;
}

inline bool Bnd_Sphere::IsValid() const
{
  return myIsValid;
}

inline void Bnd_Sphere::SetValid(const bool isValid)
{
  myIsValid = isValid;
}

inline const gp_XYZ& Bnd_Sphere::Center() const
{
  return myCenter;
}

inline double Bnd_Sphere::Radius() const
{
  return myRadius;
}
