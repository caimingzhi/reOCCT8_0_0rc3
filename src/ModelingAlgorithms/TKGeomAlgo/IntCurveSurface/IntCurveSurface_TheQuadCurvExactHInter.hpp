#pragma once

#include <Adaptor3d_Curve.hpp>
#include <Adaptor3d_Surface.hpp>
#include <NCollection_Sequence.hpp>

class Adaptor3d_HSurfaceTool;
class IntCurveSurface_TheHCurveTool;
class IntCurveSurface_TheQuadCurvFuncOfTheQuadCurvExactHInter;

class IntCurveSurface_TheQuadCurvExactHInter
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IntCurveSurface_TheQuadCurvExactHInter(const occ::handle<Adaptor3d_Surface>& S,
                                                         const occ::handle<Adaptor3d_Curve>&   C);

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT int NbRoots() const;

  Standard_EXPORT double Root(const int Index) const;

  Standard_EXPORT int NbIntervals() const;

  Standard_EXPORT void Intervals(const int Index, double& U1, double& U2) const;

private:
  int                          nbpnts;
  NCollection_Sequence<double> pnts;
  int                          nbintv;
  NCollection_Sequence<double> intv;
};
