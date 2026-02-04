#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
#include <Standard_Real.hpp>
class gp_Pnt;
class gp_Vec;
class gp_Vec2d;
class IntSurf_PntOn2S;

//! This class is root class for classes dedicated to calculate
//! 2d and 3d points and tangents of intersection lines of two surfaces of different types
//! for given u, v parameters of intersection point on two surfaces.
//!
//! The field myUseSolver is used to manage type of calculation:
//! if myUseSolver = true, input parameters u1, v1, u2, v2 are considered as first approximation of
//! exact intersection point, then coordinates u1, v1, u2, v2 are refined with help of
//! the solver used in intersection algorithm and required values are calculated.
//! if myUseSolver = false, u1, v1, u2, v2 are considered as "exact" intersection points on two
//! surfaces and required values are calculated directly using u1, v1, u2, v2
class ApproxInt_SvSurfaces
{
public:
  DEFINE_STANDARD_ALLOC

  ApproxInt_SvSurfaces()
      : myUseSolver(false)
  {
  }

  //! returns True if Tg,Tguv1 Tguv2 can be computed.
  Standard_EXPORT virtual bool Compute(double&   u1,
                                       double&   v1,
                                       double&   u2,
                                       double&   v2,
                                       gp_Pnt&   Pt,
                                       gp_Vec&   Tg,
                                       gp_Vec2d& Tguv1,
                                       gp_Vec2d& Tguv2) = 0;

  Standard_EXPORT virtual void Pnt(const double u1,
                                   const double v1,
                                   const double u2,
                                   const double v2,
                                   gp_Pnt&      P) = 0;

  //! computes point on curve and parameters on the surfaces
  Standard_EXPORT virtual bool SeekPoint(const double     u1,
                                         const double     v1,
                                         const double     u2,
                                         const double     v2,
                                         IntSurf_PntOn2S& Point) = 0;

  Standard_EXPORT virtual bool Tangency(const double u1,
                                        const double v1,
                                        const double u2,
                                        const double v2,
                                        gp_Vec&      Tg) = 0;

  Standard_EXPORT virtual bool TangencyOnSurf1(const double u1,
                                               const double v1,
                                               const double u2,
                                               const double v2,
                                               gp_Vec2d&    Tg) = 0;

  Standard_EXPORT virtual bool TangencyOnSurf2(const double u1,
                                               const double v1,
                                               const double u2,
                                               const double v2,
                                               gp_Vec2d&    Tg) = 0;
  Standard_EXPORT virtual ~ApproxInt_SvSurfaces();

  void SetUseSolver(const bool theUseSol) { myUseSolver = theUseSol; }

  virtual bool GetUseSolver() const { return myUseSolver; }

private:
  bool myUseSolver;
};

