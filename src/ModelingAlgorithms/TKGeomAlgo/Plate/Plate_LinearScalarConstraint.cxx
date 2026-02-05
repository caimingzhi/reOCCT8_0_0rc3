#include <gp_XYZ.hpp>
#include <Plate_LinearScalarConstraint.hpp>
#include <Plate_PinpointConstraint.hpp>
#include <Standard_DimensionMismatch.hpp>

Plate_LinearScalarConstraint::Plate_LinearScalarConstraint() = default;

Plate_LinearScalarConstraint::Plate_LinearScalarConstraint(const Plate_PinpointConstraint& PPC1,
                                                           const gp_XYZ&                   coeff)

{
  myPPC  = new NCollection_HArray1<Plate_PinpointConstraint>(1, 1);
  myCoef = new NCollection_HArray2<gp_XYZ>(1, 1, 1, 1);

  myPPC->ChangeValue(1)     = PPC1;
  myCoef->ChangeValue(1, 1) = coeff;
}

Plate_LinearScalarConstraint::Plate_LinearScalarConstraint(
  const NCollection_Array1<Plate_PinpointConstraint>& thePPC,
  const NCollection_Array1<gp_XYZ>&                   theCoeff)
{
  if (theCoeff.Length() != thePPC.Length())
    throw Standard_DimensionMismatch();
  myPPC  = new NCollection_HArray1<Plate_PinpointConstraint>(1, thePPC.Length());
  myCoef = new NCollection_HArray2<gp_XYZ>(1, 1, 1, theCoeff.Length());

  myPPC->ChangeArray1() = thePPC;
  for (int i = 1; i <= theCoeff.Length(); i++)
  {
    myCoef->ChangeValue(1, i) = theCoeff(i + theCoeff.Lower() - 1);
  }
}

Plate_LinearScalarConstraint::Plate_LinearScalarConstraint(
  const NCollection_Array1<Plate_PinpointConstraint>& thePPC,
  const NCollection_Array2<gp_XYZ>&                   theCoeff)
{
  if (theCoeff.RowLength() != thePPC.Length())
    throw Standard_DimensionMismatch();
  myPPC  = new NCollection_HArray1<Plate_PinpointConstraint>(1, thePPC.Length());
  myCoef = new NCollection_HArray2<gp_XYZ>(1, theCoeff.ColLength(), 1, theCoeff.RowLength());

  myPPC->ChangeArray1()  = thePPC;
  myCoef->ChangeArray2() = theCoeff;
}

Plate_LinearScalarConstraint::Plate_LinearScalarConstraint(const int ColLen, const int RowLen)
{
  myPPC  = new NCollection_HArray1<Plate_PinpointConstraint>(1, RowLen);
  myCoef = new NCollection_HArray2<gp_XYZ>(1, ColLen, 1, RowLen);
  myCoef->Init(gp_XYZ(0., 0., 0.));
}

void Plate_LinearScalarConstraint::SetPPC(const int Index, const Plate_PinpointConstraint& Value)
{
  myPPC->ChangeValue(Index) = Value;
}

void Plate_LinearScalarConstraint::SetCoeff(const int Row, const int Col, const gp_XYZ& Value)
{
  myCoef->ChangeValue(Row, Col) = Value;
}
