#include <HLRBRep_TheQuadCurvExactInterCSurf.hpp>

#include <gp_Lin.hpp>
#include <HLRBRep_LineTool.hpp>
#include <HLRBRep_Surface.hpp>
#include <HLRBRep_SurfaceTool.hpp>
#include <HLRBRep_TheQuadCurvFuncOfTheQuadCurvExactInterCSurf.hpp>

#include "../../TKGeomAlgo/IntCurveSurface/IntCurveSurface_QuadricCurveExactInterUtils.hpp"

HLRBRep_TheQuadCurvExactInterCSurf::HLRBRep_TheQuadCurvExactInterCSurf(HLRBRep_Surface* S,
                                                                       const gp_Lin&    C)
    : nbpnts(-1),
      nbintv(-1)
{
  IntCurveSurface_QuadricCurveExactInterUtils::PerformIntersection<
    HLRBRep_Surface*,
    HLRBRep_SurfaceTool,
    gp_Lin,
    HLRBRep_LineTool,
    HLRBRep_TheQuadCurvFuncOfTheQuadCurvExactInterCSurf>(S, C, pnts, intv, nbpnts, nbintv);
}

bool HLRBRep_TheQuadCurvExactInterCSurf::IsDone() const
{
  return (nbpnts != -1);
}

int HLRBRep_TheQuadCurvExactInterCSurf::NbRoots() const
{
  return nbpnts;
}

int HLRBRep_TheQuadCurvExactInterCSurf::NbIntervals() const
{
  return nbintv;
}

double HLRBRep_TheQuadCurvExactInterCSurf::Root(const int Index) const
{
  return pnts(Index);
}

void HLRBRep_TheQuadCurvExactInterCSurf::Intervals(const int Index, double& a, double& b) const
{
  int Index2 = Index + Index - 1;
  a          = intv(Index2);
  b          = intv(Index2 + 1);
}
