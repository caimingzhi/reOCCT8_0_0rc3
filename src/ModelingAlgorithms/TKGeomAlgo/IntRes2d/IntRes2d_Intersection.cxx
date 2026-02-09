#include <IntRes2d_Intersection.hpp>
#include <IntRes2d_IntersectionPoint.hpp>
#include <IntRes2d_IntersectionSegment.hpp>
#include <IntRes2d_Position.hpp>
#include <NCollection_Sequence.hpp>
#include <StdFail_NotDone.hpp>

#define PARAMEQUAL(a, b) (std::abs((a) - (b)) < (1e-8))

static void InternalVerifyPosition(IntRes2d_Transition& T1,
                                   IntRes2d_Transition& T2,
                                   const double         PParamOnFirst,
                                   const double         PParamOnSecond,
                                   const double         FirstParam1,
                                   const double         LastParam1,
                                   const double         FirstParam2,
                                   const double         LastParam2);

static bool TransitionEqual(const IntRes2d_Transition& T1, const IntRes2d_Transition& T2);

bool TransitionEqual(const IntRes2d_Transition& T1, const IntRes2d_Transition& T2)
{

  if (T1.PositionOnCurve() == T2.PositionOnCurve())
  {
    if (T1.TransitionType() == T2.TransitionType())
    {
      if (T1.TransitionType() == IntRes2d_Touch)
      {
        if (T1.IsTangent() == T2.IsTangent())
        {
          if (T1.Situation() == T2.Situation())
          {
            if (T1.IsOpposite() == T2.IsOpposite())
            {
              return (true);
            }
          }
        }
      }
      else
      {
        return (true);
      }
    }
  }
  return (false);
}

void IntRes2d_Intersection::Insert(const IntRes2d_IntersectionPoint& Pnt)
{
  int n = lpnt.Length();
  if (n == 0)
  {
    lpnt.Append(Pnt);
  }
  else
  {
    double u = Pnt.ParamOnFirst();
    int    i = 1;
    int    b = n + 1;
    while (i <= n)
    {
      const IntRes2d_IntersectionPoint& Pnti = lpnt(i);
      double                            ui   = Pnti.ParamOnFirst();
      if (ui >= u)
      {
        b = i;
        i = n;
      }
      if (PARAMEQUAL(ui, u))
      {
        if (PARAMEQUAL((Pnt.ParamOnSecond()), (Pnti.ParamOnSecond())))
        {
          if ((TransitionEqual(Pnt.TransitionOfFirst(), Pnti.TransitionOfFirst()))
              && (TransitionEqual(Pnt.TransitionOfSecond(), Pnti.TransitionOfSecond())))
          {
            b = 0;
            i = n;
          }
        }
      }

      i++;
    }
    if (b > n)
    {
      lpnt.Append(Pnt);
    }
    else if (b > 0)
    {
      lpnt.InsertBefore(b, Pnt);
    }
  }
}

void IntRes2d_Intersection::SetValues(const IntRes2d_Intersection& Other)
{
  int i;
  if (Other.done)
  {
    lseg.Clear();
    lpnt.Clear();
    int N = Other.lpnt.Length();
    for (i = 1; i <= N; i++)
    {
      lpnt.Append(Other.lpnt(i));
    }
    N = Other.lseg.Length();
    for (i = 1; i <= N; i++)
    {
      lseg.Append(Other.lseg(i));
    }

    done = true;
  }
  else
  {
    done = false;
  }
}

