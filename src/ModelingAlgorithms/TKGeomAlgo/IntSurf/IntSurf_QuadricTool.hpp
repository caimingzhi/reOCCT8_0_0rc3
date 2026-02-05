#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Real.hpp>
class IntSurf_Quadric;
class gp_Vec;

//! This class provides a tool on a quadric that can be
//! used to instantiates the Walking algorithms (see
//! package IntWalk) with a Quadric from IntSurf
//! as implicit surface.
class IntSurf_QuadricTool
{
public:
  DEFINE_STANDARD_ALLOC

  //! Returns the value of the function.
  static double Value(const IntSurf_Quadric& Quad, const double X, const double Y, const double Z);

  //! Returns the gradient of the function.
  static void Gradient(const IntSurf_Quadric& Quad,
                       const double           X,
                       const double           Y,
                       const double           Z,
                       gp_Vec&                V);

  //! Returns the value and the gradient.
  static void ValueAndGradient(const IntSurf_Quadric& Quad,
                               const double           X,
                               const double           Y,
                               const double           Z,
                               double&                Val,
                               gp_Vec&                Grad);

  //! returns the tolerance of the zero of the implicit function
  Standard_EXPORT static double Tolerance(const IntSurf_Quadric& Quad);
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

#include <IntSurf_Quadric.hpp>
#include <gp_Vec.hpp>

inline double IntSurf_QuadricTool::Value(const IntSurf_Quadric& Quad,
                                         const double           X,
                                         const double           Y,
                                         const double           Z)
{

  return Quad.Distance(gp_Pnt(X, Y, Z));
}

inline void IntSurf_QuadricTool::Gradient(const IntSurf_Quadric& Quad,
                                          const double           X,
                                          const double           Y,
                                          const double           Z,
                                          gp_Vec&                V)
{

  V = Quad.Gradient(gp_Pnt(X, Y, Z));
}

inline void IntSurf_QuadricTool::ValueAndGradient(const IntSurf_Quadric& Quad,
                                                  const double           X,
                                                  const double           Y,
                                                  const double           Z,
                                                  double&                Val,
                                                  gp_Vec&                V)
{

  Quad.ValAndGrad(gp_Pnt(X, Y, Z), Val, V);
}
