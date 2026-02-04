#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Trsf.hpp>
class gp_Vec;
class gp_Pnt;

//! This class implements elementary construction algorithms for a
//! translation in 3D space. The result is a gp_Trsf transformation.
//! A MakeTranslation object provides a framework for:
//! -   defining the construction of the transformation,
//! -   implementing the construction algorithm, and
//! -   consulting the result.
class gce_MakeTranslation
{
public:
  DEFINE_STANDARD_ALLOC

  //! Constructs a translation along the vector " Vect"
  Standard_EXPORT gce_MakeTranslation(const gp_Vec& Vect);

  //! Constructs a translation along the vector
  //! (Point1,Point2) defined from the point Point1 to the point Point2.
  Standard_EXPORT gce_MakeTranslation(const gp_Pnt& Point1, const gp_Pnt& Point2);

  //! Returns the constructed transformation.
  Standard_EXPORT const gp_Trsf& Value() const;

  Standard_EXPORT const gp_Trsf& Operator() const;
  Standard_EXPORT                operator gp_Trsf() const;

private:
  gp_Trsf TheTranslation;
};

