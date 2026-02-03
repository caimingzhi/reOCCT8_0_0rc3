// Created on: 1996-12-24
// Created by: Alexander BRIVIN
// Copyright (c) 1996-1999 Matra Datavision
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

#ifndef _Vrml_Cone_HeaderFile
#define _Vrml_Cone_HeaderFile

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>
// Created on: 1996-12-23
// Created by: Alexander BRIVIN and Dmitry TARASOV
// Copyright (c) 1996-1999 Matra Datavision
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

#ifndef _Vrml_ConeParts_HeaderFile
#define _Vrml_ConeParts_HeaderFile

enum Vrml_ConeParts
{
  Vrml_ConeSIDES,
  Vrml_ConeBOTTOM,
  Vrml_ConeALL
};

#endif // _Vrml_ConeParts_HeaderFile

#include <Standard_Real.hpp>
#include <Standard_OStream.hpp>

//! defines a Cone node of VRML specifying geometry shapes.
//! This node represents a simple cone, whose central axis is aligned
//! with the y-axis. By default, the cone is centred at (0,0,0)
//! and has size of -1 to +1 in the all three directions.
//! the cone has a radius of 1 at the bottom and height of 2,
//! with its apex at 1 and its bottom at -1. The cone has two parts:
//! the sides and the bottom
class Vrml_Cone
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Vrml_Cone(const Vrml_ConeParts aParts        = Vrml_ConeALL,
                            const double         aBottomRadius = 1,
                            const double         aHeight       = 2);

  Standard_EXPORT void SetParts(const Vrml_ConeParts aParts);

  Standard_EXPORT Vrml_ConeParts Parts() const;

  Standard_EXPORT void SetBottomRadius(const double aBottomRadius);

  Standard_EXPORT double BottomRadius() const;

  Standard_EXPORT void SetHeight(const double aHeight);

  Standard_EXPORT double Height() const;

  Standard_EXPORT Standard_OStream& Print(Standard_OStream& anOStream) const;

private:
  Vrml_ConeParts myParts;
  double         myBottomRadius;
  double         myHeight;
};

#endif // _Vrml_Cone_HeaderFile
