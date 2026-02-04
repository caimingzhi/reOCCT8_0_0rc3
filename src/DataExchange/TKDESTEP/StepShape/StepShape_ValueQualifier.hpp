#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepShape_PrecisionQualifier;
class StepShape_TypeQualifier;
class StepShape_ValueFormatTypeQualifier;

//! Added for Dimensional Tolerances
class StepShape_ValueQualifier : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepShape_ValueQualifier();

  //! Recognizes a kind of ValueQualifier Select Type :
  //! 1 -> PrecisionQualifier from StepShape
  //! 2 -> TypeQualifier from StepShape
  //! 3 -> UnceraintyQualifier .. not yet implemented
  //! 4 -> ValueFormatTypeQualifier
  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  //! Returns Value as PrecisionQualifier
  Standard_EXPORT occ::handle<StepShape_PrecisionQualifier> PrecisionQualifier() const;

  //! Returns Value as TypeQualifier
  Standard_EXPORT occ::handle<StepShape_TypeQualifier> TypeQualifier() const;

  //! Returns Value as ValueFormatTypeQualifier
  Standard_EXPORT occ::handle<StepShape_ValueFormatTypeQualifier> ValueFormatTypeQualifier() const;
};

