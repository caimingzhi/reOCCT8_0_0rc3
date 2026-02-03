// Created on: 1992-04-27
// Created by: Laurent BUCHARD
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

#ifndef _IntCurve_IntConicConic_HeaderFile
#define _IntCurve_IntConicConic_HeaderFile

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <IntCurve_IntImpConicParConic.hpp>
#include <IntRes2d_Intersection.hpp>
class gp_Lin2d;
class IntRes2d_Domain;
class gp_Circ2d;
class gp_Elips2d;
class gp_Parab2d;
class gp_Hypr2d;

//! Provides methods to intersect two conics.
//! The exception ConstructionError is raised in constructors
//! or in Perform methods when a domain (Domain from IntRes2d)
//! is not correct, i-e when a Circle (Circ2d from gp) or
//! an Ellipse (i-e Elips2d from gp) do not have a closed
//! domain (use the SetEquivalentParameters method for a domain
//! on a circle or an ellipse).
class IntCurve_IntConicConic : public IntRes2d_Intersection
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty Constructor
  IntCurve_IntConicConic();

  //! Intersection between 2 lines from gp.
  IntCurve_IntConicConic(const gp_Lin2d&        L1,
                         const IntRes2d_Domain& D1,
                         const gp_Lin2d&        L2,
                         const IntRes2d_Domain& D2,
                         const double           TolConf,
                         const double           Tol);

  //! Intersection between 2 lines from gp.
  Standard_EXPORT void Perform(const gp_Lin2d&        L1,
                               const IntRes2d_Domain& D1,
                               const gp_Lin2d&        L2,
                               const IntRes2d_Domain& D2,
                               const double           TolConf,
                               const double           Tol);

  //! Intersection between a line and a circle.
  //! The exception ConstructionError is raised if the method
  //! IsClosed of the domain of the circle returns False.
  IntCurve_IntConicConic(const gp_Lin2d&        L,
                         const IntRes2d_Domain& DL,
                         const gp_Circ2d&       C,
                         const IntRes2d_Domain& DC,
                         const double           TolConf,
                         const double           Tol);

  //! Intersection between a line and a circle.
  //! The exception ConstructionError is raised if the method
  //! IsClosed of the domain of the circle returns False.
  Standard_EXPORT void Perform(const gp_Lin2d&        L,
                               const IntRes2d_Domain& DL,
                               const gp_Circ2d&       C,
                               const IntRes2d_Domain& DC,
                               const double           TolConf,
                               const double           Tol);

  //! Intersection between a line and an ellipse.
  //! The exception ConstructionError is raised if the method
  //! IsClosed of the domain of the ellipse returns False.
  IntCurve_IntConicConic(const gp_Lin2d&        L,
                         const IntRes2d_Domain& DL,
                         const gp_Elips2d&      E,
                         const IntRes2d_Domain& DE,
                         const double           TolConf,
                         const double           Tol);

  //! Intersection between a line and an ellipse.
  //! The exception ConstructionError is raised if the method
  //! IsClosed of the domain of the ellipse returns False.
  Standard_EXPORT void Perform(const gp_Lin2d&        L,
                               const IntRes2d_Domain& DL,
                               const gp_Elips2d&      E,
                               const IntRes2d_Domain& DE,
                               const double           TolConf,
                               const double           Tol);

  //! Intersection between a line and a parabola from gp.
  IntCurve_IntConicConic(const gp_Lin2d&        L,
                         const IntRes2d_Domain& DL,
                         const gp_Parab2d&      P,
                         const IntRes2d_Domain& DP,
                         const double           TolConf,
                         const double           Tol);

  //! Intersection between a line and a parabola from gp.
  Standard_EXPORT void Perform(const gp_Lin2d&        L,
                               const IntRes2d_Domain& DL,
                               const gp_Parab2d&      P,
                               const IntRes2d_Domain& DP,
                               const double           TolConf,
                               const double           Tol);

  //! Intersection between a line and an hyperbola.
  IntCurve_IntConicConic(const gp_Lin2d&        L,
                         const IntRes2d_Domain& DL,
                         const gp_Hypr2d&       H,
                         const IntRes2d_Domain& DH,
                         const double           TolConf,
                         const double           Tol);

  //! Intersection between a line and an hyperbola.
  Standard_EXPORT void Perform(const gp_Lin2d&        L,
                               const IntRes2d_Domain& DL,
                               const gp_Hypr2d&       H,
                               const IntRes2d_Domain& DH,
                               const double           TolConf,
                               const double           Tol);

  //! Intersection between 2 circles from gp.
  //! The exception ConstructionError is raised if the method
  //! IsClosed of one of the domain returns False.
  IntCurve_IntConicConic(const gp_Circ2d&       C1,
                         const IntRes2d_Domain& D1,
                         const gp_Circ2d&       C2,
                         const IntRes2d_Domain& D2,
                         const double           TolConf,
                         const double           Tol);

  //! Intersection between 2 circles from gp.
  //! The exception ConstructionError is raised if the method
  //! IsClosed of the domain of one of the circle returns False.
  Standard_EXPORT void Perform(const gp_Circ2d&       C1,
                               const IntRes2d_Domain& D1,
                               const gp_Circ2d&       C2,
                               const IntRes2d_Domain& D2,
                               const double           TolConf,
                               const double           Tol);

  //! Intersection between a circle and an ellipse.
  //! The exception ConstructionError is raised if the method
  //! IsClosed of one the domain returns False.
  IntCurve_IntConicConic(const gp_Circ2d&       C,
                         const IntRes2d_Domain& DC,
                         const gp_Elips2d&      E,
                         const IntRes2d_Domain& DE,
                         const double           TolConf,
                         const double           Tol);

  //! Intersection between a circle and an ellipse.
  //! The exception ConstructionError is raised if the method
  //! IsClosed of one the domain returns False.
  Standard_EXPORT void Perform(const gp_Circ2d&       C,
                               const IntRes2d_Domain& DC,
                               const gp_Elips2d&      E,
                               const IntRes2d_Domain& DE,
                               const double           TolConf,
                               const double           Tol);

  //! Intersection between a circle and a parabola.
  //! The exception ConstructionError is raised if the method
  //! IsClosed of the domain of the circle returns False.
  IntCurve_IntConicConic(const gp_Circ2d&       C,
                         const IntRes2d_Domain& DC,
                         const gp_Parab2d&      P,
                         const IntRes2d_Domain& DP,
                         const double           TolConf,
                         const double           Tol);

  //! Intersection between a circle and a parabola.
  //! The exception ConstructionError is raised if the method
  //! IsClosed of the domain of the circle returns False.
  Standard_EXPORT void Perform(const gp_Circ2d&       C,
                               const IntRes2d_Domain& DC,
                               const gp_Parab2d&      P,
                               const IntRes2d_Domain& DP,
                               const double           TolConf,
                               const double           Tol);

  //! Intersection between a circle and an hyperbola.
  //! The exception ConstructionError is raised if the method
  //! IsClosed of the domain of the circle returns False.
  IntCurve_IntConicConic(const gp_Circ2d&       C,
                         const IntRes2d_Domain& DC,
                         const gp_Hypr2d&       H,
                         const IntRes2d_Domain& DH,
                         const double           TolConf,
                         const double           Tol);

  //! Intersection between a circle and an hyperbola.
  //! The exception ConstructionError is raised if the method
  //! IsClosed of the domain of the circle returns False.
  Standard_EXPORT void Perform(const gp_Circ2d&       C,
                               const IntRes2d_Domain& DC,
                               const gp_Hypr2d&       H,
                               const IntRes2d_Domain& DH,
                               const double           TolConf,
                               const double           Tol);

  //! Intersection between 2 ellipses.
  //! The exception ConstructionError is raised if the method
  //! IsClosed of one of the domain returns False.
  IntCurve_IntConicConic(const gp_Elips2d&      E1,
                         const IntRes2d_Domain& D1,
                         const gp_Elips2d&      E2,
                         const IntRes2d_Domain& D2,
                         const double           TolConf,
                         const double           Tol);

  //! Intersection between 2 ellipses.
  //! The exception ConstructionError is raised if the method
  //! IsClosed of one of the domain returns False.
  Standard_EXPORT void Perform(const gp_Elips2d&      E1,
                               const IntRes2d_Domain& D1,
                               const gp_Elips2d&      E2,
                               const IntRes2d_Domain& D2,
                               const double           TolConf,
                               const double           Tol);

  //! Intersection between an ellipse and a parabola.
  //! The exception ConstructionError is raised if the method
  //! IsClosed of the domain of the ellipse returns False.
  IntCurve_IntConicConic(const gp_Elips2d&      E,
                         const IntRes2d_Domain& DE,
                         const gp_Parab2d&      P,
                         const IntRes2d_Domain& DP,
                         const double           TolConf,
                         const double           Tol);

  //! Intersection between an ellipse and a parabola.
  //! The exception ConstructionError is raised if the method
  //! IsClosed of the domain of the ellipse returns False.
  Standard_EXPORT void Perform(const gp_Elips2d&      E,
                               const IntRes2d_Domain& DE,
                               const gp_Parab2d&      P,
                               const IntRes2d_Domain& DP,
                               const double           TolConf,
                               const double           Tol);

  //! Intersection between an ellipse and an hyperbola.
  //! The exception ConstructionError is raised if the method
  //! IsClosed of the domain of the ellipse returns False.
  IntCurve_IntConicConic(const gp_Elips2d&      E,
                         const IntRes2d_Domain& DE,
                         const gp_Hypr2d&       H,
                         const IntRes2d_Domain& DH,
                         const double           TolConf,
                         const double           Tol);

  //! Intersection between an ellipse and an hyperbola.
  //! The exception ConstructionError is raised if the method
  //! IsClosed of the domain of the ellipse returns False.
  Standard_EXPORT void Perform(const gp_Elips2d&      E,
                               const IntRes2d_Domain& DE,
                               const gp_Hypr2d&       H,
                               const IntRes2d_Domain& DH,
                               const double           TolConf,
                               const double           Tol);

  //! Intersection between 2 parabolas.
  IntCurve_IntConicConic(const gp_Parab2d&      P1,
                         const IntRes2d_Domain& D1,
                         const gp_Parab2d&      P2,
                         const IntRes2d_Domain& D2,
                         const double           TolConf,
                         const double           Tol);

  //! Intersection between 2 parabolas.
  Standard_EXPORT void Perform(const gp_Parab2d&      P1,
                               const IntRes2d_Domain& D1,
                               const gp_Parab2d&      P2,
                               const IntRes2d_Domain& D2,
                               const double           TolConf,
                               const double           Tol);

  //! Intersection between a parabola and an hyperbola.
  IntCurve_IntConicConic(const gp_Parab2d&      P,
                         const IntRes2d_Domain& DP,
                         const gp_Hypr2d&       H,
                         const IntRes2d_Domain& DH,
                         const double           TolConf,
                         const double           Tol);

  //! Intersection between a parabola and an hyperbola.
  Standard_EXPORT void Perform(const gp_Parab2d&      P,
                               const IntRes2d_Domain& DP,
                               const gp_Hypr2d&       H,
                               const IntRes2d_Domain& DH,
                               const double           TolConf,
                               const double           Tol);

  //! Intersection between 2 hyperbolas.
  IntCurve_IntConicConic(const gp_Hypr2d&       H1,
                         const IntRes2d_Domain& D1,
                         const gp_Hypr2d&       H2,
                         const IntRes2d_Domain& D2,
                         const double           TolConf,
                         const double           Tol);

  //! Intersection between 2 hyperbolas.
  Standard_EXPORT void Perform(const gp_Hypr2d&       H1,
                               const IntRes2d_Domain& D1,
                               const gp_Hypr2d&       H2,
                               const IntRes2d_Domain& D2,
                               const double           TolConf,
                               const double           Tol);

