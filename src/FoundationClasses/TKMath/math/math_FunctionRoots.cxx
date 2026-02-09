

#define No_Standard_RangeError
#define No_Standard_OutOfRange
#define No_Standard_DimensionError

#include <math_DirectPolynomialRoots.hpp>
#include <math_FunctionRoots.hpp>
#include <math_FunctionWithDerivative.hpp>
#include <math_BracketedRoot.hpp>
#include <NCollection_Array1.hpp>

#define ITMAX 100
#define EPS 1e-14
#define EPSEPS 2e-14
#define MAXBIS 100

#ifdef OCCT_DEBUG
static bool myDebug = 0;
static int  nbsolve = 0;
#endif

class DerivFunction : public math_Function
{
  math_FunctionWithDerivative* myF;

public:
  DerivFunction(math_FunctionWithDerivative& theF)
      : myF(&theF)
  {
  }

  bool Value(const double theX, double& theFval) override { return myF->Derivative(theX, theFval); }
};

static void AppendRoot(NCollection_Sequence<double>& Sol,
                       NCollection_Sequence<int>&    NbStateSol,
                       const double                  X,
                       math_FunctionWithDerivative&  F,

                       const double,
                       const double dX)
{

  int    n = Sol.Length();
  double t;
#ifdef OCCT_DEBUG
  if (myDebug)
  {
    std::cout << "   Ajout de la solution numero : " << n + 1 << std::endl;
    std::cout << "   Valeur de la racine :" << X << std::endl;
  }
#endif

  if (n == 0)
  {
    Sol.Append(X);
    F.Value(X, t);
    NbStateSol.Append(F.GetStateNumber());
  }
  else
  {
    int i  = 1;
    int pl = n + 1;
    while (i <= n)
    {
      t = Sol.Value(i);
      if (t >= X)
      {
        pl = i;
        i  = n;
      }
      if (std::abs(X - t) <= dX)
      {
        pl = 0;
        i  = n;
      }
      i++;
    }
    if (pl > n)
    {
      Sol.Append(X);
      F.Value(X, t);
      NbStateSol.Append(F.GetStateNumber());
    }
    else if (pl > 0)
    {
      Sol.InsertBefore(pl, X);
      F.Value(X, t);
      NbStateSol.InsertBefore(pl, F.GetStateNumber());
    }
  }
}

static void Solve(math_FunctionWithDerivative&  F,
                  const double                  K,
                  const double                  x1,
                  const double                  y1,
                  const double                  x2,
                  const double                  y2,
                  const double                  tol,
                  const double                  dX,
                  NCollection_Sequence<double>& Sol,
                  NCollection_Sequence<int>&    NbStateSol)
{
#ifdef OCCT_DEBUG
  if (myDebug)
  {
    std::cout << "--> Resolution :" << ++nbsolve << std::endl;
    std::cout << "   x1 =" << x1 << " y1 =" << y1 << std::endl;
    std::cout << "   x2 =" << x2 << " y2 =" << y2 << std::endl;
  }
#endif

  int    iter  = 0;
  double tols2 = 0.5 * tol;
  double a, b, c, d = 0, e = 0, fa, fb, fc, p, q, r, s, tol1, xm, min1, min2;
  a = x1;
  b = c = x2;
  fa    = y1;
  fb = fc = y2;
  for (iter = 1; iter <= ITMAX; iter++)
  {
    if ((fb > 0.0 && fc > 0.0) || (fb < 0.0 && fc < 0.0))
    {
      c  = a;
      fc = fa;
      e = d = b - a;
    }
    if (std::abs(fc) < std::abs(fb))
    {
      a  = b;
      b  = c;
      c  = a;
      fa = fb;
      fb = fc;
      fc = fa;
    }
    tol1 = EPSEPS * std::abs(b) + tols2;
    xm   = 0.5 * (c - b);
    if (std::abs(xm) < tol1 || fb == 0)
    {

      double Xp, Yp, Dp;
      int    itern = 5;
      bool   Ok;
      Xp = b;
      do
      {
        Ok = F.Values(Xp, Yp, Dp);
        if (Ok)
        {
          Ok = false;
          if (Dp > 1e-10 || Dp < -1e-10)
          {
            Xp = Xp - (Yp - K) / Dp;
          }
          if (Xp <= x2 && Xp >= x1)
          {
            F.Value(Xp, Yp);
            Yp -= K;
            if (std::abs(Yp) < std::abs(fb))
            {
              b  = Xp;
              fb = Yp;
              Ok = true;
            }
          }
        }
      } while (Ok && --itern >= 0);

      AppendRoot(Sol, NbStateSol, b, F, K, dX);
      return;
    }
    if (std::abs(e) >= tol1 && std::abs(fa) > std::abs(fb))
    {
      s = fb / fa;
      if (a == c)
      {
        p = xm * s;
        p += p;
        q = 1.0 - s;
      }
      else
      {
        q = fa / fc;
        r = fb / fc;
        p = s * ((xm + xm) * q * (q - r) - (b - a) * (r - 1.0));
        q = (q - 1.0) * (r - 1.0) * (s - 1.0);
      }
      if (p > 0.0)
      {
        q = -q;
      }
      p    = std::abs(p);
      min1 = 3.0 * xm * q - std::abs(tol1 * q);
      min2 = std::abs(e * q);
      if ((p + p) < ((min1 < min2) ? min1 : min2))
      {
        e = d;
        d = p / q;
      }
      else
      {
        d = xm;
        e = d;
      }
    }
    else
    {
      d = xm;
      e = d;
    }
    a  = b;
    fa = fb;
    if (std::abs(d) > tol1)
    {
      b += d;
    }
    else
    {
      if (xm >= 0)
        b += std::abs(tol1);
      else
        b += -std::abs(tol1);
    }
    F.Value(b, fb);
    fb -= K;
  }
#ifdef OCCT_DEBUG
  std::cout << " Non Convergence dans math_FunctionRoots.cxx " << std::endl;
#endif
}

