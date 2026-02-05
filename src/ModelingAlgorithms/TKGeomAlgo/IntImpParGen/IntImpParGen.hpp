#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <IntRes2d_Position.hpp>
#include <Standard_Real.hpp>
#include <Standard_Boolean.hpp>
class gp_Vec2d;
class IntRes2d_Transition;
class IntRes2d_Domain;
class gp_Pnt2d;

//! Gives a generic algorithm to intersect Implicit Curves
//! and Bounded Parametric Curves.
//!
//! Level: Internal
//!
//! All the methods of all the classes are Internal.
class IntImpParGen
{
public:
  DEFINE_STANDARD_ALLOC

  //! Template class for an implicit curve.
  //! Math function, instantiated inside the Intersector.
  //! Tool used by the package IntCurve and IntImpParGen
  Standard_EXPORT static void DetermineTransition(const IntRes2d_Position Pos1,
                                                  gp_Vec2d&               Tan1,
                                                  const gp_Vec2d&         Norm1,
                                                  IntRes2d_Transition&    Trans1,
                                                  const IntRes2d_Position Pos2,
                                                  gp_Vec2d&               Tan2,
                                                  const gp_Vec2d&         Norm2,
                                                  IntRes2d_Transition&    Trans2,
                                                  const double            Tol);

  Standard_EXPORT static bool DetermineTransition(const IntRes2d_Position Pos1,
                                                  gp_Vec2d&               Tan1,
                                                  IntRes2d_Transition&    Trans1,
                                                  const IntRes2d_Position Pos2,
                                                  gp_Vec2d&               Tan2,
                                                  IntRes2d_Transition&    Trans2,
                                                  const double            Tol);

  Standard_EXPORT static void DeterminePosition(IntRes2d_Position&     Pos1,
                                                const IntRes2d_Domain& Dom1,
                                                const gp_Pnt2d&        P1,
                                                const double           Tol);

  Standard_EXPORT static double NormalizeOnDomain(double& Par1, const IntRes2d_Domain& Dom1);
};
