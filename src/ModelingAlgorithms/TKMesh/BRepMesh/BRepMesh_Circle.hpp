#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <gp_XY.hpp>

//! Describes a 2d circle with a size of only 3 double
//! numbers instead of gp who needs 7 double numbers.
class BRepMesh_Circle
{
public:
  DEFINE_STANDARD_ALLOC

  //! Default constructor.
  BRepMesh_Circle()
      : myRadius(0.0)
  {
  }

  //! Constructor.
  //! @param theLocation location of a circle.
  //! @param theRadius radius of a circle.
  BRepMesh_Circle(const gp_XY& theLocation, const double theRadius)
      : myLocation(theLocation),
        myRadius(theRadius)
  {
  }

  //! Sets location of a circle.
  //! @param theLocation location of a circle.
  void SetLocation(const gp_XY& theLocation) { myLocation = theLocation; }

  //! Sets radius of a circle.
  //! @param theRadius radius of a circle.
  void SetRadius(const double theRadius) { myRadius = theRadius; }

  //! Returns location of a circle.
  const gp_XY& Location() const { return myLocation; }

  //! Returns radius of a circle.
  const double& Radius() const { return myRadius; }

private:
  gp_XY  myLocation;
  double myRadius;
};