#define NEWSEQ 1

#define MATH_FUNCTIONROOTS_NEWCODE

math_FunctionRoots::math_FunctionRoots(math_FunctionWithDerivative& F,
                                       const double                 A,
                                       const double                 B,
                                       const int                    NbSample,
                                       const double                 _EpsX,
                                       const double                 EpsF,
                                       const double                 EpsNull,
                                       const double                 K)
{
#ifdef OCCT_DEBUG
  if (myDebug)
  {
    std::cout << "---- Debut de math_FunctionRoots ----" << std::endl;
    nbsolve = 0;
  }
#endif

#if NEWSEQ
  NCollection_Sequence<double> StaticSol;
#endif
  Sol.Clear();
  NbStateSol.Clear();
#ifdef MATH_FUNCTIONROOTS_NEWCODE
  {
    Done      = true;
    double X0 = A;
    double XN = B;
    int    N  = NbSample;

    if (B < A)
    {
      X0 = B;
      XN = A;
    }
    N *= 2;
    if (N < 20)
    {
      N = 20;
    }

    double EpsX   = _EpsX;
    double DeltaU = std::abs(X0) + std::abs(XN);
    double NEpsX  = 0.0000000001 * DeltaU;
    if (EpsX < NEpsX)
    {
      EpsX = NEpsX;
    }

    int                        i;
    double                     X = X0;
    bool                       Ok;
    double                     dx = (XN - X0) / N;
    NCollection_Array1<double> ptrval(0, N);
    int                        Nvalid = -1;
    double                     aux    = 0;
    for (i = 0; i <= N; i++, X += dx)
    {
      if (X > XN)
        X = XN;
      Ok = F.Value(X, aux);
      if (Ok)
        ptrval(++Nvalid) = aux - K;
    }

    if (Nvalid < N)
    {
      Done = false;
      return;
    }

    AllNull = true;

    for (i = 0; AllNull && i <= N; i++)
    {
      if (ptrval(i) > EpsNull || ptrval(i) < -EpsNull)
      {
        AllNull = false;
      }
    }
    if (AllNull)
    {
    }
    else
    {

      int ip1;

      double tol = EpsX;
      double X2;
      for (i = 0, ip1 = 1, X = X0; i < N; i++, ip1++, X += dx)
      {
        X2 = X + dx;
        if (X2 > XN)
          X2 = XN;
        if (ptrval(i) < 0.0)
        {
          if (ptrval(ip1) > 0.0)
          {

            Solve(F, K, X, ptrval(i), X2, ptrval(ip1), tol, NEpsX, Sol, NbStateSol);
          }
        }
        else
        {
          if (ptrval(ip1) < 0.0)
          {

            Solve(F, K, X, ptrval(i), X2, ptrval(ip1), tol, NEpsX, Sol, NbStateSol);
          }
        }
      }

      for (i = 0; i <= N; i++)
      {
        if (ptrval(i) == 0)
        {

          X = X0 + i * dx;
          if (X > XN)
            X = XN;
          double u0, u1;
          u0 = dx * 0.5;
          u1 = X + u0;
          u0 += X;
          if (u0 < X0)
            u0 = X0;
          if (u0 > XN)
            u0 = XN;
          if (u1 < X0)
            u1 = X0;
          if (u1 > XN)
            u1 = XN;

          double y0, y1;
          F.Value(u0, y0);
          y0 -= K;
          F.Value(u1, y1);
          y1 -= K;
          if (y0 * y1 < 0.0)
          {
            Solve(F, K, u0, y0, u1, y1, tol, NEpsX, Sol, NbStateSol);
          }
          else
          {
            if (y0 != 0.0 || y1 != 0.0)
            {
              AppendRoot(Sol, NbStateSol, X, F, K, NEpsX);
            }
          }
        }
      }

      if (ptrval(0) <= EpsF && ptrval(0) >= -EpsF)
      {
        AppendRoot(Sol, NbStateSol, X0, F, K, NEpsX);
      }
      if (ptrval(N) <= EpsF && ptrval(N) >= -EpsF)
      {
        AppendRoot(Sol, NbStateSol, XN, F, K, NEpsX);
      }

      double xm, ym, dym, xm1, xp1;
      double majdx = 5.0 * dx;
      bool   Rediscr;

      int im1 = 0;
      ip1     = 2;
      for (i = 1, xm = X0 + dx; i < N; xm += dx, i++, im1++, ip1++)
      {
        Rediscr = false;
        if (xm > XN)
          xm = XN;
        if (ptrval(i) > 0.0)
        {
          if ((ptrval(im1) > ptrval(i)) && (ptrval(ip1) > ptrval(i)))
          {

            xm1 = xm - dx;
            if (xm1 < X0)
              xm1 = X0;
            F.Values(xm1, ym, dym);
            ym -= K;
            if (dym < -1e-10 || dym > 1e-10)
            {
              double t = ym / dym;
              if (t < majdx && t > -majdx)
              {
                Rediscr = true;
              }
            }

            if (!Rediscr)
            {
              xp1 = xm + dx;
              if (xp1 > XN)
                xp1 = XN;
              F.Values(xp1, ym, dym);
              ym -= K;
              if (dym < -1e-10 || dym > 1e-10)
              {
                double t = ym / dym;
                if (t < majdx && t > -majdx)
                {
                  Rediscr = true;
                }
              }
            }
          }
        }
        else if (ptrval(i) < 0.0)
        {
          if ((ptrval(im1) < ptrval(i)) && (ptrval(ip1) < ptrval(i)))
          {

            xm1 = xm - dx;
            if (xm1 < X0)
              xm1 = X0;
            F.Values(xm1, ym, dym);
            ym -= K;
            if (dym > 1e-10 || dym < -1e-10)
            {
              double t = ym / dym;
              if (t < majdx && t > -majdx)
              {
                Rediscr = true;
              }
            }

            if (!Rediscr)
            {
              xm1 = xm - dx;
              if (xm1 < X0)
                xm1 = X0;
              F.Values(xm1, ym, dym);
              ym -= K;
              if (dym > 1e-10 || dym < -1e-10)
              {
                double t = ym / dym;
                if (t < majdx && t > -majdx)
                {
                  Rediscr = true;
                }
              }
            }
          }
        }
        if (Rediscr)
        {
          double x0 = xm - dx;
          double x3 = xm + dx;
          if (x0 < X0)
            x0 = X0;
          if (x3 > XN)
            x3 = XN;
          double aSolX1 = 0., aSolX2 = 0.;
          double aVal1 = 0., aVal2 = 0.;
          double aDer1 = 0., aDer2 = 0.;
          bool   isSol1 = false;
          bool   isSol2 = false;

          DerivFunction      aDerF(F);
          math_BracketedRoot aBR(aDerF, x0, x3, _EpsX);
          if (aBR.IsDone())
          {
            aSolX1 = aBR.Root();
            F.Value(aSolX1, aVal1);
            aVal1 = std::abs(aVal1);
            if (aVal1 < EpsF)
            {
              isSol1 = true;
              aDer1  = aBR.Value();
            }
          }

          double x1, x2, f0, f3;
          double R               = 0.61803399;
          double C               = 1.0 - R;
          double tolCR           = NEpsX * 10.0;
          f0                     = ptrval(im1);
          f3                     = ptrval(ip1);
          bool recherche_minimum = (f0 > 0.0);

          if (std::abs(x3 - xm) > std::abs(x0 - xm))
          {
            x1 = xm;
            x2 = xm + C * (x3 - xm);
          }
          else
          {
            x2 = xm;
            x1 = xm - C * (xm - x0);
          }
          double f1, f2;
          F.Value(x1, f1);
          f1 -= K;
          F.Value(x2, f2);
          f2 -= K;

          double tolX = 0.001 * NEpsX;
          while (std::abs(x3 - x0) > tolCR * (std::abs(x1) + std::abs(x2))
                 && (std::abs(x1 - x2) > tolX))
          {

            if (recherche_minimum)
            {
              if (f2 < f1)
              {
                x0 = x1;
                x1 = x2;
                x2 = R * x1 + C * x3;
                f0 = f1;
                f1 = f2;
                F.Value(x2, f2);
                f2 -= K;
              }
              else
              {
                x3 = x2;
                x2 = x1;
                x1 = R * x2 + C * x0;
                f3 = f2;
                f2 = f1;
                F.Value(x1, f1);
                f1 -= K;
              }
            }
            else
            {
              if (f2 > f1)
              {
                x0 = x1;
                x1 = x2;
                x2 = R * x1 + C * x3;
                f0 = f1;
                f1 = f2;
                F.Value(x2, f2);
                f2 -= K;
              }
              else
              {
                x3 = x2;
                x2 = x1;
                x1 = R * x2 + C * x0;
                f3 = f2;
                f2 = f1;
                F.Value(x1, f1);
                f1 -= K;
              }
            }

            if (f1 * f0 < 0.0)
            {

              Solve(F, K, x0, f0, x1, f1, tol, NEpsX, Sol, NbStateSol);
            }
            if (f2 * f3 < 0.0)
            {

              Solve(F, K, x2, f2, x3, f3, tol, NEpsX, Sol, NbStateSol);
            }
          }
          if ((recherche_minimum && f1 < f2) || (!recherche_minimum && f1 > f2))
          {

            if (std::abs(f1) < EpsF)
            {
              isSol2 = true;
              aSolX2 = x1;
              aVal2  = std::abs(f1);
            }
          }
          else
          {

            if (std::abs(f2) < EpsF)
            {
              isSol2 = true;
              aSolX2 = x2;
              aVal2  = std::abs(f2);
            }
          }

          if (isSol1 && isSol2)
          {
            if (aVal2 - aVal1 > EpsF)
              AppendRoot(Sol, NbStateSol, aSolX1, F, K, NEpsX);
            else if (aVal1 - aVal2 > EpsF)
              AppendRoot(Sol, NbStateSol, aSolX2, F, K, NEpsX);
            else
            {
              aDer1 = std::abs(aDer1);
              F.Derivative(aSolX2, aDer2);
              aDer2 = std::abs(aDer2);
              if (aDer1 < aDer2)
                AppendRoot(Sol, NbStateSol, aSolX1, F, K, NEpsX);
              else
                AppendRoot(Sol, NbStateSol, aSolX2, F, K, NEpsX);
            }
          }
          else if (isSol1)
            AppendRoot(Sol, NbStateSol, aSolX1, F, K, NEpsX);
          else if (isSol2)
            AppendRoot(Sol, NbStateSol, aSolX2, F, K, NEpsX);
        }
      }
    }

  #if NEWSEQ
    #ifdef MATH_FUNCTIONROOTS_CHECK
    {
      StaticSol.Clear();
      int n = Sol.Length();
      for (int ii = 1; ii <= n; ii++)
      {
        StaticSol.Append(Sol.Value(ii));
      }
      Sol.Clear();
      NbStateSol.Clear();
    }
    #endif
  #endif
#endif
  }
#ifdef MATH_FUNCTIONROOTS_OLDCODE
  {

    double EpsX = _EpsX;

    double Lowr, Upp;
    double Increment;
    double Null2;
    double FLowr, FUpp, DFLowr, DFUpp;
    double U, Xu;
    double Fxu, DFxu, FFxu, DFFxu;
    double Fyu, DFyu, FFyu, DFFyu;
    bool   Finish;
    double FFi;
    int    Nbiter = 30;
    int    Iter;
    double Ambda, T;
    double AA, BB, CC;
    int    Nn;
    double Alfa1              = 0, Alfa2;
    double OldDF              = RealLast();
    double Standard_Underflow = 1e-32;
    bool   Ok;

    Done = false;

    StdFail_NotDone_Raise_if(NbSample <= 0, " ");

    if (A > B)
    {
      Lowr = B;
      Upp  = A;
    }
    else
    {
      Lowr = A;
      Upp  = B;
    }

    Increment = (Upp - Lowr) / NbSample;
    StdFail_NotDone_Raise_if(Increment < EpsX, " ");
    Done = true;

    double DeltaU = std::abs(Upp) + std::abs(Lowr);
    double NEpsX  = 0.0000000001 * DeltaU;
    if (EpsX < NEpsX)
    {
      EpsX = NEpsX;
    }

    Null2 = EpsNull * EpsNull;

    Ok = F.Values(Lowr, FLowr, DFLowr);

    if (!Ok)
    {
      Done = false;
      return;
    }

    FLowr = FLowr - K;

    Ok = F.Values(Upp, FUpp, DFUpp);

    if (!Ok)
    {
      Done = false;
      return;
    }

    FUpp = FUpp - K;

    U     = Lowr - EpsX;
    Fyu   = FLowr - EpsX * DFLowr;
    DFyu  = DFLowr;
    FFyu  = Fyu * Fyu;
    DFFyu = Fyu * DFyu;
    DFFyu += DFFyu;
    AllNull = (FFyu <= Null2);

    while (U < Upp)
    {

      Xu    = U;
      Fxu   = Fyu;
      DFxu  = DFyu;
      FFxu  = FFyu;
      DFFxu = DFFyu;

      U = Xu + Increment;
      if (U <= Lowr)
      {
        Fyu  = FLowr + (U - Lowr) * DFLowr;
        DFyu = DFLowr;
      }
      else if (U >= Upp)
      {
        Fyu  = FUpp + (U - Upp) * DFUpp;
        DFyu = DFUpp;
      }
      else
      {
        Ok = F.Values(U, Fyu, DFyu);

        if (!Ok)
        {
          Done = false;
          return;
        }

        Fyu = Fyu - K;
      }
      FFyu  = Fyu * Fyu;
      DFFyu = Fyu * DFyu;
      DFFyu += DFFyu;

      if (!AllNull || (FFyu > Null2 && U <= Upp))
      {

        if (AllNull)
        {

          AllNull = false;
          Xu      = Lowr - EpsX;
          Fxu     = FLowr - EpsX * DFLowr;
          DFxu    = DFLowr;
          FFxu    = Fxu * Fxu;
          DFFxu   = Fxu * DFxu;
          DFFxu += DFFxu;
          U  = Xu + Increment;
          Ok = F.Values(U, Fyu, DFyu);

          if (!Ok)
          {
            Done = false;
            return;
          }

          Fyu   = Fyu - K;
          FFyu  = Fyu * Fyu;
          DFFyu = Fyu * DFyu;
          DFFyu += DFFyu;
        }
        double FxuFyu = Fxu * Fyu;

        if ((DFFyu > 0. && DFFxu <= 0.) || (DFFyu < 0. && FFyu >= FFxu && DFFxu <= 0.)
            || (DFFyu > 0. && FFyu <= FFxu && DFFxu >= 0.) || (FxuFyu <= 0.))
        {

          Finish = false;
          Ambda  = Increment;
          T      = 0.;
          Iter   = 0;
          FFi    = 0.;

          if (FxuFyu > 0.)
          {

            if (Fxu * (Fxu + 2. * DFxu * Increment) > 0.
                && Fyu * (Fyu - 2. * DFyu * Increment) > 0.)
            {

              Finish = true;
              FFi    = std::min(FFxu, FFyu);
            }
            else if ((DFFxu <= Standard_Underflow && -DFFxu <= Standard_Underflow)
                     || (FFxu <= Standard_Underflow && -FFxu <= Standard_Underflow))
            {

              Finish = true;
              FFxu   = 0.0;
              FFi    = FFyu;
            }
            else if ((DFFyu <= Standard_Underflow && -DFFyu <= Standard_Underflow)
                     || (FFyu <= Standard_Underflow && -FFyu <= Standard_Underflow))
            {

              Finish = true;
              FFyu   = 0.0;
              FFi    = FFxu;
            }
          }
          else if (FFxu <= Standard_Underflow && -FFxu <= Standard_Underflow)
          {

            Finish = true;
            FFxu   = 0.0;
            FFi    = FFyu;
          }
          else if (FFyu <= Standard_Underflow && -FFyu <= Standard_Underflow)
          {

            Finish = true;
            FFyu   = 0.0;
            FFi    = FFxu;
          }
          while (!Finish)
          {

            AA = 3. * (Ambda * (DFFxu + DFFyu) + 2. * (FFxu - FFyu));
            BB = -2 * (Ambda * (DFFyu + 2. * DFFxu) + 3. * (FFxu - FFyu));
            CC = Ambda * DFFxu;

            if (std::abs(AA) < 1e-14 && std::abs(BB) < 1e-14 && std::abs(CC) < 1e-14)
            {
              AA = BB = CC = 0;
            }

            math_DirectPolynomialRoots Solv(AA, BB, CC);
            if (!Solv.InfiniteRoots())
            {
              Nn = Solv.NbSolutions();
              if (Nn <= 0)
              {
                if (Fxu * Fyu < 0.)
                {
                  Alfa1 = 0.5;
                }
                else
                  Finish = true;
              }
              else
              {
                Alfa1 = Solv.Value(1);
                if (Nn == 2)
                {
                  Alfa2 = Solv.Value(2);
                  if (Alfa1 > Alfa2)
                  {
                    AA    = Alfa1;
                    Alfa1 = Alfa2;
                    Alfa2 = AA;
                  }
                  if (Alfa1 > 1. || Alfa2 < 0.)
                  {

                    if (Fxu * Fyu < 0.)
                      Alfa1 = 0.5;
                    else
                      Finish = true;
                  }
                  else if (Alfa1 < 0. || (DFFxu > 0. && DFFyu >= 0.))
                  {

                    if (Alfa2 > 1.)
                    {
                      if (Fxu * Fyu < 0.)
                        Alfa1 = 0.5;
                      else
                        Finish = true;
                    }
                    else
                      Alfa1 = Alfa2;
                  }
                }
              }
            }
            else if (Fxu * Fyu < -1e-14)
              Alfa1 = 0.5;

            else
              Finish = true;

            if (!Finish)
            {

              if (Alfa1 <= EpsX)
              {
                Alfa1 += Alfa1;
              }
              else if (Alfa1 >= (1. - EpsX))
              {
                Alfa1 = Alfa1 + Alfa1 - 1.;
              }
              Alfa1 = Ambda * (1. - Alfa1);
              U     = U + T - Alfa1;
              if (U <= Lowr)
              {
                AA = FLowr + (U - Lowr) * DFLowr;
                BB = DFLowr;
              }
              else if (U >= Upp)
              {
                AA = FUpp + (U - Upp) * DFUpp;
                BB = DFUpp;
              }
              else
              {
                Ok = F.Values(U, AA, BB);

                if (!Ok)
                {
                  Done = false;
                  return;
                }

                AA = AA - K;
              }
              FFi = AA * AA;
              CC  = AA * BB;
              CC += CC;
              if (((CC < 0. && FFi < FFxu) || DFFxu > 0.) && AA * Fxu > 0.)
              {
                FFxu  = FFi;
                DFFxu = CC;
                Fxu   = AA;
                DFxu  = BB;
                T     = Alfa1;
                if (Alfa1 > Ambda * 0.5)
                {

                  Xu = U + Alfa1 * 0.5;
                  if (Xu <= Lowr)
                  {
                    AA = FLowr + (Xu - Lowr) * DFLowr;
                    BB = DFLowr;
                  }
                  else if (Xu >= Upp)
                  {
                    AA = FUpp + (Xu - Upp) * DFUpp;
                    BB = DFUpp;
                  }
                  else
                  {
                    Ok = F.Values(Xu, AA, BB);

                    if (!Ok)
                    {
                      Done = false;
                      return;
                    }

                    AA = AA - K;
                  }
                  FFi = AA * AA;
                  CC  = AA * BB;
                  CC += CC;
                  if (((CC >= 0. || FFi >= FFxu) && DFFxu < 0.) || Fxu * AA < 0.)
                  {
                    Fyu   = AA;
                    DFyu  = BB;
                    FFyu  = FFi;
                    DFFyu = CC;
                    T     = Alfa1 * 0.5;
                    Ambda = Alfa1 * 0.5;
                  }
                  else if (AA * Fyu < 0. && AA * Fxu > 0.)
                  {

                    Fxu   = AA;
                    DFxu  = BB;
                    FFxu  = FFi;
                    DFFxu = CC;
                    FFi   = std::min(FFxu, FFyu);
                    T     = Alfa1 * 0.5;
                    Ambda = Alfa1 * 0.5;
                    U     = Xu;
                  }
                  else
                  {
                    Ambda = Alfa1;
                  }
                }
                else
                {
                  Ambda = Alfa1;
                }
              }
              else
              {
                Fyu   = AA;
                DFyu  = BB;
                FFyu  = FFi;
                DFFyu = CC;
                if ((Ambda - Alfa1) > Ambda * 0.5)
                {

                  Xu = U - (Ambda - Alfa1) * 0.5;
                  if (Xu <= Lowr)
                  {
                    AA = FLowr + (Xu - Lowr) * DFLowr;
                    BB = DFLowr;
                  }
                  else if (Xu >= Upp)
                  {
                    AA = FUpp + (Xu - Upp) * DFUpp;
                    BB = DFUpp;
                  }
                  else
                  {
                    Ok = F.Values(Xu, AA, BB);

                    if (!Ok)
                    {
                      Done = false;
                      return;
                    }

                    AA = AA - K;
                  }
                  FFi = AA * AA;
                  CC  = AA * BB;
                  CC += CC;
                  if (AA * Fyu <= 0. && AA * Fxu > 0.)
                  {
                    FFxu  = FFi;
                    DFFxu = CC;
                    Fxu   = AA;
                    DFxu  = BB;
                    Ambda = (Ambda - Alfa1) * 0.5;
                    T     = 0.;
                  }
                  else if (AA * Fxu < 0. && AA * Fyu > 0.)
                  {
                    FFyu  = FFi;
                    DFFyu = CC;
                    Fyu   = AA;
                    DFyu  = BB;
                    Ambda = (Ambda - Alfa1) * 0.5;
                    T     = 0.;
                    FFi   = std::min(FFxu, FFyu);
                    U     = Xu;
                  }
                  else
                  {
                    T     = 0.;
                    Ambda = Ambda - Alfa1;
                  }
                }
                else
                {
                  T     = 0.;
                  Ambda = Ambda - Alfa1;
                }
              }

              if (std::abs(FFxu) <= Standard_Underflow
                  || (std::abs(DFFxu) <= Standard_Underflow && Fxu * Fyu > 0.))
              {
                Finish = true;
                if (std::abs(FFxu) <= Standard_Underflow)
                {
                  FFxu = 0.0;
                }
                FFi = FFyu;
              }
              else if (std::abs(FFyu) <= Standard_Underflow
                       || (std::abs(DFFyu) <= Standard_Underflow && Fxu * Fyu > 0.))
              {
                Finish = true;
                if (std::abs(FFyu) <= Standard_Underflow)
                {
                  FFyu = 0.0;
                }
                FFi = FFxu;
              }
              else
              {
                Iter = Iter + 1;
                Finish =
                  Iter >= Nbiter || (Ambda <= EpsX && (Fxu * Fyu >= 0. || FFi <= EpsF * EpsF));
              }
            }
          }

          if (FFxu < FFi)
          {
            U = U + T - Ambda;
          }
          else if (FFyu < FFi)
          {
            U = U + T;
          }

          if (U >= (Lowr - EpsX) && U <= (Upp + EpsX))
          {
            U   = std::max(Lowr, std::min(U, Upp));
            Ok  = F.Value(U, FFi);
            FFi = FFi - K;
            if (std::abs(FFi) < EpsF)
            {

              if (std::abs(Fxu) <= Standard_Underflow)
              {
                AA = DFxu;
              }
              else if (std::abs(Fyu) <= Standard_Underflow)
              {
                AA = DFyu;
              }
              else if (Fxu * Fyu > 0.)
              {
                AA = 0.;
              }
              else
              {
                AA = Fyu - Fxu;
              }
              if (!Sol.IsEmpty())
              {
                if (std::abs(Sol.Last() - U) > 5. * EpsX
                    || (OldDF != RealLast() && OldDF * AA < 0.))
                {
                  Sol.Append(U);
                  NbStateSol.Append(F.GetStateNumber());
                }
              }
              else
              {
                Sol.Append(U);
                NbStateSol.Append(F.GetStateNumber());
              }
              OldDF = AA;
            }
          }
          DFFyu = 0.;
          Fyu   = 0.;
          Nn    = 1;
          while (Nn < 1000000 && DFFyu <= 0.)
          {

            U = U + Nn * EpsX;
            if (U <= Lowr)
            {
              AA = FLowr + (U - Lowr) * DFLowr;
              BB = DFLowr;
            }
            else if (U >= Upp)
            {
              AA = FUpp + (U - Upp) * DFUpp;
              BB = DFUpp;
            }
            else
            {
              Ok = F.Values(U, AA, BB);
              AA = AA - K;
            }
            if (AA * Fyu < 0.)
            {
              U  = U - Nn * EpsX;
              Nn = 1000001;
            }
            else
            {
              Fyu   = AA;
              DFyu  = BB;
              FFyu  = AA * AA;
              DFFyu = 2. * DFyu * Fyu;
              Nn    = 2 * Nn;
            }
          }
        }
      }
    }
  #if NEWSEQ
    #ifdef MATH_FUNCTIONROOTS_CHECK
    {
      int n1 = StaticSol.Length();
      int n2 = Sol.Length();
      if (n1 != n2)
      {
        printf("\n mathFunctionRoots : n1=%d  n2=%d EpsF=%g EpsX=%g\n", n1, n2, EpsF, NEpsX);
        for (int x1 = 1; x1 <= n1; x1++)
        {
          double v;
          F.Value(StaticSol(x1), v);
          v -= K;
          printf(" (%+13.8g:%+13.8g) ", StaticSol(x1), v);
        }
        printf("\n");
        for (int x2 = 1; x2 <= n2; x2++)
        {
          double v;
          F.Value(Sol(x2), v);
          v -= K;
          printf(" (%+13.8g:%+13.8g) ", Sol(x2), v);
        }
        printf("\n");
      }
      int n = n1;
      if (n1 > n2)
        n = n2;
      for (int i = 1; i <= n; i++)
      {
        double t = Sol(i) - StaticSol(i);
        if (std::abs(t) > NEpsX)
        {
          printf("\n mathFunctionRoots : i:%d/%d  delta: %g", i, n, t);
        }
      }
    }
    #endif
  #endif
  }
#endif
}

void math_FunctionRoots::Dump(Standard_OStream& o) const
{

  o << "math_FunctionRoots ";
  if (Done)
  {
    o << " Status = Done \n";
    o << " Number of solutions = " << Sol.Length() << std::endl;
    for (int i = 1; i <= Sol.Length(); i++)
    {
      o << " Solution Number " << i << "= " << Sol.Value(i) << std::endl;
    }
  }
  else
  {
    o << " Status = not Done \n";
  }
}
