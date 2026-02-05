#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class Geom2d_Transformation;
class gp_Pnt2d;
class gp_Ax2d;
class gp_Lin2d;
class gp_Dir2d;

//! This class implements elementary construction algorithms for a
//! symmetrical transformation in 2D space about a point
//! or axis. The result is a Geom2d_Transformation transformation.
//! A MakeMirror object provides a framework for:
//! -   defining the construction of the transformation,
//! -   implementing the construction algorithm, and
//! -   consulting the result.
class GCE2d_MakeMirror
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GCE2d_MakeMirror(const gp_Pnt2d& Point);

  Standard_EXPORT GCE2d_MakeMirror(const gp_Ax2d& Axis);

  Standard_EXPORT GCE2d_MakeMirror(const gp_Lin2d& Line);

  //! Make a symmetry transformation af axis defined by
  //! <Point> and <Direc>.
  Standard_EXPORT GCE2d_MakeMirror(const gp_Pnt2d& Point, const gp_Dir2d& Direc);

  //! Returns the constructed transformation.
  Standard_EXPORT const occ::handle<Geom2d_Transformation>& Value() const;

  operator const occ::handle<Geom2d_Transformation>&() const { return Value(); }

private:
  occ::handle<Geom2d_Transformation> TheMirror;
};