private:
  IntCurve_IntImpConicParConic Inter;
};
// Created on: 1997-02-19
// Created by: Laurent BUCHARD
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

#define CONSTRUCTOR IntCurve_IntConicConic::IntCurve_IntConicConic
#define PERFORM void IntCurve_IntConicConic::Perform

inline CONSTRUCTOR() {}

//----------------------------------------------------------------------  L  P
inline CONSTRUCTOR(const gp_Lin2d&        L,
                   const IntRes2d_Domain& DL,
                   const gp_Parab2d&      P,
                   const IntRes2d_Domain& DP,
                   const double           TolConf,
                   const double           Tol)
{
  Perform(L, DL, P, DP, TolConf, Tol);
}

//----------------------------------------------------------------------  L  E
inline CONSTRUCTOR(const gp_Lin2d&        L,
                   const IntRes2d_Domain& DL,
                   const gp_Elips2d&      E,
                   const IntRes2d_Domain& DE,
                   const double           TolConf,
                   const double           Tol)
{

  Perform(L, DL, E, DE, TolConf, Tol);
}

//----------------------------------------------------------------------  L H
inline CONSTRUCTOR(const gp_Lin2d&        L,
                   const IntRes2d_Domain& DL,
                   const gp_Hypr2d&       H,
                   const IntRes2d_Domain& DH,
                   const double           TolConf,
                   const double           Tol)
{

  Perform(L, DL, H, DH, TolConf, Tol);
}

