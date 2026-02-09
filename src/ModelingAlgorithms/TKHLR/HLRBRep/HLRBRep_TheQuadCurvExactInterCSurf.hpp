#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <NCollection_Sequence.hpp>
#include <Standard_Boolean.hpp>
class HLRBRep_Surface;
class HLRBRep_SurfaceTool;
class gp_Lin;
class HLRBRep_LineTool;
class HLRBRep_TheQuadCurvFuncOfTheQuadCurvExactInterCSurf;

class HLRBRep_TheQuadCurvExactInterCSurf
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT HLRBRep_TheQuadCurvExactInterCSurf(HLRBRep_Surface* S, const gp_Lin& C);

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
