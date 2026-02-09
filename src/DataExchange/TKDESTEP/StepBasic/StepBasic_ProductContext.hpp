#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepBasic_ApplicationContextElement.hpp>
class TCollection_HAsciiString;
class StepBasic_ApplicationContext;

class StepBasic_ProductContext : public StepBasic_ApplicationContextElement
{

public:
  Standard_EXPORT StepBasic_ProductContext();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>&     aName,
                            const occ::handle<StepBasic_ApplicationContext>& aFrameOfReference,
                            const occ::handle<TCollection_HAsciiString>&     aDisciplineType);

  Standard_EXPORT void SetDisciplineType(
    const occ::handle<TCollection_HAsciiString>& aDisciplineType);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> DisciplineType() const;

  DEFINE_STANDARD_RTTIEXT(StepBasic_ProductContext, StepBasic_ApplicationContextElement)

private:
  occ::handle<TCollection_HAsciiString> disciplineType;
};
