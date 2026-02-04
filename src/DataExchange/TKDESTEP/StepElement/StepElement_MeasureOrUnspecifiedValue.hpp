#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
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


enum StepElement_UnspecifiedValue
{
  StepElement_Unspecified
};


class Standard_Transient;
class StepData_SelectMember;

//! Representation of STEP SELECT type MeasureOrUnspecifiedValue
class StepElement_MeasureOrUnspecifiedValue : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_EXPORT StepElement_MeasureOrUnspecifiedValue();

  //! Recognizes a kind of MeasureOrUnspecifiedValue select type
  //! return 0
  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  //! Recognizes a items of select member MeasureOrUnspecifiedValueMember
  //! 1 -> ContextDependentMeasure
  //! 2 -> UnspecifiedValue
  //! 0 else
  Standard_EXPORT int CaseMem(const occ::handle<StepData_SelectMember>& ent) const override;

  //! Returns a new select member the type MeasureOrUnspecifiedValueMember
  Standard_EXPORT occ::handle<StepData_SelectMember> NewMember() const override;

  //! Set Value for ContextDependentMeasure
  Standard_EXPORT void SetContextDependentMeasure(const double aVal);

  //! Returns Value as ContextDependentMeasure (or Null if another type)
  Standard_EXPORT double ContextDependentMeasure() const;

  //! Set Value for UnspecifiedValue
  Standard_EXPORT void SetUnspecifiedValue(const StepElement_UnspecifiedValue aVal);

  //! Returns Value as UnspecifiedValue (or Null if another type)
  Standard_EXPORT StepElement_UnspecifiedValue UnspecifiedValue() const;
};

