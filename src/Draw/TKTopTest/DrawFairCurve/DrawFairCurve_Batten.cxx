#include <DrawFairCurve_Batten.hpp>
#include <FairCurve_Batten.hpp>
#include <Geom2d_BSplineCurve.hpp>
#include <GeomTools_Curve2dSet.hpp>
#include <gp_Pnt2d.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(DrawFairCurve_Batten, DrawTrSurf_BSplineCurve2d)

DrawFairCurve_Batten::DrawFairCurve_Batten(void* const TheBatten)
    : DrawTrSurf_BSplineCurve2d(((FairCurve_Batten*)TheBatten)->Curve()),
      MyBatten(TheBatten)

{
  Compute();
  ShowCurvature();
}

void DrawFairCurve_Batten::Compute()
{
  FairCurve_AnalysisCode Iana;
  ((FairCurve_Batten*)MyBatten)->Compute(Iana, 50, 1.0e-2);
  curv = ((FairCurve_Batten*)MyBatten)->Curve();
}

void DrawFairCurve_Batten::SetPoint(const int Side, const gp_Pnt2d& Point)
{
  if (Side == 1)
  {
    ((FairCurve_Batten*)MyBatten)->SetP1(Point);
  }
  else
  {
    ((FairCurve_Batten*)MyBatten)->SetP2(Point);
  }
  Compute();
}

void DrawFairCurve_Batten::SetAngle(const int Side, const double Angle)
{
  if (Side == 1)
  {
    ((FairCurve_Batten*)MyBatten)->SetAngle1(Angle * M_PI / 180);
    if (((FairCurve_Batten*)MyBatten)->GetConstraintOrder1() == 0)
    {
      ((FairCurve_Batten*)MyBatten)->SetConstraintOrder1(1);
    }
  }
  else
  {
    ((FairCurve_Batten*)MyBatten)->SetAngle2(Angle * M_PI / 180);
    if (((FairCurve_Batten*)MyBatten)->GetConstraintOrder2() == 0)
    {
      ((FairCurve_Batten*)MyBatten)->SetConstraintOrder2(1);
    }
  }
  Compute();
}

void DrawFairCurve_Batten::SetSliding(const double Length)
{
  ((FairCurve_Batten*)MyBatten)->SetFreeSliding(false);
  ((FairCurve_Batten*)MyBatten)->SetSlidingFactor(Length);
  Compute();
}

void DrawFairCurve_Batten::SetHeight(const double Height)
{
  ((FairCurve_Batten*)MyBatten)->SetHeight(Height);
  Compute();
}

void DrawFairCurve_Batten::SetSlope(const double Slope)
{
  ((FairCurve_Batten*)MyBatten)->SetSlope(Slope);
  Compute();
}

double DrawFairCurve_Batten::GetAngle(const int Side) const
{
  if (Side == 1)
    return ((FairCurve_Batten*)MyBatten)->GetAngle1();
  else
    return ((FairCurve_Batten*)MyBatten)->GetAngle2();
}

double DrawFairCurve_Batten::GetSliding() const
{
  return ((FairCurve_Batten*)MyBatten)->GetSlidingFactor();
}

void DrawFairCurve_Batten::FreeSliding()
{
  ((FairCurve_Batten*)MyBatten)->SetFreeSliding(true);
  Compute();
}

void DrawFairCurve_Batten::FreeAngle(const int Side)
{
  if (Side == 1)
    ((FairCurve_Batten*)MyBatten)->SetConstraintOrder1(0);
  else
    ((FairCurve_Batten*)MyBatten)->SetConstraintOrder2(0);

  Compute();
}

void DrawFairCurve_Batten::Dump(Standard_OStream& S) const
{
  GeomTools_Curve2dSet::PrintCurve2d(curv, S);
  ((FairCurve_Batten*)MyBatten)->Dump(S);
}
