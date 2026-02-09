

#define No_Standard_RangeError
#define No_Standard_OutOfRange
#define No_Standard_DimensionError

#include <math_Jacobi.hpp>
#include <math_Matrix.hpp>
#include <math_NotSquare.hpp>
#include <math_Recipes.hpp>

math_Jacobi::math_Jacobi(const math_Matrix& A)
    : Done(false),
      AA(1, A.RowNumber(), 1, A.RowNumber()),
      NbRotations(0),
      EigenValues(1, A.RowNumber()),
      EigenVectors(1, A.RowNumber(), 1, A.RowNumber())
{

  math_NotSquare_Raise_if(A.RowNumber() != A.ColNumber(), " ");

  AA        = A;
  int Error = Jacobi(AA, EigenValues, EigenVectors, NbRotations);
  Done      = Error == 0;
}

void math_Jacobi::Dump(Standard_OStream& o) const
{

  o << "math_Jacobi ";
  if (Done)
  {
    o << " Status = Done \n";
    o << " The eigenvalues vector is: " << EigenValues << std::endl;
  }
  else
  {
    o << "Status = not Done \n";
  }
}
