#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class TCollection_HAsciiString;
class StepBasic_ProductDefinitionFormation;
class StepBasic_ProductDefinitionContext;

class StepBasic_ProductDefinition : public Standard_Transient
{

public:
  //! Returns a ProductDefinition
  Standard_EXPORT StepBasic_ProductDefinition();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&             aId,
    const occ::handle<TCollection_HAsciiString>&             aDescription,
    const occ::handle<StepBasic_ProductDefinitionFormation>& aFormation,
    const occ::handle<StepBasic_ProductDefinitionContext>&   aFrameOfReference);

  Standard_EXPORT void SetId(const occ::handle<TCollection_HAsciiString>& aId);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Id() const;

  Standard_EXPORT void SetDescription(const occ::handle<TCollection_HAsciiString>& aDescription);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Description() const;

  Standard_EXPORT void SetFormation(
    const occ::handle<StepBasic_ProductDefinitionFormation>& aFormation);

  Standard_EXPORT occ::handle<StepBasic_ProductDefinitionFormation> Formation() const;

  Standard_EXPORT void SetFrameOfReference(
    const occ::handle<StepBasic_ProductDefinitionContext>& aFrameOfReference);

  Standard_EXPORT occ::handle<StepBasic_ProductDefinitionContext> FrameOfReference() const;

  DEFINE_STANDARD_RTTIEXT(StepBasic_ProductDefinition, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString>             id;
  occ::handle<TCollection_HAsciiString>             description;
  occ::handle<StepBasic_ProductDefinitionFormation> formation;
  occ::handle<StepBasic_ProductDefinitionContext>   frameOfReference;
};
