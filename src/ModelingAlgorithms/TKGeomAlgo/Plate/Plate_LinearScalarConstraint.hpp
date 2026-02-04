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
// Created on: 1998-05-25
// Created by: Andre LIEUTIER
// Copyright (c) 1998-1999 Matra Datavision
// Copyright (c) 1999-2014 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

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


