// Created on: 1993-11-05
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

#ifndef _HatchGen_Domain_HeaderFile
#define _HatchGen_Domain_HeaderFile

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
#include <HatchGen_PointOnHatching.hpp>

class HatchGen_Domain
{
public:
  DEFINE_STANDARD_ALLOC

  //! Creates an infinite domain.
  Standard_EXPORT HatchGen_Domain();

  //! Creates a domain for the curve associated to a hatching.
  Standard_EXPORT HatchGen_Domain(const HatchGen_PointOnHatching& P1,
                                  const HatchGen_PointOnHatching& P2);

  //! Creates a semi-infinite domain for the curve associated
  //! to a hatching. The `First' flag means that the given
  //! point is the first one.
  Standard_EXPORT HatchGen_Domain(const HatchGen_PointOnHatching& P, const bool First);

  //! Sets the first and the second points of the domain.
  void SetPoints(const HatchGen_PointOnHatching& P1, const HatchGen_PointOnHatching& P2);

  //! Sets the first and the second points of the domain
  //! as the infinite.
  void SetPoints();

  //! Sets the first point of the domain.
  void SetFirstPoint(const HatchGen_PointOnHatching& P);

  //! Sets the first point of the domain at the
  //! infinite.
  void SetFirstPoint();

  //! Sets the second point of the domain.
  void SetSecondPoint(const HatchGen_PointOnHatching& P);

  //! Sets the second point of the domain at the
  //! infinite.
  void SetSecondPoint();

  //! Returns True if the domain has a first point.
  bool HasFirstPoint() const;

  //! Returns the first point of the domain.
  //! The exception DomainError is raised if
  //! HasFirstPoint returns False.
  const HatchGen_PointOnHatching& FirstPoint() const;

  //! Returns True if the domain has a second point.
  bool HasSecondPoint() const;

  //! Returns the second point of the domain.
  //! The exception DomainError is raised if
  //! HasSecondPoint returns False.
  const HatchGen_PointOnHatching& SecondPoint() const;

  //! Dump of the domain.
  Standard_EXPORT void Dump(const int Index = 0) const;

private:
  bool                     myHasFirstPoint;
  HatchGen_PointOnHatching myFirstPoint;
  bool                     myHasSecondPoint;
  HatchGen_PointOnHatching mySecondPoint;
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

#include <Standard_DomainError.hpp>

//=======================================================================
// Function : SetPoints
// Purpose  : Sets the first and the second points of the domain.
//=======================================================================

inline void HatchGen_Domain::SetPoints(const HatchGen_PointOnHatching& P1,
                                       const HatchGen_PointOnHatching& P2)
{
  myHasFirstPoint  = true;
  myFirstPoint     = P1;
  myHasSecondPoint = true;
  mySecondPoint    = P2;
}

//=======================================================================
// Function : SetPoints
// Purpose  : Sets the first and the second points of the domain at the
//            infinite.
//=======================================================================

inline void HatchGen_Domain::SetPoints()
{
  myHasFirstPoint  = false;
  myHasSecondPoint = false;
}

//=======================================================================
// Function : SetFirstPoint
// Purpose  : Sets the first point of the domain.
//=======================================================================

inline void HatchGen_Domain::SetFirstPoint(const HatchGen_PointOnHatching& P)
{
  myHasFirstPoint = true;
  myFirstPoint    = P;
}

//=======================================================================
// Function : SetFirstPoint
// Purpose  : Sets the first point of the domain at the infinite.
//=======================================================================

inline void HatchGen_Domain::SetFirstPoint()
{
  myHasFirstPoint = false;
}

//=======================================================================
// Function : SetSecondPoint
// Purpose  : Sets the second point of the domain.
//=======================================================================

inline void HatchGen_Domain::SetSecondPoint(const HatchGen_PointOnHatching& P)
{
  myHasSecondPoint = true;
  mySecondPoint    = P;
}

//=======================================================================
// Function : SetSecondPoint
// Purpose  : Sets the second point of the domain at the infinite.
//=======================================================================

inline void HatchGen_Domain::SetSecondPoint()
{
  myHasSecondPoint = false;
}

//=======================================================================
// Function : HasFirstPoint
// Purpose  : Returns True if the domain has a first point.
//=======================================================================

inline bool HatchGen_Domain::HasFirstPoint() const
{
  return myHasFirstPoint;
}

//=======================================================================
// Function : FirstPoint
// Purpose  : Returns the first point of the domain.
//=======================================================================

inline const HatchGen_PointOnHatching& HatchGen_Domain::FirstPoint() const
{
  Standard_DomainError_Raise_if(!myHasFirstPoint, "HatchGen_Domain::FirstPoint");
  return myFirstPoint;
}

//=======================================================================
// Function : HasSecondPoint
// Purpose  : Returns True if the domain has a second point.
//=======================================================================

inline bool HatchGen_Domain::HasSecondPoint() const
{
  return myHasSecondPoint;
}

//=======================================================================
// Function : SecondPoint
// Purpose  : Returns the second of the domain.
//=======================================================================

inline const HatchGen_PointOnHatching& HatchGen_Domain::SecondPoint() const
{
  Standard_DomainError_Raise_if(!myHasSecondPoint, "HatchGen_Domain::SecondPoint");
  return mySecondPoint;
}


#endif // _HatchGen_Domain_HeaderFile
