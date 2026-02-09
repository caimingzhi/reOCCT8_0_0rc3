#define TEST 0

#include <Standard_ConstructionError.hpp>
#include <Bnd_Box2d.hpp>
#include <gp_Pnt2d.hpp>
#include <NCollection_Array1.hpp>
#include <gp_Lin2d.hpp>
#include <gp_Vec2d.hpp>
#include <gp_Dir2d.hpp>

#define MAJORATION_DEFLECTION 1.5

IntCurve_Polygon2dGen::IntCurve_Polygon2dGen(const TheCurve&        C,
                                             const int              tNbPts,
                                             const IntRes2d_Domain& D,
                                             const double           Tol)
    : ThePnts(1, (tNbPts < 3) ? 6 : (tNbPts + tNbPts)),
      TheParams(1, (tNbPts < 3) ? 6 : (tNbPts + tNbPts)),
      TheIndex(1, (tNbPts < 3) ? 6 : (tNbPts + tNbPts))
{

  int NbPts      = (tNbPts < 3) ? 3 : tNbPts;
  TheMaxNbPoints = NbPts + NbPts;
  NbPntIn        = NbPts;

  Binf = D.FirstParameter();
  Bsup = D.LastParameter();

  double u  = Binf;
  double u1 = Bsup;
  double du = (u1 - u) / (double)(NbPts - 1);

  int i = 1;

  do
  {
    gp_Pnt2d P = TheCurveTool::Value(C, u);
    myBox.Add(P);
    TheIndex.SetValue(i, i);
    ThePnts.SetValue(i, P);
    TheParams.SetValue(i, u);
    u += du;
    i++;
  } while (i <= NbPts);

  TheDeflection = std::min(0.000000001, Tol / 100.);

  i = 1;
  u = D.FirstParameter();
  u += du * 0.5;

  do
  {
    gp_Pnt2d        Pm = TheCurveTool::Value(C, u);
    const gp_Pnt2d& P1 = ThePnts.Value(i);
    const gp_Pnt2d& P2 = ThePnts.Value(i + 1);

    u += du;
    i++;

    double dx, dy, t = 0;
    dx = P1.X() - P2.X();
    if (dx < 0)
      dx = -dx;
    dy = P1.Y() - P2.Y();
    if (dy < 0)
      dy = -dy;
    if (dx + dy > 1e-12)
    {
      gp_Lin2d L(P1, gp_Dir2d(gp_Vec2d(P1, P2)));
      t = L.Distance(Pm);
      if (t > TheDeflection)
      {
        TheDeflection = t;
      }
    }
  } while (i < NbPts);

  myBox.Enlarge(TheDeflection * MAJORATION_DEFLECTION);
  ClosedPolygon = false;
}

