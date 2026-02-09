

#define No_Standard_RangeError
#define No_Standard_OutOfRange
#define No_Standard_DimensionError

#include <math_Crout.hpp>
#include <math_Matrix.hpp>
#include <math_Uzawa.hpp>
#include <Standard_DimensionError.hpp>
#include <StdFail_NotDone.hpp>

math_Uzawa::math_Uzawa(const math_Matrix& Cont,
                       const math_Vector& Secont,
                       const math_Vector& StartingPoint,
                       const double       EpsLix,
                       const double       EpsLic,
                       const int          NbIterations)
    : Resul(1, Cont.ColNumber()),
      Erruza(1, Cont.ColNumber()),
      Errinit(1, Cont.ColNumber()),
      Vardua(1, Cont.RowNumber()),
      CTCinv(1, Cont.RowNumber(), 1, Cont.RowNumber()),
      NbIter(0),
      Done(false)
{

  Perform(Cont, Secont, StartingPoint, Cont.RowNumber(), 0, EpsLix, EpsLic, NbIterations);
}

math_Uzawa::math_Uzawa(const math_Matrix& Cont,
                       const math_Vector& Secont,
                       const math_Vector& StartingPoint,
                       const int          Nce,
                       const int          Nci,
                       const double       EpsLix,
                       const double       EpsLic,
                       const int          NbIterations)
    : Resul(1, Cont.ColNumber()),
      Erruza(1, Cont.ColNumber()),
      Errinit(1, Cont.ColNumber()),
      Vardua(1, Cont.RowNumber()),
      CTCinv(1, Cont.RowNumber(), 1, Cont.RowNumber()),
      NbIter(0),
      Done(false)
{

  Perform(Cont, Secont, StartingPoint, Nce, Nci, EpsLix, EpsLic, NbIterations);
}

void math_Uzawa::Perform(const math_Matrix& Cont,
                         const math_Vector& Secont,
                         const math_Vector& StartingPoint,
                         const int          Nce,
                         const int          Nci,
                         const double       EpsLix,
                         const double       EpsLic,
                         const int          NbIterations)
{

  int    i, j, k;
  double scale;
  double Normat, Normli, Xian, Xmax = 0, Xmuian;
  double Rho, Err, Err1, ErrMax = 0, Coef = 1. / std::sqrt(2.);
  int    Nlig = Cont.RowNumber();
  int    Ncol = Cont.ColNumber();

  Standard_DimensionError_Raise_if((Secont.Length() != Nlig) || ((Nce + Nci) != Nlig), " ");

  for (i = 1; i <= Nlig; i++)
  {
    Errinit(i) = Cont(i, 1) * StartingPoint(1) - Secont(i);
    for (j = 2; j <= Ncol; j++)
    {
      Errinit(i) += Cont(i, j) * StartingPoint(j);
    }
  }

  if (Nci == 0)
  {
    NbIter = 1;

    for (i = 1; i <= Nlig; i++)
    {
      for (j = 1; j <= i; j++)
      {

        CTCinv(i, j) = Cont(i, 1) * Cont(j, 1);
        for (k = 2; k <= Ncol; k++)
        {
          CTCinv(i, j) += Cont(i, k) * Cont(j, k);
        }
      }
    }

    math_Crout inv(CTCinv);
    CTCinv = inv.Inverse();
    for (i = 1; i <= Nlig; i++)
    {
      scale = CTCinv(i, 1) * Errinit(1);
      for (j = 2; j <= i; j++)
      {
        scale += CTCinv(i, j) * Errinit(j);
      }
      for (j = i + 1; j <= Nlig; j++)
      {
        scale += CTCinv(j, i) * Errinit(j);
      }
      Vardua(i) = scale;
    }
    for (i = 1; i <= Ncol; i++)
    {
      Erruza(i) = -Cont(1, i) * Vardua(1);
      for (j = 2; j <= Nlig; j++)
      {
        Erruza(i) -= Cont(j, i) * Vardua(j);
      }
    }

    Resul = StartingPoint + Erruza;
    Done  = true;
    return;
  }

  else
  {

    for (i = 1; i <= Nlig; i++)
    {
      if (i <= Nce)
      {
        Vardua(i) = 0.0;
      }
      else
      {
        Vardua(i) = 1.;
      }
    }

    Normat = 0.0;
    for (i = 1; i <= Nlig; i++)
    {
      Normli = Cont(i, 1) * Cont(i, 1);
      for (j = 2; j <= Ncol; j++)
      {
        Normli += Cont(i, j) * Cont(i, j);
      }
      Normat += Normli;
    }
    Rho = Coef / Normat;

    for (NbIter = 1; NbIter <= NbIterations; NbIter++)
    {
      for (i = 1; i <= Ncol; i++)
      {
        Xian      = Erruza(i);
        Erruza(i) = -Cont(1, i) * Vardua(1);
        for (j = 2; j <= Nlig; j++)
        {
          Erruza(i) -= Cont(j, i) * Vardua(j);
        }
        if (NbIter > 1)
        {
          if (i == 1)
          {
            Xmax = std::abs(Erruza(i) - Xian);
          }
          Xmax = std::max(Xmax, std::abs(Erruza(i) - Xian));
        }
      }

      for (i = 1; i <= Nlig; i++)
      {
        Err = Cont(i, 1) * Erruza(1) + Errinit(i);
        for (j = 2; j <= Ncol; j++)
        {
          Err += Cont(i, j) * Erruza(j);
        }
        if (i <= Nce)
        {
          Vardua(i) += Rho * Err;
          Err1 = std::abs(Rho * Err);
        }
        else
        {
          Xmuian    = Vardua(i);
          Vardua(i) = std::max(0.0, Vardua(i) + Rho * Err);
          Err1      = std::abs(Vardua(i) - Xmuian);
        }
        if (i == 1)
        {
          ErrMax = Err1;
        }
        ErrMax = std::max(ErrMax, Err1);
      }

      if (NbIter > 1)
      {
        if (Xmax <= EpsLix)
        {
          if (ErrMax <= EpsLic)
          {

            Done = true;
          }
          else
          {

            Done = false;
            return;
          }

          Resul = StartingPoint + Erruza;
          Done  = true;
          return;
        }
      }
    }
    Done = false;
  }
}

void math_Uzawa::Duale(math_Vector& V) const
{
  V = Vardua;
}

void math_Uzawa::Dump(Standard_OStream& o) const
{

  o << "math_Uzawa";
  if (Done)
  {
    o << " Status = Done \n";
    o << " Number of iterations = " << NbIter << std::endl;
    o << " The solution vector is: " << Resul << std::endl;
  }
  else
  {
    o << " Status = not Done \n";
  }
}
