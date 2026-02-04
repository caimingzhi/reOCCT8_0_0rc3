#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Intf_Polygon2d.hpp>
class gp_Pnt2d;

class IntPatch_Polygo : public Intf_Polygon2d
{
public:
  DEFINE_STANDARD_ALLOC

  double Error() const;

  Standard_EXPORT virtual int NbPoints() const = 0;

  Standard_EXPORT virtual gp_Pnt2d Point(const int Index) const = 0;

  //! Returns the tolerance of the polygon.
  double DeflectionOverEstimation() const override;

  //! Returns the number of Segments in the polyline.
  int NbSegments() const override;

  //! Returns the points of the segment <Index> in the Polygon.
  void Segment(const int theIndex, gp_Pnt2d& theBegin, gp_Pnt2d& theEnd) const override;

  Standard_EXPORT void Dump() const;

protected:
  Standard_EXPORT IntPatch_Polygo(const double theError = 0.0);

  double myError;
};
// Created on: 2012-02-10
// Created by: Sergey ZERCHANINOV
// Copyright (c) 2012-2014 OPEN CASCADE SAS
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

//=================================================================================================

inline double IntPatch_Polygo::Error() const
{
  return myError;
}

//=================================================================================================

inline double IntPatch_Polygo::DeflectionOverEstimation() const
{
  return myError;
}

//=================================================================================================

inline int IntPatch_Polygo::NbSegments() const
{
  return NbPoints() - 1;
}

//=================================================================================================

inline void IntPatch_Polygo::Segment(const int theIndex, gp_Pnt2d& theBegin, gp_Pnt2d& theEnd) const
{
  theBegin = Point(theIndex);
  theEnd   = Point(theIndex + 1);
}