void IntRes2d_Intersection::Append(const IntRes2d_Intersection& Other,
                                   const double                 FirstParam1,
                                   const double                 LastParam1,
                                   const double                 FirstParam2,
                                   const double                 LastParam2)
{

  if (Other.done)
  {

    int n = Other.lpnt.Length();
    int i;
    for (i = 1; i <= n; i++)
    {

      const IntRes2d_IntersectionPoint& P              = Other.lpnt(i);
      double                            PParamOnFirst  = P.ParamOnFirst();
      double                            PParamOnSecond = P.ParamOnSecond();
      IntRes2d_Transition               T1             = P.TransitionOfFirst();
      IntRes2d_Transition               T2             = P.TransitionOfSecond();
      gp_Pnt2d                          Pt             = P.Value();

      InternalVerifyPosition(T1,
                             T2,
                             PParamOnFirst,
                             PParamOnSecond,
                             FirstParam1,
                             LastParam1,
                             FirstParam2,
                             LastParam2);

      this->Insert(IntRes2d_IntersectionPoint(Pt, PParamOnFirst, PParamOnSecond, T1, T2, false));
    }

    n                       = Other.lseg.Length();
    double SegModif_P1First = 0, SegModif_P1Second = 0;
    double SegModif_P2First = 0, SegModif_P2Second = 0;

    for (i = 1; i <= n; i++)
    {

      const IntRes2d_IntersectionPoint& P1 = Other.lseg(i).FirstPoint();

      double              P1PParamOnFirst  = P1.ParamOnFirst();
      double              P1PParamOnSecond = P1.ParamOnSecond();
      IntRes2d_Transition P1T1             = P1.TransitionOfFirst();
      IntRes2d_Transition P1T2             = P1.TransitionOfSecond();
      const gp_Pnt2d&     P1Pt             = P1.Value();

      InternalVerifyPosition(P1T1,
                             P1T2,
                             P1PParamOnFirst,
                             P1PParamOnSecond,
                             FirstParam1,
                             LastParam1,
                             FirstParam2,
                             LastParam2);

      const IntRes2d_IntersectionPoint& P2 = Other.lseg(i).LastPoint();

      double              P2PParamOnFirst  = P2.ParamOnFirst();
      double              P2PParamOnSecond = P2.ParamOnSecond();
      IntRes2d_Transition P2T1             = P2.TransitionOfFirst();
      IntRes2d_Transition P2T2             = P2.TransitionOfSecond();
      const gp_Pnt2d&     P2Pt             = P2.Value();

      bool Opposite = Other.lseg(i).IsOpposite();

      InternalVerifyPosition(P2T1,
                             P2T2,
                             P2PParamOnFirst,
                             P2PParamOnSecond,
                             FirstParam1,
                             LastParam1,
                             FirstParam2,
                             LastParam2);

      int  an             = lseg.Length();
      bool NotYetModified = true;

      for (int j = 1; (j <= an) && (NotYetModified); j++)
      {

        const IntRes2d_IntersectionPoint& AnP1               = lseg(j).FirstPoint();
        double                            AnP1PParamOnFirst  = AnP1.ParamOnFirst();
        double                            AnP1PParamOnSecond = AnP1.ParamOnSecond();

        const IntRes2d_IntersectionPoint& AnP2               = lseg(j).LastPoint();
        double                            AnP2PParamOnFirst  = AnP2.ParamOnFirst();
        double                            AnP2PParamOnSecond = AnP2.ParamOnSecond();

        if (Opposite == lseg(j).IsOpposite())
        {

          if (PARAMEQUAL(P1PParamOnFirst, AnP2PParamOnFirst)
              && PARAMEQUAL(P1PParamOnSecond, AnP2PParamOnSecond))
          {
            NotYetModified    = false;
            lseg(j)           = IntRes2d_IntersectionSegment(AnP1, P2, Opposite, false);
            SegModif_P1First  = AnP1PParamOnFirst;
            SegModif_P1Second = AnP1PParamOnSecond;
            SegModif_P2First  = P2PParamOnFirst;
            SegModif_P2Second = P2PParamOnSecond;
          }

          else if (PARAMEQUAL(P2PParamOnFirst, AnP1PParamOnFirst)
                   && PARAMEQUAL(P2PParamOnSecond, AnP1PParamOnSecond))
          {
            NotYetModified    = false;
            lseg(j)           = IntRes2d_IntersectionSegment(P1, AnP2, Opposite, false);
            SegModif_P1First  = P1PParamOnFirst;
            SegModif_P1Second = P1PParamOnSecond;
            SegModif_P2First  = AnP2PParamOnFirst;
            SegModif_P2Second = AnP2PParamOnSecond;
          }

          if (PARAMEQUAL(P1PParamOnFirst, AnP1PParamOnFirst)
              && PARAMEQUAL(P1PParamOnSecond, AnP1PParamOnSecond))
          {
            NotYetModified    = false;
            lseg(j)           = IntRes2d_IntersectionSegment(AnP2, P2, Opposite, false);
            SegModif_P1First  = P2PParamOnFirst;
            SegModif_P1Second = P2PParamOnSecond;
            SegModif_P2First  = AnP2PParamOnFirst;
            SegModif_P2Second = AnP2PParamOnSecond;
          }

          else if (PARAMEQUAL(P2PParamOnFirst, AnP2PParamOnFirst)
                   && PARAMEQUAL(P2PParamOnSecond, AnP2PParamOnSecond))
          {
            NotYetModified    = false;
            lseg(j)           = IntRes2d_IntersectionSegment(P1, AnP1, Opposite, false);
            SegModif_P1First  = P1PParamOnFirst;
            SegModif_P1Second = P1PParamOnSecond;
            SegModif_P2First  = AnP1PParamOnFirst;
            SegModif_P2Second = AnP1PParamOnSecond;
          }
        }
      }
      if (NotYetModified)
      {
        this->Append(IntRes2d_IntersectionSegment(
          IntRes2d_IntersectionPoint(P1Pt, P1PParamOnFirst, P1PParamOnSecond, P1T1, P1T2, false),
          IntRes2d_IntersectionPoint(P2Pt, P2PParamOnFirst, P2PParamOnSecond, P2T1, P2T2, false),
          Opposite,
          false));
      }
      else
      {

        int rnbpts = lpnt.Length();
        for (int rp = 1; (rp <= rnbpts) && (rp >= 1); rp++)
        {
          double PonFirst  = lpnt(rp).ParamOnFirst();
          double PonSecond = lpnt(rp).ParamOnSecond();

          if (((PonFirst >= SegModif_P1First && PonFirst <= SegModif_P2First)
               || (PonFirst <= SegModif_P1First && PonFirst >= SegModif_P2First))
              && ((PonSecond >= SegModif_P1Second && PonSecond <= SegModif_P2Second)
                  || (PonSecond <= SegModif_P1Second && PonSecond >= SegModif_P2Second)))
          {
            lpnt.Remove(rp);
            rp--;
            rnbpts--;
          }
        }
      }
    }

    done = true;
  }
  else
  {
    done = false;
  }
}

