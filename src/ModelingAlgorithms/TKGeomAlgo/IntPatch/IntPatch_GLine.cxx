#include <gp_Circ.hpp>
#include <IntPatch_GLine.hpp>
#include <IntPatch_Point.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IntPatch_GLine, IntPatch_Line)

#define DEBUG 0

#include <gp_Pln.hpp>

IntPatch_GLine::IntPatch_GLine(const gp_Lin&           L,
                               const bool              Tang,
                               const IntSurf_TypeTrans Trans1,
                               const IntSurf_TypeTrans Trans2)
    : IntPatch_Line(Tang, Trans1, Trans2),
      par1(0.0),
      par2(0.0),
      fipt(false),
      lapt(false),
      indf(0),
      indl(0)
{
  typ = IntPatch_Lin;
  pos = gp_Pln(L.Location(), L.Direction()).Position().Ax2();
}

IntPatch_GLine::IntPatch_GLine(const gp_Lin&           L,
                               const bool              Tang,
                               const IntSurf_Situation Situ1,
                               const IntSurf_Situation Situ2)
    : IntPatch_Line(Tang, Situ1, Situ2),
      par1(0.0),
      par2(0.0),
      fipt(false),
      lapt(false),
      indf(0),
      indl(0)
{
  typ = IntPatch_Lin;
  pos = gp_Pln(L.Location(), L.Direction()).Position().Ax2();
}

IntPatch_GLine::IntPatch_GLine(const gp_Lin& L, const bool Tang)
    : IntPatch_Line(Tang),
      par1(0.0),
      par2(0.0),
      fipt(false),
      lapt(false),
      indf(0),
      indl(0)
{
  typ = IntPatch_Lin;
  pos = gp_Pln(L.Location(), L.Direction()).Position().Ax2();
}

IntPatch_GLine::IntPatch_GLine(const gp_Circ&          C,
                               const bool              Tang,
                               const IntSurf_TypeTrans Trans1,
                               const IntSurf_TypeTrans Trans2)
    : IntPatch_Line(Tang, Trans1, Trans2),
      pos(C.Position()),
      par1(C.Radius()),
      par2(0.0),
      fipt(false),
      lapt(false),
      indf(0),
      indl(0)
{
  typ = IntPatch_Circle;
}

IntPatch_GLine::IntPatch_GLine(const gp_Circ&          C,
                               const bool              Tang,
                               const IntSurf_Situation Situ1,
                               const IntSurf_Situation Situ2)
    : IntPatch_Line(Tang, Situ1, Situ2),
      pos(C.Position()),
      par1(C.Radius()),
      par2(0.0),
      fipt(false),
      lapt(false),
      indf(0),
      indl(0)
{
  typ = IntPatch_Circle;
}

IntPatch_GLine::IntPatch_GLine(const gp_Circ& C, const bool Tang)
    : IntPatch_Line(Tang),
      pos(C.Position()),
      par1(C.Radius()),
      par2(0.0),
      fipt(false),
      lapt(false),
      indf(0),
      indl(0)
{
  typ = IntPatch_Circle;
}

IntPatch_GLine::IntPatch_GLine(const gp_Elips&         E,
                               const bool              Tang,
                               const IntSurf_TypeTrans Trans1,
                               const IntSurf_TypeTrans Trans2)
    : IntPatch_Line(Tang, Trans1, Trans2),
      pos(E.Position()),
      par1(E.MajorRadius()),
      par2(E.MinorRadius()),
      fipt(false),
      lapt(false),
      indf(0),
      indl(0)
{
  typ = IntPatch_Ellipse;
}

IntPatch_GLine::IntPatch_GLine(const gp_Elips&         E,
                               const bool              Tang,
                               const IntSurf_Situation Situ1,
                               const IntSurf_Situation Situ2)
    : IntPatch_Line(Tang, Situ1, Situ2),
      pos(E.Position()),
      par1(E.MajorRadius()),
      par2(E.MinorRadius()),
      fipt(false),
      lapt(false),
      indf(0),
      indl(0)
{
  typ = IntPatch_Ellipse;
}

IntPatch_GLine::IntPatch_GLine(const gp_Elips& E, const bool Tang)
    : IntPatch_Line(Tang),
      pos(E.Position()),
      par1(E.MajorRadius()),
      par2(E.MinorRadius()),
      fipt(false),
      lapt(false),
      indf(0),
      indl(0)
{
  typ = IntPatch_Ellipse;
}