void IntCurve_Polygon2dGen::ComputeWithBox(const TheCurve& C, const Bnd_Box2d& BoxOtherPolygon)
{
  if (myBox.IsOut(BoxOtherPolygon))
  {
    NbPntIn = 2;
    myBox.SetVoid();
  }
  else
  {
    double bx0, bx1, by0, by1;
    BoxOtherPolygon.Get(bx0, by0, bx1, by1);

    bx0 -= TheDeflection;
    by0 -= TheDeflection;
    bx1 += TheDeflection;
    by1 += TheDeflection;
    int    MaxIndexUsed = 1;
    int    i, nbp;
    int    Rprec, Ri;
    double x, y;

    nbp = 0;
    x   = ThePnts.Value(TheIndex.Value(1)).X();
    y   = ThePnts.Value(TheIndex.Value(1)).Y();

    Rprec = CalculRegion(x, y, bx0, bx1, by0, by1);
    for (i = 2; i <= NbPntIn; i++)
    {
      const gp_Pnt2d& P2d = ThePnts.Value(TheIndex.Value(i));
      Ri                  = CalculRegion(P2d.X(), P2d.Y(), bx0, bx1, by0, by1);
      if ((Ri & Rprec) == 0)
      {
        if (nbp)
        {
          if (TheIndex.Value(nbp) != TheIndex.Value(i - 1))
          {
            nbp++;
            TheIndex.SetValue(nbp, TheIndex.Value(i - 1));
          }
        }
        else
        {
          nbp++;
          TheIndex.SetValue(nbp, TheIndex.Value(i - 1));
        }
        nbp++;
        TheIndex.SetValue(nbp, TheIndex.Value(i));
        if (TheIndex.Value(i) > MaxIndexUsed)
          MaxIndexUsed = TheIndex.Value(i);

        Rprec = Ri;
      }

      Rprec = Ri;
    }
    if (nbp == 1)
    {
      NbPntIn = 2;
      myBox.SetVoid();
    }
    else
    {
      myBox.SetVoid();
      if (nbp)
      {
        myBox.Add(ThePnts.Value(TheIndex.Value(1)));
      }
      double RatioDeflection;
      int    nbpassagedeflection = 0;

      do
      {
        nbpassagedeflection++;

        double NewDeflection = TheDeflection;

        for (i = 2; i <= nbp; i++)
        {
          int             Ii   = TheIndex.Value(i);
          int             Iim1 = TheIndex.Value(i - 1);
          const gp_Pnt2d& Pi   = ThePnts.Value(Ii);
          const gp_Pnt2d& Pim1 = ThePnts.Value(Iim1);
          myBox.Add(Pi);
          int Regi   = CalculRegion(Pi.X(), Pi.Y(), bx0, bx1, by0, by1);
          int Regim1 = CalculRegion(Pim1.X(), Pim1.Y(), bx0, bx1, by0, by1);
          if ((Regi & Regim1) == 0)
          {
            double   u  = 0.5 * (TheParams.Value(Ii) + TheParams.Value(Iim1));
            gp_Pnt2d Pm = TheCurveTool::Value(C, u);
            double   dx, dy, t = 0;
            dx = Pim1.X() - Pi.X();
            if (dx < 0)
              dx = -dx;
            dy = Pim1.Y() - Pi.Y();
            if (dy < 0)
              dy = -dy;
            if (dx + dy > 1e-12)
            {
              gp_Lin2d L(Pim1, gp_Dir2d(gp_Vec2d(Pim1, Pi)));
              t = L.Distance(Pm);
              if ((MaxIndexUsed < (TheMaxNbPoints - 1)) && (t > (TheDeflection * 0.5)))
              {
                const gp_Pnt2d& P1 = Pim1;
                nbp++;
                for (int j = nbp; j >= i + 1; j--)
                {
                  TheIndex.SetValue(j, TheIndex.Value(j - 1));
                }
                MaxIndexUsed++;
                TheIndex.SetValue(i, MaxIndexUsed);
                ThePnts.SetValue(MaxIndexUsed, Pm);
                TheParams.SetValue(MaxIndexUsed, u);

                double   u1m = 0.5 * (u + TheParams.Value(TheIndex.Value(i - 1)));
                gp_Pnt2d P1m = TheCurveTool::Value(C, u1m);
                gp_Lin2d L1m(P1, gp_Dir2d(gp_Vec2d(P1, Pm)));
                t = L1m.Distance(P1m);
                i--;
              }
            }
            else
            {
              if (t > NewDeflection)
              {
                NewDeflection = t;
              }
            }
          }
        }
        if (NewDeflection)
          RatioDeflection = TheDeflection / NewDeflection;
        else
          RatioDeflection = 10.0;
        TheDeflection = NewDeflection;
        NbPntIn       = nbp;
      } while ((RatioDeflection < 3.0) && (nbpassagedeflection < 3)
               && (MaxIndexUsed < (TheMaxNbPoints - 2)));
    }

    TheDeflection *= MAJORATION_DEFLECTION;
    myBox.Enlarge(TheDeflection);
  }
  ClosedPolygon = false;
  Dump();
}

