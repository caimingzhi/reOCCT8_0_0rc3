#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Plate_PinpointConstraint.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <gp_XYZ.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_HArray2.hpp>
#include <Standard_Integer.hpp>
class Plate_PinpointConstraint;
class gp_XYZ;

//! define on or several constraints as linear combination of
//! the X,Y and Z components of a set of PinPointConstraint
class Plate_LinearScalarConstraint
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Plate_LinearScalarConstraint();

  Standard_EXPORT Plate_LinearScalarConstraint(const Plate_PinpointConstraint& thePPC1,
                                               const gp_XYZ&                   theCoeff);

  Standard_EXPORT Plate_LinearScalarConstraint(
    const NCollection_Array1<Plate_PinpointConstraint>& thePPC,
    const NCollection_Array1<gp_XYZ>&                   theCoeff);

  Standard_EXPORT Plate_LinearScalarConstraint(
    const NCollection_Array1<Plate_PinpointConstraint>& thePPC,
    const NCollection_Array2<gp_XYZ>&                   theCoeff);

  Standard_EXPORT Plate_LinearScalarConstraint(const int ColLen, const int RowLen);

  const NCollection_Array1<Plate_PinpointConstraint>& GetPPC() const;

  const NCollection_Array2<gp_XYZ>& Coeff() const;

  //! Sets the PinPointConstraint of index Index to
  //! Value raise if Index is greater than the length of
  //! PPC or the Row length of coeff or lower than 1
  Standard_EXPORT void SetPPC(const int Index, const Plate_PinpointConstraint& Value);

  //! Sets the coeff of index (Row,Col) to Value
  //! raise if Row (respectively Col) is greater than the
  //! Row (respectively Column) length of coeff
  Standard_EXPORT void SetCoeff(const int Row, const int Col, const gp_XYZ& Value);

private:
  occ::handle<NCollection_HArray1<Plate_PinpointConstraint>> myPPC;
  occ::handle<NCollection_HArray2<gp_XYZ>>                   myCoef;
};

#include <gp_XYZ.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_HArray2.hpp>
#include <Plate_PinpointConstraint.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

inline const NCollection_Array1<Plate_PinpointConstraint>& Plate_LinearScalarConstraint::GetPPC()
  const
{
  return myPPC->Array1();
}

inline const NCollection_Array2<gp_XYZ>& Plate_LinearScalarConstraint::Coeff() const
{
  return myCoef->Array2();
}
