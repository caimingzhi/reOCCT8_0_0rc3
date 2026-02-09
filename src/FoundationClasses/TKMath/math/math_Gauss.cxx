

#include <math_Gauss.hpp>

#include <math_Matrix.hpp>
#include <math_NotSquare.hpp>
#include <math_Recipes.hpp>
#include <Standard_DimensionError.hpp>
#include <StdFail_NotDone.hpp>

math_Gauss::math_Gauss(const math_Matrix&           A,
                       const double                 MinPivot,
                       const Message_ProgressRange& theProgress)
    : LU(1, A.RowNumber(), 1, A.ColNumber()),
      Index(1, A.RowNumber()),
      D(0.0),
      Done(false)
{
  math_NotSquare_Raise_if(A.RowNumber() != A.ColNumber(), " ");
  LU        = A;
  int Error = LU_Decompose(LU, Index, D, MinPivot, theProgress);
  Done      = Error == 0;
}

void math_Gauss::Solve(const math_Vector& B, math_Vector& X) const
{

  StdFail_NotDone_Raise_if(!Done, " ");

  X = B;
  LU_Solve(LU, Index, X);
}

void math_Gauss::Solve(math_Vector& X) const
{

  StdFail_NotDone_Raise_if(!Done, " ");

  if (X.Length() != LU.RowNumber())
  {
    throw Standard_DimensionError();
  }
  LU_Solve(LU, Index, X);
}

double math_Gauss::Determinant() const
{

  StdFail_NotDone_Raise_if(!Done, " ");

  double Result = D;
  for (int J = 1; J <= LU.UpperRow(); J++)
  {
    Result *= LU(J, J);
  }
  return Result;
}

void math_Gauss::Invert(math_Matrix& Inv) const
{

  StdFail_NotDone_Raise_if(!Done, " ");

  Standard_DimensionError_Raise_if((Inv.RowNumber() != LU.RowNumber())
                                     || (Inv.ColNumber() != LU.ColNumber()),
                                   " ");

  int         LowerRow = Inv.LowerRow();
  int         LowerCol = Inv.LowerCol();
  math_Vector Column(1, LU.UpperRow());

  int I, J;
  for (J = 1; J <= LU.UpperRow(); J++)
  {
    for (I = 1; I <= LU.UpperRow(); I++)
    {
      Column(I) = 0.0;
    }
    Column(J) = 1.0;
    LU_Solve(LU, Index, Column);
    for (I = 1; I <= LU.RowNumber(); I++)
    {
      Inv(I + LowerRow - 1, J + LowerCol - 1) = Column(I);
    }
  }
}

void math_Gauss::Dump(Standard_OStream& o) const
{
  o << "math_Gauss ";
  if (Done)
  {
    o << " Status = Done \n";
    o << " Determinant of A = " << D << std::endl;
  }
  else
  {
    o << " Status = not Done \n";
  }
}
