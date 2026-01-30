// Created on: 1997-03-26
// Created by: Christian CAILLET
// Copyright (c) 1997-1999 Matra Datavision
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

#ifndef _StepBasic_DerivedUnit_HeaderFile
#define _StepBasic_DerivedUnit_HeaderFile

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepBasic_DerivedUnitElement.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Integer.hpp>
class StepBasic_DerivedUnitElement;

//! Added from StepBasic Rev2 to Rev4
class StepBasic_DerivedUnit : public Standard_Transient
{

public:
  Standard_EXPORT StepBasic_DerivedUnit();

  Standard_EXPORT void Init(
    const occ::handle<NCollection_HArray1<occ::handle<StepBasic_DerivedUnitElement>>>& elements);

  Standard_EXPORT void SetElements(
    const occ::handle<NCollection_HArray1<occ::handle<StepBasic_DerivedUnitElement>>>& elements);

  Standard_EXPORT occ::handle<NCollection_HArray1<occ::handle<StepBasic_DerivedUnitElement>>>
                  Elements() const;

  Standard_EXPORT int NbElements() const;

  Standard_EXPORT occ::handle<StepBasic_DerivedUnitElement> ElementsValue(const int num) const;

  DEFINE_STANDARD_RTTIEXT(StepBasic_DerivedUnit, Standard_Transient)

private:
  occ::handle<NCollection_HArray1<occ::handle<StepBasic_DerivedUnitElement>>> theElements;
};

#endif // _StepBasic_DerivedUnit_HeaderFile
