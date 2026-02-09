#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <HLRBRep_TypeDef.hpp>

class gp_Dir;

class HLRBRep_EdgeFaceTool
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static double CurvatureValue(const HLRBRep_SurfacePtr F,
                                               const double             U,
                                               const double             V,
                                               const gp_Dir&            Tg);

  Standard_EXPORT static bool UVPoint(const double             Par,
                                      const HLRBRep_CurvePtr   E,
                                      const HLRBRep_SurfacePtr F,
                                      double&                  U,
                                      double&                  V);
};
