// Created on: 1993-04-23
// Created by: Modelistation
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

#ifndef _HLRBRep_SLPropsATool_HeaderFile
#define _HLRBRep_SLPropsATool_HeaderFile

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <HLRBRep_TypeDef.hpp>
#include <Standard_Real.hpp>
class gp_Pnt;
class gp_Vec;

class HLRBRep_SLPropsATool
{
public:
  DEFINE_STANDARD_ALLOC

  //! Computes the point <P> of parameter <U> and <V>
  //! on the Surface <A>.
  static void Value(const HLRBRep_SurfacePtr A, const double U, const double V, gp_Pnt& P);

  //! Computes the point <P> and first derivative <D1*>
  //! of parameter <U> and <V> on the Surface <A>.
  static void D1(const HLRBRep_SurfacePtr A,
                 const double             U,
                 const double             V,
                 gp_Pnt&                  P,
                 gp_Vec&                  D1U,
                 gp_Vec&                  D1V);

  //! Computes the point <P>, the first derivative <D1*>
  //! and second derivative <D2*> of parameter <U> and
  //! <V> on the Surface <A>.
  static void D2(const HLRBRep_SurfacePtr A,
                 const double             U,
                 const double             V,
                 gp_Pnt&                  P,
                 gp_Vec&                  D1U,
                 gp_Vec&                  D1V,
                 gp_Vec&                  D2U,
                 gp_Vec&                  D2V,
                 gp_Vec&                  DUV);

  static gp_Vec DN(const HLRBRep_SurfacePtr A,
                   const double             U,
                   const double             V,
                   const int                Nu,
                   const int                Nv);

  //! returns the order of continuity of the Surface <A>.
  //! returns 1 : first derivative only is computable
  //! returns 2 : first and second derivative only are
  //! computable.
  static int Continuity(const HLRBRep_SurfacePtr A);

  //! returns the bounds of the Surface.
  static void Bounds(const HLRBRep_SurfacePtr A, double& U1, double& V1, double& U2, double& V2);
};
// Created on: 1992-08-18
// Created by: Herve LEGRAND
// Copyright (c) 1992-1999 Matra Datavision
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

#include <HLRBRep_Surface.hpp>
#include <GeomAbs_Shape.hpp>
#include <gp_Pnt.hpp>

//=================================================================================================

inline void HLRBRep_SLPropsATool::Value(const HLRBRep_SurfacePtr A,
                                        const double             U,
                                        const double             V,
                                        gp_Pnt&                  P)
{
  P = ((HLRBRep_Surface*)A)->Value(U, V);
}

//=================================================================================================

inline void HLRBRep_SLPropsATool::D1(const HLRBRep_SurfacePtr A,
                                     const double             U,
                                     const double             V,
                                     gp_Pnt&                  P,
                                     gp_Vec&                  D1U,
                                     gp_Vec&                  D1V)
{
  ((HLRBRep_Surface*)A)->D1(U, V, P, D1U, D1V);
}

//=================================================================================================

inline void HLRBRep_SLPropsATool::D2(const HLRBRep_SurfacePtr A,
                                     const double             U,
                                     const double             V,
                                     gp_Pnt&                  P,
                                     gp_Vec&                  D1U,
                                     gp_Vec&                  D1V,
                                     gp_Vec&                  D2U,
                                     gp_Vec&                  D2V,
                                     gp_Vec&                  DUV)
{
  ((HLRBRep_Surface*)A)->D2(U, V, P, D1U, D1V, D2U, D2V, DUV);
}

//=================================================================================================

inline gp_Vec HLRBRep_SLPropsATool::DN(const HLRBRep_SurfacePtr A,
                                       const double             U,
                                       const double             V,
                                       const int                Nu,
                                       const int                Nv)
{
  return ((HLRBRep_Surface*)A)->DN(U, V, Nu, Nv);
}

//=================================================================================================

inline int HLRBRep_SLPropsATool::Continuity(const HLRBRep_SurfacePtr)
{
  return 2;
} // et boum ! cky le 27 - 04 - 1993

//=================================================================================================

inline void HLRBRep_SLPropsATool::Bounds(const HLRBRep_SurfacePtr,
                                         double& U1,
                                         double& V1,
                                         double& U2,
                                         double& V2)
{
  U1 = V1 = RealFirst();
  U2 = V2 = RealLast();
}


#endif // _HLRBRep_SLPropsATool_HeaderFile
