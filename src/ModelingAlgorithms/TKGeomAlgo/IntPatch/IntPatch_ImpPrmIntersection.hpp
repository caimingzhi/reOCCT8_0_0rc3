#pragma once


#include <Adaptor3d_Surface.hpp>
#include <IntPatch_Point.hpp>
#include <NCollection_Sequence.hpp>
#include <IntPatch_Line.hpp>
#include <IntPatch_TheSOnBounds.hpp>
#include <IntPatch_TheSearchInside.hpp>

class Adaptor3d_TopolTool;

//! Implementation of the intersection between a natural
//! quadric patch : Plane, Cone, Cylinder or Sphere and
//! a bi-parametrised surface.
class IntPatch_ImpPrmIntersection
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IntPatch_ImpPrmIntersection();

  Standard_EXPORT IntPatch_ImpPrmIntersection(const occ::handle<Adaptor3d_Surface>&   Surf1,
                                              const occ::handle<Adaptor3d_TopolTool>& D1,
                                              const occ::handle<Adaptor3d_Surface>&   Surf2,
                                              const occ::handle<Adaptor3d_TopolTool>& D2,
                                              const double                            TolArc,
                                              const double                            TolTang,
                                              const double                            Fleche,
                                              const double                            Pas);

  //! to search for solution from the given point
  Standard_EXPORT void SetStartPoint(const double U, const double V);

  Standard_EXPORT void Perform(const occ::handle<Adaptor3d_Surface>&   Surf1,
                               const occ::handle<Adaptor3d_TopolTool>& D1,
                               const occ::handle<Adaptor3d_Surface>&   Surf2,
                               const occ::handle<Adaptor3d_TopolTool>& D2,
                               const double                            TolArc,
                               const double                            TolTang,
                               const double                            Fleche,
                               const double                            Pas);

  //! Returns true if the calculus was successful.
  bool IsDone() const;

  //! Returns true if the is no intersection.
  bool IsEmpty() const;

  //! Returns the number of "single" points.
  int NbPnts() const;

  //! Returns the point of range Index.
  //! An exception is raised if Index<=0 or Index>NbPnt.
  const IntPatch_Point& Point(const int Index) const;

  //! Returns the number of intersection lines.
  int NbLines() const;

  //! Returns the line of range Index.
  //! An exception is raised if Index<=0 or Index>NbLine.
  const occ::handle<IntPatch_Line>& Line(const int Index) const;

private:
  bool                                             done;
  bool                                             empt;
  NCollection_Sequence<IntPatch_Point>             spnt;
  NCollection_Sequence<occ::handle<IntPatch_Line>> slin;
  IntPatch_TheSOnBounds                            solrst;
  IntPatch_TheSearchInside                         solins;
  bool                                             myIsStartPnt;
  double                                           myUStart;
  double                                           myVStart;
};
// Created on: 1992-05-07
// Created by: Jacques GOUSSARD
// Copyright (c) 1992-1999 Matra Datavision
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
#include <IntPatch_Line.hpp>

inline bool IntPatch_ImpPrmIntersection::IsDone() const
{
  return done;
}

inline bool IntPatch_ImpPrmIntersection::IsEmpty() const
{
  if (!done)
  {
    throw StdFail_NotDone();
  }
  return empt;
}

inline int IntPatch_ImpPrmIntersection::NbPnts() const
{
  if (!done)
  {
    throw StdFail_NotDone();
  }
  return spnt.Length();
}

inline const IntPatch_Point& IntPatch_ImpPrmIntersection::Point(const int Index) const
{
  if (!done)
  {
    throw StdFail_NotDone();
  }
  return spnt(Index);
}

inline int IntPatch_ImpPrmIntersection::NbLines() const
{
  if (!done)
  {
    throw StdFail_NotDone();
  }
  return slin.Length();
}

inline const occ::handle<IntPatch_Line>& IntPatch_ImpPrmIntersection::Line(const int Index) const
{
  if (!done)
  {
    throw StdFail_NotDone();
  }
  return slin(Index);
}