#define DEBUGPOSITION 0

#if DEBUGPOSITION
void AffPosition(IntRes2d_Transition& T, const double u, const char* Texte);

void AffPosition(IntRes2d_Transition& T, const double u, const char* Texte)
{
  if (T.PositionOnCurve() == IntRes2d_End)
  {
    std::cout << Texte << " Param :" << u << " End " << std::endl;
  }
  if (T.PositionOnCurve() == IntRes2d_Middle)
  {
    std::cout << Texte << " Param :" << u << " Middle " << std::endl;
  }
  if (T.PositionOnCurve() == IntRes2d_Head)
  {
    std::cout << Texte << " Param :" << u << " Head " << std::endl;
  }
}
#endif

void InternalVerifyPosition(IntRes2d_Transition& T1,
                            IntRes2d_Transition& T2,
                            const double         PParamOnFirst,
                            const double         PParamOnSecond,
                            const double         FirstParam1,
                            const double         LastParam1,
                            const double         FirstParam2,
                            const double         LastParam2)
{
#if DEBUGPOSITION
  AffPosition(T1, PParamOnFirst, " Point 1 ");
  AffPosition(T2, PParamOnSecond, " Point 2 ");
#endif
  if (T1.PositionOnCurve() != IntRes2d_Middle)
  {
    if (!(PARAMEQUAL(PParamOnFirst, FirstParam1) || PARAMEQUAL(PParamOnFirst, LastParam1)))
    {
      if ((PParamOnFirst > FirstParam1) && (PParamOnFirst < LastParam1))
        T1.SetPosition(IntRes2d_Middle);
    }
  }
  if (T2.PositionOnCurve() != IntRes2d_Middle)
  {
    if (!(PARAMEQUAL(PParamOnSecond, FirstParam2) || PARAMEQUAL(PParamOnSecond, LastParam2)))
    {
      if ((PParamOnSecond > FirstParam2) && (PParamOnSecond < LastParam2))
        T2.SetPosition(IntRes2d_Middle);
    }
  }
}
