// Created on: 1995-10-19
// Created by: Andre LIEUTIER
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

#ifndef _Plate_PinpointConstraint_HeaderFile
#define _Plate_PinpointConstraint_HeaderFile

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_XYZ.hpp>
#include <gp_XY.hpp>

//! define a constraint on the Plate
class Plate_PinpointConstraint
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Plate_PinpointConstraint();

  Standard_EXPORT Plate_PinpointConstraint(const gp_XY&  point2d,
                                           const gp_XYZ& ImposedValue,
                                           const int     iu = 0,
                                           const int     iv = 0);

  const gp_XY& Pnt2d() const;

  const int& Idu() const;

  const int& Idv() const;

  const gp_XYZ& Value() const;

private:
  gp_XYZ value;
  gp_XY  pnt2d;
  int    idu;
  int    idv;
};
// Created on: 1998-05-25
// Created by: Andre LIEUTIER
// Copyright (c) 1998-1999 Matra Datavision
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

inline const gp_XY& Plate_PinpointConstraint::Pnt2d() const
{
  return pnt2d;
}

inline const int& Plate_PinpointConstraint::Idu() const
{
  return idu;
}

inline const int& Plate_PinpointConstraint::Idv() const
{
  return idv;
}

inline const gp_XYZ& Plate_PinpointConstraint::Value() const
{
  return value;
}


#endif // _Plate_PinpointConstraint_HeaderFile