IntPatch_GLine::IntPatch_GLine(const gp_Parab&         P,
                               const bool              Tang,
                               const IntSurf_TypeTrans Trans1,
                               const IntSurf_TypeTrans Trans2)
    : IntPatch_Line(Tang, Trans1, Trans2),
      pos(P.Position()),
      par1(P.Focal()),
      par2(0.0),
      fipt(false),
      lapt(false),
      indf(0),
      indl(0)
{
  typ = IntPatch_Parabola;
}

IntPatch_GLine::IntPatch_GLine(const gp_Parab&         P,
                               const bool              Tang,
                               const IntSurf_Situation Situ1,
                               const IntSurf_Situation Situ2)
    : IntPatch_Line(Tang, Situ1, Situ2),
      pos(P.Position()),
      par1(P.Focal()),
      par2(0.0),
      fipt(false),
      lapt(false),
      indf(0),
      indl(0)
{
  typ = IntPatch_Parabola;
}

IntPatch_GLine::IntPatch_GLine(const gp_Parab& P, const bool Tang)
    : IntPatch_Line(Tang),
      pos(P.Position()),
      par1(P.Focal()),
      par2(0.0),
      fipt(false),
      lapt(false),
      indf(0),
      indl(0)
{
  typ = IntPatch_Parabola;
}

IntPatch_GLine::IntPatch_GLine(const gp_Hypr&          H,
                               const bool              Tang,
                               const IntSurf_TypeTrans Trans1,
                               const IntSurf_TypeTrans Trans2)
    : IntPatch_Line(Tang, Trans1, Trans2),
      pos(H.Position()),
      par1(H.MajorRadius()),
      par2(H.MinorRadius()),
      fipt(false),
      lapt(false),
      indf(0),
      indl(0)
{
  typ = IntPatch_Hyperbola;
}

IntPatch_GLine::IntPatch_GLine(const gp_Hypr&          H,
                               const bool              Tang,
                               const IntSurf_Situation Situ1,
                               const IntSurf_Situation Situ2)
    : IntPatch_Line(Tang, Situ1, Situ2),
      pos(H.Position()),
      par1(H.MajorRadius()),
      par2(H.MinorRadius()),
      fipt(false),
      lapt(false),
      indf(0),
      indl(0)
{
  typ = IntPatch_Hyperbola;
}

IntPatch_GLine::IntPatch_GLine(const gp_Hypr& H, const bool Tang)
    : IntPatch_Line(Tang),
      pos(H.Position()),
      par1(H.MajorRadius()),
      par2(H.MinorRadius()),
      fipt(false),
      lapt(false),
      indf(0),
      indl(0)
{
  typ = IntPatch_Hyperbola;
}

void IntPatch_GLine::Replace(const int, const IntPatch_Point& Pnt)
{
  svtx.Append(Pnt);
}

void IntPatch_GLine::AddVertex(const IntPatch_Point& Pnt)
{

  if (NbVertex())
  {
    const double pf  = (fipt ? svtx.Value(indf).ParameterOnLine() : 0.0);
    const double pl  = (lapt ? svtx.Value(indl).ParameterOnLine() : 0.0);
    double       par = Pnt.ParameterOnLine();
    if (ArcType() == IntPatch_Circle || ArcType() == IntPatch_Ellipse)
    {
      if (fipt && lapt)
      {
        while (par < pf)
          par += M_PI + M_PI;
        while (par > pl)
          par -= M_PI + M_PI;
        if (par < pf)
        {
          constexpr double PrecisionPConfusion(Precision::PConfusion() * 1000.0);
          if ((pf - par) > PrecisionPConfusion)
          {
            return;
          }
        }
        IntPatch_Point ParModif = Pnt;
        ParModif.SetParameter(par);
        svtx.Append(ParModif);
        return;
      }
    }
    else
    {
      if (fipt && lapt)
      {
        if (pl < par || par < pf)
          return;
      }
    }
  }
  svtx.Append(Pnt);
}

