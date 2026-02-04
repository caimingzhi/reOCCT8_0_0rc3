#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class Geom_Transformation;
class gp_Vec;
class gp_Pnt;

//! This class implements elementary construction algorithms for a
//! translation in 3D space. The result is a
//! Geom_Transformation transformation.
//! A MakeTranslation object provides a framework for:
//! -   defining the construction of the transformation,
//! -   implementing the construction algorithm, and
//! -   consulting the result.
class GC_MakeTranslation
{
public:
  DEFINE_STANDARD_ALLOC

  //! Constructs a translation along the vector " Vect "
  Standard_EXPORT GC_MakeTranslation(const gp_Vec& Vect);

  //! Constructs a translation along the vector (Point1,Point2)
  //! defined from the point Point1 to the point Point2.
  Standard_EXPORT GC_MakeTranslation(const gp_Pnt& Point1, const gp_Pnt& Point2);

  //! Returns the constructed transformation.
  Standard_EXPORT const occ::handle<Geom_Transformation>& Value() const;

  operator const occ::handle<Geom_Transformation>&() const { return Value(); }

private:
  occ::handle<Geom_Transformation> TheTranslation;
};

