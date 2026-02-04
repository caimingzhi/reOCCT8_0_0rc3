#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class Geom_Transformation;
class gp_Pnt;
class gp_Ax1;
class gp_Lin;
class gp_Dir;
class gp_Pln;
class gp_Ax2;

//! This class implements elementary construction algorithms for a
//! symmetrical transformation in 3D space about a point,
//! axis or plane. The result is a Geom_Transformation transformation.
//! A MakeMirror object provides a framework for:
//! -   defining the construction of the transformation,
//! -   implementing the construction algorithm, and
//! -   consulting the result.
class GC_MakeMirror
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GC_MakeMirror(const gp_Pnt& Point);

  Standard_EXPORT GC_MakeMirror(const gp_Ax1& Axis);

  Standard_EXPORT GC_MakeMirror(const gp_Lin& Line);

  //! Make a symmetry transformation af axis defined by
  //! <Point> and <Direc>.
  Standard_EXPORT GC_MakeMirror(const gp_Pnt& Point, const gp_Dir& Direc);

  //! Make a symmetry transformation of plane <Plane>.
  Standard_EXPORT GC_MakeMirror(const gp_Pln& Plane);

  //! Make a symmetry transformation of plane <Plane>.
  Standard_EXPORT GC_MakeMirror(const gp_Ax2& Plane);

  //! Returns the constructed transformation.
  Standard_EXPORT const occ::handle<Geom_Transformation>& Value() const;

  operator const occ::handle<Geom_Transformation>&() const { return Value(); }

private:
  occ::handle<Geom_Transformation> TheMirror;
};

