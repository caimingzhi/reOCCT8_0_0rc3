#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

//! This class implements the common services for
//! all classes of StepToTopoDS which report error
//! and sets and returns precision.
class StepToTopoDS_Root
{
public:
  DEFINE_STANDARD_ALLOC

  bool IsDone() const;

  //! Returns the value of "MyPrecision"
  double Precision() const;

  //! Sets the value of "MyPrecision"
  void SetPrecision(const double preci);

  //! Returns the value of "MaxTol"
  double MaxTol() const;

  //! Sets the value of MaxTol
  void SetMaxTol(const double maxpreci);

protected:
  Standard_EXPORT StepToTopoDS_Root();

  bool done;

private:
  double myPrecision;
  double myMaxTol;
};
// Created on: 1993-07-28
// Created by: Martine LANGLOIS
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

#include <StepToTopoDS_Root.hpp>

//=================================================================================================

inline bool StepToTopoDS_Root::IsDone() const
{
  return done;
}

//=================================================================================================

inline double StepToTopoDS_Root::Precision() const
{
  return myPrecision;
}

//=================================================================================================

inline void StepToTopoDS_Root::SetPrecision(const double preci)
{
  myPrecision = preci;
}

//=================================================================================================

inline double StepToTopoDS_Root::MaxTol() const
{
  return myMaxTol;
}

//=================================================================================================

inline void StepToTopoDS_Root::SetMaxTol(const double maxpreci)
{
  myMaxTol = maxpreci;
}


