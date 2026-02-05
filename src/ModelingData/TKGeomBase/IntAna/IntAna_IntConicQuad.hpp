#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Standard_Integer.hpp>
#include <gp_Pnt.hpp>
class gp_Lin;
class IntAna_Quadric;
class gp_Circ;
class gp_Elips;
class gp_Parab;
class gp_Hypr;
class gp_Pln;

//! This class provides the analytic intersection between
//! a conic defined as an element of gp (Lin,Circ,Elips,
//! Parab,Hypr) and a quadric as defined in the class
//! Quadric from IntAna.
//! The intersection between a conic and a plane is treated
//! as a special case.
//!
//! The result of the intersection are points (Pnt from
//! gp), associated with the parameter on the conic.
//!
//! A call to an Intersection L:Lin from gp and
//! SPH: Sphere from gp can be written either:
//! IntAna_IntConicQuad Inter(L,IntAna_Quadric(SPH))
//! or:
//! IntAna_IntConicQuad Inter(L,SPH) (it is necessary
//! to include IntAna_Quadric.hpp in this case)
class IntAna_IntConicQuad
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor.
  Standard_EXPORT IntAna_IntConicQuad();

  //! Creates the intersection between a line and a quadric.
  Standard_EXPORT IntAna_IntConicQuad(const gp_Lin& L, const IntAna_Quadric& Q);

  //! Intersects a line and a quadric.
  Standard_EXPORT void Perform(const gp_Lin& L, const IntAna_Quadric& Q);

  //! Creates the intersection between a circle and a quadric.
  Standard_EXPORT IntAna_IntConicQuad(const gp_Circ& C, const IntAna_Quadric& Q);

  //! Intersects a circle and a quadric.
  Standard_EXPORT void Perform(const gp_Circ& C, const IntAna_Quadric& Q);

  //! Creates the intersection between an ellipse and a quadric.
  Standard_EXPORT IntAna_IntConicQuad(const gp_Elips& E, const IntAna_Quadric& Q);

  //! Intersects an ellipse and a quadric.
  Standard_EXPORT void Perform(const gp_Elips& E, const IntAna_Quadric& Q);

  //! Creates the intersection between a parabola and a quadric.
  Standard_EXPORT IntAna_IntConicQuad(const gp_Parab& P, const IntAna_Quadric& Q);

  //! Intersects a parabola and a quadric.
  Standard_EXPORT void Perform(const gp_Parab& P, const IntAna_Quadric& Q);

  //! Creates the intersection between an hyperbola and
  //! a quadric.
  Standard_EXPORT IntAna_IntConicQuad(const gp_Hypr& H, const IntAna_Quadric& Q);

  //! Intersects an hyperbola and a quadric.
  Standard_EXPORT void Perform(const gp_Hypr& H, const IntAna_Quadric& Q);

  //! Intersection between a line and a plane.
  //! Tolang is used to determine if the angle between two
  //! vectors is null.
  //! Tol is used to check the distance between line and plane
  //! on the distance <Len> from the origin of the line.
  Standard_EXPORT IntAna_IntConicQuad(const gp_Lin& L,
                                      const gp_Pln& P,
                                      const double  Tolang,
                                      const double  Tol = 0,
                                      const double  Len = 0);

  //! Intersects a line and a plane.
  //! Tolang is used to determine if the angle between two
  //! vectors is null.
  //! Tol is used to check the distance between line and plane
  //! on the distance <Len> from the origin of the line.
  Standard_EXPORT void Perform(const gp_Lin& L,
                               const gp_Pln& P,
                               const double  Tolang,
                               const double  Tol = 0,
                               const double  Len = 0);

  //! Intersection between a circle and a plane.
  //! Tolang is used to determine if the angle between two
  //! vectors is null.
  //! Tol is used to determine if a distance is null.
  Standard_EXPORT IntAna_IntConicQuad(const gp_Circ& C,
                                      const gp_Pln&  P,
                                      const double   Tolang,
                                      const double   Tol);

  //! Intersects a circle and a plane.
  //! Tolang is used to determine if the angle between two
  //! vectors is null.
  //! Tol is used to determine if a distance is null.
  Standard_EXPORT void Perform(const gp_Circ& C,
                               const gp_Pln&  P,
                               const double   Tolang,
                               const double   Tol);

  //! Intersection between an ellipse and a plane.
  //! Tolang is used to determine if the angle between two
  //! vectors is null.
  //! Tol is used to determine if a distance is null.
  Standard_EXPORT IntAna_IntConicQuad(const gp_Elips& E,
                                      const gp_Pln&   P,
                                      const double    Tolang,
                                      const double    Tol);

  //! Intersects an ellipse and a plane.
  //! Tolang is used to determine if the angle between two
  //! vectors is null.
  //! Tol is used to determine if a distance is null.
  Standard_EXPORT void Perform(const gp_Elips& E,
                               const gp_Pln&   P,
                               const double    Tolang,
                               const double    Tol);

  //! Intersection between a parabola and a plane.
  //! Tolang is used to determine if the angle between two
  //! vectors is null.
  Standard_EXPORT IntAna_IntConicQuad(const gp_Parab& Pb, const gp_Pln& P, const double Tolang);

  //! Intersects a parabola and a plane.
  //! Tolang is used to determine if the angle between two
  //! vectors is null.
  Standard_EXPORT void Perform(const gp_Parab& Pb, const gp_Pln& P, const double Tolang);

  //! Intersection between an hyperbola and a plane.
  //! Tolang is used to determine if the angle between two
  //! vectors is null.
  Standard_EXPORT IntAna_IntConicQuad(const gp_Hypr& H, const gp_Pln& P, const double Tolang);

  //! Intersects an hyperbola and a plane.
  //! Tolang is used to determine if the angle between two
  //! vectors is null.
  Standard_EXPORT void Perform(const gp_Hypr& H, const gp_Pln& P, const double Tolang);

  //! Returns TRUE if the creation completed.
  bool IsDone() const;

  //! Returns TRUE if the conic is in the quadric.
  bool IsInQuadric() const;

  //! Returns TRUE if the line is in a quadric which
  //! is parallel to the quadric.
  bool IsParallel() const;

  //! Returns the number of intersection point.
  int NbPoints() const;

  //! Returns the point of range N.
  const gp_Pnt& Point(const int N) const;

  //! Returns the parameter on the line of the intersection
  //! point of range N.
  double ParamOnConic(const int N) const;

