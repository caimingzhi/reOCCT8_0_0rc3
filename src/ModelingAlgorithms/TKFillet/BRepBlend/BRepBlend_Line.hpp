#pragma once


#include <Blend_Point.hpp>
#include <NCollection_Sequence.hpp>
#include <BRepBlend_Extremity.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Integer.hpp>

class Blend_Point;

class BRepBlend_Line : public Standard_Transient
{

public:
  Standard_EXPORT BRepBlend_Line();

  //! Clears the content of the line.
  Standard_EXPORT void Clear();

  //! Adds a point in the line.
  void Append(const Blend_Point& P);

  //! Adds a point in the line at the first place.
  void Prepend(const Blend_Point& P);

  //! Adds a point in the line at the first place.
  void InsertBefore(const int Index, const Blend_Point& P);

  //! Removes from <me> all the items of
  //! positions between <FromIndex> and <ToIndex>.
  //! Raises an exception if the indices are out of bounds.
  void Remove(const int FromIndex, const int ToIndex);

  //! Sets the value of the transition of the line on S1 and
  //! the line on S2.
  Standard_EXPORT void Set(const IntSurf_TypeTrans TranS1, const IntSurf_TypeTrans TranS2);

  //! Sets the value of the transition of the line on a surface
  Standard_EXPORT void Set(const IntSurf_TypeTrans Trans);

  //! Sets the values of the start points for the line.
  void SetStartPoints(const BRepBlend_Extremity& StartPt1, const BRepBlend_Extremity& StartPt2);

  //! Sets tne values of the end points for the line.
  void SetEndPoints(const BRepBlend_Extremity& EndPt1, const BRepBlend_Extremity& EndPt2);

  //! Returns the number of points in the line.
  int NbPoints() const;

  //! Returns the point of range Index.
  const Blend_Point& Point(const int Index) const;

  //! Returns the type of the transition of the line defined
  //! on the first surface. The transition is "constant"
  //! along the line.
  //! The transition is IN if the line is oriented in such
  //! a way that the system of vectors (N,DRac,T) is
  //! right-handed, where
  //! N is the normal to the first surface at a point P,
  //! DRac is a vector tangent to the blending patch,
  //! oriented towards the valid part of this patch,
  //! T is the tangent to the line on S1 at P.
  //! The transitioon is OUT when the system of vectors is
  //! left-handed.
  IntSurf_TypeTrans TransitionOnS1() const;

  //! Returns the type of the transition of the line defined
  //! on the second surface. The transition is "constant"
  //! along the line.
  IntSurf_TypeTrans TransitionOnS2() const;

  //! Returns the start point on S1.
  const BRepBlend_Extremity& StartPointOnFirst() const;

  //! Returns the start point on S2
  const BRepBlend_Extremity& StartPointOnSecond() const;

  //! Returns the end point on S1.
  const BRepBlend_Extremity& EndPointOnFirst() const;

  //! Returns the point on S2.
  const BRepBlend_Extremity& EndPointOnSecond() const;

  //! Returns the type of the transition of the line defined
  //! on the surface.
  IntSurf_TypeTrans TransitionOnS() const;

  DEFINE_STANDARD_RTTIEXT(BRepBlend_Line, Standard_Transient)

private:
  NCollection_Sequence<Blend_Point> seqpt;
  IntSurf_TypeTrans                 tras1;
  IntSurf_TypeTrans                 tras2;
  BRepBlend_Extremity               stp1;
  BRepBlend_Extremity               stp2;
  BRepBlend_Extremity               endp1;
  BRepBlend_Extremity               endp2;
  bool                              hass1;
  bool                              hass2;
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

#include <Blend_Point.hpp>
#include <NCollection_Sequence.hpp>
#include <Standard_DomainError.hpp>

inline void BRepBlend_Line::Append(const Blend_Point& P)
{
  seqpt.Append(P);
}

inline void BRepBlend_Line::Prepend(const Blend_Point& P)
{
  seqpt.Prepend(P);
}

inline void BRepBlend_Line::InsertBefore(const int Index, const Blend_Point& P)
{
  seqpt.InsertBefore(Index, P);
}

inline void BRepBlend_Line::Remove(const int FromIndex, const int ToIndex)
{
  seqpt.Remove(FromIndex, ToIndex);
}

inline void BRepBlend_Line::SetStartPoints(const BRepBlend_Extremity& StartPtOnS1,
                                           const BRepBlend_Extremity& StartPtOnS2)

{
  stp1 = StartPtOnS1;
  stp2 = StartPtOnS2;
}

inline void BRepBlend_Line::SetEndPoints(const BRepBlend_Extremity& EndPtOnS1,
                                         const BRepBlend_Extremity& EndPtOnS2)

{
  endp1 = EndPtOnS1;
  endp2 = EndPtOnS2;
}

inline int BRepBlend_Line::NbPoints() const
{
  return seqpt.Length();
}

inline const Blend_Point& BRepBlend_Line::Point(const int Index) const
{
  return seqpt(Index);
}

inline IntSurf_TypeTrans BRepBlend_Line::TransitionOnS1() const
{
  if (!hass1)
  {
    throw Standard_DomainError();
  }
  return tras1;
}

inline IntSurf_TypeTrans BRepBlend_Line::TransitionOnS2() const
{
  if (!hass2)
  {
    throw Standard_DomainError();
  }
  return tras2;
}

inline const BRepBlend_Extremity& BRepBlend_Line::StartPointOnFirst() const
{
  return stp1;
}

inline const BRepBlend_Extremity& BRepBlend_Line::StartPointOnSecond() const
{
  return stp2;
}

inline const BRepBlend_Extremity& BRepBlend_Line::EndPointOnFirst() const
{
  return endp1;
}

inline const BRepBlend_Extremity& BRepBlend_Line::EndPointOnSecond() const
{
  return endp2;
}

inline IntSurf_TypeTrans BRepBlend_Line::TransitionOnS() const
{
  if (!hass1)
  {
    throw Standard_DomainError();
  }
  return tras1;
}


