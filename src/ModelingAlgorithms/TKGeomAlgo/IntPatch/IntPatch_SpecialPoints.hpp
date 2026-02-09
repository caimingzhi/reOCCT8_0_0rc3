#pragma once

#include <Adaptor3d_Surface.hpp>

enum IntPatch_SpecPntType
{
  IntPatch_SPntNone,
  IntPatch_SPntSeamU,
  IntPatch_SPntSeamV,
  IntPatch_SPntSeamUV,
  IntPatch_SPntPoleSeamU,
  IntPatch_SPntPole
};

class gp_Cone;
class gp_Vec;
class gp_XYZ;
class IntPatch_Point;
class IntSurf_PntOn2S;

template <typename T>
class math_VectorBase;
using math_Vector = math_VectorBase<double>;

class IntPatch_SpecialPoints
{
public:
  Standard_EXPORT static bool AddCrossUVIsoPoint(const occ::handle<Adaptor3d_Surface>& theQSurf,
                                                 const occ::handle<Adaptor3d_Surface>& thePSurf,
                                                 const IntSurf_PntOn2S&                theRefPt,
                                                 const double                          theTol3d,
                                                 IntSurf_PntOn2S& theAddedPoint,
                                                 const bool       theIsReversed = false);

  Standard_EXPORT static bool AddPointOnUorVIso(const occ::handle<Adaptor3d_Surface>& theQSurf,
                                                const occ::handle<Adaptor3d_Surface>& thePSurf,
                                                const IntSurf_PntOn2S&                theRefPt,
                                                const bool                            theIsU,
                                                const double       theIsoParameter,
                                                const math_Vector& theToler,
                                                const math_Vector& theInitPoint,
                                                const math_Vector& theInfBound,
                                                const math_Vector& theSupBound,
                                                IntSurf_PntOn2S&   theAddedPoint,
                                                const bool         theIsReversed = false);

  Standard_EXPORT static bool AddSingularPole(const occ::handle<Adaptor3d_Surface>& theQSurf,
                                              const occ::handle<Adaptor3d_Surface>& thePSurf,
                                              const IntSurf_PntOn2S&                thePtIso,
                                              IntPatch_Point&                       theVertex,
                                              IntSurf_PntOn2S&                      theAddedPoint,
                                              const bool theIsReversed    = false,
                                              const bool theIsReqRefCheck = false);

  Standard_EXPORT static bool ContinueAfterSpecialPoint(
    const occ::handle<Adaptor3d_Surface>& theQSurf,
    const occ::handle<Adaptor3d_Surface>& thePSurf,
    const IntSurf_PntOn2S&                theRefPt,
    const IntPatch_SpecPntType            theSPType,
    const double                          theTol2D,
    IntSurf_PntOn2S&                      theNewPoint,
    const bool                            theIsReversed = false);

  Standard_EXPORT static void AdjustPointAndVertex(const IntSurf_PntOn2S& theRefPoint,
                                                   const double           theArrPeriods[4],
                                                   IntSurf_PntOn2S&       theNewPoint,
                                                   IntPatch_Point* const  theVertex = nullptr);

protected:
  static Standard_EXPORT bool ProcessSphere(const IntSurf_PntOn2S& thePtIso,
                                            const gp_Vec&          theDUofPSurf,
                                            const gp_Vec&          theDVofPSurf,
                                            const bool             theIsReversed,
                                            const double           theVquad,
                                            double&                theUquad,
                                            bool&                  theIsIsoChoosen);

  static Standard_EXPORT bool ProcessCone(const IntSurf_PntOn2S& thePtIso,
                                          const gp_Vec&          theDUofPSurf,
                                          const gp_Vec&          theDVofPSurf,
                                          const gp_Cone&         theCone,
                                          const bool             theIsReversed,
                                          double&                theUquad,
                                          bool&                  theIsIsoChoosen);

  static Standard_EXPORT int GetTangentToIntLineForCone(const double  theConeSemiAngle,
                                                        const gp_XYZ& thePlnNormal,
                                                        gp_XYZ        theResult[2]);
};
