#include <Precision.hpp>
#include <TopAbs.hpp>
#include <TopAbs_Orientation.hpp>
#include <TopAbs_State.hpp>
#include <TopTrans_SurfaceTransition.hpp>

static bool STATIC_DEFINED = false;

static gp_Dir FUN_nCinsideS(const gp_Dir& tgC, const gp_Dir& ngS)
{

  gp_Dir XX(ngS ^ tgC);
  return XX;
}

#define M_REVERSED(st) (st == TopAbs_REVERSED)
#define M_INTERNAL(st) (st == TopAbs_INTERNAL)
#define M_UNKNOWN(st) (st == TopAbs_UNKNOWN)

static int FUN_OO(const int i)
{
  if (i == 1)
    return 2;
  if (i == 2)
    return 1;
  return 0;
}

static double FUN_Ang(const gp_Dir&,
                      const gp_Dir&            beafter,
                      const gp_Dir&            TgC,
                      const gp_Dir&            Norm,
                      const TopAbs_Orientation O)
{
  gp_Dir dironF = FUN_nCinsideS(TgC, Norm);
  if (M_REVERSED(O))
    dironF.Reverse();

  double ang = beafter.AngleWithRef(dironF, TgC);
  return ang;
}

static void FUN_getSTA(const double Ang, const double tola, int& i, int& j)
{
  double cos     = std::cos(Ang);
  double sin     = std::sin(Ang);
  bool   nullcos = std::abs(cos) < tola;
  bool   nullsin = std::abs(sin) < tola;
  if (nullcos)
    i = 0;
  else
    i = (cos > 0.) ? 1 : 2;
  if (nullsin)
    j = 0;
  else
    j = (sin > 0.) ? 1 : 2;
}

#ifndef OCCT_DEBUG
  #define M_Unknown (-100)
#else
  #define M_Unknown (-100.)
#endif
#define M_noupdate (0)
#define M_updateREF (1)
#define M_Ointernal (10)

static int FUN_refnearest(const double             Angref,
                          const TopAbs_Orientation Oriref,
                          const double             Ang,
                          const TopAbs_Orientation Ori,
                          const double             tola)
{
  bool undef = (Angref == 100.);
  if (undef)
    return M_updateREF;

  double cosref = std::cos(Angref), cos = std::cos(Ang);
  double dcos = std::abs(cosref) - std::abs(cos);
  if (std::abs(dcos) < tola)
  {

    if (TopAbs::Complement(Ori) == Oriref)
      return M_Ointernal;
    else
      return (int)M_Unknown;
  }
  int updateref = (dcos > 0.) ? M_noupdate : M_updateREF;
  return updateref;
}

static int FUN_refnearest(const int                i,
                          const int                j,
                          const double             CurvSref,
                          const double             Angref,
                          const TopAbs_Orientation Oriref,
                          const double             Curvref,
                          const double             Ang,
                          const TopAbs_Orientation Ori,
                          const double             Curv,
                          const double             tola,
                          bool&                    TouchFlag)
{
  bool   iisj      = (i == j);
  double abscos    = std::abs(std::cos(Ang));
  bool   i0        = (std::abs(1. - abscos) < tola);
  bool   j0        = (abscos < tola);
  bool   nullcurv  = (Curv == 0.);
  bool   curvpos   = (Curv > tola);
  bool   curvneg   = (Curv < -tola);
  bool   nullcsref = (CurvSref == 0.);

  bool undef = (Angref == 100.);
  if (undef)
  {
    if (i0)
    {
      if (iisj && curvneg)
        return M_noupdate;
      if (!iisj && curvpos)
        return M_noupdate;
    }
    if (j0)
    {
      if (!nullcsref && (j == 1) && iisj && (curvpos || nullcurv))
        return M_updateREF;
      if (!nullcsref && (j == 1) && !iisj && (curvneg || nullcurv))
        return M_updateREF;

      if (iisj && curvpos)
        return M_noupdate;
      if (!iisj && curvneg)
        return M_noupdate;
    }
    return M_updateREF;
  }

  double cosref = std::cos(Angref), cos = std::cos(Ang);
  double dcos    = std::abs(cosref) - std::abs(cos);
  bool   samecos = std::abs(dcos) < tola;
  if (samecos)
  {

    if (std::abs(Curvref - Curv) < 1.e-4)
    {
      if (TopAbs::Complement(Ori) == Oriref)
        return M_Ointernal;
      else
        return (int)M_Unknown;
    }

    bool noupdate = false;
    if (iisj && (Curvref > Curv))
      noupdate = true;
    if (!iisj && (Curvref < Curv))
      noupdate = true;
    int updateref = noupdate ? M_noupdate : M_updateREF;
    if (!j0)
      return updateref;

    if (!noupdate && !nullcsref)
    {

      if ((j == 2) && (std::abs(Curv) < CurvSref))
        updateref = M_noupdate;
      if ((j == 1) && (std::abs(Curv) > CurvSref))
        updateref = M_noupdate;
    }
    return updateref;
  }

  int updateref = (dcos > 0.) ? M_noupdate : M_updateREF;
  if (Oriref != Ori)
    TouchFlag = true;

  return updateref;
}

