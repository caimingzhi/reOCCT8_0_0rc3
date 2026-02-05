#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <HLRBRep_TypeDef.hpp>

class gp_Dir;

//! The EdgeFaceTool computes the UV coordinates at a
//! given parameter on a Curve and a Surface. It also
//! compute the signed curvature value in a direction
//! at a given u,v point on a surface.
class HLRBRep_EdgeFaceTool
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static double CurvatureValue(const HLRBRep_SurfacePtr F,
                                               const double             U,
                                               const double             V,
                                               const gp_Dir&            Tg);

  //! return True if U and V are found.
  Standard_EXPORT static bool UVPoint(const double             Par,
                                      const HLRBRep_CurvePtr   E,
                                      const HLRBRep_SurfacePtr F,
                                      double&                  U,
                                      double&                  V);
};
