#include <IntPatch_ArcFunction.hpp>
#include <IntPatch_HInterTool.hpp>
#include <IntSurf_Quadric.hpp>

IntPatch_ArcFunction::IntPatch_ArcFunction() = default;

bool IntPatch_ArcFunction::Value(const double X, double& F)
{
  gp_Pnt2d p2d(myArc->Value(X));
  mySurf->D0(p2d.X(), p2d.Y(), ptsol);
  F = myQuad.Distance(ptsol);
  return true;
}

bool IntPatch_ArcFunction::Derivative(const double X, double& D)
{
  gp_Pnt2d p2d;
  gp_Vec2d d2d;
  gp_Vec   v, d1u, d1v;
  myArc->D1(X, p2d, d2d);
  mySurf->D1(p2d.X(), p2d.Y(), ptsol, d1u, d1v);
  v.SetLinearForm(d2d.X(), d1u, d2d.Y(), d1v);
  D = v.Dot(myQuad.Gradient(ptsol));
  return true;
}

bool IntPatch_ArcFunction::Values(const double X, double& F, double& D)
{
  gp_Pnt2d p2d;
  gp_Vec2d d2d;
  gp_Vec   d1u, d1v;

  gp_Vec v1, v2;
  myArc->D1(X, p2d, d2d);
  mySurf->D1(p2d.X(), p2d.Y(), ptsol, d1u, d1v);
  v1.SetLinearForm(d2d.X(), d1u, d2d.Y(), d1v);

  myQuad.ValAndGrad(ptsol, F, v2);
  D = v1.Dot(v2);
  return true;
}

int IntPatch_ArcFunction::GetStateNumber()
{
  seqpt.Append(ptsol);
  return seqpt.Length();
}

int IntPatch_ArcFunction::NbSamples() const
{
  return std::max(std::max(IntPatch_HInterTool::NbSamplesU(mySurf, 0., 0.),
                           IntPatch_HInterTool::NbSamplesV(mySurf, 0., 0.)),
                  IntPatch_HInterTool::NbSamplesOnArc(myArc));
}
