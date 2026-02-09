#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Standard_Integer.hpp>
class IntCurve_PConic;
class gp_Pnt2d;
class gp_Vec2d;

class IntCurve_PConicTool
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static double EpsX(const IntCurve_PConic& C);

  Standard_EXPORT static int NbSamples(const IntCurve_PConic& C);

  Standard_EXPORT static int NbSamples(const IntCurve_PConic& C, const double U0, const double U1);

  Standard_EXPORT static gp_Pnt2d Value(const IntCurve_PConic& C, const double X);

  Standard_EXPORT static void D1(const IntCurve_PConic& C,
                                 const double           U,
                                 gp_Pnt2d&              P,
                                 gp_Vec2d&              T);

  Standard_EXPORT static void D2(const IntCurve_PConic& C,
                                 const double           U,
                                 gp_Pnt2d&              P,
                                 gp_Vec2d&              T,
                                 gp_Vec2d&              N);
};
