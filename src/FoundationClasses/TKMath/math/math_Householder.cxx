

#define No_Standard_RangeError
#define No_Standard_OutOfRange
#define No_Standard_DimensionError

#include <math_Householder.hpp>
#include <math_Matrix.hpp>
#include <Standard_DimensionError.hpp>
#include <StdFail_NotDone.hpp>

math_Householder::math_Householder(const math_Matrix& A, const math_Vector& B, const double EPS)
    : Sol(1, A.ColNumber(), 1, 1),
      Q(1, A.RowNumber(), 1, A.ColNumber()),
      Done(false)
{

  mylowerArow = A.LowerRow();
  mylowerAcol = A.LowerCol();
  myupperArow = A.UpperRow();
  myupperAcol = A.UpperCol();
  math_Matrix B1(1, B.Length(), 1, 1);
  B1.SetCol(1, B);
  Perform(A, B1, EPS);
}

math_Householder::math_Householder(const math_Matrix& A, const math_Matrix& B, const double EPS)
    : Sol(1, A.ColNumber(), 1, B.ColNumber()),
      Q(1, A.RowNumber(), A.LowerCol(), A.UpperCol()),
      Done(false)
{

  mylowerArow = A.LowerRow();
  mylowerAcol = A.LowerCol();
  myupperArow = A.UpperRow();
  myupperAcol = A.UpperCol();
  Perform(A, B, EPS);
}

math_Householder::math_Householder(const math_Matrix& A,
                                   const math_Matrix& B,
                                   const int          lowerArow,
                                   const int          upperArow,
                                   const int          lowerAcol,
                                   const int          upperAcol,
                                   const double       EPS)
    : Sol(1, upperAcol - lowerAcol + 1, 1, B.ColNumber()),
      Q(1, upperArow - lowerArow + 1, 1, upperAcol - lowerAcol + 1),
      Done(false)
{
  mylowerArow = lowerArow;
  myupperArow = upperArow;
  mylowerAcol = lowerAcol;
  myupperAcol = upperAcol;

  Perform(A, B, EPS);
}

void math_Householder::Perform(const math_Matrix& A, const math_Matrix& B, const double EPS)
{

  int    i, j, k, n, l, m;
  double f, g, h = 0., alfaii;
  double qki;
  double cj;
  n = Q.ColNumber();
  l = Q.RowNumber();
  m = B.ColNumber();
  math_Matrix B2(1, l, 1, m);

  int lbrow = B.LowerRow();
  for (i = 1; i <= l; i++)
  {
    for (j = 1; j <= n; j++)
    {
      Q(i, j) = A(i + mylowerArow - 1, j + mylowerAcol - 1);
    }
    for (j = 1; j <= m; j++)
    {
      B2(i, j) = B(i + lbrow - 1, j);
    }
  }

  Standard_DimensionError_Raise_if(l != B.RowNumber() || n > l, " ");

  for (i = 1; i <= n; i++)
  {
    h = 0.0;
    for (k = i; k <= l; k++)
    {
      qki = Q(k, i);
      h += qki * qki;
    }
    f = Q(i, i);
    g = f < 1.e-15 ? std::sqrt(h) : -std::sqrt(h);
    if (fabs(g) <= EPS)
    {
      Done = false;
      return;
    }
    h -= f * g;
    alfaii = g - f;
    for (j = i + 1; j <= n; j++)
    {
      double scale = 0.0;
      for (k = i; k <= l; k++)
      {
        scale += Q(k, i) * Q(k, j);
      }
      cj      = (g * Q(i, j) - scale) / h;
      Q(i, j) = Q(i, j) - alfaii * cj;
      for (k = i + 1; k <= l; k++)
      {
        Q(k, j) = Q(k, j) + cj * Q(k, i);
      }
    }

    for (j = 1; j <= m; j++)
    {
      double scale = Q(i, i) * B2(i, j);
      for (k = i + 1; k <= l; k++)
      {
        scale += Q(k, i) * B2(k, j);
      }
      cj       = (g * B2(i, j) - scale) / h;
      B2(i, j) = B2(i, j) - cj * alfaii;
      for (k = i + 1; k <= l; k++)
      {
        B2(k, j) = B2(k, j) + cj * Q(k, i);
      }
    }
    Q(i, i) = g;
  }

  for (j = 1; j <= m; j++)
  {
    Sol(n, j) = B2(n, j) / Q(n, n);
    for (i = n - 1; i >= 1; i--)
    {
      double scale = 0.0;
      for (k = i + 1; k <= n; k++)
      {
        scale += Q(i, k) * Sol(k, j);
      }
      Sol(i, j) = (B2(i, j) - scale) / Q(i, i);
    }
  }
  Done = true;
}

void math_Householder::Dump(Standard_OStream& o) const
{

  o << "math_Householder ";
  if (Done)
  {
    o << " Status = Done \n";
  }
  else
  {
    o << "Status = not Done \n";
  }
}
