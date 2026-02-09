#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Plate_PinpointConstraint.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_HArray2.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Real.hpp>
class Plate_PinpointConstraint;

class Plate_LinearXYZConstraint
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Plate_LinearXYZConstraint();

  Standard_EXPORT Plate_LinearXYZConstraint(
    const NCollection_Array1<Plate_PinpointConstraint>& thePPC,
    const NCollection_Array1<double>&                   theCoeff);

  Standard_EXPORT Plate_LinearXYZConstraint(
    const NCollection_Array1<Plate_PinpointConstraint>& thePPC,
    const NCollection_Array2<double>&                   theCoeff);

  Standard_EXPORT Plate_LinearXYZConstraint(const int ColLen, const int RowLen);

  const NCollection_Array1<Plate_PinpointConstraint>& GetPPC() const;

  const NCollection_Array2<double>& Coeff() const;

  Standard_EXPORT void SetPPC(const int Index, const Plate_PinpointConstraint& Value);

  Standard_EXPORT void SetCoeff(const int Row, const int Col, const double Value);

private:
  occ::handle<NCollection_HArray1<Plate_PinpointConstraint>> myPPC;
  occ::handle<NCollection_HArray2<double>>                   myCoef;
};

#include <NCollection_Array2.hpp>
#include <NCollection_HArray2.hpp>
#include <Plate_PinpointConstraint.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

inline const NCollection_Array1<Plate_PinpointConstraint>& Plate_LinearXYZConstraint::GetPPC() const
{
  return myPPC->Array1();
}

inline const NCollection_Array2<double>& Plate_LinearXYZConstraint::Coeff() const
{
  return myCoef->Array2();
}
