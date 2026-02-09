

#define No_Standard_RangeError
#define No_Standard_OutOfRange
#define No_Standard_DimensionError

#include <math_Crout.hpp>
#include <math_Matrix.hpp>
#include <math_NotSquare.hpp>
#include <math_Vector.hpp>
#include <Standard_DimensionError.hpp>
#include <StdFail_NotDone.hpp>

math_Crout::math_Crout(const math_Matrix& A, const double MinPivot)
    : InvA(1, A.RowNumber(), 1, A.ColNumber())
{
  int    i, j, k;
  int    Nctl = A.RowNumber();
  int    lowr = A.LowerRow(), lowc = A.LowerCol();
  double scale;

  math_Matrix L(1, Nctl, 1, Nctl);
  math_Vector Diag(1, Nctl);

  math_NotSquare_Raise_if(Nctl != A.ColNumber(), " ");

  Det = 1;
  for (i = 1; i <= Nctl; i++)
  {
    for (j = 1; j <= i - 1; j++)
    {
      scale = 0.0;
      for (k = 1; k <= j - 1; k++)
      {
        scale += L(i, k) * L(j, k) * Diag(k);
      }
      L(i, j) = (A(i + lowr - 1, j + lowc - 1) - scale) / Diag(j);
    }
    scale = 0.0;
    for (k = 1; k <= i - 1; k++)
    {
      scale += L(i, k) * L(i, k) * Diag(k);
    }
    Diag(i) = A(i + lowr - 1, i + lowc - 1) - scale;
    Det *= Diag(i);
    if (std::abs(Diag(i)) <= MinPivot)
    {
      Done = false;
      return;
    }
    L(i, i) = 1.0;
  }

  L(1, 1) = 1. / L(1, 1);
  for (i = 2; i <= Nctl; i++)
  {
    for (k = 1; k <= i - 1; k++)
    {
      scale = 0.0;
      for (j = k; j <= i - 1; j++)
      {
        scale += L(i, j) * L(j, k);
      }
      L(i, k) = -scale / L(i, i);
    }
    L(i, i) = 1. / L(i, i);
  }

  for (j = 1; j <= Nctl; j++)
  {
    scale = L(j, j) * L(j, j) / Diag(j);
    for (k = j + 1; k <= Nctl; k++)
    {
      scale += L(k, j) * L(k, j) / Diag(k);
    }
    InvA(j, j) = scale;
    for (i = j + 1; i <= Nctl; i++)
    {
      scale = L(i, j) * L(i, i) / Diag(i);
      for (k = i + 1; k <= Nctl; k++)
      {
        scale += L(k, j) * L(k, i) / Diag(k);
      }
      InvA(i, j) = scale;
    }
  }
  Done = true;
}

void math_Crout::Solve(const math_Vector& B, math_Vector& X) const
{
  StdFail_NotDone_Raise_if(!Done, " ");
  Standard_DimensionError_Raise_if((B.Length() != InvA.RowNumber()) || (X.Length() != B.Length()),
                                   " ");

  int n    = InvA.RowNumber();
  int lowb = B.Lower(), lowx = X.Lower();
  int i, j;

  for (i = 1; i <= n; i++)
  {
    X(i + lowx - 1) = InvA(i, 1) * B(1 + lowb - 1);
    for (j = 2; j <= i; j++)
    {
      X(i + lowx - 1) += InvA(i, j) * B(j + lowb - 1);
    }
    for (j = i + 1; j <= n; j++)
    {
      X(i + lowx - 1) += InvA(j, i) * B(j + lowb - 1);
    }
  }
}

void math_Crout::Dump(Standard_OStream& o) const
{
  o << "math_Crout ";
  if (Done)
  {
    o << " Status = Done \n";
  }
  else
  {
    o << " Status = not Done \n";
  }
}
