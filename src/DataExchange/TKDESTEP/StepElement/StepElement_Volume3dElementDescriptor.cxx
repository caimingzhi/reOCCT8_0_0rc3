#include <StepElement_Volume3dElementDescriptor.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepElement_Volume3dElementDescriptor, StepElement_ElementDescriptor)

//=================================================================================================

StepElement_Volume3dElementDescriptor::StepElement_Volume3dElementDescriptor() = default;

//=================================================================================================

void StepElement_Volume3dElementDescriptor::Init(
  const StepElement_ElementOrder               aElementDescriptor_TopologyOrder,
  const occ::handle<TCollection_HAsciiString>& aElementDescriptor_Description,
  const occ::handle<NCollection_HArray1<occ::handle<StepElement_VolumeElementPurposeMember>>>&
                                         aPurpose,
  const StepElement_Volume3dElementShape aShape)
{
  StepElement_ElementDescriptor::Init(aElementDescriptor_TopologyOrder,
                                      aElementDescriptor_Description);

  thePurpose = aPurpose;

  theShape = aShape;
}

//=================================================================================================

occ::handle<NCollection_HArray1<occ::handle<StepElement_VolumeElementPurposeMember>>>
  StepElement_Volume3dElementDescriptor::Purpose() const
{
  return thePurpose;
}

//=================================================================================================

void StepElement_Volume3dElementDescriptor::SetPurpose(
  const occ::handle<NCollection_HArray1<occ::handle<StepElement_VolumeElementPurposeMember>>>&
    aPurpose)
{
  thePurpose = aPurpose;
}

//=================================================================================================

StepElement_Volume3dElementShape StepElement_Volume3dElementDescriptor::Shape() const
{
  return theShape;
}

//=================================================================================================

void StepElement_Volume3dElementDescriptor::SetShape(const StepElement_Volume3dElementShape aShape)
{
  theShape = aShape;
}
