#include <Adaptor2d_Curve2d.hpp>
#include <gp_Pnt2d.hpp>
#include <IntPatch_PolyArc.hpp>
#include <Standard_ConstructionError.hpp>

inline void MinMax(const double a1, const double a2, double& amin, double& amax)
{
  if (a1 < a2)
  {
    amin = a1;
    amax = a2;
  }
  else
  {
    amin = a2;
    amax = a1;
  }
}

IntPatch_PolyArc::IntPatch_PolyArc(const occ::handle<Adaptor2d_Curve2d>& Line,
                                   const int                             NbSample,
                                   const double                          aPdeb,
                                   const double                          aPfin,
                                   const Bnd_Box2d&                      BoxOtherPolygon)
    : brise(1, std::max(1, NbSample)),
      param(1, std::max(1, NbSample)),
      offsetx(0.0),
      offsety(0.0)
{
  double   Pdeb = aPdeb;
  double   Pfin = aPfin;
  gp_Pnt2d p2d;

  if (Pdeb == RealFirst() || Pfin == RealLast() || NbSample <= 1)
  {
    throw Standard_ConstructionError();
  }

  int IndexInf = NbSample + 1;
  int IndexSup = 0;

  double bx0, by0, bxmin, bxmax, bymin, bymax, r, r2;

  BoxOtherPolygon.Get(bxmin, bymin, bxmax, bymax);
  r   = (bxmax - bxmin) + (bymax - bymin);
  bx0 = (bxmax + bxmin) * 0.5;
  by0 = (bymax + bymin) * 0.5;

  double Pas;
  double X, Y, Xs, Ys, Xm, Ym, XXs, YYs;

  r *= 0.8;
  r2         = r * r * 49.;
  int nbloop = 0;

  do
  {
    nbloop++;
    Pas      = (Pfin - Pdeb) / (NbSample - 1);
    param(1) = Pdeb;
    Line->D0(Pdeb, p2d);
    Xs = p2d.X();
    Ys = p2d.Y();
    brise(1).SetCoord(Xs, Ys);

    myBox.SetVoid();

    myBox.Add(brise(1));
    myError = 0.;

    for (int i = 2; i <= NbSample; i++)
    {
      param(i) = Pdeb + (i - 1) * Pas;
      Line->D0(param(i), p2d);
      X = p2d.X();
      Y = p2d.Y();
      brise(i).SetCoord(X, Y);
      XXs = 0.5 * (Xs + X);
      YYs = 0.5 * (Ys + Y);

      bool isMidPtInBox = (std::abs(bx0 - XXs) + std::abs(by0 - YYs)) < r;
      bool isSegOut     = true;
      if (!isMidPtInBox)
      {
        double d = (X - Xs) * (X - Xs) + (Y - Ys) * (Y - Ys);
        if (d > r2)
        {
          double xmin, xmax, ymin, ymax;
          MinMax(Xs, X, xmin, xmax);
          MinMax(Ys, Y, ymin, ymax);
          isSegOut = (xmax < bxmin || xmin > bxmax || ymax < bymin || ymin > bymax);
        }
      }
      if (isMidPtInBox || !isSegOut)
      {

        if (IndexInf > i)
          IndexInf = std::max(i - 2, 1);
        if (IndexSup < i)
          IndexSup = std::min(i + 1, NbSample);
      }

      myBox.Add(brise(i));
      Line->D0(param(i) - Pas * 0.5, p2d);
      Xm      = p2d.X() - XXs;
      Ym      = p2d.Y() - YYs;
      Xm      = std::sqrt(Xm * Xm + Ym * Ym);
      myError = std::max(myError, Xm);
      Xs      = X;
      Ys      = Y;
    }
    if (IndexInf > IndexSup)
    {
      r += r;
      r2 = r * r * 49.;
    }
    else
    {

      if ((IndexSup - IndexInf) < (NbSample / 2))
      {

        nbloop = 10;

        Pdeb = param(IndexInf);
        Pfin = param(IndexSup);

        IndexInf = NbSample + 1;
        IndexSup = 0;
      }
    }
  } while ((IndexInf > IndexSup) && nbloop <= 10);
  myError *= 1.2;
  if (myError < 0.00000001)
    myError = 0.00000001;
  myBox.Enlarge(myError);

  ferme = (Line->Value(aPdeb).Distance(Line->Value(aPfin)) <= 1e-7);
}

bool IntPatch_PolyArc::Closed() const
{
  return ferme;
}

int IntPatch_PolyArc::NbPoints() const
{
  return brise.Length();
}

gp_Pnt2d IntPatch_PolyArc::Point(const int Index) const
{
  if (offsetx == 0.0 && offsety == 0.0)
    return (brise(Index));

  const gp_Pnt2d& P = brise(Index);
  return (gp_Pnt2d(P.X() + offsetx, P.Y() + offsety));
}

double IntPatch_PolyArc::Parameter(const int Index) const
{
  return param(Index);
}

void IntPatch_PolyArc::SetOffset(const double ox, const double oy)
{
  double xmin, ymin, xmax, ymax, g;
  myBox.Get(xmin, ymin, xmax, ymax);
  g = myBox.GetGap();

  myBox.SetVoid();

  myBox.Update(xmin - offsetx, ymin - offsety, xmax - offsetx, ymax - offsety);
  offsetx = ox;
  offsety = oy;
  myBox.Update(xmin + offsetx, ymin + offsety, xmax + offsetx, ymax + offsety);
  myBox.SetGap(g);
}
