#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BRepPrim_Revolution.hpp>
class gp_Ax2;
class gp_Pnt;
class TopoDS_Face;

//! Implements the torus primitive
class BRepPrim_Torus : public BRepPrim_Revolution
{
public:
  DEFINE_STANDARD_ALLOC

  //! the STEP definition
  //! Position : center and axes
  //! Major, Minor : Radii
  //!
  //! Errors : Major < Resolution
  //! Minor < Resolution
  Standard_EXPORT BRepPrim_Torus(const gp_Ax2& Position, const double Major, const double Minor);

  //! Torus centered at origin
  Standard_EXPORT BRepPrim_Torus(const double Major, const double Minor);

  //! Torus at Center
  Standard_EXPORT BRepPrim_Torus(const gp_Pnt& Center, const double Major, const double Minor);

  //! The surface normal should be directed towards the
  //! outside.
  Standard_EXPORT TopoDS_Face MakeEmptyLateralFace() const override;

private:
  Standard_EXPORT void SetMeridian();

  double myMajor; //!< distance from the center of the pipe to the center of the torus
  double myMinor; //!< radius of the pipe
};

