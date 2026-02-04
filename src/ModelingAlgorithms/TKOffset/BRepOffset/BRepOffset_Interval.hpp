#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Real.hpp>
#include <ChFiDS_TypeOfConcavity.hpp>

class BRepOffset_Interval
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepOffset_Interval();

  Standard_EXPORT BRepOffset_Interval(const double                 U1,
                                      const double                 U2,
                                      const ChFiDS_TypeOfConcavity Type);

  void First(const double U);

  void Last(const double U);

  void Type(const ChFiDS_TypeOfConcavity T);

  double First() const;

  double Last() const;

  ChFiDS_TypeOfConcavity Type() const;

private:
  double                 f;
  double                 l;
  ChFiDS_TypeOfConcavity type;
};
// Created on: 1995-10-20
// Created by: Yves FRICAUD
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

//=================================================================================================

inline void BRepOffset_Interval::First(const double U)
{
  f = U;
}

//=================================================================================================

inline void BRepOffset_Interval::Last(const double U)
{
  l = U;
}

//=================================================================================================

inline void BRepOffset_Interval::Type(const ChFiDS_TypeOfConcavity T)
{
  type = T;
}

//=================================================================================================

inline double BRepOffset_Interval::First() const
{
  return f;
}

//=================================================================================================

inline double BRepOffset_Interval::Last() const
{
  return l;
}

//=================================================================================================

inline ChFiDS_TypeOfConcavity BRepOffset_Interval::Type() const
{
  return type;
}