//---------------------------------------------------------------------- C P
inline CONSTRUCTOR(const gp_Circ2d&       C,
                   const IntRes2d_Domain& DC,
                   const gp_Parab2d&      P,
                   const IntRes2d_Domain& DP,
                   const double           TolConf,
                   const double           Tol)
{

  Perform(C, DC, P, DP, TolConf, Tol);
}

//----------------------------------------------------------------------  C E
inline CONSTRUCTOR(const gp_Circ2d&       C,
                   const IntRes2d_Domain& DC,
                   const gp_Elips2d&      E,
                   const IntRes2d_Domain& DE,
                   const double           TolConf,
                   const double           Tol)
{

  Perform(C, DC, E, DE, TolConf, Tol);
}

//---------------------------------------------------------------------- C H
inline CONSTRUCTOR(const gp_Circ2d&       C,
                   const IntRes2d_Domain& DC,
                   const gp_Hypr2d&       H,
                   const IntRes2d_Domain& DH,
                   const double           TolConf,
                   const double           Tol)
{

  Perform(C, DC, H, DH, TolConf, Tol);
}

//---------------------------------------------------------------------- P P
inline CONSTRUCTOR(const gp_Parab2d&      P1,
                   const IntRes2d_Domain& D1,
                   const gp_Parab2d&      P2,
                   const IntRes2d_Domain& D2,
                   const double           TolConf,
                   const double           Tol)
{

  Perform(P1, D1, P2, D2, TolConf, Tol);
}

