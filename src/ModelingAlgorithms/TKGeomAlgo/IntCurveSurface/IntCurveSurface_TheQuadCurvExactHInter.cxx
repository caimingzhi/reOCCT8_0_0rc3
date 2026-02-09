#include <IntCurveSurface_TheQuadCurvExactHInter.hpp>

#include <Adaptor3d_Curve.hpp>
#include <Adaptor3d_HSurfaceTool.hpp>
#include <Adaptor3d_Surface.hpp>
#include <IntCurveSurface_TheHCurveTool.hpp>
#include <IntCurveSurface_TheQuadCurvFuncOfTheQuadCurvExactHInter.hpp>

#include "IntCurveSurface_QuadricCurveExactInterUtils.hpp"

IntCurveSurface_TheQuadCurvExactHInter::IntCurveSurface_TheQuadCurvExactHInter(
  const occ::handle<Adaptor3d_Surface>& S,
  const occ::handle<Adaptor3d_Curve>&   C)
    : nbpnts(-1),
      nbintv(-1)
{
  IntCurveSurface_QuadricCurveExactInterUtils::PerformIntersection<
    occ::handle<Adaptor3d_Surface>,
    Adaptor3d_HSurfaceTool,
    occ::handle<Adaptor3d_Curve>,
    IntCurveSurface_TheHCurveTool,
    IntCurveSurface_TheQuadCurvFuncOfTheQuadCurvExactHInter>(S, C, pnts, intv, nbpnts, nbintv);
}

bool IntCurveSurface_TheQuadCurvExactHInter::IsDone() const
{
  return (nbpnts != -1);
}

int IntCurveSurface_TheQuadCurvExactHInter::NbRoots() const
{
  return nbpnts;
}

int IntCurveSurface_TheQuadCurvExactHInter::NbIntervals() const
{
  return nbintv;
}

double IntCurveSurface_TheQuadCurvExactHInter::Root(const int Index) const
{
  return pnts(Index);
}

void IntCurveSurface_TheQuadCurvExactHInter::Intervals(const int Index, double& a, double& b) const
{
  int Index2 = Index + Index - 1;
  a          = intv(Index2);
  b          = intv(Index2 + 1);
}
