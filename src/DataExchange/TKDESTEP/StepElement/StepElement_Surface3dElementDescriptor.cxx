#include <StepElement_Surface3dElementDescriptor.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepElement_Surface3dElementDescriptor, StepElement_ElementDescriptor)

//=================================================================================================

StepElement_Surface3dElementDescriptor::StepElement_Surface3dElementDescriptor() = default;

//=================================================================================================

void StepElement_Surface3dElementDescriptor::Init(
  const StepElement_ElementOrder               aElementDescriptor_TopologyOrder,
  const occ::handle<TCollection_HAsciiString>& aElementDescriptor_Description,
  const occ::handle<NCollection_HArray1<
    occ::handle<NCollection_HSequence<occ::handle<StepElement_SurfaceElementPurposeMember>>>>>&
                                   aPurpose,
  const StepElement_Element2dShape aShape)
{
  StepElement_ElementDescriptor::Init(aElementDescriptor_TopologyOrder,
                                      aElementDescriptor_Description);

  thePurpose = aPurpose;

  theShape = aShape;
}

//=================================================================================================

occ::handle<NCollection_HArray1<
  occ::handle<NCollection_HSequence<occ::handle<StepElement_SurfaceElementPurposeMember>>>>>
  StepElement_Surface3dElementDescriptor::Purpose() const
{
  return thePurpose;
}

//=================================================================================================

void StepElement_Surface3dElementDescriptor::SetPurpose(
  const occ::handle<NCollection_HArray1<
    occ::handle<NCollection_HSequence<occ::handle<StepElement_SurfaceElementPurposeMember>>>>>&
    aPurpose)
{
  thePurpose = aPurpose;
}

//=================================================================================================

StepElement_Element2dShape StepElement_Surface3dElementDescriptor::Shape() const
{
  return theShape;
}

//=================================================================================================

void StepElement_Surface3dElementDescriptor::SetShape(const StepElement_Element2dShape aShape)
{
  theShape = aShape;
}
