#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <math_Vector.hpp>
#include <math_IntegerVector.hpp>
#include <Standard_OStream.hpp>
class math_MultipleVarFunction;

//! This class implements the integration of a function of multiple
//! variables between the parameter bounds Lower[a..b] and Upper[a..b].
//! Warning: Each element of Order must be inferior or equal to 61.
class math_GaussMultipleIntegration
{
public:
  DEFINE_STANDARD_ALLOC

  //! The Gauss-Legendre integration with Order = points of
  //! integration for each unknown, is done on the function F
  //! between the bounds Lower and Upper.
  Standard_EXPORT math_GaussMultipleIntegration(math_MultipleVarFunction& F,
                                                const math_Vector&        Lower,
                                                const math_Vector&        Upper,
                                                const math_IntegerVector& Order);

  //! returns True if all has been correctly done.
  bool IsDone() const;

  //! returns the value of the integral.
  double Value() const;

  //! Prints information on the current state of the object.
  Standard_EXPORT void Dump(Standard_OStream& o) const;

private:
  double Val;
  bool   Done;
};
// Copyright (c) 1997-1999 Matra Datavision
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

// math_GaussMultipleIntegration_1.hpp

#include <StdFail_NotDone.hpp>

inline bool math_GaussMultipleIntegration::IsDone() const
{
  return Done;
}

inline Standard_OStream& operator<<(Standard_OStream& o, const math_GaussMultipleIntegration& G)
{
  G.Dump(o);
  return o;
}

inline double math_GaussMultipleIntegration::Value() const
{
  StdFail_NotDone_Raise_if(!Done, " ");
  return Val;
}


