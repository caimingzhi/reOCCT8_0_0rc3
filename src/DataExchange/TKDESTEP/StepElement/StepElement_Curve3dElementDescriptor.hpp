#pragma once

#include <Standard.hpp>

#include <StepElement_CurveElementPurposeMember.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepElement_ElementDescriptor.hpp>
#include <StepElement_ElementOrder.hpp>
class TCollection_HAsciiString;

class StepElement_Curve3dElementDescriptor : public StepElement_ElementDescriptor
{

public:
  Standard_EXPORT StepElement_Curve3dElementDescriptor();

  Standard_EXPORT void Init(
    const StepElement_ElementOrder               aElementDescriptor_TopologyOrder,
    const occ::handle<TCollection_HAsciiString>& aElementDescriptor_Description,
    const occ::handle<NCollection_HArray1<
      occ::handle<NCollection_HSequence<occ::handle<StepElement_CurveElementPurposeMember>>>>>&
      aPurpose);

  Standard_EXPORT occ::handle<NCollection_HArray1<
    occ::handle<NCollection_HSequence<occ::handle<StepElement_CurveElementPurposeMember>>>>>
                  Purpose() const;

  Standard_EXPORT void SetPurpose(
    const occ::handle<NCollection_HArray1<
      occ::handle<NCollection_HSequence<occ::handle<StepElement_CurveElementPurposeMember>>>>>&
      Purpose);

  DEFINE_STANDARD_RTTIEXT(StepElement_Curve3dElementDescriptor, StepElement_ElementDescriptor)

private:
  occ::handle<NCollection_HArray1<
    occ::handle<NCollection_HSequence<occ::handle<StepElement_CurveElementPurposeMember>>>>>
    thePurpose;
};
