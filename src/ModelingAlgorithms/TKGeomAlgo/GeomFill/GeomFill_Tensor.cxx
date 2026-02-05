#include <GeomFill_Tensor.hpp>
#include <math_Matrix.hpp>

GeomFill_Tensor::GeomFill_Tensor(const int NbRow, const int NbCol, const int NbMat)
    : Tab(1, NbRow * NbMat * NbCol),
      nbrow(NbRow),
      nbcol(NbCol),
      nbmat(NbMat),
      nbmtcl(NbMat * NbCol)
{
}

void GeomFill_Tensor::Init(const double InitialValue)
{
  // int I, T = nbrow * nbcol *  nbmat;
  // for (I=1; I<=T; I++) {Tab(I) = InitialValue;}
  Tab.Init(InitialValue);
}

void GeomFill_Tensor::Multiply(const math_Vector& Right, math_Matrix& M) const
{
  int    i, j, k;
  double Somme;
  for (i = 1; i <= nbrow; i++)
  {
    for (j = 1; j <= nbcol; j++)
    {
      Somme = 0;
      for (k = 1; k <= nbmat; k++)
      {
        Somme += Value(i, j, k) * Right(k);
      }
      M(i, j) = Somme;
    }
  }
}
