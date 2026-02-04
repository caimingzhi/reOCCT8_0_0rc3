#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <Standard_Transient.hpp>

//! class for instantiation of AppBlend
class GeomFill_Line : public Standard_Transient
{

public:
  Standard_EXPORT GeomFill_Line();

  Standard_EXPORT GeomFill_Line(const int NbPoints);

  int NbPoints() const;

  int Point(const int Index) const;

  DEFINE_STANDARD_RTTIEXT(GeomFill_Line, Standard_Transient)

private:
  int myNbPoints;
};
// Created on: 1994-02-18
// Created by: Bruno DUMORTIER
// Copyright (c) 1994-1999 Matra Datavision
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

//=================================================================================================

inline int GeomFill_Line::NbPoints() const
{
  return myNbPoints;
}

//=================================================================================================

inline int GeomFill_Line::Point(const int Index) const
{
  return Index;
}


