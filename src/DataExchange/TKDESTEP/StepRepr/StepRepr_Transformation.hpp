#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepRepr_ItemDefinedTransformation;
class StepRepr_FunctionallyDefinedTransformation;

class StepRepr_Transformation : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  //! Returns a Transformation SelectType
  Standard_EXPORT StepRepr_Transformation();

  //! Recognizes a Transformation Kind Entity that is :
  //! 1 -> ItemDefinedTransformation
  //! 2 -> FunctionallyDefinedTransformation
  //! 0 else
  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  //! returns Value as a ItemDefinedTransformation (Null if another type)
  Standard_EXPORT occ::handle<StepRepr_ItemDefinedTransformation> ItemDefinedTransformation() const;

  //! returns Value as a FunctionallyDefinedTransformation (Null if another type)
  Standard_EXPORT occ::handle<StepRepr_FunctionallyDefinedTransformation>
                  FunctionallyDefinedTransformation() const;
};
