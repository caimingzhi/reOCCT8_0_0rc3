

#include <gp_Pnt2d.hpp>
#include <Law_Interpol.hpp>
#include <Law_Interpolate.hpp>
#include <Precision.hpp>
#include <Standard_Type.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Law_Interpol, Law_BSpFunc)

#ifdef OCCT_DEBUG
#endif

Law_Interpol::Law_Interpol() = default;

void Law_Interpol::Set(const NCollection_Array1<gp_Pnt2d>& ParAndRad, const bool Periodic)
{
  int l   = ParAndRad.Lower();
  int nbp = ParAndRad.Length();

  occ::handle<NCollection_HArray1<double>> par = new NCollection_HArray1<double>(1, nbp);
  occ::handle<NCollection_HArray1<double>> rad;
  if (Periodic)
    rad = new NCollection_HArray1<double>(1, nbp - 1);
  else
    rad = new NCollection_HArray1<double>(1, nbp);
  double x, y;
  int    i;
  for (i = 1; i <= nbp; i++)
  {
    ParAndRad(l + i - 1).Coord(x, y);
    par->SetValue(i, x);
    if (!Periodic || i != nbp)
      rad->SetValue(i, y);
  }
  Law_Interpolate inter(rad, par, Periodic, Precision::Confusion());
  inter.Perform();
  SetCurve(inter.Curve());
#ifdef OCCT_DEBUG
#endif
}

void Law_Interpol::SetInRelative(const NCollection_Array1<gp_Pnt2d>& ParAndRad,
                                 const double                        Ud,
                                 const double                        Uf,
                                 const bool                          Periodic)
{
  int                                      l = ParAndRad.Lower(), u = ParAndRad.Upper();
  double                                   wd = ParAndRad(l).X(), wf = ParAndRad(u).X();
  int                                      nbp = ParAndRad.Length();
  occ::handle<NCollection_HArray1<double>> par = new NCollection_HArray1<double>(1, nbp);
  occ::handle<NCollection_HArray1<double>> rad;
  if (Periodic)
    rad = new NCollection_HArray1<double>(1, nbp - 1);
  else
    rad = new NCollection_HArray1<double>(1, nbp);
  double x, y;
  int    i;
  for (i = 1; i <= nbp; i++)
  {
    ParAndRad(l + i - 1).Coord(x, y);
    par->SetValue(i, (Uf * (x - wd) + Ud * (wf - x)) / (wf - wd));
    if (!Periodic || i != nbp)
      rad->SetValue(i, y);
  }
  Law_Interpolate inter(rad, par, Periodic, Precision::Confusion());
  inter.Perform();
  SetCurve(inter.Curve());
#ifdef OCCT_DEBUG
#endif
}

void Law_Interpol::Set(const NCollection_Array1<gp_Pnt2d>& ParAndRad,
                       const double                        Dd,
                       const double                        Df,
                       const bool                          Periodic)
{
  int l   = ParAndRad.Lower();
  int nbp = ParAndRad.Length();

  occ::handle<NCollection_HArray1<double>> par = new NCollection_HArray1<double>(1, nbp);
  occ::handle<NCollection_HArray1<double>> rad;
  if (Periodic)
    rad = new NCollection_HArray1<double>(1, nbp - 1);
  else
    rad = new NCollection_HArray1<double>(1, nbp);
  double x, y;
  int    i;
  for (i = 1; i <= nbp; i++)
  {
    ParAndRad(l + i - 1).Coord(x, y);
    par->SetValue(i, x);
    if (!Periodic || i != nbp)
      rad->SetValue(i, y);
  }
  Law_Interpolate inter(rad, par, Periodic, Precision::Confusion());
  inter.Load(Dd, Df);
  inter.Perform();
  SetCurve(inter.Curve());
}

void Law_Interpol::SetInRelative(const NCollection_Array1<gp_Pnt2d>& ParAndRad,
                                 const double                        Ud,
                                 const double                        Uf,
                                 const double                        Dd,
                                 const double                        Df,
                                 const bool                          Periodic)
{
  int                                      l = ParAndRad.Lower(), u = ParAndRad.Upper();
  double                                   wd = ParAndRad(l).X(), wf = ParAndRad(u).X();
  int                                      nbp = ParAndRad.Length();
  occ::handle<NCollection_HArray1<double>> par = new NCollection_HArray1<double>(1, nbp);
  occ::handle<NCollection_HArray1<double>> rad;
  if (Periodic)
    rad = new NCollection_HArray1<double>(1, nbp - 1);
  else
    rad = new NCollection_HArray1<double>(1, nbp);
  double x, y;
  int    i;
  for (i = 1; i <= nbp; i++)
  {
    ParAndRad(l + i - 1).Coord(x, y);
    par->SetValue(i, (Uf * (x - wd) + Ud * (wf - x)) / (wf - wd));
    if (!Periodic || i != nbp)
      rad->SetValue(i, y);
  }
  Law_Interpolate inter(rad, par, Periodic, Precision::Confusion());
  inter.Load(Dd, Df);
  inter.Perform();
  SetCurve(inter.Curve());
}