//---------------------------------------------------------------------- E P
inline CONSTRUCTOR(const gp_Elips2d&      E,
                   const IntRes2d_Domain& DE,
                   const gp_Parab2d&      P,
                   const IntRes2d_Domain& DP,
                   const double           TolConf,
                   const double           Tol)
{
  Perform(E, DE, P, DP, TolConf, Tol);
}

//---------------------------------------------------------------------- P H
inline CONSTRUCTOR(const gp_Parab2d&      P,
                   const IntRes2d_Domain& DP,
                   const gp_Hypr2d&       H,
                   const IntRes2d_Domain& DH,
                   const double           TolConf,
                   const double           Tol)
{

  Perform(P, DP, H, DH, TolConf, Tol);
}

//---------------------------------------------------------------------- E E
inline CONSTRUCTOR(const gp_Elips2d&      E1,
                   const IntRes2d_Domain& D1,
                   const gp_Elips2d&      E2,
                   const IntRes2d_Domain& D2,
                   const double           TolConf,
                   const double           Tol)
{

  Perform(E1, D1, E2, D2, TolConf, Tol);
}

//----------------------------------------------------------------------  E H
inline CONSTRUCTOR(const gp_Elips2d&      E,
                   const IntRes2d_Domain& DE,
                   const gp_Hypr2d&       H,
                   const IntRes2d_Domain& DH,
                   const double           TolConf,
                   const double           Tol)
{

  Perform(E, DE, H, DH, TolConf, Tol);
}

//---------------------------------------------------------------------- H H
inline CONSTRUCTOR(const gp_Hypr2d&       H1,
                   const IntRes2d_Domain& DH1,
                   const gp_Hypr2d&       H2,
                   const IntRes2d_Domain& DH2,
                   const double           TolConf,
                   const double           Tol)
{

  Perform(H1, DH1, H2, DH2, TolConf, Tol);
}

//---------------------------------------------------------------------- L L
inline CONSTRUCTOR(const gp_Lin2d&        L1,
                   const IntRes2d_Domain& D1,
                   const gp_Lin2d&        L2,
                   const IntRes2d_Domain& D2,
                   const double           TolConf,
                   const double           Tol)
{
  Perform(L1, D1, L2, D2, TolConf, Tol);
}

//---------------------------------------------------------------------- L C
inline CONSTRUCTOR(const gp_Lin2d&        L1,
                   const IntRes2d_Domain& D1,
                   const gp_Circ2d&       C2,
                   const IntRes2d_Domain& D2,
                   const double           TolConf,
                   const double           Tol)
{

  Perform(L1, D1, C2, D2, TolConf, Tol);
}

//---------------------------------------------------------------------- C C

inline CONSTRUCTOR(const gp_Circ2d&       C1,
                   const IntRes2d_Domain& D1,
                   const gp_Circ2d&       C2,
                   const IntRes2d_Domain& D2,
                   const double           TolConf,
                   const double           Tol)
{
  SetReversedParameters(false);
  Perform(C1, D1, C2, D2, TolConf, Tol);
}


#endif // _IntCurve_IntConicConic_HeaderFile
