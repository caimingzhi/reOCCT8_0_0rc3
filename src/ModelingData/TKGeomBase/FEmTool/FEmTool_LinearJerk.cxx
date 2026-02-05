#include <FEmTool_ElementsOfRefMatrix.hpp>
#include <FEmTool_LinearJerk.hpp>
#include <math.hpp>
#include <math_GaussSetIntegration.hpp>
#include <math_IntegerVector.hpp>
#include <math_Matrix.hpp>
#include <math_Vector.hpp>
#include <PLib.hpp>
#include <PLib_HermitJacobi.hpp>
#include <Standard_ConstructionError.hpp>
#include <Standard_DomainError.hpp>
#include <Standard_NotImplemented.hpp>
#include <Standard_Type.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_HArray2.hpp>

IMPLEMENT_STANDARD_RTTIEXT(FEmTool_LinearJerk, FEmTool_ElementaryCriterion)

FEmTool_LinearJerk::FEmTool_LinearJerk(const int WorkDegree, const GeomAbs_Shape ConstraintOrder)
    : RefMatrix(0, WorkDegree, 0, WorkDegree)
{
  static int         Order = -333, WDeg = 14;
  static math_Vector MatrixElemts(0, ((WDeg + 2) * (WDeg + 1)) / 2 - 1);

  myOrder = PLib::NivConstr(ConstraintOrder);

  // Calculating RefMatrix
  if (myOrder != Order)
  {
    if (WorkDegree > WDeg)
      throw Standard_ConstructionError("Degree too high");
    Order        = myOrder;
    int DerOrder = 3;

    PLib_HermitJacobi           theBase(WDeg, ConstraintOrder);
    FEmTool_ElementsOfRefMatrix Elem = FEmTool_ElementsOfRefMatrix(theBase, DerOrder);

    int maxDegree = WDeg + 1;

    math_IntegerVector anOrder(1, 1, std::min(4 * (maxDegree / 2 + 1), math::GaussPointsMax()));

    math_Vector Lower(1, 1, -1.), Upper(1, 1, 1.);

    math_GaussSetIntegration anInt(Elem, Lower, Upper, anOrder);

    MatrixElemts = anInt.Value();
  }

  int i, j, ii, jj;
  for (ii = i = 0; i <= WorkDegree; i++)
  {
    RefMatrix(i, i) = MatrixElemts(ii);
    for (j = i + 1, jj = ii + 1; j <= WorkDegree; j++, jj++)
    {
      RefMatrix(j, i) = RefMatrix(i, j) = MatrixElemts(jj);
    }
    ii += WDeg + 1 - i;
  }
}

occ::handle<NCollection_HArray2<int>> FEmTool_LinearJerk::DependenceTable() const
{
  if (myCoeff.IsNull())
    throw Standard_DomainError("FEmTool_LinearJerk::DependenceTable");

  occ::handle<NCollection_HArray2<int>> DepTab = new NCollection_HArray2<int>(myCoeff->LowerCol(),
                                                                              myCoeff->UpperCol(),
                                                                              myCoeff->LowerCol(),
                                                                              myCoeff->UpperCol(),
                                                                              0);
  int                                   i;
  for (i = myCoeff->LowerCol(); i <= myCoeff->UpperCol(); i++)
    DepTab->SetValue(i, i, 1);

  return DepTab;
}

