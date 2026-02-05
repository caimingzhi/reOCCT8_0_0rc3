#include <StepElement_Curve3dElementDescriptor.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepElement_Curve3dElementDescriptor, StepElement_ElementDescriptor)

//=================================================================================================

StepElement_Curve3dElementDescriptor::StepElement_Curve3dElementDescriptor() = default;

//=================================================================================================

void StepElement_Curve3dElementDescriptor::Init(
  const StepElement_ElementOrder               aElementDescriptor_TopologyOrder,
  const occ::handle<TCollection_HAsciiString>& aElementDescriptor_Description,
  const occ::handle<NCollection_HArray1<
    occ::handle<NCollection_HSequence<occ::handle<StepElement_CurveElementPurposeMember>>>>>&
    aPurpose)
{
  StepElement_ElementDescriptor::Init(aElementDescriptor_TopologyOrder,
                                      aElementDescriptor_Description);

  thePurpose = aPurpose;
}

//=================================================================================================

occ::handle<NCollection_HArray1<
  occ::handle<NCollection_HSequence<occ::handle<StepElement_CurveElementPurposeMember>>>>>
  StepElement_Curve3dElementDescriptor::Purpose() const
{
  return thePurpose;
}

//=================================================================================================

void StepElement_Curve3dElementDescriptor::SetPurpose(
  const occ::handle<NCollection_HArray1<
    occ::handle<NCollection_HSequence<occ::handle<StepElement_CurveElementPurposeMember>>>>>&
    aPurpose)
{
  thePurpose = aPurpose;
}