private:
  bool   done;
  bool   parallel;
  bool   inquadric;
  int    nbpts;
  gp_Pnt pnts[4];
  double paramonc[4];
};

// Copyright (c) 1995-1999 Matra Datavision
// Copyright (c) 1999-2014 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

#include <StdFail_NotDone.hpp>
#include <Standard_DomainError.hpp>
#include <Standard_OutOfRange.hpp>

inline bool IntAna_IntConicQuad::IsDone() const
{
  return (done);
}

inline bool IntAna_IntConicQuad::IsInQuadric() const
{
  if (!done)
  {
    throw StdFail_NotDone();
  }
  return (inquadric);
}

inline bool IntAna_IntConicQuad::IsParallel() const
{
  if (!done)
  {
    throw StdFail_NotDone();
  }
  return (parallel);
}

inline int IntAna_IntConicQuad::NbPoints() const
{
  if (!done)
  {
    throw StdFail_NotDone();
  }
  if (parallel || inquadric)
  {
    throw Standard_DomainError();
  }
  return (nbpts);
}

inline const gp_Pnt& IntAna_IntConicQuad::Point(const int i) const
{

  if (!done)
  {
    throw StdFail_NotDone();
  }
  if (parallel || inquadric)
  {
    throw Standard_DomainError();
  }
  if ((i > nbpts) || (i <= 0))
  {
    throw Standard_OutOfRange();
  }
  return (pnts[i - 1]);
}

inline double IntAna_IntConicQuad::ParamOnConic(const int i) const
{

  if (!done)
  {
    throw StdFail_NotDone();
  }
  if (parallel || inquadric)
  {
    throw Standard_DomainError();
  }
  if ((i > nbpts) || (i <= 0))
  {
    throw Standard_OutOfRange();
  }
  return (paramonc[i - 1]);
}
