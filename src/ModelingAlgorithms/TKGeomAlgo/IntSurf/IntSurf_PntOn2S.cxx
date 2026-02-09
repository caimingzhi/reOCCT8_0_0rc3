

#include <IntSurf_PntOn2S.hpp>

IntSurf_PntOn2S::IntSurf_PntOn2S()
    : pt(0, 0, 0),
      u1(0),
      v1(0),
      u2(0),
      v2(0)
{
}

void IntSurf_PntOn2S::SetValue(const gp_Pnt& Pt, const bool OnFirst, const double U, const double V)
{

  pt = Pt;
  if (OnFirst)
  {
    u1 = U;
    v1 = V;
  }
  else
  {
    u2 = U;
    v2 = V;
  }
}

void IntSurf_PntOn2S::SetValue(const bool OnFirst, const double U, const double V)
{

  if (OnFirst)
  {
    u1 = U;
    v1 = V;
  }
  else
  {
    u2 = U;
    v2 = V;
  }
}

gp_Pnt2d IntSurf_PntOn2S::ValueOnSurface(const bool OnFirst) const
{
  gp_Pnt2d PointOnSurf;
  if (OnFirst)
    PointOnSurf.SetCoord(u1, v1);
  else
    PointOnSurf.SetCoord(u2, v2);
  return PointOnSurf;
}

void IntSurf_PntOn2S::ParametersOnSurface(const bool OnFirst, double& U, double& V) const
{
  if (OnFirst)
  {
    U = u1;
    V = v1;
  }
  else
  {
    U = u2;
    V = v2;
  }
}

bool IntSurf_PntOn2S::IsSame(const IntSurf_PntOn2S& theOterPoint,
                             const double           theTol3D,
                             const double           theTol2D) const
{
  if (pt.SquareDistance(theOterPoint.Value()) > theTol3D * theTol3D)
    return false;

  if (theTol2D < 0.0)
  {
    return true;
  }

  double aU1 = 0.0, aV1 = 0.0, aU2 = 0.0, aV2 = 0.0;
  theOterPoint.Parameters(aU1, aV1, aU2, aV2);

  gp_Pnt2d aP1(u1, v1), aP2(aU1, aV1);

  if (!aP1.IsEqual(aP2, theTol2D))
    return false;

  aP1.SetCoord(u2, v2);
  aP2.SetCoord(aU2, aV2);

  return aP1.IsEqual(aP2, theTol2D);
}