void IntPatch_GLine::ComputeVertexParameters(const double)
{
  bool         SortIsOK, APointDeleted;
  bool         SortAgain = true;
  int          i, j;
  const double ParamMinOnLine = (fipt ? Vertex(indf).ParameterOnLine() : -100000.0);
  const double ParamMaxOnLine = (lapt ? Vertex(indl).ParameterOnLine() : 100000.0);

  int nbvtx = NbVertex();

  constexpr double PrecisionPConfusion(Precision::PConfusion() * 1000.0);

  do
  {
    APointDeleted = false;
    for (i = 1; (i <= nbvtx) && (!APointDeleted); i++)
    {
      const IntPatch_Point& VTXi = svtx.Value(i);
      if (VTXi.IsOnDomS1() || VTXi.IsOnDomS2())
      {
        for (j = 1; (j <= nbvtx) && (!APointDeleted); j++)
        {
          if (i != j)
          {
            const IntPatch_Point& VTXj = svtx.Value(j);
            if ((!VTXj.IsOnDomS1()) && (!VTXj.IsOnDomS2()))
            {
              if (std::abs(VTXi.ParameterOnLine() - VTXj.ParameterOnLine()) <= PrecisionPConfusion)
              {
                svtx.Remove(j);
                nbvtx--;
                if (lapt)
                {
                  if (indl > j)
                    indl--;
                }
                if (fipt)
                {
                  if (indf > j)
                    indf--;
                }
                APointDeleted = true;
              }
            }
          }
        }
      }
    }
  } while (APointDeleted && nbvtx > 2);

  do
  {
    APointDeleted = false;
    for (i = 1; (i <= nbvtx) && (!APointDeleted); i++)
    {
      const IntPatch_Point& VTXi = svtx.Value(i);
      if (VTXi.IsOnDomS1() && (!VTXi.IsOnDomS2()))
      {
        for (j = 1; (j <= nbvtx) && (!APointDeleted); j++)
        {
          if (i != j)
          {
            const IntPatch_Point& VTXj = svtx.Value(j);
            if (VTXj.IsOnDomS1() && (!VTXj.IsOnDomS2()))
            {
              if (std::abs(VTXi.ParameterOnArc1() - VTXj.ParameterOnArc1()) <= PrecisionPConfusion)
              {
                if (VTXi.ArcOnS1() == VTXj.ArcOnS1())
                {
                  if (VTXi.IsVertexOnS1())
                  {
                    svtx.Remove(j);
                    nbvtx--;
                    if (lapt)
                    {
                      if (indl > j)
                        indl--;
                    }
                    if (fipt)
                    {
                      if (indf > j)
                        indf--;
                    }
                  }
                  else
                  {
                    svtx.Remove(i);
                    nbvtx--;
                    if (lapt)
                    {
                      if (indl > i)
                        indl--;
                    }
                    if (fipt)
                    {
                      if (indf > i)
                        indf--;
                    }
                  }
                  APointDeleted = true;
                }
              }
            }
          }
        }
      }
    }
  } while (APointDeleted);

  do
  {
    APointDeleted = false;
    for (i = 1; (i <= nbvtx) && (!APointDeleted); i++)
    {
      const IntPatch_Point& VTXi = svtx.Value(i);
      if (VTXi.IsOnDomS2() && (!VTXi.IsOnDomS1()))
      {
        for (j = 1; (j <= nbvtx) && (!APointDeleted); j++)
        {
          if (i != j)
          {
            const IntPatch_Point& VTXj = svtx.Value(j);
            if (VTXj.IsOnDomS2() && (!VTXj.IsOnDomS1()))
            {
              if (std::abs(VTXi.ParameterOnArc2() - VTXj.ParameterOnArc2()) <= PrecisionPConfusion)
              {
                if (VTXi.ArcOnS2() == VTXj.ArcOnS2())
                {
                  if (VTXi.IsVertexOnS1())
                  {
                    svtx.Remove(j);
                    nbvtx--;
                    if (lapt)
                    {
                      if (indl > j)
                        indl--;
                    }
                    if (fipt)
                    {
                      if (indf > j)
                        indf--;
                    }
                  }
                  else
                  {
                    svtx.Remove(i);
                    nbvtx--;
                    if (lapt)
                    {
                      if (indl > i)
                        indl--;
                    }
                    if (fipt)
                    {
                      if (indf > i)
                        indf--;
                    }
                  }
                  APointDeleted = true;
                }
              }
            }
          }
        }
      }
    }
  } while (APointDeleted);

  double u1min = RealLast(), u1max = RealFirst();
  double u2min = RealLast(), u2max = RealFirst();
  bool   ToBreak = false;

  do
  {
    nbvtx = NbVertex();
    if (SortAgain)
    {
      do
      {
        SortIsOK = true;
        for (i = 2; i <= nbvtx; i++)
        {
          if (svtx.Value(i - 1).ParameterOnLine() > svtx.Value(i).ParameterOnLine())
          {
            SortIsOK = false;
            svtx.Exchange(i - 1, i);
            if (fipt)
            {
              if (indf == i)
                indf = i - 1;
              else if (indf == i - 1)
                indf = i;
            }
            if (lapt)
            {
              if (indl == i)
                indl = i - 1;
              else if (indl == i - 1)
                indl = i;
            }
          }
        }
      } while (!SortIsOK);
    }

    if (ToBreak)
      break;

    SortAgain = false;
    SortIsOK  = true;
    for (i = 2; i <= nbvtx && SortIsOK; i++)
    {
      IntPatch_Point& VTX = svtx.ChangeValue(i);
      for (j = 1; j <= nbvtx && SortIsOK; j++)
      {
        if (i != j)
        {
          IntPatch_Point& VTXM1  = svtx.ChangeValue(j);
          bool            kill   = false;
          bool            killm1 = false;
          if (std::abs(VTXM1.ParameterOnLine() - VTX.ParameterOnLine()) < PrecisionPConfusion)
          {
            if (VTXM1.IsOnDomS1() && VTX.IsOnDomS1())
            {
              if (VTXM1.ArcOnS1() == VTX.ArcOnS1())
              {
                if (VTXM1.IsOnDomS2())
                {
                  if (!VTX.IsOnDomS2())
                  {
                    kill = true;
                  }
                  else
                  {
                    if (VTXM1.ArcOnS2() == VTX.ArcOnS2())
                    {
                      if (VTXM1.IsVertexOnS2())
                      {
                        kill = true;
                      }
                      else
                      {
                        killm1 = true;
                      }
                    }
                  }
                }
                else
                {
                  if (VTX.IsOnDomS2())
                  {
                    killm1 = true;
                  }
                }
              }
            }
            else
            {
              if (!VTXM1.IsOnDomS2() && !VTX.IsOnDomS2())
              {
                if (VTXM1.IsOnDomS1() && !VTX.IsOnDomS1())
                {
                  kill = true;
                }
                else if (VTX.IsOnDomS1() && !VTXM1.IsOnDomS1())
                {
                  killm1 = true;
                }
              }
            }

            if (!(kill || killm1))
            {
              if (VTXM1.IsOnDomS2() && VTX.IsOnDomS2())
              {
                if (VTXM1.ArcOnS2() == VTX.ArcOnS2())
                {
                  if (VTXM1.IsOnDomS1())
                  {
                    if (!VTX.IsOnDomS1())
                    {
                      kill = true;
                    }
                    else
                    {
                      if (VTXM1.ArcOnS1() == VTX.ArcOnS1())
                      {
                        if (VTXM1.IsVertexOnS1())
                        {

                          kill = true;
                        }
                        else
                        {
                          killm1 = true;
                        }
                      }
                    }
                  }
                  else
                  {
                    if (VTX.IsOnDomS1())
                    {
                      killm1 = true;
                    }
                  }
                }
              }
              else
              {
                if (!VTXM1.IsOnDomS1() && !VTX.IsOnDomS1())
                {
                  if (VTXM1.IsOnDomS2() && !VTX.IsOnDomS2())
                  {
                    kill = true;
                  }
                  else if (VTX.IsOnDomS2() && !VTXM1.IsOnDomS2())
                  {
                    killm1 = true;
                  }
                }
              }
            }

            if (kill)
            {
              SortIsOK = false;
              if (lapt)
              {
                if (indl > i)
                  indl--;
                else if (indl == i)
                  indl = j;
              }

              if (fipt)
              {
                if (indf > i)
                  indf--;
                else if (indf == i)
                  indf = j;
              }

              svtx.Remove(i);
              nbvtx--;
            }
            else if (killm1)
            {
              SortIsOK = false;
              if (lapt)
              {
                if (indl > j)
                  indl--;
                else if (indl == j)
                  indl = i - 1;
              }

              if (fipt)
              {
                if (indf > j)
                  indf--;
                else if (indf == j)
                  indf = i - 1;
              }

              svtx.Remove(j);
              nbvtx--;
            }
            else if (ArcType() == IntPatch_Circle || ArcType() == IntPatch_Ellipse)
            {

              double ponline = VTX.ParameterOnLine();

              double       newParam = ponline;
              const double PiPi     = M_PI + M_PI;
              bool         is2PI    = (std::abs(ponline - PiPi) <= PrecisionPConfusion);

              if (nbvtx > 2 && !is2PI)
                continue;

              if (is2PI)
                newParam = 0;
              else if (std::abs(ponline) <= PrecisionPConfusion)
                newParam = PiPi;
              else
                newParam -= PiPi;

              double u1a, v1a, u2a, v2a, u1b, v1b, u2b, v2b;
              VTXM1.Parameters(u1a, v1a, u2a, v2a);
              VTX.Parameters(u1b, v1b, u2b, v2b);
              int flag = 0;

              if ((std::abs(u1a - u1b) <= PrecisionPConfusion))
                flag |= 1;

              if ((std::abs(v1a - v1b) <= PrecisionPConfusion))
                flag |= 2;
              if ((std::abs(u2a - u2b) <= PrecisionPConfusion))
                flag |= 4;

              if ((std::abs(v2a - v2b) <= PrecisionPConfusion))
                flag |= 8;

              bool TestOn1 = false;
              bool TestOn2 = false;

              switch (flag)
              {
                case 3:
                case 7:
                case 12:
                case 13:
                case 10:

                  break;
                case 11:
                {
                  TestOn2 = true;
                  break;
                }

                case 14:
                {
                  TestOn1 = true;
                  break;
                }
                default:
                  break;
              };

              if (TestOn1)
              {

                double U1A = (u1a < u1b) ? u1a : u1b;
                double U1B = (u1a < u1b) ? u1b : u1a;

                if (u1min == RealLast())
                {
                  u1min = U1A;
                  u1max = U1B;
                }
                else
                {
                  if (std::abs(U1A - u1min) > PrecisionPConfusion)
                    ToBreak = true;
                  if (std::abs(U1B - u1max) > PrecisionPConfusion)
                    ToBreak = true;
                }

                if (newParam >= ParamMinOnLine && newParam <= ParamMaxOnLine)
                {
                  SortAgain = true;
                  SortIsOK  = false;
                  if (newParam > ponline)
                  {
                    if (u1a < u1b)
                    {
                      VTX.SetParameter(newParam);
                    }
                    else
                    {
                      VTXM1.SetParameter(newParam);
                    }
                  }
                  else
                  {
                    if (u1a > u1b)
                    {
                      VTX.SetParameter(newParam);
                    }
                    else
                    {
                      VTXM1.SetParameter(newParam);
                    }
                  }
                }
              }

              if (TestOn2)
              {

                double U2A = (u2a < u2b) ? u2a : u2b;
                double U2B = (u2a < u2b) ? u2b : u2a;
                if (u2min == RealLast())
                {
                  u2min = U2A;
                  u2max = U2B;
                }
                else
                {
                  if (std::abs(U2A - u2min) > PrecisionPConfusion)
                    ToBreak = true;

                  if (std::abs(U2B - u2max) > PrecisionPConfusion)
                    ToBreak = true;
                }

                if (newParam >= ParamMinOnLine && newParam <= ParamMaxOnLine)
                {
                  SortAgain = true;
                  SortIsOK  = false;
                  if (newParam > ponline)
                  {
                    if (u2a < u2b)
                    {
                      VTX.SetParameter(newParam);
                    }
                    else
                    {
                      VTXM1.SetParameter(newParam);
                    }
                  }
                  else
                  {
                    if (u2a > u2b)
                    {
                      VTX.SetParameter(newParam);
                    }
                    else
                    {
                      VTXM1.SetParameter(newParam);
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  } while (!SortIsOK);

  nbvtx = NbVertex();
  if (nbvtx)
  {
    do
    {
      SortIsOK = true;
      for (i = 2; i <= nbvtx; i++)
      {
        if (svtx.Value(i - 1).ParameterOnLine() > svtx.Value(i).ParameterOnLine())
        {
          SortIsOK = false;
          svtx.Exchange(i - 1, i);
        }
      }
    } while (!SortIsOK);

    indl = nbvtx;
    indf = 1;
  }
}
