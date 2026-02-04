#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Plate_PinpointConstraint.hpp>
#include <Plate_D1.hpp>
#include <gp_XY.hpp>
#include <Standard_Integer.hpp>
class gp_XYZ;
class Plate_D2;
class Plate_D3;

//! define a G1, G2 or G3 constraint on the Plate
class Plate_GtoCConstraint
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Plate_GtoCConstraint(const Plate_GtoCConstraint& ref);

  Standard_EXPORT Plate_GtoCConstraint(const gp_XY&    point2d,
                                       const Plate_D1& D1S,
                                       const Plate_D1& D1T);

  Standard_EXPORT Plate_GtoCConstraint(const gp_XY&    point2d,
                                       const Plate_D1& D1S,
                                       const Plate_D1& D1T,
                                       const gp_XYZ&   nP);

  Standard_EXPORT Plate_GtoCConstraint(const gp_XY&    point2d,
                                       const Plate_D1& D1S,
                                       const Plate_D1& D1T,
                                       const Plate_D2& D2S,
                                       const Plate_D2& D2T);

  Standard_EXPORT Plate_GtoCConstraint(const gp_XY&    point2d,
                                       const Plate_D1& D1S,
                                       const Plate_D1& D1T,
                                       const Plate_D2& D2S,
                                       const Plate_D2& D2T,
                                       const gp_XYZ&   nP);

  Standard_EXPORT Plate_GtoCConstraint(const gp_XY&    point2d,
                                       const Plate_D1& D1S,
                                       const Plate_D1& D1T,
                                       const Plate_D2& D2S,
                                       const Plate_D2& D2T,
                                       const Plate_D3& D3S,
                                       const Plate_D3& D3T);

  Standard_EXPORT Plate_GtoCConstraint(const gp_XY&    point2d,
                                       const Plate_D1& D1S,
                                       const Plate_D1& D1T,
                                       const Plate_D2& D2S,
                                       const Plate_D2& D2T,
                                       const Plate_D3& D3S,
                                       const Plate_D3& D3T,
                                       const gp_XYZ&   nP);

  const int& nb_PPC() const;

  const Plate_PinpointConstraint& GetPPC(const int Index) const;

  const Plate_D1& D1SurfInit() const;

private:
  Plate_PinpointConstraint myPPC[9];
  Plate_D1                 myD1SurfInit;
  gp_XY                    pnt2d;
  int                      nb_PPConstraints;
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

inline const int& Plate_GtoCConstraint::nb_PPC() const
{
  return nb_PPConstraints;
}

inline const Plate_PinpointConstraint& Plate_GtoCConstraint::GetPPC(const int Index) const
{
  return myPPC[Index];
}

inline const Plate_D1& Plate_GtoCConstraint::D1SurfInit() const
{
  return myD1SurfInit;
}


