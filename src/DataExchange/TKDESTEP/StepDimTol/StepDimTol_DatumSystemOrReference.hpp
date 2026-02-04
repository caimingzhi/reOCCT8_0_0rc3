#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>

class Standard_Transient;
class StepDimTol_DatumSystem;
class StepDimTol_DatumReference;

class StepDimTol_DatumSystemOrReference : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  //! Returns a DatumSystemOrReference select type
  Standard_EXPORT StepDimTol_DatumSystemOrReference();

  //! Recognizes a DatumSystemOrReference Kind Entity that is :
  //! 1 -> DatumSystem
  //! 2 -> DatumReference
  //! 0 else
  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  //! returns Value as a DatumSystem (Null if another type)
  Standard_EXPORT occ::handle<StepDimTol_DatumSystem> DatumSystem() const;

  //! returns Value as a DatumReference (Null if another type)
  Standard_EXPORT occ::handle<StepDimTol_DatumReference> DatumReference() const;
};
