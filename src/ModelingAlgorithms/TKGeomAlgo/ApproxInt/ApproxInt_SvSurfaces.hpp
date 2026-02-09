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

class ApproxInt_SvSurfaces
{
public:
  DEFINE_STANDARD_ALLOC

  ApproxInt_SvSurfaces()
      : myUseSolver(false)
  {
  }

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
