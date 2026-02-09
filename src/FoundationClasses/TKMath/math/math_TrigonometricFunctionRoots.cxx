

#define No_Standard_RangeError
#define No_Standard_OutOfRange
#define No_Standard_DimensionError

#include <math_TrigonometricFunctionRoots.hpp>
#include <math_TrigonometricEquationFunction.hpp>
#include <math_DirectPolynomialRoots.hpp>
#include <math_FunctionWithDerivative.hpp>
#include <math_NewtonFunctionRoot.hpp>
#include <Precision.hpp>

math_TrigonometricFunctionRoots::math_TrigonometricFunctionRoots(const double theD,
                                                                 const double theE,
                                                                 const double theInfBound,
                                                                 const double theSupBound)
    : NbSol(-1),
      Sol(1, 4),
      InfiniteStatus(false),
      Done(false)
{
  const double A(0.0), B(0.0), C(0.0);
  Perform(A, B, C, theD, theE, theInfBound, theSupBound);
}

math_TrigonometricFunctionRoots::math_TrigonometricFunctionRoots(const double theC,
                                                                 const double theD,
                                                                 const double theE,
                                                                 const double theInfBound,
                                                                 const double theSupBound)
    : NbSol(-1),
      Sol(1, 4),
      InfiniteStatus(false),
      Done(false)
{
  const double A(0.0), B(0.0);
  Perform(A, B, theC, theD, theE, theInfBound, theSupBound);
}

math_TrigonometricFunctionRoots::math_TrigonometricFunctionRoots(const double theA,
                                                                 const double theB,
                                                                 const double theC,
                                                                 const double theD,
                                                                 const double theE,
                                                                 const double theInfBound,
                                                                 const double theSupBound)
    : NbSol(-1),
      Sol(1, 4),
      InfiniteStatus(false),
      Done(false)
{
  Perform(theA, theB, theC, theD, theE, theInfBound, theSupBound);
}

