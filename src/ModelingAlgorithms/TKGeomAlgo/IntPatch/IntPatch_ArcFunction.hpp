#pragma once

#include <Adaptor2d_Curve2d.hpp>
#include <Adaptor3d_Surface.hpp>
#include <IntSurf_Quadric.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Sequence.hpp>
#include <math_FunctionWithDerivative.hpp>

class IntPatch_ArcFunction : public math_FunctionWithDerivative
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IntPatch_ArcFunction();

  void SetQuadric(const IntSurf_Quadric& Q);

  void Set(const occ::handle<Adaptor2d_Curve2d>& A);

  void Set(const occ::handle<Adaptor3d_Surface>& S);

  Standard_EXPORT bool Value(const double X, double& F) override;

  Standard_EXPORT bool Derivative(const double X, double& D) override;

  Standard_EXPORT bool Values(const double X, double& F, double& D) override;

  Standard_EXPORT int NbSamples() const;

  Standard_EXPORT int GetStateNumber() override;

  const gp_Pnt& Valpoint(const int Index) const;

  const IntSurf_Quadric& Quadric() const;

  const occ::handle<Adaptor2d_Curve2d>& Arc() const;

  const occ::handle<Adaptor3d_Surface>& Surface() const;

  const gp_Pnt& LastComputedPoint() const;

private:
  occ::handle<Adaptor2d_Curve2d> myArc;
  occ::handle<Adaptor3d_Surface> mySurf;
  IntSurf_Quadric                myQuad;
  gp_Pnt                         ptsol;
  NCollection_Sequence<gp_Pnt>   seqpt;
};

inline const gp_Pnt& IntPatch_ArcFunction::Valpoint(const int Index) const
{
  return seqpt(Index);
}

inline void IntPatch_ArcFunction::Set(const occ::handle<Adaptor2d_Curve2d>& A)
{
  myArc = A;
  seqpt.Clear();
}

inline void IntPatch_ArcFunction::Set(const occ::handle<Adaptor3d_Surface>& S)
{
  mySurf = S;
  seqpt.Clear();
}

inline void IntPatch_ArcFunction::SetQuadric(const IntSurf_Quadric& Q)
{
  myQuad = Q;
  seqpt.Clear();
}

inline const IntSurf_Quadric& IntPatch_ArcFunction::Quadric() const
{
  return (myQuad);
}

inline const occ::handle<Adaptor2d_Curve2d>& IntPatch_ArcFunction::Arc() const
{
  return (myArc);
}

inline const occ::handle<Adaptor3d_Surface>& IntPatch_ArcFunction::Surface() const
{
  return (mySurf);
}

inline const gp_Pnt& IntPatch_ArcFunction::LastComputedPoint() const
{
  return ptsol;
}
