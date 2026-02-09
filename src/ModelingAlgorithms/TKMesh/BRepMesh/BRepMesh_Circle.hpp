#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <gp_XY.hpp>

class BRepMesh_Circle
{
public:
  DEFINE_STANDARD_ALLOC

  BRepMesh_Circle()
      : myRadius(0.0)
  {
  }

  BRepMesh_Circle(const gp_XY& theLocation, const double theRadius)
      : myLocation(theLocation),
        myRadius(theRadius)
  {
  }

  void SetLocation(const gp_XY& theLocation) { myLocation = theLocation; }

  void SetRadius(const double theRadius) { myRadius = theRadius; }

  const gp_XY& Location() const { return myLocation; }

  const double& Radius() const { return myRadius; }

private:
  gp_XY  myLocation;
  double myRadius;
};