void math_TrigonometricFunctionRoots::Perform(const double A,
                                              const double B,
                                              const double C,
                                              const double D,
                                              const double E,
                                              const double InfBound,
                                              const double SupBound)
{

  int                        i, j = 0, k, l, NZer = 0, Nit = 10;
  double                     Depi, Delta, Mod, AA, BB, CC, MyBorneInf;
  double                     Teta, X;
  double                     Eps, Tol1 = 1.e-15;
  NCollection_Array1<double> ko(1, 5), Zer(1, 4);
  bool                       Flag4;
  InfiniteStatus = false;
  Done           = true;

  Eps = 1.5e-12;

  Depi = M_PI + M_PI;
  if (InfBound <= RealFirst() && SupBound >= RealLast())
  {
    MyBorneInf = 0.0;
    Delta      = Depi;
    Mod        = 0.0;
  }
  else if (SupBound >= RealLast())
  {
    MyBorneInf = InfBound;
    Delta      = Depi;
    Mod        = MyBorneInf / Depi;
  }
  else if (InfBound <= RealFirst())
  {
    MyBorneInf = SupBound - Depi;
    Delta      = Depi;
    Mod        = MyBorneInf / Depi;
  }
  else
  {
    MyBorneInf = InfBound;
    Delta      = SupBound - InfBound;
    Mod        = InfBound / Depi;
    if ((SupBound - InfBound) > Depi)
    {
      Delta = Depi;
    }
  }

  if ((std::abs(A) <= Eps) && (std::abs(B) <= Eps))
  {
    if (std::abs(C) <= Eps)
    {
      if (std::abs(D) <= Eps)
      {
        if (std::abs(E) <= Eps)
        {
          InfiniteStatus = true;
          return;
        }
        else
        {
          NbSol = 0;
          return;
        }
      }
      else
      {

        NbSol = 0;
        AA    = -E / D;
        if (std::abs(AA) > 1.)
        {
          return;
        }

        Zer(1) = std::asin(AA);
        Zer(2) = M_PI - Zer(1);
        NZer   = 2;
        for (i = 1; i <= NZer; i++)
        {
          if (Zer(i) <= -Eps)
          {
            Zer(i) = Depi - std::abs(Zer(i));
          }

          Zer(i) += std::trunc(Mod) * Depi;
          X = Zer(i) - MyBorneInf;
          if ((X > (-Epsilon(Delta))) && (X < Delta + Epsilon(Delta)))
          {
            NbSol++;
            Sol(NbSol) = Zer(i);
          }
        }
      }
      return;
    }
    else if (std::abs(D) <= Eps)
    {

      NbSol = 0;
      AA    = -E / C;
      if (std::abs(AA) > 1.)
      {
        return;
      }
      Zer(1) = std::acos(AA);
      Zer(2) = -Zer(1);
      NZer   = 2;

      for (i = 1; i <= NZer; i++)
      {
        if (Zer(i) <= -Eps)
        {
          Zer(i) = Depi - std::abs(Zer(i));
        }

        Zer(i) += std::trunc(Mod) * 2. * M_PI;
        X = Zer(i) - MyBorneInf;
        if ((X >= (-Epsilon(Delta))) && (X <= Delta + Epsilon(Delta)))
        {
          NbSol++;
          Sol(NbSol) = Zer(i);
        }
      }
      return;
    }
    else
    {

      AA = E - C;
      BB = 2.0 * D;
      CC = E + C;

      math_DirectPolynomialRoots Resol(AA, BB, CC);
      if (!Resol.IsDone())
      {
        Done = false;
        return;
      }
      else if (!Resol.InfiniteRoots())
      {
        NZer = Resol.NbSolutions();
        for (i = 1; i <= NZer; i++)
        {
          Zer(i) = Resol.Value(i);
        }
      }
      else if (Resol.InfiniteRoots())
      {
        InfiniteStatus = true;
        return;
      }
    }
  }
  else
  {

    if ((std::abs(A) <= Eps) && (std::abs(E) <= Eps))
    {
      if (std::abs(C) <= Eps)
      {

        NZer   = 2;
        Zer(1) = 0.0;
        Zer(2) = M_PI;

        AA = -D / (B * 2);
        if (std::abs(AA) <= 1.0 + Precision::PConfusion())
        {
          NZer = 4;
          if (AA >= 1.0)
          {
            Zer(3) = 0.0;
            Zer(4) = 0.0;
          }
          else if (AA <= -1.0)
          {
            Zer(3) = M_PI;
            Zer(4) = M_PI;
          }
          else
          {
            Zer(3) = std::acos(AA);
            Zer(4) = Depi - Zer(3);
          }
        }

        NbSol = 0;
        for (i = 1; i <= NZer; i++)
        {
          if (Zer(i) <= MyBorneInf - Eps)
          {
            Zer(i) += Depi;
          }

          Zer(i) += std::trunc(Mod) * 2. * M_PI;
          X = Zer(i) - MyBorneInf;
          if ((X >= (-Precision::PConfusion())) && (X <= Delta + Precision::PConfusion()))
          {
            if (Zer(i) < InfBound)
              Zer(i) = InfBound;
            if (Zer(i) > SupBound)
              Zer(i) = SupBound;
            NbSol++;
            Sol(NbSol) = Zer(i);
          }
        }
        return;
      }
      if (std::abs(D) <= Eps)
      {

        NZer   = 2;
        Zer(1) = M_PI / 2.0;
        Zer(2) = M_PI * 3.0 / 2.0;

        AA = -C / (B * 2);
        if (std::abs(AA) <= 1.0 + Precision::PConfusion())
        {
          NZer = 4;
          if (AA >= 1.0)
          {
            Zer(3) = M_PI / 2.0;
            Zer(4) = M_PI / 2.0;
          }
          else if (AA <= -1.0)
          {

            Zer(3) = M_PI * 3.0 / 2.0;
            Zer(4) = M_PI * 3.0 / 2.0;
          }
          else
          {
            Zer(3) = std::asin(AA);
            Zer(4) = M_PI - Zer(3);
          }
        }

        NbSol = 0;
        for (i = 1; i <= NZer; i++)
        {
          if (Zer(i) <= MyBorneInf - Eps)
          {
            Zer(i) += Depi;
          }

          Zer(i) += std::trunc(Mod) * 2. * M_PI;
          X = Zer(i) - MyBorneInf;
          if ((X >= (-Precision::PConfusion())) && (X <= Delta + Precision::PConfusion()))
          {
            if (Zer(i) < InfBound)
              Zer(i) = InfBound;
            if (Zer(i) > SupBound)
              Zer(i) = SupBound;
            NbSol++;
            Sol(NbSol) = Zer(i);
          }
        }
        return;
      }
    }

    ko(1) = A - C + E;
    ko(2) = 2.0 * D - 4.0 * B;
    ko(3) = 2.0 * E - 2.0 * A;
    ko(4) = 4.0 * B + 2.0 * D;
    ko(5) = A + C + E;
    bool bko;
    do
    {
      bko = false;
      math_DirectPolynomialRoots Resol4(ko(1), ko(2), ko(3), ko(4), ko(5));
      if (!Resol4.IsDone())
      {
        Done = false;
        return;
      }
      else if (!Resol4.InfiniteRoots())
      {
        NZer = Resol4.NbSolutions();
        for (i = 1; i <= NZer; i++)
        {
          Zer(i) = Resol4.Value(i);
        }
      }
      else if (Resol4.InfiniteRoots())
      {
        InfiniteStatus = true;
        return;
      }
      bool triok;
      do
      {
        triok = true;
        for (i = 1; i < NZer; i++)
        {
          if (Zer(i) > Zer(i + 1))
          {
            double t   = Zer(i);
            Zer(i)     = Zer(i + 1);
            Zer(i + 1) = t;
            triok      = false;
          }
        }
      } while (!triok);

      for (i = 1; i < NZer; i++)
      {
        if (std::abs(Zer(i + 1) - Zer(i)) < Eps)
        {

          double qw = Zer(i + 1);
          double va = ko(4) + qw * (2.0 * ko(3) + qw * (3.0 * ko(2) + qw * (4.0 * ko(1))));

          if (std::abs(va) > Eps)
          {
            bko = true;
#ifdef OCCT_DEBUG

#endif
            break;
          }
        }
      }
      if (bko)
      {

        ko(1) *= 0.0001;
        ko(2) *= 0.0001;
        ko(3) *= 0.0001;
        ko(4) *= 0.0001;
        ko(5) *= 0.0001;
      }
    } while (bko);
  }

  double SupmInfs100 = (SupBound - InfBound) * 0.01;
  NbSol              = 0;
  for (i = 1; i <= NZer; i++)
  {
    Teta = atan(Zer(i));
    Teta += Teta;
    if (Zer(i) <= (-Eps))
    {
      Teta = Depi - std::abs(Teta);
    }
    Teta += std::trunc(Mod) * Depi;
    if (Teta - MyBorneInf < 0)
      Teta += Depi;

    X = Teta - MyBorneInf;
    if ((X >= (-Epsilon(Delta))) && (X <= Delta + Epsilon(Delta)))
    {
      X = Teta;

      double                             TetaNewton = Teta;
      math_TrigonometricEquationFunction MyF(A, B, C, D, E);
      math_NewtonFunctionRoot            Resol(MyF, X, Tol1, Eps, Nit);
      if (Resol.IsDone())
      {
        TetaNewton = Resol.Root();
      }

      double DeltaNewton = TetaNewton - Teta;
      if ((DeltaNewton > SupmInfs100) || (DeltaNewton < -SupmInfs100))
      {
      }
      else
      {
        Teta = TetaNewton;
      }

      Flag4 = false;

      for (k = 1; k <= NbSol; k++)
      {

        if (Teta < Sol(k))
        {
          for (l = k; l <= NbSol; l++)
          {
            j          = NbSol - l + k;
            Sol(j + 1) = Sol(j);
          }
          Sol(k) = Teta;
          NbSol++;
          Flag4 = true;
          break;
        }
      }
      if (!Flag4)
      {
        NbSol++;
        Sol(NbSol) = Teta;
      }
    }
  }

  if (NbSol < 4)
  {
    int startIndex = NbSol + 1;
    for (int solIt = startIndex; solIt <= 4; solIt++)
    {
      Teta = M_PI + std::trunc(Mod) * 2.0 * M_PI;
      X    = Teta - MyBorneInf;
      if ((X >= (-Epsilon(Delta))) && (X <= Delta + Epsilon(Delta)))
      {
        if (std::abs(A - C + E) <= Eps)
        {
          Flag4 = false;
          for (k = 1; k <= NbSol; k++)
          {
            j = k;
            if (Teta < Sol(k))
            {
              Flag4 = true;
              break;
            }
            if ((solIt == startIndex) && (std::abs(Teta - Sol(k)) <= Eps))
            {
              return;
            }
          }

          if (!Flag4)
          {
            NbSol++;
            Sol(NbSol) = Teta;
          }
          else
          {
            for (k = j; k <= NbSol; k++)
            {
              i          = NbSol - k + j;
              Sol(i + 1) = Sol(i);
            }
            Sol(j) = Teta;
            NbSol++;
          }
        }
      }
    }
  }
}

void math_TrigonometricFunctionRoots::Dump(Standard_OStream& o) const
{
  o << " math_TrigonometricFunctionRoots: \n";
  if (!Done)
  {
    o << "Not Done \n";
  }
  else if (InfiniteStatus)
  {
    o << " There is an infinity of roots\n";
  }
  else if (!InfiniteStatus)
  {
    o << " Number of solutions = " << NbSol << "\n";
    for (int i = 1; i <= NbSol; i++)
    {
      o << " Value number " << i << "= " << Sol(i) << "\n";
    }
  }
}
