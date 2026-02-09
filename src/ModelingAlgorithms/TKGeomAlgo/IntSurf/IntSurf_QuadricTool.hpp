#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Real.hpp>
class IntSurf_Quadric;
class gp_Vec;

class IntSurf_QuadricTool
{
public:
  DEFINE_STANDARD_ALLOC

  static double Value(const IntSurf_Quadric& Quad, const double X, const double Y, const double Z);

  static void Gradient(const IntSurf_Quadric& Quad,
                       const double           X,
                       const double           Y,
                       const double           Z,
                       gp_Vec&                V);

  static void ValueAndGradient(const IntSurf_Quadric& Quad,
                               const double           X,
                               const double           Y,
                               const double           Z,
                               double&                Val,
                               gp_Vec&                Grad);

  Standard_EXPORT static double Tolerance(const IntSurf_Quadric& Quad);
};

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
