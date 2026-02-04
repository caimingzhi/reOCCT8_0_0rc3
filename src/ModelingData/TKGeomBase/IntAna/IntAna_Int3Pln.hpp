#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <gp_Pnt.hpp>
class gp_Pln;

//! Intersection between 3 planes. The algorithm searches
//! for an intersection point. If two of the planes are
//! parallel or identical, IsEmpty returns TRUE.
class IntAna_Int3Pln
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IntAna_Int3Pln();

  //! Determination of the intersection point between
  //! 3 planes.
  Standard_EXPORT IntAna_Int3Pln(const gp_Pln& P1, const gp_Pln& P2, const gp_Pln& P3);

  //! Determination of the intersection point between
  //! 3 planes.
  Standard_EXPORT void Perform(const gp_Pln& P1, const gp_Pln& P2, const gp_Pln& P3);

  //! Returns True if the computation was successful.
  bool IsDone() const;

  //! Returns TRUE if there is no intersection POINT.
  //! If 2 planes are identical or parallel, IsEmpty
  //! will return TRUE.
  bool IsEmpty() const;

  //! Returns the intersection point.
  const gp_Pnt& Value() const;

private:
  bool   done;
  bool   empt;
  gp_Pnt pnt;
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

inline bool IntAna_Int3Pln::IsDone() const
{

  return done;
}

inline bool IntAna_Int3Pln::IsEmpty() const
{

  if (!done)
  {
    throw StdFail_NotDone();
  }
  return empt;
}

inline const gp_Pnt& IntAna_Int3Pln::Value() const
{

  if (!done)
  {
    throw StdFail_NotDone();
  }
  if (empt)
  {
    throw Standard_DomainError();
  }
  return pnt;
}