TopTrans_SurfaceTransition::TopTrans_SurfaceTransition()
    : myCurvRef(0.0),
      myAng(1, 2, 1, 2),
      myCurv(1, 2, 1, 2),
      myOri(1, 2, 1, 2),
      myTouchFlag(false)
{
  STATIC_DEFINED = false;
}

void TopTrans_SurfaceTransition::Reset(const gp_Dir& Tgt,
                                       const gp_Dir& Norm,
                                       const gp_Dir& MaxD,
                                       const gp_Dir& MinD,
                                       const double  MaxCurv,
                                       const double  MinCurv)
{
  STATIC_DEFINED = true;

  constexpr double tola     = Precision::Angular();
  bool             curismax = (std::abs(MaxD.Dot(myTgt)) < tola);
  bool             curismin = (std::abs(MinD.Dot(myTgt)) < tola);

  if ((std::abs(MaxCurv) < tola) && (std::abs(MinCurv) < tola))
  {
    Reset(Tgt, Norm);
    return;
  }

  if (!curismax && !curismin)
  {

    STATIC_DEFINED = false;
    return;
  }

  if (curismax)
    myCurvRef = std::abs(MaxCurv);
  if (curismin)
    myCurvRef = std::abs(MinCurv);
  if (myCurvRef < tola)
    myCurvRef = 0.;

  myNorm  = Norm;
  myTgt   = Tgt;
  beafter = Norm ^ Tgt;
  for (int i = 1; i <= 2; i++)
    for (int j = 1; j <= 2; j++)
      myAng(i, j) = 100.;

  myTouchFlag = false;
}

void TopTrans_SurfaceTransition::Reset(const gp_Dir& Tgt, const gp_Dir& Norm)
{
  STATIC_DEFINED = true;

  myNorm  = Norm;
  myTgt   = Tgt;
  beafter = Norm ^ Tgt;
  for (int i = 1; i <= 2; i++)
    for (int j = 1; j <= 2; j++)
      myAng(i, j) = 100.;

  myCurvRef   = 0.;
  myTouchFlag = false;
}

void TopTrans_SurfaceTransition::Compare

  (const double,
   const gp_Dir&            Norm,
   const gp_Dir&            MaxD,
   const gp_Dir&            MinD,
   const double             MaxCurv,
   const double             MinCurv,
   const TopAbs_Orientation S,
   const TopAbs_Orientation O)
{
  if (!STATIC_DEFINED)
    return;

  double Curv = 0.;

  constexpr double tola     = Precision::Angular();
  bool             curismax = (std::abs(MaxD.Dot(myTgt)) < tola);
  bool             curismin = (std::abs(MinD.Dot(myTgt)) < tola);
  if (!curismax && !curismin)
  {

    STATIC_DEFINED = false;
    return;
  }
  if (curismax)
    Curv = std::abs(MaxCurv);
  if (curismin)
    Curv = std::abs(MinCurv);
  if (myCurvRef < tola)
    Curv = 0.;
  gp_Dir dironF = FUN_nCinsideS(myTgt, Norm);
  double prod   = (dironF ^ Norm).Dot(myTgt);
  if (prod < 0.)
    Curv = -Curv;

  double Ang;

  Ang = ::FUN_Ang(myNorm, beafter, myTgt, Norm, O);

  int i, j;

  ::FUN_getSTA(Ang, tola, i, j);

  int kmax = M_INTERNAL(O) ? 2 : 1;
  for (int k = 1; k <= kmax; k++)
  {
    if (k == 2)
    {

      i = ::FUN_OO(i);
      j = ::FUN_OO(j);
    }
    bool i0 = (i == 0), j0 = (j == 0);
    int  nmax = (i0 || j0) ? 2 : 1;
    for (int n = 1; n <= nmax; n++)
    {
      if (i0)
        i = n;
      if (j0)
        j = n;

      int refn = ::FUN_refnearest(i,
                                  j,
                                  myCurvRef,
                                  myAng(i, j),
                                  myOri(i, j),
                                  myCurv(i, j),
                                  Ang,
                                  S,
                                  Curv,
                                  tola,
                                  myTouchFlag);
      if (refn == M_Unknown)
      {
        STATIC_DEFINED = false;
        return;
      }
      if (refn > 0)
      {
        myAng(i, j)  = Ang;
        myOri(i, j)  = (refn == M_Ointernal) ? TopAbs_INTERNAL : S;
        myCurv(i, j) = Curv;
      }
    }
  }
}

