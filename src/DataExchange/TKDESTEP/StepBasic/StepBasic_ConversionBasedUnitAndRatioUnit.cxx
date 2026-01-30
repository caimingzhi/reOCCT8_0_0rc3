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

#include <Standard_Type.hpp>
#include <StepBasic_ConversionBasedUnitAndRatioUnit.hpp>
#include <StepBasic_DimensionalExponents.hpp>
#include <StepBasic_MeasureWithUnit.hpp>
#include <StepBasic_RatioUnit.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_ConversionBasedUnitAndRatioUnit, StepBasic_ConversionBasedUnit)

StepBasic_ConversionBasedUnitAndRatioUnit::StepBasic_ConversionBasedUnitAndRatioUnit() = default;

void StepBasic_ConversionBasedUnitAndRatioUnit::Init(
  const occ::handle<StepBasic_DimensionalExponents>& aDimensions,
  const occ::handle<TCollection_HAsciiString>&       aName,
  const occ::handle<Standard_Transient>&             aConversionFactor)
{
  // --- ANDOR component fields ---
  StepBasic_ConversionBasedUnit::Init(aDimensions, aName, aConversionFactor);

  // --- ANDOR component fields ---
  ratioUnit = new StepBasic_RatioUnit();
  ratioUnit->Init(aDimensions);
}

void StepBasic_ConversionBasedUnitAndRatioUnit::SetRatioUnit(
  const occ::handle<StepBasic_RatioUnit>& aRatioUnit)
{
  ratioUnit = aRatioUnit;
}

occ::handle<StepBasic_RatioUnit> StepBasic_ConversionBasedUnitAndRatioUnit::RatioUnit() const
{
  return ratioUnit;
}
