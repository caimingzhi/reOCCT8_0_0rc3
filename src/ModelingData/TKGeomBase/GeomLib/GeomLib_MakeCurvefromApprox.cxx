#include <AdvApprox_ApproxAFunction.hpp>
#include <Geom2d_BSplineCurve.hpp>
#include <Geom_BSplineCurve.hpp>
#include <GeomLib_MakeCurvefromApprox.hpp>
#include <gp_Pnt2d.hpp>
#include <Standard_OutOfRange.hpp>
#include <StdFail_NotDone.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array1.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_HArray1.hpp>

GeomLib_MakeCurvefromApprox::GeomLib_MakeCurvefromApprox(const AdvApprox_ApproxAFunction& Approx)
    : myApprox(Approx)
{
}

int GeomLib_MakeCurvefromApprox::Nb1DSpaces() const
{
  return myApprox.NumSubSpaces(1);
}

int GeomLib_MakeCurvefromApprox::Nb2DSpaces() const
{
  return myApprox.NumSubSpaces(2);
}

int GeomLib_MakeCurvefromApprox::Nb3DSpaces() const
{
  return myApprox.NumSubSpaces(3);
}

occ::handle<Geom2d_BSplineCurve> GeomLib_MakeCurvefromApprox::Curve2d(const int Index2d) const
{
  Standard_OutOfRange_Raise_if(Index2d < 0 || Index2d > Nb2DSpaces(),
                               " GeomLib_MakeCurvefromApprox : Curve2d");
  StdFail_NotDone_Raise_if(!IsDone(), " GeomLib_MakeCurvefromApprox : Curve2d");

  NCollection_Array1<gp_Pnt2d> Poles(1, myApprox.NbPoles());
  NCollection_Array1<double>   Knots(1, myApprox.NbKnots());
  NCollection_Array1<int>      Mults(1, myApprox.NbKnots());

  myApprox.Poles2d(Index2d, Poles);
  Knots = myApprox.Knots()->Array1();
  Mults = myApprox.Multiplicities()->Array1();

  occ::handle<Geom2d_BSplineCurve> C =
    new Geom2d_BSplineCurve(Poles, Knots, Mults, myApprox.Degree());

  return C;
}

occ::handle<Geom2d_BSplineCurve> GeomLib_MakeCurvefromApprox::Curve2d(const int Index1d,
                                                                      const int Index2d) const
{
  Standard_OutOfRange_Raise_if(Index1d < 0 || Index1d > Nb1DSpaces() || Index2d < 0
                                 || Index2d > Nb2DSpaces(),
                               " GeomLib_MakeCurvefromApprox : Curve2d");
  StdFail_NotDone_Raise_if(!IsDone() && !myApprox.HasResult(),
                           " GeomLib_MakeCurvefromApprox : Curve2d");

  NCollection_Array1<gp_Pnt2d> Poles(1, myApprox.NbPoles());
  NCollection_Array1<double>   Weigths(1, myApprox.NbPoles());
  NCollection_Array1<double>   Knots(1, myApprox.NbKnots());
  NCollection_Array1<int>      Mults(1, myApprox.NbKnots());

  myApprox.Poles2d(Index2d, Poles);
  myApprox.Poles1d(Index1d, Weigths);
  Knots = myApprox.Knots()->Array1();
  Mults = myApprox.Multiplicities()->Array1();

  double X, Y, W;
  for (int i = 1; i <= myApprox.NbPoles(); i++)
  {
    W = Weigths(i);
    Poles(i).Coord(X, Y);
    Poles(i).SetCoord(X / W, Y / W);
  }

  occ::handle<Geom2d_BSplineCurve> C =
    new Geom2d_BSplineCurve(Poles, Knots, Mults, myApprox.Degree());

  return C;
}

