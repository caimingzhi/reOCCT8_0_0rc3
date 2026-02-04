#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Law_BSpFunc.hpp>
#include <gp_Pnt2d.hpp>
#include <NCollection_Array1.hpp>

//! Provides an evolution law that interpolates a set
//! of parameter and value pairs (wi, radi)
class Law_Interpol : public Law_BSpFunc
{

public:
  //! Constructs an empty interpolative evolution law.
  //! The function Set is used to define the law.
  Standard_EXPORT Law_Interpol();

  //! Defines this evolution law by interpolating the set of 2D
  //! points ParAndRad. The Y coordinate of a point of
  //! ParAndRad is the value of the function at the parameter
  //! point given by its X coordinate.
  //! If Periodic is true, this function is assumed to be periodic.
  //! Warning
  //! -   The X coordinates of points in the table ParAndRad
  //! must be given in ascendant order.
  //! -   If Periodic is true, the first and last Y coordinates of
  //! points in the table ParAndRad are assumed to be
  //! equal. In addition, with the second syntax, Dd and Df
  //! are also assumed to be equal. If this is not the case,
  //! Set uses the first value(s) as last value(s).
  Standard_EXPORT void Set(const NCollection_Array1<gp_Pnt2d>& ParAndRad,
                           const bool                          Periodic = false);

  Standard_EXPORT void SetInRelative(const NCollection_Array1<gp_Pnt2d>& ParAndRad,
                                     const double                        Ud,
                                     const double                        Uf,
                                     const bool                          Periodic = false);

  //! Defines this evolution law by interpolating the set of 2D
  //! points ParAndRad. The Y coordinate of a point of
  //! ParAndRad is the value of the function at the parameter
  //! point given by its X coordinate.
  //! If Periodic is true, this function is assumed to be periodic.
  //! In the second syntax, Dd and Df define the values of
  //! the first derivative of the function at its first and last points.
  //! Warning
  //! -   The X coordinates of points in the table ParAndRad
  //! must be given in ascendant order.
  //! -   If Periodic is true, the first and last Y coordinates of
  //! points in the table ParAndRad are assumed to be
  //! equal. In addition, with the second syntax, Dd and Df
  //! are also assumed to be equal. If this is not the case,
  //! Set uses the first value(s) as last value(s).
  Standard_EXPORT void Set(const NCollection_Array1<gp_Pnt2d>& ParAndRad,
                           const double                        Dd,
                           const double                        Df,
                           const bool                          Periodic = false);

  Standard_EXPORT void SetInRelative(const NCollection_Array1<gp_Pnt2d>& ParAndRad,
                                     const double                        Ud,
                                     const double                        Uf,
                                     const double                        Dd,
                                     const double                        Df,
                                     const bool                          Periodic = false);

  DEFINE_STANDARD_RTTIEXT(Law_Interpol, Law_BSpFunc)
};

