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

//! define on or several constraints as linear combination of
//! PinPointConstraint unlike the LinearScalarConstraint, usage
//! of this kind of constraint preserve the X,Y and Z uncoupling.
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

  //! Sets the PinPointConstraint of index Index to
  //! Value raise if Index is greater than the length of
  //! PPC or the Row length of coeff or lower than 1
  Standard_EXPORT void SetPPC(const int Index, const Plate_PinpointConstraint& Value);

  //! Sets the coeff of index (Row,Col) to Value
  //! raise if Row (respectively Col) is greater than the
  //! Row (respectively Column) length of coeff
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