double FEmTool_LinearJerk::Value()
{
  int deg = std::min(myCoeff->ColLength() - 1, RefMatrix.UpperRow()), i, j,
      j0 = myCoeff->LowerRow(), degH = std::min(2 * myOrder + 1, deg), NbDim = myCoeff->RowLength(),
      dim;

  NCollection_Array2<double> NewCoeff(1, NbDim, 0, deg);

  double coeff = (myLast - myFirst) / 2., cteh3 = 2. / std::pow(coeff, 5), mfact, Jline;

  int k1;

  double J = 0.;

  for (i = 0; i <= degH; i++)
  {
    k1    = (i <= myOrder) ? i : i - myOrder - 1;
    mfact = std::pow(coeff, k1);
    for (dim = 1; dim <= NbDim; dim++)
      NewCoeff(dim, i) = myCoeff->Value(j0 + i, dim) * mfact;
  }

  for (i = degH + 1; i <= deg; i++)
  {
    for (dim = 1; dim <= NbDim; dim++)
      NewCoeff(dim, i) = myCoeff->Value(j0 + i, dim);
  }

  for (dim = 1; dim <= NbDim; dim++)
  {

    for (i = 0; i <= deg; i++)
    {

      Jline = 0.5 * RefMatrix(i, i) * NewCoeff(dim, i);

      for (j = 0; j < i; j++)
        Jline += RefMatrix(i, j) * NewCoeff(dim, j);

      J += Jline * NewCoeff(dim, i);
      if (J < 0.)
        J = 0.;
    }
  }

  return cteh3 * J;
}

void FEmTool_LinearJerk::Hessian(const int Dimension1, const int Dimension2, math_Matrix& H)
{

  occ::handle<NCollection_HArray2<int>> DepTab = DependenceTable();

  if (Dimension1 < DepTab->LowerRow() || Dimension1 > DepTab->UpperRow()
      || Dimension2 < DepTab->LowerCol() || Dimension2 > DepTab->UpperCol())
    throw Standard_OutOfRange("FEmTool_LinearJerk::Hessian");

  if (DepTab->Value(Dimension1, Dimension2) == 0)
    throw Standard_DomainError("FEmTool_LinearJerk::Hessian");

  int deg  = std::min(RefMatrix.UpperRow(), H.RowNumber() - 1),
      degH = std::min(2 * myOrder + 1, deg);

  double coeff = (myLast - myFirst) / 2., cteh3 = 2. / std::pow(coeff, 5), mfact;
  int    k1, k2, i, j, i0 = H.LowerRow(), j0 = H.LowerCol(), i1, j1;

  H.Init(0.);

  i1 = i0;
  for (i = 0; i <= degH; i++)
  {
    k1    = (i <= myOrder) ? i : i - myOrder - 1;
    mfact = std::pow(coeff, k1) * cteh3;
    // Hermite*Hermite part of matrix
    j1 = j0 + i;
    for (j = i; j <= degH; j++)
    {
      k2        = (j <= myOrder) ? j : j - myOrder - 1;
      H(i1, j1) = mfact * std::pow(coeff, k2) * RefMatrix(i, j);
      if (i != j)
        H(j1, i1) = H(i1, j1);
      j1++;
    }
    // Hermite*Jacobi part of matrix
    j1 = j0 + degH + 1;
    for (j = degH + 1; j <= deg; j++)
    {
      H(i1, j1) = mfact * RefMatrix(i, j);
      H(j1, i1) = H(i1, j1);
      j1++;
    }
    i1++;
  }

  // Jacoby*Jacobi part of matrix
  i1 = i0 + degH + 1;
  for (i = degH + 1; i <= deg; i++)
  {
    j1 = j0 + i;
    for (j = i; j <= deg; j++)
    {
      H(i1, j1) = cteh3 * RefMatrix(i, j);
      if (i != j)
        H(j1, i1) = H(i1, j1);
      j1++;
    }
    i1++;
  }
}

void FEmTool_LinearJerk::Gradient(const int Dimension, math_Vector& G)
{
  if (Dimension < myCoeff->LowerCol() || Dimension > myCoeff->UpperCol())
    throw Standard_OutOfRange("FEmTool_LinearJerk::Gradient");

  int deg = std::min(G.Length() - 1, myCoeff->ColLength() - 1);

  math_Vector X(0, deg);
  int         i, i1 = myCoeff->LowerRow();
  for (i = 0; i <= deg; i++)
    X(i) = myCoeff->Value(i1 + i, Dimension);

  math_Matrix H(0, deg, 0, deg);
  Hessian(Dimension, Dimension, H);

  G.Multiply(H, X);
}
