#include <ElCLib.hpp>
#include <Extrema_ExtElC.hpp>
#include <Extrema_POnCurv.hpp>
#include <GC_MakeArcOfCircle.hpp>
#include <gce_MakeCirc.hpp>
#include <gce_MakeLin.hpp>
#include <Geom_Circle.hpp>
#include <Geom_TrimmedCurve.hpp>
#include <gp_Circ.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <StdFail_NotDone.hpp>

//=================================================================================================

GC_MakeArcOfCircle::GC_MakeArcOfCircle(const gp_Pnt& P1, const gp_Pnt& P2, const gp_Pnt& P3)
{
  bool sense;
  //
  gce_MakeCirc Cir(P1, P2, P3);
  TheError = Cir.Status();
  if (TheError == gce_Done)
  {
    double  Alpha1, Alpha3; //,Alpha2
    gp_Circ C(Cir.Value());
    // modified by NIZNHY-PKV Thu Mar  3 10:53:02 2005f
    // Alpha1 is always =0.
    // Alpha1 = ElCLib::Parameter(C,P1);
    // Alpha2 = ElCLib::Parameter(C,P2);
    // Alpha3 = ElCLib::Parameter(C,P3);
    //
    // if (Alpha2 >= Alpha1 && Alpha2 <= Alpha3) sense = true;
    // else if (Alpha1 <= Alpha3 && Alpha2 >= Alpha3 ) sense = true;
    // else sense = false;
    //
    Alpha1 = 0.;
    Alpha3 = ElCLib::Parameter(C, P3);
    sense  = true;
    // modified by NIZNHY-PKV Thu Mar  3 10:53:04 2005t

    occ::handle<Geom_Circle> Circ = new Geom_Circle(C);
    TheArc                        = new Geom_TrimmedCurve(Circ, Alpha1, Alpha3, sense);
  }
}

//=================================================================================================

GC_MakeArcOfCircle::GC_MakeArcOfCircle(const gp_Pnt& P1, const gp_Vec& V, const gp_Pnt& P2)
{
  gp_Circ     cir;
  gce_MakeLin Corde(P1, P2);
  TheError = Corde.Status();
  if (TheError == gce_Done)
  {
    gp_Lin corde(Corde.Value());
    gp_Dir dir(corde.Direction());
    gp_Dir dbid(V);
    gp_Dir Daxe(dbid ^ dir);
    gp_Dir Dir1(Daxe ^ dir);
    gp_Lin bis(gp_Pnt((P1.X() + P2.X()) / 2., (P1.Y() + P2.Y()) / 2., (P1.Z() + P2.Z()) / 2.),
               Dir1);
    gp_Dir d(dbid ^ Daxe);
    gp_Lin norm(P1, d);
    double Tol = 0.000000001;
    Extrema_ExtElC distmin(bis, norm, Tol);
    if (!distmin.IsDone())
    {
      TheError = gce_IntersectionError;
    }
    else
    {
      int nbext = distmin.NbExt();
      if (nbext == 0)
      {
        TheError = gce_IntersectionError;
      }
      else
      {
        double          TheDist = RealLast();
        gp_Pnt          pInt, pon1, pon2;
        int             i = 1;
        Extrema_POnCurv Pon1, Pon2;
        while (i <= nbext)
        {
          if (distmin.SquareDistance(i) < TheDist)
          {
            TheDist = distmin.SquareDistance(i);
            distmin.Points(i, Pon1, Pon2);
            pon1 = Pon1.Value();
            pon2 = Pon2.Value();
            pInt = gp_Pnt((pon1.XYZ() + pon2.XYZ()) / 2.);
          }
          i++;
        }
        double Rad                      = (pInt.Distance(P1) + pInt.Distance(P2)) / 2.;
        cir                             = gp_Circ(gp_Ax2(pInt, Daxe, d), Rad);
        double                   Alpha1 = ElCLib::Parameter(cir, P1);
        double                   Alpha3 = ElCLib::Parameter(cir, P2);
        occ::handle<Geom_Circle> Circ   = new Geom_Circle(cir);
        TheArc                          = new Geom_TrimmedCurve(Circ, Alpha1, Alpha3, true);
      }
    }
  }
}

//=================================================================================================

GC_MakeArcOfCircle::GC_MakeArcOfCircle(const gp_Circ& Circ,
                                       const gp_Pnt&  P1,
                                       const gp_Pnt&  P2,
                                       const bool     Sense)
{
  double                   Alpha1 = ElCLib::Parameter(Circ, P1);
  double                   Alpha2 = ElCLib::Parameter(Circ, P2);
  occ::handle<Geom_Circle> C      = new Geom_Circle(Circ);
  TheArc                          = new Geom_TrimmedCurve(C, Alpha1, Alpha2, Sense);
  TheError                        = gce_Done;
}

//=================================================================================================

GC_MakeArcOfCircle::GC_MakeArcOfCircle(const gp_Circ& Circ,
                                       const gp_Pnt&  P,
                                       const double   Alpha,
                                       const bool     Sense)
{
  double                   Alphafirst = ElCLib::Parameter(Circ, P);
  occ::handle<Geom_Circle> C          = new Geom_Circle(Circ);
  TheArc                              = new Geom_TrimmedCurve(C, Alphafirst, Alpha, Sense);
  TheError                            = gce_Done;
}

//=================================================================================================

GC_MakeArcOfCircle::GC_MakeArcOfCircle(const gp_Circ& Circ,
                                       const double   Alpha1,
                                       const double   Alpha2,
                                       const bool     Sense)
{
  occ::handle<Geom_Circle> C = new Geom_Circle(Circ);
  TheArc                     = new Geom_TrimmedCurve(C, Alpha1, Alpha2, Sense);
  TheError                   = gce_Done;
}

//=================================================================================================

const occ::handle<Geom_TrimmedCurve>& GC_MakeArcOfCircle::Value() const
{
  StdFail_NotDone_Raise_if(TheError != gce_Done, "GC_MakeArcOfCircle::Value() - no result");
  return TheArc;
}
