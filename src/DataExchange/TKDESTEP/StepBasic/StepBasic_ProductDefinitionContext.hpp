#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepBasic_ApplicationContextElement.hpp>
class TCollection_HAsciiString;
class StepBasic_ApplicationContext;

class StepBasic_ProductDefinitionContext : public StepBasic_ApplicationContextElement
{

public:
  Standard_EXPORT StepBasic_ProductDefinitionContext();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>&     aName,
                            const occ::handle<StepBasic_ApplicationContext>& aFrameOfReference,
                            const occ::handle<TCollection_HAsciiString>&     aLifeCycleStage);

  Standard_EXPORT void SetLifeCycleStage(
    const occ::handle<TCollection_HAsciiString>& aLifeCycleStage);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> LifeCycleStage() const;

  DEFINE_STANDARD_RTTIEXT(StepBasic_ProductDefinitionContext, StepBasic_ApplicationContextElement)

private:
  occ::handle<TCollection_HAsciiString> lifeCycleStage;
};
