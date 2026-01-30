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
#include <StepBasic_ConversionBasedUnitAndTimeUnit.hpp>
#include <StepBasic_DimensionalExponents.hpp>
#include <StepBasic_MeasureWithUnit.hpp>
#include <StepBasic_TimeUnit.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_ConversionBasedUnitAndTimeUnit, StepBasic_ConversionBasedUnit)

StepBasic_ConversionBasedUnitAndTimeUnit::StepBasic_ConversionBasedUnitAndTimeUnit() = default;

void StepBasic_ConversionBasedUnitAndTimeUnit::Init(
  const occ::handle<StepBasic_DimensionalExponents>& aDimensions,
  const occ::handle<TCollection_HAsciiString>&       aName,
  const occ::handle<Standard_Transient>&             aConversionFactor)
{
  // --- ANDOR component fields ---
  StepBasic_ConversionBasedUnit::Init(aDimensions, aName, aConversionFactor);

  // --- ANDOR component fields ---
  timeUnit = new StepBasic_TimeUnit();
  timeUnit->Init(aDimensions);
}

void StepBasic_ConversionBasedUnitAndTimeUnit::SetTimeUnit(
  const occ::handle<StepBasic_TimeUnit>& aTimeUnit)
{
  timeUnit = aTimeUnit;
}

occ::handle<StepBasic_TimeUnit> StepBasic_ConversionBasedUnitAndTimeUnit::TimeUnit() const
{
  return timeUnit;
}
