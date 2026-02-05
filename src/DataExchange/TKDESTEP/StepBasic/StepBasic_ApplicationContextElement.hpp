#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class TCollection_HAsciiString;
class StepBasic_ApplicationContext;

class StepBasic_ApplicationContextElement : public Standard_Transient
{

public:
  //! Returns a ApplicationContextElement
  Standard_EXPORT StepBasic_ApplicationContextElement();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>&     aName,
                            const occ::handle<StepBasic_ApplicationContext>& aFrameOfReference);

  Standard_EXPORT void SetName(const occ::handle<TCollection_HAsciiString>& aName);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Name() const;

  Standard_EXPORT void SetFrameOfReference(
    const occ::handle<StepBasic_ApplicationContext>& aFrameOfReference);

  Standard_EXPORT occ::handle<StepBasic_ApplicationContext> FrameOfReference() const;

  DEFINE_STANDARD_RTTIEXT(StepBasic_ApplicationContextElement, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString>     name;
  occ::handle<StepBasic_ApplicationContext> frameOfReference;
};
