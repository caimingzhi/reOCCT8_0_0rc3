#include <TopAbs.hpp>
#include <TopTrans_CurveTransition.hpp>

#define GREATER 1
#define SAME 0
#define LOWER -1

TopTrans_CurveTransition::TopTrans_CurveTransition()
    : myCurv(0.0),
      Init(false),
      CurvFirst(0.0),
      CurvLast(0.0)
{
  TranFirst = TopAbs_FORWARD;
  TranLast  = TopAbs_FORWARD;
}

void TopTrans_CurveTransition::Reset(const gp_Dir& Tgt, const gp_Dir& Norm, const double Curv)
{
  myTgt  = Tgt;
  myNorm = Norm;
  myCurv = Curv;
  Init   = true;
}

void TopTrans_CurveTransition::Reset(const gp_Dir& Tgt)
{
  myTgt  = Tgt;
  myCurv = 0.;
  Init   = true;
}

void TopTrans_CurveTransition::Compare(const double             Tole,
                                       const gp_Dir&            T,
                                       const gp_Dir&            N,
                                       const double             C,
                                       const TopAbs_Orientation St,
                                       const TopAbs_Orientation Or)
{

  TopAbs_Orientation S = St;
  TopAbs_Orientation O = Or;

  if (S == TopAbs_INTERNAL)
  {
    if (T * myTgt < 0)
      S = TopAbs::Reverse(O);
    else
      S = O;
  }

  if (Init)
  {
    Init      = false;
    TgtFirst  = T;
    NormFirst = N;
    CurvFirst = C;
    TranFirst = S;
    TgtLast   = T;
    NormLast  = N;
    CurvLast  = C;
    TranLast  = S;
    switch (O)
    {

      case TopAbs_REVERSED:
        TgtFirst.Reverse();
        TgtLast.Reverse();
        break;
      case TopAbs_INTERNAL:

        if (myTgt * T > 0)
          TgtFirst.Reverse();
        else
          TgtLast.Reverse();
        break;
      case TopAbs_FORWARD:
      case TopAbs_EXTERNAL:
        break;
    }
  }

  else
  {
    bool   FirstSet    = false;
    double cosAngWithT = myTgt * T;
    switch (O)
    {
      case TopAbs_REVERSED:
        cosAngWithT = -cosAngWithT;
        break;
      case TopAbs_INTERNAL:
        if (cosAngWithT > 0)
          cosAngWithT = -cosAngWithT;
        break;
      case TopAbs_FORWARD:
      case TopAbs_EXTERNAL:
        break;
    }
    double cosAngWith1 = myTgt * TgtFirst;

    switch (Compare(cosAngWithT, cosAngWith1, Tole))
    {

      case LOWER:

        FirstSet = true;
        TgtFirst = T;
        switch (O)
        {
          case TopAbs_REVERSED:
            TgtFirst.Reverse();
            break;
          case TopAbs_INTERNAL:
            if (myTgt * T > 0)
              TgtFirst.Reverse();
            break;
          case TopAbs_FORWARD:
          case TopAbs_EXTERNAL:
            break;
        }
        NormFirst = N;
        CurvFirst = C;
        TranFirst = S;
        break;

      case SAME:

        if (IsBefore(Tole, cosAngWithT, N, C, NormFirst, CurvFirst))
        {
          FirstSet = true;
          TgtFirst = T;
          switch (O)
          {
            case TopAbs_REVERSED:
              TgtFirst.Reverse();
              break;
            case TopAbs_INTERNAL:
              if (myTgt * T > 0)
                TgtFirst.Reverse();
              break;
            case TopAbs_FORWARD:
            case TopAbs_EXTERNAL:
              break;
          }
          NormFirst = N;
          CurvFirst = C;
          TranFirst = S;
        }
        break;

      case GREATER:
        break;
    }

    if (!FirstSet || O == TopAbs_INTERNAL)
    {

      if (O == TopAbs_INTERNAL)
        cosAngWithT = -cosAngWithT;
      double cosAngWith2 = myTgt * TgtLast;

      switch (Compare(cosAngWithT, cosAngWith2, Tole))
      {

        case GREATER:

          TgtLast = T;
          switch (O)
          {
            case TopAbs_REVERSED:
              TgtLast.Reverse();
              break;
            case TopAbs_INTERNAL:
              if (myTgt * T < 0)
                TgtLast.Reverse();
              break;
            case TopAbs_FORWARD:
            case TopAbs_EXTERNAL:
              break;
          }
          NormLast = N;
          CurvLast = C;
          TranLast = S;
          break;

        case SAME:

          if (IsBefore(Tole, cosAngWithT, NormLast, CurvLast, N, C))
          {
            TgtLast = T;
            switch (O)
            {
              case TopAbs_REVERSED:
                TgtLast.Reverse();
                break;
              case TopAbs_INTERNAL:
                if (myTgt * T < 0)
                  TgtLast.Reverse();
                break;
              case TopAbs_FORWARD:
              case TopAbs_EXTERNAL:
                break;
            }
            NormLast = N;
            CurvLast = C;
            TranLast = S;
          }
      }
    }
  }
}

TopAbs_State TopTrans_CurveTransition::StateBefore() const
{
  if (Init)
    return TopAbs_UNKNOWN;
  switch (TranFirst)
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

TopAbs_State TopTrans_CurveTransition::StateAfter() const
{
  if (Init)
    return TopAbs_UNKNOWN;
  switch (TranLast)
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

bool TopTrans_CurveTransition::IsBefore(const double  Tole,
                                        const double  CosAngl,
                                        const gp_Dir& N1,
                                        const double  C1,
                                        const gp_Dir& N2,
                                        const double  C2) const
{
  double TN1       = myTgt * N1;
  double TN2       = myTgt * N2;
  bool   OneBefore = false;

  if (std::abs(TN1) <= Tole || std::abs(TN2) <= Tole)
  {

    if (myCurv == 0)
    {

      if (C1 < C2)
        OneBefore = true;

      if (CosAngl > 0)
        OneBefore = !OneBefore;
    }
    else
    {

      double deltaC1, deltaC2;
      if (C1 == 0. || myCurv == 0.)
      {
        deltaC1 = C1 - myCurv;
      }
      else
      {
        deltaC1 = (C1 - myCurv) * (N1 * myNorm);
      }
      if (C2 == 0. || myCurv == 0.)
      {
        deltaC2 = C2 - myCurv;
      }
      else
      {
        deltaC2 = (C2 - myCurv) * (N2 * myNorm);
      }
      if (deltaC1 < deltaC2)
        OneBefore = true;
      if (CosAngl > 0)
        OneBefore = !OneBefore;
    }
  }
  else if (TN1 < 0)
  {

    if (TN2 > 0)
    {

      OneBefore = true;
    }
    else
    {

      if (C1 > C2)
      {

        OneBefore = true;
      }
    }
  }
  else if (TN1 > 0)
  {

    if (TN2 > 0)
    {

      if (C1 < C2)
      {

        OneBefore = true;
      }
    }
  }
  return OneBefore;
}

int TopTrans_CurveTransition::Compare(const double Ang1, const double Ang2, const double Tole) const
{
  int res = SAME;
  if (Ang1 - Ang2 > Tole)
    res = GREATER;
  else if (Ang2 - Ang1 > Tole)
    res = LOWER;

  return res;
}