void TopTrans_SurfaceTransition::Compare

  (const double, const gp_Dir& Norm, const TopAbs_Orientation S, const TopAbs_Orientation O)
{
  if (!STATIC_DEFINED)
    return;

  double           Ang  = ::FUN_Ang(myNorm, beafter, myTgt, Norm, O);
  constexpr double tola = Precision::Angular();

  int i, j;
  ::FUN_getSTA(Ang, tola, i, j);

  int kmax = M_INTERNAL(O) ? 2 : 1;
  for (int k = 1; k <= kmax; k++)
  {
    if (k == 2)
    {

      i = ::FUN_OO(i);
      j = ::FUN_OO(j);
    }

    bool i0 = (i == 0), j0 = (j == 0);
    int  nmax = (i0 || j0) ? 2 : 1;
    for (int n = 1; n <= nmax; n++)
    {
      if (i0)
        i = n;
      if (j0)
        j = n;

      int refn = ::FUN_refnearest(myAng(i, j), myOri(i, j), Ang, S, tola);
      if (refn == M_Unknown)
      {
        STATIC_DEFINED = false;
        return;
      }

      if (refn > 0)
      {
        myAng(i, j) = Ang;
        myOri(i, j) = (refn == M_Ointernal) ? TopAbs_INTERNAL : S;
      }
    }
  }
}

#define BEFORE (2)
#define AFTER (1)

static TopAbs_State FUN_getstate(const NCollection_Array2<double>&             Ang,
                                 const NCollection_Array2<TopAbs_Orientation>& Ori,
                                 const int                                     iSTA,
                                 const int                                     iINDEX)
{
  if (!STATIC_DEFINED)
    return TopAbs_UNKNOWN;

  double a1 = Ang(iSTA, 1), a2 = Ang(iSTA, 2);
  bool   undef1 = (a1 == 100.), undef2 = (a2 == 100.);
  bool   undef = undef1 && undef2;
  if (undef)
    return TopAbs_UNKNOWN;

  if (undef1 || undef2)
  {
    int                jok = undef1 ? 2 : 1;
    TopAbs_Orientation o   = Ori(iSTA, jok);
    TopAbs_State       st  = (iINDEX == BEFORE) ? TopTrans_SurfaceTransition::GetBefore(o)
                                                : TopTrans_SurfaceTransition::GetAfter(o);
    return st;
  }

  TopAbs_Orientation o1 = Ori(iSTA, 1), o2 = Ori(iSTA, 2);
  TopAbs_State       st1 = (iINDEX == BEFORE) ? TopTrans_SurfaceTransition::GetBefore(o1)
                                              : TopTrans_SurfaceTransition::GetAfter(o1);
  TopAbs_State       st2 = (iINDEX == BEFORE) ? TopTrans_SurfaceTransition::GetBefore(o2)
                                              : TopTrans_SurfaceTransition::GetAfter(o2);
  if (st1 != st2)
    return TopAbs_UNKNOWN;
  return st1;
}

TopAbs_State TopTrans_SurfaceTransition::StateBefore() const
{
  if (!STATIC_DEFINED)
    return TopAbs_UNKNOWN;

  TopAbs_State before = ::FUN_getstate(myAng, myOri, BEFORE, BEFORE);
  if (M_UNKNOWN(before))
  {

    before = ::FUN_getstate(myAng, myOri, AFTER, BEFORE);

    if (myTouchFlag)
    {
      if (before == TopAbs_OUT)
        before = TopAbs_IN;
      else if (before == TopAbs_IN)
        before = TopAbs_OUT;
    }
  }
  return before;
}

TopAbs_State TopTrans_SurfaceTransition::StateAfter() const
{
  if (!STATIC_DEFINED)
    return TopAbs_UNKNOWN;

  TopAbs_State after = ::FUN_getstate(myAng, myOri, AFTER, AFTER);
  if (M_UNKNOWN(after))
  {

    after = ::FUN_getstate(myAng, myOri, BEFORE, AFTER);

    if (myTouchFlag)
    {
      if (after == TopAbs_OUT)
        after = TopAbs_IN;
      else if (after == TopAbs_IN)
        after = TopAbs_OUT;
    }
  }
  return after;
}

TopAbs_State TopTrans_SurfaceTransition::GetBefore(const TopAbs_Orientation Tran)
{
  if (!STATIC_DEFINED)
    return TopAbs_UNKNOWN;

  switch (Tran)
  {
    case TopAbs_FORWARD:
    case TopAbs_EXTERNAL:
      return TopAbs_OUT;
    case TopAbs_REVERSED:
    case TopAbs_INTERNAL:
      return TopAbs_IN;
  }
  return TopAbs_OUT;
}

TopAbs_State TopTrans_SurfaceTransition::GetAfter(const TopAbs_Orientation Tran)
{
  if (!STATIC_DEFINED)
    return TopAbs_UNKNOWN;

  switch (Tran)
  {
    case TopAbs_FORWARD:
    case TopAbs_INTERNAL:
      return TopAbs_IN;
    case TopAbs_REVERSED:
    case TopAbs_EXTERNAL:
      return TopAbs_OUT;
  }
  return TopAbs_OUT;
}
