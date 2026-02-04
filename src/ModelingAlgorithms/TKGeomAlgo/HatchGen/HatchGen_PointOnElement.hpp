#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>
// Created on: 1993-10-25
// Created by: Jean Marc LACHAUME
// Copyright (c) 1993-1999 Matra Datavision
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


//! Intersection type between the hatching and the
//! element.
enum HatchGen_IntersectionType
{
  HatchGen_TRUE,
  HatchGen_TOUCH,
  HatchGen_TANGENT,
  HatchGen_UNDETERMINED
};


#include <HatchGen_IntersectionPoint.hpp>
#include <Standard_Boolean.hpp>
#include <Standard_Real.hpp>
class IntRes2d_IntersectionPoint;

class HatchGen_PointOnElement : public HatchGen_IntersectionPoint
{
public:
  DEFINE_STANDARD_ALLOC

  //! ---Purpose; Creates an empty point on element
  Standard_EXPORT HatchGen_PointOnElement();

  //! Creates a point from an intersection point.
  Standard_EXPORT HatchGen_PointOnElement(const IntRes2d_IntersectionPoint& Point);

  //! Sets the intersection type at this point.
  void SetIntersectionType(const HatchGen_IntersectionType Type);

  //! Returns the intersection type at this point.
  HatchGen_IntersectionType IntersectionType() const;

  //! Tests if the point is identical to an other.
  //! That is to say :
  //! P1.myIndex  = P2.myIndex
  //! Abs (P1.myParam - P2.myParam) <= Confusion
  //! P1.myPosit  = P2.myPosit
  //! P1.myBefore = P2.myBefore
  //! P1.myAfter  = P2.myAfter
  //! P1.mySegBeg = P2.mySegBeg
  //! P1.mySegEnd = P2.mySegEnd
  //! P1.myType   = P2.myType
  Standard_EXPORT bool IsIdentical(const HatchGen_PointOnElement& Point,
                                   const double                   Confusion) const;

  //! Tests if the point is different from an other.
  Standard_EXPORT bool IsDifferent(const HatchGen_PointOnElement& Point,
                                   const double                   Confusion) const;

  //! Dump of the point on element.
  Standard_EXPORT void Dump(const int Index = 0) const override;

protected:
  HatchGen_IntersectionType myType;
};
// Created on: 1995-01-03
// Created by: Laurent BUCHARD
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

//=======================================================================
// Function : SetIntersectionType
// Purpose  : Sets the intersection type at this point.
//=======================================================================

inline void HatchGen_PointOnElement::SetIntersectionType(const HatchGen_IntersectionType Type)
{
  myType = Type;
}

//=======================================================================
// Function : IntersectionType
// Purpose  : Returns the intersection type at this point.
//=======================================================================

inline HatchGen_IntersectionType HatchGen_PointOnElement::IntersectionType() const
{
  return myType;
}


