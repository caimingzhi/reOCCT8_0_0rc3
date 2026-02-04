#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepRepr_RepresentationItem.hpp>
class StepBasic_MeasureValueMember;
class TCollection_HAsciiString;

class StepRepr_ValueRepresentationItem : public StepRepr_RepresentationItem
{

public:
  //! Returns a ValueRepresentationItem
  Standard_EXPORT StepRepr_ValueRepresentationItem();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&     theName,
    const occ::handle<StepBasic_MeasureValueMember>& theValueComponentMember);

  inline void SetValueComponentMember(
    const occ::handle<StepBasic_MeasureValueMember>& theValueComponentMember)
  {
    valueComponentMember = theValueComponentMember;
  }

  inline occ::handle<StepBasic_MeasureValueMember> ValueComponentMember() const
  {
    return valueComponentMember;
  }

  DEFINE_STANDARD_RTTIEXT(StepRepr_ValueRepresentationItem, StepRepr_RepresentationItem)

private:
  occ::handle<StepBasic_MeasureValueMember> valueComponentMember;
};