occ::handle<Geom2d_BSplineCurve> GeomLib_MakeCurvefromApprox::Curve2dFromTwo1d(
  const int Index1d,
  const int Index2d) const
{
  Standard_OutOfRange_Raise_if(Index1d < 0 || Index1d > Nb1DSpaces() || Index2d < 0
                                 || Index2d > Nb1DSpaces(),
                               " GeomLib_MakeCurvefromApprox : Curve2d");
  StdFail_NotDone_Raise_if(!IsDone() && !myApprox.HasResult(),
                           " GeomLib_MakeCurvefromApprox : Curve2d");

  NCollection_Array1<gp_Pnt2d> Poles(1, myApprox.NbPoles());
  NCollection_Array1<double>   Poles1d1(1, myApprox.NbPoles());
  NCollection_Array1<double>   Poles1d2(1, myApprox.NbPoles());
  NCollection_Array1<double>   Knots(1, myApprox.NbKnots());
  NCollection_Array1<int>      Mults(1, myApprox.NbKnots());

  myApprox.Poles1d(Index2d, Poles1d2);
  myApprox.Poles1d(Index1d, Poles1d1);

  Knots = myApprox.Knots()->Array1();
  Mults = myApprox.Multiplicities()->Array1();

  for (int i = 1; i <= myApprox.NbPoles(); i++)
  {
    Poles(i).SetCoord(Poles1d1.Value(i), Poles1d2.Value(i));
  }

  occ::handle<Geom2d_BSplineCurve> C =
    new Geom2d_BSplineCurve(Poles, Knots, Mults, myApprox.Degree());

  return C;
}

occ::handle<Geom_BSplineCurve> GeomLib_MakeCurvefromApprox::Curve(const int Index3d) const
{
  Standard_OutOfRange_Raise_if(Index3d < 0 || Index3d > Nb3DSpaces(),
                               " GeomLib_MakeCurvefromApprox : Curve");
  StdFail_NotDone_Raise_if(!IsDone() && !myApprox.HasResult(),
                           " GeomLib_MakeCurvefromApprox : Curve");

  NCollection_Array1<gp_Pnt> Poles(1, myApprox.NbPoles());
  NCollection_Array1<double> Knots(1, myApprox.NbKnots());
  NCollection_Array1<int>    Mults(1, myApprox.NbKnots());

  myApprox.Poles(Index3d, Poles);
  Knots = myApprox.Knots()->Array1();
  Mults = myApprox.Multiplicities()->Array1();

  occ::handle<Geom_BSplineCurve> C = new Geom_BSplineCurve(Poles, Knots, Mults, myApprox.Degree());

  return C;
}

occ::handle<Geom_BSplineCurve> GeomLib_MakeCurvefromApprox::Curve(const int Index1d,
                                                                  const int Index3d) const
{
  Standard_OutOfRange_Raise_if(Index1d < 0 || Index1d > Nb1DSpaces() || Index3d < 0
                                 || Index3d > Nb3DSpaces(),
                               " GeomLib_MakeCurvefromApprox : Curve3d");
  StdFail_NotDone_Raise_if(!IsDone(), " GeomLib_MakeCurvefromApprox : Curve3d");

  NCollection_Array1<gp_Pnt> Poles(1, myApprox.NbPoles());
  NCollection_Array1<double> Weigths(1, myApprox.NbPoles());
  NCollection_Array1<double> Knots(1, myApprox.NbKnots());
  NCollection_Array1<int>    Mults(1, myApprox.NbKnots());

  myApprox.Poles(Index3d, Poles);
  myApprox.Poles1d(Index1d, Weigths);
  Knots = myApprox.Knots()->Array1();
  Mults = myApprox.Multiplicities()->Array1();

  double X, Y, Z, W;
  for (int i = 1; i <= myApprox.NbPoles(); i++)
  {
    W = Weigths(i);
    Poles(i).Coord(X, Y, Z);
    Poles(i).SetCoord(X / W, Y / W, Z / W);
  }

  occ::handle<Geom_BSplineCurve> C = new Geom_BSplineCurve(Poles, Knots, Mults, myApprox.Degree());

  return C;
}
