

#include <IntCurveSurface_TheHCurveTool.hpp>

#include <Adaptor3d_Curve.hpp>
#include <GeomAbs_CurveType.hpp>
#include <GeomAbs_Shape.hpp>
#include <Geom_BSplineCurve.hpp>
#include <Geom_BezierCurve.hpp>
#include <Standard_DomainError.hpp>
#include <Standard_NoSuchObject.hpp>
#include <Standard_OutOfRange.hpp>
#include <NCollection_Array1.hpp>
#include <gce_MakeLin.hpp>
#include <gp_Lin.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>

#define myMinPnts 5

int IntCurveSurface_TheHCurveTool::NbSamples(const occ::handle<Adaptor3d_Curve>& C,
                                             const double                        U0,
                                             const double                        U1)
{
  GeomAbs_CurveType typC     = C->GetType();
  const double      nbsOther = 10.0;
  double            nbs      = nbsOther;

  if (typC == GeomAbs_Line)
    nbs = 2;
  else if (typC == GeomAbs_BezierCurve)
    nbs = 3 + C->NbPoles();
  else if (typC == GeomAbs_BSplineCurve)
  {
    nbs = C->NbKnots();
    nbs *= C->Degree();
    nbs *= C->LastParameter() - C->FirstParameter();
    nbs /= U1 - U0;
    if (nbs < 2.0)
      nbs = 2;
  }
  if (nbs > 50)
    nbs = 50;
  return ((int)nbs);
}

void IntCurveSurface_TheHCurveTool::SamplePars(const occ::handle<Adaptor3d_Curve>&       C,
                                               const double                              U0,
                                               const double                              U1,
                                               const double                              Defl,
                                               const int                                 NbMin,
                                               occ::handle<NCollection_HArray1<double>>& Pars)
{
  GeomAbs_CurveType typC     = C->GetType();
  const double      nbsOther = 10.0;
  double            nbs      = nbsOther;

  if (typC == GeomAbs_Line)
    nbs = 2;
  else if (typC == GeomAbs_BezierCurve)
  {
    nbs = 3 + C->NbPoles();
  }

  if (typC != GeomAbs_BSplineCurve)
  {
    if (nbs > 50)
      nbs = 50;
    int nnbs = (int)nbs;

    Pars      = new NCollection_HArray1<double>(1, nnbs);
    double du = (U1 - U0) / (nnbs - 1);

    Pars->SetValue(1, U0);
    Pars->SetValue(nnbs, U1);
    int    i;
    double u;
    for (i = 2, u = U0 + du; i < nnbs; ++i, u += du)
    {
      Pars->SetValue(i, u);
    }
    return;
  }

  const occ::handle<Geom_BSplineCurve>& aBC = C->BSpline();

  int    i, j, k, nbi;
  double t1, t2, dt;
  int    ui1 = aBC->FirstUKnotIndex();
  int    ui2 = aBC->LastUKnotIndex();

  for (i = ui1; i < ui2; ++i)
  {
    if (U0 >= aBC->Knot(i) && U0 < aBC->Knot(i + 1))
    {
      ui1 = i;
      break;
    }
  }

  for (i = ui2; i > ui1; --i)
  {
    if (U1 <= aBC->Knot(i) && U1 > aBC->Knot(i - 1))
    {
      ui2 = i;
      break;
    }
  }

  int nbsu = ui2 - ui1 + 1;
  nbsu += (nbsu - 1) * (aBC->Degree() - 1);
  bool bUniform = false;
  if (nbsu < NbMin)
  {
    nbsu     = NbMin;
    bUniform = true;
  }

  NCollection_Array1<double> aPars(1, nbsu);
  NCollection_Array1<bool>   aFlg(1, nbsu);

  if (bUniform)
  {
    t1          = U0;
    t2          = U1;
    dt          = (t2 - t1) / (nbsu - 1);
    aPars(1)    = t1;
    aFlg(1)     = false;
    aPars(nbsu) = t2;
    aFlg(nbsu)  = false;
    for (i = 2, t1 += dt; i < nbsu; ++i, t1 += dt)
    {
      aPars(i) = t1;
      aFlg(i)  = false;
    }
  }
  else
  {
    nbi = aBC->Degree();
    k   = 0;
    t1  = U0;
    for (i = ui1 + 1; i <= ui2; ++i)
    {
      if (i == ui2)
        t2 = U1;
      else
        t2 = aBC->Knot(i);
      dt = (t2 - t1) / nbi;
      j  = 1;
      do
      {
        ++k;
        aPars(k) = t1;
        aFlg(k)  = false;
        t1 += dt;
      } while (++j <= nbi);
      t1 = t2;
    }
    ++k;
    aPars(k) = t1;
  }

  double aDefl2 = std::max(Defl * Defl, 1.e-9);
  double tol    = std::max(0.01 * aDefl2, 1.e-9);
  int    l;

  int NbSamples = 2;
  aFlg(1)       = true;
  aFlg(nbsu)    = true;
  j             = 1;
  bool bCont    = true;
  while (j < nbsu - 1 && bCont)
  {
    if (aFlg(j + 1))
    {
      ++j;
      continue;
    }

    t2        = aPars(j);
    gp_Pnt p1 = aBC->Value(t2);
    for (k = j + 2; k <= nbsu; ++k)
    {
      t2        = aPars(k);
      gp_Pnt p2 = aBC->Value(t2);

      if (p1.SquareDistance(p2) <= tol)
        continue;

      gce_MakeLin   MkLin(p1, p2);
      const gp_Lin& lin = MkLin.Value();
      bool          ok  = true;
      for (l = j + 1; l < k; ++l)
      {
        if (aFlg(l))
        {
          ok = false;
          break;
        }

        gp_Pnt pp = aBC->Value(aPars(l));
        double d  = lin.SquareDistance(pp);

        if (d <= aDefl2)
          continue;

        ok = false;
        break;
      }

      if (!ok)
      {
        j       = k - 1;
        aFlg(j) = true;
        ++NbSamples;
        break;
      }

      if (aFlg(k))
      {
        j = k;
        break;
      }
    }

    if (k >= nbsu)
      bCont = false;
  }

  if (NbSamples < myMinPnts)
  {

    NbSamples = myMinPnts;
    Pars      = new NCollection_HArray1<double>(1, NbSamples);
    t1        = U0;
    t2        = U1;
    dt        = (t2 - t1) / (NbSamples - 1);
    Pars->SetValue(1, t1);
    Pars->SetValue(NbSamples, t2);
    for (i = 2, t1 += dt; i < NbSamples; ++i, t1 += dt)
    {
      Pars->SetValue(i, t1);
    }
    return;
  }

  Pars = new NCollection_HArray1<double>(1, NbSamples);
  j    = 0;
  for (i = 1; i <= nbsu; ++i)
  {
    if (aFlg(i))
    {
      ++j;
      Pars->SetValue(j, aPars(i));
    }
  }
}