bool IntCurve_Polygon2dGen::AutoIntersectionIsPossible() const
{

  gp_Vec2d VRef(ThePnts.Value(TheIndex.Value(1)), ThePnts.Value(TheIndex.Value(2)));
  for (int i = 3; i <= NbPntIn; i++)
  {
    gp_Vec2d V(ThePnts.Value(TheIndex.Value(i - 1)), ThePnts.Value(TheIndex.Value(i)));
    if (V.Dot(VRef) < 0.0)
    {
      return (true);
    }
  }
  return (false);
}

double IntCurve_Polygon2dGen::ApproxParamOnCurve(const int    Aindex,
                                                 const double TheParamOnLine) const
{
  int    Indexp1, Index = Aindex;
  double ParamOnLine = TheParamOnLine;
  if (Index > NbPntIn)
  {
    std::cout << "OutOfRange Polygon2d::ApproxParamOnCurve " << std::endl;
  }
  if ((Index == NbPntIn) && (ParamOnLine == 0.0))
  {
    Index--;
    ParamOnLine = 1.0;
  }
  if (Index == 0)
  {
    Index       = 1;
    ParamOnLine = 0.0;
  }
  Indexp1 = TheIndex.Value(Index + 1);
  Index   = TheIndex.Value(Index);

  double du = TheParams.Value(Indexp1) - TheParams.Value(Index);
  double u  = TheParams.Value(Index) + ParamOnLine * du;
  return (u);
}

#if TEST

extern bool DebugPolygon2d;
extern void DrawSegmentBlanc(const gp_Pnt2d& _P1, const gp_Pnt2d& _P2);
extern void DrawSegment(const gp_Pnt2d& _P1, const gp_Pnt2d& _P2);

void IntCurve_Polygon2dGen::Dump(void) const
{
  if (!DebugPolygon2d)
    return;
  double bx0, bx1, by0, by1;
  if (myBox.IsVoid())
    return;
  myBox.Get(bx0, by0, bx1, by1);
  DrawSegment(gp_Pnt2d(bx0, by0), gp_Pnt2d(bx1, by0));
  DrawSegment(gp_Pnt2d(bx1, by0), gp_Pnt2d(bx1, by1));
  DrawSegment(gp_Pnt2d(bx1, by1), gp_Pnt2d(bx0, by1));
  DrawSegment(gp_Pnt2d(bx0, by1), gp_Pnt2d(bx0, by0));
  int i;
  if (NbPntIn <= 1)
    return;
  for (i = 2; i <= NbPntIn; i++)
  {
    DrawSegmentBlanc(ThePnts.Value(TheIndex.Value(i - 1)), ThePnts.Value(TheIndex.Value(i)));
  }
}
#else
void IntCurve_Polygon2dGen::Dump(void) const
{
  static int debug = 0;
  if (debug)
  {
    double bx0, bx1, by0, by1;

    std::cout << "\n ----- Dump of IntCurve_Polygon2dGen -----" << std::endl;
    if (myBox.IsVoid())
    {
      std::cout << "  Polygone Vide " << std::endl;
      return;
    }
    myBox.Get(bx0, by0, bx1, by1);
    std::cout << "  bx0:" << bx0 << std::endl;
    std::cout << "  by0:" << by0 << std::endl;
    std::cout << "  bx1:" << bx1 << std::endl;
    std::cout << "  by1:" << by1 << std::endl;

    int i;
    for (i = 1; i <= NbPntIn; i++)
    {
      const gp_Pnt2d& P = ThePnts(TheIndex(i));
      std::cout << "  (" << i << ") u:" << TheParams.Value(TheIndex(i)) << " X:" << P.X()
                << "  Y:" << P.Y() << std::endl;
    }
  }
}
#endif

void IntCurve_Polygon2dGen::Segment(const int theIndex, gp_Pnt2d& theBegin, gp_Pnt2d& theEnd) const
{
  int ind  = theIndex;
  theBegin = ThePnts(TheIndex(theIndex));
  if (theIndex >= NbPntIn)
  {
    if (!ClosedPolygon)
      throw Standard_OutOfRange("IntCurve_Polygon2dGen::Segment!");
    ind = 0;
  }
  theEnd = ThePnts(TheIndex(ind + 1));
}
