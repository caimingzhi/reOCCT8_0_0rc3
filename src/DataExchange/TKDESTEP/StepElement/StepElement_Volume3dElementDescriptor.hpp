#pragma once

#include <Standard.hpp>

#include <StepElement_VolumeElementPurposeMember.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

enum StepElement_Volume3dElementShape
{
  StepElement_Hexahedron,
  StepElement_Wedge,
  StepElement_Tetrahedron,
  StepElement_Pyramid
};

#include <StepElement_ElementDescriptor.hpp>
#include <StepElement_ElementOrder.hpp>
class TCollection_HAsciiString;

class StepElement_Volume3dElementDescriptor : public StepElement_ElementDescriptor
{

public:
  Standard_EXPORT StepElement_Volume3dElementDescriptor();

  Standard_EXPORT void Init(
    const StepElement_ElementOrder               aElementDescriptor_TopologyOrder,
    const occ::handle<TCollection_HAsciiString>& aElementDescriptor_Description,
    const occ::handle<NCollection_HArray1<occ::handle<StepElement_VolumeElementPurposeMember>>>&
                                           aPurpose,
    const StepElement_Volume3dElementShape aShape);

  Standard_EXPORT occ::handle<
    NCollection_HArray1<occ::handle<StepElement_VolumeElementPurposeMember>>>
    Purpose() const;

  Standard_EXPORT void SetPurpose(
    const occ::handle<NCollection_HArray1<occ::handle<StepElement_VolumeElementPurposeMember>>>&
      Purpose);

  Standard_EXPORT StepElement_Volume3dElementShape Shape() const;

  Standard_EXPORT void SetShape(const StepElement_Volume3dElementShape Shape);

  DEFINE_STANDARD_RTTIEXT(StepElement_Volume3dElementDescriptor, StepElement_ElementDescriptor)

private:
  occ::handle<NCollection_HArray1<occ::handle<StepElement_VolumeElementPurposeMember>>> thePurpose;
  StepElement_Volume3dElementShape                                                      theShape;
};
